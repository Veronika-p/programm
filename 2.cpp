#include <iostream>
using namespace std;

int main(){
int b,c,d;
int a = 50;

cin >>b;
if (a > b) {
while(a> b){
    c = b % a;
    d = a - c;
     break;
}
cout << d;
}

 else if(a < b){
 while(a< b){

    c = b % a;
    d = a - c;
    break;
  }
  cout << d;
 }
}
