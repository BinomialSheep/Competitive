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

  int64_t getTime() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count();
  }
};

constexpr int input_N = 50, input_T = 800;
int input_M, input_K;
class Citizen {
 public:
  int idx_, sy_, sx_, ty_, tx_, dist_;
  Citizen() : idx_(0), sy_(0), sx_(0), ty_(0), tx_(0), dist_(0) {}
  Citizen(int idx, int sy, int sx, int ty, int tx)
      : idx_(idx), sy_(sy), sx_(sx), ty_(ty), tx_(tx) {
    this->dist_ = abs(sy - ty) + abs(sx - tx);
  };

  void debug_citizen() {
    cerr << idx_ << " " << sy_ << " " << sx_ << " " << ty_ << " " << tx_ << " "
         << dist_ << endl;
  }
};
array<Citizen, 1600> input_citizen_list;

constexpr array<int, 13> dy13 = {-2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2};
constexpr array<int, 13> dx13 = {0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0};
constexpr array<int, 13> dy4 = {-1, 1, 0, 0};
constexpr array<int, 13> dx4 = {0, 0, -1, 1};
// ある土地に駅が立ったら利用する人々（人iに対して、家はi, 駅はi+input_M）
array<array<vector<int>, 50>, 50> land_user_list;
// ある市民のために、どこに土地を建てるか（高速化用）
vector<int> citizen_use_station;
unordered_set<int> citizen_use_station_set;

void initialize_citizen_use_station() {
  citizen_use_station.resize(input_M * 2);
  // 13近傍のうち、一番利用者の多い駅を利用駅とする（暫定）
  rep(i, input_M) {
    int s, mx_s = 0, t, mx_t = 0;
    rep(di, 13) {
      int y1 = input_citizen_list[i].sy_ + dy13[di];
      int x1 = input_citizen_list[i].sx_ + dx13[di];
      int y2 = input_citizen_list[i].ty_ + dy13[di];
      int x2 = input_citizen_list[i].tx_ + dx13[di];
      if (0 <= y1 && y1 < input_N && 0 <= x1 && x1 < input_N) {
        if (chmax(mx_s, (int)land_user_list[y1][x1].size())) s = y1 * 50 + x1;
      }
      if (0 <= y2 && y2 < input_N && 0 <= x2 && x2 < input_N) {
        if (chmax(mx_t, (int)land_user_list[y2][x2].size())) t = y2 * 50 + x2;
      }
    }
    citizen_use_station[i] = s;
    citizen_use_station[i + input_M] = t;
    citizen_use_station_set.insert(s);
    citizen_use_station_set.insert(t);
  }
}

// ある土地と土地に駅が立ったらいくらincomeが増えるか管理する（2つの駅を建てる時にしか使わない）
class LandPairValue {
 public:
  vector<vector<int>> land_pair_value_list_;

  priority_queue<pair<int, pair<int, int>>> pq;

  LandPairValue() : land_pair_value_list_(2500, vector<int>(2500, 0)) {}

  void initialize() {
    int d = (input_K - 10000) / 100;
    rep(i, input_M) {
      rep(di, 13) {
        int y1 = input_citizen_list[i].sy_ + dy13[di];
        int x1 = input_citizen_list[i].sx_ + dx13[di];
        int y2 = input_citizen_list[i].ty_ + dy13[di];
        int x2 = input_citizen_list[i].tx_ + dx13[di];
        if (0 <= y1 && y1 < input_N && 0 <= x1 && x1 < input_N && 0 <= y2 &&
            y2 < input_N && 0 <= x2 && x2 < input_N) {
          if (abs(y1 - y2) + abs(x1 - x2) > d) continue;
          int s = y1 * 50 + x1;
          int t = y2 * 50 + x2;
          if (s > t) swap(s, t);
          land_pair_value_list_[s][t] += input_citizen_list[i].dist_;
        }
      }
    }
    rep(i, 2500) rep(j, i) {
      if (land_pair_value_list_[j][i])
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
      if (0 <= y1 && y1 < input_N && 0 <= x1 && x1 < input_N && 0 <= y2 &&
          y2 < input_N && 0 <= x2 && x2 < input_N) {
        int s = y1 * 50 + x1;
        int t = y2 * 50 + x2;
        if (s > t) swap(s, t);
        land_pair_value_list_[s][t] -= input_citizen_list[citizen_id].dist_;
      }
    }
  }
};

// あるStateにおける土地の価値（今その土地に駅を建てた場合に増える収益）
// 土地はcitizen_use_station分しか持たない
class LandValue {
 private:
  // ある土地の現在の価値を計算する
  int evaluate_land_value() { return 0; }

 public:
  // 土地の価値、土地の座標
  priority_queue<pair<int, int>> pq;

  LandValue() {}

  // 駅を建てたタイミングでpushする
  void update(int y, int x) {
    for (auto v : land_user_list[y][x]) {
      // 駅が立っていない方の家/職場付近の価値を高める
      int s = v < input_M ? citizen_use_station[v + input_M]
                          : citizen_use_station[v - input_M];

      int value = this->evaluate_land_value();

      pq.emplace(value, s);
    }
  }

  // もっとも高い土地を返す
  int toppop() {
    int ret = 0;
    while (pq.size()) {
      auto [value, station] = pq.top();
      pq.pop();
      // 古い情報の場合は捨ててやり直す
      if (this->evaluate_land_value() != value) continue;
      ret = station;
      break;
    }
    return ret;
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
        land_user_list[y2][x2].push_back(i + input_M);
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

  // 線路で繋がっている座標の管理
  dsu board_uf_;
  // 駅の座標
  set<pair<int, int>> stations_;

  // 通勤可能な人
  unordered_set<int> commutable_citizens_;

  Board() : board_uf_(2500) { rep(i, 50) rep(j, 50) board_[i][j] = EMPTY; }

  void errect(int y, int x, int type) {
    assert(board_[y][x] != STATION);
    board_[y][x] = type;
  }
  bool is_connect(int sy, int sx, int ty, int tx) {
    return board_uf_.same(sy * 50 + sx, ty * 50 + tx);
  }

  // 既に通勤可能な人か
  bool is_commutable_citizens(int v) {
    return this->commutable_citizens_.count(v) &&
           this->commutable_citizens_.count(v + input_M);
  }

  void apply_ope_board(const Operation& ope) {
    if (ope.type_ != WAIT) {
      this->errect(ope.y_, ope.x_, ope.type_);
    }
    if (ope.type_ == STATION) {
      if (ope.y_ != 0 && (this->board_[ope.y_ - 1][ope.x_] == STATION ||
                          this->board_[ope.y_ - 1][ope.x_] == TRACK_TB ||
                          this->board_[ope.y_ - 1][ope.x_] == TRACK_LB ||
                          this->board_[ope.y_ - 1][ope.x_] == TRACK_RB))
        board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
      if (ope.y_ != 49 && (this->board_[ope.y_ + 1][ope.x_] == STATION ||
                           this->board_[ope.y_ + 1][ope.x_] == TRACK_TB ||
                           this->board_[ope.y_ + 1][ope.x_] == TRACK_LT ||
                           this->board_[ope.y_ + 1][ope.x_] == TRACK_RT))
        board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
      if (ope.x_ != 0 && (this->board_[ope.y_][ope.x_ - 1] == STATION ||
                          this->board_[ope.y_][ope.x_ - 1] == TRACK_LR ||
                          this->board_[ope.y_][ope.x_ - 1] == TRACK_RT ||
                          this->board_[ope.y_][ope.x_ - 1] == TRACK_RB))
        board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
      if (ope.x_ != 49 && (this->board_[ope.y_][ope.x_ + 1] == STATION ||
                           this->board_[ope.y_][ope.x_ + 1] == TRACK_LR ||
                           this->board_[ope.y_][ope.x_ + 1] == TRACK_LT ||
                           this->board_[ope.y_][ope.x_ + 1] == TRACK_LB))
        board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
    } else if (ope.type_ == TRACK_TB) {
      board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
      board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
    } else if (ope.type_ == TRACK_LR) {
      board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
      board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
    } else if (ope.type_ == TRACK_LT) {
      board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
      board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
    } else if (ope.type_ == TRACK_LB) {
      board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
      board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ - 1);
    } else if (ope.type_ == TRACK_RT) {
      board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ - 1) * 50 + ope.x_);
      board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
    } else if (ope.type_ == TRACK_RB) {
      board_uf_.merge(ope.y_ * 50 + ope.x_, (ope.y_ + 1) * 50 + ope.x_);
      board_uf_.merge(ope.y_ * 50 + ope.x_, ope.y_ * 50 + ope.x_ + 1);
    }
  }

  void add_station(int oy, int ox) { stations_.emplace(oy, ox); }

  // ボードの駅treeに駅(ty,
  // tx)を繋いだ時に新しく通勤可能になる市民のリストを返す
  vector<int> list_new_commuters(int ty, int tx) {
    vector<int> ret;
    for (int v : land_user_list[ty][tx]) {
      if (this->commutable_citizens_.count(v)) continue;
      if (v < input_M) {
        if (this->commutable_citizens_.count(v + input_M)) {
          ret.push_back(v);
        }
      } else {
        if (this->commutable_citizens_.count(v - input_M)) {
          ret.push_back(v - input_M);
        }
      }
    }
    return ret;
  }
};

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
};

// 2点を最短距離で繋ぐ
array<array<int, 50>, 50> distance_points;
array<array<int, 50>, 50> parent_direction;
vector<Operation> connect_station(int sy, int sx, int ty, int tx,
                                  Board& board) {
  vector<Operation> ret;
  // debug(board.board_);

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
    assert(board.board_[y][x] == STATION || board.board_[y][x] == EMPTY);

    // そこが駅だったら、繋がっている他の駅を距離0としてpush_front
    if (board.board_[y][x] == STATION) {
      for (auto [ny, nx] : board.stations_) {
        assert(board.board_[ny][nx] == STATION);
        if (board.is_connect(y, x, ny, nx)) {
          if (chmin(distance_points[ny][nx], distance_points[y][x])) {
            // (0, 0)が駅になった時のために-1しておく
            parent_direction[ny][nx] = -(y * 50 + x) - 1;
            if (ny == ty && nx == tx) {
              is_reach = true;
              break;
            }
            dq.emplace_front(ny, nx);
          }
        }
      }
    }

    rep(di, 4) {
      int ny = y + dy4[di], nx = x + dx4[di];
      if (0 <= ny && ny < 50 && 0 <= nx && nx < 50) {
        // 道をつぶして駅にすることもできるが、ここでは考慮しない
        if (board.board_[ny][nx] == STATION) {
          if (chmin(distance_points[ny][nx], distance_points[y][x])) {
            parent_direction[ny][nx] = di;
            if (ny == ty && nx == tx) {
              is_reach = true;
              break;
            }
            dq.emplace_front(ny, nx);
          }
        } else if (board.board_[ny][nx] == EMPTY) {
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
    assert(board.board_[y][x] == STATION || board.board_[y][x] == EMPTY);
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

    if (parent_direction[y][x] < 0) {
      parent_direction[y][x]++;
      int y2 = -parent_direction[y][x] / 50, x2 = -parent_direction[y][x] % 50;
      last = parent_direction[y2][x2];
      y = y2, x = x2;
      if (y == sy && x == sx) break;
      continue;
    }

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
      debug(y, x, last, parent_direction[y][x]);
      Operation::debug_ope_list(ret);
      debug(distance_points);
      debug(parent_direction);
      assert(false);
    }
    last = parent_direction[y][x];
  }
  // Operation::debug_ope_list(ret);

  return ret;
}

using ScoreType = int;
class State {
 private:
  void check_update_station(int oy, int ox) {
    if (this->board_.board_[oy][ox] != STATION) return;
    this->board_.add_station(oy, ox);

    for (auto v : land_user_list[oy][ox]) {
      if (board_.commutable_citizens_.count(v)) continue;
      board_.commutable_citizens_.insert(v);
      int v2 = v < input_M ? v : v - input_M;
      if (board_.is_commutable_citizens(v2)) {
        this->income_ += input_citizen_list[v2].dist_;
      }
    }
    // debug(this->income_);
  }

 public:
  Board board_;
  int money_ = -1;
  int income_;
  vector<Operation> ans_;
  int evaluated_score_;

  State() {}

  State(int init_money) : money_(init_money), income_(0) {}

  // 収穫フェイズ
  void consume_turn() { money_ += income_; }

  void apply_ope_state(const Operation& ope) {
    ans_.push_back(ope);
    if (ope.type_ != WAIT) {
      assert(money_ >= (ope.type_ == STATION ? 5000 : 100));
      money_ -= ope.type_ == STATION ? 5000 : 100;

      this->board_.apply_ope_board(ope);

      if (ope.type_ == STATION) {
        check_update_station(ope.y_, ope.x_);
      } else if (ope.type_ == TRACK_TB) {
        check_update_station(ope.y_ - 1, ope.x_);
        check_update_station(ope.y_ + 1, ope.x_);
      } else if (ope.type_ == TRACK_LR) {
        check_update_station(ope.y_, ope.x_ - 1);
        check_update_station(ope.y_, ope.x_ + 1);
      } else if (ope.type_ == TRACK_LT) {
        check_update_station(ope.y_ - 1, ope.x_);
        check_update_station(ope.y_, ope.x_ - 1);
      } else if (ope.type_ == TRACK_LB) {
        check_update_station(ope.y_ + 1, ope.x_);
        check_update_station(ope.y_, ope.x_ - 1);
      } else if (ope.type_ == TRACK_RT) {
        check_update_station(ope.y_ - 1, ope.x_);
        check_update_station(ope.y_, ope.x_ + 1);
      } else if (ope.type_ == TRACK_RB) {
        check_update_station(ope.y_ + 1, ope.x_);
        check_update_station(ope.y_, ope.x_ + 1);
      }
    }
    this->consume_turn();
  }

  // 現在のターン
  int get_turn() { return (int)ans_.size(); }

  // 残りをWAITした場合のスコア
  int evaluate_score() {
    if (money_ != -1)
      evaluated_score_ = money_ + (input_T - (int)ans_.size()) * income_;
    return evaluated_score_;
  }

  // 2つの駅を繋ぐアクション
  void exec_connect_action(Action& action) {
    Operation wait_ope(WAIT);
    // debug(opes_.size());

    for (auto& ope : action.opes_) {
      // debug(ope.type_, ope.y_, ope.x_, this->money_, this->income_);
      // もう駅が立ってたら道を立てる必要なし
      if (this->board_.board_[ope.y_][ope.x_] == STATION) continue;
      while (this->money_ < 100) this->apply_ope_state(wait_ope);
      this->apply_ope_state(ope);
    }
    if (this->board_.board_[action.sy_][action.sx_] != STATION) {
      while (this->money_ < 5000) this->apply_ope_state(wait_ope);
      Operation ope(STATION, action.sy_, action.sx_);
      this->apply_ope_state(ope);
    }
    if (this->board_.board_[action.ty_][action.tx_] != STATION) {
      while (this->money_ < 5000) this->apply_ope_state(wait_ope);
      Operation ope(STATION, action.ty_, action.tx_);
      this->apply_ope_state(ope);
    }
  }

  void calc_operations(Action& action) {
    // 線路をつぶして駅にする場合
    if (this->board_.board_[action.ty_][action.tx_] >= 1) return;

    action.opes_ = connect_station(action.sy_, action.sx_, action.ty_,
                                   action.tx_, this->board_);
    // 接続不能で悲しい
    if (action.opes_.empty()) action.action_type_ = -1;
  }

  vector<Action> legal_actions() {
    vector<Action> ret;

    auto& stations = this->board_.stations_;
    int sy = stations.begin()->first, sx = stations.begin()->second;

    for (auto yx : citizen_use_station_set) {
      int ty = yx / 50, tx = yx % 50;
      Action action;
      int earn = 0;

      vector<int> vec = this->board_.list_new_commuters(ty, tx);
      for (auto v : vec) earn += input_citizen_list[v].dist_;

      if (earn == 0) continue;
      action.action_type_ = 1;
      action.sy_ = sy, action.sx_ = sx, action.ty_ = ty, action.tx_ = tx;
      action.earn_ = earn;
      action.cost_ = 0;
      ret.push_back(action);
    }
    sort(ret.begin(), ret.end(),
         [](const Action& a, const Action& b) { return a.earn_ > b.earn_; });

    // debug(ret.size());

    return ret;
  }
};
// 探索時のソート用に評価を比較する
bool operator<(const State& state_1, const State& state_2) {
  return state_1.evaluated_score_ < state_2.evaluated_score_;
}

// 最初の1手は駅を2つ建てて間を結ぶ
void early_stage(vector<State>& beam) {
  LandPairValue land_pair_value;
  land_pair_value.initialize();
  // 2つの駅を繋ぐ場合
  auto get_conenct_action = [&](State state, int& last_dist) {
    while (land_pair_value.pq.size()) {
      auto [start, target] =
          land_pair_value.toppop(state.income_ == 0 ? state.money_ : -1);

      if (land_pair_value.land_pair_value_list_[start][target] == 0) break;

      int sy = start / 50, sx = start % 50, ty = target / 50, tx = target % 50;
      // last_distと同じ距離は飛ばす
      if (abs(sy - ty) + abs(sx - tx) == last_dist) continue;
      // 既に立っていたら建てない
      // if (state.board_.board_[sy][sx] >= 1 ||
      //     state.board_.board_[sy][sx] >= 1)
      //   continue;

      vector<Operation> opes = connect_station(sy, sx, ty, tx, state.board_);
      // 到達不可
      if (opes.empty()) continue;
      last_dist = abs(sy - ty) + abs(sx - tx);

      Action action;
      action.opes_ = opes;
      action.action_type_ = 2;
      action.cost_ = 10000 + (int)opes.size() * 100;
      action.earn_ = land_pair_value.land_pair_value_list_[start][target];
      action.sy_ = sy, action.sx_ = sx, action.ty_ = ty, action.tx_ = tx;
      return action;
    }
    Action action;
    action.action_type_ = -1;
    return action;
  };

  int last_dist = -1;
  rep(i, 5) {
    State state(input_K);
    Action action2 = get_conenct_action(state, last_dist);
    if (action2.action_type_ == -1) return;
    state.exec_connect_action(action2);
    state.evaluate_score();
    last_dist = action2.earn_;
    beam[state.get_turn()] = state;
  }
}

// 適当に駅を建てて、近くとつなぐ
Action get_one_action(State& state) {
  int mx_earn = 0;
  int bsy = -1, bsx, bty = -1, btx;
  Action action;
  action.action_type_ = -1;

  auto& stations = state.board_.stations_;
  bsy = stations.begin()->first, bsx = stations.begin()->second;

  for (auto yx : citizen_use_station_set) {
    // yxを新しい駅にした時に得られる収益
    int earn = 0;

    int ty = yx / 50, tx = yx % 50;
    vector<int> vec = state.board_.list_new_commuters(ty, tx);
    for (auto v : vec) earn += input_citizen_list[v].dist_;
    // debug(ty, tx, vec, earn);

    // 線路上の駅は掛かるターンが1なので優遇したさはある
    // if (state.board_.board_[ty][tx] >= 1) {
    //   // debug(sy, sx, ty, tx, earn);
    //   if (earn > 0) {
    //     bsy = sy, bsx = sx, bty = ty, btx = tx;
    //     break;
    //   }
    // }
    if (chmax(mx_earn, earn)) {
      bty = ty, btx = tx;
    }
  }
  // debug(bsy, bsx, bty, btx, mx_earn);

  // 収益が増える駅がないので何もしない（長期的には線路上とかに適当に駅を建てておくと得するかもだけど……）
  if (bty == -1) return action;
  action.action_type_ = 1;
  action.sy_ = bsy, action.sx_ = bsx, action.ty_ = bty, action.tx_ = btx;
  action.earn_ = mx_earn;
  action.cost_ = 0;
  return action;
}

vector<Operation> solve(TimeKeeper& time_keeper) {
  vector<Operation> ret;

  vector<State> beam(input_T + 1);

  auto debug_beam = [&]() {
    rep(i, input_T + 1) { debug(i, beam[i].income_, beam[i].money_); }
  };

  early_stage(beam);

  int mx_turn = 0, mx_score = 0;
  for (int turn = 1; turn < input_T; turn++) {
    State& state = beam[turn];
    if (state.money_ == -1) continue;
    // debug(turn, state.money_, time_keeper.getTime());
    assert(state.income_ > 0);
    if (chmax(mx_score, state.evaluated_score_)) mx_turn = turn;

    vector<Action> action_list = state.legal_actions();

    rep(i, action_list.size()) {
      if (i == 10) break;
      Action& action = action_list[i];
      // Action action = get_one_action(state);
      // debug(time_keeper.getTime());
      if (action.action_type_ != -1) state.calc_operations(action);
      if (action.action_type_ != -1) {
        state.exec_connect_action(action);
        if (state.get_turn() <= input_T) {
          state.evaluate_score();
          if (chmax(beam[state.get_turn()].evaluated_score_,
                    state.evaluated_score_)) {
            beam[state.get_turn()] = state;
          }
        }
      }
    }
  }

  return beam[mx_turn].ans_;
}

// 長さ調整や、途中からのwait調整を行う
void adjast_ans(vector<Operation>& operation_list) {
  // 長すぎたら切る
  while (operation_list.size() > input_T) operation_list.pop_back();

  // シミュレートして、最適な位置からwaitを開始する

  State state(input_K);
  // ここから全てwaitした場合の金額
  int exepted_money_max = input_K, max_idx = -1;

  rep(ti, operation_list.size()) {
    state.apply_ope_state(operation_list[ti]);

    // ここから最後のターンまで何もしなかった場合、残りターン分のincomeを得る
    int expected_money = state.money_ + (input_T - ti - 1) * state.income_;
    // debug(state.money_, state.income_, expected_money);
    if (chmax(exepted_money_max, expected_money)) max_idx = ti;
  }
  cerr << exepted_money_max << endl;
  while ((int)operation_list.size() > max_idx + 1) operation_list.pop_back();
  while ((int)operation_list.size() < input_T)
    operation_list.emplace_back(WAIT);
}

int main() {
  const int time_threshold = 10000;
  auto time_keeper = TimeKeeper(time_threshold);

  exec_input();
  calc_land_user_list();
  initialize_citizen_use_station();

  vector<Operation> ans = solve(time_keeper);
  adjast_ans(ans);
  exec_output(ans);

  cerr << "経過ms:" << time_keeper.getTime() << endl;
}