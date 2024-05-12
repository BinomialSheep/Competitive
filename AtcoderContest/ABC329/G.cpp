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

struct Solver {
  void solve() {
    /* input */
    INT(N, M, K);

    vvi G(N);
    rep(i, N - 1) {
      INT(b);
      int a = i + 1;
      --b;
      G[b].push_back(a);
    }
    vvi ST(N);
    rep(i, M) {
      INT(S, T);
      --S, --T;
      debug(S, T);
      ST[S].push_back(T);
    }
    debug(G);
    debug(ST);

    int flag = 0;  // isZero

    // 子孫セット
    vector<set<int>> children(N);
    // 兄弟への個数
    vector<int> bcnt(N);
    // 親への個数
    vector<int> pcnt(N);
    auto dfs2 = [&](auto rec, int v = 0) -> set<int> {
      set<int> ret;
      for (auto u : G[v]) children[v].insert(u);

      if ((int)G[v].size() == 2) {
        set<int> st0 = rec(rec, G[v][0]);
        set<int> st1 = rec(rec, G[v][1]);
        for (auto u : children[G[v][0]]) children[v].insert(u);
        for (auto u : children[G[v][1]]) children[v].insert(u);
        for (auto u : st0) {
          if (children[G[v][1]].count(u)) {
            bcnt[G[v][0]]++;
          } else {
            ret.insert(u);
          }
        }
        for (auto u : st1) {
          if (children[G[v][0]].count(u)) {
            bcnt[G[v][1]]++;
          } else {
            ret.insert(u);
          }
        }
        if (bcnt[G[v][0]] && bcnt[G[v][1]]) flag = 1;
      } else if ((int)G[v].size() == 1) {
        ret = rec(rec, G[v][0]);
        for (auto u : children[G[v][0]]) children[v].insert(u);
      }
      if (ret.count(v)) ret.erase(v);
      for (auto u : ST[v])
        if (children[v].count(u) == 0) ret.insert(u);
      pcnt[v] = (int)ret.size();
      return ret;
    };
    dfs2(dfs2);

    debug(children);
    debug(bcnt);
    debug(pcnt);

    if (flag) {
      out(0);
      return;
    }

    /* solve */
    using mint = modint998244353;
    mint ans = 0;

    auto dfs = [&](auto rec, int v = 0, int p = -1,
                   int k = 0) -> pair<mint, int> {
      pair<mint, int> ret = make_pair(mint(0), 0);
      // 自分宛ての荷物があれば行きに降ろして帰りに伝える
      

      if ((int)G[v].size() == 0) {
        return make_pair(mint(0), 0);
      } else if ((int)G[v].size() == 1) {
        // 子ども宛の荷物があるなら渡す、ないなら渡さないが最善
        int k2 = k;
        for (auto u : ST[v])
          if (children[v].count(u)) k2++;
        if (k2 > K) return make_pair(mint(0), 0);
        pair<mint, int> res = rec(rec, G[v][0], v, k2);
        ret.first += res.first;
        ret.second += res.second;
      } else {
        int tmp = -1;
        // 兄→弟
        if (bcnt[G[v][1]] == 0) {
          pair<mint, int> ret1 = rec(rec, G[v][0], v, k);
          int k2 = k;
          k2 -= ret1.second;
          k2 += bcnt[G[v][0]];
          pair<mint, int> ret2 = rec(rec, G[v][1], v, k2);
          ret.first += ret1.first * ret2.first;
          if (tmp == -1) tmp = ret1.second + ret2.second;
        }
        // 弟→兄
        if (bcnt[G[v][0]] == 0) {
          pair<mint, int> ret1 = rec(rec, G[v][1], v, k);
          int k2 = k;
          k2 -= ret1.second;
          k2 += bcnt[G[v][1]];
          pair<mint, int> ret2 = rec(rec, G[v][0], v, k2);
          ret.first += ret1.first * ret2.first;
          if (tmp == -1) tmp = ret1.second + ret2.second;
        }
      }
      return ret;
    };
    dfs(dfs);

    /* output */
    out(ans.val());
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