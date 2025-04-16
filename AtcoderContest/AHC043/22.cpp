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

/* ハイパーパラメータ */
// 最初に2つ駅を建てるパターン数
constexpr int PARAM_EARLY_ACTION_COUNT = 400;
// legal_actionsで列挙する行動のサイズ
constexpr int PARAM_LEGAL_ACTION_COUNT = 40;
// chokudaiビームの幅
constexpr int PARAM_BEAM_WIDTH = 10;
//
constexpr int PARAM_TIME_THRESHOLD = 28000;

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
array<array<int, 50>, 50> is_citizen_use_station;

// keyに駅の状態、valueにevaluate_scoreを入れて盤面重複除去
unordered_map<bitset<2500>, int> memo;

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
    is_citizen_use_station[s / 50][s % 50] = 1;
    is_citizen_use_station[t / 50][t % 50] = 1;
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
  int operation_;

  Operation(int type) : operation_(type * 2500) {}
  Operation(int type, int y, int x) : operation_(type * 2500 + y * 50 + x) {
    assert(type == operation_ / 2500);
    assert(y == operation_ % 2500 / 50);
    assert(x == operation_ % 50);
  }

  int get_type() const { return operation_ / 2500; }
  int get_y() const { return operation_ % 2500 / 50; }
  int get_x() const { return operation_ % 50; }

  void debug_ope() const {
    int type = operation_ / 2500;
    int y = operation_ % 2500 / 50;
    int x = operation_ % 50;
    cerr << type << " " << y << " " << x << endl;
  }

  static void debug_ope_list(vector<Operation>& ope_list) {
    for (auto& ope : ope_list) ope.debug_ope();
  }
};

void exec_output(vector<Operation> operation_list) {
  for (auto& ope : operation_list) {
    if (ope.get_type() == STATION) {
      out(0, ope.get_y(), ope.get_x());
    } else if (ope.get_type() == WAIT) {
      out(-1);
    } else {
      out(ope.get_type(), ope.get_y(), ope.get_x());
    }
  }
}

const int EMPTY = -1;
class Board {
 public:
  // 線路で繋がっている座標の管理
  dsu board_uf_;
  // 駅があるか
  bitset<2500> stations_;
  // 通勤可能な人
  bitset<3200> commutable_citizens_;

  Board() : board_uf_(2500) {}

  void errect(int y, int x, int type) {
    assert(!is_station(y, x));
    if (type == STATION) add_station(y, x);
  }
  bool is_connect(int sy, int sx, int ty, int tx) {
    return board_uf_.same(sy * 50 + sx, ty * 50 + tx);
  }

  // 既に通勤可能な人か
  bool is_commutable_citizens(int v) {
    return this->commutable_citizens_.test(v) &&
           this->commutable_citizens_.test(v + input_M);
  }

  bool is_station(int y, int x) const { return stations_.test(y * 50 + x); }
  bool is_track(int y, int x) {
    return !stations_.test(y * 50 + x) && board_uf_.size(y * 50 + x) > 1;
  }
  bool is_blank_space(int y, int x) { return board_uf_.size(y * 50 + x) == 1; }
  void add_station(int y, int x) { stations_.set(y * 50 + x); }

  void apply_ope_board(const Operation& ope, const Operation& last_ope) {
    int type = ope.get_type(), y = ope.get_y(), x = ope.get_x();
    if (type != WAIT) {
      this->errect(y, x, type);
      int last_type = last_ope.get_type(), last_y = last_ope.get_y(),
          last_x = last_ope.get_x();
      if (last_type != WAIT) board_uf_.merge(last_y * 50 + last_x, y * 50 + x);
    }
    if (type == STATION) {
      int last_type = last_ope.get_type(), last_y = last_ope.get_y(),
          last_x = last_ope.get_x();
      if (last_type != WAIT) board_uf_.merge(last_y * 50 + last_x, y * 50 + x);
    } else if (type == TRACK_TB) {
      board_uf_.merge(y * 50 + x, (y - 1) * 50 + x);
      board_uf_.merge(y * 50 + x, (y + 1) * 50 + x);
    } else if (type == TRACK_LR) {
      board_uf_.merge(y * 50 + x, y * 50 + x - 1);
      board_uf_.merge(y * 50 + x, y * 50 + x + 1);
    } else if (type == TRACK_LT) {
      board_uf_.merge(y * 50 + x, (y - 1) * 50 + x);
      board_uf_.merge(y * 50 + x, y * 50 + x - 1);
    } else if (type == TRACK_LB) {
      board_uf_.merge(y * 50 + x, (y + 1) * 50 + x);
      board_uf_.merge(y * 50 + x, y * 50 + x - 1);
    } else if (type == TRACK_RT) {
      board_uf_.merge(y * 50 + x, (y - 1) * 50 + x);
      board_uf_.merge(y * 50 + x, y * 50 + x + 1);
    } else if (type == TRACK_RB) {
      board_uf_.merge(y * 50 + x, (y + 1) * 50 + x);
      board_uf_.merge(y * 50 + x, y * 50 + x + 1);
    }
  }

  // ボードの駅treeに駅(ty,
  // tx)を繋いだ時に新しく通勤可能になる市民のリストを返す
  vector<int> list_new_commuters(int ty, int tx) {
    vector<int> ret;
    for (int v : land_user_list[ty][tx]) {
      if (this->commutable_citizens_.test(v)) continue;
      if (v < input_M) {
        if (this->commutable_citizens_.test(v + input_M)) {
          ret.push_back(v);
        }
      } else {
        if (this->commutable_citizens_.test(v - input_M)) {
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
vector<Operation> connect_station(int sy, int sx, Board& board) {
  vector<Operation> ret;
  int ty = -1, tx = -1;
  // TODO：全部見るのは無駄だがどうするか
  rep(y, 50) rep(x, 50) distance_points[y][x] = 1e9;

  distance_points[sy][sx] = 0;
  queue<pair<int, int>> dq;
  dq.emplace(sy, sx);

  bool is_reach = false;
  while ((int)dq.size() && !is_reach) {
    assert(dq.size());
    auto [y, x] = dq.front();
    dq.pop();
    assert(board.is_blank_space(y, x));

    rep(di, 4) {
      int ny = y + dy4[di], nx = x + dx4[di];
      if (0 <= ny && ny < 50 && 0 <= nx && nx < 50) {
        // 道をつぶして駅にすることもできるが、ここでは考慮しない
        if (board.is_station(ny, nx)) {
          parent_direction[ny][nx] = di;
          ty = ny, tx = nx;
          is_reach = true;
          break;
        } else if (board.is_blank_space(ny, nx)) {
          if (chmin(distance_points[ny][nx], distance_points[y][x] + 1)) {
            parent_direction[ny][nx] = di;
            dq.emplace(ny, nx);
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
  assert(0 <= ty && ty < 50 && 0 <= tx && tx < 50);
  int last = parent_direction[ty][tx];
  int y = ty, x = tx;
  while (true) {
    assert(0 <= y && y < 50 && 0 <= x && x < 50);
    assert(!board.is_track(y, x));
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

vector<Operation> connect_station_early(int sy, int sx, int ty, int tx) {
  vector<Operation> ret;
  if (sx > tx) {
    swap(sy, ty);
    swap(sx, tx);
  }

  vector dp(50, vector<int>(50, -1));
  dp[sy][sx] = 0;
  const int TOP = 0, BOTTOM = 1, LEFT = 2, RIGHT = 3;
  for (int y = sy;; sy <= ty ? y++ : y--) {
    for (int x = sx; x <= tx; x++) {
      dp[y][x] += is_citizen_use_station[y][x];
      if (x < tx && chmax(dp[y][x + 1], dp[y][x])) {
        parent_direction[y][x + 1] = RIGHT;
      }
      if (y != ty) {
        if (sy < ty && chmax(dp[y + 1][x], dp[y][x])) {
          parent_direction[y + 1][x] = BOTTOM;
        }
        if (sy > ty && chmax(dp[y - 1][x], dp[y][x])) {
          parent_direction[y - 1][x] = TOP;
        }
      }
    }
    if (y == ty) break;
  }
  int last = parent_direction[ty][tx];
  int y = ty, x = tx;
  while (true) {
    assert(0 <= y && y < 50 && 0 <= x && x < 50);
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
      debug(y, x, last, parent_direction[y][x]);
      Operation::debug_ope_list(ret);
      debug(distance_points);
      debug(parent_direction);
      assert(false);
    }
    last = parent_direction[y][x];
  }
  return ret;
}

using ScoreType = int;
class State {
 private:
  void check_update_station(int oy, int ox) {
    if (!board_.is_station(oy, ox)) return;

    for (auto v : land_user_list[oy][ox]) {
      if (board_.commutable_citizens_.test(v)) continue;
      board_.commutable_citizens_.set(v);
      int v2 = v < input_M ? v : v - input_M;
      if (board_.is_commutable_citizens(v2)) {
        this->income_ += input_citizen_list[v2].dist_;
      }
    }
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

  void apply_ope_state(const Operation& ope, const Operation& last_ope) {
    ans_.push_back(ope);
    if (ope.get_type() != WAIT) {
      int type = ope.get_type(), y = ope.get_y(), x = ope.get_x();

      assert(money_ >= (type == STATION ? 5000 : 100));
      money_ -= type == STATION ? 5000 : 100;

      this->board_.apply_ope_board(ope, last_ope);

      if (type == STATION) {
        check_update_station(y, x);
      } else if (type == TRACK_TB) {
        check_update_station(y - 1, x);
        check_update_station(y + 1, x);
      } else if (type == TRACK_LR) {
        check_update_station(y, x - 1);
        check_update_station(y, x + 1);
      } else if (type == TRACK_LT) {
        check_update_station(y - 1, x);
        check_update_station(y, x - 1);
      } else if (type == TRACK_LB) {
        check_update_station(y + 1, x);
        check_update_station(y, x - 1);
      } else if (type == TRACK_RT) {
        check_update_station(y - 1, x);
        check_update_station(y, x + 1);
      } else if (type == TRACK_RB) {
        check_update_station(y + 1, x);
        check_update_station(y, x + 1);
      }
    }
    this->consume_turn();
  }

  // 現在のターン
  int get_turn() { return (int)ans_.size(); }

  int predict_turn(Action& action) {
    int ret = this->get_turn();

    // ceil((cost - have) / earn) を整数演算で実現する関数
    // have >= cost のときは 0 を返す
    // earn > 0 を仮定
    auto wait_turn = [&](int have, int cost, int earn) {
      if (have >= cost) return 0;  // 待機不要
      // ceil((cost - have) / (double)earn)
      return (cost - have + earn - 1) / earn;
    };

    // O(1) で最小ターンを予測
    auto predict_turn_fast = [&](int money, int earn, int track_count) {
      // まず「線路 track_count 本を連続で建設するための待機ターン」を x とする
      int x = 0;
      if (earn >= 100) {
        // 1本目を建てるのに必要な 100 円を満たすまで待つだけ
        x = wait_turn(money, 100, earn);
      } else {
        // earn < 100
        // track_count 本を連続で建てきるのに必要な初期所持金
        //   = 100 * track_count - (track_count - 1) * earn
        int need = 100 * track_count - (track_count - 1) * earn;
        x = wait_turn(money, need, earn);
      }

      // x ターン待機後に所持金はいくらか
      int afterWait = money + x * earn;

      // そこから連続で track_count 本建設すると、最終的な所持金は
      //   afterWait + track_count*(earn - 100)
      int M_afterTrack = afterWait + track_count * (earn - 100);

      // 次に駅を建設する前に、5000 円足りない分を待機
      int y = wait_turn(M_afterTrack, 5000, earn);

      // 線路建設トータル = x(待機) + track_count(建設)
      // 駅建設トータル   = y(待機) + 1(建設)
      // 合計
      return (x + track_count) + (y + 1);
    };

    return ret + predict_turn_fast(this->money_, this->income_,
                                   (int)action.opes_.size());
  }
  // 実際に実行せずにスコアを求める
  int predict_score(int turn, Action& action) {
    int ret = money_;
    ret += (turn - (int)ans_.size() - 1) * income_;
    int next_income = action.earn_ + income_;
    ret += (input_T - turn + 1) * next_income;
    ret -= 100 * (int)action.opes_.size() + 5000;
    return ret;
  }

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
    Operation last_ope = wait_ope;

    for (auto& ope : action.opes_) {
      // debug(ope.get_type(), ope.get_y(), ope.get_x(), this->money_,
      // this->income_); もう駅が立ってたら道を立てる必要なし
      if (this->board_.is_station(ope.get_y(), ope.get_x())) continue;
      while (this->money_ < 100) this->apply_ope_state(wait_ope, last_ope);
      this->apply_ope_state(ope, last_ope);
      last_ope = ope;
    }
    if (action.sy_ != -1 && !board_.is_station(action.sy_, action.sx_)) {
      while (this->money_ < 5000) this->apply_ope_state(wait_ope, last_ope);
      Operation ope(STATION, action.sy_, action.sx_);
      this->apply_ope_state(ope, last_ope);
    }
    if (!board_.is_station(action.ty_, action.tx_)) {
      while (this->money_ < 5000) this->apply_ope_state(wait_ope, last_ope);
      Operation ope(STATION, action.ty_, action.tx_);
      this->apply_ope_state(ope, wait_ope);
    }
  }

  void calc_operations(Action& action) {
    // 線路をつぶして駅にする場合
    if (this->board_.is_track(action.ty_, action.tx_)) return;
    action.opes_ = connect_station(action.ty_, action.tx_, this->board_);
    // 接続不能で悲しい
    if (action.opes_.empty()) action.action_type_ = -1;
  }

  vector<Action> legal_actions() {
    vector<Action> ret;

    // 小さい earn_ を優先
    auto cmp = [](const Action& a, const Action& b) {
      return a.earn_ > b.earn_;
    };
    priority_queue<Action, vector<Action>, decltype(cmp)> pq(cmp);
    for (auto yx : citizen_use_station_set) {
      int ty = yx / 50, tx = yx % 50;
      // rep(ty, 50) rep(tx, 50) {
      int earn = 0;

      vector<int> vec = this->board_.list_new_commuters(ty, tx);
      for (auto v : vec) earn += input_citizen_list[v].dist_;

      if (earn == 0) continue;

      if (pq.size() == PARAM_LEGAL_ACTION_COUNT) {
        if (pq.top().earn_ >= earn) continue;
        pq.pop();
      }
      Action action;
      action.action_type_ = 1;
      action.sy_ = -1, action.ty_ = ty, action.tx_ = tx;
      action.earn_ = earn;
      action.cost_ = 0;
      pq.emplace(action);
    }

    ret.reserve(PARAM_LEGAL_ACTION_COUNT);
    while (pq.size()) {
      ret.emplace_back(pq.top());
      pq.pop();
    }

    return ret;
  }
};
// 探索時のソート用に評価を比較する
bool operator<(const State& state_1, const State& state_2) {
  return state_1.evaluated_score_ < state_2.evaluated_score_;
}

// 最初の1手は駅を2つ建てて間を結ぶ
void early_stage(vector<PriorityQueue<State>>& beam) {
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

      vector<Operation> opes = connect_station_early(sy, sx, ty, tx);
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
    Action action;
    action.action_type_ = -1;
    return action;
  };

  int last_dist = -1;
  rep(i, PARAM_EARLY_ACTION_COUNT) {
    State state(input_K);
    Action action2 = get_conenct_action(state, last_dist);
    if (action2.action_type_ == -1) return;
    // debug(action2.sx_, action2.sy_, action2.tx_, action2.ty_);
    state.exec_connect_action(action2);
    state.evaluate_score();
    beam[state.get_turn()].push(state);
    if (beam[state.get_turn()].size() == PARAM_BEAM_WIDTH) {
      last_dist = action2.earn_;
    }
  }
}

vector<Operation> solve(TimeKeeper& time_keeper) {
  vector<Operation> ret;
  auto beam = vector<PriorityQueue<State>>(input_T + 1);
  rep(i, beam.size()) beam[i] = PriorityQueue<State>();

  // auto debug_beam = [&]() {
  //   rep(i, input_T + 1) { debug(i, beam[i].income_, beam[i].money_); }
  // };

  early_stage(beam);

  int mx_score = input_K;
  int count = 0;
  for (;; count++) {
    for (int t = 1; t < input_T; t++) {
      auto& now_beam = beam[t];
      for (int i = 0; i < PARAM_BEAM_WIDTH; i++) {
        if (now_beam.empty()) break;
        State now_state = now_beam.get_max();
        now_beam.pop_max();
        assert(now_state.income_ > 0);
        if (chmax(mx_score, now_state.evaluated_score_)) {
          ret = now_state.ans_;
        }

        vector<Action> legal_actions = now_state.legal_actions();

        auto& stations = now_state.board_.stations_;

        for (auto& action : legal_actions) {
          if (action.action_type_ == -1) continue;
          State next_state = now_state;
          next_state.calc_operations(action);
          if (action.action_type_ != -1) {
            // ここで先にスコアとターン計算できるから枝刈りできるね？
            int predict_turn = next_state.predict_turn(action);
            if (predict_turn > input_T) continue;
            int predict_score = next_state.predict_score(predict_turn, action);

            stations.set(action.ty_ * 50 + action.tx_);
            if (!chmax(memo[stations], predict_score)) {
              stations.reset(action.ty_ * 50 + action.tx_);
              continue;
            }
            stations.reset(action.ty_ * 50 + action.tx_);

            if (now_beam.size() < PARAM_BEAM_WIDTH) {
              next_state.exec_connect_action(action);
              next_state.evaluate_score();
              beam[next_state.get_turn()].push(next_state);

              // if (next_state.get_turn() != predict_turn) {
              //   debug(next_state.get_turn(), predict_turn);
              //   assert(false);
              // }
              // if (next_state.evaluated_score_ != predict_score) {
              //   debug(next_state.money_, next_state.income_,
              //         next_state.ans_.size());
              //   debug(next_state.evaluated_score_, predict_score,
              //   predict_turn,
              //         action.earn_);
              //   assert(false);
              // }
            } else {
              // now_beam.get_min().evaluated_score_の高速化
              if (now_beam.d[now_beam.d.size() < 2u ? 0 : 1].evaluated_score_ <
                  predict_score) {
                now_beam.pop_min();
                next_state.exec_connect_action(action);
                next_state.evaluate_score();
                beam[next_state.get_turn()].push(next_state);

                // if (next_state.get_turn() != predict_turn) {
                //   debug(next_state.get_turn(), predict_turn);
                //   assert(false);
                // }
                // if (next_state.evaluated_score_ != predict_score) {
                //   debug(next_state.money_, next_state.income_,
                //         next_state.ans_.size());
                //   debug(next_state.evaluated_score_, predict_score,
                //         predict_turn, action.earn_);
                //   assert(false);
                // }
              }
            }
          }
        }
      }
      if (time_keeper.isTimeOver()) break;
    }
    if (time_keeper.isTimeOver()) break;
  }
  cerr << "count: " << count << endl;
  return ret;
}

// 長さ調整や、途中からのwait調整を行う
void adjast_ans(vector<Operation>& operation_list) {
  // 長すぎたら切る
  while (operation_list.size() > input_T) operation_list.pop_back();

  // シミュレートして、最適な位置からwaitを開始する

  State state(input_K);
  // ここから全てwaitした場合の金額
  int exepted_money_max = input_K, max_idx = -1;

  Operation wait_ope(WAIT);
  Operation last_ope = wait_ope;

  rep(ti, operation_list.size()) {
    state.apply_ope_state(operation_list[ti], last_ope);
    if (operation_list[ti].get_type() != WAIT) last_ope = operation_list[ti];

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
  auto time_keeper = TimeKeeper(PARAM_TIME_THRESHOLD);

  exec_input();
  calc_land_user_list();
  initialize_citizen_use_station();

  vector<Operation> ans = solve(time_keeper);
  adjast_ans(ans);
  exec_output(ans);

  cerr << "経過ms:" << time_keeper.getTime() << endl;
}