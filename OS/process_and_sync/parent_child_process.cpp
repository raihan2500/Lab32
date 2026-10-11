#include<bits/stdc++.h>
#include <sys/wait.h>

using namespace std;

int main(){
    pid_t pid;
    cout << "Parent process started" << endl;
    cout << "Parrent PID: " << getpid() << endl << endl;
    pid = fork();

    if(pid < 0){
        cout << "Fork failed\n";
        exit(1);
    }else if(pid == 0){
        cout << "Child process executing\n";
        cout << "Child PID: " << getpid() << endl;
        cout << "Child Parent PID: " << getppid() << endl;
        cout << "Child process finished\n\n";
    }else{
        wait(NULL);
        cout << "Parent Process Executing\n";
        cout << "Parent PID: " << getpid() << endl;
        cout << "Parent process Terminated\n";
    }
}