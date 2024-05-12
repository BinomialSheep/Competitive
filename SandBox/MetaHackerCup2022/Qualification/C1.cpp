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
  vs ans;
  vs parts;
  int N;

  void dfs(int now, int depth, string s) {
    if (now == depth) {
      ans.push_back(s);
      return;
    }

    rep(i, (int)parts.size()) {
      if (ans.size() < N - 1) dfs(now + 1, depth, s + parts[i]);
    }
  }

  void solve() {
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */

      cin >> N;
      string C;
      cin >> C;

      ans.clear();
      parts.clear();
      /* solve */
      if (C.size() == 1) {
        rep(bit, (1 << 10)) {
          string s = (C == ".") ? "-" : ".";
          rep(i, 10) {
            if (bit & (1 << i))
              s.push_back('-');
            else
              s.push_back('.');
          }
          ans.push_back(s);
          if (ans.size() + 1 == N) break;
        }
      } else if (C.size() >= 10) {
        int bit = -1;
        string init;
        rep(i, (int)C.size()) init.push_back('.');
        while (true) {
          bit++;
          string s = init;
          rep(i, 10) {
            if (bit & (1 << i)) s[i] = '-';
          }
          if (s == C) continue;
          ans.push_back(s);
          if (ans.size() + 1 == N) break;
        }
      } else {
        int sz = 200 / (int)C.size();

        rep(bit, (1 << C.size())) {
          string s;
          rep(i, (int)C.size()) {
            if (bit & (1 << i))
              s.push_back('-');
            else
              s.push_back('.');
          }
          if (s == C) continue;
          parts.push_back(s);
        }
        dfs(0, sz, "");
      }

      /* output */
      printf("Case #%d:\n", ti + 1);
      rep(i, (int)ans.size()) cout << ans[i] << "\n";
    }
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