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
set<pair<int, int>> dirtyPoints;

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
  vector dp(N, vi(N));
  dist[y][x] = 0;
  queue<pair<int, int>> q;
  q.emplace(y, x);
  while (q.size()) {
    auto [y2, x2] = q.front();
    q.pop();
    int nc = dist[y2][x2] + 1;
    int now = 1e6;
    if (cells[y2][x2].visitedVec.size()) {
      now = ((int)path.size() + 1 - cells[y2][x2].visitedVec.back()) *
            cells[y2][x2].d;
    }

    if (cells[y2][x2].up && chmin(dist[y2 - 1][x2], nc)) {
      chmax(dp[y2 - 1][x2], dp[y2][x2] + now);
      if (y2 - 1 == ny && x2 == nx) break;
      q.emplace(y2 - 1, x2);
    }
    if (cells[y2][x2].down && chmin(dist[y2 + 1][x2], nc)) {
      chmax(dp[y2 + 1][x2], dp[y2][x2] + now);
      if (y2 + 1 == ny && x2 == nx) break;
      q.emplace(y2 + 1, x2);
    }
    if (cells[y2][x2].left && chmin(dist[y2][x2 - 1], nc)) {
      chmax(dp[y2][x2 - 1], dp[y2][x2] + now);
      if (y2 == ny && x2 - 1 == nx) break;
      q.emplace(y2, x2 - 1);
    }
    if (cells[y2][x2].right && chmin(dist[y2][x2 + 1], nc)) {
      chmax(dp[y2][x2 + 1], dp[y2][x2] + now);
      if (y2 == ny && x2 + 1 == nx) break;
      q.emplace(y2, x2 + 1);
    }
  }

  rep(i, N) rep(j, N) {
    if (cells[i][j].visitedVec.empty()) {
      dp[i][j] += (int)1e6;
    } else {
      dp[i][j] += ((int)path.size() + 1 - cells[i][j].visitedVec.back()) *
                  cells[i][j].d;
    }
  }

  stack<pair<int, int>> homePathStk;
  while (ny != y || nx != x) {
    homePathStk.emplace(ny, nx);
    // まだ通ってなくて汚いところを通りたい
    vector<pair<int, int>> vec;
    auto f = [&](int ny2, int nx2) -> int {
      if (!visited[ny2][nx2]) return cells[ny2][nx2].d + (int)2e7 + 9;
      return ((int)path.size() - cells[ny2][nx2].visitedVec.back()) *
             cells[ny2][nx2].d;
    };

    int now = 1e6;
    if (cells[ny][nx].visitedVec.size()) {
      now = ((int)path.size() + 1 - cells[ny][nx].visitedVec.back()) *
            cells[ny][nx].d;
    }

    if (cells[ny][nx].up && dist[ny - 1][nx] == dist[ny][nx] - 1 &&
        dp[ny - 1][nx] == dp[ny][nx] - now) {
      vec.emplace_back(f(ny - 1, nx), UP);
    }
    if (cells[ny][nx].down && dist[ny + 1][nx] == dist[ny][nx] - 1 &&
        dp[ny + 1][nx] == dp[ny][nx] - now) {
      vec.emplace_back(f(ny + 1, nx), DOWN);
    }
    if (cells[ny][nx].left && dist[ny][nx - 1] == dist[ny][nx] - 1 &&
        dp[ny][nx - 1] == dp[ny][nx] - now) {
      vec.emplace_back(f(ny, nx - 1), LEFT);
    }
    if (cells[ny][nx].right && dist[ny][nx + 1] == dist[ny][nx] - 1 &&
        dp[ny][nx + 1] == dp[ny][nx] - now) {
      vec.emplace_back(f(ny, nx + 1), RIGHT);
    }
    auto p = *max_element(all(vec));
    // 更新
    if (p.second == UP) ny--;
    if (p.second == DOWN) ny++;
    if (p.second == LEFT) nx--;
    if (p.second == RIGHT) nx++;
  }

  while (homePathStk.size()) {
    auto [y2, x2] = homePathStk.top();
    homePathStk.pop();
    pushBackCell(cells, path, visited, y2, x2);
  }
  return ret;
}

void addDirtyPoints(stack<pair<int, int>>& stk, vvi& visited) {
  for (auto [y, x] : dirtyPoints) {
    stk.emplace(y, x);
    visited[y][x] = 0;
  }
}

//
pair<int, int> bfsNearestUnvisited(int y, int x, vvi& visited, Cells& cells) {
  int ny = -1, nx = -1;
  // UF
  dsu uf(N * N);
  rep(i, N) rep(j, N) {
    if (visited[i][j]) continue;
    if (i == y && x == j) continue;
    if (cells[i][j].right && !visited[i][j + 1])
      uf.merge(i * N + j, i * N + j + 1);
    if (cells[i][j].down && !visited[i + 1][j])
      uf.merge(i * N + j, i * N + N + j);
  }

  // BFS
  queue<pair<int, int>> q;
  q.emplace(y, x);
  vvi dist(N, vi(N, 10000));
  dist[y][x] = 0;
  int d = 10000;
  set<pair<int, int>> st;
  while (q.size()) {
    auto [y2, x2] = q.front();
    q.pop();
    int now = dist[y2][x2];
    if (visited[y2][x2] == 0 && (chmin(d, now) || now == d)) {
      st.emplace(y2, x2);
    } else if (now > d) {
      break;
    }
    if (cells[y2][x2].up && chmin(dist[y2 - 1][x2], now + 1))
      q.emplace(y2 - 1, x2);
    if (cells[y2][x2].down && chmin(dist[y2 + 1][x2], now + 1))
      q.emplace(y2 + 1, x2);
    if (cells[y2][x2].left && chmin(dist[y2][x2 - 1], now + 1))
      q.emplace(y2, x2 - 1);
    if (cells[y2][x2].right && chmin(dist[y2][x2 + 1], now + 1))
      q.emplace(y2, x2 + 1);
  }

  // if (d == 1) {
  //   vector<int> explorable;
  //   if (cells[y][x].up && !visited[y - 1][x]) explorable.push_back(UP);
  //   if (cells[y][x].down && !visited[y + 1][x]) explorable.push_back(DOWN);
  //   if (cells[y][x].left && !visited[y][x - 1]) explorable.push_back(LEFT);
  //   if (cells[y][x].right && !visited[y][x + 1]) explorable.push_back(RIGHT);
  //   // 横移動が大抵正解ヒューリスティック
  //   if (explorable.size() == 3) {
  //     int su = uf.size(N * (y - 1) + x);
  //     int sd = uf.size(N * (y + 1) + x);
  //     int sl = uf.size(N * y + x - 1);
  //     int sr = uf.size(N * y + x + 1);
  //     if (!cells[y][x].up || visited[y - 1][x]) {
  //       if (sd < sl && sd < sr) return {y + 1, x};
  //       if (sl < sr) return {y, x - 1};
  //       return {y, x + 1};
  //     }
  //     if (!cells[y][x].down || visited[y + 1][x]) {
  //       if (su < sl && su < sr) return {y - 1, x};
  //       if (sl < sr) return {y, x - 1};
  //       return {y, x + 1};
  //     }
  //     if (!cells[y][x].left || visited[y][x - 1]) {
  //       if (sr < su && sr < sd) return {y, x + 1};
  //       if (su < sd) return {y - 1, x};
  //       return {y + 1, x};
  //     }
  //     if (!cells[y][x].right || visited[y][x + 1]) {
  //       if (sl < su && sl < su) return {y, x - 1};
  //       if (su < sd) return {y - 1, x};
  //       return {y + 1, x};
  //     }
  //   }
  // }

  int mx = 1000000;
  for (auto [y2, x2] : st) {
    if (chmin(mx, 10 * uf.size(y2 * N + x2))) {
      ny = y2, nx = x2;
    }
  }

  return make_pair(ny, nx);
}

// BFSをする
Path init4(Cells& cells, int dirtyN) {
  Path path;
  vector visited(N, vi(N));

  int y = 0, x = 0;
  pushBackCell(cells, path, visited, y, x);
  while (true) {
    // 候補を探す
    auto [ny, nx] = bfsNearestUnvisited(y, x, visited, cells);
    if (ny == -1) break;  // 未訪問頂点なし

    // 移動をする
    connectPath(y, x, ny, nx, cells, visited, path);
    y = ny, x = nx;
  }
  // 最後に0に戻る
  if (path.back().first != 0 || path.back().second != 0) {
    connectPath(path.back().first, path.back().second, 0, 0, cells, visited,
                path);
  }

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

bool delNeighbor(Cells& cells, Path& path, ll& bestScore) {
  int i;
  i = randXor() % (int)path.size();
  // 削除できるか判定
  auto [y, x] = path[i];

  if (cells[y][x].visitedVec.size() <= 1) return false;
  int start = randXor() % ((int)cells[y][x].visitedVec.size() - 1);
  map<pair<int, int>, int> mp;

  for (int j = cells[y][x].visitedVec[start] + 1;
       j < cells[y][x].visitedVec[start + 1]; j++) {
    mp[path[j]]++;
  }
  for (auto [k, v] : mp)
    if ((int)cells[k.first][k.second].visitedVec.size() <= v) return false;
  Cells prevCells = cells;
  // 削除の実施
  Path newPath;
  rep(j, cells[y][x].visitedVec[start] + 1) newPath.push_back(path[j]);
  for (int j = cells[y][x].visitedVec[start + 1] + 1; j < (int)path.size(); j++)
    newPath.push_back(path[j]);
  makeVisitedVec(cells, newPath);
  ll nowScore = calcScore(cells, (int)newPath.size() - 1);
  // 山登り
  if (bestScore < nowScore) {
    cells = prevCells;
  } else {
    swap(path, newPath);
    bestScore = nowScore;
    return true;
  }
  return false;
}

// 2opt風近傍

bool twoOptNeighbor(Cells& cells, Path& path, ll& bestScore) {
  int i = randXor() % ((int)path.size() - 1);
  auto [y, x] = path[i];

  Path prevPath;
  Cells prevCells;
  int flag = -1;
  int alpha = 50;

  if (cells[y][x].up) {
    auto it = upper_bound(all(cells[y - 1][x].visitedVec), i + alpha);
    if (it != cells[y - 1][x].visitedVec.end()) {
      flag = 1;
      int j = *it;
      prevPath = path;
      prevCells = cells;
      path.insert(path.begin() + j + 1, make_pair(y, x));
      path.insert(path.begin() + i + 1, make_pair(y - 1, x));
      for (int k = i + 2; k < j + 1; k++) {
        int k2 = j + 1 - k + (i + 2);
        if (k2 < k) break;
        swap(path[k], path[k2]);
      }
    }
  } else if (!flag && cells[y][x].down) {
    auto it = upper_bound(all(cells[y + 1][x].visitedVec), i + alpha);
    if (it != cells[y + 1][x].visitedVec.end()) {
      flag = 1;
      int j = *it;
      prevPath = path;
      prevCells = cells;
      path.insert(path.begin() + j + 1, make_pair(y, x));
      path.insert(path.begin() + i + 1, make_pair(y + 1, x));
      for (int k = i + 2; k < j + 1; k++) {
        int k2 = j + 1 - k + (i + 2);
        if (k2 < k) break;
        swap(path[k], path[k2]);
      }
    }
  } else if (!flag && cells[y][x].left) {
    auto it = upper_bound(all(cells[y][x - 1].visitedVec), i + alpha);
    if (it != cells[y][x - 1].visitedVec.end()) {
      flag = 1;
      int j = *it;
      prevPath = path;
      prevCells = cells;
      path.insert(path.begin() + j + 1, make_pair(y, x));
      path.insert(path.begin() + i + 1, make_pair(y, x - 1));
      for (int k = i + 2; k < j + 1; k++) {
        int k2 = j + 1 - k + (i + 2);
        if (k2 < k) break;
        swap(path[k], path[k2]);
      }
    }
  } else if (!flag && cells[y][x].right) {
    auto it = upper_bound(all(cells[y][x + 1].visitedVec), i + alpha);
    if (it != cells[y][x + 1].visitedVec.end()) {
      flag = 1;
      int j = *it;
      prevPath = path;
      prevCells = cells;
      path.insert(path.begin() + j + 1, make_pair(y, x));
      path.insert(path.begin() + i + 1, make_pair(y, x + 1));
      for (int k = i + 2; k < j + 1; k++) {
        int k2 = j + 1 - k + (i + 2);
        if (k2 < k) break;
        swap(path[k], path[k2]);
      }
    }
  }
  if (!flag) return false;

  makeVisitedVec(cells, path);
  ll nowScore = calcScore(cells, (int)path.size() - 1);
  // ダメなら戻す
  if (bestScore < nowScore) {
    path = prevPath, cells = prevCells;
  } else if (bestScore == nowScore) {
    // うう
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

  auto startClock = system_clock::now();
  // // const static double START_TEMP = 1e4;    // 開始時の温度
  // // const static double END_TEMP = 1e2;      // 終了時の温度
  const static double END_TIME = 1.8;  // 終了時間（秒）
  double time = 0.0;                   // 経過時間（秒）

  // build
  Cells cells(N, vector<Cell>(N));
  rep(i, N - 1) rep(j, N) {
    if (H[i][j] == '0') cells[i][j].down = true, cells[i + 1][j].up = true;
  }
  rep(i, N) rep(j, N - 1) {
    if (V[i][j] == '0') cells[i][j].right = true, cells[i][j + 1].left = true;
  }
  rep(i, N) rep(j, N) cells[i][j].d = D[i][j];
  // 汚いエリアを前計算

  priority_queue<pair<int, pair<int, int>>> pq;
  queue<pair<int, int>> q;

  rep(i, N) rep(j, N) {
    if (D[i][j] >= 150) pq.emplace(D[i][j], make_pair(i, j));
  }
  rep(i, min(10, (int)pq.size())) q.push(pq.top().second), pq.pop();
  while (q.size()) {
    auto p = q.front();
    q.pop();
    for (int dy = -2; dy <= 2; dy++)
      for (int dx = -2; dx <= 2; dx++) {
        int y = p.first + dy;
        int x = p.second + dy;
        if (y < 0 || y >= N || x < 0 || x >= N) continue;
        if (D[y][x] >= 150 && dirtyPoints.count(make_pair(y, x)) == 0) {
          q.emplace(y, x);
        }
        dirtyPoints.insert(p);
      }
  }
  // init
  Path path = init4(cells, 1);
  string bestAns = path2str(path);
  ll bestScore = calcScore(cells, (int)bestAns.size());
  int bestDirtyN = 1;

  auto initCells = [&]() {
    rep(i, N) rep(j, N) cells[i][j].visitedVec.clear();
  };

  int cnt = 0;
  int addCnt = 0, delCnt = 0, twoOptCnt = 0;
  while (++cnt) {
    // 時間更新
    time =
        ((double)duration_cast<microseconds>(system_clock::now() - startClock)
             .count() *
         1e-6);
    if (time >= END_TIME) break;

    // 追加近傍
    {
      bool isChange = addNeighbor(cells, path, bestScore);
      if (isChange) addCnt++;
    }
    // // 削除近傍
    {
      bool isChange = delNeighbor(cells, path, bestScore);
      if (isChange) delCnt++;
    }
    // 2opt近傍
    // {
    //   bool isChange = twoOptNeighbor(cells, path, bestScore);
    //   if (isChange) twoOptCnt++;
    // }
  }
  // debug(cnt, addCnt, delCnt, twoOptCnt);

  // for (int dirtyN = 300; dirtyN <= 2000; dirtyN += 100) {
  //   initCells();
  //   path = init4(cells, dirtyN);
  //   if (path[0].first == -1) continue;
  //   string ans = path2str(path);
  //   // debug(dirtyN, calcScore(cells, (int)ans.size()));
  //   if (chmin(bestScore, calcScore(cells, (int)ans.size()))) {
  //     bestAns = ans;
  //     bestDirtyN = dirtyN;
  //   }
  // }

  // debug(path);
  // debug(path2str(path));

  // 追加近傍のテスト

  // output
  // debug((int)ans.size());
  // debug(calcScore(cells, (int)ans.size()));
  // cerr << bestScore << " " << bestDirtyN << endl;

  cerr << bestScore << endl;
  out(path2str(path));
}
