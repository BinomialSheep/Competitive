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

template <class T>
struct Edge {
  int rev, from, to;  // rev:逆向きの辺の番号
  T cap, original_cap;
  Edge(int r, int f, int t, T c)
      : rev(r), from(f), to(t), cap(c), original_cap(c) {}
};
template <class T>
struct Graph {
  vector<vector<Edge<T>>> G;
  Graph(int n = 0) : G(n) {}
  vector<Edge<T>>& operator[](int i) { return G[i]; }
  const size_t size() const { return G.size(); }
  Edge<T>& redge(Edge<T> e) {  // 逆向きの辺を返す
    return G[e.to][e.rev];  // 自己ループはないと仮定（あれば G[e.to][e.rev + 1]
                            // とする必要がある）
  }
  void add_edge(int from, int to, T cap) {  // 有向辺を加える
    G[from].push_back(Edge<T>((int)G[to].size(), from, to, cap));
    G[to].push_back(Edge<T>((int)G[from].size() - 1, to, from, 0));
  }
};
/* FordFulkerson: Ford-Fulkersonのアルゴリズムで最大流を求める構造体
    max_flow(G,s,t) ：グラフGの最大流が求まる
    副作用：G は最大流の残余ネットワークになる
    計算量: O(|f*||E|) (f*:最大流)
*/
template <class T>
struct FordFulkerson {
  const T INF = 1e9;
  vector<int> used;
  FordFulkerson(){};
  T dfs(Graph<T>& G, int v, int t,
        T f) {  // 増加可能経路を見つけて増加分のフローを返す
    if (v == t) return f;
    used[v] = true;
    for (auto& e : G[v]) {
      if (!used[e.to] && e.cap > 0) {
        T d = dfs(G, e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G.redge(e).cap += d;
          return d;
        }
      }
    }
    return 0;
  }
  T max_flow(Graph<T>& G, int s, int t) {
    T flow = 0;
    while (true) {
      used.assign(G.size(), 0);
      T f = dfs(G, s, t, INF);  // f が増加分のフロー
      if (f == 0) {
        return flow;
      } else {
        flow += f;
      }
    }
    return 0;
  }
};

int main() {
  /* input */

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> AB(n);
  rep(i, n) {
    int A, B;
    cin >> A >> B;
    AB[i] = make_pair(A, B);
  }
  vector<pair<int, int>> CD(m);
  rep(i, m) {
    int C, D;
    cin >> C >> D;
    CD[i] = make_pair(C, D);
  }

  /* solve */
  //
  sort(AB.begin(), AB.end());
  reverse(AB.begin(), AB.end());
  sort(CD.begin(), CD.end());
  reverse(CD.begin(), CD.end());

  // 辺を貼っていく
  Graph<int> G(n + m + 2);
  rep(i, n) G.add_edge(0, i + 1, 1);
  rep(i, n) {
    int x = AB[i].first;
    int y = AB[i].second;
    auto pos = lower_bound(CD.begin(), CD.end(), AB[i]);

    for (int j = distance(CD.begin(), pos); j < m; j++) {
      if (x <= CD[j].first && y <= CD[j].second) {
        G.add_edge(i + 1, n + j + 1, 1);
      }
    }
  }
  rep(i, m) G.add_edge(n + i + 1, n + m + 1, 1);

  FordFulkerson<int> ff;
  int num = ff.max_flow(G, 0, n + m + 1);

  /* output */
  cout << (num == n ? "Yes" : "No") << endl;

  return 0;
}