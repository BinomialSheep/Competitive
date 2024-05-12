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

// 普通の素因数分解
template <typename T>
vector<pair<T, T>> calcPrimeFactorSimple(T n) {
  vector<pair<T, T>> ret;
  for (T i = 2; i * i <= n; i++) {
    if (n % i != 0) continue;
    T tmp = 0;
    while (n % i == 0) {
      tmp++;
      n /= i;
    }
    ret.emplace_back(i, tmp);
  }
  if (n != 1) ret.emplace_back(n, 1);
  return ret;
}

struct Solver {
  ll bfs(vector<pii> &vec, ll x, ll y, ll N) {
    if (vec.empty()) {
      // cout << x * y << " " << x << " " << y << endl;
      return 1;
    }
    auto p = vec.back();
    vec.pop_back();
    // p.secondの数だけxとyを試す
    ll ret = 0;
    for (int i = 0; i <= p.second; i++) {
      ll x2 = x * (ll)pow(p.first, i);
      ll y2 = y * (ll)pow(p.first, p.second - i);
      if (x2 > N || y2 > N) continue;
      ret += bfs(vec, x2, y2, N);
    }
    vec.push_back(p);

    return ret;
  }

  void solve() {
    /* input */
    int N;
    cin >> N;

    /* solve */
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
      if (i == 1) {
        ans += 1;
        continue;
      }
      // iの素因数分解が分かればi*iの素因数分解は自明
      vector<pii> primeFactorList = calcPrimeFactorSimple(i);
      rep(j, (int)primeFactorList.size()) primeFactorList[j].second *= 2;
      //
      // cout << i * i << ": ";
      // for (auto p : primeFactorList) {
      //   cout << p.first << " " << p.second << " ";
      // }
      // cout << endl;
      // 各 x * y = i*iについて、x <= N && y <= Nになっているものだけカウント
      ans += bfs(primeFactorList, 1, 1, N);
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