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
    INT(N, Q);

    /* solve */
    map<pair<int, int>, int> dp;
    dp[make_pair(1, 2)] = 0;

    rep(qi, Q) {
      STR(H);
      INT(T);
      map<pair<int, int>, int> ndp;
      auto f = [&](int left, int right, int value, int v) {
        if (left == 0) left = N;
        if (left == N + 1) left = 1;
        if (right == 0) right = N;
        if (right == N + 1) right = 1;
        auto p = make_pair(left, right);
        if (ndp.count(p)) {
          chmin(ndp[p], value + v);
        } else {
          ndp[p] = value + v;
        }
      };

      for (auto [p, value] : dp) {
        int left = p.first, right = p.second;

        if (H == "R") {
          if (right == T) {
            // 何もしないのが最善
            f(left, T, value, 0);
          } else if (left == T) {
            // leftをプラスかマイナスにずらす
            if (right < T) {
              f(left + 1, T, value, 1 + (T - right));
              f(left - 1, T, value, 1 + (N - T + right));
            } else {
              f(left + 1, T, value, 1 + (N - right + T));
              f(left - 1, T, value, 1 + (right - T));
            }
          } else if (left < right && right < T) {
            // そのまま行く場合
            f(left, T, value, T - right);
            // leftを左回りにずらす場合
            f(T - 1, T, value, (left + 1 + N - T) + (right + N - T));
          } else if (left < T && T < right) {
            f(left, T, value, right - T);
            f(T + 1, T, value, (T - left + 1) + (T + N - right));
          } else if (right < left && left < T) {
            f(left, T, value, (N - T + right));
            f(T + 1, T, value, (T - left + 1) + (T - right));
          } else if (right < T && T < left) {
            f(left, T, value, (T - right));
            f(T - 1, T, value, (left - T + 1) + (N - T + right));
          } else if (T < left && left < right) {
            f(left, T, value, T + N - right);
            f(T - 1, T, value, (left - T + 1) + (right - T));
          } else if (T < right && right < left) {
            f(left, T, value, right - T);
            f(T + 1, T, value, (N - left + T + 1) + (N - right + T));
          }
        } else {
          if (left == T) {
            // 何もしないのが最善
            f(T, right, value, 0);
          } else if (right == T) {
            // rightをプラスかマイナスにずらす
            if (left < T) {
              f(T, T + 1, value, 1 + (T - left));
              f(T, T - 1, value, 1 + (N - T + left));
            } else {
              f(T, T + 1, value, 1 + (N - left + T));
              f(T, T - 1, value, 1 + (left - T));
            }
          } else if (left < right && right < T) {
            f(T, right, value, left + (N - T));
            f(T, T + 1, value, (1 + T - right) + (T - left));
          } else if (left < T && T < right) {
            f(T, right, value, T - left);
            f(T, T - 1, value, (right - T + 1) + (left + N - T));
          } else if (right < left && left < T) {
            f(T, right, value, T - left);
            f(T, T - 1, value, (right + N - T + 1) + (left + N - T));
          } else if (right < T && T < left) {
            f(T, right, value, left - T);
            f(T, T + 1, value, (1 + T - right) + (N - left + T));
          } else if (T < left && left < right) {
            f(T, right, value, left - T);
            f(T, T + 1, value, (N - right + T + 1) + (N - left + T));
          } else if (T < right && right < left) {
            f(T, right, value, N - left + T);
            f(T, T - 1, value, (right - T + 1) + (left - T));
          }
        }
      }
      // debug(ndp);
      swap(dp, ndp);
    }

    /* output */
    int ans = 1e9;
    for (auto [_, v] : dp) chmin(ans, v);
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