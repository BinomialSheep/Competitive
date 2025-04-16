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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#pragma endregion header

int input_N = 20;
int input_M;
vector<string> input_C(20);

void exec_input() {
  cin >> input_N >> input_M;
  rep(i, 20) { cin >> input_C[i]; }
}

// 穴の位置を探す
pair<int, int> get_hall_pos(char c = 'A') {
  rep(i, 20) rep(j, 20) {
    if (input_C[i][j] == c) return make_pair(i, j);
  }
  assert(false);
}

class Board {
 public:
  vector<string> baord_;
  Board() {};

  void debug_board() { rep(i, 20) cerr << baord_[i] << endl; }
};

const int MOVE = 1, CARRY = 2, ROLL = 3;
class Action {
 public:
  int action_type_;
  char action_direction_;
  Action() {}
  Action(char t, char d) : action_type_(t), action_direction_(d) {};
};

class State {
 public:
  // 現在の盤面
  Board board_;
  // 現在の解
  vector<Action> ans_;
  // 現在の人の座標
  int ny_, nx_;

  State() {};

  void initialize() { board_.baord_ = input_C; }

  // 移動操作
  void move(char direction) {
    ans_.emplace_back(MOVE, direction);
    if (direction == 'R') {
      nx_++;
    } else if (direction == 'L') {
      nx_--;
    } else if (direction == 'U') {
      ny_--;
    } else if (direction == 'D') {
      ny_++;
    } else {
      assert(false);
    }
    assert(0 <= ny_ && ny_ < 20 && 0 <= nx_ && nx_ < 20);
  }

  // 隣接マスへ運ぶ操作
  void carry(char direction) {
    assert(is_carriable(direction));
    ans_.emplace_back(CARRY, direction);
    char c = board_.baord_[ny_][nx_];
    assert(c != '.');
    board_.baord_[ny_][nx_] = '.';
    if (direction == 'R') {
      nx_++;
    } else if (direction == 'L') {
      nx_--;
    } else if (direction == 'U') {
      ny_--;
    } else if (direction == 'D') {
      ny_++;
    } else {
      assert(false);
    }

    if (board_.baord_[ny_][nx_] == '.') board_.baord_[ny_][nx_] = c;
  }

  // 運ぶ先にものがないか
  bool is_carriable(char direction) {
    int y = ny_, x = nx_;
    if (direction == 'R') {
      x++;
    } else if (direction == 'L') {
      x--;
    } else if (direction == 'U') {
      y--;
    } else if (direction == 'D') {
      y++;
    } else {
      assert(false);
    }
    return 0 <= y && y < 20 && 0 <= x && x < 20 &&
           (board_.baord_[y][x] == '.' || board_.baord_[y][x] == 'A' ||
            board_.baord_[y][x] == 'B' || board_.baord_[y][x] == 'C');
  }

  // 転がす操作
  void roll(char direction) {
    ans_.emplace_back(ROLL, direction);
    char c = board_.baord_[ny_][nx_];
    assert(c != '.');
    board_.baord_[ny_][nx_] = '.';
    int y = ny_, x = nx_;
    int dy = 0, dx = 0;
    if (direction == 'R') {
      dx++;
    } else if (direction == 'L') {
      dx--;
    } else if (direction == 'U') {
      dy--;
    } else if (direction == 'D') {
      dy++;
    } else {
      assert(false);
    }

    while (true) {
      y += dy, x += dx;
      if (y < 0 || y >= 20 || x < 0 || 20 <= x) {
        y -= dy, x -= dx;
        board_.baord_[y][x] = c;
        break;
      }
      if (board_.baord_[y][x] == 'A' || board_.baord_[y][x] == 'B' ||
          board_.baord_[y][x] == 'C') {
        break;
      }
      if (board_.baord_[y][x] != '.') {
        y -= dy, x -= dx;
        board_.baord_[y][x] = c;
        break;
      }
    }
  }

  // 転がした場合、どこまで転がっていくか（盤面は更新しない）
  pair<int, int> virtual_roll(char direction) {
    char c = board_.baord_[ny_][nx_];
    assert(c != '.');
    int y = ny_, x = nx_;
    int dy = 0, dx = 0;
    if (direction == 'R') {
      dx++;
    } else if (direction == 'L') {
      dx--;
    } else if (direction == 'U') {
      dy--;
    } else if (direction == 'D') {
      dy++;
    } else {
      assert(false);
    }

    while (true) {
      y += dy, x += dx;
      if (y < 0 || y >= 20 || x < 0 || 20 <= x) {
        y -= dy, x -= dx;
        break;
      }
      if (board_.baord_[y][x] == 'A' || board_.baord_[y][x] == 'B' ||
          board_.baord_[y][x] == 'C') {
        break;
      }
      if (board_.baord_[y][x] != '.') {
        y -= dy, x -= dx;
        break;
      }
    }
    return make_pair(y, x);
  }

  bool is_stone(int y = -1, int x = -1) {
    if (y == -1) return board_.baord_[ny_][nx_] == '@';
    return board_.baord_[y][x] == '@';
  }
  bool is_ore(char type, int y = -1, int x = -1) {
    if (y == -1) return board_.baord_[ny_][nx_] == type;
    return board_.baord_[y][x] == type;
  }
  bool is_hall(char type, int y, int x) {
    if (type == 'Z') {
      return board_.baord_[y][x] == 'A' || board_.baord_[y][x] == 'B' ||
             board_.baord_[y][x] == 'C';
    } else {
      return board_.baord_[y][x] == type;
    }
  }
};

vector<Action> naive() {
  State state;
  state.initialize();

  auto [sy, sx] = get_hall_pos();
  state.ny_ = sy, state.nx_ = sx;
  for (int y = sy + 1; y < 20; y++) {
    // debug(y, sx);
    if (state.is_stone(y, sx) || state.is_ore('a', y, sx)) {
      // そこまで動いて、下に戻す
      while (state.ny_ != y) {
        state.move('D');
      }
      while (state.ny_ != sy) {
        state.carry('U');
      }
    }
  }
  for (int y = sy - 1; 0 <= y; y--) {
    // debug(y, sx);
    if (state.is_stone(y, sx) || state.is_ore('a', y, sx)) {
      // そこまで動いて、下に戻す
      while (state.ny_ != y) {
        state.move('U');
      }
      while (state.ny_ != sy) {
        state.carry('D');
      }
    }
  }

  // まずは右側を処理する
  for (int x = sx + 1; x < 20; x++) {
    // debug(x);
    assert(state.ny_ == sy);
    state.move('R');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('L');
    // 上下方向を愚直に処理する
    for (int y = sy + 1; y < 20; y++) {
      // debug(y, x, state.board_.baord_[y][x]);
      if (state.is_stone(y, x) || state.is_ore('a', y, x)) {
        // debug("要移動");
        // そこまで動いて、下に戻す
        while (state.ny_ != y) {
          state.move('D');
        }
        while (state.ny_ != sy) {
          state.carry('U');
        }
        state.roll('L');
      }
    }
    for (int y = sy - 1; 0 <= y; y--) {
      // debug(y, x, state.board_.baord_[y][x]);
      if (state.is_stone(y, x) || state.is_ore('a', y, x)) {
        // debug("要移動");
        // そこまで動いて、下に戻す
        while (state.ny_ != y) {
          state.move('U');
        }
        while (state.ny_ != sy) {
          state.carry('D');
        }
        state.roll('L');
      }
    }
  }
  // スタート位置まで戻る
  while (state.nx_ != sx) state.move('L');
  // 次に左側を処理する
  for (int x = sx - 1; 0 <= x; x--) {
    assert(state.ny_ == sy);
    state.move('L');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('R');
    // 上下方向を愚直に処理する
    for (int y = sy + 1; y < 20; y++) {
      if (state.is_stone(y, x) || state.is_ore('a', y, x)) {
        // そこまで動いて、下に戻す
        while (state.ny_ != y) {
          state.move('D');
        }
        while (state.ny_ != sy) {
          state.carry('U');
        }
        state.roll('R');
      }
    }
    for (int y = sy - 1; 0 <= y; y--) {
      if (state.is_stone(y, x) || state.is_ore('a', y, x)) {
        // そこまで動いて、下に戻す
        while (state.ny_ != y) {
          state.move('U');
        }
        while (state.ny_ != sy) {
          state.carry('D');
        }
        state.roll('R');
      }
    }
  }
  return state.ans_;
}

unordered_map<char, char> rev_dir = {
    {'U', 'D'}, {'D', 'U'}, {'R', 'L'}, {'L', 'R'}};

vector<Action> naive_2() {
  State state;
  state.initialize();

  // 初期座標は穴Aの位置
  auto [sy, sx] = get_hall_pos();
  state.ny_ = sy, state.nx_ = sx;

  // 列xの処理を行う（roll_dirは転がす方向）
  auto column_process = [&](int x, char roll_dir = 'Z') {
    // 鉱石がある場所(y, x)まで移動して鉱石を穴に入れる
    auto f = [&](int y) {
      // 鉱石がある方向
      char ud_dir = sy < y ? 'D' : 'U';
      while (state.ny_ != y) {
        state.move(ud_dir);
        // 途中で岩があったら左右どちらかにずらす
        if (state.is_stone()) {
          while (true) {
            if (roll_dir != 'Z') {
              if (state.is_carriable(roll_dir)) {
                state.carry(roll_dir);
                state.move(rev_dir[roll_dir]);
                break;
              } else if (state.is_carriable(rev_dir[roll_dir])) {
                state.carry(rev_dir[roll_dir]);
                state.move(roll_dir);
                break;
              }
            } else {
              if (state.is_carriable('L')) {
                state.carry('L');
                state.move('R');
                break;
              } else if (state.is_carriable('R')) {
                state.carry('R');
                state.move('L');
                break;
              }
            }
            // 左右どちらにも動かせないので、1手穴側に戻る
            state.carry(rev_dir[ud_dir]);
            if (state.ny_ == sy) {
              // sy行まで戻ったら穴に投げる
              if (roll_dir != 'Z') state.roll(roll_dir);
              break;
            }
          }
        }
      }
      // 穴がある行まで戻る
      while (state.ny_ != sy) state.carry(rev_dir[ud_dir]);
      // 穴に向けて転がす
      if (roll_dir != 'Z') state.roll(roll_dir);
    };

    // 下側の処理
    for (int y = sy + 1; y < 20; y++) {
      if (state.is_ore('a', y, x)) f(y);
    }
    // 上側の処理
    for (int y = sy - 1; 0 <= y; y--) {
      if (state.is_ore('a', y, x)) f(y);
    }
  };

  column_process(sx);

  // まずは右側を処理する
  for (int x = sx + 1; x < 20; x++) {
    assert(state.ny_ == sy);
    state.move('R');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('L');
    // 上下方向を愚直に処理する
    column_process(x, 'L');
  }
  // スタート位置まで戻る
  while (state.nx_ != sx) state.move('L');
  // 次に左側を処理する
  for (int x = sx - 1; 0 <= x; x--) {
    assert(state.ny_ == sy);
    state.move('L');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('R');
    // 上下方向を愚直に処理する
    column_process(x, 'R');
  }
  state.board_.debug_board();
  return state.ans_;
}

vector<Action> greedy_3() {
  State state;
  state.initialize();

  // 初期座標は穴Aの位置
  auto [sy, sx] = get_hall_pos();
  state.ny_ = sy, state.nx_ = sx;

  // 列xの処理を行う（roll_dirは転がす方向）
  auto column_process = [&](int x, char roll_dir = 'Z') {
    // 鉱石がある場所(y, x)まで移動して鉱石を穴に入れる
    auto f = [&](int y) {
      // 鉱石がある方向
      char ud_dir = sy < y ? 'D' : 'U';
      while (state.ny_ != y) {
        state.move(ud_dir);
        // 途中で岩があったら左右どちらかにずらす
        if (state.is_stone()) {
          while (true) {
            if (roll_dir != 'Z') {
              if (state.is_carriable(roll_dir)) {
                state.roll(roll_dir);
                break;
              } else if (state.is_carriable(rev_dir[roll_dir])) {
                state.roll(rev_dir[roll_dir]);
                break;
              }
            } else {
              if (state.is_carriable('L')) {
                state.roll('L');
                break;
              } else if (state.is_carriable('R')) {
                state.roll('R');
                break;
              }
            }
            // 左右どちらにも動かせない場合

            // 転がしたらどこまでいくのか
            auto [y2, x2] = state.virtual_roll(rev_dir[ud_dir]);
            debug(y2, x2, y, x, sy, sx, ud_dir);
            if (sx == x || (ud_dir == 'D' && y2 < sy) ||
                ((ud_dir == 'U' && y2 > sy))) {
              state.roll(rev_dir[ud_dir]);
              break;
            }
            state.carry(rev_dir[ud_dir]);
            if (state.ny_ == sy) {
              // sy行まで戻ったら穴に投げる
              if (roll_dir != 'Z') state.roll(roll_dir);
              break;
            }
          }
        }
      }
      // 穴がある行まで戻る
      while (state.ny_ != sy) state.carry(rev_dir[ud_dir]);
      // 穴に向けて転がす
      if (roll_dir != 'Z') state.roll(roll_dir);
    };

    // 広い方からやる（あとで安全に岩を投げるため）
    if (sy < 10) {
      // 上側の処理
      for (int y = sy - 1; 0 <= y; y--) {
        if (state.is_ore('a', y, x)) f(y);
      }
      // 下側の処理
      for (int y = sy + 1; y < 20; y++) {
        if (state.is_ore('a', y, x)) f(y);
      }
    } else {
      // 下側の処理
      for (int y = sy + 1; y < 20; y++) {
        if (state.is_ore('a', y, x)) f(y);
      }
      // 上側の処理
      for (int y = sy - 1; 0 <= y; y--) {
        if (state.is_ore('a', y, x)) f(y);
      }
    }
  };

  column_process(sx);

  // まずは右側を処理する
  for (int x = sx + 1; x < 20; x++) {
    assert(state.ny_ == sy);
    state.move('R');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('L');
    // 上下方向を愚直に処理する
    column_process(x, 'L');
  }
  // スタート位置まで戻る
  while (state.nx_ != sx) state.move('L');
  // 次に左側を処理する
  for (int x = sx - 1; 0 <= x; x--) {
    assert(state.ny_ == sy);
    state.move('L');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('R');
    // 上下方向を愚直に処理する
    column_process(x, 'R');
  }
  state.board_.debug_board();
  return state.ans_;
}

void exec_output(const vector<Action>& ans) {
  for (auto& v : ans) {
    cout << v.action_type_ << " " << v.action_direction_ << endl;
  }
}

int main() {
  exec_input();

  vector<Action> ans = naive();
  vector<Action> ans_2 = naive_2();
  vector<Action> ans_3 = greedy_3();
  cerr << "ans: " << ans.size() << endl;
  cerr << "ans_2: " << ans_2.size() << endl;
  cerr << "ans_3: " << ans_3.size() << endl;

  exec_output(ans_3);
}