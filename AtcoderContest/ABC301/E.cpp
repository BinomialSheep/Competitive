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
    INT(H, W, T);
    VEC(string, A, H);

    debug(A);

    /* solve */
    using P = pair<int, int>;
    P start, goal;
    vector<P> okashiVec;
    rep(i, H) rep(j, W) {
      if (A[i][j] == 'S') start = make_pair(i, j);
      if (A[i][j] == 'G') goal = make_pair(i, j);
      if (A[i][j] == 'o') okashiVec.emplace_back(i, j);
    }
    // debug(start, goal, okashiVec);

    vi dy = {0, 0, 1, -1};
    vi dx = {1, -1, 0, 0};
    auto bfs = [&](P s, P g) -> int {
      vvi dist(H, vi(W, INFTY));
      // debug(H, W);
      dist[s.first][s.second] = 0;

      queue<P> q;
      q.push(s);
      while (q.size()) {
        auto [y, x] = q.front();
        q.pop();

        rep(i, 4) {
          int ny = y + dy[i], nx = x + dx[i];
          if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
          // debug(ny, nx);
          if (A[ny][nx] == '#') continue;
          if (dist[ny][nx] <= dist[y][x] + 1) continue;

          q.emplace(ny, nx);
          dist[ny][nx] = dist[y][x] + 1;
        }
      }
      return dist[g.first][g.second];
    };
    int sz = okashiVec.size() + 2;
    okashiVec.push_back(start);
    okashiVec.push_back(goal);
    // debug(okashiVec);
    vvi G(sz, vi(sz));
    rep(i, sz) rep(j, sz) {
      if (i == j) continue;
      // if (j < i) G[j][i] = G[i][j];
      G[i][j] = bfs(okashiVec[i], okashiVec[j]);
    }
    // debug(G);
    sz = okashiVec.size() - 2;
    vvi dist(okashiVec.size(), vi(1 << sz, INFTY));
    // debug(dist[0].size());

    queue<pair<int, int>> q;
    q.emplace(0, okashiVec.size() - 2);
    dist[okashiVec.size() - 2][0] = 0;
    while (q.size()) {
      auto [bit, idx] = q.front();
      // debug(dist[idx][bit]);
      q.pop();
      rep(i, okashiVec.size()) {
        if (idx == i) continue;
        if (G[idx][i] == INFTY) continue;
        int nxt = bit;
        if (i < okashiVec.size() - 2) nxt |= (1 << i);
        // debug(nxt, idx, i, bit, dist[idx][bit], G[idx][i]);
        if (dist[idx][bit] + G[idx][i] > T) continue;
        if (chmin(dist[i][nxt], dist[idx][bit] + G[idx][i])) q.emplace(nxt, i);
      }
    }

    int ans = -1;
    rep(bit, 1 << sz) {
      if (dist[okashiVec.size() - 1][bit] != INFTY) {
        chmax(ans, __builtin_popcountll(bit));
      }
    }
    out(ans);

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