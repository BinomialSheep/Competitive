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
#pragma endregion header
// #include <atcoder/all>
// using namespace atcoder;

ll nCk(ll ni, ll ki) {
  ll ret = 1;
  for (int i = ni; i >= ni - ki + 1; i--) ret *= i;
  for (int i = 1; i <= ki; i++) ret /= i;
  return ret;
}

struct Solver {
  void solve() {
    /* input */
    INT(N, A, B);
    VEC(ll, v, N);

    /* solve */

    sort(v.rbegin(), v.rend());
    ll sum = 0;
    rep(i, A) sum += v[i];
    double ans1 = (double)sum / A;
    // printf("%.10f\n", ans1);
    cout.precision(10);
    cout << fixed << ans1 << endl;

    debug(v);
    debug(v[A - 1]);

    int cnt1 = 0;
    rep(i, N) if (v[i] == sum / A) cnt1++;

    int cnt2 = 0;
    rep(i, A) if (v[i] == sum / A) cnt2++;

    vvl dp(51, vl(51));
    rep(i, 51) dp[i][0] = 1;
    for (int i = 1; i < 51; i++) {
      for (int j = 1; j < 51; j++) {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      }
    }
    // debug(dp);
    if (sum % A != 0) cnt1 = 0, cnt2 = 0;

    // 全部使われていたら変更の余地ない
    if (cnt1 == cnt2) {
      // 増やせないが最後だけ入れ替えられる場合もある
      int cnt3 = 0, cnt4 = 0;
      rep(i, N) if (v[i] == v[A - 1]) cnt3++;
      rep(i, A) if (v[i] == v[A - 1]) cnt4++;
      if (cnt3 == cnt4) {
        cout << 1 << endl;
        return;
      }
      assert(cnt3 > cnt4);
      debug(cnt3, cnt4);
      // debug(cnt3, cnt4);
      // cnt3個からcnt4個選ぶ（cnt3 C cnt4)
      cout << dp[cnt3][cnt4] << endl;
      return;
    }

    // cnt1の方が多い場合（少ないことはないが）、入れ替えか追加をできる
    ll ans = 0;
    for (int k = cnt2; k <= min(cnt1, cnt2 + (B - A)); k++) {
      ans += dp[cnt1][k];
    }
    /* output */
    cout << ans << endl;
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