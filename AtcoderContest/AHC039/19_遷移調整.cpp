#pragma region header
#include <bits/stdc++.h>
using namespace std;

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

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#pragma endregion header

// #pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// static uint32_t randXor() {
//   static uint32_t x = 123456789;
//   static uint32_t y = 362436069;
//   static uint32_t z = 521288629;
//   static uint32_t w = 88675123;
//   uint32_t t;

//   t = x ^ (x << 11);
//   x = y;
//   y = z;
//   z = w;
//   return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
// }

static uint32_t s0 = 123456789, s1 = 362436069, s2 = 521288629, s3 = 88675123;
static inline uint32_t randXor() {
  uint32_t t = s1 << 9;
  uint32_t r = s0 + s3;  // 戻り値を直接計算
  s2 ^= s0;
  s3 ^= s1;
  s1 ^= s2;
  s0 ^= s3;
  s2 ^= t;
  s3 = (s3 << 11) | (s3 >> 21);  // 32bitなのでシフト量は修正
  return r;
}

// 0以上1未満の小数をとる乱数
static double rand01() { return (randXor() + 0.5) * (1.0 / UINT_MAX); }

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

constexpr int input_N = 5000;
array<int, input_N> input_saba_X, input_saba_Y;
array<int, input_N> input_iwashi_X, input_iwashi_Y;

array<array<int, 320>, 320> grid_score;
array<array<char, 322>, 322> grid_on;

void process_input() {
  int dummy;
  cin >> dummy;
  rep(i, input_N) cin >> input_saba_X[i] >> input_saba_Y[i];
  rep(i, input_N) cin >> input_iwashi_X[i] >> input_iwashi_Y[i];
}

// grid_number * grid_number 個に分割し、各グリッドのスコアを求める
void calc_grid_score(int grid_number) {
  rep(y, grid_number) rep(x, grid_number) grid_score[y][x] = 0;

  const int grid_size = 100000 / grid_number;
  rep(i, input_N) {
    int x = input_saba_X[i] / grid_size;
    int y = input_saba_Y[i] / grid_size;
    grid_score[grid_number - y - 1][x]++;
  }
  rep(i, input_N) {
    int x = input_iwashi_X[i] / grid_size;
    int y = input_iwashi_Y[i] / grid_size;
    grid_score[grid_number - y - 1][x]--;
  }
}

void init_grid_on(int grid_number) {
  rep(i, grid_number + 2) rep(j, grid_number + 2) grid_on[i][j] = true;
  rep(k, 2) rep(i, grid_number + 2) grid_on[i][k] =
      grid_on[i][grid_number + 1 - k] = grid_on[k][i] =
          grid_on[grid_number + 1 - k][i] = false;
}

void output_hand_on_wall(int grid_number) {
  const int grid_size = 100000 / grid_number;
  constexpr int LEFT = 0, TOP = 1, RIGHT = 2, DOWN = 3;

  // 適当な始点を探す
  int start_y = -1, start_x = -1;
  rep(i, grid_number) {
    rep(j, grid_number) {
      if (grid_on[i][j]) {
        start_y = i, start_x = j;
        break;
      }
    }
    if (start_y != -1) break;
  }
  // 右手法で復元
  vector<int> out_y, out_x;
  int now_y = start_y, now_x = start_x, direction = RIGHT;
  out_y.push_back(now_y * grid_size);
  out_x.push_back(now_x * grid_size);
  do {
    if (direction == RIGHT) {
      now_x++;
      // 上、右、下の優先度
      if (grid_on[now_y - 1][now_x]) {
        direction = TOP;
      } else if (grid_on[now_y][now_x]) {
        direction = RIGHT;
      } else {
        direction = DOWN;
      }
    } else if (direction == TOP) {
      now_y--;
      // 左、上、右の優先度
      if (grid_on[now_y - 1][now_x - 1]) {
        direction = LEFT;
      } else if (grid_on[now_y - 1][now_x]) {
        direction = TOP;
      } else {
        direction = RIGHT;
      }
    } else if (direction == DOWN) {
      now_y++;
      // 右、下、左の優先度
      if (grid_on[now_y][now_x]) {
        direction = RIGHT;
      } else if (grid_on[now_y][now_x - 1]) {
        direction = DOWN;
      } else {
        direction = LEFT;
      }
    } else if (direction == LEFT) {
      now_x--;
      // 下、左、上の優先度
      if (grid_on[now_y][now_x - 1]) {
        direction = DOWN;
      } else if (grid_on[now_y - 1][now_x - 1]) {
        direction = LEFT;
      } else {
        direction = TOP;
      }
    }
    out_y.push_back(now_y * grid_size);
    out_x.push_back(now_x * grid_size);
  } while (now_y != start_y || now_x != start_x);
  // 最後の頂点は出力不要
  out_x.pop_back(), out_y.pop_back();

  // まっすぐな頂点はいらないので削除する(1000頂点制限回避用)
  if (out_y.size() > 1000) {
    vector<int> new_out_y, new_out_x;
    rep(i, out_y.size()) {
      if (i < 2) {
        new_out_y.push_back(out_y[i]);
        new_out_x.push_back(out_x[i]);
      } else {
        int sz = (int)new_out_y.size();
        int y1 = out_y[i], x1 = out_x[i];
        int y2 = new_out_y[sz - 1], x2 = new_out_x[sz - 1];
        int y3 = new_out_y[sz - 2], x3 = new_out_x[sz - 2];
        if ((y1 == y2 && y2 == y3) || (x1 == x2 && x2 == x3)) {
          new_out_y.pop_back();
          new_out_x.pop_back();
        }
        new_out_y.push_back(out_y[i]);
        new_out_x.push_back(out_x[i]);
      }
    }
    swap(new_out_y, out_y);
    swap(new_out_x, out_x);
  }
  out(out_y.size());
  rep(i, out_y.size()) out(out_x[i] - grid_size, 100000 + grid_size - out_y[i]);
}

void double_grid(int& grid_number, int& grid_size) {
  grid_number *= 2;
  grid_size = 100000 / grid_number;
  calc_grid_score(grid_number);

  for (int i = grid_number; i >= 1; i--)
    for (int j = grid_number; j >= 1; j--) {
      grid_on[i][j] = grid_on[(i + 1) / 2][(j + 1) / 2];
    }
}

/**
 * 自分を除く
 * 0 1 2
 * 3   4
 * 5 6 7
 */
array<int, 256> is_onable;
array<int, 256> is_offable;

void init_is_switchable() {
  rep(bit, 1 << 8) {
    int cnt_on = ((bit >> 1) & 1) + ((bit >> 3) & 1) + ((bit >> 4) & 1) +
                 ((bit >> 6) & 1);
    // OFFにするパターン
    if (cnt_on == 4) {
      // 周囲が全部ONならng
      is_offable[bit] = false;
    } else {
      is_offable[bit] =
          ((bit >> 1) & 1) + ((bit >> 3) & 1) + ((bit >> 4) & 1) +
              ((bit >> 6) & 1) -
              ((bit >> 0) & 1) * ((bit >> 1) & 1) * ((bit >> 3) & 1) -
              ((bit >> 1) & 1) * ((bit >> 2) & 1) * ((bit >> 4) & 1) -
              ((bit >> 3) & 1) * ((bit >> 5) & 1) * ((bit >> 6) & 1) -
              ((bit >> 4) & 1) * ((bit >> 6) & 1) * ((bit >> 7) & 1) ==
          1;
    }
    // ONにするパターン
    if (cnt_on == 0) {
      // 周囲が全部ONならng
      is_onable[bit] = false;
    } else {
      is_onable[bit] =
          !((bit >> 1) & 1) + !((bit >> 3) & 1) + !((bit >> 4) & 1) +
              !((bit >> 6) & 1) -
              !((bit >> 0) & 1) * !((bit >> 1) & 1) * !((bit >> 3) & 1) -
              !((bit >> 1) & 1) * !((bit >> 2) & 1) * !((bit >> 4) & 1) -
              !((bit >> 3) & 1) * !((bit >> 5) & 1) * !((bit >> 6) & 1) -
              !((bit >> 4) & 1) * !((bit >> 6) & 1) * !((bit >> 7) & 1) ==
          1;
    }
  }
}

// グリッドをオンオフできるか高速
inline bool is_switchable_grid_fast(int y2, int x2) {
  int key = grid_on[y2][x2] + (grid_on[y2][x2 + 1] << 1) +
            (grid_on[y2][x2 + 2] << 2) + (grid_on[y2 + 1][x2] << 3) +
            (grid_on[y2 + 1][x2 + 2] << 4) + (grid_on[y2 + 2][x2] << 5) +
            (grid_on[y2 + 2][x2 + 1] << 6) + (grid_on[y2 + 2][x2 + 2] << 7);
  return grid_on[y2 + 1][x2 + 1] ? is_offable[key] : is_onable[key];
}

// 320*320
constexpr int max_nn = 320 * 320;
int now_n = 100;
struct IndexSet {
  vector<int> que;
  array<int, max_nn> pos;

  IndexSet() {
    rep(i, max_nn) pos[i] = -1;
    que.reserve(max_nn);
  }

  void add(int v) {
    pos[v] = (int)que.size();
    que.push_back(v);
  }

  void remove(int v) {
    int p = pos[v];
    int b = que.back();
    que[p] = b;
    que.pop_back();
    pos[b] = p;
    pos[v] = -1;
  }

  bool contains(int v) const { return pos[v] != -1; }

  int size() const { return (int)que.size(); }

  // AHC039に固有のメソッド
  void double_set(int grid_number) {
    que.clear();

    const int prev_grid_number = grid_number / 2;
    for (int i = now_n - 1; i >= 0; i--) {
      if (pos[i] != -1) {
        int y = i / prev_grid_number;
        int x = i % prev_grid_number;

        int v1 = y * 2 * grid_number + x * 2;
        int v2 = v1 + 1;
        int v3 = v1 + grid_number;
        int v4 = v3 + 1;

        if (is_switchable_grid_fast(y * 2, x * 2)) this->add(v1);
        if (is_switchable_grid_fast(y * 2, x * 2 + 1)) this->add(v2);
        if (is_switchable_grid_fast(y * 2 + 1, x * 2)) this->add(v3);
        if (is_switchable_grid_fast(y * 2 + 1, x * 2 + 1)) this->add(v4);
      }
      if (i != 0) pos[i] = -1;
    }
    now_n *= 4;
  }
};

// diff_perimeterを求める
int calc_diff_perimeter(int y2, int x2) {
  y2++, x2++;
  // 周囲のonの数を数える
  int cnt_on = grid_on[y2 - 1][x2] + grid_on[y2][x2 - 1] + grid_on[y2 + 1][x2] +
               grid_on[y2][x2 + 1];
  if (grid_on[y2][x2]) {
    if (cnt_on == 1) return -2;
    if (cnt_on == 3) return 2;
  } else {
    if (cnt_on == 1) return 2;
    if (cnt_on == 3) return -2;
  }
  return 0;
}

// 8近傍を更新
vector<int> dy = {0, 0, -1, 1, -1, -1, 1, 1};
vector<int> dx = {-1, 1, 0, 0, -1, 1, -1, 1};
void update_index_set(int y, int x, IndexSet& index_set, int grid_number) {
  rep(i, 4) {
    int y2 = y + dy[i], x2 = x + dx[i];
    if (y2 >= 0 && x2 >= 0 && y2 < grid_number && x2 < grid_number) {
      int idx_2 = y2 * grid_number + x2;
      if (is_switchable_grid_fast(y2, x2)) {
        if (!index_set.contains(idx_2)) index_set.add(idx_2);
      } else {
        if (index_set.contains(idx_2)) index_set.remove(idx_2);
      }
    }
  }
  for (int i = 4; i < 8; i++) {
    int y2 = y + dy[i], x2 = x + dx[i];
    if (y2 >= 0 && x2 >= 0 && y2 < grid_number && x2 < grid_number &&
        grid_on[y2][x] == grid_on[y2][x]) {
      int idx_2 = y2 * grid_number + x2;
      if (is_switchable_grid_fast(y2, x2)) {
        if (!index_set.contains(idx_2)) index_set.add(idx_2);
      } else {
        if (index_set.contains(idx_2)) index_set.remove(idx_2);
      }
    }
  }
}

constexpr int init_grid_number = 10;

int main() {
  process_input();
  init_is_switchable();

  // 10 * 10個のグリッドに分割する
  int grid_number = init_grid_number;
  int grid_size = 100000 / grid_number;
  // グリッドごとのスコアを求める
  calc_grid_score(grid_number);
  init_grid_on(grid_number);
  IndexSet index_set;
  rep(y, grid_number) rep(x, grid_number) {
    if (is_switchable_grid_fast(y, x)) index_set.add(y * grid_number + x);
  }
  // 周長(grid_onの初期位置によって変える必要がある)
  int perimeter = grid_size * 8 * 4;
  int score = 1;
  rep(y, grid_number) rep(x, grid_number) {
    if (grid_on[y + 1][x + 1]) score += grid_score[y][x];
  }
  int best_score = score;

  // vector<int> times = {200, 400, 500, 500, 200, 150};
  vector<int> times = {210, 410, 500, 500, 200, 160};
  vector<double> temps = {5e3, 1e1, 5e0, 1e0, 3e-1, 3e-1, 3e-1};
  // vector<double> temps = {5e2, 5e1, 1e1, 5e0, 1e0, 3e-1, 3e-1};
  rep(i, times.size()) times[i] *= 3;
  int phase_index = 0;
  double start_temp = temps[phase_index];    // 開始時の温度
  double end_temp = temps[phase_index + 1];  // 終了時の温度
  int time_threshold = times[phase_index];
  auto time_keeper = TimeKeeper(time_threshold);

  int loop_count = 0;

  double progress_ratio =
      (double)time_keeper.getTime() / (double)time_threshold;
  double temp_inv = 1.0 / (pow(start_temp, 1.0 - progress_ratio) *
                           pow(end_temp, progress_ratio));
  double probability = 0;
  double time_threshold_inv = 1 / (double)time_threshold;

  // 焼きなましの統計値
  int last_score = score;
  int iter_count = 0;
  int accepted = 0;
  int updated = 0;
  int on_neighbor = 0, off_neighbor = 0;
  auto print_statistic = [&]() {
    cerr << "init_score: " << last_score << endl;
    cerr << "score: " << score << endl;
    cerr << "all iter: " << loop_count - iter_count << endl;
    cerr << "accepted: " << accepted << endl;
    cerr << "updated: " << updated << endl;
    cerr << "on, off: " << on_neighbor << ", " << off_neighbor << endl;
    last_score = score;
    iter_count = loop_count;
    accepted = 0;
    updated = 0;
    on_neighbor = off_neighbor = 0;
  };

  while (true) {
    loop_count++;
    if ((loop_count & 1023) == 0) {
      if (time_keeper.isTimeOver()) {
        output_hand_on_wall(grid_number);
        // debug(loop_count, score);
        // print_statistic();
        phase_index++;
        if (phase_index == (int)times.size()) break;
        double_grid(grid_number, grid_size);

        index_set.double_set(grid_number);

        start_temp = temps[phase_index];
        end_temp = temps[phase_index + 1];
        time_threshold = times[phase_index];
        time_keeper = TimeKeeper(time_threshold);
        time_threshold_inv = 1 / (double)time_threshold;
      } else {
        progress_ratio = (double)time_keeper.getTime() * time_threshold_inv;
        // temp_inv =
        //     1.0 / (start_temp + (end_temp - start_temp) * progress_ratio);
        temp_inv = 1.0 / (pow(start_temp, 1.0 - progress_ratio) *
                          pow(end_temp, progress_ratio));
      }
    }

    int idx = randXor() % index_set.size();
    int y = index_set.que[idx] / grid_number;
    int x = index_set.que[idx] % grid_number;

    if (grid_on[y + 1][x + 1]) {
      off_neighbor++;
    } else {
      on_neighbor++;
    }

    int diff_perimeter = calc_diff_perimeter(y, x) * grid_size;

    if (perimeter + diff_perimeter > 400000) continue;

    int delta_score =
        grid_on[y + 1][x + 1] ? -grid_score[y][x] : grid_score[y][x];
    probability = exp((double)delta_score * temp_inv);
    if (probability >= rand01()) {
      accepted++;
      if (chmax(best_score, score)) updated++;
      // 受理
      grid_on[y + 1][x + 1] = grid_on[y + 1][x + 1] ^ 1;
      score += delta_score;
      perimeter += diff_perimeter;
      // 更新
      update_index_set(y, x, index_set, grid_number);
    }
  }
  // cerr << "loop_count: " << loop_count << endl;
  // cerr << "score: " << score << endl;
  cerr << score << endl;

  // 左手法で復元
  output_hand_on_wall(grid_number);
}