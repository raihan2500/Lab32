#include<bits/stdc++.h>
using namespace std;
#define nl cout << endl 

struct Process{
	int pid, at, bt, tat, ct, wt, rem; 
	bool finished = false;
	void show(){
		cout << pid <<"\t" << at <<"\t" << bt <<"\t" << ct <<"\t" << tat <<"\t" << wt << endl;
	}
};

struct Gantt{
	int pid, start, end;

};

int n; 

void Print(vector<Process> &p, vector<Gantt> &g){
	cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
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
		cin >> p[i].at >> p[i].bt; 
		p[i].pid = i + 1;
		p[i].rem = p[i].bt;
	}

	sort(p.begin(), p.end(), [&](auto a, auto b){
		if(a.at == b.at)return a.pid < b.pid;
		return a.at < b.at;
	});

	vector<Gantt> g;
	int curTime = 0, completed = 0;


	while(completed < n){
		int s = -1;
		for(int i = 0; i < n; i++){
			if(!p[i].finished and p[i].at <= curTime){
				if(s == -1 or (p[i].rem < p[s].rem) or (p[i].rem == p[s].rem and p[i].at < p[s].at)){
					s = i;
				}
			}
		}
		if(s == -1){
			g.push_back({-1, curTime, curTime + 1});
			curTime++;
		}else{
			auto &x = p[s];
			if(!g.empty() and g.back().pid == x.pid){
				g.back().end++;
			}else{
				g.push_back({x.pid, curTime, curTime + 1});
			}
			curTime++;
			x.rem--;

			if(x.rem == 0){
				x.ct = curTime;
				x.tat = x.ct - x.at;
				x.wt = x.tat - x.bt;
				x.finished = true;
				completed++;
			}

		}
	}

	Print(p, g);
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