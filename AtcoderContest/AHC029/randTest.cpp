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

static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

double gauss(double mu, double sigma) {
  // Box-Muller変換を使用
  double u1 = static_cast<double>(randXor()) / UINT32_MAX;
  double u2 = static_cast<double>(randXor()) / UINT32_MAX;
  double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
  return mu + sigma * z0;
}

int randP0(int L2, int w) {
  double w_ = (double)w / L2;
  int tmp = (int)gauss(w_, w_ / 3);
  return clamp(tmp, 1, 10000) * L2;
}
int randP1(int L2, int w) {
  double w_ = (double)w / L2;
  int tmp = (int)gauss(w_, w_ / 3) * L2;
  return clamp(tmp, 1, 10000) * L2;
}
int randP2(int L2) { return randXor() % 11 * L2; }
int randP3(int L2) { return randXor() % 11 * L2; }
int randP4(int L2) { return (randXor() % 801 + 200) * L2; }
int randW(int L2) { return (randXor() % 50 + 1) * L2; }

pair<int, int> randP(int j, int L2) {
  if (j == 0) {
    int w = randW(L2);
    return make_pair(randP0(L2, w), w);
  }
  if (j == 1) {
    int w = randW(L2);
    return make_pair(randP1(L2, w), w);
  }
  if (j == 2) return make_pair(randP2(L2), 0);
  if (j == 3) return make_pair(randP3(L2), 0);
  if (j == 4) return make_pair(randP4(L2), 0);
  return make_pair(-1, -1);
}

pair<int, int> randProject(int L2) {
  double tmp = static_cast<double>(randXor()) / UINT32_MAX;
  double b = 2.0 + tmp * 6.0;
  int h = (1 << (int)b) * L2;
  int v = (int)pow(2, clamp(gauss(b, 0.5), 0.0, 10.0)) * L2;
  return make_pair(h, v);
}

int main() {
  int L = 0;
  int L2 = 1 << L;
  rep(i, 10) {
    int w = randW(L2);
    int p0 = randP0(L2, w);
    int p1 = randP1(L2, w);
    int p2 = randP2(L2);
    int p3 = randP3(L2);
    int p4 = randP4(L2);
    pair<int, int> project = randProject(L2);
    out(w, p0, p1, p2, p3, p4, project);
  }
  vi xs(5);
  xs[0] = 10, xs[1] = 5, xs[2] = 5, xs[3] = 3, xs[4] = 2;
  vi xsSum(5);
  xs[0] = 10, xs[1] = 15, xs[2] = 20, xs[3] = 23, xs[4] = 25;
  int M = 5;

  rep(k, 10) {
    vi t(M), w(M), p(M);

    rep(i, M) {
      if (i == 0) {
        t[0] = 0;
        w[0] = 1 << L;
        p[0] = 0;
        continue;
      }
      int num = randXor() % xs[4];
      rep(j, 5) {
        if (num < xs[j]) {
          auto [a, b] = randP(j, 1 << L);
          t[i] = j;
          p[i] = a;
          w[i] = b;
          break;
        }
      }
    }
  }

  return 0;
}