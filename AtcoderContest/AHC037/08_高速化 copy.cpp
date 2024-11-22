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

constexpr int N = 1000;
vector<pair<int, int>> AB(N);

int MIN_Y = 2e9, MIN_X = 2e9, MAX_Y = 0, MAX_X = 0;

void process_input() {
  INT(N2);
  rep(i, N) { cin >> AB[i].first >> AB[i].second; }
  sort(all(AB));

  for (auto [x, y] : AB) {
    chmin(MIN_X, x);
    chmin(MIN_Y, y);
    chmax(MAX_X, x);
    chmax(MAX_Y, y);
  }
  MAX_X++, MAX_Y++;
}

class Operation {
 public:
  int x_, y_, x2_, y2_;
  Operation() {}
  Operation(int x, int y, int x2, int y2) : x_(x), y_(y), x2_(x2), y2_(y2) {}

  static ll calc_score(vector<Operation>& operation_list) {
    ll score = 0;

    for (auto&& o : operation_list) {
      score += o.x2_ - o.x_ + o.y2_ - o.y_;
    }
    return score;
  }

  static void process_output(vector<Operation>& operation_list) {
    out(operation_list.size());
    for (auto&& o : operation_list) {
      out(o.x_, o.y_, o.x2_, o.y2_);
    }
  }
};

class Graph {
 public:
  map<pair<int, int>, set<pair<int, int>>> to;
  map<pair<int, int>, pair<int, int>> from;

  Graph() {}

  void add(int x, int y, int x2, int y2) {
    pair<int, int> p1 = make_pair(x, y);
    pair<int, int> p2 = make_pair(x2, y2);
    to[p1].insert(p2);
    from[p2] = p1;
  }

  ll calc_delta_score(int new_x, int new_y, int& from_x, int& from_y) {
    ll ret = 0;
    // どこから伸ばすのが最善か
    int min_cost = new_x + new_y;
    for (auto&& [to_p, _] : from) {
      auto [x, y] = to_p;
      if (x > new_x) break;
      if (y > new_y) continue;
      if (chmin(min_cost, new_x - x + new_y - y)) {
        from_x = x, from_y = y;
      }
    }
    ret -= min_cost;
    // どこに伸ばすことになるか
    int minx = 1e9, miny = 1e9;
    for (auto&& [to_p, from_p] : from) {
      auto [x2, y2] = to_p;
      if (x2 < new_x || y2 < new_y) continue;
      if (x2 > minx && y2 > miny) continue;
      auto [x, y] = from_p;
      int old_cost = x2 - x + y2 - y;
      int new_cost = x2 - new_x + y2 - new_y;
      if (new_cost < old_cost) {
        ret += old_cost - new_cost;
      } else {
        chmin(minx, x2);
        chmin(miny, y2);
      }
    }

    return ret;
  }

  void accept_add_neighborhood(int new_x, int new_y, int from_x, int from_y) {
    // どこから伸ばすのが最善か
    add(from_x, from_y, new_x, new_y);

    // どこに伸ばすことになるか
    int minx = 1e9, miny = 1e9;
    for (auto&& [to_p, from_p] : from) {
      auto [x2, y2] = to_p;
      if (x2 < new_x || y2 < new_y) continue;
      if (x2 == new_x && y2 == new_y) continue;
      if (x2 > minx && y2 > miny) continue;
      auto [x, y] = from_p;
      int old_cost = x2 - x + y2 - y;
      int new_cost = x2 - new_x + y2 - new_y;
      if (new_cost > old_cost) {
        chmin(minx, x2);
        chmin(miny, y2);
        continue;
      } else if (new_cost == old_cost) {
        add(new_x, new_y, x2, y2);
      } else {
        to[from_p].erase(to_p);
        from_p = make_pair(new_x, new_y);
      }
    }
  }

  ll calc_score() {
    ll score = 0;
    for (auto&& [to_p, from_p] : from) {
      score += to_p.first - from_p.first + to_p.second - from_p.second;
    }
    return score;
  }

  void process_output() {
    out(from.size());
    for (auto&& [to_p, from_p] : from) {
      out(from_p.first, from_p.second, to_p.first, to_p.second);
    }
  }
};

int main() {
  const int64_t time_threshold = 199000;
  auto time_keeper = TimeKeeper(time_threshold);

  process_input();

  set<pair<int, int>> now_set;
  now_set.emplace(0, 0);

  Graph graph;

  for (auto [x2, y2] : AB) {
    int min_cost = 2e9 + 9;
    int min_x = 0, min_y = 0;

    for (auto [x, y] : now_set) {
      if (x > x2) break;
      if (y > y2) continue;
      if (chmin(min_cost, x2 - x + y2 - y)) min_x = x, min_y = y;
    }

    now_set.emplace(x2, y2);
    graph.add(min_x, min_y, x2, y2);
  }

  rep(i, 10) {
    int lastM = (int)graph.from.size();
    // debug(i, lastM);
    for (auto&& [from_p, to_vec] : graph.to) {
      int sz = (int)to_vec.size();
      auto [from_x, from_y] = from_p;

      auto choose_improve_2_points = [&](int& x1, int& y1, int& x2,
                                         int& y2) -> bool {
        if (sz == 1) return false;

        // 基本的にはto_vecの後ろの2つを削除する

        auto it = to_vec.begin();
        auto [to_x_1, to_y_1] = *it;
        auto it2 = to_vec.begin();
        it2++;
        while (it2 != to_vec.end()) {
          auto [to_x_2, to_y_2] = *it2;
          if (min(to_x_1, to_x_2) != from_x || min(to_y_1, to_y_2) != from_y) {
            x1 = to_x_1, x2 = to_x_2, y1 = to_y_1, y2 = to_y_2;
            to_vec.erase(it);
            to_vec.erase(it2);
            return true;
          }
          it2++;
        }
        return false;
      };

      int to_x_1, to_y_1, to_x_2, to_y_2;
      if (!choose_improve_2_points(to_x_1, to_y_1, to_x_2, to_y_2)) continue;

      // from_vecからも削除する
      // graph.del_from(to_x_1, to_y_1, from_x, from_y);
      // graph.del_from(to_x_2, to_y_2, from_x, from_y);

      // その中間に置く
      int x3 = min(to_x_1, to_x_2);
      int y3 = min(to_y_1, to_y_2);

      // 既に別の場所で作られていることもある
      if (!graph.from.count(make_pair(x3, y3))) {
        graph.add(from_x, from_y, x3, y3);
      }
      graph.add(x3, y3, to_x_1, to_y_1);
      graph.add(x3, y3, to_x_2, to_y_2);
    }
    if (lastM == (int)graph.from.size()) break;
  }
  // graph.update_best_graph();

  vector<pair<int, int>> to_set_vec;
  for (auto&& [to, from] : graph.from) to_set_vec.emplace_back(to);

  // 焼きなましますか……
  int loop_cnt = 0, add_cnt = 0;
  while (true) {
    loop_cnt++;
    if (loop_cnt % 64 == 0 && time_keeper.isTimeOver()) break;
    // ランダムな頂点を選ぶ
    int new_x = randXor() % MAX_X, new_y = randXor() % MAX_Y;
    if (randXor() % 2) {
      // 有望な頂点を選ぶ
      int idx = randXor() % to_set_vec.size();
      auto to = to_set_vec[idx];
      auto from = graph.from[to];

      if (from.first == to.first || from.second == to.second) {
      } else {
        if (randXor() % 2) {
          new_x = from.first, new_y = to.second;
        } else {
          new_x = to.first, new_y = from.second;
        }
      }
    }
    auto new_xy = make_pair(new_x, new_y);
    if (graph.from.count(new_xy)) continue;
    // 加えた場合のスコアを計算する
    int from_x = 0, from_y = 0;
    ll delta_score = graph.calc_delta_score(new_x, new_y, from_x, from_y);

    if (delta_score > 0) {
      graph.accept_add_neighborhood(new_x, new_y, from_x, from_y);
      add_cnt++;
      // debug(delta_score, new_xy);
      // break;
    }
  }
  debug(loop_cnt, add_cnt);

  rep(i, 10) {
    int lastM = (int)graph.from.size();
    // debug(i, lastM);
    for (auto&& [from_p, to_vec] : graph.to) {
      // debug(from_p);
      int sz = (int)to_vec.size();
      auto [from_x, from_y] = from_p;

      auto choose_improve_2_points = [&](int& x1, int& y1, int& x2,
                                         int& y2) -> bool {
        if (sz < 1) return false;

        // 基本的にはto_vecの後ろの2つを削除する

        auto it = to_vec.begin();
        auto [to_x_1, to_y_1] = *it;
        auto it2 = to_vec.begin();
        it2++;
        while (it2 != to_vec.end()) {
          auto [to_x_2, to_y_2] = *it2;
          if (min(to_x_1, to_x_2) != from_x || min(to_y_1, to_y_2) != from_y) {
            x1 = to_x_1, x2 = to_x_2, y1 = to_y_1, y2 = to_y_2;
            to_vec.erase(it);
            to_vec.erase(it2);
            return true;
          }
          it2++;
        }
        return false;
      };

      int to_x_1, to_y_1, to_x_2, to_y_2;
      if (!choose_improve_2_points(to_x_1, to_y_1, to_x_2, to_y_2)) continue;

      // from_vecからも削除する
      // graph.del_from(to_x_1, to_y_1, from_x, from_y);
      // graph.del_from(to_x_2, to_y_2, from_x, from_y);

      // その中間に置く
      int x3 = min(to_x_1, to_x_2);
      int y3 = min(to_y_1, to_y_2);

      // 既に別の場所で作られていることもある
      if (!graph.from.count(make_pair(x3, y3))) {
        graph.add(from_x, from_y, x3, y3);
      }
      graph.add(x3, y3, to_x_1, to_y_1);
      graph.add(x3, y3, to_x_2, to_y_2);

      if (graph.from.size() == 5000) break;
    }
    if (graph.from.size() == 5000 || lastM == (int)graph.from.size()) break;
  }

  // debug

  // for (auto [from_p, to_set] : graph.to) {
  //   debug(from_p, to_set.size());
  // }

  // output
  // cerr << graph.calc_score() << " " << M << endl;
  debug(time_threshold, graph.calc_score());
  // cerr << graph.calc_score() << endl;
  graph.process_output();
}