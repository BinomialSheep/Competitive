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
    INT(N, M);
    vvi OB(M, vi(N / M));
    rep(i, M) rep(j, N / M) cin >> OB[i][j];
    vvi B(M, vi(N / M));

    // debug(B);
    /*  */

    /* functions */
    // 山iの下からj個目を、山i2に移す
    auto operation1 = [&](int i, int j, int i2) {
      for (int k = j; k < (int)B[i].size(); k++) B[i2].push_back(B[i][k]);
      while ((int)B[i].size() > j) B[i].pop_back();
    };
    //
    auto operation2 = [&](int i) { B[i].pop_back(); };

    auto topCheck = [&](vpii& ans, int& now) {
      // 操作2ができるならできるだけやる
      int flag = 1;
      while (flag) {
        flag = 0;
        rep(j, M) {
          if (B[j].size() && B[j].back() == now) {
            flag = 1;
            ans.emplace_back(now, 0);
            now++;
            operation2(j);
          }
        }
      }
    };

    vpii bestAns;
    int bestScore = 10000000;

    /* solve */
    auto sol = [&](vi& A, vi& C) {
      vpii ans;
      int V = 0;
      int now = 1;

      // C[0]列目に入れる前にできるならやる
      topCheck(ans, now);

      // 最初はC[0]列目に入れる
      for (int ci = 1; ci < M; ci++) {
        int i = C[ci];
        if (B[i].empty()) continue;
        while (B[i].size()) {
          int flag = 0;
          for (int j = (int)B[i].size() - 1; j >= 0; j--) {
            if (B[i][j] == now) {
              flag = 1;
              // 操作1をしてから
              if (j != (int)B[i].size() - 1) {
                V += (int)B[i].size() + 1 - (j + 1);
                ans.emplace_back(B[i][j + 1], C[0] + 1);
                operation1(i, j + 1, C[0]);
              }
              // 操作2をする
              now++;
              ans.emplace_back(B[i][j], 0);
              operation2(i);
              break;
            }
          }
          if (flag) continue;
          // nowがなければ全部置く
          V += (int)B[i].size() + 1;
          ans.emplace_back(B[i][0], C[0] + 1);
          operation1(i, 0, C[0]);
        }
      }
      // debug(V, B);
      // 上から順に処理
      while (B[C[0]].size()) {
        topCheck(ans, now);
        if (B[C[0]].empty()) break;
        rep(i, A.size()) {
          if (B[C[0]].back() <= A[i]) {
            // 複数個やる
            int j = (int)B[C[0]].size() - 1;
            while (j >= 1 && B[C[0]][j] < B[C[0]][j - 1] &&
                   A[i - 1] < B[C[0]][j - 1] && B[C[0]][j - 1] <= A[i])
              j--;
            ans.emplace_back(B[C[0]][j], C[i] + 1);
            V += (int)B[C[0]].size() + 1 - j;
            operation1(C[0], j, C[i]);
            break;
          }
        }
      }
      // debug(V, B, ans);
      // debug(B[C[1]].size());
      // それぞれやる
      rep(ci, M) {
        int i = C[ci];
        while (B[i].size()) {
          // 操作2ができるならできるだけやる
          topCheck(ans, now);
          if (B[i].empty()) break;
          // 操作1を何個目からやるか
          int j = (int)B[i].size() - 1;
          while (j >= 1 && B[i][j] < B[i][j - 1]) j--;
          // どこに置くか
          for (int i2 = 0; i2 < M; i2++) {
            if (i2 != i && (B[i2].empty() || B[i2].back() > B[i][j])) {
              ans.emplace_back(B[i][j], i2 + 1);
              V += (int)B[i].size() + 1 - j;
              operation1(i, j, i2);
              // debug(i, i2, j, B[i][j]);
              break;
            }
            if (i2 == M - 1 || (i == M - 1 && i2 == M - 2)) {
              // debug("詰みなので最後まで掘る");
              // debug(now, B);
              j = 0;
              for (; j < (int)B[i].size(); j++) {
                if (B[i][j] == now) {
                  int tmp = (int)B[C[0]].size();
                  V += (int)B[i].size() + 1 - (j + 1);
                  operation1(i, j + 1, C[0]);
                  ans.emplace_back(B[i][j + 1], C[0] + 1);
                  ans.emplace_back(now, 0);
                  now++;
                  operation2(i);
                  ans.emplace_back(B[C[0]][tmp], i + 1);
                  V += (int)B[C[0]].size() + 1 - tmp;
                  operation1(C[0], tmp, i);
                  break;
                }
              }
              // assert(false);
            }
          }
        }
      }
      assert(now == 201);
      rep(i, M) assert(B[i].size() == 0);
      if (chmin(bestScore, V)) swap(bestAns, ans);
    };
    vi C;
    {
      vi D(N);
      rep(i, M) rep(j, OB[i].size()) D[OB[i][j] - 1] = i;
      set<int> st;
      rep(i, N) if (st.count(D[i]) == 0) {
        C.push_back(D[i]);
        st.insert(D[i]);
      }
      reverse(all(C));
      rotate(C.begin(), C.begin(), C.end());
    }

    rep(i0, 12) rep(i1, 4) rep(i2, 4) rep(i3, 4) rep(i4, 4) rep(i5, 4)
        rep(i6, 4) rep(i7, 4) {
      vi A(10);
      A[1] = A[0] + 15 + i0;
      A[2] = A[1] + 20 + i1;
      A[3] = A[2] + 20 + i2;
      A[4] = A[3] + 20 + i3;
      A[5] = A[4] + 20 + i4;
      A[6] = A[5] + 20 + i5;
      A[7] = A[6] + 20 + i6;
      A[8] = A[7] + 20 + i7;
      A[9] = 200;
      if (A[9] - A[8] <= 15) continue;
      B = OB;
      sol(A, C);
    }

    out(bestAns);
    cerr << bestScore << endl;

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