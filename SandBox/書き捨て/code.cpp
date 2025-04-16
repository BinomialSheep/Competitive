// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//   {
//     // 7種類を1つずつ揃えるまでの期待値
//     vector<double> dp(8);
//     // 配るDP
//     for (int i = 0; i < 7; i++) {
//       /**
//        * 1回回すたびに、確率(7-i)/7で次の1枚が揃い、確率i/7で今と被る
//        * dp[i+1] = dp[i] * p + dp[i+1] * (1-p) + 1
//        * dp[i+1] = dp[i] + 7 / i
//        *  */
//       dp[i + 1] = dp[i] + 7. / (7 - i);
//     }
//     cout << dp[7] << endl;  // 18.15回
//   }
//   {
//     //
//     // dp[i][j] :=
//     //
//     2個揃ったものがi個、1個揃ったものがj個から、7種類を2つずつ揃えるまでの期待値
//     vector dp(8, vector<double>(8));
//     for (int i = 7; i >= 0; i--) {
//       for (int j = 7 - i; j >= 0; j--) {
//         if (i == 7 && j == 0) {
//           // 終了状態
//           dp[7][0] = 0;
//           continue;
//         }
//         // p_k = 今k個のものを引くとして下記漸化式から自己ループを除けばよい
//         // dp[i][j] = 1 + p0*dp[i][j+1] + p1*dp[a+1][b-1] + p2*dp[i][j]
//         dp[i][j] = 1;
//         // 0個揃ったものが1個揃う
//         if (j < 7) dp[i][j] += dp[i][j + 1] * (7 - i - j) / 7;
//         // 1個揃ったものが2個揃う
//         if (i < 7 && j >= 1) dp[i][j] += dp[i + 1][j - 1] * j / 7;
//         // 2個揃ったものが被る
//         dp[i][j] *= 7. / (7 - i);
//       }
//     }
//     cout << dp[0][0] << endl;
//   }
//   return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
  // dp[a][b] :=
  // 2個揃ったものがi個、1個揃ったものがj個から、7種類を2つずつ揃えるまでの期待値
  vector dp(8, vector<double>(8));
  for (int a = 7; a >= 0; a--) {
    for (int b = 7 - a; b >= 0; b--) {
      if (a == 7 && b == 0) {
        dp[7][0] = 0;
        continue;
      }
      double p0 = (7 - a - b) / 7., p1 = b / 7., p2 = a / 7.;
      dp[a][b] = 1;
      // 0個揃ったものが1個揃う
      if (b < 7) dp[a][b] += p0 * dp[a][b + 1];
      // 1個揃ったものが2個揃う
      if (a < 7 && b >= 1) dp[a][b] += p1 * dp[a + 1][b - 1];
      // 2個揃ったものが被る
      dp[a][b] /= 1 - p2;
    }
  }
  cout << dp[0][0] << endl;
  return 0;
}