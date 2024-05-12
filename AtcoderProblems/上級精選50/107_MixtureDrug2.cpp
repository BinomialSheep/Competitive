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
    INT(N, M);
    // 隣接行列
    int SIZE1 = N / 2;
    int SIZE2 = N - N / 2;
    vvi G(N, vi(N));
    rep(i, M) {
      INT(A, B);
      --A, --B;
      G[A][B] = G[B][A] = 1;
    }

    // 頂点集合V1の部分集合S1について、S1が独立集合かという配列ok
    // 頂点集合V2についてのok2
    vector<int> ok(1 << SIZE1);
    vector<int> ok2(1 << SIZE2);

    ok[0] = 1;
    rep(S1, 1 << SIZE1) {
      rep(i, SIZE1) {
        int next = S1 | (1 << i);
        if (!ok[S1]) continue;
        if (ok[next]) continue;
        int flag = 1;
        rep(j, SIZE1) if ((S1 >> j & 1) && G[i][j]) flag = 0;
        if (flag) ok[next] = 1;
      }
    }
    // debug(ok);

    ok2[0] = 1;
    rep(S2, 1 << SIZE2) {
      rep(i, SIZE2) {
        int next = S2 | (1 << i);
        if (!ok2[S2]) continue;
        if (ok2[next]) continue;
        int flag = 1;
        rep(j, SIZE2) if ((S2 >> j & 1) && G[i + SIZE1][j + SIZE1]) flag = 0;
        if (flag) ok2[next] = 1;
      }
    }
    // debug(ok2);

    // S1の頂点と辺で結ばれていないV2の頂点の集合
    vector<int> U(1 << SIZE1);
    U[0] = (1 << SIZE2) - 1;
    rep(i, SIZE1) rep(j, SIZE2) {
      if (G[i][j + SIZE1]) continue;
      U[1 << i] |= 1 << j;
    }
    // debug(U);
    rep(bit, 1 << SIZE1) rep(i, SIZE1) {
      if (U[bit | 1 << i]) {
        assert(U[bit | (1 << i)] == (U[bit] & U[1 << i]));
      } else {
        U[bit | (1 << i)] = U[bit] & U[1 << i];
      }
    }
    // debug(U);

    // V2の部分集合Uの最大独立集合
    vector<int> dp(1 << SIZE2);
    rep(S2, 1 << SIZE2) if (ok2[S2]) dp[S2] = S2;
    rep(S2, 1 << SIZE2) {
      rep(i, SIZE2) {
        int next = S2 | (1 << i);
        if (__builtin_popcount(dp[next]) < __builtin_popcount(dp[S2]))
          dp[next] = dp[S2];
      }
    }
    // debug(dp);

    // 計算
    int ans = 0;
    rep(i, ok.size()) {
      if (!ok[i]) continue;
      int s1Size = __builtin_popcount(i);
      int s2Size = __builtin_popcount(dp[U[i]]);
      chmax(ans, s1Size + s2Size);
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