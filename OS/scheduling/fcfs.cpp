#include<bits/stdc++.h>
using namespace std;

#define nl cout << endl;

struct Process{
  int pid, at, bt;
  int ct, tat, wt;
  void show(){
    cout << pid <<"\t" << at <<"\t" << bt <<"\t" << ct <<"\t" << tat <<"\t" << wt << endl;
  }
};

struct Gantt{
  int pid, start, end;
};

void showGanttChart(vector<Gantt> g){
  cout << "\n\nGantt Chart\n\n";
  for(auto x : g){
    cout <<"| P" << x.pid <<" ";
  }
  cout << "|\n";
  cout << g[0].start;
  for(auto x : g){
    cout << setw(5) << x.end;
  }
  nl;
}

int32_t main(){
  int n = 0; 
  cin >> n;
  vector<Process> p(n);
  for(int i = 0; i < n; i++){
    p[i].pid = i + 1;
    cin >> p[i].at >> p[i].bt;

  }

  sort(p.begin(), p.end(), [](Process a, Process b){
    if(a.at == b.at)return a.pid < b.pid;
    return a.at < b.at;
  });

  int curTime = 0;
  vector<Gantt> g;
  for(int i = 0; i < n; i++){
    if(curTime < p[i].at){
      curTime = p[i].at;
    }
    curTime += p[i].bt;
    g.push_back({p[i].pid, curTime - p[i].bt, curTime});

    p[i].ct = curTime;
    p[i].tat = p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;
  }

  cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

  double totTat = 0, totWt = 0;
  for(auto i : p){
    totTat += i.tat;
    totWt += i.wt;
    i.show();
  }
  totTat /= n; totWt /= n;
  nl;
  cout << "Total turnaround time: " << totTat << endl;
  cout << "Total waiting time: " << totWt << endl;

  showGanttChart(g);

  
}

/*
Input Format:
First enter the number of processes (n).
Then enter Arrival Time (AT) and Burst Time (BT) for each process.

Example Input:
5
0 5
1 3
2 8
3 6
4 4

Algorithm:
- The processes are sorted according to Arrival Time (AT).
- If two processes have the same arrival time, the process with the smaller PID executes first.
- This program implements FCFS (First Come First Serve) CPU Scheduling.
- It calculates Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Finally, it displays the average turnaround time, average waiting time, and Gantt Chart.
*/