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

  // インスタンス生成時から指定した時間制限を超過したか判定する。
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

constexpr int input_N = 100, input_L = 500000;
vector<int> input_T(input_N);

//--------------------------
// 社員情報を保持するクラス
//--------------------------
class Employee {
 public:
  int id_, target_;  // 社員ID, 目標割当回数
  int a_, b_;        // 遷移先 (a_x, b_x)
  int predict_count_ =
      0;  // フロー近似での推定割当回数(最終的にintに丸めて格納)

  Employee() {}
  Employee(int id, int target) : id_(id), target_(target) {}

  void debug_pirnt() {
    cerr << id_ << " " << target_ << " " << a_ << " " << b_ << " "
         << predict_count_ << endl;
  }
};

//--------------------------
// 入力・出力
//--------------------------
void exec_input() {
  int _;
  cin >> _ >> _;  // N=100, L=500000 は固定
  rep(i, input_N) cin >> input_T[i];
}

void exec_output(vector<Employee>& employee_list) {
  // 社員indexで昇順ソートして (a_i,b_i) を出力
  sort(all(employee_list),
       [](const Employee& a, const Employee& b) { return a.id_ < b.id_; });
  rep(i, input_N) {
    cout << employee_list[i].a_ << " " << employee_list[i].b_ << "\n";
  }
  cout << flush;
}

//--------------------------
// 初期解 (例)
//--------------------------
vector<Employee> init_1() {
  vector<Employee> employee_list(input_N);
  rep(i, input_N) {
    employee_list[i].id_ = i;
    employee_list[i].target_ = input_T[i];
  }
  // 目標値で昇順ソートし、IDを基準に組み合わせる適当な例
  // （ユーザの init_1() を継承）
  sort(all(employee_list), [](const Employee& a, const Employee& b) {
    return a.target_ < b.target_;
  });

  // a_ の割当 (偶数インデックスどうしで繋ぐ)
  for (int i = 0; i <= 96; i += 2) {
    int to = employee_list[i + 2].id_;
    employee_list[i].a_ = to;
  }
  for (int i = 99; i >= 3; i -= 2) {
    int to = employee_list[i - 2].id_;
    employee_list[i].a_ = to;
  }
  // 微調整
  employee_list[98].a_ = employee_list[99].id_;
  employee_list[1].a_ = employee_list[0].id_;

  // b_ の割当 (例: 前半と後半を結ぶ)
  for (int i = 0; i < 50; i++) {
    employee_list[i].b_ = employee_list[i + 50].id_;
  }
  for (int i = 50; i < input_N; i += 2) {
    if (i + 1 < input_N) {
      int from = employee_list[i].id_;
      int to = employee_list[i + 1].id_;
      employee_list[i].b_ = to;
      employee_list[i + 1].b_ = from;
    }
  }

  // ソートを戻す（id_ 昇順に整列し直し）
  sort(all(employee_list),
       [](const Employee& a, const Employee& b) { return a.id_ < b.id_; });
  return employee_list;
}

int calc_score(vector<Employee>& employee_list) {
  int score = 1000000;
  // id_ -> vector上のindex に変換するマップ
  vector<int> id2idx(input_N);
  rep(i, input_N) id2idx[employee_list[i].id_] = i;

  vector<int> actual_count(input_N);

  int now_duty = 0;  // 最初の週は社員0
  rep(turn, input_L) {
    int idx = id2idx[now_duty];
    actual_count[idx]++;
    if (actual_count[idx] % 2 == 1) {
      now_duty = employee_list[idx].a_;
    } else {
      now_duty = employee_list[idx].b_;
    }
  }
  // スコア計算 (1000000 - Σ|actial_count - target_|)
  rep(i, input_N) { score -= abs(actual_count[i] - employee_list[i].target_); }
  return score;
}

//------------------------------
// フロー近似で predict_count_ を再計算
//   iter_count 回程度の反復
//------------------------------
void update_predict_count_flow(vector<Employee>& employee_list,
                               int iter_count) {
  // (1) X(0) の初期値: T_i 比率 * L
  double sumT = 0.0;
  for (auto& e : employee_list) sumT += e.target_;
  vector<double> dist(input_N, 0.0);

  if (sumT < 1e-9) {
    // 全員のターゲットが0なら均等
    rep(i, input_N) dist[i] = (double)input_L / input_N;
  } else {
    rep(i, input_N) {
      dist[i] = ((double)employee_list[i].target_ / sumT) * input_L;
    }
  }

  // (2) 反復
  //   dist'[i] = Σ ( dist[x]/2 )_{ x s.t. a_x=i } + 同様に b_x=i
  //   最後に dist'[i] を合計=500000 にスケーリング
  rep(it, iter_count) {
    vector<double> newDist(input_N, 0.0);
    rep(x, input_N) {
      double half = dist[x] * 0.5;
      newDist[employee_list[x].a_] += half;
      newDist[employee_list[x].b_] += half;
    }
    // スケーリング
    double s = 0.0;
    for (auto& val : newDist) s += val;
    if (s < 1e-9) {
      // 流れが消滅したら均等へ
      rep(i, input_N) newDist[i] = (double)input_L / input_N;
    } else {
      double scale = (double)input_L / s;
      for (auto& val : newDist) val *= scale;
    }
    dist = newDist;
  }

  // (3) 結果を predict_count_ に格納 (丸め)
  rep(i, input_N) { employee_list[i].predict_count_ = (int)round(dist[i]); }
}

//--------------------------------------
// コスト関数: sum of |predict_count_ - target_|
// (問題文にある誤差に対応)
//--------------------------------------
int calc_cost_from_predict(const vector<Employee>& employee_list) {
  ll cost = 0;
  rep(i, input_N) {
    cost += llabs((ll)employee_list[i].predict_count_ -
                  (ll)employee_list[i].target_);
  }
  return (int)cost;
}

//=========================================================
// 近傍操作
//=========================================================

//----[0] 単純: 1社員の (a_,b_) をランダム変更
void mutate_one_employee(vector<Employee>& emps) {
  int x = randXor() % input_N;
  emps[x].a_ = randXor() % input_N;
  emps[x].b_ = randXor() % input_N;
}

//----[1] SwapEdges: 2社員間で (a_x,b_x) <-> (a_y,b_y) を丸ごと交換
void mutate_swap_edges(vector<Employee>& emps) {
  int x = randXor() % input_N;
  int y = randXor() % input_N;
  if (x == y) return;  // 同じなら意味なし
  swap(emps[x].a_, emps[y].a_);
  swap(emps[x].b_, emps[y].b_);
}

//----[2] SwapPartial: 2社員間で a_だけ or b_だけを交換
void mutate_swap_partial(vector<Employee>& emps) {
  int x = randXor() % input_N;
  int y = randXor() % input_N;
  if (x == y) return;
  bool flip = (randXor() % 2 == 0);  // 50%で a_/b_ を決める
  if (flip) {
    // swap a_
    swap(emps[x].a_, emps[y].a_);
  } else {
    // swap b_
    swap(emps[x].b_, emps[y].b_);
  }
}

//----[3] MultiNodeRandom: 2 or 3ノードを選んで (a_,b_) をランダム変更
void mutate_multi_node_random(vector<Employee>& emps) {
  int c = (randXor() % 2) + 2;  // 2or3
  while (c--) {
    int x = randXor() % input_N;
    emps[x].a_ = randXor() % input_N;
    emps[x].b_ = randXor() % input_N;
  }
}

//---------------------------------------------------
// メイン
//---------------------------------------------------
int main() {
  const int time_threshold = 1980;
  auto time_keeper = TimeKeeper(time_threshold);

  exec_input();

  // (1) 初期解
  vector<Employee> employee_list = init_1();
  int initial_score = calc_score(employee_list);
  debug(initial_score);

  // まずフロー近似で predict_count_ を求めておく
  update_predict_count_flow(employee_list, 10);
  int best_cost = calc_cost_from_predict(employee_list);
  vector<Employee> best_sol = employee_list;

  int loop_count = 0;

  double start_temp = 1e3;  // 開始時の温度
  double end_temp = 1;      // 終了時の温度
  double progress_ratio =
      (double)time_keeper.getTime() / (double)time_threshold;
  double temp = start_temp + (end_temp - start_temp) * progress_ratio;
  double probability = 0;
  double time_threshold_inv = 1 / (double)time_threshold;
  while (true) {
    loop_count++;
    if (loop_count % 64 == 0) {
      if (time_keeper.isTimeOver()) break;
      progress_ratio = (double)time_keeper.getTime() * time_threshold_inv;
      temp = start_temp + (end_temp - start_temp) * progress_ratio;
    }

    // 近傍を作成
    vector<Employee> new_sol = employee_list;

    int nbtype = randXor() % 100;
    if (nbtype < 40) {
      mutate_one_employee(new_sol);
    } else if (nbtype < 60) {
      mutate_swap_edges(new_sol);
    } else if (nbtype < 80) {
      mutate_swap_partial(new_sol);
    } else if (nbtype < 100) {
      mutate_multi_node_random(new_sol);
    }

    // predict_count_ を更新
    update_predict_count_flow(new_sol, 3);  // 少し回数を減らして高速化
    int cost_new = calc_cost_from_predict(new_sol);
    int diff = best_cost - cost_new;

    probability = exp((double)diff / temp);

    if (probability >= rand01()) {
      employee_list = new_sol;
      best_cost = cost_new;
      if (diff > 0) best_sol = new_sol;
    }
  }

  // (3) ベスト解を出力
  //   ここでは再度 predict_count_ を計算しておいてもいい
  update_predict_count_flow(best_sol, 5);

  exec_output(best_sol);

  // (4) デバッグ用に最終スコアを計算 (本番提出時には不要かも)
  //   1回のみ実際のシミュレーションしてみる
  int final_score = calc_score(best_sol);

  cerr << "final_score: " << final_score << endl;
  cerr << "loop_count: " << loop_count << endl;

  return 0;
}
