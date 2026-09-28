#include<bits/stdc++.h>
#include<atomic>
using namespace std;

atomic<bool> flag[2];
atomic<int> turn = 1;

void process1(){
  for(int i = 0; i < 5; i++){
    
    flag[0] = true; //process 1 need to use
    turn = 1; //check if process2 needs or not
    
    while(flag[1] == 1 and turn == 1);

    cout << "Process 1 is in critical section\n";
    flag[0] = false;
    cout << "Process 1 doing other job\n";
  }
}


void process2(){
  for(int i = 0; i < 5; i++){
    flag[1] = true; //process 2 needs to enter critical section
    turn = 0; //check if Process1 needs it or not
    while(flag[0] and turn == 0);

    cout << "Process 2 is in critical section\n";

    flag[1] = false;

    cout << "Process 2 doing other jobs\n";
  }
}

int32_t main(){
  flag[0] = flag[1] = false;
  thread t1(process1);
  thread t2(process2);

  t1.join();
  t2.join();
}