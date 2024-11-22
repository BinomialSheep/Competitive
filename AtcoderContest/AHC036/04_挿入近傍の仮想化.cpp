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
  debug(walk.size());
  return walk;
}

vector<int> find_smart_walk(vector<set<int>>& traffic_light_set_vec) {
  vector<int> walk;

  // 探索中の頂点
  int now = 0;
  rep(di, travel_plan.size()) {
    int destination = travel_plan[di];
    // 今青信号になっている最善のところまで戻る
    // if (di) {
    //   int v = now;
    //   for (int u : traffic_light_set_vec.back()) {
    //     // TODO：イコールでも最小の頂点移動の調整した方がいいか？
    //     if (dists[v][destination] > dists[u][destination]) {
    //       v = u;
    //     }
    //   }
    //   for (int i = (int)walk.size() - 1;; i--) {
    //     if (walk[i] != now) walk.push_back(walk[i]);
    //     if (walk[i] == v) break;
    //   }
    //   now = v;
    // }
    // ターゲットまで進む
    while (now != destination) {
      for (auto u : G[now]) {
        if (dists[now][destination] - 1 == dists[u][destination]) {
          walk.push_back(u);
          now = u;
          if (traffic_light_set_vec.empty() ||
              (int)traffic_light_set_vec.back().size() == LB) {
            set<int> st;
            traffic_light_set_vec.emplace_back(st);
          }
          traffic_light_set_vec.back().insert(u);
          break;
        }
      }
    }
  }

  // debug(trafic_lights_list);
  // debug(walk.size());
  return walk;
}

// そこそこ性能のいい配列Aを作る（1秒間）
vector<int> compress_trafic_lights_list(
    vector<set<int>>& traffic_light_set_vec) {
  // rep(i, trafic_lights_list.size()) {
  //   debug(i);
  //   trafic_lights_list[i].print();
  // }

  // debug(traffic_light_set_vec.size());

  vector<TraficLights> trafic_lights_list;
  {
    set<set<int>> st2;
    rep(i, traffic_light_set_vec.size()) {
      if (!st2.count(traffic_light_set_vec[i])) {
        st2.insert(traffic_light_set_vec[i]);
        trafic_lights_list.push_back(TraficLights());
        for (auto v : traffic_light_set_vec[i]) {
          trafic_lights_list.back().insert(v);
        }
      }
    }
    // debug(st2.size());
  }
  int value = 0;
  int sz = (int)trafic_lights_list.size();
  rep(i, sz - 1) {
    value +=
        TraficLights::connect(trafic_lights_list[i], trafic_lights_list[i + 1]);
  }
  debug("焼きなまし前：", value);

  // 端に挿入する時の番兵
  TraficLights dummy_tl;

  auto swap_tl = [&](int i, int j) -> int {
    int diff_value = 0;
    if (i != sz - 1) {
      diff_value -= TraficLights::disconnect(trafic_lights_list[i],
                                             trafic_lights_list[i + 1]);
    }
    if (i != 0) {
      diff_value -= TraficLights::disconnect(trafic_lights_list[i - 1],
                                             trafic_lights_list[i]);
    }
    if (j != sz - 1) {
      diff_value -= TraficLights::disconnect(trafic_lights_list[j],
                                             trafic_lights_list[j + 1]);
    }
    if (j != 0) {
      diff_value -= TraficLights::disconnect(trafic_lights_list[j - 1],
                                             trafic_lights_list[j]);
    }
    if (i != sz - 1) {
      diff_value += TraficLights::connect(trafic_lights_list[j],
                                          trafic_lights_list[i + 1]);
    }
    if (i != 0) {
      diff_value += TraficLights::connect(trafic_lights_list[i - 1],
                                          trafic_lights_list[j]);
    }
    if (j != sz - 1) {
      diff_value += TraficLights::connect(trafic_lights_list[i],
                                          trafic_lights_list[j + 1]);
    }
    if (j != 0) {
      diff_value += TraficLights::connect(trafic_lights_list[j - 1],
                                          trafic_lights_list[i]);
    }
    swap(trafic_lights_list[i], trafic_lights_list[j]);
    return diff_value;
  };

  auto virtual_swap_tl = [&](int i, int j) -> int {
    int diff_value = 0;
    if (i != sz - 1) {
      diff_value -= TraficLights::virtual_disconnect(trafic_lights_list[i],
                                                     trafic_lights_list[i + 1]);
    }
    if (i != 0) {
      diff_value -= TraficLights::virtual_disconnect(trafic_lights_list[i - 1],
                                                     trafic_lights_list[i]);
    }
    if (j != sz - 1) {
      diff_value -= TraficLights::virtual_disconnect(trafic_lights_list[j],
                                                     trafic_lights_list[j + 1]);
    }
    if (j != 0) {
      diff_value -= TraficLights::virtual_disconnect(trafic_lights_list[j - 1],
                                                     trafic_lights_list[j]);
    }
    if (i == 0) {
      diff_value += TraficLights::virtual_connect(
          dummy_tl, trafic_lights_list[j], trafic_lights_list[i + 1]);
    } else if (i == sz - 1) {
      diff_value += TraficLights::virtual_connect(
          trafic_lights_list[i - 1], trafic_lights_list[j], dummy_tl);
    } else {
      diff_value += TraficLights::virtual_connect(trafic_lights_list[i - 1],
                                                  trafic_lights_list[j],
                                                  trafic_lights_list[i + 1]);
    }
    if (j == 0) {
      diff_value += TraficLights::virtual_connect(
          dummy_tl, trafic_lights_list[i], trafic_lights_list[j + 1]);
    } else if (j == sz - 1) {
      diff_value += TraficLights::virtual_connect(
          trafic_lights_list[j - 1], trafic_lights_list[i], dummy_tl);
    } else {
      diff_value += TraficLights::virtual_connect(trafic_lights_list[j - 1],
                                                  trafic_lights_list[i],
                                                  trafic_lights_list[j + 1]);
    }
    return diff_value;
  };

  // rep(i, sz) rep(j, sz) {
  //   if (abs(i - j) <= 2) continue;

  //   if (i == 0 && j == 178) {
  //     trafic_lights_list[i].print();
  //     trafic_lights_list[i + 1].print();
  //     trafic_lights_list[j - 1].print();
  //     trafic_lights_list[j].print();
  //     trafic_lights_list[j + 1].print();
  //   }

  //   int tmp = virtual_swap_tl(i, j);
  //   int tmp2 = swap_tl(i, j);

  //   if (tmp != tmp2) {
  //     debug(i, j, sz, tmp, tmp2);

  //     trafic_lights_list[i].print();
  //     trafic_lights_list[i + 1].print();
  //     trafic_lights_list[j - 1].print();
  //     trafic_lights_list[j].print();
  //     trafic_lights_list[j + 1].print();

  //     assert(false);
  //   }

  //   // assert(virtual_swap_tl(i, j) == swap_tl(i, j));
  //   // assert(virtual_swap_tl(i, j) == swap_tl(i, j));
  // }

  const int64_t time_threshold = 2500;
  auto time_keeper = TimeKeeper(time_threshold);

  int cnt = 0;                         // debug用
  const static double START_TEMP = 5;  // 開始時の温度
  const static double END_TEMP = 1;    // 終了時の温度
  double progressRatio = 0;
  double temp = START_TEMP;

  // do {
  //   cnt++;
  //   // 温度管理
  //   progressRatio = (double)time_keeper.getTime() / (double)time_threshold;
  //   temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;
  //   // tempInv = 1.0 / temp;

  //   // swap近傍
  //   int i = randXor() % sz;
  //   int j = randXor() % sz;
  //   if (abs(i - j) <= 2) continue;

  //   // debug(ti, i, j);
  //   int delta_score = virtual_swap_tl(i, j);

  //   const double probability = exp((double)delta_score / temp);
  //   debug(probability, delta_score, progressRatio, temp);
  //   if (probability >= rand01()) {
  //     int res = swap_tl(i, j);
  //     if (res != delta_score) {
  //       debug(i, j, delta_score, res);
  //       swap_tl(i, j);
  //       trafic_lights_list[i - 1].print();
  //       trafic_lights_list[i].print();
  //       trafic_lights_list[i + 1].print();
  //       trafic_lights_list[j - 1].print();
  //       trafic_lights_list[j].print();
  //       trafic_lights_list[j + 1].print();
  //       assert(false);
  //     }
  //     value += delta_score;
  //   } else {
  //     // 未受理
  //   }
  // } while (!time_keeper.isTimeOver());

  // 山登り
  while (!time_keeper.isTimeOver()) {
    cnt++;
    int i = randXor() % sz;
    int j = randXor() % sz;
    if (abs(i - j) <= 2) continue;

    int delta_score = virtual_swap_tl(i, j);
    // debug(delta_score);
    if (delta_score >= 0) {
      int res = swap_tl(i, j);
      if (res != delta_score) {
        debug(i, j, delta_score, res);
        swap_tl(i, j);
        trafic_lights_list[i - 1].print();
        trafic_lights_list[i].print();
        trafic_lights_list[i + 1].print();
        trafic_lights_list[j - 1].print();
        trafic_lights_list[j].print();
        trafic_lights_list[j + 1].print();
        assert(false);
      }
      value += delta_score;
    } else {
      // 未受理
    }
  }

  debug("焼きなましスコア", cnt, value);

  vector<int> list_A;
  rep(i, sz) {
    if (i == 0) {
      for (auto v : trafic_lights_list[i].head) {
        list_A.emplace_back(v);
      }
    }
    for (auto v : trafic_lights_list[i].body) {
      list_A.emplace_back(v);
    }
    for (auto v : trafic_lights_list[i].tail) {
      list_A.emplace_back(v);
    }
  }
  // assert(list_A.size() <= LA);
  debug("long_long_A圧縮後", list_A.size());
  return list_A;
}

// 長さをLAに収める
vector<int> compress_trafic_lights_list_2(
    vector<int>& long_list_A, vector<set<int>>& traffic_light_set_vec) {
  //
  map<set<int>, int> st_mp;
  for (auto st : traffic_light_set_vec) st_mp[st]++;
  // listAに出現する各頂点の個数
  vector<int> occurrence_count(N);
  for (auto v : long_list_A) occurrence_count[v]++;
  // 本処理で削る個数
  int delete_count = (int)long_list_A.size() - LA;

  // 各場所のスコア
  vector<pair<int, int>> score_idx_pair_list;
  rep(i, long_list_A.size()) {
    int score = 0;
    for (int start = max(0, i - LB + 1);
         start <= i && start + LB <= (int)long_list_A.size(); start++) {
      set<int> st;
      rep(j, LB) st.insert(long_list_A[start + j]);
      score += st_mp[st];
    }
    score_idx_pair_list.emplace_back(score, i);
  }
  sort(all(score_idx_pair_list));

  vector<bool> delete_idx(long_list_A.size());
  // スコアが低い順に削除するが、listAに各頂点は最低1つは必要
  for (auto [score, idx] : score_idx_pair_list) {
    if (occurrence_count[long_list_A[idx]] == 1) continue;
    occurrence_count[long_list_A[idx]]--;
    delete_idx[idx] = true;
    if (--delete_count == 0) break;
  }
  assert(delete_count == 0);
  // debug(score_idx_pair_list);
  // debug(delete_idx);

  vector<int> list_A;

  rep(i, long_list_A.size()) {
    if (!delete_idx[i]) list_A.emplace_back(long_list_A[i]);
  }

  // debug(list_A.size());

  assert((int)list_A.size() == LA);

  return list_A;
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
      rep(j, l) exist_B_set.insert(now_A[pa + j]);
    }
    // 進む
    ret.emplace_back(v);
  }

  return Answer(ret, now_A);
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

int main() {
  process_input();
  all_pairs_shortest_path();

  // 先に経路を決める
  vector<set<int>> traffic_light_set_vec;
  vector<int> walk = find_smart_walk(traffic_light_set_vec);
  // find_naive_walk();
  // vector<int> walk = find_smart_walk();
  // debug(walk);

  vector<int> long_list_A = compress_trafic_lights_list(traffic_light_set_vec);

  vector<int> list_A =
      compress_trafic_lights_list_2(long_list_A, traffic_light_set_vec);

  // vector<int> walk = find_naive_walk();

  //
  // Answer ans = find_naive_answer(walk);
  Answer ans = find_smart_answer(walk, list_A);

  ans.print_list_A();
  ans.print_operation_list();

  debug(ans.calc_score());
}