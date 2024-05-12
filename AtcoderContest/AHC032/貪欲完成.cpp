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
#include <atcoder/all>
using namespace atcoder;
using namespace chrono;
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

struct Solver {
  void solve() {
    auto startClock = system_clock::now();
    const static double END_TIME = 1.95;  // 終了時間（秒）
    double time = 0.0;                    // 経過時間（秒）
    /* input */
    INT(N, M, K);
    using mint = modint998244353;
    vector a(N, vector<mint>(N));
    rep(i, N) rep(j, N) {
      INT(hoyo);
      a[i][j] = hoyo;
    }
    vvvi s(M, vvi(3, vi(3)));
    rep(i, M) rep(j, 3) rep(k, 3) cin >> s[i][j][k];

    //
    int L = 0;
    vector<int> m, p, q;

    /* solve */
    ll score = 0;
    rep(i, N) rep(j, N) score += a[i][j].val();
    // debug(score);

    auto calcDiff = [&](int mi, int pi, int qi) {
      ll diff = 0;
      rep(j, 3) rep(k, 3) {
        ll tmp1 = (a[pi + j][qi + k] + s[mi][j][k]).val();
        diff += tmp1 - a[pi + j][qi + k].val();
      }
      return diff;
    };

    auto stamp = [&](int mi, int pi, int qi) {
      rep(j, 3) rep(k, 3) { a[pi + j][qi + k] += s[mi][j][k]; }
      L++, m.push_back(mi), p.push_back(pi), q.push_back(qi);
    };
    ll MOD = 998244353;

    ll epsCorner = 5e7;
    ll epsSide = 5e7;
    ll epsCenter = 5e7;

    // pi, qiにスタンプを押した時のa[pi+dy][qi+dx]を最大化する
    auto greedyCorner = [&](int pi, int qi, int dy, int dx) {
      vector<pair<ll, int>> vec;
      rep(i, M) vec.emplace_back(s[i][dy][dx], i);
      sort(all(vec));
      ll diff = MOD - a[pi + dy][qi + dx].val();

      for (int i = M - 1; i >= 0; i--) {
        if (L == K) break;
        if (diff < epsCorner || vec[i].first < epsCorner) break;
        if (vec[i].first > diff) continue;
        diff -= vec[i].first;
        stamp(vec[i].second, pi, qi);
      }
    };
    auto greedySide = [&](int pi, int qi, int sy, int sx, int dy, int dx) {
      rep(ki, 100) {
        if (L == K) break;

        // maxdiffを求める
        ll maxdiff = 0;
        int mi = -1;
        rep(i, M) {
          ll diff = 0;
          rep(j, 3) {
            int y = sy + dy * j, x = sx + dx * j;
            ll tmp1 = (a[pi + y][qi + x] + s[i][y][x]).val();
            diff += tmp1 - a[pi + y][qi + x].val();
          }
          if (chmax(maxdiff, diff)) mi = i;
        }
        if (mi == -1) break;
        if (maxdiff < epsSide) break;
        stamp(mi, pi, qi);
      }
    };
    auto greedyCenter = [&]() {
      int pi = 3, qi = 3;

      rep(ki, 100) {
        if (L == K) break;
        ll maxdiff = 0;
        int mi = -1;
        rep(i, M) {
          if (chmax(maxdiff, calcDiff(i, pi, qi))) mi = i;
        }
        if (mi == -1) break;
        if (maxdiff < epsCenter) break;
        stamp(mi, pi, qi);
      }
    };

    auto init = [&]() {
      // 角を詰める
      for (int j = 0; j < 3; j++) greedyCorner(0, j, 0, 0);
      for (int i = 1; i < 3; i++) greedyCorner(i, 0, 0, 0);
      for (int j = 0; j < 3; j++) greedyCorner(0, N - 3 - j, 0, 2);
      for (int i = 1; i < 3; i++) greedyCorner(i, N - 3, 0, 2);
      for (int j = 0; j < 3; j++) greedyCorner(N - 3, j, 2, 0);
      for (int i = 1; i < 3; i++) greedyCorner(N - 3 - i, 0, 2, 0);
      for (int j = 0; j < 3; j++) greedyCorner(N - 3, N - 3 - j, 2, 2);
      for (int i = 1; i < 3; i++) greedyCorner(N - 3 - i, N - 3, 2, 2);
      //
      for (int j = 1; j < 3; j++) greedyCorner(1, j, 0, 0);
      for (int i = 2; i < 3; i++) greedyCorner(i, 1, 0, 0);
      for (int j = 1; j < 3; j++) greedyCorner(1, N - 3 - j, 0, 2);
      for (int i = 2; i < 3; i++) greedyCorner(i, N - 4, 0, 2);
      for (int j = 1; j < 3; j++) greedyCorner(N - 4, j, 2, 0);
      for (int i = 2; i < 3; i++) greedyCorner(N - 3 - i, 1, 2, 0);
      for (int j = 1; j < 3; j++) greedyCorner(N - 4, N - 3 - j, 2, 2);
      for (int i = 2; i < 3; i++) greedyCorner(N - 3 - i, N - 4, 2, 2);
      //
      greedyCorner(2, 2, 0, 0);
      greedyCorner(2, N - 5, 0, 2);
      greedyCorner(N - 5, 2, 2, 0);
      greedyCorner(N - 5, N - 5, 2, 2);

      // debug(L);
      // 辺を詰める
      greedySide(0, 3, 0, 0, 0, 1);
      greedySide(3, 0, 0, 0, 1, 0);
      greedySide(6, 3, 2, 0, 0, 1);
      greedySide(3, 6, 0, 2, 1, 0);
      //
      greedySide(1, 3, 0, 0, 0, 1);
      greedySide(3, 1, 0, 0, 1, 0);
      greedySide(5, 3, 2, 0, 0, 1);
      greedySide(3, 5, 0, 2, 1, 0);
      //
      greedySide(2, 3, 0, 0, 0, 1);
      greedySide(3, 2, 0, 0, 1, 0);
      greedySide(4, 3, 2, 0, 0, 1);
      greedySide(3, 4, 0, 2, 1, 0);
      //
      greedyCenter();

      score = 0;
      rep(i, N) rep(j, N) score += a[i][j].val();
      rep(i, 50000) {
        if (L == K) break;

        // 全探索してもよくない？
        int mi = randXor() % M;
        int pi = randXor() % (N - 4) + 1;
        int qi = randXor() % (N - 4) + 1;

        ll diff = calcDiff(mi, pi, qi);
        if (diff > 0) {
          score += diff;  // for debug
          stamp(mi, pi, qi);
        }
      }
      // 全範囲で山登り
      rep(i, 50000) {
        if (L == K) break;

        // 全探索してもよくない？
        int mi = randXor() % M;
        int pi = randXor() % (N - 2);
        int qi = randXor() % (N - 2);

        ll diff = calcDiff(mi, pi, qi);
        if (diff > 0) {
          score += diff;  // for debug
          stamp(mi, pi, qi);
        }
      }
    };
    init();
    cerr << score << endl;

    //   // 時間更新
    //   time =
    //       ((double)duration_cast<microseconds>(system_clock::now() -
    //       startClock)
    //            .count() *
    //        1e-6);
    // } while (time < END_TIME);

    /* output */
    out(L);
    rep(i, L) out(m[i], p[i], q[i]);
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