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
  vector<double> v(n);
  rep(i, n) cin >> v[i];

  sort(v.begin(), v.end(), greater<double>());

  double compound;
  rep(i, n - 1) {
    compound = (v[n - i - 2] + v[n - i - 1]) / 2;

    v.pop_back();
    v.pop_back();
    v.push_back(compound);
  }
  cout << v[0] << endl;

  return 0;
}