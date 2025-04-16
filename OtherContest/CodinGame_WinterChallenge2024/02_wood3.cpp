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
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

// 時間を管理するクラス
class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限をミリ秒単位で指定してインスタンスをつくる。
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}

  // インスタンス生成した時から指定した時間制限を超過したか判定する。
  bool isTimeOver() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count() >=
           time_threshold_;
  }
};

enum WinningStatus {
  WIN,
  LOSE,
  DRAW,
  NONE,
};

enum EntytyType {
  WALL,
  ROOT,
  BASIC,
  HARVESTER,
  A,
  B,
  C,
  D,
};

int grid_height;  // rows in the game grid
int grid_width;   // columns in the game grid

vector<int> dy = {1, -1, 0, 0}, dx = {0, 0, 1, -1};
// こっちの方を向いているべき
vector<string> harvester_dist = {"N", "S", "W", "E"};

class Entyty {
 public:
  int x_, y_;
  // WALL, ROOT, BASIC, TENTACLE, HARVESTER, SPORER, A, B, C, D
  string type_;
  // 1 if your organ, 0 if enemy organ, -1 if neither
  int owner_;
  // id of this entity if it's an organ, 0 otherwise
  int organ_id_;
  // N,E,S,W or X if not an organ
  string organ_dir_;
  int organ_parent_id_, organ_root_id_;

  Entyty() {};

  // 空白マス用の設定
  void initial_entyty(int y, int x) {
    y_ = y, x_ = x;
    type_ = "NONE";
    owner_ = -1;
    organ_id_ = -1;
    organ_dir_ = "Z";
    organ_parent_id_ = organ_root_id_ = -1;
  }

  void input_entyty() {
    cin >> x_ >> y_ >> type_ >> owner_ >> organ_id_ >> organ_dir_ >>
        organ_parent_id_ >> organ_root_id_;
    cin.ignore();
  }
};

class ActionType {
 public:
  int y_, x_, id_;
  string type_, dir_;
  ActionType(int y, int x, int id, string type)
      : y_(y), x_(x), id_(id), type_(type) {}
  ActionType(int y, int x, int id, string type, string dir)
      : y_(y), x_(x), id_(id), type_(type), dir_(dir) {}

  void print() {
    cout << "GROW " << id_ << " " << x_ << " " << y_ << " " << type_;
    if (type_ == "HARVESTER") cout << " " << dir_;
    cout << endl;
  }
  void debug_print() {
    cerr << "GROW " << id_ << " " << x_ << " " << y_ << " " << type_;
    if (type_ == "HARVESTER") cerr << " " << dir_;
    cerr << endl;
  }
};

class State {
 public:
  vector<vector<Entyty>> board;
  int my_a_, my_b_, my_c_, my_d_;
  int opp_a_, opp_b_, opp_c_, opp_d_;
  set<pair<int, int>> my_harvest_, opp_harvest_;
  bool is_my_turn_ = true;
  int turn_ = -1;
  int now_organ_id_ = 1;
  bool is_my_end_ = false;
  bool is_opp_end_ = false;

  State() {};

  void init_board(vector<Entyty>& entyty_list) {
    board.resize(grid_height);
    rep(i, grid_height) board[i].resize(grid_width);
    rep(y, grid_height) rep(x, grid_width) { board[y][x].initial_entyty(y, x); }
    for (auto& e : entyty_list) board[e.y_][e.x_] = e;

    rep(y, grid_height) rep(x, grid_width) {
      if (board[y][x].type_ == "A") {
        rep(di, 4) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (y2 >= 0 && x2 >= 0 && y2 < grid_height && x2 < grid_width) {
            if (board[y2][x2].type_ == "HARVESTER" &&
                board[y2][x2].organ_dir_ == harvester_dist[di]) {
              if (board[y2][x2].owner_ == 1) my_harvest_.emplace(y, x);
              if (board[y2][x2].owner_ == 0) opp_harvest_.emplace(y, x);
            }
          }
        }
      }
    }
    cerr << "init_harvest_size:" << my_harvest_.size() << opp_harvest_.size()
         << endl;
  }

  void set_abcd(int a, int b, int c, int d, int oa, int ob, int oc, int od) {
    my_a_ = a, my_b_ = b, my_c_ = c, my_d_ = d, opp_a_ = oa, opp_b_ = ob,
    opp_c_ = oc, opp_d_ = od;
  }

  // 指定したactionでゲームを1ターン進め、次のプレイヤー視点の盤面にする
  void advance(ActionType action) {
    if (board[action.y_][action.x_].type_ == "A") {
      my_harvest_.erase(make_pair(action.y_, action.x_));
      opp_harvest_.erase(make_pair(action.y_, action.x_));
      if (is_my_turn_) {
        my_a_ += 3;
      } else {
        opp_a_ += 3;
      }
    }
    if (action.type_ == "BASIC") {
      if (is_my_turn_) {
        my_a_ -= 1;
      } else {
        opp_a_ -= 1;
      }
      board[action.y_][action.x_].type_ = "BASIC";
      assert(board[action.y_][action.x_].owner_ = -1);
      board[action.y_][action.x_].owner_ = is_my_turn_ ? 1 : 0;
      board[action.y_][action.x_].organ_id_ = now_organ_id_++;
    } else if (action.type_ == "HARVESTER") {
      if (is_my_turn_) {
        my_c_ -= 1, my_d_ -= 1;
      } else {
        opp_c_ -= 1, opp_d_ -= 1;
      }
      board[action.y_][action.x_].type_ = "HARVESTER";
      assert(board[action.y_][action.x_].owner_ = -1);
      board[action.y_][action.x_].owner_ = is_my_turn_ ? 1 : 0;
      board[action.y_][action.x_].organ_id_ = now_organ_id_++;
      board[action.y_][action.x_].organ_dir_ = action.dir_;

      int y2 = action.y_, x2 = action.x_;
      if (action.dir_ == "N") {
        y2--;
      } else if (action.dir_ == "S") {
        y2++;
      } else if (action.dir_ == "E") {
        x2++;
      } else if (action.dir_ == "W") {
        x2--;
      } else {
        assert(false);
      }
      if (y2 >= 0 && x2 >= 0 && y2 < grid_height && x2 < grid_width &&
          board[y2][x2].type_ == "A") {
        if (is_my_turn_) {
          my_harvest_.emplace(y2, x2);
        } else {
          opp_harvest_.emplace(y2, x2);
        }
      }
    } else {
      assert(false);
    }
    if (is_my_turn_) {
      my_a_ += (int)my_harvest_.size();
    } else {
      opp_a_ += (int)opp_harvest_.size();
    }
    is_my_turn_ ^= 1;
    if (is_my_turn_) turn_++;
  }

  void pass() {
    if (is_my_turn_) {
      my_a_ += (int)my_harvest_.size();
      is_my_end_ = true;
    } else {
      opp_a_ += (int)opp_harvest_.size();
      is_opp_end_ = true;
    }
    is_my_turn_ ^= 1;
    if (is_my_turn_) turn_++;
  }

  WinningStatus get_winning_status() {
    if (!is_my_turn_) return WinningStatus::NONE;
    if (turn_ <= 100 && (!is_my_end_ || !is_opp_end_))
      return WinningStatus::NONE;
    int my_cnt = 0, opp_cnt = 0;
    rep(y, grid_height) rep(x, grid_width) {
      if (board[y][x].owner_ == 1) my_cnt++;
      if (board[y][x].owner_ == 0) opp_cnt++;
    }
    // cerr << "organ cnt:" << my_cnt << " " << opp_cnt << " " << turn_ << endl;
    if (my_cnt > opp_cnt) {
      return WinningStatus::WIN;
    } else if (my_cnt < opp_cnt) {
      return WinningStatus::LOSE;
    } else {
      return WinningStatus::DRAW;
    }
  }

  vector<ActionType> legal_actions() {
    // cerr << "abcd:" << my_a_ << my_b_ << my_c_ << my_d_ << endl;
    vector<ActionType> ret;

    rep(y, grid_height) rep(x, grid_width) {
      // 自分がオーナーだったらその隣接マスに動かせる
      if (is_my_turn_ && board[y][x].owner_ == 1) {
        // cerr << "owner: " << x << " " << y << endl;
        rep(di, dy.size()) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (y2 >= 0 && x2 >= 0 && y2 < grid_height && x2 < grid_width) {
            if (board[y2][x2].type_ != "WALL" && board[y2][x2].owner_ == -1) {
              // cerr << "next: " << x2 << " " << y2 << endl;
              if (my_a_) {
                ret.emplace_back(y2, x2, board[y][x].organ_id_, "BASIC");
              }
              if (my_c_ && my_d_) {
                // "N"
                if (y2 - 1 >= 0 && board[y2 - 1][x2].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "N");
                }
                // "W"
                if (x2 - 1 >= 0 && board[y2][x2 - 1].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "W");
                }
                // "E"
                if (x2 + 1 >= 0 && board[y2][x2 + 1].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "E");
                }
                // "S"
                if (y2 + 1 >= 0 && board[y2 + 1][x2].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "S");
                }
                // BASICが出来ない場合も仕方なく
                if (my_a_ == 0) {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "N");
                }
              }
            }
          }
        }
      } else if (!is_my_turn_ && board[y][x].owner_ == 0) {
        // cerr << "owner: " << x << " " << y << endl;
        rep(di, dy.size()) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (y2 >= 0 && x2 >= 0 && y2 < grid_height && x2 < grid_width) {
            if (board[y2][x2].type_ != "WALL" && board[y2][x2].owner_ == -1) {
              // cerr << "next: " << x2 << " " << y2 << endl;
              if (opp_a_) {
                ret.emplace_back(y2, x2, board[y][x].organ_id_, "BASIC");
              }
              if (opp_c_ && opp_d_) {
                // "N"
                if (y2 - 1 >= 0 && board[y2 - 1][x2].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "N");
                }
                // "W"
                if (x2 - 1 >= 0 && board[y2][x2 - 1].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "W");
                }
                // "E"
                if (x2 + 1 >= 0 && board[y2][x2 + 1].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "E");
                }
                // "S"
                if (y2 + 1 >= 0 && board[y2 + 1][x2].type_ == "A") {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "S");
                }
                // BASICが出来ない場合も仕方なく
                if (opp_a_ == 0) {
                  ret.emplace_back(y2, x2, board[y][x].organ_id_, "HARVESTER",
                                   "N");
                }
              }
            }
          }
        }
      }
    }

    if (ret.size() == 0) {
      if (is_my_turn_) {
        // assert(my_a_ == 0 && (my_c_ == 0 || my_d_ == 0));
        cerr << "my ret.size() == 0: " << my_a_ << my_b_ << my_c_ << my_d_
             << endl;
      } else {
        // assert(opp_a_ == 0 && (opp_c_ == 0 || opp_d_ == 0));
        cerr << "opp ret.size() == 0: " << opp_a_ << opp_b_ << opp_c_ << opp_d_
             << endl;
      }
    }

    // cerr << ret.size() << endl;
    // for (auto act : ret) {
    //   cerr << "(" << act.x_ << "," << act.y_ << "," << act.id_ << ") ";
    // }
    // cerr << endl;

    return ret;
  }

  void print_board() {
    rep(y, grid_height) rep(x, grid_width) {
      cerr << x << " " << y << endl;
      cerr << "type:" << board[y][x].type_ << ", owner:" << board[y][x].owner_
           << ", oragan_id:" << board[y][x].organ_id_
           << ", oragan_dir:" << board[y][x].organ_dir_
           << ", oragan_parent_id:" << board[y][x].organ_parent_id_
           << ", oragan_root_id:" << board[y][x].organ_root_id_ << endl;
    }
  }
};

namespace montecarlo {

int playout(State& state) {
  // 既に決着しているならそれを返す
  WinningStatus winningStatus = state.get_winning_status();
  if (winningStatus == WinningStatus::WIN) return 1;
  if (winningStatus == WinningStatus::LOSE) return -1;
  if (winningStatus == WinningStatus::DRAW) return 0;

  // 合法手を取得
  auto legal_actions = state.legal_actions();
  // 置く場所がない時は次へ進む
  if (legal_actions.empty()) {
    state.pass();
  } else {
    // ランダムプレイ
    ActionType action = legal_actions[randXor() % (legal_actions.size())];
    state.advance(action);
  }

  return -playout(state);
}

ActionType exec_montecalro(State& state, const int64_t time_threshold = 40) {
  auto time_keeper = TimeKeeper(time_threshold);
  int turn = 0;
  int cnt = 0;

  vector<ActionType> legal_actions = state.legal_actions();
  vector<int> actions_score(legal_actions.size());

  for (;; turn++) {
    if (time_keeper.isTimeOver()) break;
    rep(i, legal_actions.size()) {
      cnt++;
      State new_state = state;
      new_state.advance(legal_actions[i]);
      actions_score[i] -= playout(new_state);
    }
  }
  cerr << "cnt: " << cnt << endl;
  rep(i, legal_actions.size()) {
    legal_actions[i].debug_print();
    cerr << actions_score[i] << endl;
  }

  int idx = 0, max_score = -1e9;
  rep(i, legal_actions.size()) if (chmax(max_score, actions_score[i])) idx = i;
  return legal_actions[idx];
}

}  // namespace montecarlo

int main() {
  cin >> grid_width >> grid_height;
  cin.ignore();

  // game loop
  int turn = 0;
  while (1) {
    turn++;
    int entity_count;
    cin >> entity_count;
    cin.ignore();

    cerr << "entity_count:" << entity_count << endl;

    vector<Entyty> entyty_list(entity_count);
    for (int i = 0; i < entity_count; i++) {
      Entyty entyty;
      entyty.input_entyty();
      entyty_list[i] = entyty;
    }

    INT(my_a, my_b, my_c, my_d);
    INT(opp_a, opp_b, opp_c, opp_d);
    INT(required_actions_count);
    cerr << "required_actions_count:" << required_actions_count << endl;
    cin.ignore();

    State state;
    state.init_board(entyty_list);
    // state.print_board();
    state.set_abcd(my_a, my_b, my_c, my_d, opp_a, opp_b, opp_c, opp_d);
    state.turn_ = turn;

    for (int i = 0; i < required_actions_count; i++) {
      vector<ActionType> legal_action_list = state.legal_actions();

      if (legal_action_list.size()) {
        ActionType ans = montecarlo::exec_montecalro(state);
        ans.print();
      } else {
        cout << "WAIT" << endl;
      }
    }
  }
}