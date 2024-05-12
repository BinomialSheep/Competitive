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

// コンストラクタ
Eratosthenes(ll N)
    : isPrime(N + 1, true), minfactor(N + 1, -1), mobius(N + 1, 1), size(N) {
  isPrime[1] = false;
  minfactor[1] = 1;
  // ふるい
  for (ll p = 2; p <= N; ++p) {
    // すでに合成数ならスキップ
    if (!isPrime[p]) continue;
    // pはpで割り切れる
    minfactor[p] = p;

    mobius[p] = -1;

    // p以外のpの倍数を合成数に
    for (ll q = p * 2; q <= N; q += p) {
      isPrime[q] = false;
      // qはpで割り切れる旨を更新
      if (minfactor[q] == -1) minfactor[q] = p;
      // nが2回以上割り切れるなら0、そうでなければ符号反転
      if ((q / p) % p == 0)
        mobius[q] = 0;
      else
        mobius[q] = -mobius[q];
    }
  }
}

// 高速素因数分解 O(N log N)
vector<pair<ll, ll>> factorize(ll n) {
  vector<pair<ll, ll>> res;
  while (n > 1) {
    ll p = minfactor[n];
    ll exp = 0;
    // nで割れるだけ割る
    while (minfactor[n] == p) {
      n /= p;
      ++exp;
    }
    res.emplace_back(p, exp);
  }
  return res;
}

// 約数列挙：O(約数の個数個)。n <= 10^9の場合1344
vector<ll> divisors(ll n) {
  vector<ll> res({1});
  // nを素因数分解
  auto pf = factorize(n);
  // 約数列挙
  for (auto p : pf) {
    ll s = (ll)res.size();
    for (ll i = 0; i < s; ++i) {
      ll v = 1;
      for (ll j = 0; j < p.second; ++j) {
        v += p.first;
        res.push_back(res[i] * v);
      }
    }
  }
  return res;
};

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