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

// 座標圧縮ライブラリ窃盗
// https://ei1333.github.io/luzhiled/snippets/other/compress.html
template <typename T>
struct Compress {
  vector<T> xs;
  Compress() = default;
  Compress(const vector<T>& vec) { add(vec); }
  Compress(const initializer_list<vector<T>>& vec) {
    for (auto& p : vec) add(p);
  }

  void add(const vector<T>& vec) {
    copy(begin(vec), end(vec), back_inserter(xs));
  }
  void add(const T& x) { xs.emplace_back(x); }

  void build() {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
  }

  vector<int> get(const vector<T>& vec) const {
    vector<int> ret;
    transform(begin(vec), end(vec), back_inserter(ret), [&](const T& x) {
      return lower_bound(begin(xs), end(xs), x) - begin(xs);
    });
    return ret;
  }

  int get(const T& x) const {
    return (int)(lower_bound(begin(xs), end(xs), x) - begin(xs));
  }

  int size() const { return (int)xs.size(); }

  // inverted
  const T& operator[](int k) const { return xs[k]; }
};

struct Solver {
  void solve() {
    /* input */
    INT(W, H);
    INT(N);
    vi X1(N), Y1(N), X2(N), Y2(N);
    rep(i, N) { cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i]; }
    vi A;
    vi A2;
    A.push_back(0);
    A2.push_back(0);
    rep(i, N) {
      A.push_back(X1[i]);
      A.push_back(X2[i]);
      A.push_back(X2[i] + 1);
      A2.push_back(Y1[i]);
      A2.push_back(Y2[i]);
      A2.push_back(Y2[i] + 1);
    }
    Compress c1(A);
    c1.build();
    Compress c2(A2);
    c2.build();
    /* solve */
    vvi vec(c2.get(H) + 1, vi(c1.get(W) + 1));

    rep(i, N) {
      int x1 = c1.get(X1[i]);
      int x2 = c1.get(X2[i]);
      int y1 = c2.get(Y1[i]);
      int y2 = c2.get(Y2[i]);
      vec[y1][x1]++;
      vec[y1][x2]--;
      vec[y2][x1]--;
      vec[y2][x2]++;
    }
    rep(i, c2.get(H) + 1) rep(j, c1.get(W) + 1) {
      if (j) vec[i][j] += vec[i][j - 1];
    }
    rep(i, c2.get(H) + 1) rep(j, c1.get(W) + 1) {
      if (i) vec[i][j] += vec[i - 1][j];
    }
    rep(i, c2.get(H) + 1) rep(j, c1.get(W) + 1) if (vec[i][j]) vec[i][j] = -1;
    //
    debug(vec);

    vi dy = {1, -1, 0, 0};
    vi dx = {0, 0, 1, -1};

    auto bfs = [&](int y, int x, int color) {
      queue<pair<int, int>> q;
      q.emplace(y, x);
      vec[y][x] = color;
      while (q.size()) {
        auto [yy, xx] = q.front();
        q.pop();

        rep(i, 4) {
          int yyy = yy + dy[i];
          int xxx = xx + dx[i];
          if (yyy < 0 || yyy >= c2.get(H) || xxx < 0 || xxx >= c1.get(W))
            continue;
          if (vec[yyy][xxx] == 0) {
            vec[yyy][xxx] = color;
            q.emplace(yyy, xxx);
          }
        }
      }
    };

    int ans = 0;
    rep(i, c2.get(H)) rep(j, c1.get(W)) {
      if (vec[i][j] == 0) {
        bfs(i, j, ++ans);
      }
    }
    out(ans);

    // debug(vec);

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