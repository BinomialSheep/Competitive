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

bool sheep(int N, int M, int L, vi A, vi B, vi C) {
  /* input */

  /* solve */
  int TAKAHASHI = 0;
  int AOKI = 1;

  map<pair<multiset<int>, multiset<int>>, int> memo0;
  map<pair<multiset<int>, multiset<int>>, int> memo1;

  auto dfs = [&](auto rec, multiset<int> sta, multiset<int> stb,
                 multiset<int> stc, int teban) -> int {
    // debug(sta, stb, stc, teban);
    if (teban == TAKAHASHI && sta.empty()) {
      // 出せない。手番1の勝ち
      return AOKI;
    }
    if (teban == AOKI && stb.empty()) return TAKAHASHI;
    //
    auto key = make_pair(sta, stb);
    if (teban == 0 && memo0.count(key)) return memo0[key];
    if (teban == 1 && memo1.count(key)) return memo1[key];
    if (teban == TAKAHASHI) {
      // カードを出してカードを得る
      multiset<int> sta2 = sta;
      multiset<int> stc2 = stc;

      for (auto a : sta) {
        auto it = sta2.lower_bound(a);
        sta2.erase(it);
        stc2.insert(a);
        // 何も拾わない
        int res = rec(rec, sta2, stb, stc2, AOKI);
        if (res == TAKAHASHI) return memo0[key] = TAKAHASHI;

        // 拾う
        for (auto c : stc) {
          if (c < a) {
            it = stc2.lower_bound(c);
            stc2.erase(it);
            sta2.insert(c);
            res = rec(rec, sta2, stb, stc2, AOKI);
            if (res == TAKAHASHI) return memo0[key] = TAKAHASHI;
            it = sta2.lower_bound(c);
            sta2.erase(it);
            stc2.insert(c);
          }
        }
        sta2.insert(a);
        it = stc2.lower_bound(a);
        stc2.erase(it);
      }

      return memo0[key] = AOKI;
    } else {
      multiset<int> stb2 = stb;
      multiset<int> stc2 = stc;

      for (auto b : stb) {
        auto it = stb2.lower_bound(b);
        stb2.erase(it);
        stc2.insert(b);
        // 何も拾わない
        int res = rec(rec, sta, stb2, stc2, TAKAHASHI);
        if (res == AOKI) return memo1[key] = AOKI;
        // 拾う
        for (auto c : stc) {
          if (c < b) {
            it = stc2.lower_bound(c);
            stc2.erase(it);
            stb2.insert(c);
            res = rec(rec, sta, stb2, stc2, TAKAHASHI);
            if (res == AOKI) return memo1[key] = AOKI;
            it = stb2.lower_bound(c);
            stc2.insert(c);
            stb2.erase(it);
          }
        }
        stb2.insert(b);
        it = stc2.lower_bound(b);
        stc2.erase(it);
      }

      return memo1[key] = TAKAHASHI;
    }
  };

  multiset<int> sta;
  multiset<int> stb;
  multiset<int> stc;
  for (auto v : A) sta.insert(v);
  for (auto v : B) stb.insert(v);
  for (auto v : C) stc.insert(v);

  int res = dfs(dfs, sta, stb, stc, TAKAHASHI);

  /* output */
  if (res == TAKAHASHI) {
    out("Takahashi");
  } else {
    out("Aoki");
  }
  return res == TAKAHASHI;
}

bool hiro(int N, int M, int L, vector<int> A) {
  vector<int> C(N + M + L);
  int c = 0;
  for (int i = 0; i < N; i++) {
    C[i] = 1;
    c |= (1 << (2 * i));
  }
  for (int i = N; i < N + M; i++) {
    C[i] = 2;
    c |= (1 << (2 * i + 1));
  }
  map<int, int> m;
  auto dfs = [&](auto self, bool now) -> bool {
    if (m[c] == 1) return true;
    if (m[c] == 2) return false;
    if (now) {
      bool win = false;
      for (int i = 0; i < N + M + L; i++) {
        if (C[i] == 1) {
          for (int j = 0; j < N + M + L; j++) {
            if (C[j] == 0 && A[j] < A[i]) {
              C[i] = 0;
              C[j] = 1;
              c ^= (1 << (2 * i));
              c ^= (1 << (2 * j));
              if (self(self, false)) {
                win = true;
              }
              C[i] = 1;
              C[j] = 0;
              c ^= (1 << (2 * i));
              c ^= (1 << (2 * j));
            }
          }
          C[i] = 0;
          c ^= (1 << (2 * i));
          if (self(self, false)) {
            win = true;
          }
          C[i] = 1;
          c ^= (1 << (2 * i));
        }
      }
      m[c] = (win ? 1 : 2);
      return win;
    } else {
      bool win = true;
      for (int i = 0; i < N + M + L; i++) {
        if (C[i] == 2) {
          for (int j = 0; j < N + M + L; j++) {
            if (C[j] == 0 && A[j] < A[i]) {
              C[i] = 0;
              C[j] = 2;
              c ^= (1 << (2 * i + 1));
              c ^= (1 << (2 * j + 1));
              if (!self(self, true)) {
                win = false;
              }
              C[i] = 2;
              C[j] = 0;
              c ^= (1 << (2 * i + 1));
              c ^= (1 << (2 * j + 1));
            }
          }
          C[i] = 0;
          c ^= (1 << (2 * i + 1));
          if (!self(self, true)) {
            win = false;
          }
          C[i] = 2;
          c ^= (1 << (2 * i + 1));
        }
      }
      m[c] = (win ? 1 : 2);
      return win;
    }
  };
  int res = dfs(dfs, true);
  cout << (res ? "Takahashi" : "Aoki") << '\n';
  return res;
}

int main() {
  int ts = 1;
  rep(ti, ts) {
    INT(N, M, L);
    VEC(int, A, N);
    VEC(int, B, M);
    VEC(int, C, L);

    bool res1 = sheep(N, M, L, A, B, C);
    vi D;
    for (auto v : A) D.push_back(v);
    for (auto v : B) D.push_back(v);
    for (auto v : C) D.push_back(v);
    bool res2 = hiro(N, M, L, D);

    // assert(res1 == res2);
  }

  return 0;
}