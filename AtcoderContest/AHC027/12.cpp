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

using namespace chrono;
// 0以上UINT_MAX(0xffffffff)以下の整数をとる乱数 xorshift
// https://ja.wikipedia.org/wiki/Xorshift
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

const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;

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
      // 連続して同じ位置にいるやつはDFSのゴミ
      debug(i, path[i]);
      debug(path);
      debug(ret);
      assert(false);
    }
  }
  return ret;
}

void makeVisitedVec(Cells& cells, Path& path) {
  rep(i, N) rep(j, N) cells[i][j].visitedVec.clear();
  rep(i, path.size()) {
    cells[path[i].first][path[i].second].visitedVec.push_back(i);
  }
  cells[0][0].visitedVec.pop_back();  // 最後のゴール到達は無視
}

ll calcScore(Cells& cells, ll L, int final = 1) {
  ll ret = 0;
  auto f = [](ll d, ll dist) -> ll { return dist * (dist + 1) / 2 * d; };

  rep(i, N) rep(j, N) {
    vi& vec = cells[i][j].visitedVec;
    ll d = cells[i][j].d;
    ll now = 0;
    rep(k, (int)vec.size() - 1) { now += f(d, vec[k + 1] - vec[k] - 1); }
    if ((int)vec.size() == 1) {
      now += f(d, L - 1);
    } else if (vec.empty()) {
      if (final) {
        debug(i, j);
        cells[i][j].debugPrint();
        // rep(i2, N) rep(j2, N) cells[i2][j2].debugPrint();
        assert(false);
      } else {
        // プレイアウト中の計算は、全頂点到達済みとは限らないのでよい
      }
    } else {
      now += f(d, L - 1 - vec.back() + vec[0]);
    }
    ret += now;
  }
  return ret / L;
}

void pushBackCell(Cells& cells, Path& path, vvi& visited, int y, int x) {
  cells[y][x].visitedVec.push_back((int)path.size());
  visited[y][x] = true;
  path.emplace_back(y, x);
}

// (y, x)と(y2, x2)は隣接しているか
bool isAdjacent(int y, int x, int y2, int x2, Cells& cells) {
  if (y - 1 == y2 && x == x2 && cells[y][x].up) return true;
  if (y + 1 == y2 && x == x2 && cells[y][x].down) return true;
  if (y == y2 && x - 1 == x2 && cells[y][x].left) return true;
  if (y == y2 && x + 1 == x2 && cells[y][x].right) return true;
  return false;
}

pair<int, int> connectPath(int y, int x, int ny, int nx, Cells& cells,
                           vvi& visited, Path& path) {
  pair<int, int> ret = {-1, -1};
  // unimplemented：使いまわせば高速だが速度に困ってない
  vector dist(N, vi(N, 1e9));
  dist[y][x] = 0;
  queue<pair<int, int>> q;
  q.emplace(y, x);
  while (q.size()) {
    auto [y2, x2] = q.front();
    q.pop();
    int nc = dist[y2][x2] + 1;

    if (cells[y2][x2].up && chmin(dist[y2 - 1][x2], nc)) {
      if (y2 - 1 == ny && x2 == nx) break;
      q.emplace(y2 - 1, x2);
    }
    if (cells[y2][x2].down && chmin(dist[y2 + 1][x2], nc)) {
      if (y2 + 1 == ny && x2 == nx) break;
      q.emplace(y2 + 1, x2);
    }
    if (cells[y2][x2].left && chmin(dist[y2][x2 - 1], nc)) {
      if (y2 == ny && x2 - 1 == nx) break;
      q.emplace(y2, x2 - 1);
    }
    if (cells[y2][x2].right && chmin(dist[y2][x2 + 1], nc)) {
      if (y2 == ny && x2 + 1 == nx) break;
      q.emplace(y2, x2 + 1);
    }
  }

  stack<pair<int, int>> homePathStk;
  while (ny != y || nx != x) {
    homePathStk.emplace(ny, nx);
    // まだ通ってなくて汚いところを通りたい
    vector<pair<int, int>> vec;
    auto f = [&](int ny2, int nx2) -> int {
      if (!visited[ny2][nx2]) return cells[ny2][nx2].d + 2e7 + 9;
      return ((int)path.size() - cells[ny2][nx2].visitedVec.back()) *
             cells[ny2][nx2].d;
    };

    if (cells[ny][nx].up && dist[ny - 1][nx] == dist[ny][nx] - 1) {
      vec.emplace_back(f(ny - 1, nx), UP);
    }
    if (cells[ny][nx].down && dist[ny + 1][nx] == dist[ny][nx] - 1) {
      vec.emplace_back(f(ny + 1, nx), DOWN);
    }
    if (cells[ny][nx].left && dist[ny][nx - 1] == dist[ny][nx] - 1) {
      vec.emplace_back(f(ny, nx - 1), LEFT);
    }
    if (cells[ny][nx].right && dist[ny][nx + 1] == dist[ny][nx] - 1) {
      vec.emplace_back(f(ny, nx + 1), RIGHT);
    }
    auto p = *max_element(all(vec));
    // 未訪問頂点と繋がっているならそこから探索を開始する
    if (cells[ny][nx].up && !visited[ny - 1][nx]) ret = make_pair(ny, nx);
    if (cells[ny][nx].down && !visited[ny + 1][nx]) ret = make_pair(ny, nx);
    if (cells[ny][nx].left && !visited[ny][nx - 1]) ret = make_pair(ny, nx);
    if (cells[ny][nx].right && !visited[ny][nx + 1]) ret = make_pair(ny, nx);
    // 更新
    if (p.second == UP) ny--;
    if (p.second == DOWN) ny++;
    if (p.second == LEFT) nx--;
    if (p.second == RIGHT) nx++;
  }

  while (homePathStk.size()) {
    auto [y2, x2] = homePathStk.top();
    homePathStk.pop();
    if (y2 == ret.first && x2 == ret.second) break;
    pushBackCell(cells, path, visited, y2, x2);
  }
  return ret;
}

// DFSをしない
Path init3(Cells& cells) {
  Path path;
  vector visited(N, vi(N));
  vvi searchNow(N, vi(N));

  stack<pair<int, int>> stk;
  stk.emplace(0, 0);
  while (stk.size()) {
    // 取り出し
    auto [y, x] = stk.top();
    stk.pop();
    if (visited[y][x]) continue;
    // 直前の頂点と繋げる
    if (path.size() &&
        !isAdjacent(y, x, path.back().first, path.back().second, cells)) {
      auto res = connectPath(path.back().first, path.back().second, y, x, cells,
                             visited, path);
      if (res.first != -1) {
        // 途中で未探索頂点が見つかったら、そこから始める
        stk.emplace(y, x);
        y = res.first, x = res.second;
      }
    }

    pushBackCell(cells, path, visited, y, x);

    // 探索が必要な個所を列挙
    vector<int> explorable;
    if (cells[y][x].up && !visited[y - 1][x]) explorable.push_back(UP);
    if (cells[y][x].down && !visited[y + 1][x]) explorable.push_back(DOWN);
    if (cells[y][x].left && !visited[y][x - 1]) explorable.push_back(LEFT);
    if (cells[y][x].right && !visited[y][x + 1]) explorable.push_back(RIGHT);

    if (explorable.size()) {
      // TODO：優先度を決定する
      for (auto d : explorable) {
        if (d == UP) stk.emplace(y - 1, x);
        if (d == DOWN) stk.emplace(y + 1, x);
        if (d == LEFT) stk.emplace(y, x - 1);
        if (d == RIGHT) stk.emplace(y, x + 1);
      }
    }
  }
  // 最後に0に戻る
  if (path.back().first != 0 || path.back().second != 0) {
    connectPath(path.back().first, path.back().second, 0, 0, cells, visited,
                path);
  }

  // cells[0][0].visitedVec.pop_back();
  // debug用
  // rep(i, N) rep(j, N) {
  //   if (!visited[i][j]) {
  //     debug(i, j);
  //     debug(visited);
  //     debug(path);
  //     debug(path2str(path));
  //     assert(false);
  //   }
  // }

  return path;
}

bool addNeighbor(Cells& cells, Path& path, ll& bestScore) {
  int i;
  int y, x;
  int direct;
  int flag = 0;
  rep(ni2, 10) {
    i = randXor() % (int)path.size();
    y = path[i].first, x = path[i].second;
    direct = randXor() % 4;
    if (direct == 0 && cells[y][x].up) {
      flag = 1;
      break;
    }
    if (direct == 1 && cells[y][x].down) {
      flag = 1;
      break;
    }
    if (direct == 2 && cells[y][x].right) {
      flag = 1;
      break;
    }
    if (direct == 3 && cells[y][x].left) {
      flag = 1;
      break;
    }
  }
  if (!flag) return false;

  Path prevPath = path;
  Cells prevCells = cells;

  if (direct == 0 && cells[y][x].up) {
    path.insert(path.begin() + i + 1, make_pair(y - 1, x));
  } else if (direct == 1 && cells[y][x].down) {
    path.insert(path.begin() + i + 1, make_pair(y + 1, x));
  } else if (direct == 2 && cells[y][x].right) {
    path.insert(path.begin() + i + 1, make_pair(y, x + 1));
  } else if (direct == 3 && cells[y][x].left) {
    path.insert(path.begin() + i + 1, make_pair(y, x - 1));
  }
  path.insert(path.begin() + i + 2, make_pair(y, x));

  makeVisitedVec(cells, path);
  ll nowScore = calcScore(cells, (int)path.size() - 1);
  // ダメなら戻す
  if (bestScore < nowScore) {
    path = prevPath, cells = prevCells;
  } else {
    bestScore = nowScore;
    return true;
  }
  return false;
}

int main() {
  // input
  cin >> N;
  VEC(string, H, N - 1);
  VEC(string, V, N);
  vector D(N, vi(N));
  rep(i, N) rep(j, N) cin >> D[i][j];

  // auto startClock = system_clock::now();
  // // const static double START_TEMP = 1e4;    // 開始時の温度
  // // const static double END_TEMP = 1e2;      // 終了時の温度
  // const static double END_TIME = 1.8;  // 終了時間（秒）
  // double time = 0.0;                   // 経過時間（秒）

  // build
  Cells cells(N, vector<Cell>(N));
  rep(i, N - 1) rep(j, N) {
    if (H[i][j] == '0') cells[i][j].down = true, cells[i + 1][j].up = true;
  }
  rep(i, N) rep(j, N - 1) {
    if (V[i][j] == '0') cells[i][j].right = true, cells[i][j + 1].left = true;
  }
  rep(i, N) rep(j, N) cells[i][j].d = D[i][j];
  // init
  Path path = init3(cells);

  // debug(path);
  // debug(path2str(path));

  // 追加近傍のテスト

  // output
  string ans = path2str(path);
  // debug((int)ans.size());
  // debug(calcScore(cells, (int)ans.size()));
  cerr << calcScore(cells, (int)ans.size()) << endl;
  out(ans);
}
