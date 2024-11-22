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

int player_idx;
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

vi haudleRace(string gpu, vi reg) {
  int pos = reg[player_idx];
  gpu += ".....";
  vi ret(4);
  // スタン中ならどうでもいい
  if (reg[3 + player_idx]) return ret;
  if (gpu[pos + 1] == '#') {
    ret[0] = 10;
    ret[1] = ret[2] = ret[3] = -10;
  } else if (gpu[pos + 2] == '#') {
    ret[1] = 10;
    ret[0] = ret[2] = ret[3] = -10;
  } else if (gpu[pos + 3] == '#') {
    ret[0] = ret[2] = 5;
    ret[1] = 1;
    ret[3] = -9;
  } else {
    ret[1] = 1;
    ret[2] = ret[0] = 5;
    ret[3] = 10;
    // TODO：ゴール直前なら評価は変わらないが
  }
  return ret;
}

vi archery(string gpu, vi reg) {
  vi ret(4);

  int x = reg[player_idx * 2], y = reg[player_idx * 2 + 1];

  ret[UP] = abs(y + gpu[0]) - abs(y);
  ret[LEFT] = abs(x - gpu[0]) - abs(x);
  ret[DOWN] = abs(y - gpu[0]) - abs(y);
  ret[RIGHT] = abs(x + gpu[0]) - abs(x);
  return ret;
}

vi rollerSpeedSkating(string gpu, vi reg) {
  vi ret(4);
  // スタン中ならどうでもいい
  if (reg[3 + player_idx] < 0) return ret;

  vi move(4);
  rep(i, 4) {
    if (gpu[i] == 'U') move[i] = UP;
    if (gpu[i] == 'L') move[i] = LEFT;
    if (gpu[i] == 'D') move[i] = DOWN;
    if (gpu[i] == 'R') move[i] = RIGHT;
  }

  if (reg[6] == 1) {
    ret[move[0]] = 1;
    ret[move[1]] = ret[move[2]] = 2;
    ret[move[3]] = 3;
  } else if (reg[3 + player_idx] == 0) {
    ret[move[0]] = 1;
    ret[move[1]] = ret[move[2]] = 3;
    ret[move[3]] = 2;
  } else if (reg[3 + player_idx] == 4) {
    ret[move[0]] = 3;
    ret[move[1]] = ret[move[2]] = 1;
    ret[move[3]] = 2;
  } else {
    ret[move[0]] = 2;
    ret[move[1]] = ret[move[2]] = 2;
    ret[move[3]] = 1;
  }

  return ret;
}

vi diving(string gpu, vi reg) {
  vi ret(4, -1);

  if (gpu[0] == 'U') ret[UP] = 1;
  if (gpu[0] == 'L') ret[LEFT] = 1;
  if (gpu[0] == 'D') ret[DOWN] = 1;
  if (gpu[0] == 'R') ret[RIGHT] = 1;

  return ret;
}

int main() {
  cin >> player_idx;
  assert(0 <= player_idx && player_idx <= 2);
  cerr << player_idx << endl;
  cin.ignore();
  int nb_games;
  cin >> nb_games;
  cin.ignore();

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

    cerr << scores[player_idx] << endl;
    vector<string> gpus(nb_games);
    vector regs(nb_games, vector(7, 0));
    rep(i, nb_games) {
      cin >> gpus[i];
      rep(j, 7) cin >> regs[i][j];
    }
    cin.ignore();

    vector evaluationValues(4, vector(4, 0));
    rep(i, nb_games) {
      string gpu = gpus[i];
      if (gpu == "GAME_OVER") continue;

      if (i == 0) evaluationValues[i] = haudleRace(gpus[i], regs[i]);
      if (i == 1) evaluationValues[i] = archery(gpus[i], regs[i]);
      if (i == 2) evaluationValues[i] = rollerSpeedSkating(gpus[i], regs[i]);
      if (i == 3) evaluationValues[i] = diving(gpus[i], regs[i]);
    }
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

    int mx = 0, move = -1;
    rep(j, 4) {
      int now = 0;
      rep(i, 4) now += coefficient[i] * evaluationValues[i][j];
      if (chmax(mx, now)) move = j;
    }
    if (move == UP) cout << "UP" << endl;
    if (move == LEFT) cout << "LEFT" << endl;
    if (move == DOWN) cout << "DOWN" << endl;
    if (move == RIGHT) cout << "RIGHT" << endl;
  }
}