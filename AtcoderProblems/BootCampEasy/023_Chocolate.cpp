#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, d, x;
  cin >> n >> d >> x;
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  rep(i, n) {
    for (int j = 0; 1 + a[i] * j <= d; j++) x++;
  }

  cout << x << endl;

  return 0;
}