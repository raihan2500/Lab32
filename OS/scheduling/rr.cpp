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
	int tq = 1; 
	cin >> tq;
	sort(p.begin(), p.end(), [&](auto a, auto b){
		if(a.at == b.at)return a.pid < b.pid;
		return a.at < b.at;
	});

	vector<Gantt> g;
	int curTime = 0, completed = 0, i = 0;

	queue<int> q;
	while(completed < n){
		if(q.empty() and i < n and curTime < p[i].at){
			g.push_back({-1, curTime, p[i].at});
			curTime = p[i].at;
		}

		while(i < n and p[i].at <= curTime){
			q.push(i); i++;
		}
		
		int idx = q.front(); q.pop();

		auto &x = p[idx];
		int exc = min(tq, x.rem);
		g.push_back({x.pid, curTime, curTime + exc});
		curTime += exc;
		x.rem -= exc;

		while(i < n and p[i].at <= curTime){
			q.push(i); i++;
		}

		if(x.rem == 0){
			x.ct = curTime;
			x.tat = x.ct - x.at;
			x.wt = x.tat - x.bt;
			completed++;
		}else{
			q.push(idx);
		}
	}

	Print(p, g);
}

/*
Input Format:
First enter the number of processes (n).
Then enter Arrival Time (AT) and Burst Time (BT) for each process.
Finally, enter the Time Quantum (TQ) value.

Example Input:
5
0 5
1 3
2 8
3 6
4 4
2

Algorithm:
- This program implements Round Robin CPU Scheduling.
- Each process gets a fixed CPU time called Time Quantum (TQ).
- If a process is not completed within its quantum, it is moved to the end of the ready queue.
- Processes are executed in circular order until all processes are completed.
- The program calculates Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT).
- Finally, it displays average TAT, average WT, and the Gantt Chart.
*/