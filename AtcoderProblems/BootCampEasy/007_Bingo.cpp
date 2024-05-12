#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  vector<vector<int> > A(3, vector<int>(3));
  rep(i, 3) rep(j, 3) cin >> A[i][j];
  int n;
  cin >> n;
  // チェックされたやつ
  vector<vector<bool> > bingo(3, vector<bool>(3, false));
  int m;
  rep(i, n) {
    cin >> m;
    rep(j, 3) rep(k, 3) {
      if (A[j][k] == m) bingo[j][k] = true;
    }
  }

  if (bingo[0][0] && bingo[0][1] && bingo[0][2])
    cout << "Yes" << endl;
  else if (bingo[1][0] && bingo[1][1] && bingo[1][2])
    cout << "Yes" << endl;
  else if (bingo[2][0] && bingo[2][1] && bingo[2][2])
    cout << "Yes" << endl;
  else if (bingo[0][0] && bingo[1][0] && bingo[2][0])
    cout << "Yes" << endl;
  else if (bingo[0][1] && bingo[1][1] && bingo[2][1])
    cout << "Yes" << endl;
  else if (bingo[0][2] && bingo[1][2] && bingo[2][2])
    cout << "Yes" << endl;
  else if (bingo[0][0] && bingo[1][1] && bingo[2][2])
    cout << "Yes" << endl;
  else if (bingo[0][2] && bingo[1][1] && bingo[2][0])
    cout << "Yes" << endl;
  else
    cout << "No" << endl;

  return 0;
}