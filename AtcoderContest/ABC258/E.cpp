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
  void solve() {
    /* input */
    ll N, Q, X;
    cin >> N >> Q >> X;
    vl W(N);
    rep(i, N) cin >> W[i];
    vl K(Q);
    rep(i, Q) cin >> K[i];

    /* solve */

    // iから始まったら何個で蓋を閉じるか
    vl M(N, -1);
    int start = 0;
    int loopStart = -1;
    vl MM;
    vl Midx;
    while (true) {
      if (M[start] != -1) {
        loopStart = start;
        break;
      }
      ll we = 0;
      int cnt = 0;
      while (true) {
        ll idx = start + cnt;
        if (idx >= N) idx -= N;
        we += W[idx];
        cnt++;
        if (we >= X) break;
      }
      M[start] = cnt;
      Midx.push_back(start);
      MM.push_back(cnt);
      start += cnt;
      if (start >= N) start -= (int)N;
    }
    debug(Midx, M);

    ll loopTime;
    ll idx = 0;
    ll time = 0;
    for (auto m : MM) {
      if (idx == loopStart) {
        loopTime = time;
      }
      idx += (int)m;
      if (idx >= N) idx -= (int)N;
      time++;
    }

    ll loopE = (int)MM.size() - loopTime;

    debug(MM, loopTime, loopE);

    rep(i, Q) {
      if (K[i] - 1 <= loopTime) {
        cout << MM[K[i] - 1] << endl;
      } else {
        ll kk = K[i] - 1 - loopTime;
        kk %= loopE;
        if (kk + loopTime < 0) {
          while (true) {
          }
        }
        cout << MM[kk + loopTime] << endl;
      }
    }

    /* output */
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