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
    int N, K;
    cin >> N >> K;
    vi A(N);
    rep(i, N) cin >> A[i];
    /* solve */
    sort(A.rbegin(), A.rend());
    using pll = pair<ll, ll>;
    deque<pll> q;
    rep(i, N) {
      if (q.empty()) {
        q.emplace_back(A[i], 1);
        continue;
      }
      if (q.back().first == A[i]) {
        q.back().second++;
      } else {
        q.emplace_back(A[i], 1);
      }
    }
    // debug(q);

    ll ans = 0;
    ll cnt = 0;
    while (cnt <= K) {
      debug(ans, q);
      if (q.front().first == 0) break;

      if (q.size() == 1) {
        if (q[0].second * q[0].first < K - cnt) {
          ans += (1 + q[0].first) * q[0].first / 2 * q[0].second;
        } else {
          ll d = (K - cnt) / q[0].second;
          ans += (q[0].first + q[0].first - d + 1) * d / 2 * q[0].second;
          ans += (q[0].first - d) * ((K - cnt) % q[0].second);
        }
        break;
      }

      ll n = q[0].first - q[1].first;
      ll an = q[0].first;
      ll a1 = q[1].first + 1;
      if (cnt + n * q[0].second < K) {
        ans += (a1 + an) * n / 2 * q[0].second;
        cnt += n * q[0].second;
        q[1].second += q[0].second;
        q.pop_front();
      } else {
        ll n2 = (K - cnt) / q[0].second;
        // debug(n, an, a1, n2);
        ans += (an + an - n2 + 1) * n2 / 2 * q[0].second;
        // debug(ans);
        ans += (q[0].first - n2) * ((K - cnt) % q[0].second);
        // debug(ans);
        break;
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