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
// 0以上1未満の小数をとる乱数
static double rand01() { return (randXor() + 0.5) * (1.0 / UINT_MAX); }

class TimeKeeper {
 private:
  chrono::high_resolution_clock::time_point start_time_;
  int64_t time_threshold_;

 public:
  // 時間制限をミリ秒単位で指定してインスタンスをつくる。
  TimeKeeper(const int64_t& time_threshold)
      : start_time_(chrono::high_resolution_clock::now()),
        time_threshold_(time_threshold) {}

  // インスタンス生成した時から指定した時間制限を超過したか判定する。
  bool isTimeOver() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count() >=
           time_threshold_;
  }

  int64_t getTime() const {
    auto diff = chrono::high_resolution_clock::now() - this->start_time_;
    return chrono::duration_cast<chrono::milliseconds>(diff).count();
  }
};

int N = 20;
vector<string> C(N);
vector<int> dy = {1, -1, 0, 0};
vector<int> dx = {0, 0, 1, -1};
const int DOWN = 0, UP = 1, RIGHT = 2, LEFT = 3;
string d2c = "DURL";
string d2revc = "UDLR";

int rev(int d) {
  return d == UP ? DOWN : d == DOWN ? UP : d == RIGHT ? LEFT : RIGHT;
};

class Board {
 public:
  vector<string> c_;

  Board() {}
  Board(vector<string> c) : c_(c) {}

  void move(int d, int idx, int cnt = 1) {
    assert(0 <= idx && idx < N);
    rep(ci, cnt) {
      if (d == DOWN) {
        if (c_[N - 1][idx] == 'o') assert(false);
        for (int y = N - 1; y >= 1; y--) {
          c_[y][idx] = c_[y - 1][idx];
        }
        c_[0][idx] = '.';
      } else if (d == UP) {
        if (c_[0][idx] == 'o') assert(false);
        rep(y, N - 1) { c_[y][idx] = c_[y + 1][idx]; }
        c_[19][idx] = '.';
      } else if (d == RIGHT) {
        if (c_[idx][N - 1] == 'o') assert(false);
        for (int x = N - 1; x >= 1; x--) {
          c_[idx][x] = c_[idx][x - 1];
        }
        c_[idx][0] = '.';
      } else {
        if (c_[idx][0] == 'o') assert(false);
        rep(x, N - 1) { c_[idx][x] = c_[idx][x + 1]; }
        c_[idx][19] = '.';
      }
    }
  }

  vector<int> get_fuku_idxes(int d, int idx) {
    assert(0 <= idx && idx < N);
    vector<int> ret;
    if (d == DOWN || d == UP) {
      for (int y = 0; y < N; y++) {
        if (c_[y][idx] == 'o') ret.push_back(y);
      }
    } else {
      for (int x = 0; x < N; x++) {
        if (c_[idx][x] == 'o') ret.push_back(x);
      }
    }
    return ret;
  }

  vector<int> get_oni_idxes(int d, int idx) {
    assert(0 <= idx && idx < N);
    vector<int> ret;
    if (d == DOWN || d == UP) {
      for (int y = 0; y < N; y++) {
        if (c_[y][idx] == 'x') ret.push_back(y);
      }
    } else {
      for (int x = 0; x < N; x++) {
        if (c_[idx][x] == 'x') ret.push_back(x);
      }
    }
    return ret;
  }

  void print_board() {
    cerr << "xx01234567890123456789" << endl;
    rep(i, N) { cerr << i % 10 << ":" << c_[i] << endl; }
    cerr << endl;
  }
};

void exec_input() {
  int _;
  cin >> _;
  rep(i, N) cin >> C[i];
}

vector<pair<char, int>> stupid_4() {
  vector<pair<char, int>> ret;
  // key：(動く方向、動く行あるいは列), value：動かす回数
  map<pair<int, int>, int> mp;

  rep(i, N) rep(j, N) {
    if (C[i][j] == 'x') {
      int d = -1, cnt = 1e9;
      rep(di, 4) {
        int ok = 1;
        int y = i, x = j, nowcnt = 0;
        while (0 <= y && y < N && 0 <= x && x < N) {
          nowcnt++;
          if (C[y][x] == 'o') {
            ok = 0;
            break;
          }
          y += dy[di], x += dx[di];
        }
        if (ok && chmin(cnt, nowcnt)) d = di;
      }
      assert(d != -1);
      if (d < 2) {
        chmax(mp[make_pair(d, j)], cnt);

      } else {
        chmax(mp[make_pair(d, i)], cnt);
      }

      // debug(i, j, d, cnt);
    }
  }

  Board board(C);

  for (auto it = mp.begin(); it != mp.end();) {
    auto [p, cnt] = *it;
    int d = p.first, idx = p.second;
    vector<int> oni_idxes = board.get_oni_idxes(d, idx);
    if (oni_idxes.empty()) {
      // 過去に巻き込まれて上手くいってる
      it = mp.erase(it);
      continue;
    }
    // 後ろで巻き込める
    if (oni_idxes.size() == 1) {
      int ok = 0;
      if (d < 2) {
        int y = oni_idxes[0], x = idx;
        if (mp.count(make_pair(LEFT, y)) && x < mp[make_pair(LEFT, y)]) {
          ok = 1;
        } else if (mp.count(make_pair(RIGHT, y)) &&
                   x > N - mp[make_pair(RIGHT, y)])
          ok = 1;
      } else {
        int y = idx, x = oni_idxes[0];
        if (mp.count(make_pair(UP, x)) && y < mp[make_pair(UP, x)]) ok = 1;
        if (mp.count(make_pair(DOWN, x)) && y > N - mp[make_pair(DOWN, x)])
          ok = 1;
      }
      if (ok) {
        it = mp.erase(it);
        continue;
      }
    }

    rep(k, cnt) ret.emplace_back(d2c[d], idx);

    // 実際に順方向に動かす
    board.move(d, idx, cnt);

    // その行や列にまだ鬼が残っているなら戻す
    if (board.get_oni_idxes(d, idx).size()) {
      rep(k, cnt) ret.emplace_back(d2revc[d], idx);
      board.move(rev(d), idx, cnt);
    } else {
      // debug(d, idx, cnt);
      // board.print_board();
      // この列の全ての福が今いる行を取得。その列に対する左右（上下）操作が残ってたら戻す
      auto f = [&]() {
        vector<int> fuku_idxes = board.get_fuku_idxes(d, idx);
        // debug(fuku_idxes);
        for (auto v : fuku_idxes) {
          if (d < 2) {
            if (mp.count(make_pair(LEFT, v))) return true;
            if (mp.count(make_pair(RIGHT, v))) return true;
          } else {
            if (mp.count(make_pair(DOWN, v))) return true;
            if (mp.count(make_pair(RIGHT, v))) return true;
          }
        }
        return false;
      };
      rep(i, cnt) {
        if (!f()) break;
        board.move(rev(d), idx);
        ret.emplace_back(d2revc[d], idx);
      }
    }
    it = mp.erase(it);
  }
  return ret;
}

// 戻りをサボれるならサボる
vector<pair<char, int>> stupid_10() {
  vector<pair<char, int>> ret;
  // key：(動く方向、動く行あるいは列), value：動かす回数
  map<pair<int, int>, int> mp;

  rep(i, N) rep(j, N) {
    if (C[i][j] == 'x') {
      // int d = -1, cnt = 1e9;
      vi oks, cnts;
      rep(di, 4) {
        int ok = 1;
        int y = i, x = j, nowcnt = 0;
        while (0 <= y && y < N && 0 <= x && x < N) {
          nowcnt++;
          if (C[y][x] == 'o') {
            ok = 0;
            break;
          }
          y += dy[di], x += dx[di];
        }
        if (ok) {
          oks.push_back(di);
          cnts.push_back(nowcnt);
        }
        // if (ok && chmin(cnt, nowcnt)) d = di;
      }

      int idx = randXor() % (int)oks.size();
      int d = oks[idx], cnt = cnts[idx];

      assert(d != -1);
      if (d < 2) {
        chmax(mp[make_pair(d, j)], cnt);

      } else {
        chmax(mp[make_pair(d, i)], cnt);
      }

      // debug(i, j, d, cnt);
    }
  }

  Board board(C);

  for (auto it = mp.begin(); it != mp.end();) {
    auto [p, cnt] = *it;
    int d = p.first, idx = p.second;

    vector<int> oni_idxes = board.get_oni_idxes(d, idx);
    if (oni_idxes.empty()) {
      // 過去に巻き込まれて上手くいってる
      it = mp.erase(it);
      continue;
    }
    // 後ろで巻き込める
    if (oni_idxes.size() == 1) {
      int ok = 0;
      if (d < 2) {
        int y = oni_idxes[0], x = idx;
        if (mp.count(make_pair(LEFT, y)) && x < mp[make_pair(LEFT, y)]) {
          ok = 1;
        } else if (mp.count(make_pair(RIGHT, y)) &&
                   x > N - mp[make_pair(RIGHT, y)])
          ok = 1;
      } else {
        int y = idx, x = oni_idxes[0];
        if (mp.count(make_pair(UP, x)) && y < mp[make_pair(UP, x)])
          ok = 1;
        else if (mp.count(make_pair(DOWN, x)) && y > N - mp[make_pair(DOWN, x)])
          ok = 1;
      }
      if (ok) {
        it = mp.erase(it);
        continue;
      }
    }

    rep(k, cnt) ret.emplace_back(d2c[d], idx);

    // 実際に順方向に動かす
    board.move(d, idx, cnt);

    // その行や列にまだ鬼が残っているなら戻す
    if (board.get_oni_idxes(d, idx).size()) {
      rep(k, cnt) ret.emplace_back(d2revc[d], idx);
      board.move(rev(d), idx, cnt);
    } else {
      // debug(d, idx, cnt);
      // board.print_board();
      // この列の全ての福が今いる行を取得。その列に対する左右（上下）操作が残ってたら戻す
      auto f = [&]() {
        vector<int> fuku_idxes = board.get_fuku_idxes(d, idx);
        // debug(fuku_idxes);
        for (auto v : fuku_idxes) {
          if (d < 2) {
            if (mp.count(make_pair(LEFT, v))) return true;
            if (mp.count(make_pair(RIGHT, v))) return true;
          } else {
            if (mp.count(make_pair(DOWN, v))) return true;
            if (mp.count(make_pair(RIGHT, v))) return true;
          }
        }
        return false;
      };
      rep(i, cnt) {
        if (!f()) break;
        board.move(rev(d), idx);
        ret.emplace_back(d2revc[d], idx);
      }
    }
    it = mp.erase(it);
  }
  return ret;
}

int calc_score(const vector<pair<char, int>>& ans) {
  return 8 * N * N - (int)ans.size();
}

int main() {
  const int time_threshold = 1970;
  auto time_keeper = TimeKeeper(time_threshold);
  exec_input();

  vector<pair<char, int>> best_ans = stupid_4();
  int best_score = calc_score(best_ans);
  // debug(best_score);

  int loop_count = 0;
  while (true) {
    loop_count++;
    if (loop_count % 128 == 0) {
      if (time_keeper.isTimeOver()) break;
    }

    vector<pair<char, int>> res = stupid_10();
    int score = calc_score(res);
    if (chmax(best_score, score)) best_ans = res;
  }
  debug(loop_count);

  cerr << best_score << endl;

  rep(i, best_ans.size()) {
    //
    cout << best_ans[i].first << " " << best_ans[i].second << endl;
  }
}