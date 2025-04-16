#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

// 繰り返し二乗法でa^b modを求める
long long modpow(long long a, long long b, int m) {
  long long res = 1 % m;
  a %= m;
  while (b > 0) {
    if (b & 1) res = (res * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  // 初期パターン: i番目(1-indexed)は i%2 == 1 ? 1 : 0
  // 端点チェック
  if (A[0] != 1) {
    // マス1は初期1だから1でないと無理
    cout << 0 << "\n";
    return 0;
  }
  int init_last = (N % 2 == 1) ? 1 : 0;  // A_NはN mod 2
  if (A[N - 1] != init_last) {
    cout << 0 << "\n";
    return 0;
  }

  // 内部で異なる箇所をカウント
  int c = 0;
  for (int i = 1; i < N - 1; i++) {
    int init_val =
        ((i + 1) % 2 == 1) ? 1 : 0;  // iは0-basedなのでi+1で1-basedへ
    if (A[i] != init_val) c++;
  }

  if (c == 0) {
    cout << 1 << "\n";
  } else {
    long long ans = modpow(3, c - 1, MOD);
    cout << ans << "\n";
  }

  return 0;
}
