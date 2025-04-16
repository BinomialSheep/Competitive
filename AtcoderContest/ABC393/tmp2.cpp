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

const int SIZE = 1e6 + 1;
vector isPrime(SIZE + 1, true);
// 整数iを割り切る最小の素数
vector<int> minfactor(SIZE + 1);
// 高速素因数分解
vector<pair<ll, ll>> factorize(int n) {
  vector<pair<ll, ll>> res;
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

void eratosthenes() {
  minfactor[1] = 1;
  for (int p = 2; p <= SIZE; ++p) {
    // すでに合成数ならスキップ
    if (!isPrime[p]) continue;
    // pはpで割り切れる
    minfactor[p] = p;
    // p以外のpの倍数を合成数に
    for (int q = p * 2; q <= SIZE; q += p) {
      isPrime[q] = false;
      // qはpで割り切れる旨を更新
      if (minfactor[q] == -1) minfactor[q] = p;
    }
  }
}

/**
    例えば
    2^2 * 3^2 * 5^1
    だった場合、
    2^0 * 3^0 * 5^0
    2^0 * 3^0 * 5^1
    2^0 * 3^1 * 5^0
    ...
    2^2 * 3^2 * 5^1
    のようにDFSしていると読み取りました。

    これは漸近的に十分高速ですが、直接配列に
    [1]
    [1, 2, 4]
    [1, 2, 4, 3, 6, 12, 9, 18, 36]
    と突っ込む方が軽いです。
 */
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

int main() {
  ci(n, k);
  cvi(a, n);

  eratosthenes();

  //   vi prime = Prime_List(2e6);
  vector<vpii> soi(1e6 + 1);
  rep(i, n) {
    if (!soi.empty()) soi[a[i]] = factorize(a[i]);
  }
  //   rep(i, n) {
  //     ll x = a[i];
  //     for (auto p : prime) {
  //       ll cnt = 0;
  //       while (x % p == 0) {
  //         x /= p;
  //         cnt++;
  //       }
  //       if (cnt > 0) soi[i].pb(p, cnt);
  //     }
  //   }

  vvi yaku(n);
  map<ll, vi> m;  // 約数aをもつ数bの配ind
  rep(i, n) {
    // 役数列挙
    dfs(yaku[i], soi[i], 0, 1);
    for (auto x : yaku[i]) {
      m[x].pb(a[i]);
    }
  }
  set<ll> li;
  for (auto [a, v] : m) {
    if (v.sz >= k) {
      li.insert(a);
    }
  }
  rep(i, n) {
    ll x = a[i];
    ll mx = 1;
    for (auto j : yaku[i]) {
      if (li.count(j)) chmax(mx, j);
    }
    pr(mx);
  }
}