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

// 隣接辺を見栄えの悪い順に持つ
void sort_graph() {
  for (auto&& vec : input_G) {
    sort(all(vec), [&](int const left, int const right) {
      return input_A[left] < input_A[right];
    });
  }
}

struct IndexSet {
  vector<int> que;
  vector<int> pos;

  IndexSet(int n) {
    pos = vector<int>(n, -1);
    que.reserve(n);
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
};

int main() {
  const int time_threshold = 1980;
  auto time_keeper = TimeKeeper(time_threshold);

  exec_input();
  sort_nice_look();
  sort_graph();
  //

  vector<int> ans_p(1000, -2);
  vector<int> v_height(1000);
  auto dfs = [&](auto rec, int v = 0, int parent = -1, int height = 0) -> void {
    ans_p[v] = parent;
    v_height[v] = height;
    if (height == 10) return;
    for (auto u : input_G[v]) {
      if (ans_p[u] == -2) rec(rec, u, v, height + 1);
    }
  };

  rep(i, 1000) {
    if (ans_p[nice_look[999 - i]] == -2) dfs(dfs, nice_look[999 - i]);
  }
  out(ans_p);

  // 時間目一杯山登り？

  // 子どもを持つグラフ
  vector<unordered_set<int>> child_g(1000);
  rep(i, 1000) {
    assert(ans_p[i] != -2);
    if (ans_p[i] != -1) child_g[ans_p[i]].insert(i);
  }
  // 子どもが0かつ深さ10でない頂点集合
  IndexSet no_childs(1000);
  // rep(i, 1000) if (child_g[i].empty() && v_height[i] != 10) no_childs.add(i);
  rep(i, 1000) if (child_g[i].empty()) no_childs.add(i);
  // debug(no_childs.que);

  double start_temp = 350;  // 開始時の温度
  double end_temp = 0.4;    // 終了時の温度
  double progress_ratio =
      (double)time_keeper.getTime() / (double)time_threshold;
  double temp = start_temp + (end_temp - start_temp) * progress_ratio;
  double probability = 0;
  double time_threshold_inv = 1 / (double)time_threshold;

  int loop_count = 0;
  while (true) {
    loop_count++;
    if (loop_count % 2048 == 0) {
      if (time_keeper.isTimeOver()) break;
      progress_ratio = (double)time_keeper.getTime() * time_threshold_inv;
      temp = start_temp + (end_temp - start_temp) * progress_ratio;
    }
    int idx = randXor() % no_childs.size();
    int v = no_childs.que[idx];

    // 周囲の頂点の周囲の頂点を探して、繋ぎ変えを検討する
    int best_u = -1, best_k = -1, best_diff_score = -1e9;
    for (auto u : input_G[v]) {
      if (ans_p[v] == u) continue;
      if (v_height[u] < 10) {
        int diff_score = (v_height[u] + 1 - v_height[v]) * input_A[v];
        if (chmax(best_diff_score, diff_score)) {
          best_u = u;
          best_k = -1;
        }
        continue;
      }
      // 繋ぎ変える前のスコア
      int prev_score = (v_height[v] + 1) * input_A[v] + 11 * input_A[u];
      for (auto k : input_G[u]) {
        if (k == v || v_height[k] >= 9) continue;
        // debug(v, u, k, v_height[k]);
        // 繋ぎ変えた後のスコア
        int next_score =
            (v_height[k] + 3) * input_A[v] + (v_height[k] + 2) * input_A[u];
        // debug(prev_score, next_score);
        if (chmax(best_diff_score, next_score - prev_score)) {
          best_u = u;
          best_k = k;
        }
      }
    }

    // ans_p[v] = new_pとする
    auto update = [&](int child, int new_p) {
      if (ans_p[child] != -1) {
        child_g[ans_p[child]].erase(child);
        if (child_g[ans_p[child]].empty()) no_childs.add(ans_p[child]);
      }
      child_g[new_p].insert(child);
      if (no_childs.contains(new_p)) no_childs.remove(new_p);

      ans_p[child] = new_p;
    };

    probability = exp((double)best_diff_score / temp);

    if (probability >= rand01()) {
      // debug(best_u, best_k, best_diff_score);

      if (best_k == -1) {
        v_height[v] = v_height[best_u] + 1;
        update(v, best_u);
      } else {
        v_height[v] = v_height[best_k] + 2;
        v_height[best_u] = v_height[best_k] + 1;
        update(v, best_u);
        update(best_u, best_k);
      }
      // out(ans_p);
      // break;
    }
    if (loop_count % 100000 == 1) out(ans_p);
  }
  // debug(loop_count);

  // debug(ans_p, v_height);
  // debug(calc_score(v_height));
  cerr << calc_score(v_height) << endl;
  out(ans_p);
}