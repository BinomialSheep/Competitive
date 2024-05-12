#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int n, m, k, s, t, x;
  cin >> n >> m >> k >> s >> t >> x;
  s--;
  t--;
  x--;
  vector<vector<int>> graph(n);
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  /* solve */
  // まず、同じ辺を使わずにsからtに到達する経路の数を求める
  // ただし、辺uvと辺vuは異なるものとみなす

  // 使った辺
  map<pair<int, int>, bool> used;
  // 経路
  vector<vector<int>> pathVec;

  // 深さ優先探索する
  stack<int> myStack;
  myStack.push(s);

  int u;
  while (!myStack.empty()) {
    u = q.top();

    if (u == t) {
      // tに到達
      u.pop();
    }

    for (int i = 0; i < graph[u].size(); i++) {
      // 使用済みの辺は使わない
      if (used[make_pair(u, graph[u][i])]) continue;
      // 使用済みの辺でないなら使用する
      used[make_pair(u, graph[u][i])] = true;
      myStack.push(graph[u][i]));
    }
  }

  /* output */

  return 0;
}