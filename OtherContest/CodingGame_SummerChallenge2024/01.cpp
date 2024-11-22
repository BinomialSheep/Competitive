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

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

int main() {
  int player_idx;
  cin >> player_idx;
  assert(0 <= player_idx && player_idx <= 2);
  cerr << player_idx << endl;
  cin.ignore();
  int nb_games;
  cin >> nb_games;
  cin.ignore();

  // game loop
  int turn = 0;
  ll END_TURN = 1e18;
  // ll END_TURN = 10;
  while (++turn < END_TURN) {
    for (int i = 0; i < 3; i++) {
      string score_info;
      getline(cin, score_info);
    }
    vector<string> gpus(nb_games);
    vector regs(nb_games, vector(7, 0));
    rep(i, nb_games) {
      cin >> gpus[i];
      rep(j, 7) cin >> regs[i][j];
    }
    cin.ignore();

    bool mustJump = false;
    bool canStep3 = true;
    bool canStep2 = true;

    rep(i, nb_games) {
      string gpu = gpus[i];
      if (gpu == "GAME_OVER") continue;
      int pos = regs[i][player_idx];
      gpu += ".....";
      if (gpu[pos + 1] == '#') {
        mustJump = true;
      } else if (gpu[pos + 2] == '#') {
        canStep2 = false;
      } else if (gpu[pos + 3] == '#') {
        canStep3 = false;
      }
    }
    if (mustJump) {
      cout << "UP" << endl;
    } else if (canStep3) {
      cout << "RIGHT" << endl;
    } else if (canStep2) {
      cout << "DOWN" << endl;
    } else {
      cout << "LEFT" << endl;
    }
  }
}