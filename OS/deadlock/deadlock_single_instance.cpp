#include<bits/stdc++.h>
using namespace std;

#define int long long

#ifdef DEBUG
#include<algo/debug.h>
#include<algo/resources.h>
#else
#   define clog if (0) cerr
#   define DB(...)
#   define db(...) "" 
#endif

const int M = 1e9 + 7;
const int N = 2e5 + 10;


int n, m, edg;
vector<vector<int>> graph(N);

void show(int u, int v){
  if(u > n){
    cout << "R" << u - n <<" -> P" << v << endl;
  }else{
    cout << "P" << u <<" -> R" << v - n << endl;
  }

}

bool cycle(int u, vector<int> &state){
  state[u] = 1;
  for(auto &v : graph[u]){
    if(state[v] == 1){
      return true;
    }
    if(state[v] == 0){
      if(cycle(v, state)){
        return true;
      }
    }
  }
  state[u] = 2;
  return false;
}
bool isCyclic(){
  vector<int> state(n + m + 1, 0ll);
  for(int i = 1; i <= n; i++){
    if(!state[i]){
      if(cycle(i, state))return true;
    }
  }
  return false;
}




signed main(){
  cin >> n >> m >> edg;
  for(int i = 0; i < edg; i++){
    int t, u, v;
    cin >> t >> u >> v;
    if(t == 1){
      v += n;
    }else{
      u += n;
    }
    graph[u].push_back(v);
  }

  if(isCyclic()){
    cout << "Deadlock exists\n";
  }else{
    cout << "No Deadlock found\n";
  }
}

/*
Algorithm: Deadlock Detection using DFS (State/Color Method)

This program detects deadlock in a single-instance Resource Allocation Graph (RAG).
Since each resource has only one instance, a cycle in the graph means a deadlock exists.

Node Representation:
- Process Pi  -> node i
- Resource Ri -> node (n + i)

Edge Representation:
- t = 1 : Process requests Resource      => Pu -> Rv
- t = 2 : Resource allocated to Process  => Ru -> Pv

DFS State:
- 0 = Unvisited
- 1 = Currently in DFS path
- 2 = Completely processed

During DFS, if we reach a node with state = 1, a cycle is found.
Therefore, deadlock exists.

Input Format:
n m edg
Then edg lines:
t u v

Where:
n   = number of processes
m   = number of resources
edg = number of edges

Example Input:
2 2 4
1 1 1
2 1 2
1 2 2
2 2 1

Graph:
P1 -> R1
R1 -> P2
P2 -> R2
R2 -> P1

This forms a cycle:
P1 -> R1 -> P2 -> R2 -> P1

Example Output:
Deadlock exists

Another Example Input:
2 2 3
1 1 1
2 1 2
1 2 2

Example Output:
No Deadlock found

Output:
"Deadlock exists"   -> if a cycle is found
"No Deadlock found" -> if no cycle exists

Time Complexity: O(V + E)
where V = n + m and E = edg.
*/