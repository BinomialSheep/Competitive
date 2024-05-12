#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INTFY (1 << 29)

class DisjointSet {
 public:
  vector<int> rank, p;

  DisjointSet() {}
  DisjointSet(int size) {
    rank.resize(size, 0);
    p.resize(size, 0);
    rep(i, size) makeSet(i);
  }

  void makeSet(int x) {
    p[x] = x;
    rank[x] = 0;
  }
  bool same(int x, int y) { return findSet(x) == findSet(y); }
  void unite(int x, int y) { link(findSet(x), findSet(y)); }
  void link(int x, int y) {
    if (rank[x] > rank[y]) {
      p[y] = x;
    } else {
      p[x] = y;
      if (rank[x] == rank[y]) {
        rank[y]++;
      }
    }
  }

  int findSet(int x) {
    if (x != p[x]) {
      p[x] = findSet(p[x]);
    }
    return p[x];
  }
};

class Edge {
 public:
  int source, target, cost;
  Edge(int source = 0, int target = 0, int cost = 0)
      : source(source), target(target), cost(cost) {}
  bool operator<(const Edge &e) const { return cost < e.cost; }
};

int kruskal(int N, vector<Edge> edges) {
  int totalCost = 0;
  sort(edges.begin(), edges.end());

  DisjointSet dset = DisjointSet(N + 1);

  rep(i, N) dset.makeSet(i);

  int sorce, target;
  rep(i, edges.size()) {
    Edge e = edges[i];
    if (!dset.same(e.source, e.target)) {
      totalCost += e.cost;
      dset.unite(e.source, e.target);
    }
  }
  return totalCost;
}

int main() {
  int N, M, cost;
  int source, target;

  cin >> N >> M;
  vector<Edge> edges;
  rep(i, M) {
    cin >> source >> target >> cost;
    edges.push_back(Edge(source, target, cost));
  }

  cout << kruskal(N, edges) << endl;

  return 0;
}