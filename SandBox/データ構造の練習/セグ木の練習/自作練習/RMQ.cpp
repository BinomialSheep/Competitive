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

// https://tsutaj.hatenablog.com/entry/2017/03/29/204841
// セグメント木をソラで書きたいあなたへ

struct SegmentTree {
 private:
  int n;
  vector<ll> node;
  const ll INF = 1e18;

 public:
  // 元配列vをセグ木で表現する
  SegmentTree(vl v) {
    int sz = (int)v.size();
    n = 1;
    while (n < sz) n *= 2;        // 2べきで持つ
    node.resize(2 * n - 1, INF);  // 先祖はn-1個ある
    // 最下段のセット
    rep(i, sz) node[i + n - 1] = v[i];
    // 計算しながら上をセット
    for (int i = n - 2; i >= 0; i--)
      node[i] = min(node[2 * i + 1], node[2 * i + 2]);
  }
  // v[x]（0-indexed）をvalに更新
  void update(int x, ll val) {
    x += n - 1;  // 最下段のindex
    // 最下段から最上段に上る
    node[x] = val;
    while (x > 0) {
      x = (x - 1) / 2;
      node[x] = min(node[2 * x + 1], node[2 * x + 2]);
    }
  }
  // 要求区間[a, b)の要素の最小値を答える
  // k := 自分がいるノードのインデックス
  // 対象区間（自身の範囲）は[l, r)にあたる
  ll getmin(int a, int b, int k = 0, int l = 0, int r = -1) {
    if (r == -1) r = n;  // NOTE:デフォルト引数にstaticでないnは使えない
    // 完全に守備範囲外なら、単位元を返す
    if (r <= a || b <= l) return INF;
    // 完全に被覆してるなら、そのまま返す
    debug(a, b, k, l, r);
    if (a <= l && r <= b) return node[k];
    // 一部一致なら、子を探索する
    ll left = getmin(a, b, 2 * k + 1, l, (l + r) / 2);
    ll right = getmin(a, b, 2 * k + 2, (l + r) / 2, r);
    return min(left, right);
  }

  // デバッグ用
  void printDebug() {
    debug(n, node.size());
    debug(node);
  }
};

int main() {
  INT(n, q);
  ll ini = (1LL << 31) - 1;
  vl v(n, ini);
  SegmentTree seg(v);
  // seg.printDebug();

  rep(qi, q) {
    INT(com, x, y);
    if (com == 0) {
      seg.update(x, y);
    } else {
      out(seg.getmin(x, y + 1));
    }
  }

  return 0;
}