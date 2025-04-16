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

constexpr int input_N = 50, input_T = 800;
int input_M, input_K;
class Citizen {
 public:
  int idx_, sy_, sx_, ty_, tx_;
  Citizen() : idx_(0), sy_(0), sx_(0), ty_(0), tx_(0) {}
  Citizen(int idx, int sy, int sx, int ty, int tx)
      : idx_(idx), sy_(sy), sx_(sx), ty_(ty), tx_(tx) {};

  void debug_citizen() {
    cerr << idx_ << " " << sy_ << " " << sx_ << " " << ty_ << " " << tx_
         << endl;
  }
};
array<Citizen, 1600> input_citizen_list;

constexpr array<int, 13> dy13 = {-2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2};
constexpr array<int, 13> dx13 = {0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0};
constexpr array<int, 13> dy4 = {-1, 1, 0, 0};
constexpr array<int, 13> dx4 = {0, 0, -1, 1};
// ある土地に駅が立ったら利用する人々
array<array<vector<int>, 50>, 50> land_user_list;

void exec_input() {
  int _;
  cin >> _ >> input_M >> input_K >> _;
  rep(i, input_M) {
    INT(sy, sx, ty, tx);
    input_citizen_list[i] = Citizen(i, sy, sx, ty, tx);
  }
}

void calc_land_user_list() {
  rep(i, input_M) {
    rep(di, 13) {
      int y1 = input_citizen_list[i].sy_ + dy13[di];
      int x1 = input_citizen_list[i].sx_ + dx13[di];
      int y2 = input_citizen_list[i].ty_ + dy13[di];
      int x2 = input_citizen_list[i].tx_ + dx13[di];
      if (0 <= y1 && y1 < input_N && 0 <= x1 && x1 < input_N)
        land_user_list[y1][x1].push_back(i);
      if (0 <= y2 && y2 < input_N && 0 <= x2 && x2 < input_N)
        land_user_list[y2][x2].push_back(i);
    }
  }
}

constexpr int STATION = 0, WAIT = -1, TRACK_LR = 1, TRACK_TB = 2, TRACK_LB = 3,
              TRACK_LT = 4, TRACK_RT = 5, TRACK_RB = 6;
class Operation {
 public:
  int type_, y_, x_;

  Operation(int type) : type_(type) {}
  Operation(int type, int y, int x) : type_(type), y_(y), x_(x) {}
};

void exec_output(vector<Operation> operation_list) {
  assert(operation_list.size() == input_T);
  for (auto& ope : operation_list) {
    if (ope.type_ == STATION) {
      out(0, ope.y_, ope.x_);
    } else if (ope.type_ == WAIT) {
      out(-1);
    } else {
      out(ope.type_, ope.y_, ope.x_);
    }
  }
}

const int EMPTY = -1;
class Board {
 public:
  array<array<int, 50>, 50> board_;

  // 駅で繋がっている座標同士をdsuで管理するとよさそう
  dsu connected;
  // 通勤可能な人（arrayにした方が速い）
  unordered_set<int> commutable_citizens_;

  Board() {
    rep(i, 50) rep(j, 50) board_[i][j] = EMPTY;
    connected = dsu(2500);
  }

  void errect(int y, int x, int type) {
    assert(board_[y][x] == EMPTY);
    board_[y][x] = type;
  }
};

// 2点を線路のみを使って最短距離で繋ぐ
array<array<int, 50>, 50> distance_points;
array<array<int, 50>, 50> parent_direction;
vector<Operation> connect_station(int sy, int sx, int ty, int tx,
                                  Board& board) {
  vector<Operation> ret;

  rep(i, 50) rep(j, 50) distance_points[i][j] = 1e9;
  distance_points[sy][sx] = 0;
  // 復元用。いつか高速化する
  // 01BFSをするべき
  deque<pair<int, int>> dq;
  dq.emplace_back(sy, sx);

  bool is_reach = false;
  while ((int)dq.size() && !is_reach) {
    assert(dq.size());
    auto [y, x] = dq.front();
    dq.pop_front();

    // TODO：そこが駅だったら、繋がっている他の駅を距離0としてpush_front

    rep(di, 4) {
      int ny = y + dy4[di], nx = x + dx4[di];
      if (0 <= ny && ny < 50 && 0 <= nx && nx < 50) {
        // TODO：道をつぶして駅にすることもできるが、ここでは考慮しない
        if (board.board_[ny][nx] != EMPTY && board.board_[ny][nx] != STATION)
          continue;
        if (chmin(distance_points[ny][nx], distance_points[y][x] + 1)) {
          parent_direction[ny][nx] = di;
          if (ny == ty && nx == tx) {
            is_reach = true;
            break;
          }
          dq.emplace_back(ny, nx);
        }
      }
    }
  }
  if (!is_reach) {
    // debug("到達できない");
    return ret;
  }
  const int TOP = 0, BOTTOM = 1, LEFT = 2, RIGHT = 3;

  // 復元
  int last = parent_direction[ty][tx];
  int y = ty, x = tx;
  while (true) {
    // 親から見たら上に移動した（復元するには下に移動する）
    if (parent_direction[y][x] == TOP)
      y++;
    else if (parent_direction[y][x] == BOTTOM)
      y--;
    else if (parent_direction[y][x] == LEFT)
      x++;
    else if (parent_direction[y][x] == RIGHT)
      x--;

    if (y == sy && x == sx) break;

    if ((last == BOTTOM && parent_direction[y][x] == BOTTOM) ||
        (last == TOP && parent_direction[y][x] == TOP)) {
      ret.emplace_back(TRACK_TB, y, x);
    } else if ((last == LEFT && parent_direction[y][x] == LEFT) ||
               (last == RIGHT && parent_direction[y][x] == RIGHT)) {
      ret.emplace_back(TRACK_LR, y, x);
    } else if ((last == RIGHT && parent_direction[y][x] == BOTTOM) ||
               (last == TOP && parent_direction[y][x] == LEFT)) {
      ret.emplace_back(TRACK_RT, y, x);
    } else if ((last == RIGHT && parent_direction[y][x] == TOP) ||
               (last == BOTTOM && parent_direction[y][x] == LEFT)) {
      ret.emplace_back(TRACK_RB, y, x);
    } else if ((last == LEFT && parent_direction[y][x] == BOTTOM) ||
               (last == TOP && parent_direction[y][x] == RIGHT)) {
      ret.emplace_back(TRACK_LT, y, x);
    } else if ((last == LEFT && parent_direction[y][x] == TOP) ||
               (last == BOTTOM && parent_direction[y][x] == RIGHT)) {
      ret.emplace_back(TRACK_LB, y, x);
    } else {
      // debug(last, parent_direction[y][x]);
      assert(false);
    }
    last = parent_direction[y][x];
  }

  return ret;
}

/**
 * 初投用。
 * 初期状態で距離が近いペアから順に繋いでいく（距離の更新とかはしない）
 */
vector<Operation> naive() {
  vector<Operation> ret;
  // (距離, 市民idx)
  vector<pair<int, int>> ps;
  rep(i, input_M) {
    int dist = abs(input_citizen_list[i].sy_ - input_citizen_list[i].ty_) +
               abs(input_citizen_list[i].sx_ - input_citizen_list[i].tx_);
    ps.emplace_back(dist, i);
  }
  sort(all(ps));
  // 所持金と、現在の1ターンあたりの集金額
  int money = input_K, income = 0;
  Board board;

  auto wait_turn = [&]() {
    ret.emplace_back(WAIT);
    money += income;
  };

  auto errect_turn = [&](int y, int x, int type) {
    ret.emplace_back(type, y, x);
    board.errect(y, x, type);
    money -= type == STATION ? 5000 : 100;
    money += income;
  };

  for (auto [_, idx] : ps) {
    // 既に通勤可能なら繋がない
    if (board.commutable_citizens_.count(idx)) continue;
    int sy = input_citizen_list[idx].sy_, sx = input_citizen_list[idx].sx_,
        ty = input_citizen_list[idx].ty_, tx = input_citizen_list[idx].tx_;
    // なんか立っていたらやめておく（TODO：実は辞める必要ないらしいが）
    if (board.board_[sy][sx] != EMPTY || board.board_[ty][tx] != EMPTY)
      continue;
    // input_citizen_list[idx].debug_citizen();

    while (money < 5000) wait_turn();
    errect_turn(sy, sx, STATION);
    while (money < 5000) wait_turn();
    errect_turn(ty, tx, STATION);
    vector<Operation> opes = connect_station(sy, sx, ty, tx, board);

    for (auto& ope : opes) {
      // debug(ope.type_, ope.y_, ope.x_, money, income);
      // もう駅が立ってたら道を立てる必要なし
      if (board.board_[ope.y_][ope.x_] == STATION) continue;
      while (money < 100) wait_turn();
      errect_turn(ope.y_, ope.x_, ope.type_);
    }

    // 駅の利用者を更新する
    for (auto v : land_user_list[sy][sx])
      for (auto u : land_user_list[ty][tx]) {
        if (v == u) {
          board.commutable_citizens_.insert(v);
          int dist =
              abs(input_citizen_list[v].sy_ - input_citizen_list[v].ty_) +
              abs(input_citizen_list[v].sx_ - input_citizen_list[v].tx_);
          money += dist;  // 最後のターン分
          income += dist;
        }
      }
  }

  return ret;
}
// 長さ調整や、途中からのwait調整を行う
void adjast_ans(vector<Operation>& operation_list) {
  // 長すぎたら切る
  while (operation_list.size() > input_T) operation_list.pop_back();

  // シミュレートして、最適な位置からwaitを開始する
  int money = input_K, income = 0;
  // ここから全てwaitした場合の金額
  int exepted_money_max = input_K, max_idx = -1;
  Board board;

  int sy = -1, sx, ty, tx;
  dsu uf(2500);

  rep(ti, operation_list.size()) {
    auto& ope = operation_list[ti];
    if (ope.type_ != WAIT) {
      assert(money >= (ope.type_ == STATION ? 5000 : 100));
      money -= ope.type_ == STATION ? 5000 : 100;
      board.errect(ope.y_, ope.x_, ope.type_);
      // HACK
      if (ope.type_ == STATION) {
        if (sy == -1) {
          sy = ope.y_, sx = ope.x_;
        } else {
          ty = ope.y_, tx = ope.x_;
        }
      } else {
        if (ope.type_ == TRACK_TB) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
        } else if (ope.type_ == TRACK_LR) {
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
        } else if (ope.type_ == TRACK_LT) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
        } else if (ope.type_ == TRACK_LB) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
        } else if (ope.type_ == TRACK_RT) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
        } else if (ope.type_ == TRACK_RB) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
        }
        if (uf.same(sy * 50 + sx, ty * 50 + tx)) {
          for (auto v : land_user_list[sy][sx])
            for (auto u : land_user_list[ty][tx]) {
              if (v == u) {
                board.commutable_citizens_.insert(v);
                int dist =
                    abs(input_citizen_list[v].sy_ - input_citizen_list[v].ty_) +
                    abs(input_citizen_list[v].sx_ - input_citizen_list[v].tx_);
                money += dist;  // 最後のターン分
                income += dist;
              }
            }
          sy = -1;
        }
      }
    }

    money += income;
    // ここから最後のターンまで何もしなかった場合、残りターン分のincomeを得る
    int expected_money = money + (input_T - ti - 1) * income;
    // debug(money, income, expected_money);
    if (chmax(exepted_money_max, expected_money)) max_idx = ti;
  }
  cerr << exepted_money_max << endl;
  while ((int)operation_list.size() > max_idx + 1) operation_list.pop_back();
  while ((int)operation_list.size() < input_T)
    operation_list.emplace_back(WAIT);
}

int main() {
  exec_input();
  calc_land_user_list();
  // debug(land_value_list);

  vector<Operation> ans = naive();
  adjast_ans(ans);

  exec_output(ans);
}