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

// 盤面情報 0-24：コンテナ、30：空き
const int EMPTY = 30;
vector board(5, vi(5, EMPTY));

class Crane {
 public:
  int id;
  pair<int, int> position;
  int container;
  pair<int, int> destination;
  string path;

  Crane() {}

  Crane(int argId) {
    id = argId;
    position = make_pair(id, 0);
    container = -1;
    destination = make_pair(-1, -1);
    path = "";
  }

  void hold(int argContainer) {
    assert(board[position.first][position.second] != EMPTY);
    board[position.first][position.second] = EMPTY;
    path.push_back('P');
    container = argContainer;
  }
  void release() {
    path.push_back('Q');
    assert(board[position.first][position.second] == EMPTY);
    if (position.second != 4)
      board[position.first][position.second] = container;
    container = -1;
  }
  void move(char d) {
    path.push_back(d);
    if (d == 'U') position.first--;
    if (d == 'D') position.first++;
    if (d == 'R') position.second++;
    if (d == 'L') position.second--;
    assert(min(position.first, position.second) >= 0);
    assert(max(position.first, position.second) < 5);
  }

  void explode() {
    path.push_back('B');
    id = -1;
  }

  void printCrane() {
    //
    debug(id, position, container, destination);
  }
};

class Score {
 public:
  int M0, M1, M2, M3;

  Score() { M0 = 0, M1 = 0, M2 = 0, M3 = 25; }

  int calcScore() {
    //
    return M0 + 100 * M1 + 10000 * M2 + 1000000 * M3;
  }
};

int main() {
  // 入力
  INT(N);
  vector A(N, vi(N));
  rep(i, N) rep(j, N) cin >> A[i][j];

  // 次に運ぶべきコンテナ
  vi targetContainer = {0, 5, 10, 15, 20};
  // 次搬入されるコンテナのidx
  vi aidx(5);
  // 最初の搬入
  rep(i, 5) board[i][0] = A[i][aidx[i]];
  // クレーン
  vector<Crane> craneList;
  rep(i, 5) craneList.emplace_back(i);
  //

  rep(i, 4) {
    // 持つ
    rep(j, N) {
      craneList[j].hold(board[j][0]);
      aidx[j]++;
      // 出現する
      if (aidx[j] < N) board[j][0] = A[j][aidx[j]];
    }
    // 右に移動
    rep(j, N) rep(k, 3 - i) {
      //
      craneList[j].move('R');
    }
    // 離す
    rep(j, N) { craneList[j].release(); }
    // i=2なら爆発
    if (i == 2) {
      craneList[0].move('L');
      for (int j = 1; j < N; j++) craneList[j].explode();
      break;
    }
    // スタート位置に戻る
    rep(j, N) rep(k, 3 - i) craneList[j].move('L');
  }
  debug(board);
  unordered_set<int> delivered;

  int target = -1;
  rep(i, 5) rep(j, 4) if (board[i][j] % 5 == 0) target = board[i][j];
  if (target == -1) target = 1;

  auto moveToDestination = [&](int ty, int tx, int& ny, int& nx) {
    while (ty > ny) ny++, craneList[0].move('D');
    while (ty < ny) ny--, craneList[0].move('U');
    while (tx > nx) nx++, craneList[0].move('R');
    while (tx < nx) nx--, craneList[0].move('L');
  };

  auto f = [&]() -> int {
    // 取り出せていないところがあるかも
    rep(i, 5) {
      if (aidx[i] < N - 1) {
        int ty = i, tx = 0;
        int ok = 0;
        for (int j = 1; j < 4; j++)
          if (board[i][j] == EMPTY) ok = 1;
        if (!ok) continue;

        auto [ny, nx] = craneList[0].position;
        moveToDestination(ty, tx, ny, nx);
        craneList[0].hold(board[ty][tx]);
        aidx[ty]++;
        board[ty][tx] = A[ty][aidx[ty]];

        while (board[ny][nx] != EMPTY) {
          craneList[0].move('R');
          nx++;
        }
        // 離す
        craneList[0].release();
        return board[i][0];
      }
    }
    return -1;
  };

  while (target >= 0) {
    // target
    int ty, tx, kind = target / 5;
    rep(i, 5) rep(j, 4) if (board[i][j] == target) ty = i, tx = j;
    // now position
    auto [ny, nx] = craneList[0].position;
    // debug(board);
    // debug(target, ty, tx, ny, nx);
    // そこまで行く
    moveToDestination(ty, tx, ny, nx);

    // 掴む
    craneList[0].hold(board[ny][nx]);
    if (nx == 0 && ++aidx[ny] < N) {
      board[ny][0] = A[ny][aidx[ny]];
    }
    // 目的地まで行く
    ty = kind, tx = 4;
    moveToDestination(ty, tx, ny, nx);
    // debug(ny, nx, board[ny][nx]);
    // 離す
    craneList[0].release();
    // queueに入れる
    if (targetContainer[kind] % 5 == 4) {
      targetContainer[kind] = -1;
    } else {
      targetContainer[kind]++;
    }
    delivered.insert(target);
    target = -1;
    rep(k, 5) {
      if (targetContainer[k] == -1) continue;
      targetContainer[k] = k * 5;
      while (delivered.count(targetContainer[k])) targetContainer[k]++;
      if (targetContainer[k] >= (k + 1) * 5) targetContainer[k] = -1;
    }
    rep(k, 5) {
      if (target != -1) break;
      rep(i, 5) rep(j, 4) {
        if (board[i][j] == targetContainer[k]) target = targetContainer[k];
      }
    }
    if (target == -1) target = f();
  }
  debug(board);
  // rep(i, N) rep(j, N) assert(board[i][j] == 30);

  // 出力
  rep(i, N) out(craneList[i].path);
}