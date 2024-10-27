/*
Certain positive integers have their decimal representation consisting only of ones and zeros, and having at least one digit one, e.g. 101. If a positive integer does not have such a property, one can try to multiply it by some positive integer to find out whether the product has this property.
*/

#include <iostream>
#include <vector>
using namespace std;

int smallestMultiple(int n){

}

int main()
{
    int testCases;
    cout<<"Number of test cases: ";
    cin>>testCases;
    for(int i =0; i<testCases; i++){
        int n;
        cout<<"Input n: ";
        cin>>n;
        cout<<"Smallest multiple of "<<n<<"consisting only of digits 1 and 0 is "<<smallestMultiple(n)<<endl;

    }
    return 0;
}
/*
Input:
3
17
11011
17

Output:
11101
11011
11101
*/