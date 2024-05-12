#pragma region header
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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define INT(...)   \
  int __VA_ARGS__; \
  in(__VA_ARGS__)
#define LL(...)   \
  ll __VA_ARGS__; \
  in(__VA_ARGS__)
#define STR(...)      \
  string __VA_ARGS__; \
  in(__VA_ARGS__)
#define Sort(a) sort(all(a))
#define VEC(type, name, size) \
  vector<type> name(size);    \
  in(name)
[[maybe_unused]] void print() {}
template <class T, class... Ts>
void print(const T& t, const Ts&... ts);
template <class... Ts>
void out(const Ts&... ts) {
  print(ts...);
  cout << '\n';
}

namespace IO {
#define VOID(a) decltype(void(a))
struct S {
  S() {
    cin.tie(nullptr)->sync_with_stdio(0);
    fixed(cout).precision(12);
  }
} S;
template <int I>
struct P : P<I - 1> {};
template <>
struct P<0> {};
template <class T>
void i(T& t) {
  i(t, P<3>{});
}
void i(vector<bool>::reference t, P<3>) {
  int a;
  i(a);
  t = a;
}
template <class T>
auto i(T& t, P<2>) -> VOID(cin >> t) {
  cin >> t;
}
template <class T>
auto i(T& t, P<1>) -> VOID(begin(t)) {
  for (auto&& x : t) i(x);
}
template <class T, size_t... idx>
void ituple(T& t, index_sequence<idx...>) {
  in(get<idx>(t)...);
}
template <class T>
auto i(T& t, P<0>) -> VOID(tuple_size<T>{}) {
  ituple(t, make_index_sequence<tuple_size<T>::value>{});
}
template <class T>
void o(const T& t) {
  o(t, P<4>{});
}
template <size_t N>
void o(const char (&t)[N], P<4>) {
  cout << t;
}
template <class T, size_t N>
void o(const T (&t)[N], P<3>) {
  o(t[0]);
  for (size_t i = 1; i < N; i++) {
    o(' ');
    o(t[i]);
  }
}
template <class T>
auto o(const T& t, P<2>) -> VOID(cout << t) {
  cout << t;
}
template <class T>
auto o(const T& t, P<1>) -> VOID(begin(t)) {
  bool first = 1;
  for (auto&& x : t) {
    if (first)
      first = 0;
    else
      o(' ');
    o(x);
  }
}
template <class T, size_t... idx>
void otuple(const T& t, index_sequence<idx...>) {
  print(get<idx>(t)...);
}
template <class T>
auto o(T& t, P<0>) -> VOID(tuple_size<T>{}) {
  otuple(t, make_index_sequence<tuple_size<T>::value>{});
}
#undef VOID
}  // namespace IO
#define unpack(a) \
  (void)initializer_list<int> { (a, 0)... }
template <class... Ts>
void in(Ts&... t) {
  unpack(IO::i(t));
}
template <class T, class... Ts>
void print(const T& t, const Ts&... ts) {
  IO::o(t);
  unpack(IO::o((cout << ' ', ts)));
}
#undef unpack
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#define YESNO(yes, no)                          \
  void yes(bool i = 1) { out(i ? #yes : #no); } \
  void no() { out(#no); }
YESNO(first, second)
YESNO(First, Second)
YESNO(Yes, No)
YESNO(YES, NO)
YESNO(possible, impossible)
YESNO(POSSIBLE, IMPOSSIBLE)
#pragma endregion header
#include <atcoder/all>
using namespace atcoder;

// HL分解（Heavy Light Decomposition）
// beet-aizuさんから窃盗
// https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
// BEGIN CUT HERE
class HLD {
 private:
  void dfs_sz(int v) {
    auto& es = G[v];
    if (~par[v]) es.erase(find(es.begin(), es.end(), par[v]));

    for (int& u : es) {
      par[u] = v;
      dfs_sz(u);
      sub[v] += sub[u];
      if (sub[u] > sub[es[0]]) swap(u, es[0]);
    }
  }

  void dfs_hld(int v, int& pos) {
    vid[v] = pos++;
    inv[vid[v]] = v;
    for (int u : G[v]) {
      if (u == par[v]) continue;
      nxt[u] = (u == G[v][0] ? nxt[v] : u);
      dfs_hld(u, pos);
    }
  }

 public:
  vector<vector<int>> G;

  // vid: vertex -> idx
  // inv: idx -> vertex
  vector<int> vid, nxt, sub, par, inv;

  HLD(int n) : G(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

  void add_edge(int u, int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  void build(int r = 0) {
    int pos = 0;
    dfs_sz(r);
    nxt[r] = r;
    dfs_hld(r, pos);
  }

  int lca(int u, int v) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      if (nxt[u] == nxt[v]) return u;
      v = par[nxt[v]];
    }
  }

  template <typename F>
  void for_each(int u, int v, const F& f) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      f(max(vid[nxt[v]], vid[u]), vid[v] + 1);
      if (nxt[u] != nxt[v])
        v = par[nxt[v]];
      else
        break;
    }
  }

  template <typename F>
  void for_each_edge(int u, int v, const F& f) {
    while (1) {
      if (vid[u] > vid[v]) swap(u, v);
      if (nxt[u] != nxt[v]) {
        f(vid[nxt[v]], vid[v] + 1);
        v = par[nxt[v]];
      } else {
        if (u != v) f(vid[u] + 1, vid[v] + 1);
        break;
      }
    }
  }
};
// END CUT HERE

using mint = modint1000000007;

// 遅延セグ木を定義（区間和取得、区間加算）
struct S {
  mint value;
  mint infl;
};
using F = mint;

S op(S a, S b) { return {a.value + b.value, a.infl + b.infl}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {x.value + f * x.infl, x.infl}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  /* input */
  INT(N);
  vector<mint> prices(N);
  rep(i, N) {
    INT(a);
    prices[i] = a;
  }
  vector<mint> inflation(N);
  rep(i, N) {
    INT(a);
    inflation[i] = a;
  }
  HLD G(N);
  rep(i, N - 1) {
    INT(A, B);
    --A;
    --B;
    G.add_edge(A, B);
  }
  /* preprocessing */
  G.build();
  debug(G.vid, G.nxt, G.par, G.sub);
  std::vector<S> v(N);
  rep(i, N) v[i] = {prices[G.inv[i]], inflation[G.inv[i]]};
  lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

  /* query */
  INT(Q);
  rep(qi, Q) {
    INT(ty, X, Y);
    --X, --Y;
    if (ty == 0) {
      INT(Z);
      G.for_each(X, Y, [&](int l, int r) { seg.apply(l, r, Z); });

    } else {
      mint ans = 0;
      debug(ty, X, Y);
      G.for_each(X, Y, [&](int l, int r) { ans += seg.prod(l, r).value; });
      out(ans.val());
    }
  }

  return 0;
}