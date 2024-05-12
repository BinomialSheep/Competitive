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
    INT(N, M, K);
    vpii A, B;
    rep(i, N) {
      INT(a, b);
      A.emplace_back(a, b);
    }
    rep(i, M) {
      INT(a, b);
      B.emplace_back(a, b);
    }

    /* solve */

    auto g = [](double mid, int x1, int x2, int y1, int y2) {
      double tmp = 100 * (x1 + x2) / (double)(x1 + x2 + y1 + y2);
      debug(mid, tmp);
      return mid <= tmp;
    };

    auto f = [&](double mid) {
      int cnt = 0;
      // vector<pair<double, pii>> C, D;
      // rep(i, N) C.emplace_back(
      //     100 * A[i].first - mid * A[i].second - mid * A[i].second, A[i]);
      // rep(i, M) D.emplace_back(
      //     100 * B[i].first - mid * B[i].second - mid * B[i].second, B[i]);
      // sort(all(D));
      // // debug(C, D);

      // rep(i, N) {
      //   int x1 = C[i].second.first;
      //   int y1 = C[i].second.second;
      //   if (!g(mid, x1, D[M - 1].second.first, y1, D[M - 1].second.second)) {
      //     continue;
      //   }
      //   if (g(mid, x1, D[0].second.first, y1, D[0].second.second)) {
      //     cnt += M;
      //     continue;
      //   }
      //   int ng = 0, ok = M - 1;
      //   int wj;
      //   while (ok - ng > 1) {
      //     wj = (ok + ng) / 2;
      //     auto [x2, y2] = D[wj].second;
      //     if (g(mid, x1, x2, y1, y2)) {
      //       ok = wj;
      //     } else {
      //       ng = wj;
      //     }
      //   }
      //   cnt += M - ng - 1;
      // }

      // tmp
      rep(i, N) rep(j, M) {
        int x1 = A[i].first;
        int x2 = B[j].first;
        int y1 = A[i].second;
        int y2 = B[j].second;
        double tmp = 100 * (x1 + x2) / (double)(x1 + x2 + y1 + y2);
        if (mid <= tmp) cnt++;
      }
      // debug(mid, cnt);

      return cnt >= K;
    };

    double ok = 0, ng = 101;
    rep(ri, 100) {
      double mid = (ok + ng) / 2;

      if (f(mid)) {
        ok = mid;
      } else {
        ng = mid;
      }
    }

    cout.precision(20);
    cout << fixed << ok << endl;

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