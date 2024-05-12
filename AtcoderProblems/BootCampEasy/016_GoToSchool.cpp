#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

bool myCompare(pair<int, int> a, pair<int, int> b) { return a.first < b.first; }

int main() {
  int n;
  cin >> n;
  // 登校順と出席番号のペア
  vector<pair<int, int>> A(n + 1);
  int num;
  pair<int, int> p;
  A[0] = pair<int, int>(-1, 0);
  rep(i, n) {
    cin >> num;
    p.first = num + 1;
    p.second = i + 1;
    A[i + 1] = p;
  }
  sort(A.begin(), A.end(), myCompare);

  for (int i = 1; i <= n; i++) {
    cout << A[i].second << " ";
  }
  cout << endl;

  return 0;
}