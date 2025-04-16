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

// 乱数生成 (XorShift 32)
static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// 時間計測用
class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // time_thresholdをミリ秒で指定
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

static const int N = 100;
static const int L = 500000;
static vector<int> Tvec(N);

struct Employee {
  int a, b;  // a_i, b_i
};

///////////////////////////////////////////////////////
// 部分シミュレーション
//   steps 回だけ週を進め、各社員が担当した回数 usageCount[i] を返す。
//   初週の担当は社員0固定。
//   t回目の担当が奇数なら a[now], 偶数なら b[now].
///////////////////////////////////////////////////////
vector<int> partialSimulation(const vector<Employee>& employees, int steps) {
  vector<int> usageCount(N, 0);
  int now = 0;
  for (int week = 0; week < steps; week++) {
    usageCount[now]++;
    int c = usageCount[now];
    if (c % 2 == 1) {
      now = employees[now].a;
    } else {
      now = employees[now].b;
    }
  }
  return usageCount;
}

///////////////////////////////////////////////////////
// 誤差計算
//   部分シミュレーション結果 usageCount を L/steps 倍して近似分布を得る
//   その上で |t_i - T_i| の総和を返す。
//   返り値が小さいほど良い (最終的に 10^6 - E がスコア)
///////////////////////////////////////////////////////
long long computeError(const vector<int>& usageCount, int steps) {
  // usageCount[i] を (L / (double)steps) 倍して「近似的な担当回数」を算出
  // ただし一応浮動小数計算するが、誤差評価のために long long にまとめてもOK
  long double ratio = (long double)L / (long double)steps;
  long long sumDiff = 0;
  for (int i = 0; i < N; i++) {
    long double approximate = usageCount[i] * ratio;  // 担当回数の近似
    long long approx_ll = (long long)llroundl(approximate);
    sumDiff += llabs(approx_ll - Tvec[i]);
  }
  return sumDiff;
}

///////////////////////////////////////////////////////
// メインロジック
///////////////////////////////////////////////////////
int main() {
  // 入力受付
  {
    int dummyN, dummyL;
    cin >> dummyN >> dummyL;  // N=100, L=500000 (問題の仕様)
    for (int i = 0; i < N; i++) cin >> Tvec[i];
  }

  // 時間制限 (ms)
  TimeKeeper tk(1950);

  // (a_i, b_i) の初期化
  //   - まずは「ランダムに」あるいは「単純なサイクル」で割り当て
  vector<Employee> employees(N);
  {
    // 例1: 完全ランダムにする
    // (どちらでもいいですが,
    // 遷移先が自分自身ばかりになるのは避けた方が良いかも)
    for (int i = 0; i < N; i++) {
      employees[i].a = randXor() % N;
      employees[i].b = randXor() % N;
    }
    // 例2: a_i=b_i=(i+1)%N というシンプルなサイクル
    // for(int i=0;i<N;i++){
    //   employees[i].a=(i+1)%N;
    //   employees[i].b=(i+1)%N;
    // }
  }

  // 部分シミュレーション (初期解)
  const int SIM_STEPS = 5000;  // 部分シミュレーションする週数(要調整)
  auto usageCountInit = partialSimulation(employees, SIM_STEPS);
  long long bestScore = computeError(usageCountInit, SIM_STEPS);
  vector<Employee> bestEmployees = employees;

  // 局所探索 (ランダムに少し書き換えて改善を試みる)
  // 時間切れになるまで繰り返す
  while (!tk.isTimeOver()) {
    // ランダムに1人 (emp) を選び, a/bどちらかを選び, 値を変更してみる
    int emp = randXor() % N;
    bool chooseA = (randXor() & 1);
    int oldVal = chooseA ? employees[emp].a : employees[emp].b;
    int newVal = randXor() % N;
    // もし同じ値になったら変化がないので変える
    if (newVal == oldVal) continue;

    // 候補解として差し替え
    if (chooseA) {
      employees[emp].a = newVal;
    } else {
      employees[emp].b = newVal;
    }

    // 部分シミュレーションして誤差評価
    auto usageCandidate = partialSimulation(employees, SIM_STEPS);
    long long candidateScore = computeError(usageCandidate, SIM_STEPS);

    // 改善したら採用、悪化したら元に戻す
    if (candidateScore < bestScore) {
      bestScore = candidateScore;
      bestEmployees = employees;
    } else {
      // 戻す
      if (chooseA) {
        employees[emp].a = oldVal;
      } else {
        employees[emp].b = oldVal;
      }
    }
  }

  // 最終的に bestEmployees を出力
  // 問題の出力仕様: i番目の行に「a_i b_i」を出力 (0<=i<=N-1)
  for (int i = 0; i < N; i++) {
    cout << bestEmployees[i].a << " " << bestEmployees[i].b << "\n";
  }
  cout.flush();

  return 0;
}
