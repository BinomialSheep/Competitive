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
    int H, W;
    cin >> H >> W;
    vvi A(H, vi(W));
    rep(i, H) rep(j, W) cin >> A[i][j];

    /* solve */
    vpii Hp(H, make_pair(INFTY, -1));
    // vpii Wp(W, make_pair(INFTY, -1));

    rep(i, H) {
      rep(j, W) {
        chmax(Hp[i].second, A[i][j]);
        // chmax(Wp[j].second, A[i][j]);
        if (A[i][j] != 0) {
          chmin(Hp[i].first, A[i][j]);
          // chmin(Wp[j].first, A[i][j]);
        }
      }
    }
    // debug(Hp);
    // debug(Wp);
    sort(all(Hp));
    // sort(all(Wp));
    debug(Hp);
    // debug(Wp);
    rep(i, H - 1) {
      if (Hp[i].second > Hp[i + 1].first) {
        cout << "No" << endl;
        return;
      }
    }
    // rep(i, W - 1) {
    //   if (Wp[i].second > Wp[i + 1].first) {
    //     cout << "No" << endl;
    //     return;
    //   }
    // }

    unordered_set<ll> st;

    rep(i, H) {
      vpii B;
      rep(j, W) {
        if (A[i][j] != 0) B.emplace_back(A[i][j], j);
      }
      sort(all(B));
      rep(k, B.size()) rep(k2, k) {
        ll v1 = k * 20000000 + k2;
        ll v2 = k2 * 20000000 + k;
        st.insert(v1);
        if (st.count(v2)) {
          cout << "No" << endl;
          return;
        }
      }
    }

    cout << "Yes" << endl;

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