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

int N = 6, M = 15, T = 10;
int NN = 36;
int RAWS = 2 * N * (N - 1);

int main() {
  {
    int n, m, t;
    cin >> n >> m >> t;
  }
  vvi x(RAWS, vi(M));
  rep(i, RAWS) rep(j, M) cin >> x[i][j];

  rep(ti, T) {
    vvi A(N, vi(N));

    // 各評価項目の最大値
    vi maxM(M);
    rep(i, RAWS) rep(j, M) chmax(maxM[j], x[i][j]);
    // 各種の価値
    vector<pair<int, int>> sumX(RAWS);
    rep(i, RAWS) {
      sumX[i].second = i;
      rep(j, M) sumX[i].first += x[i][j];
    }
    debug(maxM);
    debug(sumX);

    // N^2個選定する
    vi top36(NN);
    // 単に合計値で選定
    sort(sumX.rbegin(), sumX.rend());
    rep(i, NN) top36[i] = sumX[i].second;
    debug(top36);

    // 配置する
    int idx = 0;
    rep(i, 4) rep(j, 4) A[i + 1][j + 1] = top36[idx++];
    rep(j, 4) A[0][1 + j] = top36[idx++], A[5][1 + j] = top36[idx++];
    rep(i, 4) A[1 + i][0] = top36[idx++], A[1 + i][5] = top36[idx++];
    A[0][0] = top36[idx++], A[0][5] = top36[idx++], A[5][0] = top36[idx++],
    A[5][5] = top36[idx++];
    debug(A);

    // 出力
    rep(i, N) {
      rep(j, N) { cout << A[i][j] << ((j < N - 1) ? " " : "\n"); }
    }
    cout << flush;

#ifdef LOCAL
    vector<vector<string>> u(N, vs(N - 1));
    rep(i, N) rep(j, N - 1) cin >> u[i][j];
    vector<vector<string>> v(N - 1, vs(N));
    rep(i, N - 1) rep(j, N) cin >> v[i][j];
    vvi x2;
    rep(i, N) rep(j, N - 1) {
      vi next(M);
      rep(l, M) {
        if (u[i][j][l] == '1') {
          next[l] = x[A[i][j]][l];
        } else {
          next[l] = x[A[i][j + 1]][l];
        }
      }
      x2.push_back(next);
    }
    rep(i, N - 1) rep(j, N) {
      vi next(M);
      rep(l, M) {
        if (v[i][j][l] == '1') {
          next[l] = x[A[i][j]][l];
        } else {
          next[l] = x[A[i + 1][j]][l];
        }
      }
      x2.push_back(next);
    }
    swap(x, x2);
#else
    // 入力を再度受け取る
    rep(i, RAWS) rep(j, M) cin >> x[i][j];
#endif
  }
}