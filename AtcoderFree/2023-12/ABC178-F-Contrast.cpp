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
    VEC(int, B, N);

    /* solve */
    map<int, int> mp, mpA, mpB;
    rep(i, N) mp[A[i]]++, mp[B[i]]++;
    rep(i, N) mpA[A[i]]++, mpB[B[i]]++;

    deque<pair<int, int>> vec;
    for (auto [k, v] : mp) vec.emplace_back(v, k);
    sort(vec.rbegin(), vec.rend());
    if (vec[0].first > N) {
      out("No");
      return;
    }
    out("Yes");

    deque<int> dqA, dqB;

    priority_queue<pair<int, int>> pq;
    deque<pair<int, int>> q;
    rep(i, vec.size()) {
      int tmp = vec[i].second;
      if (mpA.count(tmp) && mpB.count(tmp)) {
        pq.emplace(vec[i].first, tmp);
      } else {
        q.emplace_back(vec[i].first, tmp);
      }
    }

    vector<pair<int, int>> ps;

    while (pq.size() > 1) {
      auto p1 = pq.top();
      pq.pop();
      auto p2 = pq.top();
      pq.pop();

      ps.emplace_back(p1.second, p2.second);
      mpA[p1.second]--;
      mpB[p2.second]--;

      if (mpA[p1.second] && mpB[p1.second]) {
        pq.emplace(p1.first - 1, p1.second);
      } else if (p1.first >= 2) {
        q.emplace_back(p1.first - 1, p1.second);
      }
      if (mpA[p2.second] && mpB[p2.second]) {
        pq.emplace(p2.first - 1, p2.second);
      } else if (p2.first >= 2) {
        q.emplace_back(p2.first - 1, p2.second);
      }
    }
    if (pq.size()) q.push_front(pq.top());

    // debug(q);
    // debug(mpA, mpB);
    // debug(ps);

    if (dqA.size()) debug(dqA.size(), dqA.front(), dqA.back());
    if (dqB.size()) debug(dqB.size(), dqB.front(), dqB.back());

    while (q.size()) {
      auto p = q.front();
      q.pop_front();
      rep(i, mpA[p.second]) dqA.push_back(p.second);
      rep(i, mpB[p.second]) dqB.push_back(p.second);

      // debug(dqA, dqB);
      while (true) {
        if (dqA.empty() || dqB.empty()) break;
        if (dqA.front() != dqB.front()) {
          ps.emplace_back(dqA.front(), dqB.front());
          dqA.pop_front(), dqB.pop_front();
        } else if (dqA.front() != dqB.back()) {
          ps.emplace_back(dqA.front(), dqB.back());
          dqA.pop_front(), dqB.pop_back();
        } else if (dqB.front() != dqA.back()) {
          ps.emplace_back(dqA.back(), dqB.front());
          dqA.pop_back(), dqB.pop_front();
        } else {
          // 同じ値しか入っていない
          break;
        }
      }
    }
    debug(ps);

    vi ans(N);
    map<int, vector<int>> mp2;
    for (auto [a, b] : ps) mp2[a].push_back(b);
    // debug(mp2);
    rep(i, N) {
      ans[i] = mp2[A[i]].back();
      mp2[A[i]].pop_back();
    } /* output */
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