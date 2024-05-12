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
    vector<vpii> vec(N);
    rep(i, N) {
      int m;
      cin >> m;
      rep(j, m) {
        int p, e;
        cin >> p >> e;
        vec[i].emplace_back(p, e);
      }
    }

    /* solve */

    if (N == 1) {
      cout << 1 << endl;
      return;
    }

    map<int, int> mp;
    rep(i, N) {
      for (auto p : vec[i]) {
        if (mp.count(p.first)) {
          mp[p.first] = max(mp[p.first], p.second);
        } else {
          mp[p.first] = p.second;
        }
      }
    }
    debug(mp);

    // 最小公倍数に寄与し得る値の数
    map<int, int> mp2;
    rep(i, N) {
      for (auto p : vec[i]) {
        if (mp[p.first] == p.second) mp2[p.first]++;
      }
    }

    debug(mp2);

    ll cnt = 0;

    bool flag = false;

    rep(i, N) {
      bool flag2 = false;
      for (auto p : vec[i]) {
        if (mp[p.first] == p.second && mp2[p.first] == 1) {
          cnt++;
          flag2 = true;
          break;
        }
      }
      if (!flag2) flag = true;
    }

    if (flag) cnt++;

    /* output */
    cout << cnt << endl;
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