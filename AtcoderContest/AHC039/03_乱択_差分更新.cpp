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

class Square {
 public:
  int _x1, _x2, _y1, _y2;
  int _cnt_saba, _cnt_iwashi;

  Square(int x1, int y1, int x2, int y2, int saba, int iwashi) {
    _x1 = min(x1, x2);
    _x2 = max(x1, x2);
    _y1 = min(y1, y2);
    _y2 = max(y1, y2);
    _cnt_saba = saba;
    _cnt_iwashi = iwashi;
  }

  void print() const {
    // デバッグ用出力
    debug(_x1, _x2, _y1, _y2, _cnt_saba, _cnt_iwashi);
  }

  // スコア昇順ソート
  bool operator<(const Square& another) const {
    return _cnt_saba - _cnt_iwashi < another._cnt_saba - another._cnt_iwashi;
  }
  bool operator>(const Square& another) const {
    return _cnt_saba - _cnt_iwashi > another._cnt_saba - another._cnt_iwashi;
  }
};

int count_saba(int x1, int x2, int y1, int y2) {
  int saba = 0;
  auto saba_it = saba_XY_map.lower_bound(x1);
  while (saba_it != saba_XY_map.end()) {
    if (saba_it->first > x2) break;
    for (auto v : saba_it->second) {
      if (y2 < v) break;
      if (y1 <= v) saba++;
    }
    saba_it++;
  }
  return saba;
}
int count_iwashi(int x1, int x2, int y1, int y2) {
  int iwashi = 0;
  auto iwashi_it = iwashi_XY_map.lower_bound(x1);
  while (iwashi_it != iwashi_XY_map.end()) {
    if (iwashi_it->first > x2) break;
    for (auto v : iwashi_it->second) {
      if (y2 < v) break;
      if (y1 <= v) iwashi++;
    }
    iwashi_it++;
  }
  return iwashi;
}

int main() {
  const int64_t time_threshold = 500;
  const int64_t time_threshold_2 = 1490;
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
  const int pq_size = 5;
  using P = Square;
  priority_queue<P, vector<P>, greater<P>> pq;

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

    int saba = count_saba(x1, x2, y1, y2);
    int iwashi = count_iwashi(x1, x2, y1, y2);

    // 更新
    if (pq.size() < pq_size) {
      pq.emplace(Square(x1, y1, x2, y2, saba, iwashi));
    } else {
      int score = saba - iwashi;
      int score2 = pq.top()._cnt_saba - pq.top()._cnt_iwashi;
      if (score > score2) {
        pq.pop();
        pq.emplace(Square(x1, y1, x2, y2, saba, iwashi));
      }
    }
  }

  vector<Square> square_vec;

  while (pq.size()) {
    square_vec.emplace_back(pq.top());
    pq.pop();
  }
  reverse(all(square_vec));

  auto g = [&](int idx) {
    int max_score = square_vec[idx]._cnt_saba - square_vec[idx]._cnt_iwashi;
    int best_x1 = square_vec[idx]._x1;
    int best_x2 = square_vec[idx]._x2;
    int best_y1 = square_vec[idx]._y1;
    int best_y2 = square_vec[idx]._y2;

    auto time_keeper_2 = TimeKeeper(time_threshold_2 / 5);
    int loop_count_2 = 0;
    while (!time_keeper_2.isTimeOver()) {
      loop_count_2++;
      //
      int x1 = best_x1;
      int x2 = best_x2;
      int y1 = best_y1;
      int y2 = best_y2;
      //
      int ty = randXor() % 4;
      int len = randXor() % 2000 - 1000;
      if (ty == 0) {
        x1 += len;
        chmax(x1, saba_min_x);
        chmin(x1, x2);
      } else if (ty == 1) {
        x2 += len;
        chmax(x2, x1);
        chmin(x2, saba_max_x);
      } else if (ty == 2) {
        y1 += len;
        chmax(y1, saba_min_y);
        chmin(y1, y2);
      } else if (ty == 3) {
        y2 += len;
        chmax(y2, y1);
        chmin(y2, saba_max_y);
      }

      if (chmax(max_score,
                count_saba(x1, x2, y1, y2) - count_iwashi(x1, x2, y1, y2))) {
        best_x1 = x1;
        best_x2 = x2;
        best_y1 = y1;
        best_y2 = y2;
      }
    }
    square_vec[idx]._x1 = best_x1;
    square_vec[idx]._x2 = best_x2;
    square_vec[idx]._y1 = best_y1;
    square_vec[idx]._y2 = best_y2;
    square_vec[idx]._cnt_saba = max_score;
  };

  rep(i, 5) g(i);

  int max_score = 0;
  int best_x1 = 0;
  int best_x2 = 0;
  int best_y1 = 0;
  int best_y2 = 0;

  rep(i, 5) {
    if (chmax(max_score, square_vec[i]._cnt_saba)) {
      best_x1 = square_vec[i]._x1;
      best_x2 = square_vec[i]._x2;
      best_y1 = square_vec[i]._y1;
      best_y2 = square_vec[i]._y2;
    }
  }

  /* output */
  out(4);
  out(best_x1, best_y1);
  out(best_x2, best_y1);
  out(best_x2, best_y2);
  out(best_x1, best_y2);
}