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
#pragma endregion header
// #include <atcoder/all>
// using namespace atcoder;

struct Solver {
  void solve() {
    /* input */
    INT(N);
    VEC(int, d, N);
    vector<vpii> G(N);
    rep(i, N - 1) {
      INT(u, v, w);
      --u, --v;
      G[u].emplace_back(v, w);
      G[v].emplace_back(u, w);
    }

    /* solve */
    vvl dp(N, vl(2));
    vi visited(N);

    auto dfs = [&](auto f, int from, int parent = -1) -> void {
      visited[from] = 1;
      // 先に子を計算
      for (auto [to, w] : G[from]) {
        if (visited[to]) continue;
        f(f, to, from);
      }
      ll sum1 = 0;
      vpii ps;
      for (auto [to, w] : G[from]) {
        if (to == parent) continue;
        if (d[to] == 0) {
          sum1 += dp[to][0];
        } else if (w <= dp[to][0] - dp[to][1]) {
          sum1 += dp[to][0];
        } else {
          sum1 += dp[to][1];
          ps.emplace_back(w - (dp[to][0] - dp[to][1]), to);
        }
      }
      sort(ps.rbegin(), ps.rend());
      if (ps.size()) {
        assert(ps.back().first > 0);
      }
      ll diff0 = 0;
      ll diff1 = 0;
      int cnt = 0;
      for (auto [v1, to] : ps) {
        if (cnt < d[from] - 1) {
          auto w = v1 + (dp[to][0] - dp[to][1]);
          assert(w >= 0);
          diff0 += w;
          diff1 += w;
          cnt++;
        } else if (cnt == d[from] - 1) {
          auto w = v1 + (dp[to][0] - dp[to][1]);
          assert(w >= 0);
          diff0 += w;
          diff1 += dp[to][0] - dp[to][1];
          cnt++;
        } else {
          diff0 += dp[to][0] - dp[to][1];
          diff1 += dp[to][0] - dp[to][1];
        }
      }

      assert(diff0 >= 0);
      assert(diff1 >= 0);
      dp[from][0] = sum1 + diff0;
      dp[from][1] = sum1 + diff1;
    };

    dfs(dfs, 0);

    // debug(dp);

    ll ans = max(dp[0][0], dp[0][1]);
    /* output */
    cout << ans << endl;
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