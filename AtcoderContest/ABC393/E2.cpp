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
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

// 素数列挙：O(N loglogN)
// 素因数分解：O(N longN)
struct Eratosthenes {
  // 1-indexed
  vector<bool> isPrime;
  // 整数iを割り切る最小の素数
  vector<int> minfactor;

  //
  int size;

  // コンストラクタ
  Eratosthenes(int N) : isPrime(N + 1, true), minfactor(N + 1, -1), size(N) {
    isPrime[1] = false;
    minfactor[1] = 1;
    // ふるい
    for (int p = 2; p <= N; ++p) {
      // すでに合成数ならスキップ
      if (!isPrime[p]) continue;
      // pはpで割り切れる
      minfactor[p] = p;

      // p以外のpの倍数を合成数に
      for (int q = p * 2; q <= N; q += p) {
        isPrime[q] = false;
        // qはpで割り切れる旨を更新
        if (minfactor[q] == -1) minfactor[q] = p;
      }
    }
  }

  // 高速素因数分解 O(log N)
  vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> res;
    while (n > 1) {
      int p = minfactor[n];
      int exp = 0;
      // nで割れるだけ割る
      while (minfactor[n] == p) {
        n /= p;
        ++exp;
      }
      res.emplace_back(p, exp);
    }
    return res;
  }

  // 約数列挙：O(約数の個数個)。n <= 10^9の場合1344
  vector<int> divisors(int n) {
    vector<int> res({1});
    // nを素因数分解
    auto pf = factorize(n);
    // 約数列挙
    for (auto p : pf) {
      int s = (int)res.size();
      for (int i = 0; i < s; ++i) {
        int v = 1;
        for (int j = 0; j < p.second; ++j) {
          v *= p.first;
          res.push_back(res[i] * v);
        }
      }
    }
    return res;
  }
};

struct Solver {
  void solve() {
    /* input */
    INT(N, K);
    VEC(int, A, N);
    // Eratosthenes er(1000001);

    vi cnt(1e6 + 1);
    rep(i, N) cnt[A[i]]++;

    vi B(1e6 + 1);

    for (int i = 1; i <= 1e6; i++) {
      for (int a = i; a <= 1e6; a += i) {
        B[i] += cnt[a];
      }
    }

    vi mp(1e6 + 1);
    for (int i = 1; i <= 1e6; i++) {
      if (B[i] >= K) {
        for (int a = i; a <= 1e6; a += i) {
          mp[a] = i;
        }
      }
    }
    vi ans(N);
    rep(i, N) ans[i] = mp[A[i]];

    // vvi cnt(1e6 + 1);

    /* solve */
    // rep(i, N) {
    //   vi vec = er.divisors(A[i]);
    //   // debug(A[i], vec);

    //   // for (auto v : vec) cnt[v]++;
    //   for (auto v : vec) {
    //     cnt[v].push_back(i);
    //   }
    // }
    // vi ans(N);

    // rep(i, cnt.size()) {
    //   if (cnt[i].size() >= K) {
    //     for (auto v : cnt[i]) ans[v] = i;
    //   }
    // }

    // rep(i, N) {
    //   vi vec = er.divisors(A[i]);
    //   sort(vec.rbegin(), vec.rend());
    //   for (auto v : vec) {
    //     if (cnt[v] >= K) {
    //       ans[i] = v;
    //       break;
    //     }
    //   }
    // }

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