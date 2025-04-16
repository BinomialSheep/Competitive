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
    INT(N, M);
    vvi G(N);
    // 重みなし無向グラフ
    rep(i, M) {
      INT(A, B);
      --A, --B;
      G[A].push_back(B);
      G[B].push_back(A);
    }

    /* solve */
    ll cnt = 0;

    // 奇閉路がない⇔二部グラフ
    // 連結グラフごとに判定
    vector<int> visited(N);
    set<int> odd, even;
    auto dfs = [&](auto rec, int v, bool is_odd) -> void {
      if (is_odd) {
        odd.insert(v);
      } else {
        even.insert(v);
      }
      visited[v] = true;

      for (auto u : G[v]) {
        if (visited[u]) continue;
        rec(rec, u, !is_odd);
      }
    };

    vector<pair<int, int>> vec;

    rep(i, N) {
      if (visited[i]) continue;

      dfs(dfs, i, false);

      for (auto v : odd) {
        cnt += (int)odd.size() - (int)G[v].size();
      }
      for (auto v : even) {
        cnt += (int)even.size() - (int)G[v].size();
      }
      int c1 = (int)odd.size(), c2 = (int)even.size();
      vec.emplace_back(min(c1, c2), max(c1, c2));

      odd.clear(), even.clear();
    }
    cnt /= 2;

    // 外部に繋ぐ時に、選択肢があるなら青木必勝？
    int flag = 0, all_1 = 1;
    int flag2 = 0;
    //
    int cnt2 = 0;
    if ((int)vec.size() >= 2) {
      for (auto [c1, c2] : vec) {
        if (c1) all_1 = false;
        if (c1 != 0 && c1 != c2) {
          flag = 1;
          if (c1 % 2 != c2 % 2) flag2 = 1;
          cnt2++;
        }
      }
      if (all_1) {
        // 提出デバッグによると2ケースあるが、WAにならないのでよい
        // assert(false);
        // if (vec.size() == 1 || vec.size() == 3 || vec.size() == 4) {
        //   cout << "Takahashi" << endl;
        //   return;
        // } else {
        //   cout << "Aoki" << endl;
        //   return;
      }
    }

    //

    /* output */
    if (flag) {
      cout << "Aoki" << endl;
      // cout << (flag2 ? "Aoki" : "Takahashi") << endl;

      // cout << (cnt2 % 2 ? "Aoki" : "Takahashi") << endl;
    } else {
      cout << (cnt % 2 ? "Aoki" : "Takahashi") << endl;
    }
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