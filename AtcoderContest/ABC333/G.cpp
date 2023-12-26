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

ll N;

// 許容誤差（小さくすると精度向上）
#define ZERO 1e-06

// 近似分数の最大計算回数（これを超えたら計算中断）
#define MAX_CALC_NUM_FOR_APPROX_FRAC 100

// 最大公約数を求める
long gcd(long a, long b) { return b == 0 ? a : gcd(b, a % b); }

// 分数（p／q）
typedef struct {
  unsigned long p, q;
} Frac;

// 既約分数を作る
Frac reg_frac(Frac frac) {
  Frac ret = frac;
  long g = gcd(ret.p, ret.q);
  ret.p /= g;
  ret.q /= g;
  return ret;
}

// 分母分子の値から分数を生成
Frac new_frac(unsigned long p, unsigned long q) {
  Frac ret;
  ret.p = p;
  ret.q = q;
  ret = reg_frac(ret);
  return ret;
}

// 分数の足し算
Frac add_frac(Frac frac1, Frac frac2) {
  return new_frac(frac1.p * frac2.q + frac1.q * frac2.p, frac1.q * frac2.q);
}

// 逆数
Frac reverse_frac(Frac frac) { return new_frac(frac.q, frac.p); }

// 連分数展開の計算回数
static long approx_frac_calc_num = 0;

// 連分数展開を使って近似分数を作る
Frac approx_frac(double x) {
  approx_frac_calc_num++;
  // 許容誤差に収まるか、計算回数が最大になったら終了
  if (fabs(x - ((long)x)) < ZERO ||
      approx_frac_calc_num > MAX_CALC_NUM_FOR_APPROX_FRAC) {
    approx_frac_calc_num = 0;
    return new_frac((long)x, 1);
  }
  Frac tmp = add_frac(new_frac((long)x, 1),
                      reverse_frac(approx_frac(1.0 / (x - (long)x))));

  // debug(approx_frac_calc_num, tmp.p, tmp.q);

  if (tmp.q <= N + 0.000001) return tmp;
  return new_frac((long)x, 1);
}

int main() {
  // 1.16666… を近似分数に変換 7／6が出力される
  double r;
  cin >> r;
  cin >> N;
  Frac a = approx_frac(r);
  double dif1 = double(a.p) / (double)(a.q) - r;
  double l = r - dif1;
  Frac b = approx_frac(l);
  double dif2 = r - double(b.p) / double(b.q);
  debug(a.p, a.q, dif1);
  debug(b.p, b.q, dif2);

  if (abs(dif1 - dif2) < -1e9) {
    out(b.p, b.q);
  } else {
    out(a.p, a.q);
  }
}