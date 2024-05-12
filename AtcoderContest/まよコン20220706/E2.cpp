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
    int N;
    cin >> N;
    vi A(N);
    vi B(N);
    rep(i, N) cin >> A[i];
    rep(i, N) cin >> B[i];
    vpii AB(N);
    rep(i, N) AB[i] = make_pair(A[i], -B[i]);

    /* solve */

    sort(AB.rbegin(), AB.rend());
    multiset<int> ms;
    rep(i, N) ms.insert(-AB[i].second);

    // debug(AB);

    ll ans = 0;
    rep(i, N) {
      auto it = ms.lower_bound(-AB[i].second);
      if (it != ms.end()) {
        // それより高いやつを足す
        ans += ms.size() - distance(ms.begin(), it);
      }

      // 消す
      ms.erase(ms.find(-AB[i].second));
    }

    map<pii, int> sameMap;

    rep(i, N - 1) {
      if (AB[i] == AB[i + 1]) sameMap[AB[i]]++;
    }
    for (auto p : sameMap) {
      ll cnt = ++p.second;
      ans += cnt * (cnt - 1) / 2;
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