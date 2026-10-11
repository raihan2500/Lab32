#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int n, m;
vector<vector<int>> graph(N);

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
  vector<int> state(n + 1, 0ll);
  for(int i = 1; i <= n; i++){
    if(!state[i]){
      if(cycle(i, state))return true;
    }
  }
  return false;
}

int32_t main(){
  cin >> n >> m;
  map<int,int> mp;
  vector<pair<int, int>> edg;
  for(int i = 0; i < m; i++){
    int t, x, y;
    cin >> t >> x >> y;
    if(t == 1){
      edg.push_back({x, y});
    }else{
      mp[x] = y;
    }
  }

  for(auto [x, y] : edg){
    auto it = mp.find(y);
    if(it != mp.end()){
      graph[x].push_back(it->second);
    }
  }

  if(isCyclic()){
    cout << "Deadlock exists\n";
  }else{
    cout << "No deadlock found\n";
  }

}