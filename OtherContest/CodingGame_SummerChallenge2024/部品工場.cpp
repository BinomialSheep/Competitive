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

int player_idx = 0, other1_idx = 1, other2_idx = 2;
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
string action = "ULDR";
vector<string> actions1 = {"U", "L", "D", "R"};
vector<string> actions2;
vector<string> actions3;

int pow(int x, int y) {
  int ret = 1;
  rep(i, y) ret *= x;
  return ret;
}

struct RaceState {
  vector<int> dp;
  RaceState(){};

  void reset(string gpu) {
    dp.resize(30);
    rep(i, 30) dp[i] = 1e9;
    dp[29] = 0;
    for (int i = 28; i >= 0; i--) {
      // LEFT
      if (gpu[i + 1] == '#') {
        chmin(dp[i], dp[i + 1] + 3);
      } else {
        chmin(dp[i], dp[i + 1] + 1);
      }
      // UP
      if (i == 28) {
        chmin(dp[i], dp[i + 1] + 1);
      } else if (gpu[i + 2] == '#') {
        chmin(dp[i], dp[i + 2] + 3);
      } else {
        chmin(dp[i], dp[i + 2] + 1);
      }
      // DOWN
      if (i == 28) {
        chmin(dp[i], dp[i + 1] + 1);
      } else if (gpu[i + 1] == '#') {
        chmin(dp[i], dp[i + 1] + 3);
      } else if (gpu[i + 2] == '#') {
        chmin(dp[i], dp[i + 2] + 3);
      } else {
        chmin(dp[i], dp[i + 2] + 1);
      }
      // RIGHT
      if (i == 28) {
        chmin(dp[i], dp[i + 1] + 1);
      } else if (i == 27) {
        chmin(dp[i], dp[i + 2] + 1);
      } else if (gpu[i + 1] == '#') {
        chmin(dp[i], dp[i + 1] + 3);
      } else if (gpu[i + 2] == '#') {
        chmin(dp[i], dp[i + 2] + 3);
      } else if (gpu[i + 3] == '#') {
        chmin(dp[i], dp[i + 3] + 3);
      } else {
        chmin(dp[i], dp[i + 3] + 1);
      }
    }
  }

  void print() {
    cerr << "RaceState: ";
    rep(i, 30) cerr << dp[i] << " ";
    cerr << endl;
  }
};

// dp[i][j] := 残りiターン、リスクjから何マス進めるか
vector skatingDp(16, vector(6, 0));
void calcSkatingDp() {
  for (int i = 1; i < 16; i++) {
    // スタンからの回復
    if (i >= 2) chmax(skatingDp[i][5], skatingDp[i - 2][0]);
    rep(j, 5) {
      // move1: 1スペース前進し、リスクは1減少します
      chmax(skatingDp[i][j], skatingDp[i - 1][max(0, j - 1)] + 1);
      // move2: 2スペース前進し、リスクは変化しません
      chmax(skatingDp[i][j], skatingDp[i - 1][j] + 2);
      // move3: 2スペース前進し、リスクは1増加します
      chmax(skatingDp[i][j], skatingDp[i - 1][min(5, j + 1)] + 2);
      // move4: 3スペース前進し、リスクは2増加します
      chmax(skatingDp[i][j], skatingDp[i - 1][min(5, j + 2)] + 3);
    }
  }

  debug(skatingDp);
}

// スケートで移動した距離
struct SkatingState {
  vector<int> dist;
  vector<int> lastScape;

  SkatingState() : dist(3, 0), lastScape(3, 0){};

  void update(string& gpu, vi& reg) {
    if (gpu == "GAME_OVER") {
      rep(i, 3) dist[i] = 0, lastScape[i] = 0;
    } else {
      rep(i, 3) {
        if (reg[i] - lastScape[i] >= 0) {
          dist[i] += reg[i] - lastScape[i];
        } else {
          dist[i] += reg[i] - lastScape[i] + 10;
        }
        lastScape[i] = reg[i];
      }
    }
  }

  void print() {
    cerr << "SkatingState: " << dist[player_idx] << " " << dist[other1_idx]
         << " " << dist[other2_idx] << endl;
  }
};

void skatingSort() {
  vector<int> priorityMove(4);
  rep(i, 4) priorityMove[i] = i;

  vector<bool> isStan(4);

  int reg1 = 0, reg6 = 3;

  auto f = [&](int v) -> int {
    if (v == 0) return skatingDp[reg6 - 1][max(0, reg1 - 1)] + 1;
    if (v == 1) return skatingDp[reg6 - 1][reg1] + 2;
    if (v == 2) return skatingDp[reg6 - 1][min(5, reg1 + 1)] + 2;
    if (v == 3) return skatingDp[reg6 - 1][min(5, reg1 + 2)] + 3;
    assert(false);
    return -1;
  };

  sort(all(priorityMove), [&](int a, int b) {
    if (isStan[a] == isStan[b]) {
      return f(a) > f(b);
    } else if (isStan[a]) {
      return false;
    } else {
      return true;
    }
  });
  debug(priorityMove);
}

void divingPoint() {
  // 最善を尽くした場合に得られるポイント
  auto f = [&](int turnLeft, int points, int combo) {
    return points + turnLeft * (2 * combo + turnLeft - 1) / 2;
  };

  assert(f(1, 0, 1) == 1);
  assert(f(1, 0, 2) == 2);
  assert(f(1, 3, 5) == 8);
  assert(f(2, 0, 1) == 3);
  assert(f(5, 0, 1) == 15);
  assert(f(5, 100, 2) == 120);

  // 今回サボる場合
  assert(f(4, 100, 1) == 110);
}

vi haudleRace(string& gpu, vi& reg, int nowTurn, RaceState& state,
              int lookTurn) {
  vi ret(pow(4, lookTurn));
  if (gpu == "GAME_OVER") return ret;
  // スタン中ならどうでもいい
  if (reg[3 + player_idx]) return ret;

  gpu += ".....";

  int playerBest = state.dp[reg[player_idx]];
  int other1Best = state.dp[reg[other1_idx]] + reg[3 + other1_idx];
  int other2Best = state.dp[reg[other2_idx]] + reg[3 + other2_idx];
  int playerSecond = 0;
  for (int i = 1; i <= 3; i++) {
    int tmp = state.dp[reg[player_idx] + i];
    if (gpu[player_idx] + i == '#') tmp += 2;
    chmax(playerSecond, tmp);
  }

  // 終わらないならどうでもいい
  int turnLest = 100 - nowTurn + 1;
  cerr << "race: " << turnLest << " " << playerBest << " " << other1Best << " "
       << other2Best << " " << playerSecond << endl;
  if (turnLest < playerBest && turnLest < other1Best && turnLest < other2Best)
    return ret;
  // 自分が何しても単独金ならなんでもいい
  {
    bool existHaudle = false;
    for (int i = reg[player_idx] + 1; i < 29; i++)
      if (gpu[i] == '#') existHaudle = true;
    if (!existHaudle && 29 - reg[player_idx] < other1Best &&
        reg[player_idx] < other2Best) {
      cerr << "ハードル確定金" << endl;
      return ret;
    }
  }
  // string action = "ULDR";
  int actionIdx = 0;
  auto rec = [&](auto rec2, string& s, int pos, int stanTurn,
                 int actionTurn) -> void {
    if ((int)s.size() == lookTurn) {
      int sumTurn = state.dp[pos] + actionTurn + stanTurn;
      // 判定
      if (sumTurn < other1Best && sumTurn < other2Best) {
        ret[actionIdx] = (15);
      } else if (sumTurn <= other1Best && sumTurn <= other2Best) {
        ret[actionIdx] = (12);
      } else if (sumTurn <= other1Best || sumTurn <= other2Best) {
        ret[actionIdx] = (5);
      } else {
        ret[actionIdx] = (1);
      }
      actionIdx++;
      return;
    }

    for (auto c : action) {
      int pos2 = pos, stanTurn2 = stanTurn, actionTurn2 = actionTurn;
      s.push_back(c);
      if (pos >= 29) {
        rec2(rec2, s, pos, stanTurn, actionTurn);
      } else {
        actionTurn2++;
        if (c == 'U') {
          pos2 += 2;
        } else if (c == 'L') {
          pos2 += 1;
        } else if (c == 'D') {
          if (gpu[pos2 + 1] == '#') {
            pos2 += 1;
          } else {
            pos2 += 2;
          }
        } else if (c == 'R') {
          if (gpu[pos2 + 1] == '#') {
            pos2 += 1;
          } else if (gpu[pos2 + 2] == '#') {
            pos2 += 2;
          } else {
            pos2 += 3;
          }
        }
        if (gpu[pos2] == '#') stanTurn2 += 2;
        rec2(rec2, s, pos2, stanTurn2, actionTurn2);
      }
      s.pop_back();
    }
  };
  string s = "";
  rec(rec, s, reg[player_idx], 0, 0);

  rep(i, ret.size()) cerr << "haudleRace Ret: " << ret[i] << endl;
  return ret;
}

vi archery(string& gpu, vi& reg, int nowTurn, int lookTurn) {
  int x = reg[player_idx * 2], y = reg[player_idx * 2 + 1];
  cerr << "gpu: " << gpu << ", x: " << x << ", y: " << y << endl;

  vi ret(pow(4, lookTurn));
  if (gpu == "GAME_OVER") return ret;

  vector<string> actions;
  if (lookTurn == 1) actions = actions1;
  if (lookTurn == 2) actions = actions2;
  if (lookTurn == 3) actions = actions3;

  // 100ターン経過まで終わらないならどうでもいい
  if (100 - nowTurn + 1 < (int)gpu.size()) return ret;

  auto g = [&](int& sx, int& sy) {
    sx = abs(sx), sy = abs(sy);
    if (sx > sy) swap(sx, sy);
    chmin(sx, 20);
    chmin(sy, 20);
  };

  unordered_map<int, int> memo;

  auto f = [&](auto rec, int sx, int sy, int idx = 0) -> int {
    g(sx, sy);
    if (idx >= (int)gpu.size()) {
      return sx + sy;
    }
    int key = (idx << 10) + (sx << 5) + sy;
    if (memo.count(key)) return memo[key];

    int score = 1e9;
    int v = gpu[idx] - '0';
    chmin(score, rec(rec, sx + v, sy, idx + 1));
    if (score != 0) chmin(score, rec(rec, sx - v, sy, idx + 1));
    if (score != 0) chmin(score, rec(rec, sx, sy + v, idx + 1));
    if (score != 0) chmin(score, rec(rec, sx, sy - v, idx + 1));

    return memo[key] = score;
  };

  int other1Best = f(f, reg[other1_idx * 2], reg[other1_idx * 2 + 1]);
  int other2Best = f(f, reg[other2_idx * 2], reg[other2_idx * 2 + 1]);
  // debug(other1Best, other2Best);

  rep(actionIdx, actions.size()) {
    int sx = x, sy = y;
    string s = actions[actionIdx];
    rep(i, s.size()) {
      if (i >= (int)gpu.size()) continue;
      int v = gpu[i] - '0';
      if (s[i] == 'U') {
        sy = max(-20, sy - v);
      } else if (s[i] == 'L') {
        sx = max(-20, sx - v);
      } else if (s[i] == 'D') {
        sy = min(20, sy + v);
      } else if (s[i] == 'R') {
        sx = min(20, sx + v);
      }
    }

    int score = f(f, sx, sy, (int)s.size());

    // debug(sx, sy, s.size(), score);

    // 判定
    if (score < other1Best && score < other2Best) {
      ret[actionIdx] = (15);
    } else if (score <= other1Best && score <= other2Best) {
      ret[actionIdx] = (12);
    } else if (score <= other1Best || score <= other2Best) {
      ret[actionIdx] = (5);
    } else {
      ret[actionIdx] = (1);
    }
  }

  rep(i, ret.size()) cerr << "archery Ret: " << actions[i] << " " << ret[i]
                          << endl;

  return ret;
}

vi skating(string& gpu, vi& reg, int nowTurn, SkatingState& state,
           int lookTurn) {
  vi ret(pow(4, lookTurn));

  state.update(gpu, reg);

  if (gpu == "GAME_OVER") return ret;
  if (nowTurn >= 95) return ret;
  // スタン中ならどうでもいい
  if (reg[3 + player_idx] < 0) return ret;

  vector<string> actions;
  if (lookTurn == 1) actions = actions1;
  if (lookTurn == 2) actions = actions2;
  if (lookTurn == 3) actions = actions3;

  //

  auto f = [&](int leftTurn, int player, int risk) {
    int res = 0;
    if (risk < 0) {
      res = skatingDp[leftTurn + reg[3 + player_idx]][0];
    } else {
      res = skatingDp[leftTurn][risk];
    }
    return res + state.dist[player];
  };

  int other1Best = f(reg[6], other1_idx, reg[3 + other1_idx]);
  int other2Best = f(reg[6], other2_idx, reg[3 + other2_idx]);

  debug(other1Best, other2Best);

  // スタンに入る行動は評価が低い
  vector<bool> isStan(4);
  if (reg[3 + other1_idx] < 0) {
    if ((reg[player_idx] + 1) % 10 == reg[other1_idx]) isStan[0] = true;
    if ((reg[player_idx] + 2) % 10 == reg[other1_idx])
      isStan[1] = isStan[2] = true;
    if ((reg[player_idx] + 3) % 10 == reg[other1_idx]) isStan[3] = true;
  }
  if (reg[3 + other2_idx] < 0) {
    if ((reg[player_idx] + 1) % 10 == reg[other2_idx]) isStan[0] = true;
    if ((reg[player_idx] + 2) % 10 == reg[other2_idx])
      isStan[1] = isStan[2] = true;
    if ((reg[player_idx] + 3) % 10 == reg[other2_idx]) isStan[3] = true;
  }

  rep(actionIdx, actions.size()) {
    char c = actions[actionIdx][0];
    int risk = 0, d = 0;

    rep(i, 4) {
      if (gpu[i] == c) {
        if (i == 0) {
          if (risk) risk--;
          d++;
        } else if (i == 1) {
          d += 2;
        } else if (i == 2) {
          risk++;
          d += 2;
        } else {
          risk += 2;
          d += 3;
        }
        if (isStan[i]) risk += 2;
      }
    }
    if (risk > 5) risk = -2;
    int score = d + f(reg[6] - 1, player_idx, risk);

    // 判定
    if (score > other1Best && score > other2Best) {
      ret[actionIdx] = (15);
    } else if (score >= other1Best && score >= other2Best) {
      ret[actionIdx] = (12);
    } else if (score >= other1Best || score >= other2Best) {
      ret[actionIdx] = (5);
    } else {
      ret[actionIdx] = (1);
    }
  }

  rep(i, ret.size()) cerr << "skating Ret: " << actions[i] << " " << ret[i]
                          << endl;

  return ret;
}

vi diving(string& gpu, vi& reg, int nowTurn, int lookTurn) {
  vi ret(pow(4, lookTurn));
  if (gpu == "GAME_OVER") return ret;

  // 100ターン経過まで終わらないならどうでもいい
  if (100 - nowTurn + 1 < (int)gpu.size()) return ret;

  // 最善を尽くした場合に得られるポイント
  auto f = [&](int turnLeft, int points, int combo) {
    combo++;
    return points + turnLeft * (2 * combo + turnLeft - 1) / 2;
  };

  int turnLeft = (int)gpu.size();
  int playerBest = f(turnLeft, reg[player_idx], reg[player_idx + 3]);
  int other1Best = f(turnLeft, reg[other1_idx], reg[other1_idx + 3]);
  int other2Best = f(turnLeft, reg[other2_idx], reg[other2_idx + 3]);
  int playerSecond = f(turnLeft - 1, reg[player_idx], 1);

  cerr << reg[player_idx] << " " << reg[player_idx + 3] << " " << turnLeft
       << " " << playerBest << " " << other1Best << " " << other2Best << endl;

  if (other1Best < reg[player_idx] && other2Best < reg[player_idx]) return ret;

  int actionIdx = 0;

  auto rec = [&](auto rec2, string& s, int points, int combo) -> void {
    if ((int)s.size() == lookTurn) {
      debug(s, points);
      int score = f(max(0, turnLeft - (int)s.size()), points, combo);
      debug(s, score);

      // 判定
      if (points > other1Best && points > other2Best) {
        ret[actionIdx] = (17);
      } else if (score > other1Best && score > other2Best) {
        ret[actionIdx] = (15);
      } else if (score >= other1Best && score >= other2Best) {
        ret[actionIdx] = (12);
      } else if (score >= other1Best || score >= other2Best) {
        ret[actionIdx] = (5);
      } else {
        ret[actionIdx] = score / 20;
      }
      return;
    }

    int idx = (int)s.size() - 1;

    for (auto c : action) {
      s.push_back(c);
      int combo2 = combo, points2 = points;
      if (idx >= (int)gpu.size()) continue;
      combo2++;
      if (s[idx] == gpu[idx]) {
        points2 += combo2;
      } else {
        combo2 = 0;
      }
      rec2(rec2, s, points2, combo2);
      s.pop_back();
    }
  };
  string s = "";
  rec(rec, s, reg[player_idx], reg[player_idx + 3]);

  // rep(i, ret.size()) cerr << "diving Ret: " << actions[i] << " " << ret[i]
  //                         << endl;

  return ret;
}

void testHaudle() {
  RaceState raseState;
  string gpu = ".....#...#...#................";
  raseState.reset(gpu);
  raseState.print();
  int nowTurn = 10;
  int lookTurn = 3;
  vi reg = {0, 0, 0, 0, 0, 0, 1};
  haudleRace(gpu, reg, nowTurn, raseState, lookTurn);
}

void testArchery() {
  string gpu = "1432";
  int nowTurn = 10;
  int lookTurn = 3;
  vi reg = {0, 0, 1, 0, 0, 1, 1};
  archery(gpu, reg, nowTurn, lookTurn);
}

void testSkating() {
  string gpu = "URLD";
  int nowTurn = 10;
  int lookTurn = 3;
  SkatingState state;
  vi reg = {0, 0, 0, 0, 0, 0, 4};
  skating(gpu, reg, nowTurn, state, lookTurn);
}

void testDiving() {
  string gpu = "UUUDDLLLULDRLL";
  int nowTurn = 10;
  int lookTurn = 3;
  vi reg = {90, 0, 0, 0, 0, 0, 4};
  diving(gpu, reg, nowTurn, lookTurn);
}

int main() {
  //
  calcSkatingDp();
  skatingSort();

  vector<vector<string>> actions(10);
  actions[0] = {"U", "L", "D", "R"};
  for (int i = 1; i < 5; i++) {
    for (auto s : actions[i - 1]) {
      rep(j, 4) {
        s.push_back(action[j]);
        actions[i].push_back(s);
        s.pop_back();
      }
    }
  }
  debug(actions);

  // 3ターン分先読む
  rep(i, 4) rep(j, 4) {
    string tmp = "";
    tmp.push_back(action[i]);
    tmp.push_back(action[j]);
    actions2.push_back(tmp);
  }
  for (auto s : actions2) {
    rep(i, 4) {
      s.push_back(action[i]);
      actions3.push_back(s);
      s.pop_back();
    }
  }

  // debug(actions2, actions3);
  // testHaudle();
  // testArchery();
  // testSkating();
  testDiving();

  // divingPoint();
}