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
  vector<int> A(n);
  rep(i, n) cin >> A[i];
  int first = -1, second = -1;
  rep(i, n) {
    if (first <= A[i]) {
      second = first;
      first = A[i];
    } else {
      second = max(second, A[i]);
    }
  }

  rep(i, n) cout << (A[i] == first ? second : first) << endl;

  return 0;
}