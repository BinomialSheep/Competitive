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

// 定数の設定
const int BOARD_SIZE = 5;
const int NUM_VALUES = 10;  // 各セルが取りうる値の数 (例えば、0-9)

// ランダムな64ビット整数を生成するためのエンジン
const int SEED = 1;
std::mt19937_64 rng(SEED);
std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);

// Zobristハッシュ用のテーブル
uint64_t zobristTable[5][5][26];
uint64_t zobristPosition[5][5][5];
uint64_t zobristDestination[5][6][5];
uint64_t zobristAssigned[5][26];

// Zobristテーブルの初期化
void initializeZobrist() {
  rep(i, 5) rep(j, 5) rep(k, 26) zobristTable[i][j][k] = dist(rng);
  rep(i, 5) rep(j, 5) rep(k, 5) zobristPosition[i][j][k] = dist(rng);
  rep(i, 5) rep(j, 6) rep(k, 5) zobristDestination[i][j][k] = dist(rng);
  rep(i, 5) rep(j, 25) zobristAssigned[i][j] = dist(rng);
}

// ボードの初期ハッシュ値を計算
uint64_t computeInitialHash(const vector<vector<int>>& board, vpii& position,
                            vpii& destination, vi& assigneds) {
  uint64_t hash = 0;
  rep(i, 5) rep(j, 5) {
    int value = board[i][j];
    hash ^= zobristTable[i][j][value];
  }
  rep(i, 5) hash ^= zobristPosition[i][position[i].first][position[i].second];
  rep(i, 5) hash ^=
      zobristDestination[i][destination[i].first][destination[i].second];
  rep(i, 5) hash ^= zobristAssigned[i][assigneds[i]];

  return hash;
}

// ボードの一部が変更された際にハッシュ値を更新
uint64_t updateHash(uint64_t currentHash, int x, int y, int oldValue,
                    int newValue) {
  currentHash ^= zobristTable[x][y][oldValue];  // 古い値をハッシュから除外
  currentHash ^= zobristTable[x][y][newValue];  // 新しい値をハッシュに追加
  return currentHash;
}

int main() {
  // ボードの例
  vector<vector<int>> board = {{1, 2, 3, 4, 5},
                               {6, 7, 8, 9, 0},
                               {1, 2, 3, 4, 5},
                               {6, 7, 8, 9, 0},
                               {1, 2, 3, 4, 5}};

  vector<pair<int, int>> positions = {{1, 2}, {0, 1}, {4, 2}, {2, 1}, {3, 1}};
  vector<pair<int, int>> destination = {{1, 2}, {0, 0}, {4, 2}, {2, 1}, {5, 4}};
  vector<int> assigneds = {1, 6, 3, 4, 5};

  // Zobristテーブルの初期化
  initializeZobrist();

  // 初期ハッシュ値の計算
  uint64_t hash = computeInitialHash(board, positions, destination, assigneds);
  cout << "初期ハッシュ: " << hash << endl;

  // ボードの更新とハッシュ値の更新
  int x = 2, y = 3;  // 変更する位置
  int oldValue = board[x][y];
  int newValue = 7;  // 新しい値

  board[x][y] = newValue;
  hash = updateHash(hash, x, y, oldValue, newValue);
  cout << "更新後のハッシュ: " << hash << endl;

  return 0;
}