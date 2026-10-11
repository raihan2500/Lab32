#include<bits/stdc++.h>
using namespace std;

int turn = 0;

void process1(){
  for(int i = 0; i < 5; i++){
    while(turn != 0);
    cout << "Process 1 is in critical section\n";
    turn = 1;
    cout << "Process 1 doing other job\n";
  }
}


void process2(){
  for(int i = 0; i < 5; i++){
    while(turn != 1);
    cout << "Process 2 is in critical section\n";
    turn = 0;
    cout << "Process 2 doing other jobs\n";
  }
}

int32_t main(){
  thread t1(process1);
  thread t2(process2);

  t1.join();
  t2.join();
}