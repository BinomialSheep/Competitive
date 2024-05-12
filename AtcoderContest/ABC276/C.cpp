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
    vi P(N);
    rep(i, N) cin >> P[i];

    /* solve */
    int keta = -1;
    for (int i = N - 1; i >= 0; i--) {
      if (P[i] > P[i - 1]) continue;
      keta = i - 1;
      break;
    }
    int minKeta = 0;
    int minV = 0;
    for (int i = keta + 1; i < N; i++) {
      if (P[i] < P[keta] && chmax(minV, P[i])) minKeta = i;
    }
    swap(P[keta], P[minKeta]);

    vi temp;
    for (int i = keta + 1; i < N; i++) {
      temp.push_back(P[i]);
    }
    sort(temp.rbegin(), temp.rend());
    for (int i = 0; i + keta + 1 < N; i++) {
      P[i + keta + 1] = temp[i];
    }

    /* output */
    rep(i, N) cout << P[i] << " ";
    cout << endl;
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