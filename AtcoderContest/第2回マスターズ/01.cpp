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
  Board board_;
  vector<Action> ans_;
  // 今の座標
  int ny_, nx_;

  State() {};

  void initialize() { board_.baord_ = input_C; }

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

  void carry(char direction) {
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
    assert(0 <= ny_ && ny_ < 20 && 0 <= nx_ && nx_ < 20);
    assert(board_.baord_[ny_][nx_] == '.' || board_.baord_[ny_][nx_] == 'A' ||
           board_.baord_[ny_][nx_] == 'B' || board_.baord_[ny_][nx_] == 'C');

    if (board_.baord_[ny_][nx_] == '.') board_.baord_[ny_][nx_] = c;
  }

  void roll(char direction) {
    debug("roll", ny_, nx_, board_.baord_[ny_][nx_]);
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

  bool is_stone(int y = -1, int x = -1) {
    if (y == -1) return board_.baord_[ny_][nx_] == '@';
    return board_.baord_[y][x] == '@';
  }
  bool is_ore(char type, int y = -1, int x = -1) {
    if (y == -1) return board_.baord_[ny_][nx_] == type;
    return board_.baord_[y][x] == type;
  }
};

vector<Action> naive() {
  State state;
  state.initialize();

  auto [sy, sx] = get_hall_pos();
  state.ny_ = sy, state.nx_ = sx;
  for (int y = sy + 1; y < 20; y++) {
    debug(y, sx);
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
    debug(y, sx);
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
    debug(x);
    assert(state.ny_ == sy);
    state.move('R');
    // 邪魔なので穴に入れる
    if (state.is_stone() || state.is_ore('a')) state.roll('L');
    // 上下方向を愚直に処理する
    state.board_.debug_board();
    for (int y = sy + 1; y < 20; y++) {
      debug(y, x, state.board_.baord_[y][x]);
      if (state.is_stone(y, x) || state.is_ore('a', y, x)) {
        debug("要移動");
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
      debug(y, x, state.board_.baord_[y][x]);
      if (state.is_stone(y, x) || state.is_ore('a', y, x)) {
        debug("要移動");
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

  vector<Action> naive_ans = naive();

  exec_output(naive_ans);
}