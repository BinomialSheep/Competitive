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

// 繰り返し自乗法 O(log n)
/* pow(x, n)
   = 1 (n == 0)
   = power(xx, n/2) (nが偶数）
   = power(xx, n/2) * x (nが奇数）
   以下は、power(xx, n/2) == 2 * power(x, n/2) を利用
*/
using ull = unsigned long long;
ull myPower(ull x, ull n, ull MOD) {
  ull res = 1;
  if (n > 0) {
    res = myPower(x, n / 2, MOD);
    res = (res * res) % MOD;
    if (n % 2 == 1) res = (res * x) % MOD;
  }
  return res;
}

struct Solver {
  void solve() {
    /* input */
    ll m, n;
    cin >> m >> n;

    int MOD = 1e9 + 7;

    /* solve */
    unsigned long long ans = myPower(m, n, MOD);

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