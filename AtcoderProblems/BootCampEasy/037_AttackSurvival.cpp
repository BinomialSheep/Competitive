#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, k, q;
  cin >> n >> k >> q;
  // 0-origin
  vector<int> A(q);
  rep(i, q) cin >> A[i];

  // qラウンド終了時の得点
  vector<int> score(n, k - q);
  rep(i, q) score[--A[i]]++;

  rep(i, n) cout << (score[i] > 0 ? "Yes" : "No") << endl;

  return 0;
}