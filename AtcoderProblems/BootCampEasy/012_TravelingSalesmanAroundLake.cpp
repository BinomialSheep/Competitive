#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int k, n;
  cin >> k >> n;
  vector<int> A(n + 1);
  A[0] = 0;
  rep(i, n) cin >> A[i + 1];

  // ソートして、間隔が最大のところの1つ後からスタートすればいい
  sort(A.begin(), A.end());

  int maxV = 0;
  rep(i, n) maxV = max(maxV, A[i + 1] - A[i]);
  // 1番最後とA[1]の間
  maxV = max(maxV, A[1] + (k - A[n]));

  cout << k - maxV << endl;

  return 0;
}