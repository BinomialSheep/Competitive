#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

class Edge {
 public:
  int source, target, cost;
  Edge(int s, int t, int c) : source(s), target(t), cost(c) {}
  bool operator<(Edge &e) { return cost < e.cost; }
};

class DisjointSet {
 public:
  // rankは木の高さ、pはrootの要素
  vi rank, p;
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
  int addSet() {
    int ret = (int)p.size();
    p.push_back(ret);
    rank.push_back(0);
    return ret;
  }
  bool same(int x, int y) { return findSet(x) == findSet(y); }
  void unite(int x, int y) { link(findSet(x), findSet(y)); }
  void link(int x, int y) {
    if (x == y) return;
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

struct Solver {
  void solve() {
    /* input */
    int N, M, K;
    cin >> N >> M >> K;

    vector<Edge> edges;
    rep(i, M) {
      int a, b, c;
      cin >> a >> b >> c;
      --a;
      --b;
      edges.push_back(Edge(a, b, c));
    }

    /* solve */
    if (K == N) {
      cout << 0 << endl;
      return;
    }

    // クラスカルで、i回結合が行われたら連結要素はi個減る
    // 最初はN個に分かれていて、Kになったら終了するので、辺はN-K個
    ll ans = 0;
    sort(edges.begin(), edges.end());
    DisjointSet dset = DisjointSet(N);
    rep(i, N) dset.makeSet(i);

    int num = N;
    for (Edge e : edges) {
      if (!dset.same(e.source, e.target)) {
        ans += e.cost;
        dset.unite(e.source, e.target);
        num--;
        if (num == K) break;
      }
    }

    /* output */
    cout << ans << endl;
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}