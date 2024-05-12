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
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;

    /* solve */
    int ans = INFTY;

    for (int i = 1; i <= N; i++) {
      // 割り切れないならそのループにならない
      if (N % i != 0) continue;
      set<string> st;
      for (int j = 0; j < N; j += i) {
        st.insert(S.substr(j, i));
      }
      // debug(st);
      bool ok = false;
      for (auto s1 : st) {
        int cnt = 0;
        for (int j = 0; j < N; j += i) {
          string t = S.substr(j, i);
          // debug(t);
          assert(s1.size() == t.size() && s1.size() == i);
          rep(k, i) {
            if (s1[k] != t[k]) cnt++;
          }
        }
        // debug(s, cnt);
        if (cnt <= K) ok = true;
      }
      if (ok) {
        ans = i;
        break;
      }
    }

    if (ans > N) assert(false);

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