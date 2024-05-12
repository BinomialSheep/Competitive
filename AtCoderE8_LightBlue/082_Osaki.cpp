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
    while (true) {
      /* input */
      int n;
      cin >> n;
      if (n == 0) return;

      vvvi imos(24, vvi(60, vi(61)));

      rep(i, n) {
        string s1, s2;
        cin >> s1 >> s2;
        // hh:mm:ss
        int hh1 = stoi(s1.substr(0, 2));
        int mm1 = stoi(s1.substr(3, 2));
        int ss1 = stoi(s1.substr(6, 2));
        int hh2 = stoi(s2.substr(0, 2));
        int mm2 = stoi(s2.substr(3, 2));
        int ss2 = stoi(s2.substr(6, 2));
        imos[hh1][mm1][ss1]++;
        imos[hh2][mm2][ss2]--;
      }

      int ans = 0;
      int num = 0;
      rep(i, 24) {
        rep(j, 60) {
          rep(k, 60) {
            num += imos[i][j][k];
            chmax(ans, num);
          }
        }
      }

      cout << ans << endl;
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