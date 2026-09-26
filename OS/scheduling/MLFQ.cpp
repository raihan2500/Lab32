#include<bits/stdc++.h>
using namespace std;

#define nl cout << endl;

struct Process{
  int pid, at, bt, priority;
  int ct, tat, wt, queue_no;
  int rem_bt;
  bool finished = false, vis = false;

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
    if(x.pid == -1){
      cout <<"|Idle";
    }else{
      cout <<"| P" << x.pid <<" ";
    }
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
  vector<Gantt> g;
  for(int i = 0; i < n; i++){
    p[i].pid = i + 1;
    cin >> p[i].at >> p[i].bt;
    p[i].rem_bt = p[i].bt;
  }

  queue<int> q1, q2, q3;
  int tq1 = 2, tq2 = 4; //Time quantum for round robin 1 and 2 

  int curTime = 0, completed = 0;

  auto doneTask = [&](int i){
    p[i].ct = curTime;
    p[i].tat = p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;
    p[i].finished = true;
    completed++;
  };

  while(completed < n){
    for(int i = 0; i < n; i++){
      if(!p[i].finished and p[i].at <= curTime and !p[i].vis){
        q1.push(i);
        p[i].vis = true;
      }
    }

    if(!q1.empty()){
      int i = q1.front(); 
      q1.pop();
      int runTime = min(tq1, p[i].rem_bt);
      g.push_back({p[i].pid, curTime, curTime + runTime});
      curTime += runTime;
      p[i].rem_bt -= runTime;

      if(p[i].rem_bt == 0){
        doneTask(i);
      }else{
        q2.push(i);
      }

    }else if(!q2.empty()){
      int i = q2.front(); 
      q2.pop();

      int runTime = min(tq2, p[i].rem_bt);
      g.push_back({p[i].pid, curTime, curTime + runTime});

      curTime += runTime;
      p[i].rem_bt -= runTime;

      if(p[i].rem_bt == 0){
        doneTask(i);
      }else{
        q3.push(i);
      }

    }else if(!q3.empty()){
      int i = q3.front();
      q3.pop();
      g.push_back({p[i].pid, curTime, curTime + p[i].rem_bt});
      curTime += p[i].rem_bt;
      p[i].rem_bt = 0;

      doneTask(i);

    }else {
      g.push_back({-1, curTime, curTime + 1});
      curTime++;
    }
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
- This program implements Multilevel Queue Scheduling.
- Three priority levels are used:
    Queue 1 -> Round Robin Scheduling (Time Quantum = 2)
    Queue 2 -> Round Robin Scheduling (Time Quantum = 4)
    Queue 3 -> FCFS execution for remaining processes
- All newly arrived processes enter Queue 1 first.
- If a process is not completed in Queue 1, it moves to Queue 2.
- If it is still not completed in Queue 2, it moves to Queue 3.
- Higher priority queues are always executed before lower priority queues.
- The program calculates Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Finally, it displays average TAT, average WT, and the Gantt Chart.
*/