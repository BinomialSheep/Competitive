#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, m, x;
  cin >> n >> m >> x;
  vector<int> A(m);
  rep(i, m) cin >> A[i];

  int index;
  rep(i, m) {
    if (A[i] > x) {
      index = i;
      break;
    }
  }
  // indexの数だけ左にあり、m - indexの数だけ右にある
  cout << min(index, m - index) << endl;

  return 0;
}