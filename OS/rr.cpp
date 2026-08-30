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
  vector<Gantt> g;
  vector<Process> p(n);
  for(int i = 0; i < n; i++){
    p[i].pid = i + 1;
    cin >> p[i].at >> p[i].bt;

  }

  int tq = 0;
  cin >> tq;
  vector<int> rem(n);
  for(int i = 0; i < n; i++){
    rem[i] = p[i].bt;
  }
  
  sort(p.begin(), p.end(), [](Process a, Process b){
    if(a.at == b.at)return a.pid < b.pid;
    return a.at < b.at;
  });

  int curTime = 0;
  int completed = 0, i = 0;
  queue<int> q;

  while(completed < n){
    if(q.empty() and i < n and curTime < p[i].at){
      curTime = p[i].at;
    }
    while(i < n and p[i].at <= curTime){
      q.push(i);
      i++;
    }

    int idx = q.front(); q.pop();

    int excTime = min(tq, rem[idx]);
    rem[idx] -= excTime;

    g.push_back({p[idx].pid, curTime, curTime + excTime});
    curTime += excTime;

    while(i < n and p[i].at <= curTime){
      q.push(i); i++;
    }


    if(rem[idx]){
      q.push(idx);
    }else{
      completed++;
      p[idx].ct = curTime;
      p[idx].tat = p[idx].ct - p[idx].at;
      p[idx].wt = p[idx].tat - p[idx].bt;
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