#include<bits/stdc++.h>
using namespace std;
#define nl cout << endl 

struct Process{
	int pid, at, bt, tat, ct, wt; 
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
				if(s == -1 or (p[i].bt < p[s].bt) or (p[i].bt == p[s].bt and p[i].at < p[s].at)){
					s = i;
				}
			}
		}
		if(s == -1){
			g.push_back({-1, curTime, curTime + 1});
			curTime++;
		}else{
			auto &x = p[s];
			g.push_back({x.pid, curTime, curTime + x.bt});

			curTime += x.bt;
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
Then enter Arrival Time (AT) and Burst Time (BT) for each process.

Example Input:
5
0 5
1 3
2 8
3 6
4 4

Algorithm:
- This program implements Non-Preemptive Shortest Job First (SJF) Scheduling.
- Among all arrived processes, the process with the shortest Burst Time (BT) is selected.
- If two processes have the same Burst Time, the one with the earlier Arrival Time is selected.
- The selected process runs until completion.
- If no process has arrived, the CPU remains idle.
- The program calculates Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Finally, it displays average TAT, average WT, and the Gantt Chart.
*/