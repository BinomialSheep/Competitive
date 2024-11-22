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
using vs = vector<string>;
using vl = vector<long long>;
using pii = pair<int, int>;
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

int player_idx, other1_idx, other2_idx;
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
string action = "ULDR";

struct RaceState {
  vector<int> dp;
  RaceState(){};

  void reset(string gpu) {
    dp.resize(35);
    rep(i, 30) dp[i] = 1e9;
    for (int i = 29; i < 35; i++) dp[i] = 0;
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

int pow(int x, int y) {
  int ret = 1;
  rep(i, y) ret *= x;
  return ret;
}
vi haudleRace(string& gpu, vi& reg, int nowTurn, RaceState& state, int lookTurn,
              vs& actions) {
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

  // rep(i, ret.size()) cerr << "haudleRace Ret: " << actions[i] << " " <<
  // ret[i]
  //                         << endl;
  return ret;
}

vi archery(string& gpu, vi& reg, int nowTurn, int lookTurn, vs& actions) {
  int x = reg[player_idx * 2], y = reg[player_idx * 2 + 1];
  cerr << "gpu: " << gpu << ", x: " << x << ", y: " << y << endl;

  vi ret(pow(4, lookTurn));
  if (gpu == "GAME_OVER") return ret;

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
  if (other1Best > other2Best) swap(other1Best, other2Best);
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

    // cerr << actionIdx << " " << sx << " " << sy << " " << s.size() << endl;

    int score = f(f, sx, sy, (int)s.size());

    // cerr << actionIdx << " " << sx << " " << sy << " " << score << endl;

    // debug(sx, sy, s.size(), score);

    // 判定
    if (score < other1Best) {
      ret[actionIdx] = (15);
    } else if (score <= other1Best) {
      ret[actionIdx] = (12);
    } else if (score <= other2Best) {
      ret[actionIdx] = (5);
    } else {
      ret[actionIdx] = max(0, 5 - (score - other2Best));
    }
  }

  // rep(i, ret.size()) cerr << "archery Ret: " << actions[i] << " " << ret[i]
  //                         << endl;

  return ret;
}

vi skating(string& gpu, vi& reg, int nowTurn, SkatingState& state, int lookTurn,
           vs& actions) {
  vi ret(pow(4, lookTurn));

  state.update(gpu, reg);
  // state.print();

  if (gpu == "GAME_OVER") return ret;
  if (nowTurn >= 95) return ret;
  // スタン中ならどうでもいい
  if (reg[3 + player_idx] < 0) return ret;

  //

  auto f = [&](int leftTurn, int player, int risk) {
    int res = 0;
    // cerr << "f: " << leftTurn << " " << player << " " << risk << endl;
    if (risk < 0) {
      int turn = leftTurn + reg[3 + player];
      if (turn > 0) res = skatingDp[turn][0];
    } else {
      res = skatingDp[leftTurn][risk];
    }
    return res + state.dist[player];
  };

  int other1Best = f(reg[6], other1_idx, reg[3 + other1_idx]);
  int other2Best = f(reg[6], other2_idx, reg[3 + other2_idx]);
  if (other1Best <= state.dist[player_idx] &&
      other2Best <= state.dist[player_idx]) {
    cerr << "スケート金確定" << endl;
    return ret;
  }
  // cerr << "skating Best: " << other1Best << " " << other2Best << endl;

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

  // rep(i, ret.size()) cerr << "skating Ret: " << actions[i] << " " << ret[i]
  //                         << endl;

  return ret;
}

vi diving(string& gpu, vi& reg, int nowTurn, int lookTurn, vs& actions) {
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

  cerr << gpu << endl;

  int actionIdx = 0;
  auto rec = [&](auto rec2, string& s, int points, int combo) -> void {
    if ((int)s.size() == lookTurn) {
      // debug(s, points);
      int score = f(max(0, turnLeft - (int)s.size()), points, combo);
      // debug(s, score);
      // cerr << actions[actionIdx] << " " << max(0, turnLeft - (int)s.size())
      //      << " " << points << " " << combo << " " << score << endl;

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
      actionIdx++;
      return;
    }

    int idx = (int)s.size();
    for (auto c : action) {
      s.push_back(c);
      int combo2 = combo, points2 = points;
      if (idx < (int)gpu.size()) {
        combo2++;
        if (s[idx] == gpu[idx]) {
          points2 += combo2;
        } else {
          combo2 = 0;
        }
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

vi calcMiniGameCoefficient(vector<vector<int>>& scores) {
  vi ret(4, 1000);

  vector<pair<int, int>> nowScore(4);
  rep(i, 4) {
    nowScore[i].first =
        scores[player_idx][i * 3 + 1] * 3 + scores[player_idx][i * 3 + 2];
    nowScore[i].second = i;
  }
  rep(i, 4) cerr << "nowScore: " << nowScore[i].first << endl;
  sort(nowScore.begin(), nowScore.end());
  for (int i = 1; i < 4; i++) {
    if (nowScore[i].first > nowScore[i - 1].first) {
      ret[nowScore[i].second] = ret[nowScore[i - 1].second] / 10;
    } else {
      ret[nowScore[i].second] = ret[nowScore[i - 1].second];
    }
  }
  rep(i, 4) cerr << "miniGameCofficient: " << ret[i] << endl;
  return ret;
}

void initialInput(int& nb_games) {
  cin >> player_idx;
  assert(0 <= player_idx && player_idx <= 2);
  cerr << player_idx << endl;
  if (player_idx == 0) other1_idx = 1, other2_idx = 2;
  if (player_idx == 1) other1_idx = 0, other2_idx = 2;
  if (player_idx == 2) other1_idx = 0, other2_idx = 1;
  cin.ignore();
  cin >> nb_games;
  cin.ignore();
}

int main() {
  int nb_games;
  initialInput(nb_games);
  // 初期処理
  calcSkatingDp();
  RaceState raceState;
  SkatingState SkatingState;
  vector<vector<string>> actions(10);
  actions[0] = {"U", "L", "D", "R"};
  for (int i = 1; i < 10; i++) {
    for (auto s : actions[i - 1]) {
      rep(j, 4) {
        s.push_back(action[j]);
        actions[i].push_back(s);
        s.pop_back();
      }
    }
  }

  vector<vector<int>> scores(3, vector<int>(13));
  // game loop
  int turn = 0;
  ll END_TURN = 1e18;
  // ll END_TURN = 10;
  while (++turn < END_TURN) {
    rep(i, 3) {
      rep(j, 13) cin >> scores[i][j];
      // getline(cin, score_info);
      // scores[i] = score_info;
      // cerr << i << " " << score_info << endl;
    }

    vector<string> gpus(nb_games);
    vector regs(nb_games, vector(7, 0));
    rep(i, nb_games) {
      cin >> gpus[i];
      rep(j, 7) cin >> regs[i][j];
    }
    cin.ignore();
    // レース開始時にdpテーブルをリセットする
    if (regs[0][player_idx] == 0) raceState.reset(gpus[0]);

    // 最大あと何ターンで次のゲームが始まるか
    int lookTurn = 7;
    rep(i, 4) if (gpus[i] == "GAME_OVER") lookTurn = 1;
    if (lookTurn > 1) {
      rep(i, 3) {
        chmin(lookTurn, 1 + raceState.dp[regs[0][i]] + regs[0][3 + i]);
      }
      chmin(lookTurn, 1 + (int)gpus[1].size());
      chmin(lookTurn, 1 + regs[2][6]);
      chmin(lookTurn, 1 + (int)gpus[3].size());
    }
    // cerr << raceState.dp[regs[0][player_idx]] + regs[0][3 + player_idx] <<
    // "
    // "
    //      << gpus[1].size() << " " << regs[2][6] << " " << gpus[3].size()
    //      << endl;
    // cerr << gpus[1] << endl;
    // cerr << gpus[3] << endl;
    cerr << "lookturn: " << lookTurn << endl;

    // ミニゲームごとの係数
    // vi miniGameCoefficient = calcMiniGameCoefficient(scores);
    vi miniGameCoefficient(4, 1);
    // for debug
    // miniGameCoefficient[3] = 100;

    // evaluateScore[i][j] := i個目の競技のj個目の行動のスコア
    vector evaluateScore(4, vector(pow(4, lookTurn), 0));
    rep(i, 4) {
      cerr << "game:" << i << endl;
      // if (gpus[i] == "GAME_OVER") continue;
      if (i == 0)
        evaluateScore[i] = haudleRace(gpus[i], regs[i], turn, raceState,
                                      lookTurn, actions[lookTurn - 1]);
      if (i == 1)
        evaluateScore[i] =
            archery(gpus[i], regs[i], turn, lookTurn, actions[lookTurn - 1]);
      if (i == 2)
        evaluateScore[i] = skating(gpus[i], regs[i], turn, SkatingState,
                                   lookTurn, actions[lookTurn - 1]);
      if (i == 3)
        evaluateScore[i] =
            diving(gpus[i], regs[i], turn, lookTurn, actions[lookTurn - 1]);
    }

    {
      // デバッグのために1つの競技に特化した場合の動きを見る
      // miniGameCoefficient[3] = 1000;
    }

    int mx = -1, move = -1;
    vi moveCount(4);
    rep(i, actions[lookTurn - 1].size()) {
      int score = 0;
      rep(j, 4) score += evaluateScore[j][i] * miniGameCoefficient[j];
      if (mx <= score) {
        if (chmax(mx, score)) rep(j, 4) moveCount[j] = 0;
        if (actions[lookTurn - 1][i][0] == 'U') moveCount[0]++;
        if (actions[lookTurn - 1][i][0] == 'L') moveCount[1]++;
        if (actions[lookTurn - 1][i][0] == 'D') moveCount[2]++;
        if (actions[lookTurn - 1][i][0] == 'R') moveCount[3]++;
      }
      // cerr << actions[lookTurn - 1][i] << " " << score << " "
      //      << evaluateScore[0][i] << " " << evaluateScore[1][i] << " "
      //      << evaluateScore[2][i] << " " << evaluateScore[3][i] << endl;
    }
    mx = 0;
    rep(i, 4) if (chmax(mx, moveCount[i])) move = i;

    rep(i, 4) cerr << "moveCount: " << moveCount[i] << endl;

    cerr << "move: " << move << " mx: " << mx << endl;

    if (move == UP) cout << "UP" << endl;
    if (move == LEFT) cout << "LEFT" << endl;
    if (move == DOWN) cout << "DOWN" << endl;
    if (move == RIGHT) cout << "RIGHT" << endl;
  }
}