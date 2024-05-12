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
    string s;
    cin >> N >> s;

    /* solve */
    vvi vec(26);
    rep(i, N) vec[s[i] - 'a'].push_back(i);

    int last = N;
    for (int i = 0; i < last; i++) {
      char mn = 0;
      while (mn < 26) {
        if (s[i] <= 'a' + mn) break;
        if (vec[mn].empty() || vec[mn].back() <= i) {
          mn++;
        } else {
          break;
        }
      }
      if (mn == 26) continue;
      if (s[i] <= 'a' + mn) continue;

      int idx = vec[mn].back();
      if (idx >= last) break;
      swap(s[i], s[idx]);
      debug(i, idx);
      debug(s);
      last = idx;
      vec[mn].pop_back();

      rep(j, 26) {
        while (vec[j].size()) {
          if (vec[j].back() > last) {
            vec[j].pop_back();
          } else {
            break;
          }
        }
      }
    }

    /* output */
    cout << s << endl;
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