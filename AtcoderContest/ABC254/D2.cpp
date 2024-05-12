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

ll divisors(ll n, ll lim) {
  ll ret = 0;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i != 0) continue;
    ll j = n / i;
    if (i <= lim && j <= lim) {
      if (i == j)
        ret++;
      else
        ret += 2;
    }
  }
  return ret;
}

struct Solver {
  vl getSquareNumList(ll N) {
    vl ret;
    for (ll i = 1; i <= N; i++) {
      ret.push_back(i * i);
    }
    return ret;
  }

  void solve() {
    /* input */
    ll N;
    cin >> N;

    /* solve */
    vl squareNumList = getSquareNumList(N);
    // rep(i, squareNumList.size()) { cout << squareNumList[i] << " "; }
    // cout << endl;
    // set<pair<ll, ll>> st;
    ll ans = 0;
    for (auto sqar : squareNumList) {
      ans += divisors(sqar, N);
      // cout << ans << endl;

      // for (ll i = 1; i <= N; i++) {
      //   if (sqar % i != 0) continue;
      //   if (sqar / i > N) continue;
      //   st.emplace(i, sqar / i);
      //   st.emplace(sqar / i, i);
      // }
    }

    // for (auto v : st) {
    //   printf("{%d, %d}, ", v.first, v.second);
    // }
    // cout << endl;

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