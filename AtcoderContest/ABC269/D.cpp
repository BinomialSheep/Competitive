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
#include <atcoder/all>
using namespace atcoder;
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

struct Solver {
  void solve() {
    /* input */
    int N;
    cin >> N;
    map<pair<int, int>, int> mp;
    rep(i, N) {
      int x, y;
      cin >> x >> y;
      mp[make_pair(x, y)] = i;
    }

    /* solve */
    dsu uf(N);

    vi dx = {-1, -1, 0, 0, 1, 1};
    vi dy = {-1, 0, -1, 1, 0, 1};
    for (auto p : mp) {
      int x = p.first.first;
      int y = p.first.second;
      rep(i, 6) {
        int x2 = x + dx[i];
        int y2 = y + dy[i];
        auto p2 = make_pair(x2, y2);
        if (mp.count(p2)) {
          uf.merge(mp[p.first], mp[p2]);
        }
      }
    }

    //
    set<int> st;
    rep(i, N) { st.insert(uf.leader(i)); }

    /* output */
    cout << st.size() << endl;
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