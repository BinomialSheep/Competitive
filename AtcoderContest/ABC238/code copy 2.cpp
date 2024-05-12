#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
typedef long long ll;

int main() {
  int n;
  cin >> n;
  int A[n];
  rep(i, n) cin >> A[i];

  int B[360];
  rep(i, 360) B[i] = false;
  int top = 0;
  B[top] = true;

  rep(i, n) {
    top += A[i];
    top %= 360;
    B[top] = true;
  }

  int ans = 0;
  int length = 0;
  rep(i, 360) {
    if (B[i]) {
      ans = max(ans, length + 1);
      length = 0;
    } else if (i == 359) {
      ans = max(ans, length + 2);
    } else {
      length++;
    }
  }
  cout << ans << endl;

  return 0;
}