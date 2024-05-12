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

ll stupid(ll N, ll K) {
  vl A(N);
  rep(i, N) A[i] = i + 1;
  ll cnt = 0;

  auto f = [&](auto rec, ll l, ll r) -> void {
    cnt++;
    // debug(l, r);
    if (r == l + 1) {
      swap(A[l], A[r]);
      return;
    }
    rec(rec, l, r - 1);
    rec(rec, l + 1, r);
  };
  f(f, 0, N - 1);

  // debug(N);
  debug(A);
  // int left = 0, right = 0;
  // int mx = 0;
  // int leng = 0;
  // int nowleft = -1;
  // rep(i, N - 1) {
  //   if (A[i] + 1 == A[i + 1]) {
  //     leng++;
  //     if (chmax(mx, leng)) {
  //       left = nowleft;
  //       right = i + 1;
  //     }
  //   } else {
  //     leng = 0;
  //     nowleft = i + 1;
  //     right = -1;
  //   }
  // }
  // debug(left, right, mx);

  return A[K];
}

ll solve2(ll N, ll K) {
  ll ans = -1;
  if (K == 1) {
    ans = 2;
  }
  if (K == N) {
    if (N % 2) {
      ans = N - 2;
    } else {
      ans = N - 1;
    }
  }
  if (K == N - 1) {
    ans = N;
  }

  if (ans != -1) return ans;

  auto rec = [&](auto f, ll M, ll K2) -> ll {
    // debug(M, K2);
    if (M % 2) {
      ll tmp = f(f, M - 1, K2 - 1);
      // debug(tmp);
      return f(f, M - 1, tmp + 1);
    }
    ll M2 = M;
    ll a = 0;
    while (M2 > 1) {
      M2 /= 2;
      a++;
    }
    ll M3 = 1;
    rep(i, a) M3 *= 2;
    ll b = M - M3;

    // debug(a, b);

    if (b == 0) {
      return (K2 % 2) ? K2 + 1 : K2 - 1;
    } else if (K2 <= b) {
      return f(f, b, K2);
    } else if (M - b < K2) {
      return M - b + f(f, b, K2 - (M - b));
    }
    return K2;
  };
  return rec(rec, N, K);
}

struct Solver {
  void solve() {
    /* input */
    INT(T);
    rep(ti, T) {
      LL(N, K);

      // ll tmp = stupid(N, K - 1);
      ll ans = solve2(N, K);

      // debug(tmp, ans);
      // assert(tmp == ans);
      out(ans);

      //

      // if (b == 0) {
      // }

      // auto f = [&](ll n) -> ll { return (n % 2) ? n + 1 : n - 1; };

      // ans = K;
      // ll N4 = N;
      // if (N % 2) N4--;
      // // if (ans <= b) ans = f(ans);
      // if (b == 0 || K <= b || N4 - b < K) ans = f(ans);

      // debug(ans);

      // // ans番目がK⇔K番目がansに移っている
      // if (N % 2) {
      //   ll c = K - 1;
      //   if (b == 0 || c <= b || N4 - b < c) c = f(c);
      //   ll d = K + 1;
      //   if (b == 0 || d <= b || N4 - b < d) d = f(d);
      //   debug(c, d);
      //   //
      //   if (b == 0 || K <= b + 1 || N - b < K) {
      //     if (K % 2 == 0) {
      //       ans = d;
      //     } else {
      //       ans = c;
      //     }
      //   }
      // }

      // // debug(a, b);

      // debug(ans, tmp);
      // assert(ans == tmp);
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