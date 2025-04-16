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
// #include "app.hpp"

vector<long> create_solution(long step, long n, long m, long q,
                             vector<long> query1, vector<long> query2,
                             vector<long> query3) {
  vector<long> ans;

  map<int, vector<int>> bs;
  map<pair<int, int>, vector<int>> mp;
  map<int, int> inv;
  map<int, vector<pair<int, long>>> sum;
  // 先読み
  rep(qi, q) {
    if (query3[qi] == -1) {
      inv[qi] = (int)ans.size();
      ans.push_back(0);
      int a = query1[qi];
      bs[a].push_back(qi);
    } else {
      int x = query1[qi], y = query2[qi];
      long z = query3[qi];
      long z2 = 0;
      if (mp[make_pair(x, y)].size() != 0) {
        z2 = query3[mp[make_pair(x, y)].back()];
      }

      mp[make_pair(x, y)].push_back(qi);

      if (sum[x].size() == 0) {
        sum[x].emplace_back(qi, z);
      } else {
        long last = sum[x].back().second;
        sum[x].emplace_back(qi, z + last);
        query3[qi] += z2;
      }
    }
  }
  // debug(bs, mp, inv, sum);
  // debug(query1[346], query2[346], query3[346], inv[346]);
  // for (auto [p, vec] : mp)
  //   if (p.second == 97) debug(p, vec);

  //
  for (auto [pr, qis] : mp) {
    auto [x, y] = pr;
    for (int i = 0; i < (int)qis.size(); i++) {
      auto qi = qis[i];
      auto it = lower_bound(all(bs[y]), qi);
      // debug(qi, x, y);
      // ここはimos法で高速化可能
      while (true) {
        if (it == bs[y].end()) break;
        // 次より前なら終わる
        if (i + 1 != qis.size() && qis[i + 1] < *it) break;

        int a = query1[(*it)], b = query2[(*it)];
        assert(a == y);
        assert(query3[(*it)] == -1);

        // 合計を求める
        auto it2 = upper_bound(all(sum[x]), make_pair((*it), long(1e18)));
        --it2;
        int z = query3[qi];
        long total = (*it2).second;
        // if (inv[(*it)] == 170) debug(qi, x, y, a, b, z, total);

        if ((double)z * 100 / total + 0.001 >= b) ans[inv[(*it)]]++;

        it++;
      }
    }
    // debug(ans);
  }
  // 0だけ別で処理する
  set<long> area;
  rep(qi, q) {
    if (query3[qi] == -1) {
      int a = query1[qi], b = query2[qi];
      if (b == 0) ans[inv[qi]] = (long)area.size();
    } else {
      int x = query1[qi];
      area.insert(x);
    }
  }

  // for (auto v : ans) cout << v << endl;

  // debug(ans[170]);
  return ans;
}

int main() {
  INT(step);
  INT(N);
  INT(M);
  INT(Q);
  INT(Q2);
  VEC(long, vec1, Q);
  INT(Q3);
  VEC(long, vec2, Q);
  INT(Q4);
  VEC(long, vec3, Q);
  // debug(vec1, vec2, vec3);
  create_solution(step, N, M, Q, vec1, vec2, vec3);

  return 0;
}