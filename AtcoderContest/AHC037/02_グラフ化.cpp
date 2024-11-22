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
  map<pair<int, int>, vector<pair<int, int>>> to;
  map<pair<int, int>, vector<pair<int, int>>> from;

  Graph() {}

  void add(int x, int y, int x2, int y2) {
    pair<int, int> p1 = make_pair(x, y);
    pair<int, int> p2 = make_pair(x2, y2);
    to[p1].push_back(p2);
    from[p2].push_back(p1);
  }

  ll calc_score() {
    ll score = 0;
    for (auto&& [to_p, from_vec] : from) {
      score +=
          to_p.first - from_vec[0].first + to_p.second - from_vec[0].second;
    }
    return score;
  }

  void process_output() {
    out(from.size());
    for (auto&& [to_p, from_vec] : from) {
      out(from_vec[0].first, from_vec[0].second, to_p.first, to_p.second);
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

  // output
  cerr << graph.calc_score() << endl;
  graph.process_output();
}