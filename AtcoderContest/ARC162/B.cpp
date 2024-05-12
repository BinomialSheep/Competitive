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
#include <atcoder/all>
// using namespace atcoder;

long long calcInvNum(int maxV, vector<int>& v) {
  ll ret = 0;
  // 0-indexedなので+1、sumでr+1未満を指定したいので更に+1
  atcoder::fenwick_tree<int> fw(maxV + 2);
  for (int i = 0; i < (int)v.size(); i++) {
    // 自分より大きいのに左側にある数を数える
    // 自分より右側の数 = BITの総和（これまで見た数） - 自分より左側の数
    ret += i - fw.sum(0, v[i] + 1);
    // 自分の位置に1を足す
    fw.add(v[i], 1);
  }
  return ret;
}

struct Solver {
  void solve() {
    /* input */
    INT(N);
    VEC(int, P, N);

    ll invNum = calcInvNum(N, P);

    if (invNum % 2) {
      out("No");
      return;
    }
    if (N == 2) {
      if (P[0] == 1) {
        out("Yes");
        out(0);
      } else {
        out("No");
      }
      return;
    }

    vi ansi;
    vi ansj;

    int i = 0;

    while (i < N) {
      debug(i, P);
      if (P[i] == i + 1) {
        i++;
        continue;
      }
      for (int j = i + 1; j < N; j++) {
        if (P[j] == i + 1) {
          if (j == N - 1) {
            ansi.push_back(N - 1);
            ansj.push_back(N - 3);
            swap(P[N - 3], P[N - 2]);
            swap(P[N - 2], P[N - 1]);
          } else {
            ansi.push_back(j + 1);
            ansj.push_back(i);
            int tmp1 = P[j];
            int tmp2 = P[j + 1];
            for (int k = j - 1; k >= i; k--) P[k + 2] = P[k];
            P[i] = tmp1;
            P[i + 1] = tmp2;
            i++;
          }
          break;
        }
      }
    }
    // debug(P);
    int flag = 1;
    rep(j, N) if (P[j] != j + 1) flag = 0;

    // debug(P, ansi, ansj);
    assert(flag);

    if (flag && ansi.size() <= 2000) {
      out("Yes");
      out(ansi.size());
      rep(j, ansi.size()) cout << ansi[j] << " " << ansj[j] << endl;
    } else {
      out("No");
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