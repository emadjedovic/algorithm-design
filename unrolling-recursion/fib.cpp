#include <iostream>
#include <stack>
using namespace std;

// an example of a function that returns a value

int fib1(int n) {
  if(n<3) return 1;
  else return fib0(n-1)+fib0(n-2); // two recursive calls
}

int fib2(int n) {
  int rez,a,b;
  if(n<3) rez=1;
  else {
    // created variables for the recursive calls as well as a "result" variable
    a=fib1(n-1);
    b=fib1(n-2);
    rez=a+b;
  }
  return rez;
}

// add resursion stack, goto and labels to replace the recursive calls
int fib3(int n) {
   int rez,a,b;
   stack<int> s;
X: if(n<3) rez=1;
   else {
    // stack the formal parameters and the number of the recursive call
     s.push(a); s.push(b); s.push(n); s.push(1);
     // assign the values of the real parameters to the formal parameters
     n-=1;
     // replace the recursive call with a goto statement
     goto X;
Y:   a=rez;
     s.push(a); s.push(b); s.push(n); s.push(2);
     n-=2;
     goto X;
Z:   b=rez;
     rez=a+b;
   }

   // simulate the return from the recursive calls
   if(!s.empty()) {
     int gdje=s.top(); s.pop();
     n=s.top(); s.pop();
     b=s.top(); s.pop();
     a=s.top(); s.pop();
     if(gdje==1) goto Y; // first recursive call
     else goto Z; // second recursive call
   }
   return rez;
}

// got rid of variable b
int fib4(int n) {
   int rez,a;
   stack<int> s;
X: if(n<3) rez=1;
   else {
     s.push(a); s.push(n); s.push(1);
     n-=1;
     goto X;
Y:   a=rez;
     s.push(a); s.push(n); s.push(2);
     n-=2;
     goto X;
Z:   rez+=a;
   }
   if(!s.empty()) {
     int gdje=s.top(); s.pop();
     n=s.top(); s.pop();
     a=s.top(); s.pop();
     if(gdje==1) goto Y;
     goto Z;
   }
   return rez;
}

// since the label Z was only called from the "if" block, we moved it there
int fib5(int n) {
   int rez,a;
   stack<int> s;

X: if(n<3) rez=1;
   else {
     s.push(a); s.push(n); s.push(1);
     n-=1;
     goto X;
Y:   a=rez;
     s.push(a); s.push(n); s.push(2);
     n-=2;
     goto X;
   }
  
Z: if(!s.empty()) {
     int gdje=s.top(); s.pop();
     n=s.top(); s.pop();
     a=s.top(); s.pop();
     if(gdje==1) goto Y; // the only place we jump to Y
     rez+=a; // here
     goto Z; 
   }
   return rez;
}

// moved the Y label to the "if" block because that's where it's needed
int fib6(int n) {
   int rez,a;
   stack<int> s;
X: if(n<3) rez=1;
   else {
     s.push(a); s.push(n); s.push(1);
     n-=1;
     goto X;
   }
Z: if(!s.empty()) {
     int gdje=s.top(); s.pop();
     n=s.top(); s.pop();
     a=s.top(); s.pop();
     if(gdje==1) {
        // moved the Y label here
       a=rez;
       s.push(a); s.push(n); s.push(2);
       n-=2;
       goto X;
     }
     rez+=a;
     goto Z;
   }
   return rez;
}

int fib7(int n) {
   int rez;
   stack<int> s;
X: if(n<3) rez=1;
   else {
    // the variable "a" is not used here anymore
     s.push(n); s.push(1);
     n-=1;
     goto X;
   }
Z: if(!s.empty()) {
     int gdje=s.top(); s.pop();
     n=s.top(); s.pop();
     // we no longer have variable "a" on the stack
     if(gdje==1) {
       s.push(rez); s.push(n); s.push(2);
       n-=2;
       goto X;
     }
     rez+=s.top(); s.pop();
     goto Z;
   }
   return rez;
}

int fib8(int n) {
   int rez;
   stack<int> s;
   // cannot completely remove X label because it's being called in the next "while" block
X: while(n>=3) {
     s.push(n); s.push(1);
     n-=1;
   }
   rez=1;
   // this used to be a simple loop-like behaviour as well
   while(!s.empty()) {
     int gdje=s.top(); s.pop();
     n=s.top(); s.pop();
     if(gdje==1) {
       s.push(rez); s.push(n); s.push(2);
       n-=2; goto X;
     }
     rez+=s.top(); s.pop();
   }
   return rez;
}

int fibFinal(int n) {
  int rez;
  stack<int> s;
  while(n>=3) {
    s.push(n); s.push(1);
    n-=1;
  }
  rez=1;
  while(!s.empty()) {
    int gdje=s.top(); s.pop();
    n=s.top(); s.pop();
    if(gdje==1) {
      s.push(rez); s.push(n); s.push(2);
      n-=2;
      // inserted the "X" block here so to avoid the "goto" statement
      while(n>=3) {
        s.push(n); s.push(1);
        n-=1;
      }
      rez=1;
    }
    else {
      rez+=s.top(); s.pop();
    }
  }
  return rez;
}