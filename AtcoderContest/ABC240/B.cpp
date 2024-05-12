#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INTFY (1 << 29)

int main() {
  int n;
  cin >> n;
  set<int> kind;
  int a;
  rep(i, n) {
    cin >> a;
    kind.insert(a);
  }
  cout << kind.size() << endl;

  return 0;
}