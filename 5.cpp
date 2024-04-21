#include <iostream>
using namespace std;

bool isPalindrome(int n) {
    //завершите функцию
int n0= n, m = 0;
    while(n!=0)     
    {
        m *= 10;   
        m += n%10;
        n = n/10;
    }   
    return (m == n0);
}


int main() {
    int n;
    cin >>n;
    
    if(isPalindrome(n)) {
        cout <<n<<" is a palindrome";
    }
    else {
        cout << n<<" is NOT a palindrome";
    }
    return 0;
}
