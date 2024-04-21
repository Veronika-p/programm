#include<iostream>
using namespace std;
int main()
{
    int x1, y1;
    int x2, y2;
    bool otv = false;
    cin >> x1;
    cin >> y1;
    cin >> x2;
    cin >> y2;
    for(int i = 0; i < 8; i++)
    {
        if(x1 == x2+i && y1 == y2+i)
        otv = true;
        if(x1 == x2-i && y1 == y2-i)
        otv = true;
    }
    cout << boolalpha << otv << endl;
    return 0;
}
