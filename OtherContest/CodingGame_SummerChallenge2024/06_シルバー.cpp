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

struct RaceState {
  vector<int> dp;
  RaceState(){};

  void reset(string gpu) {
    dp.resize(35);
    rep(i, 30) dp[i] = 1e9;
    for (int i = 29; i < 35; i++) dp[i] = 0;
    for (int i = 28; i >= 0; i--) {
      // LEFT
      chmin(dp[i], dp[i + 1] + 1);
      // UP
      if (i == 28) {
        chmin(dp[i], dp[i + 1] + 1);
      } else {
        chmin(dp[i], dp[i + 2] + 1);
      }
      // DOWN
      if (gpu[i + 1] == '#' || i == 28) {
        chmin(dp[i], dp[i + 1] + 1);
      } else {
        chmin(dp[i], dp[i + 2] + 1);
      }
      // RIGHT
      if (gpu[i + 1] == '#' || i == 28) {
        chmin(dp[i], dp[i + 1] + 1);
      } else if (gpu[i + 2] == '#' || i == 27) {
        chmin(dp[i], dp[i + 2] + 1);
      } else {
        chmin(dp[i], dp[i + 3] + 1);
      }
      // スタン
      if (gpu[i] == '#') dp[i] += 2;
    }
  }

  void print() {
    cerr << "RaceState: ";
    rep(i, 30) cerr << dp[i] << " ";
    cerr << endl;
  }
};

// dp[i][j] := 残りiターン、リスクjから何マス進めるか
vector skatingDP(16, vector(6, 0));
void calcSkatingDp() {
  for (int i = 1; i < 16; i++) {
    // スタンからの回復
    if (i >= 2) chmax(skatingDP[i][5], skatingDP[i - 2][0]);
    rep(j, 5) {
      // move1: 1スペース前進し、リスクは1減少します
      chmax(skatingDP[i][j], skatingDP[i - 1][max(0, j - 1)] + 1);
      // move2: 2スペース前進し、リスクは変化しません
      chmax(skatingDP[i][j], skatingDP[i - 1][j] + 2);
      // move3: 2スペース前進し、リスクは1増加します
      chmax(skatingDP[i][j], skatingDP[i - 1][min(5, j + 1)] + 2);
      // move4: 3スペース前進し、リスクは2増加します
      chmax(skatingDP[i][j], skatingDP[i - 1][min(5, j + 2)] + 3);
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

vi haudleRace(string& gpu, vi& reg, int nowTurn, RaceState& state) {
  // レース開始時にdpテーブルをリセットする
  if (reg[player_idx] == 0) state.reset(gpu);

  vi ret(4);
  // スタン中ならどうでもいい
  if (reg[3 + player_idx]) return ret;

  int playerBest = state.dp[reg[player_idx]];
  int other1Best = state.dp[reg[other1_idx]] - reg[3 + other1_idx];
  int other2Best = state.dp[reg[other2_idx]] - reg[3 + other2_idx];
  int playerSecond = state.dp[reg[player_idx] + 1] + 1;
  chmax(playerSecond, state.dp[reg[player_idx] + 2]);
  chmax(playerSecond, state.dp[reg[player_idx] + 3]);

  // 終わらないならどうでもいい
  int turnLest = 100 - nowTurn + 1;
  cerr << "race: " << turnLest << " " << playerBest << " " << other1Best << " "
       << other2Best << " " << playerSecond << endl;
  if (turnLest < playerBest && turnLest < other1Best && turnLest < other2Best)
    return ret;

  int pos = reg[player_idx];
  gpu += ".....";
  if (gpu[pos + 1] == '#') {
    // ジャンプできるならする
    ret[UP] = 40;
  } else if (gpu[pos + 2] == '#') {
    // 1マス移動
    ret[LEFT] = 40;
  } else if (gpu[pos + 3] == '#') {
    // 2マス移動できるならする
    ret[UP] = ret[DOWN] = 40;
    // 強いていえば1マス移動したい
    ret[LEFT] = 5;
  } else {
    // ゴール直前はなんでもいい
    if (pos == 28) {
    } else if (pos == 27) {
      ret[RIGHT] = ret[UP] = ret[DOWN] = 40;
    } else {
      ret[RIGHT] = 40;
      ret[UP] = ret[DOWN] = 10;
    }
  }

  // 自分がベストを尽くせばメダルが取れる
  if (playerBest <= other1Best && playerBest <= other2Best) {
    // 自分が手抜いても1人勝ちなら評価低め
    if (playerSecond < other1Best && playerSecond < other2Best) {
      rep(i, 4) ret[i] /= 10;
    } else {
      // 本気を出したい
    }
  } else if (playerBest <= other1Best || playerBest <= other2Best) {
    // 銀メダルは取れる
    rep(i, 4) ret[i] /= 5;
  } else {
    // 相手のミス待ち
    rep(i, 4) ret[i] /= 10;
  }

  rep(i, 4) cerr << "haudleRace Ret: " << ret[i] << endl;
  return ret;
}

vi archery(string& gpu, vi& reg, int nowTurn) {
  int x = reg[player_idx * 2], y = reg[player_idx * 2 + 1];
  cerr << "gpu: " << gpu << ", x: " << x << ", y: " << y << endl;

  vi ret(4);

  // 100ターン経過まで終わらないならどうでもいい
  if (100 - nowTurn + 1 < (int)gpu.size()) return ret;

  vi mnScore(4, 1e9);

  if (gpu.size() <= 1) {
    int v = gpu[0] - '0';
    mnScore[UP] = abs(x) + abs(y - v);
    mnScore[LEFT] = abs(x - v) + abs(y);
    mnScore[DOWN] = abs(x) + abs(y + v);
    mnScore[RIGHT] = abs(x + v) + abs(y);
  } else {
    set<pair<int, int>> st;
    st.emplace(x, y);
    for (int i = 1; i < min((int)gpu.size(), 20); i++) {
      set<pair<int, int>> st2;
      int v = gpu[i] - '0';
      for (auto [x2, y2] : st) {
        st2.emplace(min(20, x2 + v), y2);
        st2.emplace(max(-20, x2 - v), y2);
        st2.emplace(x2, min(20, y2 + v));
        st2.emplace(x2, max(-20, y2 - v));
      }
      swap(st, st2);
    }

    int v = gpu[0] - '0';
    for (auto [x2, y2] : st) {
      chmin(mnScore[UP], abs(x2) + abs(max(-20, y2 - v)));
      chmin(mnScore[LEFT], abs(max(x2 - v, -20)) + abs(y2));
      chmin(mnScore[DOWN], abs(x2) + abs(min(y2 + v, 20)));
      chmin(mnScore[RIGHT], abs(min(20, x2 + v)) + abs(y2));
    }
  }
  vector<pair<int, int>> vec;
  rep(i, 4) vec.emplace_back(mnScore[i], i);
  sort(all(vec));
  ret[vec[0].second] = 40;
  for (int i = 1; i < 4; i++) {
    if (vec[i].first == vec[i - 1].first) {
      ret[vec[i].second] = ret[vec[i - 1].second];
    } else {
      ret[vec[i].second] = ret[vec[i - 1].second] / 10;
    }
  }

  rep(i, 4) cerr << "archery Ret: " << ret[i] << endl;

  return ret;
}

vi rollerSpeedSkating(string& gpu, vi& reg, int nowTurn) {
  vi ret(4);
  if (nowTurn >= 95) return ret;
  // スタン中ならどうでもいい
  if (reg[3 + player_idx] < 0) return ret;

  vi move(4);
  rep(i, 4) {
    if (gpu[i] == 'U') move[i] = UP;
    if (gpu[i] == 'L') move[i] = LEFT;
    if (gpu[i] == 'D') move[i] = DOWN;
    if (gpu[i] == 'R') move[i] = RIGHT;
  }

  // 最終ターンはmoveが大きいほどいい
  if (reg[6] == 1) {
    ret[move[0]] = 10;
    ret[move[1]] = 20;
    ret[move[2]] = 30;
    ret[move[3]] = 40;
    return ret;
  }

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
  // いい行動順に並べる
  vector<int> priorityMove(4);
  rep(i, 4) priorityMove[i] = i;
  auto f = [&](int v) -> int {
    if (v == 0) return skatingDP[reg[6] - 1][max(0, reg[player_idx] - 1)] + 1;
    if (v == 1) return skatingDP[reg[6] - 1][reg[player_idx]] + 2;
    if (v == 2) return skatingDP[reg[6] - 1][min(5, reg[player_idx] + 1)] + 2;
    if (v == 3) return skatingDP[reg[6] - 1][min(5, reg[player_idx] + 2)] + 3;
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

  rep(i, 4) ret[move[priorityMove[i]]] = 40 - i * 10;

  return ret;
}

vi diving(string& gpu, vi& reg, int nowTurn) {
  vi ret(4);

  // 100ターン経過まで終わらないならどうでもいい
  if (100 - nowTurn + 1 < (int)gpu.size()) return ret;

  int correctIdx = 0;
  if (gpu[0] == 'U') correctIdx = 0;
  if (gpu[0] == 'L') correctIdx = 1;
  if (gpu[0] == 'D') correctIdx = 2;
  if (gpu[0] == 'R') correctIdx = 3;

  // 最善を尽くした場合に得られるポイント
  auto f = [&](int turnLeft, int points, int combo) {
    return points + turnLeft * (2 * combo + turnLeft - 1) / 2;
  };

  int turnLeft = (int)gpu.size();
  int playerBest = f(turnLeft, reg[player_idx], reg[player_idx + 3]);
  int other1Best = f(turnLeft, reg[other1_idx], reg[other1_idx + 3]);
  int other2Best = f(turnLeft, reg[other2_idx], reg[other2_idx + 3]);
  int playerSecond = f(turnLeft - 1, reg[player_idx], 1);
  // 自分がベストを尽くせばメダルが取れる
  if (playerBest >= other1Best && playerBest >= other2Best) {
    // 自分が手抜いても1人勝ちなら評価低め
    // if (playerSecond > other1Best && playerSecond > other2Best) {
    //   ret[correctIdx] = 1;
    // 自分が以降何もしなくても1人勝ちなら何でもいい
    if (reg[player_idx] > other1Best && reg[player_idx] > other2Best) {
      // 何もしない
    } else {
      ret[correctIdx] = 40;
    }

  } else if (playerBest >= other1Best || playerBest >= other2Best) {
    // 銀メダルは取れる
    ret[correctIdx] = 20;
  } else {
    // 相手のミス待ち
    ret[correctIdx] = 1;
  }

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

    // ミニゲームごとの係数
    vi miniGameCoefficient = calcMiniGameCoefficient(scores);
    // evaluateScore[i][j] := i個目の競技のj個目の行動のスコア
    vector evaluateScore(4, vector(4, 0));
    rep(i, 4) {
      cerr << "game:" << i << endl;
      if (gpus[i] == "GAME_OVER") continue;
      if (i == 0)
        evaluateScore[i] = haudleRace(gpus[i], regs[i], turn, raceState);
      if (i == 1) evaluateScore[i] = archery(gpus[i], regs[i], turn);
      if (i == 2) evaluateScore[i] = rollerSpeedSkating(gpus[i], regs[i], turn);
      if (i == 3) evaluateScore[i] = diving(gpus[i], regs[i], turn);
    }

    {
      // デバッグのために1つの競技に特化した場合の動きを見る
      // miniGameCoefficient[0] = 1000;
    }

    // TODO：とりあえずミニゲーム係数 * 行動評価値を評価関数とする
    vi desicionScore(4);
    rep(i, 4) rep(j, 4) {
      desicionScore[j] += evaluateScore[i][j] * miniGameCoefficient[i];
    }
    int move = -1, mx = -1;
    rep(i, 4) if (chmax(mx, desicionScore[i])) move = i;

    rep(i, 4) {
      cerr << "desicionScore: " << i << ",  " << desicionScore[i] << endl;
    }
    cerr << "move: " << move << endl;

    if (move == UP) cout << "UP" << endl;
    if (move == LEFT) cout << "LEFT" << endl;
    if (move == DOWN) cout << "DOWN" << endl;
    if (move == RIGHT) cout << "RIGHT" << endl;
  }
}