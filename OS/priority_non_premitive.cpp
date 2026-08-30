#include<bits/stdc++.h>
using namespace std;

#define nl cout << endl;

struct Process{
  int pid, at, bt, priority;
  int ct, tat, wt;
  bool finished = false;
  void show(){
    cout << pid <<"\t" << at <<"\t" << bt <<"\t" << priority <<"\t\t\t" << ct <<"\t" << tat <<"\t" << wt << endl;
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
  vector<Gantt> g;
  for(int i = 0; i < n; i++){
    p[i].pid = i + 1;
    cin >> p[i].at >> p[i].bt >> p[i].priority;
  }

  int curTime = 0, completed = 0;
  while(completed < n){
    int selected = -1;
    for(int i = 0; i < n; i++){
      if(!p[i].finished and p[i].at <= curTime){
        if(selected == -1 or p[i].priority < p[selected].priority){
          selected = i;
        }
      }
    }
    if(selected == -1){
      curTime++;
      continue;
    }
    g.push_back({p[selected].pid, curTime, curTime + p[selected].bt});
    curTime += p[selected].bt;

    p[selected].ct = curTime;
    p[selected].tat = p[selected].ct - p[selected].at;
    p[selected].wt = p[selected].tat - p[selected].bt;
    p[selected].finished = true;
    completed++;
  }
  
  cout << "\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";

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