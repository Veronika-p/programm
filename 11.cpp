function [ T ] = DecreaseTemperature( initialTemperature, i)
%initialTemperature - начальная температура
%i - номер итерации
T = initialTemperature * 0.1 / i; 
end
function [ P ] = GetTransitionProbability( dE, T )
     P = exp(-dE/T);
end
function [ a ] = IsTransition(probability)
    value = rand(1);

    if(value <= probability)
        a = 1;
    else
        a = 0; 
    end

end
data = rand(2,100)*10;
function [ seq ] = GenerateStateCandidate(seq)
	%seq - предыдущее состояние (маршрут), из которого 
    %мы хотим получить состояние-кандидат
    
    n = size(seq,1); % определяем размер последовательности
    i = randi(n,1); % генерируем целое случайное число
    j = randi(n, 1);% генерируем целое случайное число
        
    if(i > j) 
        seq(j:i) = flipud(seq(j:i)); % обращаем подпоследовательность
    else
        seq(i:j) = flipud(seq(i:j));% обращаем подпоследовательность
    end

end
function [ state ] = SimulatedAnnealing( cities, initialTemperature, endTemperature)

    n = size(cities,1); % получаем размер вектора городов

    state = randperm(n); % задаём начальное состояние, как случайный маршрут
    % Функция randperm(n) - генерирует случайныую последовательность из целых чисел от 1 до n
    
    currentEnergy = CalculateEnergy(state, cities); % вычисляем энергию для первого состояния
    T = initialTemperature;
    
    for i = 1:100000  %на всякий случай ограничеваем количество итераций
    % может быть полезно при тестировании сложных функций изменения температуры T       

        stateCandidate = GenerateStateCandidate(state); % получаем состояние-кандидат
        candidateEnergy = CalculateEnergy(stateCandidate, cities); % вычисляем его энергию
        
        if(candidateEnergy < currentEnergy) % если кандидат обладает меньшей энергией
            currentEnergy = candidateEnergy; % то оно становится текущим состоянием
            state = stateCandidate;
        else
            p = GetTransitionProbability(candidateEnergy-currentEnergy, T); % иначе, считаем вероятность
            if (MakeTransit(p)) % и смотрим, осуществится ли переход
                currentEnergy = candidateEnergy;
                state = stateCandidate;
            end
        end;

        T = DecreaseTemperature(initialTemperature, i) ; % уменьшаем температуру
        
        if(T <= endTemperature) % условие выхода
            break;
        end;
    end

end

