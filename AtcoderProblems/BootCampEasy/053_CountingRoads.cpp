#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> count(n, 0);
  int a, b;
  rep(i, m) {
    cin >> a >> b;
    count[--a]++;
    count[--b]++;
  }

  rep(i, n) cout << count[i] << endl;

  return 0;
}