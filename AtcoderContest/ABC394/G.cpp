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

class Query {
 public:
  int A;
  int B;
  int Y;
  int C;
  int D;
  int Z;
  Query(int a, int b, int y, int c, int d, int z)
      : A(a), B(b), Y(y), C(c), D(d), Z(z) {};
};

struct Solver {
  void solve() {
    /* input */
    INT(H, W);
    vvi F(H, vi(W));
    rep(i, H) rep(j, W) cin >> F[i][j];
    INT(Q);
    vector<Query> queryVec;
    rep(qi, Q) {
      INT(A, B, Y, C, D, Z);
      --A, --B, --C, --D;
      Query q(A, B, Y, C, D, Z);
      queryVec.push_back(q);
    }

    map<pair<int, int>, vector<int>> mpq;
    rep(qi, Q) {
      auto q = queryVec[qi];
      mpq[make_pair(q.A, q.B)].push_back(qi);
      mpq[make_pair(q.C, q.D)].push_back(qi);
    }
    debug(mpq);

    /* solve */
    map<int, vector<pair<int, int>>> mp;
    // マージしたタイミングlast_update[leader]を入れよう
    vector<int> last_update(H * W);
    rep(i, H) rep(j, W) mp[F[i][j]].emplace_back(i, j);

    // dsuする
    dsu uf(H * W);
    vi ans(Q, 1e9);

    vi dy = {-1, 1, 0, 0};
    vi dx = {0, 0, -1, 1};
    auto it = mp.end();
    --it;
    for (;; it--) {
      // debug(it->first);
      int h = it->first;

      auto f = [&](int y2, int x2) {
        for (auto qi : mpq[make_pair(y2, x2)]) {
          // debug(y, x, qi);
          Query q = queryVec[qi];
          int yy, xx;
          if (q.A == y2 && q.B == x2) {
            yy = q.C, xx = q.D;
          } else {
            yy = q.A, xx = q.B;
          }
          if (uf.same(y2 * H + x2, yy * H + xx)) {
            int hh = last_update[uf.leader(yy * H + xx)];
            int cost = 0, now = q.Y;
            if (q.Y > hh) {
              // hまで降りる
              cost = q.Y - hh;
              now = hh;
            }
            cost += abs(now - q.Z);
            debug(y2, x2, yy, xx, h, hh, cost);
            chmin(ans[qi], cost);
          }
        }
      };

      for (auto [y, x] : it->second) {
        f(y, x);
        rep(di, 4) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (0 <= y2 && y2 < H && 0 <= x2 && x2 < W) {
            f(y2, x2);
          }
        }
      }

      for (auto [y, x] : it->second) {
        rep(di, 4) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (0 <= y2 && y2 < H && 0 <= x2 && x2 < W) {
            if (F[y2][x2] >= h) {
              debug(h, y, x, y2, x2);
              uf.merge(y * H + x, y2 * H + x2);
              last_update[uf.leader(y * H + x)] = h;
            }
          }
        }
      }
      debug(h, uf.same(0, 6));

      for (auto [y, x] : it->second) {
        f(y, x);
        rep(di, 4) {
          int y2 = y + dy[di], x2 = x + dx[di];
          if (0 <= y2 && y2 < H && 0 <= x2 && x2 < W) {
            f(y2, x2);
          }
        }
      }

      if (it == mp.begin()) break;
    }

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