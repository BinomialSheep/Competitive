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

  Square(int x1, int y1, int x2, int y2) {
    _x1 = min(x1, x2);
    _x2 = max(x1, x2);
    _y1 = min(y1, y2);
    _y2 = max(y1, y2);
    _cnt_saba = 1;
    _cnt_iwashi = 0;
  }

  static bool margeable(Square& s1, Square& s2, int iwashi = 0) {
    // s1からs2のあいだにイワシがn匹以下しかいなければOK
    int x1 = min(s1._x1, s2._x1);
    int x2 = max(s1._x2, s2._x2);
    int y1 = min(s1._y1, s2._y1);
    int y2 = max(s1._y2, s2._y2);

    auto it = iwashi_XY_map.lower_bound(x1);
    int iwashi_cnt = 0;
    while (it != iwashi_XY_map.end()) {
      if (it->first > x2) break;
      for (auto y : it->second) {
        if (y1 <= y && y <= y2) {
          iwashi_cnt++;
        }
        if (y > y2) break;
      }
      it++;
    }
    return iwashi_cnt <= iwashi;
  }

  static Square marge(Square& s1, Square& s2) {
    Square ret = Square(min(s1._x1, s2._x1), min(s1._y1, s2._y1),
                        max(s1._x2, s2._x2), max(s1._y2, s2._y2));
    ret._cnt_saba = s1._cnt_saba + s2._cnt_saba;
    return ret;
  }

  void print() {
    // デバッグ用出力
    debug(_x1, _x2, _y1, _y2, _cnt_saba, _cnt_iwashi);
  }
  // サバ降順ソート
  bool operator<(const Square& another) const {
    // メンバ変数であるnum1で比較した結果を
    // この構造体の比較とする
    return _cnt_saba > another._cnt_saba;
  }

  void test_output() {
    out(4);
    out(_x1, _y1);
    out(_x2, _y1);
    out(_x2, _y2);
    out(_x1, _y2);
  }
};

int main() {
  /* input */
  process_input();
  init_XY_map();

  /* solve */
  // 正方形をいっぱい作る
  vector<Square> square_vec;
  rep(i, input_N) {
    Square square(input_saba_X[i], input_saba_Y[i], input_saba_X[i],
                  input_saba_Y[i]);
    square_vec.push_back(square);
  }

  // 長方形を作る
  {
    int flag = 1;
    vector<int> used(input_N);
    while (flag) {
      flag = 0;
      rep(i, input_N) used[i] = 0;

      map<pair<int, int>, int> idx_mp;
      rep(i, square_vec.size()) {
        idx_mp[make_pair(square_vec[i]._x1, square_vec[i]._y1)] = i;
      }
      // 近い順にソート
      vector<pair<int, pair<int, int>>> dist_pair;
      // 距離100以下のものに限定する
      const int threshold = 100;
      rep(i, (int)square_vec.size()) {
        int x2i = square_vec[i]._x2, y2i = square_vec[i]._y2;
        auto it = saba_XY_map.lower_bound(x2i);
        while (it != saba_XY_map.end()) {
          int x = it->first;
          assert(x >= x2i);
          if (x - x2i > threshold) break;
          int yy = -1;
          for (auto y : it->second) {
            if (x == x2i && y == y2i) continue;
            if (y < y2i) {
              yy = y;
              continue;
            }
            assert(y >= y2i);
            // 右上
            int dist_right = y - y2i + x - x2i;
            auto p = make_pair(x, y);
            if (dist_right <= threshold && idx_mp.count(p) && idx_mp[p] != i)
              dist_pair.emplace_back(dist_right, make_pair(i, idx_mp[p]));
            break;
          }
          if (yy != -1) {
            // 左上
            int dist_left = y2i - yy + x - x2i;
            auto p = make_pair(x, yy);
            if (dist_left <= threshold && idx_mp.count(p) && idx_mp[p] != i)
              dist_pair.emplace_back(dist_left, make_pair(i, idx_mp[p]));
          }
          it++;
        }
      }
      sort(all(dist_pair));
      // debug(dist_pair);

      vector<Square> new_square_vec;
      for (auto [d, p] : dist_pair) {
        if (used[p.first] || used[p.second]) continue;
        // 範囲内にイワシがいなければマージする

        if (Square::margeable(square_vec[p.first], square_vec[p.second])) {
          // debug(d, p);
          // square_vec[p.first].print(), square_vec[p.second].print();
          new_square_vec.push_back(
              Square::marge(square_vec[p.first], square_vec[p.second]));
          flag = 1;
          used[p.first] = used[p.second] = 1;
        }
      }
      rep(i, square_vec.size()) if (!used[i])
          new_square_vec.push_back(square_vec[i]);
      swap(square_vec, new_square_vec);
    }
  }

  // 長方形の道を作る
  // サバの数で降順ソート
  sort(all(square_vec));

  /* output */
  square_vec[0].test_output();
}