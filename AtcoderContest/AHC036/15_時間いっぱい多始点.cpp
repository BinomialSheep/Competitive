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

  void insert(int v) {
    if (!head.count(v)) body.insert(v);
  }

  int size() { return (int)head.size() + (int)body.size() + (int)tail.size(); }

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

  static int virtual_disconnect(TraficLights& tl1, TraficLights& /*tl2*/) {
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

  for (auto&& vec : G) sort(all(vec));
}

/**
 * 全点間最短経路をO(NM)で求める
 */
void all_pairs_shortest_path() {
  auto bfs = [&](int start) {
    array<bool, 600> visited = {false};
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
 * traffic_light_set_vecセットした値はlist_A作成の材料になる
 * back_flagをtrueにした場合、ターゲット到達後に青信号を0コストで進んでよりよい最短歩道を作るが、実際はスコアが下がるコトが多い
 * あと100ケースくらい回すとバグがあるらしいので基本false（FIXME！）
 */
vector<int> find_walk() {
  vector<int> walk;

  // 探索中の頂点
  int now = 0;
  rep(di, travel_plan.size()) {
    int destination = travel_plan[di];
    // ターゲットまで進む
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
vector<int> find_walk_2() {
  vector<int> walk;

  // 探索中の頂点
  int now = 0;
  rep(di, travel_plan.size()) {
    int destination = travel_plan[di];
    // ターゲットまで進む
    while (now != destination) {
      for (int i = (int)G[now].size() - 1; i >= 0; i--) {
        int u = G[now][i];
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
 * リストBを高速に操作するためのいろいろなヘルパー関数
 */
class ListBOperator {
 public:
  ListBOperator(vector<int>& list_A, vector<Operation>& list_ans,
                vector<int>& walk)
      : list_A_(list_A), list_ans_(list_ans), walk_(walk) {
    list_B_ = vector<int>(LB, -1);
    initialize_include_A_pair();
    initialize_include_A_first();
  }

  // 長さと位置を全探索し、最も先に進めるように変更する
  void update_list_B(int walk_idx) {
    // 今の信号Bで一歩進めるなら信号を更新しない
    if (exist_B_set_.count(walk_[walk_idx])) return;

    int max_score = 0;
    int max_pos_a, max_pos_b, max_len;
    // list_Bの[pos_b, pos_b + len)を、list_A_の[pos_b, pos_b +
    // len)で置き換える
    for (int len = 2; len <= LB; len++) {
      // TODO：きれいにする
      if (walk_idx == (int)walk_.size() - 1) break;
      // 長さlenの場合のmax_pos_bを先に計算する
      int now_max_pos_b = calc_now_max_pos_b(len, walk_idx);

      // stb := 更新後の信号機Bに含まれる頂点集合
      unordered_set<int> stb;
      rep(i, now_max_pos_b) stb.insert(list_B_[i]);
      for (int i = now_max_pos_b + len; i < LB; i++) stb.insert(list_B_[i]);

      // 高速化のため、青信号にしたい最初の2つを含むような置き換えだけ計算する
      int v = walk_[walk_idx], u = -1;
      for (int i = walk_idx + 1; i < (int)walk_.size(); i++) {
        if (!stb.count(walk_[i]) && walk_[i] != v) {
          u = walk_[i];
          break;
        }
      }
      if (u == -1) {
        // len = 1で処理できる
        break;
      }
      if (v > u) swap(v, u);
      for (int pos_a : include_A_pair_[v][u][len - 1]) {
        // 置き換える
        unordered_set<int> sta;
        rep(i, len) sta.insert(list_A_[pos_a + i]);
        // 評価する. 新しいlist_Bで何頂点進めるかで評価する
        int score = 0;
        for (int i = walk_idx; i < (int)walk_.size(); i++) {
          if (!stb.count(walk_[i]) && !sta.count(walk_[i])) break;
          score++;
        }
        // 最大値なら更新する
        if (chmax(max_score, score)) {
          max_pos_a = pos_a, max_pos_b = now_max_pos_b, max_len = len;
        }
      }
    }
    if (max_score == 0) {
      // len = 1
      max_pos_a = include_A_first_[walk_[walk_idx]];
      max_pos_b = calc_now_max_pos_b(1, walk_idx);
      max_len = 1;
    }
    // 信号機を変更
    list_ans_.emplace_back(max_len, max_pos_a, max_pos_b);
    // list_B, exist_B_setを更新
    rep(i, max_len) list_B_[max_pos_b + i] = list_A_[max_pos_a + i];
    exist_B_set_.clear();
    for (auto& u : list_B_) exist_B_set_.insert(u);
  }

 private:
  vector<int> list_B_;
  unordered_set<int> exist_B_set_;
  //
  vector<int>& list_A_;
  vector<Operation>& list_ans_;
  vector<int>& walk_;

  // include_A[v][len] := 頂点vを含むようにlen個変えられるpaの集合
  vector<int> include_A_first_;
  vector<vector<vector<unordered_set<int>>>> include_A_pair_;

  void initialize_include_A_pair() {
    include_A_pair_.resize(N);
    rep(i, N) include_A_pair_[i].resize(N);
    rep(i, N) rep(j, N) include_A_pair_[i][j].resize(LB + 1);

    rep(start, list_A_.size()) {
      for (int len = 1; len <= LB; len++) {
        if (start + len - 1 == (int)list_A_.size()) break;
        for (int i = start; i < start + len; i++) {
          for (int j = start; j < i; j++) {
            int v = list_A_[i], u = list_A_[j];
            if (v == u) continue;
            if (v > u) swap(v, u);
            include_A_pair_[v][u][len - 1].insert(start);
          }
        }
      }
    }
  }

  void initialize_include_A_first() {
    include_A_first_ = vector<int>(N, -1);
    rep(i, list_A_.size()) {
      if (include_A_first_[list_A_[i]] == -1) include_A_first_[list_A_[i]] = i;
    }
  }

  // 信号機をlen個変更する場合の、最善の開始位置
  int calc_now_max_pos_b(int len, int walk_idx) {
    int now_max_pos_b = 0, ub_score = 0;
    unordered_map<int, int> mpb;
    for (int i = len; i < LB; i++) mpb[list_B_[i]]++;
    for (int pos_b = 0; pos_b + len <= LB; pos_b++) {
      // 置き換えていない信号に含まれる頂点
      unordered_set<int> sta;
      if (pos_b) mpb[list_B_[pos_b - 1]]++, mpb[list_B_[pos_b + len - 1]]--;
      // len個だけ自由に置き換えることができる
      int cnt = len;
      int score = 0;
      for (int i = walk_idx; i < (int)walk_.size(); i++) {
        if (!mpb[walk_[i]] && !sta.count(walk_[i])) {
          if (cnt == 0) break;
          cnt--;
          sta.insert(walk_[i]);
        }
        score++;
      }
      if (chmax(ub_score, score)) now_max_pos_b = pos_b;
    }
    return now_max_pos_b;
  }
};

/**
 * 適当な答えを返す
 */
Answer find_smart_answer(vector<int>& walk, vector<int>& list_A,
                         TimeKeeper& timekeeper) {
  // 戻り値
  vector<Operation> ret;

  ListBOperator list_B_operator(list_A, ret, walk);

  // 頂点
  rep(walk_idx, walk.size()) {
    if (timekeeper.isTimeOver()) return Answer();
    // debug(walk_idx);
    int v = walk[walk_idx];
    // 次の頂点が赤信号の場合のみ、信号の変更を行う
    list_B_operator.update_list_B(walk_idx);
    // 進む
    ret.emplace_back(v);
  }
  return Answer(ret, list_A);
}

class ListAOperator {
 public:
  ListAOperator(vector<int>& walk) : walk_(walk) {}

  vector<int> generate_list_A(TimeKeeper& timekeeper) {
    // 経路に存在し、まだlist_Aに存在しないもの
    unordered_set<int> exist_v_in_walk;
    for (auto& v : walk_) exist_v_in_walk.insert(v);

    // 圧縮できた長さ
    int compress_count = 0;
    // 今list_Aに入れている長さ
    int list_A_len = 0;

    TraficLights trafic_lights;
    for (auto& v : walk_) {
      if (timekeeper.isTimeOver()) {
        vi dummy_ret;
        return dummy_ret;
      }
      trafic_lights.insert(v);
      exist_v_in_walk.erase(v);

      if (trafic_lights.size() == LB) {
        if (trafic_lights_list_.size()) {
          compress_count -= TraficLights::disconnect(trafic_lights_list_.back(),
                                                     trafic_lights);
          compress_count +=
              TraficLights::connect(trafic_lights_list_.back(), trafic_lights);
        }
        trafic_lights_list_.push_back(trafic_lights);

        list_A_len += LB;
        trafic_lights = TraficLights();
      }

      if (list_A_len - compress_count + trafic_lights.size() +
              (int)exist_v_in_walk.size() >=
          LA) {
        int diff_value = 0;
        diff_value -=
            TraficLights::disconnect(trafic_lights_list_.back(), trafic_lights);
        diff_value +=
            TraficLights::connect(trafic_lights_list_.back(), trafic_lights);
        diff_value += annealing(5000, trafic_lights);
        if (diff_value == 0) {
          // 追加で山登りしてみる（意外と効く）
          diff_value = annealing(10000, trafic_lights);
          if (diff_value == 0) {
            trafic_lights_list_.push_back(trafic_lights);
            break;
          }
        }
        compress_count += diff_value;
      }
    }

    // 同じsetの中で順序を改善する
    return cram_list_A_2(exist_v_in_walk);

    // list_Aに入れる
    // return cram_list_A(exist_v_in_walk);
  }

  bool assert_list_A(vector<int>& list_A) {
    if ((int)list_A.size() != LA) {
      debug("長さ不一致", list_A.size(), LA);
      assert(false);
    }
    // walkの集合とlist_Aの集合は一致しているはず
    unordered_set<int> st_w;
    unordered_set<int> st_a;
    for (auto v : walk_) st_w.insert(v);
    for (auto v : list_A) st_a.insert(v);
    for (auto v : st_w) {
      if (!st_a.count(v)) {
        debug("st_Wにあってst_aにない", v);
        return false;
      }
    }
    for (auto v : st_a) {
      if (!st_w.count(v)) {
        debug("st_aにあってst_vにない", v);
        return false;
      }
    }
    return true;
  }

 private:
  vector<int>& walk_;
  vector<TraficLights> trafic_lights_list_;
  TraficLights dummy_tl_;

  int swap_tl(int i, int j, TraficLights& tail_tl) {
    int diff_value = 0;
    int sz = (int)trafic_lights_list_.size();
    if (i != sz - 1) {
      diff_value -= TraficLights::disconnect(trafic_lights_list_[i],
                                             trafic_lights_list_[i + 1]);
    } else {
      diff_value -= TraficLights::disconnect(trafic_lights_list_[i], tail_tl);
    }
    if (i != 0) {
      diff_value -= TraficLights::disconnect(trafic_lights_list_[i - 1],
                                             trafic_lights_list_[i]);
    }
    if (j != sz - 1) {
      diff_value -= TraficLights::disconnect(trafic_lights_list_[j],
                                             trafic_lights_list_[j + 1]);
    } else {
      diff_value -= TraficLights::disconnect(trafic_lights_list_[j], tail_tl);
    }
    if (j != 0) {
      diff_value -= TraficLights::disconnect(trafic_lights_list_[j - 1],
                                             trafic_lights_list_[j]);
    }
    if (i != sz - 1) {
      diff_value += TraficLights::connect(trafic_lights_list_[j],
                                          trafic_lights_list_[i + 1]);
    } else {
      diff_value += TraficLights::connect(trafic_lights_list_[j], tail_tl);
    }
    if (i != 0) {
      diff_value += TraficLights::connect(trafic_lights_list_[i - 1],
                                          trafic_lights_list_[j]);
    }
    if (j != sz - 1) {
      diff_value += TraficLights::connect(trafic_lights_list_[i],
                                          trafic_lights_list_[j + 1]);
    } else {
      diff_value += TraficLights::connect(trafic_lights_list_[i], tail_tl);
    }
    if (j != 0) {
      diff_value += TraficLights::connect(trafic_lights_list_[j - 1],
                                          trafic_lights_list_[i]);
    }
    swap(trafic_lights_list_[i], trafic_lights_list_[j]);
    return diff_value;
  }

  int virtual_swap_tl(int i, int j, TraficLights& tail_tl) {
    int diff_value = 0;
    int sz = (int)trafic_lights_list_.size();
    if (i != sz - 1) {
      diff_value -= TraficLights::virtual_disconnect(
          trafic_lights_list_[i], trafic_lights_list_[i + 1]);
    } else {
      diff_value -=
          TraficLights::virtual_disconnect(trafic_lights_list_[i], tail_tl);
    }
    if (i != 0) {
      diff_value -= TraficLights::virtual_disconnect(trafic_lights_list_[i - 1],
                                                     trafic_lights_list_[i]);
    }
    if (j != sz - 1) {
      diff_value -= TraficLights::virtual_disconnect(
          trafic_lights_list_[j], trafic_lights_list_[j + 1]);
    } else {
      diff_value -=
          TraficLights::virtual_disconnect(trafic_lights_list_[j], tail_tl);
    }
    if (j != 0) {
      diff_value -= TraficLights::virtual_disconnect(trafic_lights_list_[j - 1],
                                                     trafic_lights_list_[j]);
    }
    if (i == 0) {
      diff_value += TraficLights::virtual_connect(
          dummy_tl_, trafic_lights_list_[j], trafic_lights_list_[i + 1]);
    } else if (i == sz - 1) {
      diff_value += TraficLights::virtual_connect(
          trafic_lights_list_[i - 1], trafic_lights_list_[j], tail_tl);
    } else {
      diff_value += TraficLights::virtual_connect(trafic_lights_list_[i - 1],
                                                  trafic_lights_list_[j],
                                                  trafic_lights_list_[i + 1]);
    }
    if (j == 0) {
      diff_value += TraficLights::virtual_connect(
          dummy_tl_, trafic_lights_list_[i], trafic_lights_list_[j + 1]);
    } else if (j == sz - 1) {
      diff_value += TraficLights::virtual_connect(
          trafic_lights_list_[j - 1], trafic_lights_list_[i], tail_tl);
    } else {
      diff_value += TraficLights::virtual_connect(trafic_lights_list_[j - 1],
                                                  trafic_lights_list_[i],
                                                  trafic_lights_list_[j + 1]);
    }
    return diff_value;
  };

  // 指定回数でアニーリングし、縮めた個数を返す
  // （現在はただの山登り）
  int annealing(int cnt, TraficLights& tai_tl) {
    int value = 0;
    int sz = (int)trafic_lights_list_.size();
    rep(_, cnt) {
      int i = 0, j = 0;
      while (abs(i - j) <= 2) {
        i = randXor() % sz;
        j = randXor() % sz;
      }

      int delta_score = virtual_swap_tl(i, j, tai_tl);
      if (delta_score >= 0) {
        int res = swap_tl(i, j, tai_tl);
        assert(res == delta_score);
        value += delta_score;
      } else {
        // 未受理
      }
    }
    return value;
  }

  vector<int> cram_list_A(unordered_set<int>& exist_v_in_walk) {
    vector<int> list_A;
    // int cnt1 = 0, cnt2 = 0;
    rep(i, trafic_lights_list_.size()) {
      // cnt1 += trafic_lights_list_[i].size();
      // cnt2 += (int)trafic_lights_list_[i].head.size();
      if (i == 0) {
        for (auto v : trafic_lights_list_[i].head) {
          list_A.emplace_back(v);
        }
      }
      for (auto v : trafic_lights_list_[i].body) {
        list_A.emplace_back(v);
      }
      for (auto v : trafic_lights_list_[i].tail) {
        list_A.emplace_back(v);
      }
    }
    // cnt2 -= (int)trafic_lights_list_[0].head.size();
    // debug(cnt1, cnt2);
    for (auto& v : exist_v_in_walk) list_A.push_back(v);
    return list_A;
  }

  vector<int> cram_list_A_2(unordered_set<int>& exist_v_in_walk) {
    // 歩道の中に表れる長さiの部分集合
    vector<set<set<int>>> walk_set(LB);
    rep(start, walk_.size()) {
      set<int> st;
      int idx = start;
      while ((int)st.size() <= LB - 2 && idx < (int)walk_.size()) {
        if (st.count(walk_[idx])) {
          idx++;
          continue;
        }
        st.insert(walk_[idx]);
        walk_set[st.size()].insert(st);
        idx++;
      }
    }
    vector<int> list_A;

    // walk_setに表れる集合を先に置く
    auto f = [&](unordered_set<int>& ust) {
      set<int> st;
      for (auto v : ust) st.insert(v);
      for (int len = min(LB - 1, (int)st.size()); len >= 2; len--) {
        if (len > (int)st.size()) continue;
        for (auto& st2 : walk_set[len]) {
          if (st2.size() > st.size()) break;
          bool ok = 1;
          for (auto v : st2) {
            if (st.count(v)) continue;
            ok = 0;
            break;
          }
          if (ok) {
            for (auto v : st2) {
              st.erase(v);
              list_A.emplace_back(v);
            }
          }
        }
      }
      for (auto v : st) list_A.emplace_back(v);
    };

    rep(i, trafic_lights_list_.size()) {
      if (i == 0) f(trafic_lights_list_[i].head);
      f(trafic_lights_list_[i].body);
      f(trafic_lights_list_[i].tail);
    }
    f(exist_v_in_walk);
    return list_A;
  }
};

int main() {
  TimeKeeper timekeeper(2500);

  // 前処理
  process_input();
  all_pairs_shortest_path();

  // 経路を求めておく
  vector<int> walk_1 = find_walk();
  vector<int> walk_2 = find_walk_2();

  int best_score = INF;
  unique_ptr<Answer> best_answer;

  for (int ti = 1;; ti++) {
    vector<int> walk;
    if (ti % 2) {
      walk = walk_1;
    } else {
      walk = walk_2;
    }

    // list_Aを作る
    ListAOperator list_A_operator(walk);
    vector<int> list_A = list_A_operator.generate_list_A(timekeeper);
    // assert(list_A_operator.assert_list_A(list_A));
    if (timekeeper.isTimeOver()) break;

    Answer ans = find_smart_answer(walk, list_A, timekeeper);
    if (timekeeper.isTimeOver()) break;

    if (chmin(best_score, ans.calc_score()))
      best_answer = make_unique<Answer>(ans);
  }

  // 出力
  best_answer->print_list_A();
  best_answer->print_operation_list();

  // デバッグ用スコア計算
  cerr << best_answer->calc_score() << endl;
}