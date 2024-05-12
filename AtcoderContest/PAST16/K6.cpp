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

int main() {
  /* input */
  INT(N);
  VEC(string, S, N);

  auto p2i = [](pair<int, int> p) { return p.first * 2000 + p.second; };
  auto i2p = [](int yx) { return make_pair(yx / 2000, yx % 2000); };

  int start;
  unordered_set<int> goal;
  rep(i, N) rep(j, N) {
    if (S[i][j] == 'S') start = 2000 * i + j;
    if (S[i][j] == 'G') goal.emplace(i * 2000 + j);
  }

  vvi col(N, vi(N)), row(N, vi(N));
  rep(i, N) rep(j, N) {
    if (S[i][j] == 'X') {
      row[i][j]++;
      col[i][j]++;
    }
    if (j) row[i][j] += row[i][j - 1];
    if (i) col[i][j] += col[i - 1][j];
  }
  // debug(row, col);

  const int INF = 1e9;
  vi ans(N - 1, INF);
  /* solve */
  vi dy = {0, 0, 1, -1};
  vi dx = {1, -1, 0, 0};

  rep(i, N) {
    if (!i) continue;
    queue<int> q;
    int endy = -1, endx = -1;
    q.push(start);
    unordered_map<int, int> mp;
    mp[start] = 0;
    while (q.size()) {
      auto p = q.front();
      q.pop();
      // debug(p, mp[p]);
      auto [y, x] = i2p(p);
      int d = mp[p];
      rep(j, 4) {
        int y2 = y + dy[j] * i, x2 = x + dx[j] * i;
        int p2 = y2 * 2000 + x2;
        if (y2 < 0 || y2 >= N || x2 < 0 || x2 >= N) continue;
        if (S[y2][x2] == 'X') continue;
        if (mp.count(p2)) continue;
        // 間に障害物がないことを確かめる
        int flag = 1;
        if (x2 != x && row[y][x] != row[y2][x2]) flag = 0;
        if (y2 != y && col[y][x] != col[y2][x2]) flag = 0;
        if (flag) {
          mp[p2] = d + 1, q.push(p2);
          if (goal.count(p2)) {
            endy = y2, endx = x2;
            break;
          }
        }
      }
      if (endy != -1) break;
    }
    if (endy != -1) ans[i - 1] = mp[endy * 2000 + endx];
  }
  rep(i, N - 1) if (ans[i] == INF) ans[i] = -1;
  out(ans);
}