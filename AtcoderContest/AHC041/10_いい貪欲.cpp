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

int input_N, input_M, input_H;
vector<int> input_A(1000), input_x(1000), input_y(1000);
vector<vector<int>> input_G(1000);

void exec_input() {
  cin >> input_N >> input_M >> input_H;
  rep(i, 1000) cin >> input_A[i];
  rep(i, input_M) {
    INT(v, u);
    input_G[v].push_back(u);
    input_G[u].push_back(v);
  }
  rep(i, input_N) { cin >> input_x[i] >> input_y[i]; }
}

int calc_score(vector<int>& v_height) {
  int ret = 1;
  rep(i, 1000) { ret += input_A[i] * (v_height[i] + 1); }
  return ret;
}

// 見栄えのいい頂点順
vector<int> nice_look(1000);
void sort_nice_look() {
  vector<pair<int, int>> ps;
  rep(i, 1000) ps.emplace_back(input_A[i], i);
  sort(ps.rbegin(), ps.rend());
  rep(i, 1000) nice_look[i] = ps[i].second;
  // debug(ps, nice_look);
}

int main() {
  exec_input();
  sort_nice_look();

  // 今のv_heightからBFSして全体をvalidな高さにできるか判定する
  auto is_valid = [&](int h, vector<int> v_height_copy) -> bool {
    vector<int> used(input_N);

    // BFSする

    queue<int> q;
    rep(i, input_N) if (v_height_copy[i] == h) q.push(i);
    while (q.size()) {
      auto v = q.front();
      q.pop();

      for (auto u : input_G[v]) {
        if (v_height_copy[u] != -1) continue;
        v_height_copy[u] = v_height_copy[v] + 1;
        if (v_height_copy[u] < input_H) q.push(u);
      }
    }

    rep(i, input_N) {
      if (v_height_copy[i] == -1) return false;
    }
    return true;
  };

  // 高さhで確定する頂点を決める
  // 見栄えのいい頂点から順に、確定しなくて済むなら確定しないようにする
  auto f = [&](int h, vector<int>& v_height) {
    rep(i, input_N) {
      if (v_height[i] == -1) {
        for (auto u : input_G[i]) {
          if (v_height[u] == h - 1) {
            v_height[i] = h;
          }
        }
      }
    }
    if (h == input_H) return;

    rep(i, input_N) {
      // 見栄えのいい頂点順に処理する
      int v = nice_look[i];
      if (v_height[v] != h) continue;
      // 取り除いてみる
      v_height[v] = -1;
      // 取り除いたらvalidな解にならないなら戻す
      if (!is_valid(h, v_height)) {
        v_height[v] = h;
      }
    }
  };

  vector<int> v_height(input_N, -1);
  for (int i = 0; i <= input_H; i++) {
    f(i, v_height);
  }

  debug(v_height);

  // 復元
  vector<int> ans_p(input_N);

  rep(i, input_N) {
    if (v_height[i] == 0) {
      ans_p[i] = -1;
    } else {
      int ok = 0;
      for (auto u : input_G[i]) {
        if (v_height[u] == v_height[i] - 1) {
          ans_p[i] = u;
          ok = 1;
          break;
        }
      }
      assert(ok);
    }
  }

  cerr << calc_score(v_height) << endl;
  out(ans_p);
}