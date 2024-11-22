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
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

template <class T>
struct PriorityQueue {
  /*
    双方向優先度付きキュー
   https://natsugiri.hatenablog.com/entry/2016/10/10/035445
  */
  vector<T> d;

  PriorityQueue() {}

  PriorityQueue(const vector<T>& d_) : d(d_) { make_heap(); }

  template <class Iter>
  PriorityQueue(Iter first, Iter last) : d(first, last) {
    make_heap();
  }

  void push(const T& x) {
    int k = (int)d.size();
    d.push_back(x);
    up(k);
  }

  void pop_min() {
    if (d.size() < 3u) {
      d.pop_back();
    } else {
      swap(d[1], d.back());
      d.pop_back();
      int k = down(1);
      up(k);
    }
  }

  void pop_max() {
    if (d.size() < 2u) {
      d.pop_back();
    } else {
      swap(d[0], d.back());
      d.pop_back();
      int k = down(0);
      up(k);
    }
  }

  const T& get_min() const { return d.size() < 2u ? d[0] : d[1]; }

  const T& get_max() const { return d[0]; }

  int size() const { return (int)d.size(); }

  bool empty() const { return d.empty(); }

  void make_heap() {
    for (int i = d.size(); i--;) {
      if (i & 1 && d[i - 1] < d[i]) swap(d[i - 1], d[i]);
      int k = down(i);
      up(k, i);
    }
  }

  inline int parent(int k) const { return ((k >> 1) - 1) & ~1; }

  int down(int k) {
    int n = (int)d.size();
    if (k & 1) {  // min heap
      while (2 * k + 1 < n) {
        int c = 2 * k + 3;
        if (n <= c || d[c - 2] < d[c]) c -= 2;
        if (c < n && d[c] < d[k]) {
          swap(d[k], d[c]);
          k = c;
        } else
          break;
      }
    } else {  // max heap
      while (2 * k + 2 < n) {
        int c = 2 * k + 4;
        if (n <= c || d[c] < d[c - 2]) c -= 2;
        if (c < n && d[k] < d[c]) {
          swap(d[k], d[c]);
          k = c;
        } else
          break;
      }
    }
    return k;
  }

  int up(int k, int root = 1) {
    if ((k | 1) < (int)d.size() && d[k & ~1] < d[k | 1]) {
      swap(d[k & ~1], d[k | 1]);
      k ^= 1;
    }

    int p;
    while (root < k && d[p = parent(k)] < d[k]) {  // max heap
      swap(d[p], d[k]);
      k = p;
    }
    while (root < k && d[k] < d[p = parent(k) | 1]) {  // min heap
      swap(d[p], d[k]);
      k = p;
    }
    return k;
  }
};

// 時間を管理するクラス
class TimeKeeper {
 private:
  std::chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限をミリ秒単位で指定してインスタンスをつくる。
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(std::chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}

  // インスタンス生成した時から指定した時間制限を超過したか判定する。
  bool isTimeOver() const {
    auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
    return std::chrono::duration_cast<std::chrono::milliseconds>(diff)
               .count() >= time_threshold_;
  }
};

std::mt19937 mt_for_action(0);  // 行動選択用の乱数生成器を初期化
using ScoreType = int64_t;  // ゲームの評価スコアの型を決めておく。
constexpr const ScoreType INF =
    1000000000LL;  // あり得ないぐらい大きなスコアの例を用意しておく

const int EMPTY = 25;
const int NOT_ASSIGNED = 5;
vi dy = {1, -1, 0, 0}, dx = {0, 0, 1, -1};

#pragma region hash
// ランダムな64ビット整数を生成するためのエンジン
const int SEED = 1;
std::mt19937_64 rng(SEED);
std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
// Zobristハッシュ用のテーブル
uint64_t zobristTable[5][5][26];
uint64_t zobristPosition[5][5][5];
uint64_t zobristDestination[5][6][5];
uint64_t zobristAssigned[5][26];

// Zobristテーブルの初期化
void initializeZobrist() {
  rep(i, 5) rep(j, 5) rep(k, 26) zobristTable[i][j][k] = dist(rng);
  rep(i, 5) rep(j, 5) rep(k, 5) zobristPosition[i][j][k] = dist(rng);
  rep(i, 5) rep(j, 6) rep(k, 5) zobristDestination[i][j][k] = dist(rng);
  rep(i, 5) rep(j, 25) zobristAssigned[i][j] = dist(rng);
}

// ボードの初期ハッシュ値を計算
uint64_t computeInitialHash(const vector<vector<int>>& board, vpii& position,
                            vpii& destination, vi& assigneds) {
  uint64_t hash = 0;
  rep(i, 5) rep(j, 5) {
    int value = board[i][j];
    hash ^= zobristTable[i][j][value];
  }
  rep(i, 5) hash ^= zobristPosition[i][position[i].first][position[i].second];

  rep(i, 5) hash ^=
      zobristDestination[i][destination[i].first][destination[i].second];
  rep(i, 5) hash ^= zobristAssigned[i][assigneds[i]];

  return hash;
}

// ボードの一部が変更された際にハッシュ値を更新
void updateTableHash(uint64_t& currentHash, int y, int x, int oldValue,
                     int newValue) {
  currentHash ^= zobristTable[y][x][oldValue];  // 古い値をハッシュから除外
  currentHash ^= zobristTable[y][x][newValue];  // 新しい値をハッシュに追加
}
void updatePositionHash(uint64_t& currentHash, int idx, int oldy, int oldx,
                        int newy, int newx) {
  currentHash ^= zobristPosition[idx][oldy][oldx];
  currentHash ^= zobristPosition[idx][newy][newx];
}
void updateDestinationHash(uint64_t& currentHash, int idx, int oldy, int oldx,
                           int newy, int newx) {
  currentHash ^= zobristDestination[idx][oldy][oldx];
  currentHash ^= zobristDestination[idx][newy][newx];
}
void updateAssignedHash(uint64_t& currentHash, int idx, int oldContainer,
                        int newContainer) {
  currentHash ^= zobristAssigned[idx][oldContainer];
  currentHash ^= zobristAssigned[idx][newContainer];
}

#pragma endregion hash

class Crane {
 public:
  int id;
  pair<int, int> position;
  int hasContainer;
  string path;
  int assignedContainer;
  pii destination = make_pair(NOT_ASSIGNED, 0);

  Crane() {
    position = make_pair(NOT_ASSIGNED, 0);
    hasContainer = EMPTY;
    path = "";
    assignedContainer = EMPTY;
    destination = make_pair(NOT_ASSIGNED, 0);
  }

  void hold(vvi& board, uint64_t& hash) {
    assert(board[position.first][position.second] != EMPTY);
    hasContainer = board[position.first][position.second];
    updateTableHash(hash, position.first, position.second,
                    board[position.first][position.second], EMPTY);
    board[position.first][position.second] = EMPTY;
    path.push_back('P');
  }
  void release(vvi& board, unordered_set<int>& exportedSet, uint64_t& hash) {
    path.push_back('Q');
    // assert(board[position.first][position.second] == EMPTY);
    if (position.second == 4) {
      exportedSet.insert(hasContainer);
    } else {
      updateTableHash(hash, position.first, position.second, EMPTY,
                      hasContainer);
      board[position.first][position.second] = hasContainer;
    }
    hasContainer = EMPTY;
    updateAssignedHash(hash, id, assignedContainer, EMPTY);
    assignedContainer = EMPTY;
    updateDestinationHash(hash, id, destination.first, destination.second,
                          NOT_ASSIGNED, 0);
    destination.first = NOT_ASSIGNED;
    destination.second = 0;
  }
  void move(char d, uint64_t& hash) {
    path.push_back(d);
    int oldy = position.first, oldx = position.second;
    if (d == 'U') position.first--;
    if (d == 'D') position.first++;
    if (d == 'R') position.second++;
    if (d == 'L') position.second--;
    // '.'なら何もしない
    int newy = position.first, newx = position.second;
    updatePositionHash(hash, id, oldy, oldx, newy, newx);
    assert(min(position.first, position.second) >= 0);
    assert(max(position.first, position.second) < 5);
  }

  void explode() { path.push_back('B'); }

  void printCrane() {
    //
    debug(position, hasContainer, assignedContainer, destination);
  }
};

class Job {
 public:
  /* 1:= (y, 0)から大クレーンで搬出
     2:= (y, 0)以外から大クレーンで搬出
     3:= (y, 0)から大クレーンで移動
     4:= (y, 0)以外から大クレーンで移動
     5-8 := 1-4の小クレーン版
     9 := (y, 0)からとりあえず移動
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
    if (board[y][x] == EMPTY) continue;
    //
    bool isTarget = false;
    rep(i, 5) if (targetContainer[i] == board[y][x]) isTarget = true;
    //
    if (isTarget) {
      if (canExportable(y, x)) {
        // 搬出対象かつ小クレーンでも運べる
        if (x == 0) {
          ret.emplace_back(5, y, x);
        } else {
          ret.emplace_back(6, y, x);
        }
      } else {
        // 搬出対象で大クレーンで運ぶ必要がある
        if (x == 0) {
          ret.emplace_back(1, y, x);
        } else {
          ret.emplace_back(2, y, x);
        }
      }
    } else {
      if (canValuableMove(y, x)) {
        // 移動有効かつ小クレーン担当
        if (x == 0) {
          ret.emplace_back(7, y, x);
        } else {
          ret.emplace_back(8, y, x);
        }
      } else {
        if (x == 0) {
          ret.emplace_back(9, y, x);
        }
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

void updateDestination(vector<Crane>& craneList, vi& targetContainer,
                       uint64_t& hash) {
  rep(i, 5) {
    if (craneList[i].hasContainer == EMPTY) {
      // まだ持っていないか仕事割り当てなし（既に設定済みなのでよい）
      continue;
    }
    bool isTarget = false;
    rep(j, 5) if (targetContainer[j] == craneList[i].hasContainer) isTarget =
        true;

    int oldy = craneList[i].destination.first,
        oldx = craneList[i].destination.second;
    craneList[i].destination.first = craneList[i].hasContainer / 5;
    craneList[i].destination.second = (isTarget ? 4 : 3);
    int newy = craneList[i].destination.first,
        newx = craneList[i].destination.second;
    updateDestinationHash(hash, i, oldy, oldx, newy, newx);
  }
}

void assigneJobs(vector<Job>& jobs, vvi& board, vector<Crane>& craneList) {
  // とりあえず効率無視で仕事を振る
  unordered_set<int> isAssigned;
  rep(i, 5) isAssigned.insert(craneList[i].assignedContainer);

  sort(all(jobs), [](Job& a, Job& b) {
    if (a.kind != b.kind) return a.kind < b.kind;
    if (a.posx != b.posx) return a.posx > b.posx;
    return a.posy < b.posy;
  });
  rep(i, 5) {
    if (craneList[i].assignedContainer != EMPTY) continue;
    int nowy = -1, nowx = 0, nowkind = 0;
    int y = craneList[i].position.first, x = craneList[i].position.second;
    for (auto&& job : jobs) {
      if (i && job.kind < 5) continue;
      if (isAssigned.count(board[job.posy][job.posx])) continue;
      if (nowkind != job.kind) {
        // kindが小さい方を採用する
        if (nowy != -1) break;
        nowkind = job.kind;
      }
      if (nowy == -1) {
        nowy = job.posy, nowx = job.posx;
        continue;
      }
      // 近い方を採用する
      if (abs(y - nowy) + abs(x - nowx) >
          abs(y - job.posy) + abs(x - job.posx)) {
        nowy = job.posy, nowx = job.posx;
      }
    }
    if (nowy != -1) {
      isAssigned.insert(board[nowy][nowx]);
      craneList[i].assignedContainer = board[nowy][nowx];
      craneList[i].destination = make_pair(nowy, nowx);
    }
  }
}

class State {
 private:
  // 有効な移動ができるか判定
  bool canValuableMove(int y, int x, int containerId) {
    // 右方向に移動できるか
    if (x < 2 && board[y][x + 1] == EMPTY) return true;
    // 有効な上下方向に移動できるか
    int destY = containerId / 5;
    int ny = -1;
    if (destY > y && y + 1 < 5) ny = y + 1;
    if (destY < y && y - 1 >= 0) ny = y - 1;
    if (ny != -1 && board[ny][x] == EMPTY) return true;
    return false;
  }

 public:
  ScoreType evaluated_score_ = 0;  // 探索上で評価したスコア
  string first_action_ = "";  // 探索木のルートノードで最初に選択した行動
  vi targetContainer = {0, 5, 10, 15, 20};
  vvi board;
  vector<Crane> craneList;
  vector<deque<int>> A;
  unordered_set<int> exportedSet;
  uint64_t hash;

  State() {}

  State(vvi argBoard, vector<Crane> argCraneList, vector<deque<int>> argA,
        unordered_set<int> argExportedSet, uint64_t argHash)
      : board(argBoard),
        craneList(argCraneList),
        A(argA),
        exportedSet(argExportedSet),
        hash(argHash) {}

  // ゲームの終了判定
  bool isDone() const {
    /*処理*/
    rep(i, 5) if (targetContainer[i] != -1) return false;
    return true;
  }

  // 探索用の盤面評価をする
  void evaluateScore(string moves) {
    int value = 0;
    int cntdot = 0;
    rep(i, 5) {
      int weight = (i == 0 ? 100 : 10);  // 大クレーン優先
      // 目的がないのはなんでもいい
      if (craneList[i].destination.first == NOT_ASSIGNED) {
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
        } else if (craneList[i].position.second == 0) {
          // x = 0に置くことは基本ない
          value -= 1000;
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
        if (craneList[i].position.second < craneList[i].destination.second) {
          value += weight;
        } else {
          value -= weight;
        }
      } else if (moves[i] == 'L') {
        if (craneList[i].position.second > craneList[i].destination.second) {
          value += weight;
        } else {
          value -= weight;
        }
      }
    }
    if (cntdot == 5) value = -10000;

    evaluated_score_ += value;
  }

  // 指定したactionでゲームを1ターン進める
  void advance(const string moves) {
    assert(moves.size() == 5);
    // 移動の実行
    rep(i, 5) {
      switch (moves[i]) {
        case 'P':
          craneList[i].hold(board, hash);
          break;
        case 'Q':
          craneList[i].release(board, exportedSet, hash);
          break;
        case 'U':
        case 'D':
        case 'R':
        case 'L':
        case '.':
          craneList[i].move(moves[i], hash);
          break;
      }
    }
    // 1列目が空いていたら搬入
    rep(y, 5) if (board[y][0] == EMPTY && A[y].size()) {
      bool notEmpty = false;
      rep(i, 5) if (craneList[i].position.first == y &&
                    craneList[i].position.second == 0 &&
                    craneList[i].hasContainer != EMPTY) notEmpty = true;
      if (notEmpty) continue;
      board[y][0] = A[y].front();
      A[y].pop_front();
      updateTableHash(hash, y, 0, EMPTY, board[y][0]);
    }
    // targetの更新
    rep(i, 5) {
      while (exportedSet.count(targetContainer[i])) {
        targetContainer[i]++;
        if (targetContainer[i] % 5 == 0) targetContainer[i] = -1;
        break;
      }
    }
  }

  // 現在の状況でプレイヤーが可能な行動を全て取得する
  vector<string> legalActions() {
    vector<string> actions;
    /*処理*/
    string operation = "QRLUD";

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
        // debug(moves);
        if (!checkCollision(moves)) actions.push_back(moves);
        return;
      }

      if (craneList[idx].position == craneList[idx].destination) {
        // 掴む離すは一択
        if (craneList[idx].hasContainer == EMPTY) {
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
          if (idx && craneList[idx].hasContainer != EMPTY) {
            int y = craneList[idx].position.first;
            int x = craneList[idx].position.second;
            if (c == 'D') y++;
            if (c == 'U') y--;
            if (c == 'R') x++;
            if (c == 'L') x--;
            if (board[y][x] != EMPTY) continue;
          }
          // TODO：大クレーンはコンテナを超えて移動できるが、置ける見込みがないと困る
          if (idx == 0 && craneList[idx].hasContainer != EMPTY &&
              targetContainer[craneList[idx].hasContainer / 5] !=
                  craneList[idx].hasContainer) {
            int y = craneList[idx].position.first;
            int x = craneList[idx].position.second;
            if (c == 'D') y++;
            if (c == 'U') y--;
            if (c == 'R') x++;
            if (c == 'L') x--;
            if (board[y][x] != EMPTY) continue;
          }
          // 持ってなきゃ置けない
          if (c == 'Q' && craneList[idx].hasContainer == EMPTY) continue;
          // 空きマス以外には置けない
          if (c == 'Q' && board[craneList[idx].position.first]
                               [craneList[idx].position.second] != EMPTY)
            continue;
          // targetじゃないなら5列目には動かさない
          if (c == 'R' && craneList[idx].position.second == 3 &&
              craneList[idx].hasContainer != EMPTY &&
              targetContainer[craneList[idx].hasContainer / 5] !=
                  craneList[idx].hasContainer)
            continue;
          moves.push_back(c);
          rec(rec, idx + 1, moves);
          moves.pop_back();
        }
      }
    };
    string tmp;
    f(f, 0, tmp);

    return actions;
  }
};

// 探索時のソート用に評価を比較する
bool operator<(const State& state_1, const State& state_2) {
  return state_1.evaluated_score_ < state_2.evaluated_score_;
}

// ビーム幅と制限時間(ms)を指定してビームサーチで行動を決定する
vector<string> beamSearchActionWithTimeThreshold(const State& state,
                                                 int beam_width,
                                                 const int64_t time_threshold) {
  auto time_keeper = TimeKeeper(time_threshold);

  PriorityQueue<State> now_beam;
  State best_state;
  unordered_set<uint64_t> seenHash;

  now_beam.push(state);
  for (int t = 0; t < 300; t++) {
    debug(t);
    PriorityQueue<State> next_beam;
    if (time_keeper.isTimeOver()) {
      beam_width = 40;
    }

    for (int i = 0; i < beam_width; i++) {
      if (now_beam.empty()) break;
      State now_state = now_beam.get_max();
      now_beam.pop_max();

      // 仕事の割り当て
      vector<Job> jobs = listJobs(now_state.targetContainer, now_state.board,
                                  now_state.craneList);
      assigneJobs(jobs, now_state.board, now_state.craneList);
      updateDestination(now_state.craneList, now_state.targetContainer,
                        now_state.hash);

      // 合法手を取得
      auto legal_actions = now_state.legalActions();
      // debug(t, now_state.evaluated_score_, legal_actions.size());
      // 全て試して、合法手を評価
      for (const auto& action : legal_actions) {
        State next_state = now_state;
        next_state.evaluated_score_ = now_state.evaluated_score_;
        next_state.evaluateScore(action);

        // ビームのサイズ分しか持たない
        bool popFlag = false;
        if (next_beam.size() == beam_width) {
          if (next_beam.get_min().evaluated_score_ >=
              next_state.evaluated_score_) {
            continue;
          } else {
            popFlag = true;
          }
        }
        next_state.advance(action);

        if (seenHash.count(next_state.hash) == 0) {
          seenHash.insert(next_state.hash);
          if (popFlag) next_beam.pop_min();
          next_beam.push(next_state);
        }
      }
    }

    // TODO swapでよさそう
    swap(now_beam, next_beam);
    // now_beam = next_beam;
    // ゲーム終了してたら終了
    best_state = now_beam.get_max();
    // rep(i, 5) best_state.craneList[i].printCrane();
    if (best_state.isDone()) break;
  }
  vector<string> ret(5);
  best_state = now_beam.get_max();
  rep(i, 5) ret[i] = best_state.craneList[i].path;
  return ret;
}

int main() {
  /* input */
  INT(N);
  vector<deque<int>> A(N, deque<int>(N));
  rep(i, N) rep(j, N) cin >> A[i][j];

  int beam_width = 25000;
  int time_threshold = 2400;

  /* initialize */
  vector board(5, vi(5, EMPTY));
  vi targetContainer = {0, 5, 10, 15, 20};
  // 最初の搬入
  rep(i, 5) {
    board[i][0] = A[i].front();
    A[i].pop_front();
  }
  // クレーン
  vector<Crane> craneList(5);
  unordered_set<int> exportedSet;
  rep(i, 5) craneList[i].position.first = i, craneList[i].id = i;
  // zobristhash
  initializeZobrist();
  vpii position = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}};
  vpii destination(5, {NOT_ASSIGNED, 0});
  vi assigns(5, EMPTY);
  uint64_t hash = computeInitialHash(board, position, destination, assigns);

  State initState(board, craneList, A, exportedSet, hash);

  /* solve */

  vector<string> ans =
      beamSearchActionWithTimeThreshold(initState, beam_width, time_threshold);

  /* output */
  rep(i, N) out(ans[i]);
}