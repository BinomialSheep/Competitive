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

int input_N;
vector<int> input_saba_X(5000), input_saba_Y(5000);
vector<int> input_iwashi_X(5000), input_iwashi_Y(5000);

map<int, vector<int>> iwashi_XY_map;
map<int, vector<int>> saba_XY_map;

void process_input() {
  cin >> input_N;
  rep(i, input_N) cin >> input_saba_X[i] >> input_saba_Y[i];
  rep(i, input_N) cin >> input_iwashi_X[i] >> input_iwashi_Y[i];
}

void init_XY_map() {
  rep(i, input_N) {
    saba_XY_map[input_saba_X[i]].emplace_back(input_saba_Y[i]);
    iwashi_XY_map[input_iwashi_X[i]].emplace_back(input_iwashi_Y[i]);
  }
  for (auto& [k, vec] : saba_XY_map) sort(all(vec));
  for (auto& [k, vec] : iwashi_XY_map) sort(all(vec));
}

int main() {
  const int64_t time_threshold = 1000;
  auto time_keeper = TimeKeeper(time_threshold);
  /* input */
  process_input();
  init_XY_map();

  int saba_min_x = 1e9, saba_max_x = 0, saba_min_y = 1e9, saba_max_y = 0;
  rep(i, input_N) {
    chmax(saba_max_x, input_saba_X[i]);
    chmax(saba_max_y, input_saba_Y[i]);
    chmin(saba_min_x, input_saba_X[i]);
    chmin(saba_min_y, input_saba_Y[i]);
  }
  int saba_range_x = saba_max_x - saba_min_x;
  int saba_range_y = saba_max_y - saba_min_y;

  /* solve */
  int max_score = 0;
  int best_x1, best_x2, best_y1, best_y2;

  int loop_count = 0;

  while (!time_keeper.isTimeOver()) {
    loop_count++;
    int x1 = randXor() % saba_range_x + saba_min_x;
    int x2 = randXor() % saba_range_x + saba_min_x;
    int y1 = randXor() % saba_range_y + saba_min_y;
    int y2 = randXor() % saba_range_y + saba_min_y;
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    //
    int score = 0;

    auto saba_it = saba_XY_map.lower_bound(x1);
    while (saba_it != saba_XY_map.end()) {
      if (saba_it->first > x2) break;
      for (auto v : saba_it->second) {
        if (y2 < v) break;
        if (y1 <= v) score++;
      }
      saba_it++;
    }
    auto iwashi_it = iwashi_XY_map.lower_bound(x1);
    while (iwashi_it != iwashi_XY_map.end()) {
      if (iwashi_it->first > x2) break;
      for (auto v : iwashi_it->second) {
        if (y2 < v) break;
        if (y1 <= v) score--;
      }
      iwashi_it++;
    }

    if (chmax(max_score, score)) {
      best_x1 = x1, best_x2 = x2, best_y1 = y1, best_y2 = y2;
    }
  }
  debug(loop_count, max_score);

  /* output */
  out(4);
  out(best_x1, best_y1);
  out(best_x2, best_y1);
  out(best_x2, best_y2);
  out(best_x1, best_y2);
}