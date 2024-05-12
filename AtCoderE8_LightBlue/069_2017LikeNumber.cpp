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

// 素数列挙：O(N loglogN)
// 素因数分解：O(N longN)
struct Eratosthenes {
  // 1-indexed
  vector<bool> isPrime;
  // 整数iを割り切る最小の素数
  vector<int> minfactor;
  // メビウス関数値
  vector<int> mobius;
  //
  int size;

  // コンストラクタ
  Eratosthenes(int N)
      : isPrime(N + 1, true), minfactor(N + 1, -1), mobius(N + 1, 1), size(N) {
    isPrime[1] = false;
    minfactor[1] = 1;
    // ふるい
    for (int p = 2; p <= N; ++p) {
      // すでに合成数ならスキップ
      if (!isPrime[p]) continue;
      // pはpで割り切れる
      minfactor[p] = p;

      mobius[p] = -1;

      // p以外のpの倍数を合成数に
      for (int q = p * 2; q <= N; q += p) {
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
  vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> res;
    while (n > 1) {
      int p = minfactor[n];
      int exp = 0;
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
  vector<int> divisors(int n) {
    vector<int> res({1});
    // nを素因数分解
    auto pf = factorize(n);
    // 約数列挙
    for (auto p : pf) {
      int s = (int)res.size();
      for (int i = 0; i < s; ++i) {
        int v = 1;
        for (int j = 0; j < p.second; ++j) {
          v += p.first;
          res.push_back(res[i] * v);
        }
      }
    }
    return res;
  }
};

struct Solver {
  void solve() {
    // 前処理
    int LIM = 100009;
    Eratosthenes er(LIM);
    // iまでの2017like num
    vi prefixPrimeList(LIM);
    for (int i = 3; i < LIM - 5; i++) {
      prefixPrimeList[i] = prefixPrimeList[i - 1];
      if (i % 2 == 0) continue;
      if (er.isPrime[i] && er.isPrime[(i + 1) / 2]) prefixPrimeList[i]++;
    }

    int Q;
    cin >> Q;
    rep(qi, Q) {
      int l, r;
      cin >> l >> r;

      cout << prefixPrimeList[r] - prefixPrimeList[l - 1] << endl;
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