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

// 交差判定セット（整数VER）
typedef complex<ll> C;
// 外積
ll cross(C a, C b) { return a.real() * b.imag() - a.imag() * b.real(); }
// 内積
ll dot(C a, C b) { return a.real() * b.real() + a.imag() * b.imag(); }
// a is in b and c ?
bool is_in(C a, C b, C c) {
  if (a == b) return true;
  if (a == c) return true;
  C v0 = b - a;
  C v1 = c - a;
  if (cross(v0, v1) != 0) return false;  // 同一線上にない
  if (dot(v0, v1) < 0) return true;      // 逆向きならin
  return false;
}
// ベクトル p0->p1, q0->q1
bool is_intersect(C p0, C p1, C q0, C q1) {
  {
    // 同じ点があるなら交差
    if (p0 == p1) return true;
    if (p0 == q0) return true;
    if (p0 == q1) return true;
    if (p1 == q0) return true;
    if (p1 == q1) return true;
    if (q0 == q1) return true;
  }

  bool is_parallel = false;
  {
    C v = p0 - p1;
    C w = q0 - q1;
    if (cross(v, w) == 0) is_parallel = true;
  }

  if (is_parallel) {
    // 包含・重なり・ギリギリ接触を交差とする

    if (is_in(p0, q0, q1)) return true;
    if (is_in(p1, q0, q1)) return true;

    if (is_in(q0, p0, p1)) return true;
    if (is_in(q1, p0, p1)) return true;

    return false;
  }

  // 以降、平行ではないとする

  // p側から見た交差チェック
  auto v0 = p1 - p0;
  auto v1 = q0 - p0;
  auto v2 = q1 - p0;
  if (cross(v0, v1) * cross(v0, v2) > 0) {
    return false;
  }
  // q側から見た交差チェック
  v0 = q1 - q0;
  v1 = p0 - q0;
  v2 = p1 - q0;
  if (cross(v0, v1) * cross(v0, v2) > 0) {
    return false;
  }

  return true;
}

struct Solver {
  void solve() {
    /* input */
    INT(a1, b1, c1, d1);
    INT(a2, b2, c2, d2);

    int isYes = 0;
    if (a1 == a2 && b1 == b2) isYes = 1;
    if (a1 == c2 && b1 == d2) isYes = 1;
    if (c1 == a2 && c1 == b2) isYes = 1;
    if (c1 == c2 && d1 == d2) isYes = 1;
    if (isYes) {
      out("Yes");
      return;
    }

    /* solve */

    C p11(a1, b1);
    C p12(c1, d1);
    C p21(a2, b2);
    C p22(c2, d2);
    Yes(is_intersect(p11, p12, p21, p22));
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