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
// ある土地と土地に駅が立ったらいくらincomeが増えるかなどを管理する
class LandPairValue {
 public:
  vector<vector<int>> land_pair_value_list_;

  priority_queue<pair<int, pair<int, int>>> pq;

  LandPairValue() : land_pair_value_list_(2500, vector<int>(2500, 0)) {}

  void initialize() {
    rep(i, input_M) {
      int dist = abs(input_citizen_list[i].sy_ - input_citizen_list[i].ty_) +
                 abs(input_citizen_list[i].sx_ - input_citizen_list[i].tx_);
      rep(di, 13) {
        int y1 = input_citizen_list[i].sy_ + dy13[di];
        int x1 = input_citizen_list[i].sx_ + dx13[di];
        int y2 = input_citizen_list[i].ty_ + dy13[di];
        int x2 = input_citizen_list[i].tx_ + dx13[di];
        if (0 <= y1 && y1 < input_N && 0 <= x1 && x1 < input_N && 0 <= y2 &&
            y2 < input_N && 0 <= x2 && x2 < input_N) {
          int s = y1 * 50 + x1;
          int t = y2 * 50 + x2;
          if (s > t) swap(s, t);
          land_pair_value_list_[s][t] += dist;
        }
      }
    }
    rep(i, 2500) rep(j, i) {
      pq.emplace(land_pair_value_list_[j][i], make_pair(j, i));
    }
  }

  // 収益性が高い土地のペアを返す（予算が指定された場合、予算以下で返す）
  pair<int, int> toppop(int money = -1) {
    pair<int, int> ret;
    vector<pair<int, pair<int, int>>> tmp;
    while (true) {
      assert(!pq.empty());
      auto p = pq.top();
      pq.pop();
      // 古い値だったら入れ替える
      if (p.first != land_pair_value_list_[p.second.first][p.second.second]) {
        pq.emplace(land_pair_value_list_[p.second.first][p.second.second],
                   p.second);
      } else {
        // 予算以下だったら一次置きする
        if (money != -1) {
          int dist = abs(p.second.first / 50 - p.second.second / 50) +
                     abs(p.second.first % 50 - p.second.second % 50);
          if (dist * 100 + 10000 > money) {
            tmp.push_back(p);
            continue;
          }
        }
        ret = p.second;
        break;
      }
    }
    for (auto p : tmp) pq.push(p);
    // debug(ret, land_pair_value_list_[ret.first][ret.second]);
    return ret;
  }

  // 市民が通勤可能になったことによる更新
  void update(int citizen_id) {
    // 今回住人が通勤可能になったことによる影響を引く
    rep(di, 13) {
      int y1 = input_citizen_list[citizen_id].sy_ + dy13[di];
      int x1 = input_citizen_list[citizen_id].sx_ + dx13[di];
      int y2 = input_citizen_list[citizen_id].ty_ + dy13[di];
      int x2 = input_citizen_list[citizen_id].tx_ + dx13[di];
      int dist = abs(input_citizen_list[citizen_id].sy_ -
                     input_citizen_list[citizen_id].ty_) +
                 abs(input_citizen_list[citizen_id].ty_ +
                     input_citizen_list[citizen_id].tx_);
      if (0 <= y1 && y1 < input_N && 0 <= x1 && x1 < input_N && 0 <= y2 &&
          y2 < input_N && 0 <= x2 && x2 < input_N) {
        int s = y1 * 50 + x1;
        int t = y2 * 50 + x2;
        if (s > t) swap(s, t);
        land_pair_value_list_[s][t] -= dist;
      }
    }
  }

  // ある駅から繋ぐ最適な場所
  pair<int, pair<int, int>> top_place(int sy, int sx,
                                      array<int, 1600>& commutable_citizens) {
    pair<int, int> ret;
    int mx = 0;
    int s = sy * 50 + sx;
    for (auto citizen : land_user_list[sy][sx]) {
      if (commutable_citizens[citizen]) continue;
      int y = input_citizen_list[citizen].sy_,
          x = input_citizen_list[citizen].sx_;
      if (abs(sy - y) + abs(sx - x) <= 2) {
        y = input_citizen_list[citizen].ty_,
        x = input_citizen_list[citizen].tx_;
      }
      rep(di, 13) {
        int ty = y + dy13[di], tx = x + dx13[di];
        if (0 <= ty && ty < input_N && 0 <= tx && tx < input_N) {
          int t = ty * 50 + tx;
          if (s > t) swap(s, t);
          if (chmax(mx, land_pair_value_list_[s][t])) ret = make_pair(s, t);
        }
      }
    }
    return make_pair(mx, ret);
  }
};

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

  void debug_ope() { cerr << type_ << " " << y_ << " " << x_ << endl; }

  static void debug_ope_list(vector<Operation>& ope_list) {
    for (auto& ope : ope_list) ope.debug_ope();
  }
};

void exec_output(vector<Operation> operation_list) {
  // assert(operation_list.size() == input_T);
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

  // connected[y*50+x] = どの駅と繋がっているか
  array<unordered_set<int>, 2500> connected_;
  // 通勤可能な人
  array<int, 1600> commutable_citizens_{};

  Board() { rep(i, 50) rep(j, 50) board_[i][j] = EMPTY; }

  void errect(int y, int x, int type) {
    if (board_[y][x] != EMPTY) debug(y, x, type, board_[y][x]);
    assert(board_[y][x] == EMPTY);
    board_[y][x] = type;
  }

  void connect(int sy, int sx, int ty, int tx) {
    int s = sy * 50 + sx, t = ty * 50 + tx;
    if (connected_[s].count(t)) return;
    connected_[s].insert(t);
    connected_[t].insert(s);
    for (auto v : connected_[s]) {
      connected_[t].insert(v);
      connected_[v].insert(t);
    }
    for (auto v : connected_[t]) {
      connected_[s].insert(v);
      connected_[v].insert(s);
    }
  }
  bool is_connect(int sy, int sx, int ty, int tx) {
    return connected_[sy * 50 + sx].count(ty * 50 + tx);
  }
  bool is_connect(int s, int t) { return connected_[s].count(t); }
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

class Action {
 public:
  int cost_, earn_;
  int action_type_;
  int sy_, sx_, ty_, tx_;
  vector<Operation> opes_;
  Action() {}

  void debug_action() {
    cerr << "action_type: " << action_type_ << " sy: " << sy_ << " sx: " << sx_
         << " ty: " << ty_ << " tx: " << tx_ << " cost: " << cost_
         << " earn: " << earn_ << endl;
  }

  void wait_turn(int& money, int income, vector<Operation>& ans) {
    ans.emplace_back(WAIT);
    money += income;
  }

  void errect_turn(int y, int x, int type, int& money, int income,
                   vector<Operation>& ans, Board& board) {
    ans.emplace_back(type, y, x);
    board.errect(y, x, type);
    money -= type == STATION ? 5000 : 100;
    money += income;
  }

  // 2つの駅を繋ぐアクション
  void exec_connect_action(int& money, int& income, Board& board,
                           LandPairValue& land_pair_value,
                           vector<Operation>& ans) {
    // たまたま通過した駅
    vector<pair<int, int>> stations;

    for (auto& ope : opes_) {
      // debug(ope.type_, ope.y_, ope.x_, money, income);
      // もう駅が立ってたら道を立てる必要なし
      if (board.board_[ope.y_][ope.x_] == STATION) {
        stations.emplace_back(ope.y_, ope.x_);
        continue;
      }
      while (money < 100) wait_turn(money, income, ans);
      errect_turn(ope.y_, ope.x_, ope.type_, money, income, ans, board);
    }
    if (board.board_[sy_][sx_] != STATION) {
      while (money < 5000) wait_turn(money, income, ans);
      errect_turn(sy_, sx_, STATION, money, income, ans, board);
    }
    if (board.board_[ty_][tx_] != STATION) {
      while (money < 5000) wait_turn(money, income, ans);
      errect_turn(ty_, tx_, STATION, money, income, ans, board);
    }

    auto connect_station = [&](int sy, int sx, int ty, int tx) {
      board.connect(sy, sx, ty, tx);

      for (int station : board.connected_[sy * 50 + sx]) {
        int y = station / 50, x = station % 50;
        if (sy != y || sx != x) {
          for (auto v : land_user_list[sy][sx])
            for (auto u : land_user_list[y][x]) {
              if (v == u && board.commutable_citizens_[v] == 0) {
                // 2つの駅が両方家（両方職場）近くの時に誤判定を起こすのでその対策
                if ((abs(sy - input_citizen_list[v].sy_) +
                             abs(sx - input_citizen_list[v].sx_) <=
                         2 &&
                     (abs(y - input_citizen_list[v].ty_) +
                          abs(x - input_citizen_list[v].tx_) <=
                      2)) ||
                    (abs(y - input_citizen_list[v].sy_) +
                             abs(x - input_citizen_list[v].sx_) <=
                         2 &&
                     (abs(sy - input_citizen_list[v].ty_) +
                          abs(sx - input_citizen_list[v].tx_) <=
                      2))) {
                  board.commutable_citizens_[v] = 1;
                  land_pair_value.update(v);
                  int dist = abs(input_citizen_list[v].sy_ -
                                 input_citizen_list[v].ty_) +
                             abs(input_citizen_list[v].sx_ -
                                 input_citizen_list[v].tx_);
                  money += dist;  // 最後のターン分
                  income += dist;
                }
              }
            }
        }
        if (ty != y || tx != x) {
          for (auto v : land_user_list[ty][tx])
            for (auto u : land_user_list[y][x]) {
              if (v == u && board.commutable_citizens_[v] == 0) {
                // 2つの駅が両方家（両方職場）近くの時に誤判定を起こすのでその対策
                if ((abs(ty - input_citizen_list[v].sy_) +
                             abs(tx - input_citizen_list[v].sx_) <=
                         2 &&
                     (abs(y - input_citizen_list[v].ty_) +
                          abs(x - input_citizen_list[v].tx_) <=
                      2)) ||
                    (abs(y - input_citizen_list[v].sy_) +
                             abs(x - input_citizen_list[v].sx_) <=
                         2 &&
                     (abs(ty - input_citizen_list[v].ty_) +
                          abs(tx - input_citizen_list[v].tx_) <=
                      2))) {
                  board.commutable_citizens_[v] = 1;
                  land_pair_value.update(v);
                  int dist = abs(input_citizen_list[v].sy_ -
                                 input_citizen_list[v].ty_) +
                             abs(input_citizen_list[v].sx_ -
                                 input_citizen_list[v].tx_);
                  money += dist;  // 最後のターン分
                  income += dist;
                }
              }
            }
        }
      }

      // 駅の利用者を更新する
      // for (auto v : land_user_list[sy][sx])
      //   for (auto u : land_user_list[ty][tx]) {
      //     if (v == u && board.commutable_citizens_[v] == 0) {
      //       board.commutable_citizens_[v] = 1;
      //       land_pair_value.update(v);
      //       int dist =
      //           abs(input_citizen_list[v].sy_ - input_citizen_list[v].ty_) +
      //           abs(input_citizen_list[v].sx_ - input_citizen_list[v].tx_);
      //       income += dist;
      //     }
      //   }
    };
    connect_station(sy_, sx_, ty_, tx_);
    for (auto [y, x] : stations) {
      connect_station(sy_, sx_, y, x);
      connect_station(ty_, tx_, y, x);
    }
  }
};

// 4投目用
vector<Operation> naive04() {
  vector<Operation> ret;

  int money = input_K, income = 0;
  Board board;

  LandPairValue land_pair_value;
  land_pair_value.initialize();

  // 2つの駅を繋ぐ場合
  auto get_conenct_action = [&]() {
    while (true) {
      assert(land_pair_value.pq.size());
      auto [start, target] = land_pair_value.toppop(income == 0 ? money : -1);
      int sy = start / 50, sx = start % 50, ty = target / 50, tx = target % 50;
      // 既に立っていたら建てない
      if (board.board_[sy][sx] >= 1 || board.board_[sy][sx] >= 1) continue;

      vector<Operation> opes = connect_station(sy, sx, ty, tx, board);
      // 到達不可
      if (opes.empty()) continue;

      Action action;
      action.opes_ = opes;
      action.action_type_ = 2;
      action.cost_ = 10000 + (int)opes.size() * 100;
      action.earn_ = land_pair_value.land_pair_value_list_[start][target];
      action.sy_ = sy, action.sx_ = sx, action.ty_ = ty, action.tx_ = tx;
      return action;
    }
  };

  // 今ある駅を繋ぐ場合
  auto get_zero_action = [&]() {
    vector<int> stations;
    rep(i, 2500) if (board.connected_[i].size()) stations.push_back(i);

    // (スコア, (s, t))
    priority_queue<pair<int, pair<int, int>>> pq;

    rep(i, stations.size()) rep(j, i) {
      if (board.is_connect(stations[j], stations[i])) continue;
      pq.emplace(
          land_pair_value.land_pair_value_list_[stations[j]][stations[i]],
          make_pair(stations[j], stations[i]));
    }
    Action action;
    action.action_type_ = -1;

    while (pq.size()) {
      auto p = pq.top();
      pq.pop();
      vector<Operation> opes = connect_station(action.sy_, action.sx_,
                                               action.ty_, action.tx_, board);
      if (opes.empty()) continue;

      action.action_type_ = 0;
      action.sy_ = p.second.first / 50, action.sx_ = p.second.first % 50;
      action.ty_ = p.second.second / 50, action.tx_ = p.second.second % 50;
      action.earn_ = p.first;
      action.opes_ = opes;
      action.cost_ = (int)opes.size() * 100;
      break;
    }

    return action;
  };

  rep(ti, 1000) {
    Action action0 = get_zero_action();
    Action action2 = get_conenct_action();

    if (action0.action_type_ == -1) {
      action2.exec_connect_action(money, income, board, land_pair_value, ret);
    } else if (money < 10000) {
      action0.exec_connect_action(money, income, board, land_pair_value, ret);
    } else if (action0.earn_ > action2.earn_) {
      action0.exec_connect_action(money, income, board, land_pair_value, ret);
    } else {
      action2.exec_connect_action(money, income, board, land_pair_value, ret);
    }
    if (ret.size() >= input_T) break;
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

  dsu uf(2500);
  set<pair<int, int>> stations;

  auto check_update_station = [&](int oy, int ox) {
    if (board.board_[oy][ox] != STATION) return;
    stations.emplace(oy, ox);
    // debug(oy, ox, stations);
    for (auto [sy, sx] : stations)
      for (auto [ty, tx] : stations) {
        if (sy == ty && sx == tx) continue;
        if (!uf.same(sy * 50 + sx, ty * 50 + tx)) continue;
        // debug(sy, sx, ty, tx);
        for (auto v : land_user_list[sy][sx])
          for (auto u : land_user_list[ty][tx]) {
            if (v == u && board.commutable_citizens_[v] == 0) {
              // 2つの駅が両方家（両方職場）近くの時に誤判定を起こすのでその対策
              if ((abs(sy - input_citizen_list[v].sy_) +
                           abs(sx - input_citizen_list[v].sx_) <=
                       2 &&
                   (abs(ty - input_citizen_list[v].ty_) +
                        abs(tx - input_citizen_list[v].tx_) <=
                    2)) ||
                  (abs(ty - input_citizen_list[v].sy_) +
                           abs(tx - input_citizen_list[v].sx_) <=
                       2 &&
                   (abs(sy - input_citizen_list[v].ty_) +
                        abs(sx - input_citizen_list[v].tx_) <=
                    2))) {
                board.commutable_citizens_[v] = 1;
                int dist =
                    abs(input_citizen_list[v].sy_ - input_citizen_list[v].ty_) +
                    abs(input_citizen_list[v].sx_ - input_citizen_list[v].tx_);
                // debug(sy, sx, ty, tx, v, dist);
                income += dist;
              }
            }
          }
      }
    stations.emplace(oy, ox);
  };

  rep(ti, operation_list.size()) {
    auto& ope = operation_list[ti];
    if (ope.type_ != WAIT) {
      assert(money >= (ope.type_ == STATION ? 5000 : 100));
      money -= ope.type_ == STATION ? 5000 : 100;
      board.errect(ope.y_, ope.x_, ope.type_);

      if (ope.type_ == STATION) {
        if (ope.y_ != 0 && (board.board_[ope.y_ - 1][ope.x_] == STATION ||
                            board.board_[ope.y_ - 1][ope.x_] == TRACK_TB ||
                            board.board_[ope.y_ - 1][ope.x_] == TRACK_LB ||
                            board.board_[ope.y_ - 1][ope.x_] == TRACK_RB))
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
        if (ope.y_ != 49 && (board.board_[ope.y_ + 1][ope.x_] == STATION ||
                             board.board_[ope.y_ + 1][ope.x_] == TRACK_TB ||
                             board.board_[ope.y_ + 1][ope.x_] == TRACK_LT ||
                             board.board_[ope.y_ + 1][ope.x_] == TRACK_RT))
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
        if (ope.x_ != 0 && (board.board_[ope.y_][ope.x_ - 1] == STATION ||
                            board.board_[ope.y_][ope.x_ - 1] == TRACK_LR ||
                            board.board_[ope.y_][ope.x_ - 1] == TRACK_RT ||
                            board.board_[ope.y_][ope.x_ - 1] == TRACK_RB))
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
        if (ope.x_ != 49 && (board.board_[ope.y_][ope.x_ + 1] == STATION ||
                             board.board_[ope.y_][ope.x_ + 1] == TRACK_LR ||
                             board.board_[ope.y_][ope.x_ + 1] == TRACK_LT ||
                             board.board_[ope.y_][ope.x_ + 1] == TRACK_LB))
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);

        // 駅を建てたら他の駅と繋がっているかチェックし、繋がっていればincomeを更新
        // debug(stations);
        check_update_station(ope.y_, ope.x_);
      } else {
        if (ope.type_ == TRACK_TB) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
          check_update_station(ope.y_ - 1, ope.x_);
          check_update_station(ope.y_ + 1, ope.x_);
        } else if (ope.type_ == TRACK_LR) {
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
          check_update_station(ope.y_, ope.x_ - 1);
          check_update_station(ope.y_, ope.x_ + 1);
        } else if (ope.type_ == TRACK_LT) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
          check_update_station(ope.y_ - 1, ope.x_);
          check_update_station(ope.y_, ope.x_ - 1);
        } else if (ope.type_ == TRACK_LB) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
          check_update_station(ope.y_ + 1, ope.x_);
          check_update_station(ope.y_, ope.x_ - 1);
        } else if (ope.type_ == TRACK_RT) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
          check_update_station(ope.y_ - 1, ope.x_);
          check_update_station(ope.y_, ope.x_ + 1);
        } else if (ope.type_ == TRACK_RB) {
          uf.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
          uf.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
          check_update_station(ope.y_ + 1, ope.x_);
          check_update_station(ope.y_, ope.x_ + 1);
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

  // vector<Operation> ans_naive = naive();
  // adjast_ans(ans_naive);
  vector<Operation> ans_naive04 = naive04();
  // exec_output(ans_naive04);

  adjast_ans(ans_naive04);
  // debug(ans.size());
  // exec_output(ans);

  exec_output(ans_naive04);
}