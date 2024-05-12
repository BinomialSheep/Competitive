#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> value(n);
  rep(i, n) {
    cin >> x;
    value[i] = x;
  }

  static const NIL = -1;
  static const ROOT = -2;
  vector<int> parent(n, NIL);
  parent[0] = ROOT;
  list<int> orderdList(n);
  int a, b;
  rep(i, n) { cin >> a >> b; }

  return 0;
}