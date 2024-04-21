#include <iostream>
using namespace std;

int main() {
int ages[5];
int k;
float h = 0;

for (int i = 0; i < 5; ++i) {
cin >> ages[i];};
k = ages[0];
for (int i =0; i<5;i++)
{
if(ages[i]< k){
k = ages[i];
}
}

h =(50.0-50.0*k/100.0);
cout << h << endl;

return 0;
}
