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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // map<int, vi> mp;

    int Q;
    cin >> Q;
    vs Qt(Q);
    vi Qn(Q);
    rep(qi, Q) {
      cin >> Qt[qi];
      if (Qt[qi][0] != 'D') cin >> Qn[qi];
    }

    // rep(qi, Q) {
    //   if (Qt[qi][0] == 'L') mp[Qn[qi]].push_back(qi);
    // }

    // debug(mp);

    map<int, stack<int>> memo;

    /* input */
    stack<int> st;
    rep(qi, Q) {
      if (Qt[qi][0] == 'A') {
        st.push(Qn[qi]);
      } else if (Qt[qi][0] == 'D') {
        if (!st.empty()) st.pop();
      } else if (Qt[qi][0] == 'S') {
        memo[Qn[qi]] = st;
      } else if (Qt[qi][0] == 'L') {
        st = memo[Qn[qi]];
      }

      cout << (st.empty() ? -1 : st.top()) << "\n";

      /* solve */

      /* output */
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