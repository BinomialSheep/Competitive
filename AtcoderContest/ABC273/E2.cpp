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
    // debug(Qt);
    // debug(Qn);

    // rep(qi, Q) {
    //   if (Qt[qi][0] == 'L') mp[Qn[qi]].push_back(qi);
    // }

    // debug(mp);

    vi ans(Q);
    map<int, stack<int>> memo;

    auto rec = [&](auto f, auto idx, auto &stk) -> int {
      int ret = Q - 1;
      if (idx == Q) return Q - 1;
      if (Qt[idx][0] == 'A') {
        stk.push(Qn[idx]);
        ans[idx] = (stk.empty() ? -1 : stk.top());
        // debug(idx, ans);
        ret = f(f, idx + 1, stk);
        if (!stk.empty()) stk.pop();
      } else if (Qt[idx][0] == 'D') {
        int tmp = -1;
        if (!stk.empty()) tmp = stk.top(), stk.pop();
        ans[idx] = (stk.empty() ? -1 : stk.top());
        ret = f(f, idx + 1, stk);
        if (tmp != -1) stk.push(Qn[idx]);
      } else if (Qt[idx][0] == 'S') {
        memo[Qn[idx]] = stk;
        ans[idx] = (stk.empty() ? -1 : stk.top());
        ret = f(f, idx + 1, stk);
      } else if (Qt[idx][0] == 'L') {
        return idx;
      }
      return ret;
    };

    int start = 0;
    while (start < Q) {
      stack<int> st;
      if (start != 0) {
        if (memo.count(Qn[start - 1])) st = memo[Qn[start - 1]];
        ans[start - 1] = (st.empty() ? -1 : st.top());
      }
      // debug(start, st);
      start = rec(rec, start, st);
      start++;
    }
    if (Qt[Q - 1][0] == 'L') {
      if (memo.count(Qn[Q - 1])) {
        ans[Q - 1] = (memo[Qn[Q - 1]].empty() ? -1 : memo[Qn[Q - 1]].top());
      } else {
        ans[Q - 1] = -1;
      }
    }

    rep(qi, Q) cout << ans[qi] << "\n";
    /* input */

    /* solve */

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