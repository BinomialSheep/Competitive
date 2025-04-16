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

int N = 20;
vector<string> C(N);
vector<int> dy = {1, -1, 0, 0};
vector<int> dx = {0, 0, 1, -1};

void exec_input() {
  int _;
  cin >> _;
  rep(i, N) cin >> C[i];
}

// ウルトラ自明解 400564
vector<pair<char, int>> stupid() {
  vector<pair<char, int>> ret;

  rep(i, N) rep(j, N) {
    if (C[i][j] == 'x') {
      // 各方向に
      int d = -1;
      rep(di, 4) {
        int ok = 1;
        int y = i, x = j;
        while (0 <= y && y < N && 0 <= x && x < N) {
          if (C[y][x] == 'o') ok = 0;
          y += dy[di], x += dx[di];
        }
        if (ok) d = di;
      }
      assert(d != -1);

      int y = i, x = j, cnt = 0;
      while (0 <= y && y < N && 0 <= x && x < N) {
        cnt++;
        y += dy[d], x += dx[d];
      }
      // debug(i, j, d, cnt);
      if (d == 0) {
        rep(k, cnt) ret.emplace_back('D', j);
        rep(k, cnt) ret.emplace_back('U', j);
      } else if (d == 1) {
        rep(k, cnt) ret.emplace_back('U', j);
        rep(k, cnt) ret.emplace_back('D', j);
      } else if (d == 2) {
        rep(k, cnt) ret.emplace_back('R', i);
        rep(k, cnt) ret.emplace_back('L', i);
      } else if (d == 3) {
        rep(k, cnt) ret.emplace_back('L', i);
        rep(k, cnt) ret.emplace_back('R', i);
      }
    }
  }
  return ret;
}
// 一番近く追い出せる方向に追い出す 426558
vector<pair<char, int>> stupid_2() {
  vector<pair<char, int>> ret;

  rep(i, N) rep(j, N) {
    if (C[i][j] == 'x') {
      // 各方向に
      int d = -1, cnt = 1e9;
      rep(di, 4) {
        int ok = 1;
        int y = i, x = j, nowcnt = 0;
        while (0 <= y && y < N && 0 <= x && x < N) {
          nowcnt++;
          if (C[y][x] == 'o') {
            ok = 0;
            break;
          }
          y += dy[di], x += dx[di];
        }
        if (ok && chmin(cnt, nowcnt)) d = di;
      }
      assert(d != -1);

      // debug(i, j, d, cnt);
      if (d == 0) {
        rep(k, cnt) ret.emplace_back('D', j);
        rep(k, cnt) ret.emplace_back('U', j);
      } else if (d == 1) {
        rep(k, cnt) ret.emplace_back('U', j);
        rep(k, cnt) ret.emplace_back('D', j);
      } else if (d == 2) {
        rep(k, cnt) ret.emplace_back('R', i);
        rep(k, cnt) ret.emplace_back('L', i);
      } else if (d == 3) {
        rep(k, cnt) ret.emplace_back('L', i);
        rep(k, cnt) ret.emplace_back('R', i);
      }
    }
  }
  return ret;
}

// まとめて追い出せるなら追い出す（不完全） 438,364
vector<pair<char, int>> stupid_3() {
  vector<pair<char, int>> ret;
  // key：(動く方向、動く行あるいは列), value：動かす回数
  map<pair<int, int>, int> mp;

  rep(i, N) rep(j, N) {
    if (C[i][j] == 'x') {
      int d = -1, cnt = 1e9;
      rep(di, 4) {
        int ok = 1;
        int y = i, x = j, nowcnt = 0;
        while (0 <= y && y < N && 0 <= x && x < N) {
          nowcnt++;
          if (C[y][x] == 'o') {
            ok = 0;
            break;
          }
          y += dy[di], x += dx[di];
        }
        if (ok && chmin(cnt, nowcnt)) d = di;
      }
      assert(d != -1);
      if (d < 2) {
        chmax(mp[make_pair(d, j)], cnt);

      } else {
        chmax(mp[make_pair(d, i)], cnt);
      }

      debug(i, j, d, cnt);
    }
  }

  for (auto [p, cnt] : mp) {
    int d = p.first, idx = p.second;
    if (d == 0) {
      rep(k, cnt) ret.emplace_back('D', idx);
      rep(k, cnt) ret.emplace_back('U', idx);
    } else if (d == 1) {
      rep(k, cnt) ret.emplace_back('U', idx);
      rep(k, cnt) ret.emplace_back('D', idx);
    } else if (d == 2) {
      rep(k, cnt) ret.emplace_back('R', idx);
      rep(k, cnt) ret.emplace_back('L', idx);
    } else if (d == 3) {
      rep(k, cnt) ret.emplace_back('L', idx);
      rep(k, cnt) ret.emplace_back('R', idx);
    }
  }

  return ret;
}

int calc_score(const vector<pair<char, int>>& ans) {
  return 8 * N * N - (int)ans.size();
}

int main() {
  exec_input();
  //
  debug(calc_score(stupid()));
  debug(calc_score(stupid_2()));
  vector<pair<char, int>> res = stupid_3();
  debug(calc_score(res));
  out(res);
}