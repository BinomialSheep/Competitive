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

// https://tsutaj.hatenablog.com/entry/2017/03/30/224339
// 遅延評価セグメント木をソラで書きたいあなたに
struct LazySegmentTree {
  int n;
  vl node, lazy;

 public:
  LazySegmentTree(vl v) {
    int sz = (int)v.size();
    n = 1;
    while (n < sz) n *= 2;
    node.resize(2 * n - 1);
    lazy.resize(2 * n - 1, 0);

    rep(i, sz) node[i + n - 1] = v[i];
    for (int i = n - 2; i >= 0; i--)
      node[i] = node[i * 2 + 1] + node[i * 2 + 2];
  }

  // k番目のノードについて遅延評価を行う
  void eval(int k, int l, int r) {
    // 遅延配列が空でない場合、自ノード及び子ノードへの値の伝搬が起こる
    if (lazy[k] != 0) {
      node[k] += lazy[k];
      if (r - l > 1) {  // r-l==1なら最下段
        lazy[2 * k + 1] += lazy[k] / 2;
        lazy[2 * k + 2] += lazy[k] / 2;
      }
      lazy[k] = 0;
    }
  }

  // [a, b)にxを加算
  void add(int a, int b, ll x, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    // k番目のノードに対して遅延評価を行う
    eval(k, l, r);
    // 範囲外
    if (b <= l || r <= a) return;
    // 完全に被覆
    if (a <= l && r <= b) {
      lazy[k] += (r - l) * x;
      eval(k, l, r);
      return;
    }
    // それ以外
    add(a, b, x, 2 * k + 1, l, (l + r) / 2);
    add(a, b, x, 2 * k + 2, (l + r) / 2, r);
    node[k] = node[2 * k + 1] + node[2 * k + 2];
  }

  // [a, b]の区間和を取得
  ll getsum(int a, int b, int k = 0, int l = 0, int r = -1) {
    if (r < 0) r = n;
    if (b <= l || r <= a) return 0;
    // 関数が呼び出されたら評価
    eval(k, l, r);
    if (a <= l && r <= b) return node[k];
    ll suml = getsum(a, b, 2 * k + 1, l, (l + r) / 2);
    ll sumr = getsum(a, b, 2 * k + 2, (l + r) / 2, r);
    return suml + sumr;
  }
};

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja
int main() {
  INT(n, q);
  vl A(n);
  LazySegmentTree seg(A);
  while (q--) {
    INT(ty);
    if (ty == 0) {
      INT(s, t, x);
      --s;
      seg.add(s, t, x);
    } else {
      INT(s, t);
      --s;
      out(seg.getsum(s, t));
    }
  }

  return 0;
}