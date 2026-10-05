#include<bits/stdc++.h>
using namespace std;

#define int long long

#ifdef DEBUG
#include<algo/debug.h>
#include<algo/resources.h>
#else
#   define clog if (0) cerr
#   define DB(...)
#   define db(...) "" 
#endif

const int M = 1e9 + 7;
const int N = 2e5 + 10;


int32_t main(){
  int n, m;
  cin >> n >> m;
  vector<int> avail(m), work(m), finished(n);
  vector<vector<int>> mx(n, vector<int>(m)), alloc = mx, need = mx;

  for(int i = 0; i < m; i++)cin >> avail[i];
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> mx[i][j];
    }
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> alloc[i][j];
      need[i][j] = mx[i][j] - alloc[i][j];
    }
  }


  work = avail;

  auto check = [&](int i){
    for(int j = 0; j < m; j++){
      if(need[i][j] > work[j]){
        return false;
      }
    }
    for(int j = 0; j < m; j++){
      work[j] += alloc[i][j];
    }
    return true;
  };

  vector<int> safe_sequence;
  int completed = 0;
  while(completed < n){
    bool flg = false;
    for(int i = 0; i < n; i++){
      if(!finished[i] and check(i)){
        flg = true;
        completed++;
        finished[i] = true;
        safe_sequence.push_back(i);
      }
    }
    if(!flg)break;
  }


  if(completed < n){
    cout << "System is unsafe\n";
  }else{
    cout << "System is safe\n";
    cout << "Safe sequence: ";
    for(int i = 0; i < n; i++){
      cout << "T"<< safe_sequence[i];
      if(i < n - 1)cout << " -> ";
    }
  }

}


/*
Algorithm: Banker's Safety Algorithm

Description:
This program checks whether a system with multiple instances of resources
is in a safe state using the Banker's Algorithm. It calculates the Need
matrix using:

        Need = Max - Allocation

Then it repeatedly checks whether any process can complete with the currently
available resources. If a process can finish, its allocated resources are
released back to the Work vector, and the process is added to the safe sequence.

If all processes can complete, the system is considered safe and the program
prints a possible safe execution sequence. Otherwise, the system is unsafe.

Input Format:
First line:
    n m
    n = number of processes
    m = number of resource types

Second line:
    Available resources (m values)

Next n lines:
    Maximum resource requirement matrix (Max)

Next n lines:
    Current allocation matrix (Allocation)

Output Format:
If the system is safe:
    System is safe
    Safe sequence: T0 -> T1 -> T2 ...

If the system is unsafe:
    System is unsafe


Example Input:
5 3

3 3 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2


Example Output:
System is safe
Safe sequence: T1 -> T3 -> T4 -> T0 -> T2
*/