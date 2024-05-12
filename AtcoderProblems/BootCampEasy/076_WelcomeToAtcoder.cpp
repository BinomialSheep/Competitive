#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  int n, m;
  cin >> n >> m;
  int p;
  string s;

  vector<bool> isAC(n, false);
  vector<int> numWA(n, 0);

  rep(i, m) {
    cin >> p >> s;
    if (s == "AC") {
      isAC[p - 1] = true;
    } else {
      if (!isAC[p - 1]) numWA[p - 1]++;
    }
  }

  int ansAC = 0;
  int ansWA = 0;
  rep(i, n) {
    if (isAC[i]) {
      ansAC++;
      ansWA += numWA[i];
    }
  }
  cout << ansAC << " " << ansWA << endl;

  return 0;
}