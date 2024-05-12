#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

// mapでマージテクを使えるUnionFind（ABC183）
// UnionFind
// coding: https://youtu.be/TdR816rqc3s?t=726
// comment: https://youtu.be/TdR816rqc3s?t=6822
struct UnionFind {
  // 親を指すが、自分がルートの時はサイズの-1倍が入る
  vector<int> par;
  vector<map<int, int>> mp;
  UnionFind(int n = 0) : par(n, -1), mp(n) {}
  int find(int x) {
    if (par[x] < 0) return x;
    return par[x] = find(par[x]);
  }
  bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);  // 負なので、サイズが大きい方がx
    // 大きい方に小さい方をマージ（マージテク）
    for (auto p : mp[y]) {
      mp[x][p.first] += p.second;
    }
    mp[y] = map<int, int>();  // メモリ解法
    par[x] += par[y];
    par[y] = x;
    return true;
  }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return -par[find(x)]; }
};

struct Solver {
  void solve() {
    /* input */
    int n, q;
    cin >> n >> q;
    /* solve */
    UnionFind t(n);
    rep(i, n) {
      int c;
      cin >> c;
      t.mp[i][c] = 1;
    }
    rep(qi, q) {
      int type;
      cin >> type;
      if (type == 1) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        t.unite(a, b);
      } else {
        int x, y;
        cin >> x >> y;
        --x;
        x = t.find(x);
        int ans = t.mp[x][y];
        printf("%d\n", ans);
      }
    }

    /* output */
  }
};

int main() {
  int ts = 3;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}