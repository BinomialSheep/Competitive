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
using namespace chrono;

struct Solver {
  void solve() {
    INT(turn);

    rep(ti, turn) {
      /* input */
      STR(S, X, Y);

      auto startClock = system_clock::now();
      const static double END_TIME = 0.9;  // 終了時間（秒）
      double time = 0.0;                   // 経過時間（秒）

      // 圧縮
      while (X.size() && Y.size()) {
        if (X.back() != Y.back()) break;
        X.pop_back(), Y.pop_back();
      }
      reverse(all(X));
      reverse(all(Y));
      while (X.size() && Y.size()) {
        if (X.back() != Y.back()) break;
        X.pop_back(), Y.pop_back();
      }
      reverse(all(X));
      reverse(all(Y));

      /* solve */
      auto getTlen = [&]() -> ll {
        ll xt = 0, yt = 0;
        for (auto c : X)
          if (c == '1') xt++;
        for (auto c : Y)
          if (c == '1') yt++;
        ll xs = (int)X.size() - xt;
        ll ys = (int)Y.size() - yt;
        ll xss = xs * (int)S.size();
        ll yss = ys * (int)S.size();
        if (xt == yt) {
          // 任意長の時は何とかなるのでよい
          return (xss == yss) ? 0 : -1;
        }
        yss -= xss;
        xt -= yt;
        if (yss % xt) return -1;
        return yss / xt;
      };

      ll slen = S.size();
      ll tlen = getTlen();
      debug(tlen);
      if (tlen == -1) {
        out("No");
        continue;
      }
      if (tlen == 0) {
        out("Yes");
        continue;
      }

      int xidx = 0, yidx = 0;
      char xnow = X[0], ynow = Y[0];
      int xidx2 = 0, yidx2 = 0;
      unordered_map<int, char> mp;
      int isYes = 1;

      while (true) {
        time = ((double)duration_cast<microseconds>(system_clock::now() -
                                                    startClock)
                    .count() *
                1e-6);
        if (time >= (END_TIME)) break;
        // debug(mp);
        xidx2++, yidx2++;
        if ((xnow == '0' && xidx2 == slen) || (xnow == '1' && xidx2 == tlen)) {
          xidx++;
          if (xidx == (int)X.size()) break;
          xnow = X[xidx];
          xidx2 = 0;
        }
        if ((ynow == '0' && yidx2 == slen) || (ynow == '1' && yidx2 == tlen)) {
          yidx++;
          if (yidx == (int)Y.size()) break;
          ynow = Y[yidx];
          yidx2 = 0;
        }
        if (xnow == '0' && ynow == '0') {
          if (S[xidx2] != S[yidx2]) {
            isYes = 0;
            break;
          }
        } else if (xnow == '1' && ynow == '0') {
          if (mp.count(xidx2) == 0) {
            mp[xidx2] = S[yidx2];
          } else if (mp[xidx2] != S[yidx2]) {
            isYes = 0;
            break;
          }
        } else if (xnow == '0' && ynow == '1') {
          if (mp.count(yidx2) == 0) {
            mp[yidx2] = S[xidx2];
          } else if (mp[yidx2] != S[xidx2]) {
            isYes = 0;
            break;
          }
        } else if (xnow == '1' && ynow == '1') {
          if (mp.count(xidx2) && mp.count(yidx2)) {
            if (mp[yidx2] != mp[xidx2]) {
              isYes = 0;
              break;
            }
          } else if (!mp.count(xidx2) && mp.count(yidx2)) {
            mp[xidx2] = mp[yidx2];
          } else if (mp.count(xidx2) && !mp.count(yidx2)) {
            mp[yidx2] = mp[xidx2];
          }
        }
      }
      // debug(mp);

      /* output */
      Yes(isYes);
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