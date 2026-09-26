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
  vector<Gantt> g;
  vector<Process> p(n);
  vector<int> rem(n);
  for(int i = 0; i < n; i++){
    p[i].pid = i + 1;
    cin >> p[i].at >> p[i].bt;
    rem[i] = p[i].bt;
  }


  int curTime = 0;
  int completed = 0;
  int exc = 1;

  while(completed < n){
    int selected = -1;
    for(int i = 0; i < n; i++){
      if(p[i].at <= curTime and rem[i]){
        if(selected == -1 or rem[i] < rem[selected] or (rem[i] == rem[selected] and p[i].at < p[selected].at)){
          selected = i;
        }
      }
    }

    if(selected == -1){
      curTime++;
      g.push_back({-1, curTime, curTime + 1});
      continue;
    }
    rem[selected]--;
    g.push_back({p[selected].pid, curTime, curTime + 1});
    curTime++;

    if(rem[selected] == 0){
      p[selected].ct = curTime;
      p[selected].tat = p[selected].ct - p[selected].at;
      p[selected].wt = p[selected].tat - p[selected].bt;
      completed++;
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
- This program implements Preemptive Shortest Job First (SRTF - Shortest Remaining Time First) Scheduling.
- At every unit of time, the process with the shortest remaining burst time among arrived processes is selected.
- The running process can be interrupted if another process with a shorter remaining time arrives.
- Remaining burst time is stored in the rem array.
- The program calculates Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Finally, it displays average TAT, average WT, and the Gantt Chart.
*/