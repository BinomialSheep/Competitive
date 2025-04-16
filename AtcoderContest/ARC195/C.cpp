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
    INT(T);
    rep(ti, T) {
      /* input */
      INT(R, B);
      /* solve */
      // Rはo->x, x->o
      // Bはo->o, x->x
      vector<char> p;
      vector<int> r, c;

      auto print = [&]() {
        out("Yes");
        rep(i, p.size()) {
          cout << p[i] << " " << r[i] + 1000000 << " " << c[i] + 1000000
               << endl;
        }
      };

      int ny = 0, nx = 0;
      auto pb = [&](int y, int x) {
        p.push_back('B');
        r.push_back(y);
        c.push_back(x);
        ny = y, nx = x;
      };
      auto pr = [&](int y, int x) {
        p.push_back('R');
        r.push_back(y);
        c.push_back(x);
        ny = y, nx = x;
      };

      // 一般性を失わず、最初にoに置く
      // Rが偶数であることは必要条件
      if (R % 2) {
        out("No");
        continue;
      }
      if (B == 0) {
        // 0, 0のまま
      } else {
        pb(0, 0);
        if (B == 2) {
          pb(1, 1);
        } else if (B >= 3) {
          int b = B - 1;
          // 右上に進む
          rep(i, b / 2) { pb(ny - 1, nx + 1); }
          b -= b / 2;
          pb(ny + 1, nx + 1);
          b--;
          rep(i, b) { pb(ny + 1, nx - 1); }
        }
      }
      // debug(ti, R, B, ny, nx);
      // debug(p, r, c);
      if (B <= 1) {
        assert(ny == 0 && nx == 0);
      } else if (B % 2) {
        assert(ny == 0 && nx == 2);
      } else {
        assert(ny == 1 && nx == 1);
      }
      if (R == 0) {
        if (ny == 1 && nx == 1) {
          print();
        } else {
          out("No");
        }
        continue;
      }
      int nowR = R;

      if (ny == 1 && nx == 1) {
        pr(2, 0);
        nowR--;
      } else if (B == 0) {
        pr(0, 0);
        nowR--;
      } else {
        pr(1, 1);
        nowR--;
      }
      pr(1, 0);
      nowR--;
      if (nowR == 0) {
        print();
        continue;
      }

      // debug(R, nowR, ny, nx);
      rep(i, nowR / 2) pr(ny, nx - 1);
      // debug(R, ny, nx);
      nowR /= 2;
      pr(ny - 1, nx);
      // debug(R, ny, nx);
      nowR--;
      rep(i, nowR) pr(ny, nx + 1);
      // debug(R, ny, nx);

      // assert(ny == 0 && nx == -1);

      print();

      /* output */
    }
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