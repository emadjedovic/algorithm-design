#include <iostream>
#include <stack>
using namespace std;

// an example of a function that doesn't return a value

/*
N - number of disks
A - source (1, 2 or 3)
B - destination (1, 2 or 3)
C - auxiliary (1, 2 or 3) = 6-A-B
*/
void Hanoi1(int N,int A,int B) {
  if(N!=0) {
    Hanoi(N-1,A,6-A-B); // Move N-1 disks from A to C
    Hanoi(N-1,6-A-B,B); // Move N-1 disks from C to B
  }
}

void Hanoi2(int N,int A,int B) {
X: if(N!=0) {
     Hanoi(N-1,A,6-A-B);
     // replaced a recursive call with a label and a goto
     N--; A=6-A-B;
     goto X;
   }
}

void Hanoi3(int N,int A,int B) {
  while(N!=0) {
    Hanoi(N-1,A,6-A-B);
    N--; A=6-A-B;
    // turned a goto into a while loop
  }
}

void Hanoi4(int N,int A,int B) {
   stack<int> s;
X: while(N!=0) {
    // the same procedure for the first recursive call, but pushing the formal parameters onto the stack first
     s.push(N); s.push(A); s.push(B);
     N--; B=6-A-B;
     goto X;
Y:   N--; A=6-A-B;
   }
   // reading from the stack
   if(!s.empty()) {
     B=s.top(); s.pop();
     A=s.top(); s.pop();
     N=s.top(); s.pop();
     goto Y;
   }
}

void Hanoi5(int N,int A,int B) {
   stack<int> s;
X: while(N!=0) {
     s.push(N); s.push(A); s.push(B);
     N--; B=6-A-B;
     goto X;
   }
   if(!s.empty()) {
     B=s.top(); s.pop();
     A=s.top(); s.pop();
     N=s.top(); s.pop();
     // moved the Y label here
     N--; A=6-A-B;
     goto X;
   }
}

void HanoiFinal(int N,int A,int B) {
  stack<int> s;
  while(true) {
    while(N!=0) {
      s.push(N); s.push(A); s.push(B);
       N--; B=6-A-B;
       // remove the goto
    }
    if(s.empty()) break;
    B=s.top(); s.pop();
    A=s.top(); s.pop();
    N=s.top(); s.pop();
    N--; A=6-A-B;
    // replaced this goto X with while(true) loop
  }
}
