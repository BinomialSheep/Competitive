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
using namespace atcoder;

struct Solver {
  void solve() {
    /* input */
    using mint = modint998244353;
    // INT(N);
    // VEC(int, A, N);
    // rep(i, N) A[i]--;
    int N = 5;
    vi A(N);
    random_device rng;
    rep(i, N) A[i] = rng() % N;
    debug(A);

    /* solve */
    auto naive = [&]() {
      mint ret = 0;

      map<vi, int> mp;

      auto f = [&](vi P) {
        vi B(N);
        iota(all(B), 0);

        while (true) {
          int j = -1;

          rep(i, N) {
            if (B[i] < P[B[i]]) {
              j = i;
              break;
            }
          }

          if (j == -1) break;

          B[j] = P[B[j]];
        }

        mp[B]++;
        // debug(P, B, B == A);
        // if (B == A) debug(P);
        return B == A;
      };

      vi perm(N);
      iota(all(perm), 0);
      do {
        //
        if (f(perm)) ret++;

      } while (next_permutation(all(perm)));

      // debug(mp);

      return ret;
    };

    // out(naive().val());

    auto smart = [&]() {
      set<int> st;
      rep(i, N) st.insert(i);
      map<int, int> mp;
      for (int i = N - 1; i >= 0; i--) {
        if (A[i] < i) {
          return 0;
        }
        if (A[i] == i) continue;
        int v = -1;
        if (mp.count(A[i]) == 0) {
          v = A[i];
          mp[A[i]] = i;
        } else {
          v = mp[A[i]];
          mp[A[i]] = i;
        }
        // debug(v, mp[A[i]]);

        if (st.count(v) == 0) {
          return 0;
        }
        st.erase(v);
      }
      // debug(st);

      vector<int> vec;
      for (auto v : st) vec.push_back(v);

      int cnt = 0;
      mint ans = 1;
      rep(i, N) {
        if (A[i] != i) continue;
        if (vec.size() == 0) {
          return 0;
        }
        auto it = upper_bound(all(vec), i);
        // if (it == vec.begin()) {
        //   out(0);
        //   return;
        // }
        // --it;
        // debug(i, *it);
        // if (*it < i) {
        //   out(0);
        //   return;
        // }
        int d = distance(vec.begin(), it);
        ans *= (d - cnt);
        cnt++;
      }

      return (int)ans.val();
    };

    mint ans = smart();

    /* output */
    if (ans.val() != naive().val()) {
      debug(ans.val(), naive().val());
    }
    out(ans.val());
  }
};

int main() {
  int ts = 100;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}