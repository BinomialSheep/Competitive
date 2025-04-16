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
    INT(N);
    VEC(int, A, N);

    /* solve */

    auto f = [&](vector<char> S) {
      for (int i = 3; i < N; i++) {
        if (S[i] != 'Z') {
          if (A[i] == 0) {
            if (S[i] == 'C') return false;
            if (S[i] == 'R') {
              // CRA
              if (S[i - 1] == 'C') {
                if (S[i + 1] == 'Z' || S[i + 1] == 'A') {
                  S[i + 1] = 'A';
                } else {
                  return false;
                }
              } else if (S[i - 1] == 'A') {
                // ARC
                if (S[i + 1] == 'Z' || S[i + 1] == 'C') {
                  S[i + 1] = 'C';
                } else {
                  return false;
                }
                S[i + 1] = 'C';
              } else {
                return false;
              }
            } else if (S[i] == 'A') {
              // CRA
              if (S[i - 1] == 'R' && S[i - 2] == 'C') {
                // OK
              } else {
                // ARCにしたい
                if (S[i + 1] == 'Z' || S[i + 1] == 'R') {
                  S[i + 1] = 'R';
                } else {
                  return false;
                }
                if (S[i + 2] == 'Z' || S[i + 2] == 'C') {
                  S[i + 2] = 'C';
                } else {
                  return false;
                }
              }
            } else {
              assert(false);
            }
          }
        } else {
          if (A[i] == 1) {
            // Cにしておくのが多分リーズナブルだが、Rにしたいこともあるか……
            S[i] = 'C';
          } else {
            if (S[i - 1] == 'A') {
              // ARCにするか、AARCになる
              if (S[i + 1] == 'Z' || S[i + 1] == 'C') {
                // リーズナブルに
                S[i] = 'R', S[i + 1] = 'C';
              } else if (S[i + 1] == 'R') {
                if (S[i + 2] == 'Z' || S[i + 2] == 'C') {
                  S[i] = 'A', S[i + 2] = 'C';
                }
              } else {
                return false;
              }
            } else if (S[i - 1] == 'R') {
              // CRA
              if (S[i - 2] == 'C') {
                S[i] = 'A';
              } else {
                // ARC
                S[i] = 'A';
                if (S[i + 1] == 'R' || S[i + 1] == 'Z') {
                  S[i + 1] = 'R';
                } else {
                  return false;
                }
                if (S[i + 2] == 'C' || S[i + 2] == 'Z') {
                  S[i + 2] = 'C';
                } else {
                  return false;
                }
              }
            } else {
              // CRAまたはCARC
              if (S[i + 1] == 'Z' || S[i + 1] == 'A') {
                S[i] = 'R', S[i + 1] = 'A';
              } else if (S[i + 1] == 'R' &&
                         (S[i + 2] == 'C' || S[i + 2] == 'Z')) {
                S[i] = 'A', S[i + 1] = 'R', S[i + 2] = 'C';
              } else {
                return false;
              }
            }
          }
        }
      }
      // debug(S);

      rep(i, N) {
        if (A[i] == 1) continue;
        int p2 = (N + i - 2) % N;
        int p1 = (N + i - 1) % N;
        int n1 = (i + 1) % N;
        int n2 = (i + 2) % N;
        int ok = 0;
        // debug(p2, p1, i, n1, n2);
        if (S[i] == 'A' && S[n1] == 'R' && S[n2] == 'C') ok = 1;
        if (S[p1] == 'A' && S[i] == 'R' && S[n1] == 'C') ok = 1;
        if (S[p2] == 'C' && S[p1] == 'R' && S[i] == 'A') ok = 1;
        if (S[p1] == 'C' && S[i] == 'R' && S[n1] == 'A') ok = 1;
        if (!ok) return false;
      }

      debug(S);

      return true;
    };

    string hoyo = "ARC";
    vector<char> S(N + 2, 'Z');
    int ans = 0;
    rep(i, 3) rep(j, 3) rep(k, 3) {
      S[0] = hoyo[i], S[1] = hoyo[j], S[2] = hoyo[k];
      S[N] = S[0], S[N + 1] = S[1];
      rep(a, 3) if (S[a] == 'C' && A[a] == 0) continue;

      bool res = f(S);
      if (res) ans = 1;
    }

    /* output */
    Yes(ans);
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