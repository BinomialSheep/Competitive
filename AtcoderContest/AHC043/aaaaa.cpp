#include <bits/stdc++.h>
using namespace std;

int predict_turn_naive(int money, int earn, int track_count) {
  int ret = 0;
  // 線路を track_count 本建設
  for (int i = 0; i < track_count; i++) {
    // お金が 100 円に足りるまで待機
    while (money < 100) {
      ret++;
      money += earn;
    }
    // 線路建設
    money -= 100;
    ret++;
    money += earn;
  }
  // 駅を 1つ 建設
  while (money < 5000) {
    ret++;
    money += earn;
  }
  money -= 5000;
  ret++;
  money += earn;
  return ret;
}


int waitTurns(int have, int cost, int earn) {

}

// O(1) で最小ターンを予測
int predict_turn_fast(int money, int earn, int track_count) {
  // まず「線路 track_count 本を連続で建設するための待機ターン」を x とする
  int x = 0;
  if (earn >= 100) {
    // 1本目を建てるのに必要な 100 円を満たすまで待つだけ
    x = waitTurns(money, 100, earn);
  } else {
    // earn < 100
    // track_count 本を連続で建てきるのに必要な初期所持金
    //   = 100 * track_count - (track_count - 1) * earn
    int need = 100 * track_count - (track_count - 1) * earn;
    x = waitTurns(money, need, earn);
  }

  // x ターン待機後に所持金はいくらか
  int afterWait = money + x * earn;

  // そこから連続で track_count 本建設すると、最終的な所持金は
  //   afterWait + track_count*(earn - 100)
  int M_afterTrack = afterWait + track_count * (earn - 100);

  // 次に駅を建設する前に、5000 円足りない分を待機
  int y = waitTurns(M_afterTrack, 5000, earn);

  // 線路建設トータル = x(待機) + track_count(建設)
  // 駅建設トータル   = y(待機) + 1(建設)
  // 合計
  return (x + track_count) + (y + 1);
}

int main() {
  int money, earn, track_count;
  // 入力例：初期所持金、1ターンあたりの収入、線路建設回数
  cin >> money >> earn >> track_count;

  cout << predict_turn_naive(money, earn, track_count) << endl;
  cout << predict_turn_fast(money, earn, track_count) << endl;
  assert(predict_turn_naive(money, earn, track_count) ==
         predict_turn_fast(money, earn, track_count));

  return 0;
}
