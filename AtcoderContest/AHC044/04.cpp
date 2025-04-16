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
static double rand01() {
  // UINT_MAX ~ 4,294,967,295
  return (randXor() + 0.5) * (1.0 / (double)UINT_MAX);
}

class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限(ミリ秒)を指定
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}
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
  int id_, target_;        // 社員ID, 目標割当回数
  int a_, b_;              // (a_x, b_x)
  int predict_count_ = 0;  // フロー近似での推定割当回数

  Employee() {}
  Employee(int id, int target) : id_(id), target_(target) {}

  void debug_pirnt() {
    cerr << id_ << " " << target_ << " " << a_ << " " << b_ << " "
         << predict_count_ << endl;
  }
};

//--------------------------
// 入力
//--------------------------
void exec_input() {
  int _;
  cin >> _ >> _;  // 今回 N=100, L=500000固定
  rep(i, input_N) cin >> input_T[i];
}

//--------------------------
// 出力
//--------------------------
void exec_output(vector<Employee>& employee_list) {
  // 社員id_昇順に並べて (a_i,b_i) を出力
  sort(all(employee_list),
       [](const Employee& a, const Employee& b) { return a.id_ < b.id_; });
  rep(i, input_N) {
    cout << employee_list[i].a_ << " " << employee_list[i].b_ << "\n";
  }
  cout << flush;
}

//---------------------------------------------------
// (参考) 実際 50万週シミュレーションしてスコア計算
//        (コンテスト提出時には時間コストが大きいので注意)
//---------------------------------------------------
int calc_score(vector<Employee>& employee_list) {
  int score = 1000000;
  vector<int> id2idx(input_N);
  rep(i, input_N) id2idx[employee_list[i].id_] = i;

  vector<int> actual_count(input_N, 0);

  int now = 0;  // 最初の週は社員0
  rep(turn, input_L) {
    int idx = id2idx[now];
    actual_count[idx]++;
    if (actual_count[idx] % 2 == 1) {
      now = employee_list[idx].a_;
    } else {
      now = employee_list[idx].b_;
    }
  }

  // 誤差( sum |actual_count_i - target_i| ) を 1000000 - ...
  rep(i, input_N) { score -= abs(actual_count[i] - employee_list[i].target_); }
  return score;
}

//------------------------------
// フロー近似: predict_count_ を算出
//------------------------------
void update_predict_count_flow(vector<Employee>& emps, int iter_count) {
  // 初期 X(0) = (T_i / sumT)*L
  double sumT = 0.0;
  rep(i, input_N) sumT += emps[i].target_;
  vector<double> dist(input_N, 0.0);

  if (sumT < 1e-9) {
    // 全員 0
    rep(i, input_N) dist[i] = (double)input_L / input_N;
  } else {
    rep(i, input_N) { dist[i] = ((double)emps[i].target_ / sumT) * input_L; }
  }

  // iter_count回反復
  rep(it, iter_count) {
    vector<double> nxt(input_N, 0.0);
    rep(x, input_N) {
      double half = dist[x] * 0.5;
      nxt[emps[x].a_] += half;
      nxt[emps[x].b_] += half;
    }
    double s = 0.0;
    rep(i, input_N) s += nxt[i];
    if (s < 1e-9) {
      // すべて消滅
      rep(i, input_N) nxt[i] = (double)input_L / input_N;
    } else {
      double scale = (double)input_L / s;
      rep(i, input_N) nxt[i] *= scale;
    }
    dist = nxt;
  }

  // 丸めて predict_count_ に保存
  rep(i, input_N) { emps[i].predict_count_ = (int)round(dist[i]); }
}

//------------------------------
// コスト関数: sum of |predict_count_ - target_|
//------------------------------
int calc_cost_from_predict(const vector<Employee>& emps) {
  ll cost = 0;
  rep(i, input_N) {
    cost += llabs((ll)emps[i].predict_count_ - (ll)emps[i].target_);
  }
  return (int)cost;
}

//===================================================
// 近傍操作
//===================================================

//---------- [0] 1社員の (a_,b_) を完全ランダムに変更 ----------
void mutate_one_employee(vector<Employee>& emps) {
  int x = randXor() % input_N;
  emps[x].a_ = randXor() % input_N;
  emps[x].b_ = randXor() % input_N;
}

//---------- [1] 2社員間の (a_,b_) を丸ごと交換 ----------
void mutate_swap_edges(vector<Employee>& emps) {
  int x = randXor() % input_N;
  int y = randXor() % input_N;
  if (x == y) return;  // 同じなら意味なし
  swap(emps[x].a_, emps[y].a_);
  swap(emps[x].b_, emps[y].b_);
}

//---------- [2] 2社員間で a_かb_どちらかだけ交換 ----------
void mutate_swap_partial(vector<Employee>& emps) {
  int x = randXor() % input_N;
  int y = randXor() % input_N;
  if (x == y) return;
  bool flip = (randXor() % 2 == 0);  // 50%で選択
  if (flip) {
    // swap a_
    swap(emps[x].a_, emps[y].a_);
  } else {
    // swap b_
    swap(emps[x].b_, emps[y].b_);
  }
}

//---------- [3] 2 or 3ノードを選んでランダム変更 ----------
void mutate_multi_node_random(vector<Employee>& emps) {
  int c = 2 + (randXor() % 2);  // 2or3
  while (c--) {
    int x = randXor() % input_N;
    emps[x].a_ = randXor() % input_N;
    emps[x].b_ = randXor() % input_N;
  }
}

//---------- [4] ランダムに10ノードを選んで部分的に貪欲割り当て ----------
void mutate_subset_reassign(vector<Employee>& emps) {
  // 1) 現在のフロー近似を行い ratio[i] = T_i / (predict_count_i + eps)
  vector<Employee> tmp = emps;
  update_predict_count_flow(tmp, 5);
  vector<double> ratio(input_N);
  rep(i, input_N) {
    double eps = 1e-9;
    ratio[i] =
        (double)emps[i].target_ / max((double)tmp[i].predict_count_, eps);
  }

  // 2) 10ノードをランダム選択
  int K = 10;
  vector<int> subset(K);
  rep(i, K) { subset[i] = randXor() % input_N; }

  // 3) subset 内の x について ratio上位2人を (a_x,b_x) に
  vector<int> idx(input_N);
  iota(all(idx), 0);
  for (auto& x : subset) {
    sort(all(idx), [&](int a, int b) { return ratio[a] > ratio[b]; });
    int t1 = idx[0], t2 = idx[1];
    // t1==t2はほぼないが保険
    if (t1 == t2) t2 = (t2 + 1) % input_N;
    emps[x].a_ = t1;
    emps[x].b_ = t2;
  }
}

//---------- [5] GreedyOneNode: 1ノード x を全ペア(i,j)試して最良を選ぶ
//----------
void mutate_greedy_one_node(vector<Employee>& emps, TimeKeeper& tk) {
  // 時間ギリギリならスキップ
  if (tk.isTimeOver()) return;

  int x = randXor() % input_N;

  // 現状のコスト
  vector<Employee> base = emps;
  update_predict_count_flow(base, 3);
  int best_cost = calc_cost_from_predict(base);

  // 最良解を保存
  vector<Employee> best_ems = emps;

  // (i,j)を全探索 (100x100=10000通り)
  // 都度フロー近似(3回)→コスト計算(重いので回数注意)
  rep(i, input_N) {
    rep(j, input_N) {
      // 途中で時間切れなら中断
      if (tk.isTimeOver()) break;

      emps[x].a_ = i;
      emps[x].b_ = j;

      // コスト計算
      vector<Employee> tmp = emps;
      update_predict_count_flow(tmp, 3);
      int cst = calc_cost_from_predict(tmp);

      if (cst < best_cost) {
        best_cost = cst;
        best_ems = emps;
      }
    }
    if (tk.isTimeOver()) break;
  }

  // 最良のものを emps に反映
  emps = best_ems;
}

//--------------------------
// 初期解
//--------------------------
vector<Employee> init_1() {
  vector<Employee> employees(input_N);
  rep(i, input_N) {
    employees[i].id_ = i;
    employees[i].target_ = input_T[i];
  }
  // 例として: 目標値順にソート→(a_,b_)割り当て→元に戻す
  sort(all(employees), [&](auto& a, auto& b) { return a.target_ < b.target_; });

  for (int i = 0; i <= 96; i += 2) {
    int to = employees[i + 2].id_;
    employees[i].a_ = to;
  }
  for (int i = 99; i >= 3; i -= 2) {
    int to = employees[i - 2].id_;
    employees[i].a_ = to;
  }
  employees[98].a_ = employees[99].id_;
  employees[1].a_ = employees[0].id_;

  for (int i = 0; i < 50; i++) {
    employees[i].b_ = employees[i + 50].id_;
  }
  for (int i = 50; i < 100; i += 2) {
    if (i + 1 < 100) {
      int from = employees[i].id_;
      int to = employees[i + 1].id_;
      employees[i].b_ = to;
      employees[i + 1].b_ = from;
    }
  }
  sort(all(employees), [&](auto& a, auto& b) { return a.id_ < b.id_; });
  return employees;
}

//===================================================
// main
//===================================================
int main() {
  // 時間制限
  const int time_threshold = 19800;
  TimeKeeper time_keeper(time_threshold);

  // 入力
  exec_input();

  // 初期解生成
  vector<Employee> cur_sol = init_1();
  // 現在のコスト計算用
  update_predict_count_flow(cur_sol, 5);
  int best_cost = calc_cost_from_predict(cur_sol);
  vector<Employee> best_sol = cur_sol;

  // パラメータ
  double start_temp = 1000.0;
  double end_temp = 1.0;
  double base_time = (double)time_threshold;

  int loop_count = 0;

  while (!time_keeper.isTimeOver()) {
    loop_count++;
    // 温度を指数減衰
    double now_ms = time_keeper.getTime();
    double progress = now_ms / base_time;  // 0->1
    if (progress > 1.0) progress = 1.0;
    double temperature = start_temp * pow(end_temp / start_temp, progress);

    // 複数近傍操作をランダムに選ぶ
    int nbtype = randXor() % 4;
    vector<Employee> new_sol = cur_sol;
    switch (nbtype) {
      case 0:
        mutate_one_employee(new_sol);
        break;
      case 1:
        mutate_swap_edges(new_sol);
        break;
      case 2:
        mutate_swap_partial(new_sol);
        break;
      case 3:
        mutate_multi_node_random(new_sol);
        break;
      case 4:
        mutate_subset_reassign(new_sol);
        break;
      case 5:
        mutate_greedy_one_node(new_sol, time_keeper);
        // ここで時間超過の可能性があるので即チェック
        if (time_keeper.isTimeOver()) break;
        break;
    }

    // 近傍解 new_sol をフロー近似
    update_predict_count_flow(new_sol, 3);
    int new_cost = calc_cost_from_predict(new_sol);
    int diff = best_cost - new_cost;

    // 焼きなまし判定
    if (diff > 0) {
      // 改善
      cur_sol = new_sol;
      best_cost = new_cost;
      best_sol = new_sol;
    } else {
      // 悪化
      double prob = exp((double)diff / temperature);  // diff<0
      double r = rand01();
      if (r < prob) {
        // 受理
        cur_sol = new_sol;
      }
    }
  }

  // 最後に5回フロー近似しておく(出力前の整合)
  update_predict_count_flow(best_sol, 5);

  // 出力
  exec_output(best_sol);

  // デバッグ用: 実際にシミュレーションしてスコアを表示
  // (提出時は不要なら削ってOK)
  int final_score = calc_score(best_sol);
  cerr << "final_score: " << final_score << "\n";
  cerr << "loop_count: " << loop_count << "\n";

  return 0;
}
