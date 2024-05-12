#include <bits/stdc++.h>
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
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

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
    int cntSS = 0;
    int cntS = 0;
    int cntA1 = 0;
    int cntA2 = 0;
    int cnt = 0;
    int total = 0;

    while (!cin.eof()) {
      int num;
      string s;
      cin >> num >> s;
      if (s.substr(0, 2) == "To") {
        cntSS += num;
      }
      if (s.substr(0, 2) == "pv") {
        cntS += num;
      }
      if (s.substr(0, 2) == "1f") {
        cntA1 += num;
      }
      if (s.substr(0, 2) == "AP") {
        cntA2 += num;
      }
      cnt += num;
      if (cnt >= 1000) {
        total += cnt;
        printf("%d %d %d\n", cntSS, cntS, cntA1 + cntA2);
        cntSS = 0;
        cntS = 0;
        cntA1 = 0;
        cntA2 = 0;
        cnt -= 1000;
      }
    }

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