#include <bits/stdc++.h>
using namespace std;

int main() {
  int K, N;
  cin >> K >> N;

  // dp[i-1] := i個の卵を落とした時に試せる階数
  vector dp(K, 1);

  for (int j = 1; j < N; j++) {
    vector ndp(K, 0);
    ndp[0] = j + 1;
    for (int i = 1; i < K; i++) {
      ndp[i] = 1 + dp[i] + dp[i - 1];
    }
    swap(dp, ndp);
    if (dp[K - 1] >= N) {
      cout << j + 1 << endl;
      break;
    }
  }

  return 0;
}
