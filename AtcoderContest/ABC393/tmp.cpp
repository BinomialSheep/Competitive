// All 2024/11/14
#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using vpii = vector<pair<ll, ll>>;
using vvi = vector<vector<ll>>;
using vvb = vector<vector<bool>>;
using pii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vs = vector<string>;
using mint = modint1000000007;
using MINT = modint;
const ll MOD = 998244353;
const ll INF = 1000000007;
const ll LINF = 1e18;
template <class T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template <class... T>
void input(T&... a) {
  (cin >> ... >> a);
}
template <class T, class... Ts>
void pr(const T& a, const Ts&... b) {
  cout << a;
  (cout << ... << (cout << ' ', b));
  cout << '\n';
}
template <class T, class... Ts>
void prs(const T& a, const Ts&... b) {
  cout << a;
  (cout << ... << (cout << ' ', b));
  cout << ' ';
}
template <class T, class... Ts>
void prn(const T& a, const Ts&... b) {
  cout << a;
  (cout << ... << (cout << ' ', b));
}
template <class T>
void prv(vector<T>& a) {
  for (T x : a) cout << x << ' ';
  cout << '\n';
}
template <class T>
void prvp(vector<T>& a) {
  for (T x : a) cout << x.first << ' ' << x.second << '\n';
  cout << '\n';
}
template <class T>
void prvv(vector<T>& a) {
  for (auto x : a) {
    for (auto y : x) {
      cout << y << ' ';
    }
    cout << '\n';
  }
}
template <class T>
void prvvi(vector<T>& a) {
  for (auto x : a) {
    for (auto y : x) {
      if (y != INF && y != LINF && y != -1)
        cout << y << ' ';
      else
        cout << '#' << ' ';
    }
    cout << '\n';
  }
}
void prp(pii& a) {
  cout << a.first << ' ' << a.second;
  cout << '\n';
}
void Say(bool x) {
  if (x == 1)
    cout << "Yes" << '\n';
  else if (x == 0)
    cout << "No" << '\n';
}
void pr() { cout << '\n'; }
template <class T, class U>
inline bool chmin(T& a, const U& b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <class T, class U>
inline bool chmax(T& a, const U& b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
#define ci(...)   \
  ll __VA_ARGS__; \
  input(__VA_ARGS__)
#define cs(...)       \
  string __VA_ARGS__; \
  input(__VA_ARGS__)
#define rep(i, n) for (ll i = 0; i < n; i++)
#define repe(i, n) for (ll i = 1; i <= n; i++)
#define all(x) x.begin(), x.end()
#define rev(x) x.rbegin(), x.rend()
#define cvi(a, H) \
  vi a(H);        \
  rep(i, H) cin >> a[i]
#define cvs(a, H) \
  vs a(H);        \
  rep(i, H) cin >> a[i]
#define cvvi(x, h, w) \
  vvi x(h, vi(w));    \
  rep(i, h) rep(j, w) cin >> x[i][j]
#define eraseSame(s) s.erase(unique(s.begin(), s.end()), s.end())
#define sz size()
#define re0 return 0
#define ft first
#define sd second
#define pb emplace_back
#define itos to_string

vb Make_isPrimeTable(ll n) {
  n++;
  vb isPrime(n, 1);
  isPrime[0] = 0, isPrime[1] = 0;
  for (ll i = 2; i * i <= n; i++) {
    if (isPrime[i]) {
      for (ll j = i * 2; j < n; j += i) isPrime[j] = 0;
    }
  }
  return isPrime;
}

vi Prime_List(ll n) {
  vi pl;
  vb isPrime = Make_isPrimeTable(n);
  for (ll i = 0; i < n; i++) {
    if (isPrime[i]) pl.push_back(i);
  }
  return pl;
}

void dfs(vi& yaku, vpii& soi, ll i, ll x) {
  if (i == soi.sz) {
    yaku.pb(x);
    return;
  }
  rep(j, soi[i].sd + 1) {
    dfs(yaku, soi, i + 1, x);
    x *= soi[i].ft;
  }
}

// 素数列挙：O(N loglogN)
// 素因数分解：O(N longN)
struct Eratosthenes {
  // 1-indexed
  vector<bool> isPrime;
  // 整数iを割り切る最小の素数
  vector<int> minfactor;

  //
  int size;

  // コンストラクタ
  Eratosthenes(int N) : isPrime(N + 1, true), minfactor(N + 1, -1), size(N) {
    isPrime[1] = false;
    minfactor[1] = 1;
    // ふるい
    for (int p = 2; p <= N; ++p) {
      // すでに合成数ならスキップ
      if (!isPrime[p]) continue;
      // pはpで割り切れる
      minfactor[p] = p;

      // p以外のpの倍数を合成数に
      for (int q = p * 2; q <= N; q += p) {
        isPrime[q] = false;
        // qはpで割り切れる旨を更新
        if (minfactor[q] == -1) minfactor[q] = p;
      }
    }
  }

  // 高速素因数分解 O(log N)
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

  // 約数列挙：O(約数の個数個)。1e6以下の最大の約数の個数は240、1e9で1344
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
          v *= p.first;
          res.push_back(res[i] * v);
        }
      }
    }
    return res;
  }
};

int main() {
  ci(n, k);
  cvi(a, n);

  //   vi prime = Prime_List(1e6 + 1);
  //   // A[i]の素因数分解
  //   vector<vpii> soi(1e6 + 1);
  //   rep(i, n) {
  //     if (!soi[a[i]].empty()) continue;
  //     ll x = a[i];
  //     for (auto p : prime) {
  //       ll cnt = 0;
  //       while (x % p == 0) {
  //         x /= p;
  //         cnt++;
  //       }
  //       if (cnt > 0) soi[a[i]].pb(p, cnt);
  //       if (p > x) break;
  //     }
  //   }

  Eratosthenes er(1000001);

  // A[i]が重複した時に再計算しなくて済むように、yaku[i]でなくyaku[A[i]]を持つ
  vector<vector<int>> yaku(1e6);
  // 個数だけ分かればいいので、map<ll, vi>からviに変更
  vi m(1e6);
  rep(i, n) {
    // 役数列挙はけんちょんさんの記事を参考に高速化する
    if (yaku[a[i]].empty()) yaku[a[i]] = er.divisors((int)a[i]);
    for (auto x : yaku[a[i]]) {
      m[x]++;
    }
  }
  rep(i, n) {
    ll mx = 1;
    for (auto j : yaku[a[i]]) {
      if (m[j] >= k) chmax(mx, j);
    }
    pr(mx);
  }
}