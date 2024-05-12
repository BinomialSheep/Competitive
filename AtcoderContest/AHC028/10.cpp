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
using namespace chrono;
static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
int N, M, si, sj;
vector<string> A, t;

int diff(pair<int, int> p1, pair<int, int> p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second) + 1;
}

string initS(map<char, vector<pair<int, int>>>& charMap) {
  vi dy = {1, -1, 0, 0};
  vi dx = {0, 0, 1, -1};
  unordered_set<string> strSet;
  rep(i, M) strSet.insert(t[i]);

  vector<int> nonUsed(M);
  vector<string> t2;

  rep(i, M) rep(j, M) {
    if (i == j || nonUsed[i] || nonUsed[j]) continue;
    string s2 = t[i] + t[j];
    for (int k = 1; k <= 4; k++) {
      string s3 = s2.substr(k, 5);
      if (strSet.count(s3) && t[i] != s3 && t[j] != s3) {
        nonUsed[i] = 1, nonUsed[j] = 1;
        rep(i2, M) if (s3 == t[i2]) {
          nonUsed[i2] = 1;
          break;
        }
        t2.push_back(s2);
      }
    }
  }

  // debug(t2);

  rep(i, M) if (nonUsed[i] == 0) t2.push_back(t[i]);
  swap(t, t2);
  M = (int)t.size();

  string S;
  // どの文字で始まるか
  vector<unordered_set<int>> st(26);
  rep(i, M) st[t[i][0] - 'A'].insert(i);

  pair<int, int> p = make_pair(si, sj);
  int ni = -1;
  rep(cnt, M) {
    char c = S.empty() ? A[si][sj] : S.back();

    int ok = 0;

    if (st[c - 'A'].size()) {
      auto it = st[c - 'A'].begin();
      S += t[*it];
      ok = 1;
      st[c - 'A'].erase(it);
    }

    if (!ok) {
      // pからbfsする
      queue<pair<int, int>> q;
      q.push(p);
      vector<vector<int>> dist(N, vi(N, 1e9));
      dist[p.first][p.second] = 0;

      while (ok == 0) {
        auto [y, x] = q.front();
        q.pop();

        if (st[A[y][x] - 'A'].size()) {
          auto it = st[A[y][x] - 'A'].begin();
          S += t[*it];
          ok = 1;
          st[A[y][x] - 'A'].erase(it);
        } else {
          rep(k, 4) {
            int ny = y + dy[k], nx = x + dx[k];
            if (min(ny, nx) < 0 || max(ny, nx) >= N) continue;
            if (chmin(dist[ny][nx], dist[y][x] + 1)) q.emplace(ny, nx);
          }
        }
      }
    }
    for (int i = ni + 1; i < (int)S.size(); i++) {
      int nowCost = 1 << 30;
      pair<int, int> np = make_pair(-1, -1);

      for (auto p1 : charMap[S[i]]) {
        if (i == (int)S.size() - 1) {
          if (chmin(nowCost, diff(p, p1))) np = p1;
        } else {
          for (auto p2 : charMap[S[i + 1]]) {
            if (i == (int)S.size() - 2) {
              if (chmin(nowCost, diff(p, p1) + diff(p1, p2))) np = p1;
            } else {
              for (auto p3 : charMap[S[i + 2]])
                if (i == (int)S.size() - 3) {
                  if (chmin(nowCost, diff(p, p1) + diff(p1, p2) + diff(p2, p3)))
                    np = p1;
                } else {
                  for (auto p4 : charMap[S[i + 3]])
                    // if (i == (int)S.size() - 4) {
                    if (chmin(nowCost, diff(p, p1) + diff(p1, p2) +
                                           diff(p2, p3) + diff(p3, p4)))
                      np = p1;
                  // } else {
                  //   for (auto p5 : charMap[S[i + 4]])

                  //     if (chmin(nowCost, diff(p, p1) + diff(p1, p2) +
                  //                            diff(p2, p3) + diff(p3, p4) +
                  //                            diff(p4, p5)))
                  //       np = p1;
                  // }
                }
            }
          }
        }

        p = np;
      }
    }
  }

  // debug(used);

  return S;
}

struct Solver {
  void solve() {
    /* input */
    cin >> N >> M >> si >> sj;
    A.resize(N), t.resize(M);
    rep(i, N) cin >> A[i];
    rep(i, M) cin >> t[i];

    auto startClock = system_clock::now();
    const static double END_TIME = 1.99;  // 終了時間（秒）
    double time = 0.0;                    // 経過時間（秒）
    // int loopCount = 0;

    // 特定のアルファベットの座標たち
    map<char, vector<pair<int, int>>> charMap;
    rep(i, N) rep(j, N) charMap[A[i][j]].emplace_back(i, j);

    string S = initS(charMap);

    ll bestCost = 0;
    vector<pair<int, int>> ans;
    ans.emplace_back(si, sj);
    rep(i, S.size()) {
      int nowCost = 1 << 30;
      pair<int, int> np = make_pair(-1, -1);

      for (auto p : charMap[S[i]]) {
        if (i == (int)S.size() - 1) {
          if (chmin(nowCost, diff(ans.back(), p))) np = p;
        } else {
          for (auto p2 : charMap[S[i + 1]]) {
            if (i == (int)S.size() - 2) {
              if (chmin(nowCost, diff(ans.back(), p) + diff(p, p2))) np = p;
            } else {
              for (auto p3 : charMap[S[i + 2]])
                if (i == (int)S.size() - 3) {
                  if (chmin(nowCost,
                            diff(ans.back(), p) + diff(p, p2) + diff(p2, p3)))
                    np = p;
                } else {
                  for (auto p4 : charMap[S[i + 3]])
                    if (i == (int)S.size() - 4) {
                      if (chmin(nowCost, diff(ans.back(), p) + diff(p, p2) +
                                             diff(p2, p3) + diff(p3, p4)))
                        np = p;
                    } else {
                      for (auto p5 : charMap[S[i + 4]])

                        if (chmin(nowCost, diff(ans.back(), p) + diff(p, p2) +
                                               diff(p2, p3) + diff(p3, p4) +
                                               diff(p4, p5)))
                          np = p;
                    }
                }
            }
          }
        }
      }

      bestCost += diff(ans.back(), np);
      ans.push_back(np);
    }

    // debug(ans.size());

    // 改善パート
    do {
      // 適当な3点を最適化する(最初と最後の方は選ばない)
      int idx = randXor() % ((int)ans.size() - 5) + 1;

      int minDiff = 1 << 30;
      vector<pair<int, int>> np(4);
      for (auto p1 : charMap[A[ans[idx].first][ans[idx].second]])
        for (auto p2 : charMap[A[ans[idx + 1].first][ans[idx + 1].second]])
          for (auto p3 : charMap[A[ans[idx + 2].first][ans[idx + 2].second]])
            for (auto p4 : charMap[A[ans[idx + 3].first][ans[idx + 3].second]])
              if (chmin(minDiff, diff(ans[idx - 1], p1) + diff(p1, p2) +
                                     diff(p2, p3) + diff(p3, p4) +
                                     diff(p4, ans[idx + 4])))
                np[0] = p1, np[1] = p2, np[2] = p3, np[3] = p4;

      ans[idx] = np[0];
      ans[idx + 1] = np[1];
      ans[idx + 2] = np[2];
      ans[idx + 3] = np[3];

      // 時間更新
      time =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);
    } while (time < END_TIME);

    /* solve */
    // score
    // cerr << 10000 - bestCost << endl;

    /* output */
    // 最初は出力しない
    for (int i = 1; i < min(5002, (int)ans.size()); i++) {
      out(ans[i]);
    }
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