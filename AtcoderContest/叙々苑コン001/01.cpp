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

struct Solver {
  int N, M;
  vi a, b;
  // α
  int A = 5;

  vpii stupidInit() {
    vpii ret;
    rep(i, N) ret.emplace_back(1, i + 1);
    ret.emplace_back(1, 1);
    return ret;
  }

  // シンプルなスコア計算
  ll calcScore(vpii &tr) {
    ll ret = 0;
    int len = (int)tr.size();

    auto dist = [](int x1, int y1, int x2, int y2) {
      return (ll)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };

    rep(i, len - 1) {
      if (tr[i].first == 1 && tr[i + 1].first == 1) {
        int x1 = a[tr[i].second - 1];
        int y1 = b[tr[i].second - 1];
        int x2 = a[tr[i + 1].second - 1];
        int y2 = b[tr[i + 1].second - 1];
        ret += A * A * dist(x1, y1, x2, y2);
      } else if (tr[i].first == 2 && tr[i + 1].first == 2) {
        // TODO
      } else {
        // TODO
      }
    }
    return ret;
  }

  void solve() {
    /* input */
    cin >> N >> M;
    a.resize(N);
    b.resize(N);
    rep(i, N) cin >> a[i] >> b[i];

    /* solve */
    vpii cd(M);
    vpii tr = stupidInit();

    debug(tr);
    debug(calcScore(tr));

    /* output */
    int V = (int)tr.size();
    assert(tr[0].second == 1);
    assert(tr[V - 1].second == 1);

    rep(i, M) cout << cd[i].first << " " << cd[i].second << "\n";

    cout << V << endl;
    rep(i, V) cout << tr[i].first << " " << tr[i].second << "\n";
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