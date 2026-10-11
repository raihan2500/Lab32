#include<bits/stdc++.h>
using namespace std;

atomic_flag lock_flag = ATOMIC_FLAG_INIT;

bool TSL(){
  return lock_flag.test_and_set();
}

void process(int id){
  cout << "Process " << id << " is trying to enter critical section\n";
  while(TSL()){
    //waiting
  } 
  cout << "Process " << id <<" is in critical section now\n";
  cout << "Process " << id << " is executing...\n";
  for(int i = 0; i < 1e7; i++);

  cout << "Process " << id <<" leaving critical section\n";
  lock_flag.clear();
  cout << "Process " << id <<" released critial section\n"; 
}

int32_t main(){
  thread p1(process, 1);
  thread p2(process, 2);
  thread p3(process, 3);

  p1.join();
  p2.join();
  p3.join();
  cout << "Done\n"; 
}