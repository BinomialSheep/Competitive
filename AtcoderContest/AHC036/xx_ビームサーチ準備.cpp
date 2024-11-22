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

// グローバルな入力値（と前処理した値）
int N, M, T, LA, LB;
array<vector<int>, 600> G;
vector<int> travel_plan;
array<array<int, 600>, 600> dists;
const int INF = 1e9;

/**
 * 長さBの信号機集合
 */
class TraficLights {
 public:
  unordered_set<int> head;
  unordered_set<int> body;
  unordered_set<int> tail;
  int num;

  TraficLights() : num(1) {}

  void insert(int v) { body.insert(v); }

  // 2つのTraficLightsを引数順に繋ぐ
  static int connect(TraficLights& tl1, TraficLights& tl2) {
    assert(tl1.tail.empty());
    assert(tl2.head.empty());

    for (auto v : tl1.body) {
      if (tl2.body.count(v)) {
        tl1.tail.insert(v);
        tl2.head.insert(v);
      }
    }
    for (auto v : tl1.tail) {
      tl1.body.erase(v);
      tl2.body.erase(v);
    }
    return (int)tl1.tail.size();
  }
  // 2つのTraficLightsの引数順の接続を解除する
  static int disconnect(TraficLights& tl1, TraficLights& tl2) {
    int ret = (int)tl1.tail.size();

    for (auto v : tl1.tail) {
      tl1.body.insert(v);
      tl2.body.insert(v);
    }
    tl1.tail.clear();
    tl2.head.clear();

    return ret;
  }

  /**
   * 実際には繋がず、繋いだ際に得られるスコアだけを返す
   * 先頭か末尾の場合は呼び出し側で番兵が入っているのでこれで上手くいく
   */
  static int virtual_connect(TraficLights& tl1, TraficLights& tl2,
                             TraficLights& tl3) {
    int score = 0;
    for (auto v : tl1.body)
      if (tl2.body.count(v) || tl2.head.count(v) || tl2.tail.count(v)) score++;
    for (auto v : tl1.tail)
      if (tl2.body.count(v) || tl2.head.count(v) || tl2.tail.count(v)) score++;
    for (auto v : tl2.head)
      if (!tl1.body.count(v) && !tl1.tail.count(v) &&
          (tl3.body.count(v) || tl3.head.count(v)))
        score++;
    for (auto v : tl2.body)
      if (!tl1.body.count(v) && !tl1.tail.count(v) &&
          (tl3.body.count(v) || tl3.head.count(v)))
        score++;
    for (auto v : tl2.tail)
      if (!tl1.body.count(v) && !tl1.tail.count(v) &&
          (tl3.body.count(v) || tl3.head.count(v)))
        score++;

    return score;
  }

  static int virtual_disconnect(TraficLights& tl1, TraficLights& tl2) {
    return (int)tl1.tail.size();
  }

  void print() {
    debug(head);
    debug(body);
    debug(tail);
  }
};

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
 * ビームサーチの進捗用
 */
class State {
 public:
  int count_operation_B;
  int progress_travel;
  vector<int> list_A;
  vector<int> list_B;

  State() : count_operation_B(100), progress_travel(0) {}
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
  debug(walk.size());
  return walk;
}

/**
 * 適当な答えを返す
 */
Answer find_smart_answer(vector<int>& walk, vector<int>& list_A) {
  unordered_set<int> exist_B_set;
  vector<Operation> ret;

  vector<vector<pair<int, unordered_set<int>>>> vec(N);
  rep(i, list_A.size()) {
    for (int start = max(0, i - LB + 1);
         start <= i && start + LB <= (int)list_A.size(); start++) {
      unordered_set<int> st;
      rep(j, LB) st.insert(list_A[start + j]);
      vec[list_A[i]].emplace_back(start, st);
    }
  }
  // debug(vec);

  auto f = [&](int walk_idx) -> int {
    int num = 0;
    int ret_idx = 0;
    for (auto& st : vec[walk[walk_idx]]) {
      for (int i = walk_idx; i < walk_idx + LB; i++) {
        if (st.second.count(walk[i])) {
          if (chmax(num, i - walk_idx + 1)) ret_idx = st.first;
        } else {
          break;
        }
      }
    }
    // debug(walk_idx, ret_idx, num);
    assert(num);
    return ret_idx;
  };

  // 頂点
  rep(i, walk.size()) {
    int v = walk[i];
    // 信号機をまとめて青にする
    if (!exist_B_set.count(v)) {
      exist_B_set.clear();

      int pa = f(i);
      int l = min(LB, LA - pa);
      ret.emplace_back(l, pa, 0);
      // debug(i, pa, l);
      rep(j, l) exist_B_set.insert(list_A[pa + j]);
    }
    // 進む
    ret.emplace_back(v);
  }

  return Answer(ret, list_A);
}

/**
 * 配列Aを構築しながらやる
 */
vector<int> find_list_A_beam(const vector<int>& walk) {
  vector<vector<State>> dp(LA + 1);
  dp[0].push_back(State());
  dp[0][0].count_operation_B = 0;
  rep(i, LB) dp[0][0].list_B.push_back(-1);
  vector<double> threshold_list(LA + 1);
  rep(dpi, LA) {
    queue<State> state_queue;
    for (auto& state : dp[dpi]) state_queue.push(state);
    while (state_queue.size()) {
      State state = state_queue.front();
      state_queue.pop();
      // 今のリストAからLA個選んで点灯させる場合
      // TODO：「今のリストAから1<=i<=LA個選んで点灯させる」に拡張
      for (int i = 0; i + LB < (int)state.list_A.size(); i++) {
        // 信号機の更新
        vi nlb = state.list_B;
        rep(j, LB) nlb[j] = state.list_A[i + j];
        // 信号機に含まれる頂点
        unordered_set<int> st;
        for (auto v : nlb) st.insert(v);

        // 新しい信号機で何個進めるか
        int progress = 0;
        while (true) {
          if (st.count(walk[state.progress_travel + progress + 1])) {
            progress++;
            if (state.progress_travel + progress + 1 == (int)walk.size()) break;
            continue;
          }
          break;
        }
        if (progress == 0) continue;

        // 配列の長さ：±0、操作回数：+1、進捗+progress
        double evaluation = (double)(state.progress_travel + progress) /
                            (state.count_operation_B + 1);
        // if (chmax(threshold_list[state.list_A.size()], evaluation)) {
        if (evaluation >= 1) {
          State next_state = state;
          next_state.list_B = nlb;
          next_state.count_operation_B++;
          next_state.progress_travel += progress;
          state_queue.push(next_state);
        }
      }

      // 配列に新しく加えたものだけで点灯させる
      // TODO：配列に新しく加えたものとリストAの末尾を組み合わせて点灯させる
      // 新しく作る個数の全探索
      for (int i = 1; i <= LB && (int)state.list_A.size() + LB <= LA; i++) {
        // nlbの更新位置の全探索
        for (int j = 0; j + i < LB; j++) {
          debug(dpi, i, j);
          vi nlb = state.list_B;
          rep(k, i) nlb[j + k] = -2;
          // 信号機に含まれる頂点
          unordered_set<int> st;
          for (auto v : nlb) st.insert(v);
          // i個まで好きな数値にしていい
          vector<int> add_list;
          int progress = 0;
          while (true) {
            if (st.count(walk[state.progress_travel + progress + 1])) {
              progress++;
              if (state.progress_travel + progress + 1 == (int)walk.size())
                break;
              continue;
            } else if ((int)add_list.size() < i) {
              nlb[j + (int)add_list.size()] =
                  walk[state.progress_travel + progress + 1];
              add_list.push_back(walk[state.progress_travel + progress + 1]);
              st.insert(add_list.back());
              continue;
            }
            break;
          }
          if (progress == 0) continue;
          // 配列の長さ：+i、操作回数：+1、進捗+progress
          int len = (int)state.list_A.size() + (int)add_list.size();
          double evaluation = (double)(state.progress_travel + progress) /
                              (state.count_operation_B + 1);
          if (chmax(threshold_list[len], evaluation)) {
            State next_state = state;
            next_state.list_B = nlb;
            next_state.count_operation_B++;
            next_state.progress_travel += progress;
            for (auto v : add_list) state.list_A.push_back(v);
            state_queue.push(next_state);
            dp[len].push_back(next_state);
          }
        }
      }
    }
  }
  // rep(i, LA + 1) debug(dp[i].size());

  int idx = 0;
  int best_score = 1e9;
  rep(i, dp[LA].size()) if (chmin(best_score, dp[LA][i].count_operation_B))
      idx = i;
  return dp[LA][idx].list_A;
}

int main() {
  process_input();
  all_pairs_shortest_path();

  vector<int> walk = find_naive_walk();

  vector<int> list_A = find_list_A_beam(walk);
  debug(list_A);

  Answer ans = find_smart_answer(walk, list_A);

  ans.print_list_A();
  ans.print_operation_list();

  debug(ans.calc_score());
}