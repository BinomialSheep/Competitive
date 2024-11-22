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

constexpr int N = 1000;
vector<pair<int, int>> AB(N);

void process_input() {
  INT(N2);
  rep(i, N) { cin >> AB[i].first >> AB[i].second; }
  sort(all(AB));
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
  map<pair<int, int>, set<pair<int, int>>> from;

  Graph() {}

  void add(int x, int y, int x2, int y2) {
    pair<int, int> p1 = make_pair(x, y);
    pair<int, int> p2 = make_pair(x2, y2);
    to[p1].insert(p2);
    from[p2].insert(p1);
  }

  // fromから(to_x, to_y, from_x, from_y)を削除する
  void del_from(int x2, int y2, int x, int y) {
    //
    assert(from.count(make_pair(x2, y2)));
    from[make_pair(x2, y2)].erase(make_pair(x, y));
  }

  void update_best_graph() {
    // fromごとに見て整理する
    set<pair<int, int>> from_set;
    for (auto&& [key, _] : to) from_set.emplace(key);
    to.clear();

    map<pair<int, int>, set<pair<int, int>>> new_from;

    for (auto&& [to_p, _] : from) {
      int min_cost = 2e9 + 9;
      auto [x2, y2] = to_p;

      for (auto&& [x, y] : from_set) {
        if (x > x2) break;
        if (y > y2) continue;
        if (x == x2 && y == y2) continue;
        chmin(min_cost, x2 - x + y2 - y);
      }

      set<pair<int, int>> new_from_set;
      for (auto&& [x, y] : from_set) {
        if (x > x2) break;
        if (y > y2) continue;
        if (min_cost == x2 - x + y2 - y) {
          new_from_set.emplace(x, y);
          to[make_pair(x, y)].emplace(x2, y2);
        }
      }
      new_from[to_p] = new_from_set;
    }
    swap(from, new_from);
  }

  ll calc_score() {
    ll score = 0;
    for (auto&& [to_p, from_set] : from) {
      score += to_p.first - (*from_set.begin()).first + to_p.second -
               (*from_set.begin()).second;
    }
    return score;
  }

  void process_output() {
    out(from.size());
    for (auto&& [to_p, from_set] : from) {
      out((*from_set.begin()).first, (*from_set.begin()).second, to_p.first,
          to_p.second);
    }
  }
};

int main() {
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

  rep(i, 100) {
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
      graph.del_from(to_x_1, to_y_1, from_x, from_y);
      graph.del_from(to_x_2, to_y_2, from_x, from_y);

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

  graph.update_best_graph();

  // debug

  // for (auto [from_p, to_set] : graph.to) {
  //   debug(from_p, to_set.size());
  // }

  // output
  // cerr << graph.calc_score() << " " << M << endl;
  cerr << graph.calc_score() << endl;
  graph.process_output();
}