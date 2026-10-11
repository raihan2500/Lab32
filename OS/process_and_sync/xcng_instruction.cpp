#include<iostream>
#include<atomic>
#include<thread>
using namespace std;

atomic<int> lock(0);


void process(int id){
  int key = 1;
  while(key == 1){
    key = atomic_exchange(&lock, key);
  }
  cout << "Process " << id << " entered critical section\n";
  for(int i = 0; i < 1e7; i++);
  cout << "Process " << id << " entered critical section\n";
  lock = 0;
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