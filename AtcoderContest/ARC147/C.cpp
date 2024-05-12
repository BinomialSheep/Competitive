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
    using vpli = vector<pair<ll, int>>;
    vpli L, R;
    rep(i, N) {
      ll l, r;
      cin >> l >> r;
      L.emplace_back(l, i);
      R.emplace_back(r, i);
    }
    sort(L.rbegin(), L.rend());
    sort(all(R));

    vb used(N);
    ll ans = 0;
    ll lx = 0, ly = 0, rx = 0, ry = 0;
    ll r = -1, l = -1;
    int li = 0;
    int ri = 0;
    rep(cnt, N) {
      // // 範囲が被ったら全部同じ位置に置く
      if (L[li].first <= R[ri].first) {
        // どこに置くのが最善か求める
        ll cost = INFTY;
        for (int i = R[ri].first; i <= L[li].first; i++) {
          ll now = 0;
          if (r != -1) now += abs(i - r) * rx + ry;
          if (l != -1) now += abs(i - l) * lx + ly;
          chmin(cost, now);
        }
        ans += cost * (N - cnt);
        break;
      }

      // 右端が小さいやつをできるだけ右側に置くコスト
      ll cr = 0;
      if (r != -1) cr += abs(R[ri].first - r) * rx + ry;
      if (l != -1) cr += abs(R[ri].first - l) * lx + ly;
      // 左端が大きいやつをできるだけ左側に置くコスト
      ll cl = 0;
      if (l != -1) cl = abs(L[li].first - l) * lx + ly;
      if (r != -1) cl += abs(L[li].first - r) * rx + ry;

      if (cr < cl) {
        debug(R[ri]);
        // 右端が小さいやつを置く
        ans += cr;
        rx++;
        ry += (r == -1) ? 0 : (abs(R[ri].first - r) * rx + ry);
        r = R[ri].first;
        used[R[ri].second] = true;
        if (cnt == N - 1) break;
        while (used[R[ri].second]) ri++;
      } else {
        debug(L[li]);
        // 左端が大きいやつを置く
        ans += cl;
        lx++;
        ly += (l == -1) ? 0 : (abs(L[li].first - l) * lx + ly);
        l = L[li].first;
        used[L[li].second] = true;
        if (cnt == N - 1) break;
        while (used[L[li].second]) li++;
      }
      debug(used);
      debug(cnt, ans);
      debug(l, lx, ly, r, rx, ry);
    }

    /* solve */

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