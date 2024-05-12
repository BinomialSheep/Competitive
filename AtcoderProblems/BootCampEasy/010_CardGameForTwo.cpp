#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, n) cin >> a[i];
  // 降順にソート
  sort(a.begin(), a.end(), greater<int>{});

  int aliceScore = 0;
  int bobScore = 0;
  rep(i, n) {
    if (i % 2 == 0)
      aliceScore += a[i];
    else
      bobScore += a[i];
  }
  cout << aliceScore - bobScore << endl;


  return 0;
}