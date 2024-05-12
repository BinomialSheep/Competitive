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
    while (true) {
      /* input */
      int n, w, d;
      cin >> n >> w >> d;
      if (w == 0) break;
      vi p(n), s(n);
      rep(i, n) cin >> p[i] >> s[i];

      /* solve */
      vector<tuple<int, int, int>> vec;
      vec.emplace_back(1, w, d);
      rep(i, n) {
        int idx = p[i] - 1;
        int a, ww, dd;
        tie(a, ww, dd) = vec[idx];
        // debug(idx, ww, dd);

        tuple<int, int, int> trip1;
        tuple<int, int, int> trip2;
        s[i] %= (ww + dd + ww + dd);
        if (s[i] % (ww + dd) < ww) {
          int ww1 = s[i] % (ww + dd);
          int ww2;
          if (ww1 > ww) {
            ww2 = ww1 - dd;
            ww1 = ww - ww2;
          } else {
            ww2 = ww - ww1;
          }
          if (ww1 <= ww2) {
            trip1 = make_tuple(i + 1, ww1, dd);
            trip2 = make_tuple(i + 2, ww2, dd);
          } else {
            trip2 = make_tuple(i + 1, ww1, dd);
            trip1 = make_tuple(i + 2, ww2, dd);
          }
        } else {
          int dd1 = s[i] - ww;
          int dd2;
          if (dd1 > dd) {
            dd2 = dd1 - dd - ww;
            dd1 = dd - dd2;
          } else {
            dd2 = dd - dd1;
          }
          if (dd1 <= dd2) {
            trip1 = make_tuple(i + 1, ww, dd1);
            trip2 = make_tuple(i + 2, ww, dd2);
          } else {
            trip2 = make_tuple(i + 1, ww, dd1);
            trip1 = make_tuple(i + 2, ww, dd2);
          }
        }

        vector<tuple<int, int, int>> newVec;
        rep(j, i + 1) {
          if (j == idx) continue;
          newVec.push_back(vec[j]);
        }
        newVec.push_back(trip1);
        newVec.push_back(trip2);

        vec.resize(i + 2);
        vec = newVec;
        // debug(vec);
      }
      /* output */
      multiset<int> st;
      for (auto trip : vec) {
        int a, ww, dd;
        tie(a, ww, dd) = trip;
        st.insert(ww * dd);
      }
      int cnt = 0;
      for (auto area : st) {
        cout << area;
        cnt++;
        if (cnt != st.size()) cout << " ";
      }
      cout << endl;
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