#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
 
typedef long long ll;
 
 
 
 
 
 
int main() {
  int h, w;
  cin >> h >> w;
 
  int A[h][w];
 
  rep(i, h) {
    rep(j, w) {
      cin >> A[i][j];
    }
  }
 
  rep(j, w) {
    rep(i, h - 1) {
      cout << A[i][j] << " ";
    }
    cout << A[h-1][j] << endl;
  }
 
 
  return 0;
}