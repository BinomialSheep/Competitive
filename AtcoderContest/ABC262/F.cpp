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
    vi P(N);
    rep(i, N) cin >> P[i];

    /* solve */
    if (K == 0) {
      rep(i, N) { cout << P[i] << " "; }
      cout << endl;
      return;
    }

    vi inv(N + 1);
    rep(i, N) inv[P[i]] = i;
    vi Q = P;
    sort(all(Q));

    int pre = INFTY;
    int preIdx = -1;
    rep(i, K) if (chmin(pre, P[i])) preIdx = i;
    int tal = INFTY;
    int talIdx = -1;
    rep(i, K) if (chmin(tal, P[N - 1 - i])) talIdx = i;

    //
    vi ans;
    int nexIdx = -1;
    int last = N - 1;
    if (pre < tal) {
      // 消し切る
      K -= preIdx;
      ans.push_back(pre);
      nexIdx = preIdx + 1;
    } else {
      // 消してから回す
      last = talIdx - 1;
      ans.push_back(tal);
      rep(i, (int)Q.size()) {
        if (Q[i] <= tal) continue;
        if (inv[Q[i]] > talIdx) {
          // 右の最小を取る
          // 消していく
          K -= inv[Q[i]] - talIdx - 1;
          ans.push_back(Q[i]);
          tal = Q[i];
          talIdx = Q[i];
        } else if (N - talIdx + inv[Q[i]] > K) {
          // これは取れないので諦める
          continue;
        } else {
          // 左を取る
          // 消して右に1回
          K -= N - talIdx;
          // 消していく
          K -= inv[Q[i]];
          ans.push_back(Q[i]);
          nexIdx += inv[Q[i]] + 1;
          break;
        }
      }
    }
    debug(ans);
    // 頑張って消していくだけ
    map<int, int> mp;
    for (int i = nexIdx; i <= last; i++) {
      mp[P[i]] = i;
    }

    while (true) {
      for (auto p : mp) {
        if (p.second < nexIdx) continue;
        if (p.second == nexIdx) {
          ans.push_back(p.first);
          nexIdx++;
          continue;
        }
        if (K >= p.second - nexIdx) {
          K -= p.second - nexIdx;
          ans.push_back(p.first);
          nexIdx = p.second + 1;
        }
        p.second - nexIdx;
      }
    }

    // 消せなかったのは足す
    for (int i = nexIdx; i <= last; i++) {
      ans.push_back(P[i]);
    }

    /* output */
    rep(i, (int)ans.size()) cout << ans[i] << " ";
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