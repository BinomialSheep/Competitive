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
  int source, target;
  double cost;
  int flag;
  Edge(int s, int t, double c, int f)
      : source(s), target(t), cost(c), flag(f) {}
  bool operator<(Edge &e) { return cost < e.cost; }
};

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

struct Solver {
  void solve() {
    /* input */
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<Edge> edges;

    rep(i, M) {
      int a, b, c;
      cin >> a >> b >> c;
      --a;
      --b;
      if (a == b) continue;
      edges.push_back(Edge(a, b, c, -1));
    }

    rep(i, Q) {
      int a, b, c;
      cin >> a >> b >> c;
      --a;
      --b;
      if (a == b) continue;
      edges.push_back(Edge(a, b, c, i));
    }

    /* solve */
    sort(edges.begin(), edges.end());

    DisjointSet dset = DisjointSet(N);
    rep(i, N) dset.makeSet(i);

    vi ans(Q);

    // その頂点が何個目の辺で入ったか
    for (Edge e : edges) {
      if (!dset.same(e.source, e.target)) {
        if (e.flag == -1) {
          dset.unite(e.source, e.target);
        } else {
          ans[e.flag] = 1;
        }
      }
    }

    /* output */
    rep(i, Q) { cout << (ans[i] == 1 ? "Yes" : "No") << endl; }
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