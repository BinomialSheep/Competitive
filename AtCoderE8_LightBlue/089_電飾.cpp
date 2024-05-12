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
    vi light(N);
    rep(i, N) cin >> light[i];

    /* solve */
    deque<pii> q;
    // 圧縮
    rep(i, N) {
      if (q.empty()) {
        q.emplace_back(light[i], 1);
      } else {
        if (q.back().first == light[i]) {
          q.back().second++;
        } else {
          q.emplace_back(light[i], 1);
        }
      }
    }

    deque<pii> q2;
    for (auto p : q) {
      if (p.second != 1) {
        q2.push_back(p);
      } else {
        if (!q2.empty() && q2.back().first == -1) {
          q2.back().second++;
        } else {
          q2.emplace_back(-1, 1);
        }
      }
    }
    debug(q2);
    //
    ll ans = 2;
    // 3個繋がってるところの真ん中を変えると増えうる
    rep(i, (int)q2.size()) {
      if (q2[i].first != -1 && q2[i].second == 3) {
        ll cnt = 3;
        if (i != 0) {
          if (q2[i - 1].first == -1) {
            cnt += q2[i - 1].second;
            if (i - 1 != 0) cnt++;
          } else {
            cnt++;
          }
        }
        if (i != (int)q2.size() - 1) {
          if (q2[i + 1].first == -1) {
            cnt += q2[i + 1].second;
            if (i + 1 != (int)q2.size() - 1) cnt++;
          } else {
            cnt++;
          }
        }
        chmax(ans, cnt);
      }

      // (2以上)11111(2以上）は増え得る
      if (q2[i].first == -1) {
        ll cnt = q2[i].second;
        if (i != 0) {
          cnt += 2;
          if (i - 2 >= 0 && q2[i - 1].second == 2 && q2[i - 2].first == -1) {
            cnt += q2[i - 2].second;
          }
        }
        if (i != (int)q2.size() - 1) {
          cnt += 2;
          if (i + 2 <= (int)q2.size() - 1 && q2[i + 1].second == 2 &&
              q2[i + 2].first == -1) {
            cnt += q2[i + 2].second;
          }
        }
        chmax(ans, cnt);
      }
      // 000010101みたいなパターンのケア
      if (q2[i].first == -1) {
        ll cnt = q2[i].second;
        if (i != 0 && q2[i - 1].second >= 3) {
          chmax(ans, cnt + 3);
        }
        if (i != (int)q2.size() - 1 && q2[i + 1].second >= 3) {
          chmax(ans, cnt + 3);
        }
      }
    }

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