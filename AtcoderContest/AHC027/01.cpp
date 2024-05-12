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

int N;

class Cell {
 public:
  // 壁がなければtrue
  bool up, down, right, left;
  // 汚れやすさ
  int d;
  // 到達したターン数
  vector<int> visitedVec;

  Cell() { up = down = right = left = false; }

  void debugPrint() {
    debug(up, down, right, left, d);
    debug(visitedVec);
  }
};
using Cells = vector<vector<Cell>>;
using Path = vector<pair<int, int>>;

string path2str(Path& path) {
  string ret;
  rep(i, (int)path.size() - 1) {
    if (path[i + 1].first - path[i].first == 1) {
      ret.push_back('D');
    } else if (path[i + 1].first - path[i].first == -1) {
      ret.push_back('U');
    } else if (path[i + 1].second - path[i].second == 1) {
      ret.push_back('R');
    } else if (path[i + 1].second - path[i].second == -1) {
      ret.push_back('L');
    } else {
      // 連続して同じ位置にいるやつはDFSのゴミなので捨てる
    }
  }
  return ret;
}

Path initDfs(Cells& cells) {
  // 愚直にdfsをする
  Path ret;
  vector visited(N, vi(N));

  auto dfs = [&](auto rec, int y = 0, int x = 0) -> bool {
    debug(y, x);
    int isMove = false;
    auto f = [&](int dy, int dx) {
      isMove = true;
      ret.emplace_back(y + dy, x + dx);
      visited[y + dy][x + dx] = true;
      rec(rec, y + dy, x + dx);
      ret.emplace_back(y, x);
    };
    if (cells[y][x].up && !visited[y - 1][x]) f(-1, 0);
    if (cells[y][x].down && !visited[y + 1][x]) f(1, 0);
    if (cells[y][x].left && !visited[y][x - 1]) f(0, -1);
    if (cells[y][x].right && !visited[y][x + 1]) f(0, 1);
    return isMove;
  };
  ret.emplace_back(0, 0);
  visited[0][0] = true;
  dfs(dfs);
  ret.emplace_back(0, 0);
  return ret;
}

int main() {
  // input
  cin >> N;
  VEC(string, H, N - 1);
  VEC(string, V, N);
  vector D(N, vi(N));
  rep(i, N) rep(j, N) cin >> D[i][j];
  // build
  Cells cells(N, vector<Cell>(N));
  rep(i, N - 1) rep(j, N) {
    if (H[i][j] == '0') cells[i][j].down = true, cells[i + 1][j].up = true;
  }
  rep(i, N) rep(j, N - 1) {
    if (V[i][j] == '0') cells[i][j].right = true, cells[i][j + 1].left = true;
  }
  rep(i, N) rep(j, N) cells[i][j].d = D[i][j];
  rep(i, N) rep(j, N) debug(i, j), cells[i][j].debugPrint();
  // init
  Path path = initDfs(cells);
  rep(i, (int)path.size()) debug(i, path[i]);
  string ans = path2str(path);
  // 改善パート

  // output
  out(ans);
}