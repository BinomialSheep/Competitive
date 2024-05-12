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
// #include <atcoder/all>
// using namespace atcoder;

int dfs2(int v, vvi& G, vi& paths, int depth = 0) {
  int ret = 0;
  for (auto u : G[v]) {
    // debug(u, depth);
    ret += dfs2(u, G, paths, depth + 1);
  }
  chmax(ret, 1);
  paths[v] = ret;
  return ret;
}

pair<unordered_set<string>, unordered_set<string>> dfs(
    int v, vector<unordered_set<string>>& S, vvi& G, vi& paths) {
  unordered_map<string, unordered_set<int>> mp;
  unordered_map<string, int> mp2;
  for (auto u : G[v]) {
    pair<unordered_set<string>, unordered_set<string>> res =
        dfs(u, S, G, paths);
    for (auto s : res.first) {
      mp[s].insert(u);
    }
    for (auto s : res.second) {
      mp2[s]++;
    }
  }
  pair<unordered_set<string>, unordered_set<string>> ret;
  if (paths[v] == 1) {
    for (auto [s, st] : mp) ret.first.insert(s);
    for (auto s : S[v]) ret.first.insert(s);
  } else {
    for (auto [s, st] : mp) {
      if ((int)st.size() >= (int)G[v].size()) {
        ret.first.insert(s);
      } else if ((int)st.size() == (int)G[v].size() - 1) {
        for (auto u : G[v]) {
          if (st.count(u) == 0) {
            // debug(u, paths[u], v, s);
            if (paths[u] == 1) {
              if (S[v].count(s)) {
                ret.first.insert(s);
              } else {
                ret.second.insert(s);
              }
            }
            break;
          }
        }
      }
    }
    for (auto [s, cnt] : mp2) {
      if (cnt == 1) {
        if (S[v].count(s)) {
          ret.first.insert(s);
        } else {
          ret.second.insert(s);
        }
      }
    }
  }
  // debug(v, ret);
  return ret;
}
struct Solver {
  void solve() {
    INT(T);
    rep(ti, T) {
      /* input */
      INT(N);
      vvi G(N);
      rep(i, N - 1) {
        INT(a);
        --a;
        G[a].push_back(i + 1);
      }
      // debug(G);

      vector<unordered_set<string>> S(N);
      rep(i, N) {
        INT(M);
        rep(j, M) {
          STR(s);
          S[i].insert(s);
        }
      }
      // debug(S);

      vi paths(N);

      dfs2(0, G, paths);
      // debug(paths);

      int ans = (int)dfs(0, S, G, paths).first.size();

      /* output */
      debug(ti, ans);
      printf("Case #%d: %d\n", ti + 1, ans);
    }
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