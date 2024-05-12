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

struct Solver {
  void solve() {
    /* input */
    int M = 108;
    vi A = {2, 3, 4, 1, 6, 7, 8, 9, 5, 11, 12, 13, 14, 15, 16, 10};
    rep(i, 8) A.emplace_back(18 + i);
    A.emplace_back(17);
    rep(i, 10) A.emplace_back(27 + i);
    A.emplace_back(26);
    rep(i, 12) A.emplace_back(38 + i);
    A.emplace_back(37);
    rep(i, 16) A.emplace_back(51 + i);
    A.emplace_back(50);
    rep(i, 18) A.emplace_back(68 + i);
    A.emplace_back(67);
    rep(i, 22) A.emplace_back(87 + i);
    A.emplace_back(86);
    set<int> st;
    rep(i, 108) st.insert(A[i]);
    debug(A);
    debug(st);

    /* solve */
    cout << M << endl;
    rep(i, M - 1) cout << A[i] << " ";
    cout << A[M - 1] << endl;

    //
    vi B(M);
    rep(i, M) cin >> B[i];

    deque<int> dq;
    int v = A[107] - 86;
    int i = v;
    while (i <= 1e9) {
      dq.push_back(i);
      i += 23;
    }
    v = A[84] - 67;
    int sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 19 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[65] - 49;
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 17 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[48] - 36;
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 13 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[35] - 25;
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 11 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[24] - 16;
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 9 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[15] - 9;
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 7 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[8] - 4;
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 5 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }
    v = A[3];
    sz = dq.size();
    rep(i, sz) {
      if (dq.front() % 4 == v) {
        dq.push_back(dq.front());
      }
      dq.pop_front();
    }

    // A[0] A[4] A[10] A[17] A[26] A[37] A[50] A[67] A[86]

    cout << dq[0] << endl;

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