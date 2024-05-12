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
    int N, M;
    cin >> N >> M;
    vi A(N), B(N);
    rep(i, N) cin >> A[i] >> B[i];

    /* solve */
    map<int, int> mp;

    vvi rev(M + 10);
    rep(i, N) {
      rev[A[i]].push_back(i + 1);
      rev[B[i]].push_back(i + 1);
    }

    vl imos(M + 2);

    int idx = 1;
    int flag = true;
    for (int i = 1; i <= M; i++) {
      while (true) {
        if (idx < i) {
          idx = i;
          flag = true;
        }
        // 格納
        if (flag) {
          for (auto v : rev[idx]) {
            mp[v]++;
          }
        }
        // 判定
        if ((int)mp.size() == N) {
          // debug(i, idx, "これ以降はOK");
          imos[idx - i + 1]++;
          imos[M - i + 2]--;
          // debug(imos);
          flag = false;
          break;
        }
        idx++;
        flag = true;
        if (idx == M + 1) break;
      }
      if (idx == M + 1) break;
      // 削除
      // debug(i, idx, mp);
      for (auto v : rev[i]) {
        if (mp[v] == 1) {
          mp.erase(v);
        } else {
          --mp[v];
        }
      }
    }

    // debug(imos);

    for (int i = 1; i <= M + 1; i++) {
      imos[i] += imos[i - 1];
    }
    // debug(imos);

    /* output */
    rep(i, M) { cout << imos[i + 1] << " "; }
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