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

// 普通の素因数分解 O(√N)
template <typename T>
vector<pair<T, T>> calcPrimeFactorSimple(T n) {
  vector<pair<T, T>> ret;
  for (T i = 2; i * i <= n; i++) {
    if (n % i != 0) continue;
    T tmp = 0;
    while (n % i == 0) {
      tmp++;
      n /= i;
    }
    ret.emplace_back(i, tmp);
  }
  if (n != 1) ret.emplace_back(n, 1);
  return ret;
}

struct Solver {
  void solve() {
    /* input */
    ll K;
    cin >> K;

    /* solve */
    vpll vecs = calcPrimeFactorSimple(K);

    // m!がkeyを素因数に何個含むか
    auto rec = [&](auto f, ll m, ll key) -> ll {
      if (m == 0) return 0;
      return m / key + f(f, m / key, key);
    };

    // 判定
    auto isAc = [&](ll m) {
      for (auto [fst, scd] : vecs) {
        ll num = rec(rec, m, fst);
        if (num < scd) return false;
      }
      return true;
    };

    ll ac = K, wa = 0;
    while (ac - wa > 1) {
      ll wj = (ac + wa) / 2;
      if (isAc(wj)) {
        ac = wj;
      } else {
        wa = wj;
      }
    }

    /* output */
    cout << ac << endl;
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