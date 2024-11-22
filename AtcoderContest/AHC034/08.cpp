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

struct Solver {
  void solve() {
    /* input */
    INT(N);
    vvi origH(N, vi(N));
    rep(i, N) rep(j, N) cin >> origH[i][j];

    auto startClock = system_clock::now();
    const static double END_TIME = 1.8;  // 終了時間（秒）
    double time = 0.0;                   // 経過時間（秒）

    ll mncost = 1e18;
    vpii minpath;
    vi minloading;

    /* solve */

    while (true) {
      time =
          ((double)duration_cast<microseconds>(system_clock::now() - startClock)
               .count() *
           1e-6);
      if (time >= (END_TIME)) break;

      vvi H = origH;

      set<pair<int, int>> plus;
      set<pair<int, int>> minus;
      rep(i, N) rep(j, N) {
        if (H[i][j] > 0) plus.emplace(i, j);
        if (H[i][j] < 0) minus.emplace(i, j);
      }

      vector<pair<int, int>> path;
      vector<int> loading;

      int dump = 0;
      path.emplace_back(0, 0);
      if (H[0][0] > 0) {
        plus.erase(make_pair(0, 0));
        loading.emplace_back(H[0][0]);
        dump += H[0][0];
        H[0][0] = 0;
      } else {
        loading.emplace_back(0);
      }

      int nowY = 0, nowX = 0;
      int turn = 0;

      while (minus.size()) {
        ++turn;
        // debug(nowY, nowX, dump, plus.size(), minus.size());
        // 最近傍を見つける
        int nextY, nextX;
        {
          int mnDist = 1e9;
          int isMinus = 0;
          for (auto [y, x] : minus) {
            if (-H[y][x] > dump) continue;
            int dist = abs(nowY - y) + abs(nowX - x);
            if (chmin(mnDist, dist)) {
              isMinus = 1, nextY = y, nextX = x;
            } else if (mnDist == dist && randXor() % 5 == 0) {
              isMinus = 1, nextY = y, nextX = x;
            }
          }
          for (auto [y, x] : plus) {
            int dist = abs(nowY - y) + abs(nowX - x);
            if (chmin(mnDist, dist)) {
              nextY = y, nextX = x;
              isMinus = 0;
            } else if (mnDist == dist && !isMinus && randXor() % 5 == 0) {
              nextY = y, nextX = x;
            }
          }
        }
        // debug(nextY, nextX);
        //
        plus.erase(make_pair(nextY, nextX));
        minus.erase(make_pair(nextY, nextX));
        // 最近傍まで移動する
        path.emplace_back(nextY, nextX);
        nowY = nextY, nowX = nextX;
        // 貪欲に操作する
        if (H[nowY][nowX] > 0) {
          loading.push_back(H[nowY][nowX]);
          dump += H[nowY][nowX];
        } else if (H[nowY][nowX] < 0) {
          loading.push_back(H[nowY][nowX]);
          dump += H[nowY][nowX];
        } else {
          debug(nowY, nowX);
          assert(false);
        }
        H[nowY][nowX] = 0;
      }
      assert(path.size() == loading.size());
      // debug(path.size(), loading.size());
      // 後回し改善
      bool continueFlag = true;
      while (continueFlag) {
        continueFlag = false;

        dump = 0;
        rep(i, path.size()) {
          dump += loading[i];
          if (loading[i] <= 0) continue;
          int mnDump = 1e9;
          int dump2 = dump;
          for (int j = i + 2; j < (int)path.size(); j++) {
            dump2 += loading[j - 1];
            chmin(mnDump, dump2);
            // 後回しにできる余力がないので抜ける
            if (mnDump == 0) break;
            // あとで立ち寄れる
            int oky = 0, okx = 0;
            if (path[j].first >= path[j - 1].first &&
                path[j].first >= path[i].first &&
                path[i].first >= path[j - 1].first)
              oky = 1;
            if (path[j].first <= path[j - 1].first &&
                path[j].first <= path[i].first &&
                path[i].first <= path[j - 1].first)
              oky = 1;
            if (path[j].second >= path[j - 1].second &&
                path[j].second >= path[i].second &&
                path[i].second >= path[j - 1].second)
              okx = 1;
            if (path[j].second <= path[j - 1].second &&
                path[j].second <= path[i].second &&
                path[i].second <= path[j - 1].second)
              okx = 1;
            if (!oky || !okx) continue;
            // そこで立ち寄るとしたら、最大mnDumpを後回しにできる
            int tmp = min(loading[i], mnDump);
            // debug(i, j - 1, loading[i], mnDump, tmp, path[i]);
            path.insert(path.begin() + j, path[i]);
            loading.insert(loading.begin() + j, tmp);
            loading[i] -= tmp;
            dump -= tmp;
            continueFlag = true;
            // debug(i, j, loading[i], loading[j]);
            break;
          }
        }
        // いらないパスをキレイにしておく
        vpii npath;
        vi nloading;
        rep(i, path.size()) {
          if (i && loading[i] == 0) continue;
          npath.push_back(path[i]);
          nloading.push_back(loading[i]);
        }
        swap(path, npath);
        swap(loading, nloading);
        // debug(path);
      }

      // debug(path.size(), loading.size());
      vpii npath;
      vi nloading;
      nowY = 0, nowX = 0;
      npath.emplace_back(0, 0);
      nloading.push_back(loading[0]);
      rep(i, path.size()) {
        auto [y, x] = path[i];
        while (y < nowY)
          nowY--, npath.emplace_back(nowY, nowX), nloading.push_back(0);
        while (x < nowX)
          nowX--, npath.emplace_back(nowY, nowX), nloading.push_back(0);
        while (x > nowX)
          nowX++, npath.emplace_back(nowY, nowX), nloading.push_back(0);
        while (y > nowY)
          nowY++, npath.emplace_back(nowY, nowX), nloading.push_back(0);
        npath.pop_back();
        nloading.pop_back();
        npath.push_back(path[i]);
        nloading.push_back(loading[i]);
      }
      swap(path, npath);
      swap(loading, nloading);
      // debug(path.size(), loading.size());
      // debug(path);

      ll cost = 0;
      dump = 0;
      rep(i, path.size()) {
        if (i) {
          int num = abs(path[i].first - path[i - 1].first) +
                    abs(path[i].second - path[i - 1].second);
          cost += (100 + dump) * num;
        }

        cost += abs(loading[i]);
        dump += loading[i];
      }
      // debug(cost);
      cerr << cost << endl;

      if (chmin(mncost, cost)) {
        minpath = path;
        minloading = loading;
      }
    }

    vector<string> ans;
    int nowY = 0, nowX = 0;
    rep(i, minpath.size()) {
      // 経路復元
      auto [y, x] = minpath[i];
      while (y < nowY) nowY--, ans.push_back("U");
      while (x < nowX) nowX--, ans.push_back("L");
      while (x > nowX) nowX++, ans.push_back("R");
      while (y > nowY) nowY++, ans.push_back("D");
      // 積み下ろし
      if (minloading[i] > 0) {
        ans.push_back("+" + to_string(minloading[i]));
      } else if (minloading[i] < 0) {
        ans.push_back(to_string(minloading[i]));
      }
    }

    rep(i, ans.size()) out(ans[i]);
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