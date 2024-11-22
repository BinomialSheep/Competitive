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

// 盤面が空きであることを表す
const int EMPTY = 30;

vi dy = {1, -1, 0, 0}, dx = {0, 0, 1, -1};

class Crane {
 public:
  int id;
  pair<int, int> position;
  int hasContainer;
  int assignedContainer;
  pair<int, int> destination;
  string path;
  vvi& board;
  unordered_set<int>& exportedSed;

  Crane(int argId, vvi& argBoard, unordered_set<int>& argExportedSed)
      : id(argId), board(argBoard), exportedSed(argExportedSed) {
    position = make_pair(id, 0);
    hasContainer = -1;
    assignedContainer = -1;
    destination = make_pair(-1, -1);
    path = "";
  }

  void hold() {
    assert(board[position.first][position.second] != EMPTY);
    hasContainer = board[position.first][position.second];
    board[position.first][position.second] = EMPTY;
    path.push_back('P');
  }
  void release() {
    path.push_back('Q');
    // assert(board[position.first][position.second] == EMPTY);
    if (position.second == 4) {
      exportedSed.insert(hasContainer);
    } else {
      board[position.first][position.second] = hasContainer;
    }
    hasContainer = -1;
    assignedContainer = -1;
    destination.first = -1;
  }
  void move(char d) {
    path.push_back(d);
    if (d == 'U') position.first--;
    if (d == 'D') position.first++;
    if (d == 'R') position.second++;
    if (d == 'L') position.second--;
    // '.'なら何もしない
    assert(min(position.first, position.second) >= 0);
    assert(max(position.first, position.second) < 5);
  }

  void explode() {
    path.push_back('B');
    id = -1;
  }

  void printCrane() {
    //
    debug(id, position, hasContainer, assignedContainer, destination);
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

class Job {
 public:
  /* 1:= (y, 0)から大クレーンで搬出
     2:= (y, 0)以外から大クレーンで搬出
     3:= (y, 0)から大クレーンで移動
     4:= (y, 0)以外から大クレーンで移動
     5-8 := 1-4の小クレーン版
  */
  int kind;
  int containerNum, posy, posx;

  Job() {}

  Job(int argKind, int argPosy, int argPposx)
      : kind(argKind), posy(argPosy), posx(argPposx) {}

  bool operator<(const Job& other) const { return this->kind < other.kind; }
};

vector<Job> listJobs(vi& targetContainer, vvi& board,
                     vector<Crane>& craneList) {
  vector<Job> ret;
  // クレーンが担当中のものを列挙
  unordered_set<int> isAssigned;
  rep(i, 5) isAssigned.insert(craneList[i].assignedContainer);
  // 搬出できるものを列挙
  dsu uf(5 * 5);
  rep(y, 5) rep(x, 5) {
    int pos = y * 5 + x;
    if (x < 4 && board[y][x] == EMPTY && board[y][x + 1] == EMPTY)
      uf.merge(pos, pos + 1);
    if (y < 4 && board[y][x] == EMPTY && board[y + 1][x] == EMPTY)
      uf.merge(pos, pos + 5);
  }
  auto canExportable = [&](int y, int x) -> bool {
    return (x < 4 && uf.same(y * 5 + x + 1, 4)) ||
           (y < 4 && uf.same((y + 1) * 5 + x, 4));
  };
  // 有効な移動ができるか判定
  auto canValuableMove = [&](int y, int x) -> bool {
    // 右方向に移動できるか
    if (x < 2 && board[y][x + 1] == EMPTY) return true;
    // 有効な上下方向に移動できるか
    int destY = board[y][x] / 5;
    if (destY > y && board[y + 1][x] == EMPTY) return true;
    if (destY < y && board[y - 1][x] == EMPTY) return true;
    return false;
  };

  rep(y, 5) rep(x, 5) {
    if (board[y][x] == 30) continue;
    //
    bool isTarget = false;
    rep(i, 5) if (targetContainer[i] == board[y][x]) isTarget = true;
    //
    if (isTarget) {
      if (canExportable(y, x)) {
        // 搬出対象かつ小クレーンでも運べる
        if (y == 0) {
          ret.emplace_back(5, y, x);
        } else {
          ret.emplace_back(6, y, x);
        }
      } else {
        // 搬出対象で大クレーンで運ぶ必要がある
        if (y == 0) {
          ret.emplace_back(1, y, x);
        } else {
          ret.emplace_back(2, y, x);
        }
      }
    } else {
      if (canValuableMove(y, x)) {
        // 移動有効かつ小クレーン担当
        if (y == 0) {
          ret.emplace_back(7, y, x);
        } else {
          ret.emplace_back(8, y, x);
        }
      } else {
        // TODO：有効な移動箇所があるかちゃんと探索する必要があり面倒
        // if (y == 0) {
        //   ret.emplace_back(3, y, x);
        // } else {
        //   ret.emplace_back(4, y, x);
        // }
      }
    }
  }
  return ret;
}

void assigneJobs(vector<Job>& jobs, vvi& board, vector<Crane>& craneList) {
  // とりあえず効率無視で仕事を振る
  unordered_set<int> isAssigned;
  rep(i, 5) isAssigned.insert(craneList[i].assignedContainer);
  sort(all(jobs));
  rep(i, 5) {
    if (craneList[i].assignedContainer != -1) continue;
    for (auto&& job : jobs) {
      if (i && job.kind < 5) continue;
      if (isAssigned.count(board[job.posy][job.posx])) continue;
      isAssigned.insert(board[job.posy][job.posx]);
      craneList[i].assignedContainer = board[job.posy][job.posx];
      craneList[i].destination = make_pair(job.posy, job.posx);
      break;
    }
  }
}

void updateDestination(vector<Crane>& craneList, vi& targetContainer) {
  rep(i, 5) {
    if (craneList[i].hasContainer == -1) {
      // まだ持っていないか仕事割り当てなし（既に設定済みなのでよい）
      continue;
    }
    bool isTarget = false;
    rep(j, 5) if (targetContainer[j] == craneList[i].hasContainer) isTarget =
        true;

    craneList[i].destination.first = craneList[i].hasContainer / 5;
    craneList[i].destination.second = (isTarget ? 4 : 3);
  }
}

string exploreMoves(vector<Crane>& craneList, vvi& board) {
  string ret;
  int mxValue = -100100100;
  string operation = "UDLR.Q";

  auto checkCollision = [&](string& moves) -> bool {
    rep(i, 5) {
      int iy = craneList[i].position.first;
      int ix = craneList[i].position.second;
      int niy = iy, nix = ix;
      if (moves[i] == 'D') niy = iy + 1;
      if (moves[i] == 'U') niy = iy - 1;
      if (moves[i] == 'R') nix = ix + 1;
      if (moves[i] == 'L') nix = ix - 1;
      rep(j, i) {
        int jy = craneList[j].position.first;
        int jx = craneList[j].position.second;
        int njy = jy, njx = jx;
        if (moves[j] == 'D') njy = jy + 1;
        if (moves[j] == 'U') njy = jy - 1;
        if (moves[j] == 'R') njx = jx + 1;
        if (moves[j] == 'L') njx = jx - 1;
        // 同じところに移動しようとしていたら衝突
        if (niy == njy && nix == njx) return true;
        // すれ違いは衝突
        if (iy == jy && ix + 1 == jx && moves[i] == 'R' && moves[j] == 'L')
          return true;
        if (iy == jy && ix == jx + 1 && moves[i] == 'L' && moves[j] == 'R')
          return true;
        if (iy + 1 == jy && ix == jx && moves[i] == 'D' && moves[j] == 'U')
          return true;
        if (iy == jy + 1 && ix == jx && moves[i] == 'U' && moves[j] == 'D')
          return true;
      }
    }
    return false;
  };

  auto f = [&](auto rec, int idx, string& moves) -> void {
    if (idx == 5) {
      if (!checkCollision(moves)) {
        // 評価
        // 進捗を生めば+、遠ざかれば-
        // TODO：大クレーンと小クレーンで差を付けるなど
        int value = 0;
        int cntdot = 0;
        rep(i, 5) {
          int weight = (i == 0 ? 100 : 10);  // 大クレーン優先
          // 目的がないのはなんでもいい
          if (craneList[i].destination.first == -1) {
            if (moves[i] == '.') value -= weight;
            continue;
          }
          if (moves[i] == 'P') {
            value += weight;
          } else if (moves[i] == 'Q') {
            if (craneList[i].position == craneList[i].destination) {
              value += weight;
            } else if (craneList[i].position.second == 4) {
              // 別の場所に搬入するのは最悪
              value = -10000;
            } else {
              value += weight / 2;
            }
          } else if (moves[i] == '.') {
            // ±0（全部.だと-INFだが）
            // と思ったけどすれ違えるようにマイナスしておく
            cntdot++;
            value -= weight;
          } else if (moves[i] == 'D') {
            if (craneList[i].position.first < craneList[i].destination.first) {
              value += weight;
            } else {
              value -= weight;
            }
          } else if (moves[i] == 'U') {
            if (craneList[i].position.first > craneList[i].destination.first) {
              value += weight;
            } else {
              value -= weight;
            }
          } else if (moves[i] == 'R') {
            if (craneList[i].position.second <
                craneList[i].destination.second) {
              value += weight;
            } else {
              value -= weight;
            }
          } else if (moves[i] == 'L') {
            if (craneList[i].position.second >
                craneList[i].destination.second) {
              value += weight;
            } else {
              value -= weight;
            }
          }
        }
        // debug(value, moves);

        if (cntdot == 5) value = -10000;
        if (chmax(mxValue, value)) ret = moves;
      }
      return;
    }
    //     if (craneList[idx].destination.first == -1) {
    //   // 目標地点がないクレーンは何もしない？邪魔かも
    //   moves.push_back('.');
    //   rec(rec, idx + 1, moves);
    //   moves.pop_back();
    // } else

    if (craneList[idx].position == craneList[idx].destination) {
      // debug("確定", idx), craneList[idx].printCrane();
      // 掴む離すは一択
      if (craneList[idx].hasContainer == -1) {
        moves.push_back('P');
        rec(rec, idx + 1, moves);
        moves.pop_back();
      } else {
        moves.push_back('Q');
        rec(rec, idx + 1, moves);
        moves.pop_back();
      }
    } else {
      // 動きを全探索する
      for (auto c : operation) {
        // 非合法な動きはできない
        if (c == 'D' && craneList[idx].position.first == 4) continue;
        if (c == 'U' && craneList[idx].position.first == 0) continue;
        if (c == 'R' && craneList[idx].position.second == 4) continue;
        if (c == 'L' && craneList[idx].position.second == 0) continue;
        // 小クレーンはコンテナを持っている時に他のコンテナマスに移動できない
        if (idx && craneList[idx].hasContainer != -1) {
          int y = craneList[idx].position.first;
          int x = craneList[idx].position.second;
          if (c == 'D') y++;
          if (c == 'U') y--;
          if (c == 'R') x++;
          if (c == 'L') x--;
          if (board[y][x] != EMPTY) continue;
        }
        // TODO：大クレーンはコンテナを超えて移動できるが、置ける見込みがないと困る
        if (idx == 0 && craneList[idx].hasContainer != -1 &&
            craneList[idx].destination.second != 4) {
          int y = craneList[idx].position.first;
          int x = craneList[idx].position.second;
          if (c == 'D') y++;
          if (c == 'U') y--;
          if (c == 'R') x++;
          if (c == 'L') x--;
          if (board[y][x] != EMPTY) continue;
        }
        // 持ってなきゃ置けない
        if (c == 'Q' && craneList[idx].hasContainer == -1) continue;
        // 空きマス以外には置けない
        if (c == 'Q' && board[craneList[idx].position.first]
                             [craneList[idx].position.second] != EMPTY)
          continue;
        // targetじゃないなら5列目には動かさない
        if (c == 'R' && craneList[idx].position.second == 3 &&
            craneList[idx].destination.second <= 3)
          continue;
        moves.push_back(c);
        rec(rec, idx + 1, moves);
        moves.pop_back();
      }
    }
  };
  string tmp;
  f(f, 0, tmp);
  // debug(ret);

  return ret;
}

vector<Crane> naive(vector<deque<int>> A) {
  // 次に運ぶべきコンテナ
  vi targetContainer = {0, 5, 10, 15, 20};
  // 最初の搬入
  vector board(5, vi(5, EMPTY));
  int N = 5;
  rep(i, 5) {
    board[i][0] = A[i].front();
    A[i].pop_front();
  }
  // クレーン
  vector<Crane> craneList;
  unordered_set<int> exportedSet;
  rep(i, 5) craneList.emplace_back(i, board, exportedSet);
  //

  rep(i, 4) {
    // 持つ
    rep(y, N) {
      craneList[y].hold();
      board[y][0] = A[y].front();
      A[y].pop_front();
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
      if (A[i].size()) {
        int ty = i, tx = 0;
        int ok = 0;
        for (int j = 1; j < 4; j++)
          if (board[i][j] == EMPTY) ok = 1;
        if (!ok) continue;

        auto [ny, nx] = craneList[0].position;
        moveToDestination(ty, tx, ny, nx);
        craneList[0].hold();
        board[ty][0] = A[ty].front();
        A[ty].pop_front();

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
    craneList[0].hold();
    if (nx == 0 && A[ny].size()) {
      board[ny][0] = A[ny].front();
      A[ny].pop_front();
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
  rep(i, 5) rep(j, 5) assert(board[i][j] == 30);

  return craneList;
}

int main() {
  // 入力
  INT(N);
  vector<deque<int>> A(N, deque<int>(N));
  rep(i, N) rep(j, N) cin >> A[i][j];

  vector<deque<int>> origA = A;

  // 盤面情報 0-24：コンテナ、30：空き
  vector board(5, vi(5, EMPTY));
  // 次に運ぶべきコンテナ
  vi targetContainer = {0, 5, 10, 15, 20};
  // 最初の搬入
  rep(i, 5) {
    board[i][0] = A[i].front();
    A[i].pop_front();
  }
  // クレーン
  vector<Crane> craneList;
  unordered_set<int> exportedSet;
  rep(i, 5) craneList.emplace_back(i, board, exportedSet);

  auto isEnd = [&] {
    rep(i, 5) if (targetContainer[i] != -1) return false;
    return true;
  };

  int turn = 0;

  while (!isEnd() && ++turn < 500) {
    // 仕事の列挙
    vector<Job> jobs = listJobs(targetContainer, board, craneList);
    // for (auto job : jobs) debug(job.kind, job.containerNum, job.posy,
    // job.posx);
    //
    // 仕事の割り当て
    assigneJobs(jobs, board, craneList);
    // rep(i, 5) craneList[i].printCrane();
    // 目標地点の更新
    updateDestination(craneList, targetContainer);
    // 1ターン実行
    // 全移動を列挙し、一番評価値が高い移動を行う
    string moves = exploreMoves(craneList, board);
    rep(i, 5) {
      switch (moves[i]) {
        case 'P':
          craneList[i].hold();
          break;
        case 'Q':
          craneList[i].release();
          break;
        case 'U':
        case 'D':
        case 'R':
        case 'L':
        case '.':
          craneList[i].move(moves[i]);
          break;
      }
    }
    // 1列目が空いていたら搬入
    rep(y, 5) if (board[y][0] == EMPTY && A[y].size()) {
      bool notEmpty = false;
      rep(i, 5) if (craneList[i].position.first == y &&
                    craneList[i].position.second == 0 &&
                    craneList[i].hasContainer != -1) notEmpty = true;
      if (notEmpty) continue;
      board[y][0] = A[y].front();
      A[y].pop_front();
    }
    // targetの更新
    rep(i, 5) {
      while (exportedSet.count(targetContainer[i])) {
        targetContainer[i]++;
        if (targetContainer[i] % 5 == 0) targetContainer[i] = -1;
        break;
      }
    }

    // rep(i, 5) craneList[i].printCrane();

    // rep(i, N) out(craneList[i].path);
  }

  debug(board);
  // rep(i, N) rep(j, N) assert(board[i][j] == 30);

  // 上手くいっていなかったら仕方なくやる
  int flag = 0;
  rep(i, 5) rep(j, 5) if (board[i][j] != 30) flag = 1;
  if (flag) craneList = naive(origA);

  // 出力
  rep(i, N) out(craneList[i].path);
}
