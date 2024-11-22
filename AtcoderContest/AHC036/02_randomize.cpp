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
};

// グローバルな入力値（と前処理した値）
int N, M, T, LA, LB;
array<vector<int>, 600> G;
vector<int> travel_plan;
array<array<int, 600>, 600> dists;
const int INF = 1e9;

/**
 * 出力形式用の構造体
 */
class Operation {
 public:
  char type;
  int l, pa, pb;
  int v;

  Operation(int _l, int _pa, int _pb) : type('s'), l(_l), pa(_pa), pb(_pb) {}
  Operation(int _v) : type('m'), v(_v) {}
};

class Answer {
 public:
  vector<Operation> list_operation;
  vector<int> list_A;
  Answer(vector<Operation>& os, vector<int>& as)
      : list_operation(os), list_A(as) {}
  Answer() {}

  void print_list_A() {
    rep(i, (int)list_A.size() - 1) printf("%d ", list_A[i]);
    printf("%d\n", list_A.back());
  }

  void print_operation_list() {
    rep(i, list_operation.size()) {
      if (list_operation[i].type == 's') {
        printf("s %d %d %d\n", list_operation[i].l, list_operation[i].pa,
               list_operation[i].pb);
      } else {
        printf("m %d\n", list_operation[i].v);
      }
    }
  }

  void debug_print_operation_list() {
    rep(i, list_operation.size()) {
      if (list_operation[i].type == 's') {
        debug(i, 's', list_operation[i].l, list_operation[i].pa,
              list_operation[i].pb);
      } else {
        debug(i, 'm', list_operation[i].v);
      }
    }
  }

  // 答えが正常な列か確認する
  void assert_answer() {}

  int calc_score() {
    int score = 0;
    for (auto ope : list_operation)
      if (ope.type == 's') score++;
    return score;
  }
};

/**
 * 入力処理
 */
void process_input() {
  cin >> N >> M >> T >> LA >> LB;
  rep(i, M) {
    INT(A, B);
    G[A].push_back(B);
    G[B].push_back(A);
  }
  travel_plan.resize(T);
  rep(i, T) cin >> travel_plan[i];
}

/**
 * 全点間最短経路をO(NM)で求める
 */
void all_pairs_shortest_path() {
  auto bfs = [&](int start) {
    vector visited(N, false);
    queue<int> q;
    visited[start] = 1;
    q.emplace(start);
    while (q.size()) {
      auto v = q.front();
      q.pop();
      for (auto u : G[v]) {
        if (!visited[u]) {
          visited[u] = 1;
          q.push(u);
          dists[start][u] = dists[start][v] + 1;
        }
      }
    }
  };
  rep(i, N) bfs(i);
}

/**
 * 旅行計画を満たす最短の歩道の1つを返す
 * 計算量：O(NM)
 * 詳細：最短路が複数ある場合、最も小さい頂点へ向かう
 * TODO：ランダマイズする？
 */
vector<int> find_naive_walk() {
  vector<int> walk;

  int now = 0;
  for (int destination : travel_plan) {
    while (now != destination) {
      for (auto u : G[now]) {
        if (dists[now][destination] - 1 == dists[u][destination]) {
          walk.push_back(u);
          now = u;
          break;
        }
      }
    }
  }
  return walk;
}

/**
 * 複数の最短経路がある場合、ランダムに返す
 * ただしある頂点からある目的値に向かう経路は固定する（信号機配置の有効活用のため）
 */
vector<int> find_randomized_walk() {
  vector<int> walk;

  // (now, destination)の時の次の頂点
  vector<vector<int>> memo(N, vector<int>(N, -1));

  int now = 0;
  for (int destination : travel_plan) {
    while (now != destination) {
      if (memo[now][destination] != -1) {
        now = memo[now][destination];
        walk.push_back(now);
        continue;
      }
      vector<int> us;
      for (auto u : G[now]) {
        if (dists[now][destination] - 1 == dists[u][destination]) {
          us.push_back(u);
        }
      }
      memo[now][destination] = us[randXor() % (int)us.size()];
      now = us[randXor() % (int)us.size()];
      walk.push_back(now);
    }
  }
  return walk;
}

/**
 * 適当な答えを返す
 */
Answer find_naive_answer(vector<int>& walk) {
  vector<Operation> ret;
  vector<int> now_A(LA, -1);
  // 今のBに出現する頂点集合
  unordered_set<int> exist_B_set;
  // 頂点vが歩道で最初に出現する位置
  vector<int> first_appearance(N, INF);
  // 歩道上のindexが与えられた時に変えるべき信号の開始地点
  vector<int> walk_idx_to_pa(walk.size(), -1);
  {
    // 歩道に表れる頂点が1つはAに入るように後ろから詰める
    vector<pair<int, int>> pairs;
    rep(i, walk.size()) {
      if (chmin(first_appearance[walk[i]], i)) {
        pairs.emplace_back(walk[i], i);
      }
    }
    rep(i, (int)pairs.size()) now_A[LA - 1 - i] =
        pairs[(int)pairs.size() - 1 - i].first;
  }
  // 歩道通りに前から詰めていく（後ろを壊しすぎないように）
  int ai = 0;
  rep(i, walk.size()) {
    int v = walk[i];
    if (exist_B_set.count(v)) {
      walk_idx_to_pa[i] = -2;
      continue;
    }
    if ((int)exist_B_set.size() == LB) exist_B_set.clear();
    exist_B_set.insert(v);
    now_A[ai] = v;
    walk_idx_to_pa[i] = ai;
    ai++;
    if (now_A[ai] != -1 && first_appearance[now_A[ai]] >= i) {
      break;
    }
  }
  rep(i, walk.size()) {
    if (walk_idx_to_pa[i] == -1) {
      for (int k = LA - 1; k >= 0; k--) {
        if (now_A[k] == walk[i]) {
          walk_idx_to_pa[i] = k;
          break;
        }
      }
    }
  }
  exist_B_set.clear();

  // 頂点
  rep(i, walk.size()) {
    int v = walk[i];
    // 信号機をまとめて青にする
    if (!exist_B_set.count(v)) {
      exist_B_set.clear();
      int pa = walk_idx_to_pa[i];
      int l = min(LB, LA - pa);
      ret.emplace_back(l, pa, 0);
      // debug(i, pa, l);
      rep(j, l) {
        if (pa + j >= now_A.size() || pa + j < 0) {
          debug(walk_idx_to_pa);
          debug(i);
          debug(pa, l);
        }
        exist_B_set.insert(now_A[pa + j]);
      }
    }
    // 進む
    ret.emplace_back(v);
  }

  return Answer(ret, now_A);
}

int main() {
  const int64_t time_threshold = 2900;
  auto time_keeper = TimeKeeper(time_threshold);

  process_input();
  all_pairs_shortest_path();

  vector<int> init_walk = find_naive_walk();
  Answer best_ans = find_naive_answer(init_walk);
  int best_score = best_ans.calc_score();
  debug(best_score);
  int cnt = 0;

  while (!time_keeper.isTimeOver()) {
    cnt++;
    // vector<int> walk = find_naive_walk();
    vector<int> walk = find_randomized_walk();
    Answer ans = find_naive_answer(walk);
    int score = ans.calc_score();
    // debug(score);
    if (chmin(best_score, score)) best_ans = ans;
  }
  debug(cnt);
  debug(best_score);
  best_ans.print_list_A();
  best_ans.print_operation_list();
}