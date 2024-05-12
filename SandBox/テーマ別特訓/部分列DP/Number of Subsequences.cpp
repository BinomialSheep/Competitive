#include <bits/stdc++.h>
using namespace std;

// https://judge.yosupo.jp/problem/number_of_subsequences
// 部分列DP。累積和を貰うDPで遷移を高速化する
int main() {
  /* input */
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  const int MOD = 998244353;
  /* solve */
  vector<int> dp(N + 1);
  dp[0] = 1;
  vector<int> sum(N + 1);
  sum[0] = 1;

  map<int, int> last;
  for (int i = 1; i <= N; i++) {
    int left = sum[i - 1] + MOD;
    int right = (last.count(A[i - 1]) ? sum[last[A[i - 1]] - 1] : 0);

    dp[i] = (left - right) % MOD;
    sum[i] = (sum[i - 1] + dp[i]) % MOD;
    last[A[i - 1]] = i;
  }

  /* output */
  cout << sum[N] - 1 << endl;

  return 0;
}
