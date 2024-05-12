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
    LL(N);
    string S = to_string(N);
    S = string(15 - (int)S.size(), '0') + S;
    debug(S);

    /* solve */
    ll ans = 0;
    // 下から
    for (int i = 1; i <= 126; i++) {
      // for (int i = 1; i <= 1; i++) {
      // 今の桁,  今の桁和, 今の余り,以下になっているか
      vector dp(16, vector(i + 1, vector(i, vector<int>(2))));
      // ll dp[16][i][i + 1][2];
      dp[0][0][0][1] = 1;

      for (int keta = 1; keta <= 15; keta++) {
        // keta桁目が0-9の場合
        for (int k = 0; k < 9; k++) {
          int tmp = (int)S.size() - keta;
          int tmp2 = (int)(S[tmp] - '0');
          // debug(keta, tmp, S[tmp]);
          // if (S[(int)S.size() - tmp] > k) break;
          for (int amari = 0; amari < i; amari++) {
            for (int ketawa = 0; ketawa <= i; ketawa++) {
              //
              int newKetawa = ketawa + k;
              // debug(ketawa, k, newKetawa, i);
              if (newKetawa > i) break;

              int newAmari = (amari + k) % i;
              // debug(i, keta, k, amari, ketawa, newKetawa, newAmari);
              //

              if (tmp2 == k) {
                // 下次第
                dp[keta][newKetawa][newAmari][1] +=
                    dp[keta - 1][ketawa][amari][1];
                dp[keta][newKetawa][newAmari][0] +=
                    dp[keta - 1][ketawa][amari][0];
              } else if (tmp2 > k) {
                // 以下
                dp[keta][newKetawa][newAmari][1] +=
                    dp[keta - 1][ketawa][amari][0];
                dp[keta][newKetawa][newAmari][1] +=
                    dp[keta - 1][ketawa][amari][1];
              } else {
                // 下がどうであれ超えている
                dp[keta][newKetawa][newAmari][0] +=
                    dp[keta - 1][ketawa][amari][0];
                dp[keta][newKetawa][newAmari][0] +=
                    dp[keta - 1][ketawa][amari][1];
              }
              // debug(tmp2, k, dp[keta][newKetawa][newAmari]);
            }
          }
        }
      }
      // debug(dp);
      ans += dp[15][i][0][1];
    }

    // auto stupid = [](ll N) {
    //   string s = to_string(N);

    //   ll ketawa = 0;
    //   for (auto c : s) ketawa += c - '0';
    //   return N % ketawa == 0;
    // };

    // int ans = 0;

    // for (ll i = 1; i <= N; i++) {
    //   if (stupid(i)) {
    //     ans++;
    //     debug(i);
    //   }
    // }
    // out(ans);

    /* output */
    out(ans);
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