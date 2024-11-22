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

void haudleRace(string gpu, vi reg, int mode, set<int>& moveSet) {
  int pos = reg[player_idx];
  gpu += ".....";
  // スタン中ならどうでもいい
  if (reg[3 + player_idx]) return;

  if (gpu[pos + 1] == '#') {
    // ジャンプできるならする
    if (moveSet.count(UP)) {
      moveSet.erase(LEFT);
      moveSet.erase(DOWN);
      moveSet.erase(RIGHT);
    }
  } else if (gpu[pos + 2] == '#') {
    // 1マス移動できるならする
    if (moveSet.count(LEFT)) {
      moveSet.erase(UP);
      moveSet.erase(DOWN);
      moveSet.erase(RIGHT);
    }
  } else if (gpu[pos + 3] == '#') {
    // 2マス移動できるならする
    if (moveSet.count(UP) || moveSet.count(DOWN)) {
      moveSet.erase(LEFT);
      moveSet.erase(RIGHT);
    } else if (moveSet.count(LEFT)) {
      // 強いていえば1マス移動したい
      moveSet.erase(RIGHT);
    }
  } else {
    // TODO：ゴール直前ならなんでもいい
    // 3マス移動できるならする
    if (moveSet.count(RIGHT)) {
      moveSet.erase(UP);
      moveSet.erase(LEFT);
      moveSet.erase(DOWN);
    } else if (moveSet.count(UP) || moveSet.count(DOWN)) {
      moveSet.erase(LEFT);
    }
  }
}

void archery(string gpu, vi reg, int mode, set<int>& moveSet) {
  int x = reg[player_idx * 2], y = reg[player_idx * 2 + 1];

  // TODO：DP復元する
  int score = 1e9;
  int move = -1;
  for (auto v : moveSet) {
    if (v == UP && chmin(score, abs(x) + abs(y + gpu[0]))) move = UP;
    if (v == LEFT && chmin(score, abs(x - gpu[0]) + abs(y))) move = LEFT;
    if (v == DOWN && chmin(score, abs(x) + abs(y - gpu[0]))) move = DOWN;
    if (v == RIGHT && chmin(score, abs(x + gpu[0]) + abs(y))) move = RIGHT;
  }
  rep(i, 4) if (move != i) moveSet.erase(i);
}

void rollerSpeedSkating(string gpu, vi reg, int mode, set<int>& moveSet) {
  vi ret(4);
  // スタン中ならどうでもいい
  if (reg[3 + player_idx] < 0) return;

  vi move(4);
  rep(i, 4) {
    if (gpu[i] == 'U') move[i] = UP;
    if (gpu[i] == 'L') move[i] = LEFT;
    if (gpu[i] == 'D') move[i] = DOWN;
    if (gpu[i] == 'R') move[i] = RIGHT;
  }

  if (reg[6] == 1) {
    if (moveSet.count(move[3])) {
      moveSet.erase(move[0]);
      moveSet.erase(move[1]);
      moveSet.erase(move[2]);
    } else if (moveSet.count(move[1]) || moveSet.count(move[2])) {
      moveSet.erase(move[0]);
    }
  } else if (reg[3 + player_idx] == 0) {
    if (moveSet.count(move[1]) || moveSet.count(move[2])) {
      moveSet.erase(move[0]);
      moveSet.erase(move[3]);
    } else if (moveSet.count(move[3])) {
      moveSet.erase(move[0]);
    }
  } else if (reg[3 + player_idx] == 4) {
    if (moveSet.count(move[0])) {
      moveSet.erase(move[1]);
      moveSet.erase(move[2]);
      moveSet.erase(move[3]);
    } else if (moveSet.count(move[3])) {
      moveSet.erase(move[1]);
      moveSet.erase(move[2]);
    }
  } else {
    if (moveSet.size() >= 2 && moveSet.count(move[3])) {
      moveSet.count(move[3]);
    }
  }
}

void diving(string gpu, vi reg, int mode, set<int>& moveSet) {
  vi ret(4, -1);

  if (gpu[0] == 'U' && moveSet.count(UP)) {
    moveSet.erase(LEFT);
    moveSet.erase(DOWN);
    moveSet.erase(RIGHT);
  }
  if (gpu[0] == 'L' && moveSet.count(LEFT)) {
    moveSet.erase(UP);
    moveSet.erase(DOWN);
    moveSet.erase(RIGHT);
  }
  if (gpu[0] == 'D' && moveSet.count(DOWN)) {
    moveSet.erase(UP);
    moveSet.erase(LEFT);
    moveSet.erase(RIGHT);
  }
  if (gpu[0] == 'R' && moveSet.count(RIGHT)) {
    moveSet.erase(UP);
    moveSet.erase(LEFT);
    moveSet.erase(DOWN);
  }
}
// 取れる順位の判定 20：取れる　10：微妙　0：無理
vi calcPossibleRank(vector<string> gpus, vector<vector<int>> regs) {
  vi ret(4);

  auto possibleHurdle = [&]() {
    string gpu = gpus[0];
    gpu += ".....";
    vi reg = regs[0];
    // それぞれ何ターンでゴール可能か判定する
    vi turns(3);
    rep(i, 3) {
      // スタン
      turns[i] += reg[3 + i];
      int t = 0;
      int j = reg[i];
      while (j < 29) {
        t++;
        if (reg[i + 1] == '#') {
          j += 2;
        } else if (reg[i + 2] == '#') {
          j += 1;
        } else if (reg[i + 3] == '#') {
          j += 2;
        } else {
          j += 3;
        }
      }
      turns[i] = t;
    }
    if (turns[player_idx] <= turns[other1_idx] &&
        turns[player_idx] <= turns[other2_idx])
      return 20;
    if (turns[player_idx] > turns[other1_idx] &&
        turns[player_idx] > turns[other2_idx])
      return 0;
    return 10;
  };
  auto possibleArchery = [&]() {
    string gpu = gpus[1];
    vi reg = regs[1];

    set<pair<int, int>> st;
    st.emplace(0, 0);
    int turn = 0;
    for (auto c : gpu) {
      if (++turn > 5) break;
      set<pair<int, int>> st2;
      int v = c - '0';
      for (auto [x, y] : st) {
        st2.emplace(x + v, y);
        st2.emplace(x - v, y);
        st2.emplace(x, y + x);
        st2.emplace(x, y - x);
      }
      swap(st, st2);
    }
    vi scores(3, 1e9);
    for (auto [x, y] : st) {
      rep(i, 3) {
        int score = abs(reg[i * 2] + x) + abs(reg[2 * i + 1] + y);
        chmin(scores[i], score);
      }
    }
    if (scores[player_idx] <= scores[other1_idx] &&
        scores[player_idx] <= scores[other2_idx])
      return 20;
    if (scores[player_idx] > scores[other1_idx] &&
        scores[player_idx] > scores[other2_idx])
      return 0;
    return 10;
  };

  auto possibleDiving = [&]() {
    string gpu = gpus[3];
    vi reg = regs[3];
    vi scores(3);
    rep(i, 3) scores[i] += reg[0];
    rep(i, 3) {
      // 初項reg[3 + i], 項数gpu.size(), 項差1の等差数列
      scores[i] += (int)gpu.size() * (2 * reg[3 + i] + (int)gpu.size() - 1) / 2;
    }
    if (scores[player_idx] >= scores[other1_idx] &&
        scores[player_idx] >= scores[other2_idx])
      return 20;
    if (scores[player_idx] < scores[other1_idx] &&
        scores[player_idx] < scores[other2_idx])
      return 0;
    return 10;
  };

  rep(i, 4) {
    if (gpus[i] == "GAME_OVER") continue;
    // ハードル走
    if (i == 0) ret[i] = possibleHurdle();
    // アーチェリー
    if (i == 1) ret[i] = possibleArchery();
    // スケートは知らない
    if (i == 2) ret[i] = 10;
    // ダイビングはスコアとコンボで決まる
    if (i == 3) ret[i] = possibleDiving();
  }
  return ret;
}

// 30：絶対取る 20：できれば取る 10：取れたら取る 0：無理
vi calcModes(vector<string> scores, vi possibleRank) {
  vi ret(4);

  // これまでのメダルに応じて係数を掛ける
  vector<pair<int, int>> nowScore(4);
  rep(i, 4) {
    nowScore[i].first =
        scores[player_idx][3 * 4 + 1] * 3 + scores[player_idx][3 * 4 + 2];
    nowScore[i].second = i;
  }
  sort(nowScore.begin(), nowScore.end());
  vector<int> coefficient(4, 40);
  for (int i = 1; i < 4; i++) {
    if (nowScore[i].first > nowScore[i - 1].second) {
      coefficient[nowScore[i].second] =
          coefficient[nowScore[i].second - 1] - 10;
    } else {
      coefficient[nowScore[i].second] = coefficient[nowScore[i].second - 1];
    }
  }
  //
  map<int, vector<int>> mp;
  rep(i, 4) mp[possibleRank[i]].push_back(i);
  // 最優先を決める
  rep(i, 4) {
    if (coefficient[i] == 40 && possibleRank[i] == 20) {
      ret[i] = 30;
      break;
    }
  }
  rep(i, 4) {
    if (possibleRank[i] == 20 && ret[i] != 30) ret[i] = 20;
    if (possibleRank[i] == 10) ret[i] = 10;
  }
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

  vector<string> scores(3);
  // game loop
  int turn = 0;
  ll END_TURN = 1e18;
  // ll END_TURN = 10;
  while (++turn < END_TURN) {
    rep(i, 3) {
      string score_info;
      getline(cin, score_info);
      scores[i] = score_info;
    }

    vector<string> gpus(nb_games);
    vector regs(nb_games, vector(7, 0));
    rep(i, nb_games) {
      cin >> gpus[i];
      rep(j, 7) cin >> regs[i][j];
    }
    cin.ignore();

    // 絶対1位を取るのか、できるだけ頑張るのか、頑張らないか
    vi possibleRank = calcPossibleRank(gpus, regs);

    // 取りに行くか設定 30：絶対取る 20：できれば取る 10：取れたら取る 0：無理
    vi modes = calcModes(scores, possibleRank);
    rep(i, 4) cerr << i << " " << possibleRank[i] << " " << modes[i] << endl;

    // 優先度順に動きを確定させる
    // TODO タイブレークならすぐ入るメダルを優先？
    vector<pair<int, int>> ps;
    rep(i, 4) ps.emplace_back(modes[i], i);
    sort(ps.rbegin(), ps.rend());
    set<int> moveSet = {UP, LEFT, DOWN, RIGHT};
    for (auto [mode, idx] : ps) {
      if (gpus[idx] == "GAME_OVER") continue;

      if (idx == 0) haudleRace(gpus[idx], regs[idx], mode, moveSet);
      if (idx == 1) archery(gpus[idx], regs[idx], mode, moveSet);
      if (idx == 2) rollerSpeedSkating(gpus[idx], regs[idx], mode, moveSet);
      if (idx == 3) diving(gpus[idx], regs[idx], mode, moveSet);
    }

    assert(moveSet.size());
    auto move = *(moveSet.begin());
    if (move == UP) cout << "UP" << endl;
    if (move == LEFT) cout << "LEFT" << endl;
    if (move == DOWN) cout << "DOWN" << endl;
    if (move == RIGHT) cout << "RIGHT" << endl;
  }
}