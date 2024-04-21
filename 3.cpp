#include <iostream>
using namespace std;

int main() {
 int num;
    cin >> num;
    while (num >0) {
        cout << num << endl;
        
        if (num % 5 == 0){
            cout << "Beep"<<endl;
        }
        num--;
    }
    return 0;
}
