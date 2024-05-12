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
    STR(S1, S2, S3);

    set<char> st;
    set<char> st2;
    for (auto c : S1) st.insert(c), st2.insert(c);
    for (auto c : S2) st.insert(c), st2.insert(c);
    for (auto c : S3) st.insert(c);
    if (st.size() > 10) {
      cout << "UNSOLVABLE" << endl;
      return;
    }

    /* solve */
    auto isOK = [&](unordered_map<char, char>& mp,
                    unordered_map<char, bool>& used) {
      string t1 = S1, t2 = S2, t3 = S3;
      // debug(mp);
      rep(i, t1.size()) t1[i] = mp[t1[i]];
      rep(i, t2.size()) t2[i] = mp[t2[i]];

      string sum = to_string(stoll(t1) + stoll(t2));

      if (sum.size() != t3.size()) return false;

      unordered_map<char, char> mp2;

      rep(i, t3.size()) {
        if (mp.count(t3[i])) {
          t3[i] = mp[t3[i]];
          continue;
        }
        if (mp2.count(t3[i])) {
          t3[i] = mp2[t3[i]];
          continue;
        }
        char c2 = char('0' + sum[i]);
        if (used[c2]) return false;
        t3[i] = sum[i];
        mp2[t3[i]] = c2;
      }
      if (t3 == sum) {
        cout << t1 << " " << t2 << " " << t3 << endl;
        return true;
      }
      return false;
    };

    auto can0 = [&](char c) { return S1[0] != c && S2[0] != c && S1[0] != c; };

    auto dfs = [&](auto f, unordered_map<char, char>& mp,
                   unordered_map<char, bool>& used) -> bool {
      for (auto c : S1) {
        if (mp.count(c)) continue;
        rep(i, 10) {
          if (i == 0 && !can0(c)) continue;
          char c2 = char('0' + i);
          if (used[c2]) continue;
          mp[c] = c2;
          used[c2] = true;
          if (f(f, mp, used)) return true;
          mp.erase(c);
          used[c2] = false;
        }
      }
      for (auto c : S2) {
        if (mp.count(c)) continue;
        rep(i, 10) {
          if (i == 0 && !can0(c)) continue;
          char c2 = char('0' + i);
          if (used[c2]) continue;
          mp[c] = c2;
          used[c2] = true;
          if (f(f, mp, used)) return true;
          mp.erase(c);
          used[c2] = false;
        }
      }
      if (mp.size() != st2.size()) return false;
      return isOK(mp, used);
    };

    unordered_map<char, char> tmp;
    unordered_map<char, bool> tmp2;
    if (dfs(dfs, tmp, tmp2)) return;
    cout << "UNSOLVABLE" << endl;

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