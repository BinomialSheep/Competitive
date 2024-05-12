#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<long> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  long ans = 0;
  long MOD = 1e8 + 0.0001;

  for (int i = 0; i < N - 1; i++) {
    for (int j = i + 1; j < N; j++) {
      ans += (A[i] + A[j]) % MOD;
    }
  }
  cout << ans << endl;

  return 0;
}