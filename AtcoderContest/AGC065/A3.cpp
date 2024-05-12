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
    INT(N, K);
    VEC(ll, A, N);
    rep(i, N) A[i] %= K;

    vl origA = A;

    /* solve */

    set<pair<ll, int>> st;
    rep(i, N) st.emplace(A[i] % K, i);
    auto mod = [&](ll a, ll b) -> ll { return ((b - a) % K + K) % K; };

    rep(i, N) rep(j, N) if (i != j) debug(i, j, mod(A[i], A[j]));

    // auto f = [&](ll a, ll b) { return max(mod(a, b), mod(b, a)); };

    vi prev(N);
    vi next(N);
    dsu uf(N);

    priority_queue<pair<ll, pair<int, int>>> pq;
    auto g = [&](pair<ll, int> p) {
      ll a = p.first;
      pair<ll, int> bp;
      int flag = false;
      if (a > (*st.begin()).first) {
        auto it = st.lower_bound(make_pair(a, -1));
        --it;
        while (true) {
          if ((*it).second != p.second && !uf.same(p.second, (*it).second)) {
            bp = *it;
            flag = true;
            break;
          }
          if (it == st.begin()) break;
          --it;
        }
      }
      if (!flag) {
        auto it = st.end();
        --it;
        while (true) {
          if ((*it).second != p.second && !uf.same(p.second, (*it).second)) {
            bp = *it;
            flag = true;
            break;
          }
          if (it == st.begin()) break;
          --it;
        }
      }
      assert(flag);
      pq.emplace(mod(a, bp.first), make_pair(p.second, bp.second));
    };

    rep(i, N) { g(make_pair(A[i], i)); }
    debug(pq);

    ll ans = 0;
    int cnt = 0;
    while (pq.size() && cnt < N - 1) {
      // debug(pq);
      // debug(st);
      // debug(prev, next);
      auto [d, p] = pq.top();
      pq.pop();
      if (next[p.first] == 0 && prev[p.second] == 0 &&
          !uf.same(p.first, p.second)) {
        next[p.first]++, prev[p.second]++;
        uf.merge(p.first, p.second);
        ans += d;
        cnt++;
        st.erase(make_pair(A[p.second], p.second));
      } else if (next[p.first] == 0) {
        g(make_pair(A[p.first], p.first));
      }
    }

    out(ans);

    int pc = 0, nc = 0;
    rep(i, N) {
      assert(next[i] <= 1 && prev[i] <= 1);
      pc += prev[i], nc += next[i];
    }
    assert(pc == N - 1 && nc == N - 1);

    auto stupid = [&]() {
      ll ans2 = -1;
      vi besePerm;
      vi perm(N);
      iota(all(perm), 0);
      do {
        //
        ll now = 0;
        rep(i, N - 1) { now += ((A[perm[i + 1]] - A[perm[i]]) % K + K) % K; }
        // vl C(N);
        // rep(i, N) C[i] = A[perm[i]];
        // debug(C);
        // debug(now);
        if (chmax(ans2, now)) besePerm = perm;
      } while (next_permutation(all(perm)));

      vl B(N);
      rep(i, N) B[i] = A[besePerm[i]];
      debug(B);
      debug(ans2);
      assert(ans2 == ans);
    };
    stupid();

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