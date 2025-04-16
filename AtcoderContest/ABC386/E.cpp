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

struct Solver {
  void solve() {
    /* input */
    INT(N, K);
    VEC(ll, A, N);

    ll ans = 0;

    if (K == 1) {
      rep(i, N) chmax(ans, A[i]);
    } else if (K == 2) {
      rep(i, N) rep(j, i) { chmax(ans, A[i] ^ A[j]); }
    } else if (K == 3) {
      rep(i, N) rep(j, i) rep(k, j) { chmax(ans, A[i] ^ A[j] ^ A[k]); }
    } else if (K == 4) {
      rep(i, N) rep(j, i) rep(k, j) rep(l, k) {
        chmax(ans, A[i] ^ A[j] ^ A[k] ^ A[l]);
      }
    } else if (N < 20) {
      /* solve */
      auto f = [&](auto rec, int idx = 0, int selected = 0,
                   ll nowXor = 0) -> void {
        if (selected + N - idx < K) return;
        if (selected == K) {
          chmax(ans, nowXor);
          return;
        }
        rec(rec, idx + 1, selected + 1, nowXor ^ A[idx]);
        rec(rec, idx + 1, selected, nowXor);
      };
      f(f);
    } else {
      vector<set<ll>> mp(11);
      auto g = [&](auto rec, int idx = 0, int selected = 0,
                   ll nowXor = 0) -> void {
        // debug(idx, selected);
        if (idx == 10) {
          mp[selected].insert(nowXor);
          return;
        }
        rec(rec, idx + 1, selected + 1, nowXor ^ A[idx]);
        rec(rec, idx + 1, selected, nowXor);
      };
      g(g);

      // rep(i, 10) st1.insert(A[i]);
      // rep(i, 10) rep(j, i) st2.insert(A[i] ^ A[j]);
      // rep(i, 10) rep(j, i) rep(k, j) st3.insert(A[i] ^ A[j] ^ A[k]);
      // rep(i, 10) rep(j, i) rep(k, j) rep(l, j)
      //     st4.insert(A[i] ^ A[j] ^ A[k] ^ A[l]);

      // debug(st1, st2, st3, st4);
      // debug(mp);

      auto f = [&](auto rec, int K2, int idx, int selected, ll nowXor) -> void {
        // debug(selected, N - idx, nowXor, K);
        if (selected + N - idx < K) return;
        if (selected == K) {
          // debug(selected, K2, nowXor);
          for (auto v : mp[K2]) {
            chmax(ans, nowXor ^ v);
          }
          // if (K2 == 0) {
          //   chmax(ans, nowXor);
          // } else if (K2 == 1) {
          //   for (auto v : st1) chmax(ans, nowXor ^ v);
          // } else if (K2 == 2) {
          //   for (auto v : st2) chmax(ans, nowXor ^ v);
          // }
          // // else if (K2 == K - 3) {
          //   for (auto v : st3) chmax(ans, nowXor ^ v);
          // } else if (K2 == K - 4) {
          //   for (auto v : st4) chmax(ans, nowXor ^ v);
          // }
          return;
        }
        // if (idx == N) return;
        rec(rec, K2, idx + 1, selected + 1, nowXor ^ A[idx]);
        rec(rec, K2, idx + 1, selected, nowXor);
      };

      // f(f, 0, 10, 0, 0);

      rep(i, 10) { f(f, i, 10, i, 0); }

      // f(f, K - 3, 10, 3);
      // f(f, K - 4, 10, 4);
    }

    /* output */
    out(ans);
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