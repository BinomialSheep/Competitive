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
    INT(N, K);
    STR(S);

    /* solve */
    int cx = 0, cy = 0;
    for(auto c : S) {
      if(c == 'X') cx++;
      else cy++;
    }
    //
    deque<pair<char, int>> dq;
    for(auto c : S) {
      if(dq.empty() || dq.back().first != c) {
        dq.emplace_back(c, 1);
      } else {
        dq[dq.size()-1].second++;
      }
    }
    debug(dq, cx, cy);
    //
    if(K >= cx) {
      // yを降順にxにするゲーム
      K -= cx;
      rep(i, N) if(S[i] == 'X') S[i] = 'Y';
      set<int> st;
      for(auto [c, v] : dq) {
        if(c == 'Y') st.insert(v);
      }
      vi vt;
      for(auto v : st) vt.push_back(v);
      reverse(all(vt));
      //
      if(K > 0 && dq[0].first == 'Y') {
        // できるだけ詰めておく
        int v2 = dq[0].second;
        rep(i, v2) {
          if(K == 0) break;
          int j = i;
          assert(S[j] == 'Y');
          S[j] = 'X';
          K--;
        }
      }
      if(K > 0 && dq[dq.size()-1].first == 'Y') {
        int v2 = dq.back().second;
        rep(i, v2) {
          if(K == 0) break;
          int j = N - 1- i;
          assert(S[j] == 'Y');
          S[j] = 'X';
          K--;
        }
      }
      for(auto v : vt) {
        int idx = 0;
        rep(i2, dq.size()) {
          auto c = dq[i2].first;
          auto v2 = dq[i2].second;
          if(i2 == 0 || i2 == dq.size() - 1) {
            idx += v2;
            continue;
          }
          if(c == 'Y' && v2 == v) {
            rep(i, v2) {
              if(K == 0) break;
              int j = idx+i;
              assert(S[j] == 'Y');
              S[j] = 'X';
              K--;
            }
          }
            idx += v2;
        } 
        if(K == 0) break;
      }



    } else {
      // xを昇順にyにするゲーム
      set<int> st;
      for(auto [c, v] : dq) {
        if(c == 'X') st.insert(v);
      }
      for(auto v : st) {
        int idx = 0;
        rep(i2, dq.size()) {
          auto c = dq[i2].first;
          auto v2 = dq[i2].second;
          if(i2 == 0 || i2 == dq.size() - 1) {
            idx += v2;
            continue;
          }
          if(c == 'X' && v2 == v) {
            rep(i, v2) {
              if(K == 0) break;
              int j = idx+i;
              debug(S, i, idx, j);

              assert(S[j] == 'X');
              S[j] = 'Y';
              K--;
            }
          }
            idx += v2;
        } 
        if(K == 0) break;
      }
      if(K > 0 && dq[0].first == 'X') {
        // 先頭のXだけは後ろから詰める。面倒！
        int v2 = dq[0].second;
        rep(i, v2) {
          if(K == 0) break;
          int j = v2-1-i;
          assert(S[j] == 'X');
          S[j] = 'Y';
          K--;
        }
      }
      if(K > 0) {
        int v2 = dq.back().second;
        int idx = N - v2 - 1;
        rep(i, v2) {
          if(K == 0) break;
          int j = idx + i;
          assert(S[j] == 'X');
          S[j] = 'Y';
          K--;
        }
      }

    } 
      debug(S);

    int ans = 0;
    rep(i, N-1) if(S[i] == 'Y' && S[i+1] == 'Y') ans++;
    out(ans); 


  


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