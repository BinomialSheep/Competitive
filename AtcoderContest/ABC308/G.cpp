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

template <typename U = unsigned, int B = 32>
class binary_trie {
  struct node {
    int cnt;
    node* ch[2];
    node() : cnt(0), ch{nullptr, nullptr} {}
  };
  node* add(node* t, U val, int b = B - 1) {
    if (!t) t = new node;
    t->cnt += 1;
    if (b < 0) return t;
    bool f = (val >> (U)b) & (U)1;
    t->ch[f] = add(t->ch[f], val, b - 1);
    return t;
  }
  node* del(node* t, U val, int b = B - 1) {
    assert(t);
    t->cnt -= 1;
    if (t->cnt == 0) return nullptr;
    if (b < 0) return t;
    bool f = (val >> (U)b) & (U)1;
    t->ch[f] = del(t->ch[f], val, b - 1);
    return t;
  }
  U get(node* t, int k, U bias, int b = B - 1) const {
    if (b < 0) return 0;
    int f = (bias >> (U)b) & (U)1, m = t->ch[f] ? t->ch[f]->cnt : 0;
    if (k < m) return get(t->ch[f], k, bias, b - 1) | ((U)f << (U)b);
    return get(t->ch[!f], k - m, bias, b - 1) | ((U)(!f) << (U)b);
  }
  node* root;

 public:
  binary_trie() : root(nullptr) {}
  int size() const { return root ? root->cnt : 0; }
  bool empty() const { return !root; }
  void insert(U val) { root = add(root, val); }
  void erase(U val) { root = del(root, val); }
  U max_element(U bias = 0) const {
    assert(root);
    return get(root, 0, ~bias);
  }
  U min_element(U bias = 0) const {
    assert(root);
    return get(root, 0, bias);
  }
  U kth_min(int k, U bias = 0) const {
    assert(0 <= k && k < size());
    return get(root, k, bias);
  }
  int lower_count(U val, U bias = 0) const {  // count x : (x ^ bias) < val
    node* t = root;
    int res = 0;
    for (int b = B - 1; b >= 0 && t; b--) {
      bool f = (val >> (U)b) & (U)1;
      bool g = (bias >> (U)b) & (U)1;
      res += (f && t->ch[g]) ? t->ch[g]->cnt : 0;
      t = t->ch[f ^ g];
    }
    return res;
  }
  U lower_bound(U val, U bias = 0) const {
    return kth_min(lower_count(val, bias), bias);
  }
  int count(U val) const {
    if (!root) return 0;
    node* t = root;
    for (int i = B - 1; i >= 0; i--) {
      t = t->ch[(val >> (U)i) & (U)1];
      if (!t) return 0;
    }
    return t->cnt;
  }
};

struct Solver {
  void solve() {
    /* input */
    binary_trie bt = binary_trie();
    multiset<int> mt;
    INT(Q);
    rep(qi, Q) {
      INT(ty);
      if (ty == 1) {
        INT(X);
        bt.insert(X);
        mt.insert(X);
      } else if (ty == 2) {
        INT(X);
        bt.erase(X);
        auto it = mt.lower_bound(X);
        mt.erase(it);
      } else {
        int ans = (1 << 30) + 10;
        for (auto v : mt) {
          int mn = bt.min_element(v);
          out(v, mn, v ^ mn);
          if (v ^ mn != 0) chmin(ans, v ^ mn);
        }
        out(ans);
        // rep(j, bt.size()) out(bt[j]);
      }
      // out(bt.size());
    }

    /* solve */

    /* output */
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}