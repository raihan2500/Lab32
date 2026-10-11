#include<bits/stdc++.h>
#include <wait.h>
using namespace std;

void withdraw(int amount){
  ifstream in("balance.txt");
  int balance; 
  in >> balance;
  balance -= amount;
  in.close();
  
  sleep(1);
  ofstream out("balance.txt");
  out << balance;
  out.close();
}

int32_t main(){

  int pid1 = fork();
  if(pid1 == 0){
    withdraw(500);
    cout << "Child 1 finished\n";
    exit(0);
  }

  int pid2 = fork();
  if(pid2 == 0){
    withdraw(300);
    cout << "Child 2 finished\n";
    exit(0);
  }


  wait(NULL);
  wait(NULL);

  ifstream in("balance.txt");
  int balance; 
  in >> balance;
  cout << "Final balance: " << balance << endl;
  in.close();
}