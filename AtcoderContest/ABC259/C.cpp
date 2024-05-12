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
    string S, T;
    cin >> S >> T;

    /* solve */
    deque<pair<char, int>> pq, tq;
    rep(i, (int)S.size()) {
      if (pq.empty()) {
        pq.emplace_back(S[i], 1);
      } else if (pq.back().first == S[i]) {
        pq[(int)pq.size() - 1].second++;
      } else {
        pq.emplace_back(S[i], 1);
      }
    }
    rep(i, (int)T.size()) {
      if (tq.empty()) {
        tq.emplace_back(T[i], 1);
      } else if (tq.back().first == T[i]) {
        tq[(int)tq.size() - 1].second++;
      } else {
        tq.emplace_back(T[i], 1);
      }
    }
    debug(pq, tq);

    if (pq.size() != tq.size()) {
      cout << "No" << endl;
      return;
    }
    rep(i, (int)pq.size()) {
      auto si = pq[i];
      auto ti = tq[i];

      if (si.first != ti.first) {
        cout << "No" << endl;
        return;
      }
      if (si.second == 1 && ti.second == 1) continue;
      if (si.second == 1 && ti.second != 1) {
        cout << "No" << endl;
        return;
      }
      if (si.second > ti.second) {
        cout << "No" << endl;
        return;
      }
    }

    /* output */
    cout << "Yes" << endl;
    return;
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