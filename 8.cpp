#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <clocale>
using namespace std;
 
int main() 
{ 
    setlocale(LC_ALL,"Rus");
    string s;
    set<string> vs;
    ifstream ff("Text.dat");
    if(ff)
    {
        while( getline(ff,s) )
            vs.insert(s);
        for(set<string>::iterator p=vs.begin();p!=vs.end();++p)
            cout<<*p<<endl;
    }
    system("pause");
    return 0; 
}
