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
    INT(N);
    INT(MG);
    vvi G(N, vi(N));
    vvi H(N, vi(N));
    rep(i, MG) {
      INT(v, u);
      v--, u--;
      G[v][u] = G[u][v] = 1;
    }

    INT(MH);
    rep(i, MH) {
      INT(v, u);
      v--, u--;
      H[v][u] = H[u][v] = 1;
    }

    vvi A(N, vi(N));
    rep(i, N - 1) {
      rep(j, N - 1 - i) { cin >> A[i][j + i + 1]; }
    }

    debug(A);

    /* solve */
    int len = N * (N - 1) / 2;
    vector<pair<int, int>> toEdge;
    rep(i, N) rep(j, i) { toEdge.emplace_back(j, i); }
    debug(toEdge);

    int ans = 1e9;

    set<pair<int, int>> stG;

    rep(i, N) rep(j, i) {
      if (G[j][i]) stG.insert(make_pair(j, i));
    }

    vi perm(N);
    iota(all(perm), 0);

    do {
      int cost = 0;

      rep(i, N) rep(j, i) {
        int v = min(perm[i], perm[j]);
        int u = max(perm[i], perm[j]);

        if ((H[j][i] && !G[v][u]) || (!H[j][i] && G[v][u])) {
          cost += A[j][i];
        }
      }
      chmin(ans, cost);

    } while (next_permutation(all(perm)));

    // auto f = [&](vvi& H2) {
    //   vi perm(N);
    //   iota(all(perm), 0);
    //   do {
    //     set<pair<int, int>> stH;
    //     rep(i, N) rep(j, i) {
    //       int v = min(perm[i], perm[j]);
    //       int u = max(perm[i], perm[j]);
    //       if (H2[v][u]) stH.insert(make_pair(v, u));
    //     }
    //     if (stG == stH) return true;
    //     //
    //   } while (next_permutation(all(perm)));

    //   return false;
    // };

    // debug(len);
    // rep(bit, 1 << len) {
    //   vvi H2 = H;
    //   int cost = 0;
    //   // debug(bit);
    //   rep(i, len) {
    //     if ((bit >> i) & 1) {
    //       int v = toEdge[i].first, u = toEdge[i].second;
    //       H2[v][u] ^= 1;
    //       H2[u][v] ^= 1;
    //       cost += A[v][u];
    //     }
    //   }
    //   if (ans <= cost) continue;
    //   if (f(H2)) ans = cost;
    //   // debug(bit, cost, G2);
    // }

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