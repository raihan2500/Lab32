#include<iostream>
#include<thread> 
#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;

#define BUFFER_SIZE 5
queue<int> buffer;
mutex mtx;
condition_variable empt, full;

void producer(){
  int item = 0;
  while(true){
    item++;
    unique_lock<mutex> lock(mtx);
    empt.wait(lock, [](){
      return buffer.size() < BUFFER_SIZE;
    });
    buffer.push(item);
    cout << "Producer: " << item << endl;
    lock.unlock();
    full.notify_one();
  }
}

void consumer(){
  while(true){
    unique_lock<mutex> lock(mtx);
    full.wait(lock, [](){
      return !buffer.empty();
    });
    int item = buffer.front();
    buffer.pop();
    cout << "Consumed: " << item << endl;
    lock.unlock();
    empt.notify_one();
  }
}

int main(){
  thread p(producer);
  thread c(consumer);
  p.join();
  c.join();
}