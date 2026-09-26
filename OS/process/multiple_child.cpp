#include<bits/stdc++.h>
#include <sys/wait.h>

using namespace std;

int main(){
  cout << "Parent started." << endl << endl;
  for(int i = 1; i <= 3; i++){
    pid_t pid = fork();
    if(pid < 0){
      cout << "Fork failed\n";
      exit(1);
    }else if(pid == 0){
      cout << "Child: " << i <<" is running" << endl;
      cout << "Child PID: " << getpid() << endl;
      cout << "Parent PID: " << getppid() << endl;
      cout << "Child: " << i <<" finished.\n" << endl;
      exit(0);
    }else{
      wait(NULL);
    }
  }
  cout << "Parent finished\n";
}