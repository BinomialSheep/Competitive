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

const int EMPTY = 30;
vi dy = {1, -1, 0, 0}, dx = {0, 0, 1, -1};

class Crane {
 public:
  int id;
  pair<int, int> position;
  int hasContainer;
  string path;

  Crane(int argId) : id(argId) {
    position = make_pair(id, 0);
    hasContainer = -1;
    path = "";
  }

  void hold(vvi& board) {
    assert(board[position.first][position.second] != EMPTY);
    hasContainer = board[position.first][position.second];
    board[position.first][position.second] = EMPTY;
    path.push_back('P');
  }
  void release(vvi& board, unordered_set<int>& exportedSet) {
    path.push_back('Q');
    // assert(board[position.first][position.second] == EMPTY);
    if (position.second == 4) {
      exportedSet.insert(hasContainer);
    } else {
      board[position.first][position.second] = hasContainer;
    }
    hasContainer = -1;
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
    debug(id, position, hasContainer);
  }
};

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

  State() {}

  State(vvi argBoard, vector<Crane> argCraneList, vector<deque<int>> argA,
        unordered_set<int> argExportedSet)
      : board(argBoard),
        craneList(argCraneList),
        A(argA),
        exportedSet(argExportedSet) {}

  // ゲームの終了判定
  bool isDone() const {
    /*処理*/
    rep(i, 5) if (targetContainer[i] != -1) return false;
    return true;
  }

  // 探索用の盤面評価をする
  void evaluateScore(string moves) {
    if (moves == "LQQQQ") {
      rep(i, 5) {
        craneList[i].printCrane();
        debug(canValuableMove(craneList[i].position.first,
                              craneList[i].position.second,
                              craneList[i].hasContainer));
      }
    }
    int value = 0;
    int cntdot = 0;
    rep(i, 5) {
      int weight = (i == 0 ? 100 : 10);  // 大クレーン優先
      switch (moves[i]) {
        case 'P':
          // 移動の見込みがあるならプラス
          if (canValuableMove(craneList[i].position.first,
                              craneList[i].position.second,
                              craneList[i].hasContainer)) {
            value += weight;
          } else {
            value -= weight;
          }
          break;
        case 'Q':
          // 移動の見込みがないならプラス
          if (!canValuableMove(craneList[i].position.first,
                               craneList[i].position.second,
                               craneList[i].hasContainer)) {
            value += weight;
          } else {
            value -= weight;
          }
          break;
        case 'U':
          // 持っているなら、移動すべき方向ならプラス
          if (craneList[i].hasContainer != -1) {
            int destY = craneList[i].hasContainer / 5;
            if (destY < craneList[i].position.first) {
              value += weight;
            } else {
              value -= weight;
            }
          } else {
            // 持っていない時はなんでもいいや
            value += weight / 2;
          }
          break;
        case 'D':
          // 持っているなら、移動すべき方向ならプラス
          if (craneList[i].hasContainer != -1) {
            int destY = craneList[i].hasContainer / 5;
            if (destY > craneList[i].position.first) {
              value += weight;
            } else {
              value -= weight;
            }
          } else {
            // 持っていない時はなんでもいいや
            value += weight / 2;
          }
          break;
        case 'R':
          // 持っているなら、移動すべき方向ならプラス
          if (craneList[i].hasContainer != -1) {
            value += weight;
          } else {
            // 持っていない時もたまには右に行く？
            value += weight / 5;
          }
          break;
        case 'L':
          // 持っているなら、移動すべき方向ならプラス
          if (craneList[i].hasContainer != -1) {
            value -= weight * 2;
          } else {
            // 持っていない時も左に行く方がいいがち
            value += weight;
          }
          break;
        case '.':
          cntdot++;
          break;
      }
    }
    if (cntdot == 5) value = -1000;
    evaluated_score_ += value;
  }

  // 指定したactionでゲームを1ターン進める
  void advance(const string moves) {
    assert(moves.size() == 5);
    // 移動の実行
    rep(i, 5) {
      switch (moves[i]) {
        case 'P':
          craneList[i].hold(board);
          break;
        case 'Q':
          craneList[i].release(board, exportedSet);
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
  }

  // 現在の状況でプレイヤーが可能な行動を全て取得する
  vector<string> legalActions() const {
    vector<string> actions;
    /*処理*/
    string operation = "UDLR.PQ";

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
        if (!checkCollision(moves)) actions.push_back(moves);
        return;
      }

      // if (craneList[idx].position == craneList[idx].destination) {
      //   // 掴む離すは一択
      //   if (craneList[idx].hasContainer == -1) {
      //     moves.push_back('P');
      //     rec(rec, idx + 1, moves);
      //     moves.pop_back();
      //   } else {
      //     moves.push_back('Q');
      //     rec(rec, idx + 1, moves);
      //     moves.pop_back();
      //   }
      // } else {
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
        // 持っている時に更に持つことはできない
        if (c == 'P' && craneList[idx].hasContainer != -1) continue;
        // 空マスを持つことはできない
        if (c == 'P' && board[craneList[idx].position.first]
                             [craneList[idx].position.second] == EMPTY)
          continue;
        // 持ってなきゃ置けない
        if (c == 'Q' && craneList[idx].hasContainer == -1) continue;
        // 空きマス以外には置けない
        if (c == 'Q' && board[craneList[idx].position.first]
                             [craneList[idx].position.second] != EMPTY)
          continue;
        // targetじゃないなら5列目には動かさない
        if (c == 'R' && craneList[idx].position.second == 3 &&
            targetContainer[craneList[idx].hasContainer / 5] !=
                craneList[idx].hasContainer)
          continue;
        moves.push_back(c);
        rec(rec, idx + 1, moves);
        moves.pop_back();
      }
    };
    // };
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
                                                 const int beam_width,
                                                 const int64_t time_threshold) {
  auto time_keeper = TimeKeeper(time_threshold);
  auto legal_actions = state.legalActions();

  std::priority_queue<State> now_beam;
  State best_state;

  now_beam.push(state);
  for (int t = 0; t < 20; t++) {
    debug(t);
    std::priority_queue<State> next_beam;
    if (time_keeper.isTimeOver()) break;
    for (int i = 0; i < beam_width; i++) {
      if (now_beam.empty()) break;
      //
      State now_state = now_beam.top();
      now_beam.pop();
      if (t == 9 && i == 0) debug(now_state.board);

      // 合法手を取得
      legal_actions = now_state.legalActions();
      debug(t, now_state.evaluated_score_, legal_actions.size());
      // 全て試して、合法手を評価
      for (const auto& action : legal_actions) {
        State next_state = now_state;
        next_state.evaluated_score_ = now_state.evaluated_score_;
        next_state.evaluateScore(action);
        next_state.advance(action);
        next_beam.push(next_state);
        if (t == 9 && i == 0) debug(action, next_state.evaluated_score_);
      }
    }

    // TODO swapでよさそう
    swap(now_beam, next_beam);
    // now_beam = next_beam;
    // ゲーム終了してたら終了
    best_state = now_beam.top();
    // rep(i, 5) best_state.craneList[i].printCrane();
    if (best_state.isDone()) break;
  }
  vector<string> ret(5);
  best_state = now_beam.top();
  rep(i, 5) ret[i] = best_state.craneList[i].path;
  return ret;
}

int main() {
  /* input */
  INT(N);
  vector<deque<int>> A(N, deque<int>(N));
  rep(i, N) rep(j, N) cin >> A[i][j];

  int beam_width = 5;
  int time_threshold = 10000;

  /* initialize */
  vector board(5, vi(5, EMPTY));
  vi targetContainer = {0, 5, 10, 15, 20};
  // 最初の搬入
  rep(i, 5) {
    board[i][0] = A[i].front();
    A[i].pop_front();
  }
  // クレーン
  vector<Crane> craneList;
  unordered_set<int> exportedSet;
  rep(i, 5) craneList.emplace_back(i);

  State initState(board, craneList, A, exportedSet);

  /* solve */

  vector<string> ans =
      beamSearchActionWithTimeThreshold(initState, beam_width, time_threshold);

  /* output */
  rep(i, N) out(ans[i]);
}