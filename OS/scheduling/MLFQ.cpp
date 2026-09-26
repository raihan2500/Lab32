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
  //q1 = rr, q2 = rr, q3 = sjf
  int tq1 = 2, tq2 = 4;

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