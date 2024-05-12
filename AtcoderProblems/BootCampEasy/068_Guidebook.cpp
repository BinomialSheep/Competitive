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
  int n;
  cin >> n;
  map<string, vector<pair<int, int>>> myMap;
  string s;
  int p;
  rep(i, n) {
    cin >> s >> p;
    myMap[s].push_back(make_pair(-p, i + 1));
  }

  for (auto [key, value] : myMap) {
    sort(value.begin(), value.end());
    for (auto myPair : value) {
      cout << myPair.second << endl;
    }
  }

  return 0;
}