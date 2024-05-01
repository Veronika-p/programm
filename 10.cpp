struct AntPath {
    std::vector<std::size_t> vertices;
    double distance = 0;
};

struct Ant {
     explicit Ant(std::size_t start_vertex = 0);

     AntPath path;

     std::vector<std::size_t> visited;
     std::size_t start_location = 0, current_location = 0;
     bool can_continue = true;

     void MakeChoice(const Graph<double> &g, const Matrix<double> &p, double a, double b);
     double getRandomChoice();
     std::vector<std::size_t> getNeighborVertexes(const Graph<double> &g)
};

class AntColonyOptimization {
public:
    explicit AntColonyOptimization(const Graph<double> &graph);

    AntPath SolveSalesmansProblem();

private:
    const double kAlpha_ = 1.0;
    const double kBeta_ = 2.0;
    const double kPheromone0_ = 1;
    const double kQ_ = 5.0;
    const double kEvaporation_ = 0.2;

    Graph<double> graph_;
    Matrix<double> pheromone_;

    std::vector<Ant> ants_;

    void CreateAnts();
    void UpdateGlobalPheromone(const Matrix<double> &local_pheromone_update);
};
AntColonyOptimization::AntColonyOptimization(const Graph<double> &graph)
        : graph_(graph), kQ_(0.015 * graph.getGraphWeight()) {
   const std::size_t kVertexesCount = graph_.getVertexesCount();
   Matrix<double> matrix(kVertexesCount);
   for (std::size_t row = 0; row != kVertexesCount; ++row)
       for (std::size_t col = 0; col != kVertexesCount; ++col)
           if (row != col) matrix(row, col) = kPheromone0_;

   pheromone_ = std::move(matrix);
}
void AntColonyOptimization::CreateAnts() {
    const auto kAntsCount = graph_.getVertexesCount();
    ants_.resize(kAntsCount);

    for (std::size_t i = 0, size = ants_.size(); i != size; ++i)
        ants_[i] = Ant(i);
}
void AntColonyOptimization::UpdateGlobalPheromone(const Matrix<double> &lpu) {
    // lpu - local pheromone update
    for (std::size_t from = 0, size = lpu.getRows(); from != size; ++from) {
        for (std::size_t to = 0; to != size; ++to) {
            pheromone_(from, to) = (1 - kEvaporation_) * pheromone_(from, to) + lpu(from, to);
            if (pheromone_(from, to) < 0.01 and from != to)
                pheromone_(from, to) = 0.01;
        }
    }
}
double Ant::getRandomChoice() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    std::default_random_engine re(system_clock::now().time_since_epoch().count());
    return dist(re);
}
std::vector<std::size_t> Ant::getNeighborVertexes(const Graph<double> &g) {
    std::vector<std::size_t> vertexes;
    for (std::size_t to = 0; to != graph.getVertexesCount(); ++to) {
         bool edge_is_exist = g(current_location, to) != 0;
         bool vertex_is_unvisited = std::find(visited.begin(), visited.end(), to) == visited.end()
         if (edge_is_exist and vertex_is_unvisited)
              vertexes.push_back(to);
    }
    return vertexes;   
}
void Ant::MakeChoice(const Graph<T> &g, const Matrix<double> &p, double a, double b) {
    if (path.vertices.empty()) {
        path.vertices.push_back(current_location);
        visited.push_back(current_location);
    }

   std::vector<std::size_t> neighbor_vertexes = getNeighborVertexes(g);

   if (neighbor_vertexes.empty()) {
       can_continue = false;
       if (graph(current_location, start_location) != 0) {
           path.vertices.push_back(start_location);
           path.distance += graph(current_location, start_location);
       }
       return;
  }

   std::vector<double> choosing_probability(neighbor_vertexes.size());

   {
        // Подсчет вероятности перехода муравья из одной вершины в другую
        std::vector<double> wish;
        std::vector<double> probability; 
        double summary_wish = 0.0f;
        for (auto v : neighbor_vertexes) {
                double t = p(current_location, v);
                double w = g(current_location, v);
                double n = 1 / w;
                wish.push_back(std::pow(t, alpha) * std::pow(n, beta));
                summary_wish += wish.back();
       }

       for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size(); ++neighbor) {
           probability.push_back(wish[neighbor] / summary_wish);
           if (neighbor == 0)
               choosing_probability[neighbor] = probability.back();
           else
               choosing_probability[neighbor] = choosing_probability[neighbor - 1] + probability.back();
        }
   }

   // Определение следующей вершины, которую посетит муравей
   std::size_t next_vertex = 0;
   double choose = getRandomChoice();

   for (std::size_t n = 0; n != neighbor_vertexes.size(); ++n ) {
       if (choose <= choosing_probability[n ]) {
           next_vertex = neighbor_vertexes[n ];
           break;
       }
   }

   path.vertices.push_back(next_vertex);
   path.distance += graph(current_location, next_vertex);
   visited.push_back(next_vertex);
   current_location = next_vertex;
}
AntPath AntColonyOptimization::SolveSalesmansProblem() {
    if (graph_.IsEmpty())
         return {};

    constexpr std::size_t kMaxIterationsWithoutImprovement = 100;
    const std::size_t kVertexesCount = graph_.getVertexesCount();
    std::size_t counter = 0;

    AntPath path;
    path.distance = kInf<double>;

    while (counter++ != kMaxIterationsWithoutImprovement) {
        Matrix<double> local_pheromone_update(kVertexesCount, 0.0);
        CreateAnts();

        for (auto &ant : ants_) {
            while (ant.can_continue)
                ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);

            auto ant_path = ant.path;
            if (ant_path.vertices.size() == kVertexesCount + 1) {
                 if (path.distance > ant.path.distance) {
                     path = std::move(ant.path);
                     counter = 0;
                }

                for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v)
                    local_pheromone_update(ant_path.vertices[v], ant_path.vertices[v + 1]) += kQ_ / ant_path.distance;
            }
        }
        UpdateGlobalPheromone(local_pheromone_update);
    }
    return path;
}
