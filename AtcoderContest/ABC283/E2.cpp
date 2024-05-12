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

struct Solver {
  void solve() {
    /* input */
    INT(H, W);
    vvi A(H, vi(W));
    rep(i, H) rep(j, W) cin >> A[i][j];

    /* solve */

    vvi dp(H, vi(2));
    dp[0][0] = 0;
    dp[0][1] = 1;
    vi vec0(W);
    vi vec1(W);
    rep(i, W - 1) {
      if (A[0][i] == A[0][i + 1]) {
        vec0[i] = 1;
        vec1[i] = 1;
        vec0[i + 1] = 1;
        vec1[i + 1] = 1;
      }
    }
    // debug(vec0, vec1);
    rep(i, H) {
      if (i == 0) continue;
      // i行目を反転しないで成立するか
      // i-1行目が反転していない場合
      int ok = 1;
      if (dp[i - 1][0] == INFTY) {
        ok = 0;
      } else {
        rep(j, W) {
          if (vec0[j]) continue;
          if (A[i - 1][j] == A[i][j]) continue;
          ok = 0;
          break;
        }
      }
      // i-1行目が反転している場合
      int ok2 = 1;
      if (dp[i - 1][1] == INFTY) {
        ok2 = 0;
      } else {
        rep(j, W) {
          if (vec1[j]) continue;
          if (A[i - 1][j] != A[i][j]) continue;
          ok2 = 0;
          break;
        }
      }

      rep(j, W) vec0[j] = 0;
      if (i == H - 1) {
        // 整合性チェック
        rep(j, W - 1) {
          if (A[i][j] == A[i][j + 1]) {
            vec0[j] = vec0[j + 1] = 1;
          }
        }
        rep(j, W) {
          if (vec0[j]) continue;
          if (A[i - 1][j] != A[i][j]) ok = 0;
          if (A[i - 1][j] == A[i][j]) ok2 = 0;
        }
      }
      if (!ok && !ok2) {
        dp[i][0] = INFTY;
      } else if (ok && (!ok2 || dp[i - 1][0] <= dp[i - 1][1])) {
        dp[i][0] = dp[i - 1][0];
        rep(j, W) {
          if (A[i - 1][j] == A[i][j]) vec0[j] = 1;
        }
        rep(j, W - 1) {
          if (A[i][j] == A[i][j + 1]) {
            vec0[j] = 1;
            vec0[j + 1] = 1;
          }
        }
      } else {
        dp[i][0] = dp[i - 1][1];
        rep(j, W) {
          if (A[i - 1][j] != A[i][j]) vec0[j] = 1;
        }
        rep(j, W - 1) {
          if (A[i][j] == A[i][j + 1]) {
            vec0[j] = 1;
            vec0[j + 1] = 1;
          }
        }
      }

      // i行目を反転して成立するか
      // i-1行目が反転していない場合
      ok = 1;
      if (dp[i - 1][0] == INFTY) {
        ok = 0;
      } else {
        rep(j, W) {
          if (vec0[j]) continue;
          if (A[i - 1][j] != A[i][j]) continue;
          ok = 0;
          break;
        }
      }
      // i-1行目が反転している場合
      ok2 = 1;
      if (dp[i - 1][1] == INFTY) {
        ok2 = 0;
      } else {
        rep(j, W) {
          if (vec1[j]) continue;
          if (A[i - 1][j] == A[i][j]) continue;
          ok2 = 0;
          break;
        }
      }
      rep(j, W) vec1[j] = 0;
      if (i == H - 1) {
        // 整合性チェック
        rep(j, W - 1) {
          if (A[i][j] == A[i][j + 1]) {
            vec1[j] = 1;
            vec1[j + 1] = 1;
          }
        }
        rep(j, W) {
          if (vec1[j]) continue;
          if (A[i - 1][j] == A[i][j]) ok = 0;
          if (A[i - 1][j] != A[i][j]) ok2 = 0;
        }
      }
      if (!ok && !ok2) {
        dp[i][1] = INFTY;
      } else if (ok && (!ok2 || dp[i - 1][0] <= dp[i - 1][1])) {
        dp[i][1] = dp[i - 1][0] + 1;
        rep(j, W) {
          if (A[i - 1][j] != A[i][j]) vec1[j] = 1;
        }
        rep(j, W - 1) {
          if (A[i][j] == A[i][j + 1]) {
            vec1[j] = 1;
            vec1[j + 1] = 1;
          }
        }
      } else {
        dp[i][1] = dp[i - 1][1] + 1;
        rep(j, W) {
          if (A[i - 1][j] == A[i][j]) vec1[j] = 1;
        }
        rep(j, W - 1) {
          if (A[i][j] == A[i][j + 1]) {
            vec1[j] = vec1[j + 1] = 1;
          }
        }
      }
    }

    debug(dp);

    /* output */
    int ans = min(dp[H - 1][0], dp[H - 1][1]);
    cout << (ans == INFTY ? -1 : ans) << endl;
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