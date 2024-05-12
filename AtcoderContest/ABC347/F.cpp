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
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace chrono;
struct Solver {
  void solve() {
    auto startClock = system_clock::now();
    const static double END_TIME = 2.9;  // 終了時間（秒）
    double time = 0.0;                    // 経過時間（秒）
    /* input */
    INT(N, M);
    vvl A(N, vl(N));
    rep(i, N) rep(j, N) cin >> A[i][j];

    /* solve */

    using P = pair<ll, pair<int, int>>;

    vector<P> vec;

    vector<vl> s(N + 1, vl(N + 1, 0));
    rep(i, N) rep(j, N) {
      s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + A[i][j];
    }

    rep(i, N) rep(j, N) {
      ll sum = 0;
      if (i + M > N || j + M > N) continue;
      int i2 = i + M, j2 = j + M;

      sum = s[i2][j2] - s[i][j2] - s[i2][j] + s[i][j];
      vec.emplace_back(sum, make_pair(i, j));
    }
    // debug(vec);
    sort(all(vec));
    reverse(all(vec));

    // debug(vec);

    auto f = [&](pair<int, int> p1, pair<int, int> p2) {
      auto [x1, y1] = p1;
      auto [x2, y2] = p2;

      if (x1 > x2) swap(x1, x2);
      if (y1 > y2) swap(y1, y2);

      return x2 - x1 < M && y2 - y1 < M;
    };
    ll ans = 0;

    rep(i, (int)vec.size()) {
      if (time >= END_TIME) break;
      rep(j, i) {
        if (f(vec[i].second, vec[j].second)) continue;

        time = ((double)duration_cast<microseconds>(system_clock::now() -
                                                    startClock)
                    .count() *
                1e-6);
        if (time >= END_TIME) break;
        rep(k, j) {
          // debug(i, j, k, vec[i], vec[j], vec[k]);

          // debug(vec[i].second, vec[j].second, vec[k].second);
          // debug(f(vec[j].second, vec[k].second),
          // f(vec[i].second, vec[k].second));
          if (f(vec[j].second, vec[k].second)) continue;
          if (f(vec[i].second, vec[k].second)) continue;
          time = ((double)duration_cast<microseconds>(system_clock::now() -
                                                      startClock)
                      .count() *
                  1e-6);
          // debug(i, j, k);
          ll mx = vec[i].first + vec[j].first + vec[k].first;
          if (chmax(ans, mx)) break;
        }
      }
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