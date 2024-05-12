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

int exp1(vl A, vl B) {
  int N = A.size();
  set<vl> st;
  st.insert(A);
  rep(ti, 5) {
    set<vl> newst;
    for (auto C : st) {
      for (int x = 0; x < 8; x++) {
        for (int y = x + 1; y <= 8; y++) {
          vl D = C;
          rep(i, N) D[i] = (D[i] + x) % y;
          newst.insert(D);
        }
      }
    }
    if (st.size() == newst.size()) return 0;
    swap(st, newst);
    if (st.count(B)) {
      return ti + 1;
    }
  }
  return 0;
}
bool exp2(vl A, vl B) {
  int N = A.size();
  set<vl> st;
  st.insert(A);
  rep(ti, 1) {
    set<vl> newst;
    for (auto C : st) {
      for (int x = 0; x < 10; x++) {
        for (int y = x + 1; y <= 10; y++) {
          vl D = C;
          rep(i, N) D[i] = (D[i] + x) % y;
          newst.insert(D);
        }
      }
    }
    swap(st, newst);
    if (st.count(B)) {
      debug(ti + 1);
      return true;
    }
  }
  return false;
}

bool exp3(vl A, vl B) {
  int N = A.size();
  set<vl> st;
  st.insert(A);
  rep(ti, 1) {
    set<vl> newst;
    for (auto C : st) {
      for (int x = 0; x < 1000; x++) {
        for (int y = x + 1; y <= 1000; y++) {
          vl D(N);
          rep(i, N) D[i] = (D[i] + x) % y;
          newst.insert(D);
        }
      }
    }
    swap(st, newst);
    if (st.count(B)) {
      debug(ti + 1);
      return true;
    }
  }
  return false;
}

struct Solver {
  void solve() {
    /* input */
    INT(N);
    VEC(ll, A, N);
    VEC(ll, B, N);

    /* solve */
    // exp1(A, B);
    vl AA(3);
    vl BB(3);

    vi cnt(10);
    rep(a1, 6) rep(a2, 6) rep(a3, 6) {
      AA[0] = a1, AA[1] = a2, AA[2] = a3;
      rep(b1, 6) rep(b2, 6) rep(b3, 6) {
        BB[0] = b1, BB[1] = b2, BB[2] = b3;
        // 流石に自明すぎるのは略
        if (!b1 && !b2 && !b3) {
          cnt[1]++;
          continue;
        }
        int isSame = 1;
        rep(i, AA.size()) if (AA[i] != BB[i]) isSame = 0;
        if (isSame) {
          cnt[0]++;
          continue;
        }

        int res = exp1(AA, BB);  //
        // bool res = exp2(AA, BB); // cnt:1615
        if (res) {
          cnt[res]++;
          // out(AA, "\n", BB);
        } else {
          cnt[9]++;
        }
      }
    }
    debug(cnt);

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