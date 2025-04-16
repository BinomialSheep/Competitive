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

int grid_height;  // rows in the game grid
int grid_width;   // columns in the game grid

vector<int> dy = {1, -1, 0, 0}, dx = {0, 0, 1, -1};

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
  ActionType(int y, int x, int id) : y_(y), x_(x), id_(id) {}

  void print() {
    cout << "GROW " << id_ << " " << x_ << " " << y_ << " BASIC" << endl;
  }
};

class State {
 public:
  vector<vector<Entyty>> board;

  State() {};

  void init_board(vector<Entyty>& entyty_list) {
    board.resize(grid_height);
    rep(i, grid_height) board[i].resize(grid_width);
    rep(y, grid_height) rep(x, grid_width) { board[y][x].initial_entyty(y, x); }
    for (auto& e : entyty_list) board[e.y_][e.x_] = e;
  }

  vector<ActionType> legal_actions() {
    vector<ActionType> ret;

    rep(y, grid_height) rep(x, grid_width) {
      // 自分がオーナーだったらその隣接マスに動かせる
      if (board[y][x].owner_ == 1) {
        cerr << "owner: " << x << " " << y << endl;
        rep(di, dy.size()) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (y2 >= 0 && x2 >= 0 && y2 < grid_height && x2 < grid_width) {
            if (board[y2][x2].type_ != "WALL" && board[y2][x2].owner_ == -1) {
              cerr << "next: " << x2 << " " << y2 << endl;
              ret.emplace_back(y2, x2, board[y][x].organ_id_);
            }
          }
        }
      }
    }

    cerr << ret.size() << endl;
    for (auto act : ret) {
      cerr << "(" << act.x_ << "," << act.y_ << "," << act.id_ << ") ";
    }
    cerr << endl;

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

int main() {
  cin >> grid_width >> grid_height;
  cin.ignore();

  // game loop
  while (1) {
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
    cerr << "set entyty_list is Done" << endl;

    State state;
    state.init_board(entyty_list);
    // state.print_board();
    cerr << "state.init_board is Done" << endl;

    INT(my_a, my_b, my_c, my_d);
    INT(opp_a, opp_b, opp_c, opp_d);
    INT(required_actions_count);
    cerr << "required_actions_count:" << required_actions_count << endl;
    cin.ignore();

    vector<ActionType> legal_action_list = state.legal_actions();

    for (int i = 0; i < required_actions_count; i++) {
      if (legal_action_list.size()) {
        legal_action_list[0].print();
      } else {
        cout << "WAIT" << endl;
      }
    }
  }
}