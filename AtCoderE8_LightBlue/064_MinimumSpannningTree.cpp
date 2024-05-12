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

class DisjointSet {
 public:
  // rankは木の高さ（0-origen), pはrootの要素（rootのrootは自分自身）
  vector<int> rank, p;
  DisjointSet() {}
  DisjointSet(int size) {
    // 長さsizeで初期値0の動的配列を作る
    rank.resize(size, 0);
    p.resize(size, 0);
    // 0,..,n-1をそれぞれ唯一の要素とするn個の互いに素な集合を作る
    rep(i, size) makeSet(i);
  }
  void makeSet(int x) {
    p[x] = x;
    rank[x] = 0;
  }
  // 新しく要素数1の木を追加する
  int addSet() {
    int ret = (int)p.size();
    p.push_back(ret);
    rank.push_back(0);
    return ret;
  }
  // 同じ木に所属しているか
  bool same(int x, int y) { return findSet(x) == findSet(y); }
  // xが所属する木とyが所属する木の合成
  void unite(int x, int y) { link(findSet(x), findSet(y)); }
  // 高い方に合成する（rankの更新を減らすため）
  void link(int x, int y) {
    if (x == y) return;
    if (rank[x] > rank[y]) {
      p[y] = x;
    } else {
      p[x] = y;
      if (rank[x] == rank[y]) {
        // 同じ高さ同士の木を合成した場合はインクリメント
        rank[y]++;
      }
    }
  }
  // 再帰的に親を辿ってrootを見つける。この実装では経路圧縮はしない。
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
  Edge(int s = 0, int t = 0, int c = 0) : source(s), target(t), cost(c) {}
  bool operator<(Edge &e) { return cost < e.cost; }
};

// クラスカルで解く
struct Solver {
  // 最小全域木の重みを返す
  ll kruskal(int N, vector<Edge> edges) {
    // TODO：使用した辺のvectorを記録
    // TODO：最小全域木になったら枝刈り
    ll ret = 0;
    sort(edges.begin(), edges.end());

    DisjointSet dset = DisjointSet(N + 1);
    rep(i, N) dset.makeSet(i);

    for (Edge e : edges) {
      if (!dset.same(e.source, e.target)) {
        ret += e.cost;
        dset.unite(e.source, e.target);
      }
    }
    return ret;
  }

  void solve() {
    /* input */
    int V;
    int E;
    cin >> V >> E;

    vector<Edge> edges;
    rep(i, E) {
      int s, t, w;
      cin >> s >> t >> w;
      edges.push_back(Edge(s, t, w));
    }

    /* solve */
    ll ans = kruskal(V, edges);

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