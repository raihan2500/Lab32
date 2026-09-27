#include<bits/stdc++.h>
using namespace std;
#define nl cout << endl 

struct Process{
	int pid, at, bt, tat, ct, wt, rem, priority; 
	bool finished = false;
	void show(){
    cout << pid <<"\t" << at <<"\t" << bt <<"\t" << priority <<"\t\t\t" << ct <<"\t" << tat <<"\t" << wt << endl;
	}
};

struct Gantt{
	int pid, start, end;

};

int n; 

void Print(vector<Process> &p, vector<Gantt> &g){
  cout << "\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
	double totTat = 0, totWt = 0;
	for(auto i : p){
		totWt += i.wt;
		totTat += i.tat;
		i.show();
	}	
	totTat /= n; totWt /= n;

	nl;
	cout << "Total turnaround time: " << totTat << endl;
	cout << "Total waiting time: " << totWt << endl;

	//Gantt Chart
	cout << "\n\nGantt Chart\n\n";
	for(auto i : g){
    if(i.pid == -1){
      cout <<"|Idle";
    }else{
      cout <<"| P" << i.pid <<" ";
    }
  }
	cout << "|\n";
	cout << g[0].start;
	for(auto i : g){
		cout << setw(5) << i.end;
	}
	nl;

}

int32_t main(){
	cin >> n;
	vector<Process> p(n);
	for(int i = 0; i < n; i++){
		cin >> p[i].at >> p[i].bt >> p[i].priority; 
		p[i].pid = i + 1;
		p[i].rem = p[i].bt;
	}


	vector<Gantt> g;
	int curTime = 0, completed = 0;

	while(completed < n){
		int s = -1;
		for(int i = 0; i < n; i++){
			if(!p[i].finished and p[i].at <= curTime){
				if(s == -1 or p[i].priority < p[s].priority){
					s = i;
				}
			}
		}
		if(s == -1){
			if(!g.empty() and g.back().pid == -1){
				g.back().end++;
			}else{
				g.push_back({-1, curTime, curTime + 1});
			}
			curTime++;
			continue;
		}
		auto &x = p[s];
		if(!g.empty() and g.back().pid == x.pid){
			g.back().end++;
		}else{
			g.push_back({x.pid, curTime, curTime + 1});
		}
		x.rem--;
		curTime++;
		if(x.rem == 0){
			x.ct = curTime;
			x.tat = x.ct - x.at;
			x.wt = x.tat - x.bt;
			x.finished = true;
			completed++;
		}
	}

	Print(p, g);
}

/*
Input Format:
First enter the number of processes (n).
Then enter Arrival Time (AT), Burst Time (BT), and Priority value for each process.

Example Input:
5
0 5 2
1 3 1
2 8 4
3 6 3
4 4 2

Algorithm:
- This program implements Preemptive Priority Scheduling.
- At every unit of time, the scheduler selects the arrived process with the highest priority.
- A smaller priority number indicates a higher priority.
- The running process can be interrupted if another higher-priority process arrives.
- Remaining Burst Time (rem_bt) is used to track unfinished execution.
- The program calculates Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Finally, it displays average TAT, average WT, and the Gantt Chart.
*/