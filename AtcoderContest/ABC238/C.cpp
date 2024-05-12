#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
typedef long long ll;

ll mySum(ll m) { return m * (m + 1) / 2; }

int main() {
  int n;
  cin >> n;

  // 桁数を求める
  int length = to_string(n).size();

  ll ans = 0;

  // 1つ下まで足す
  for (int i = 1; i < length; i++) {
    ans += mySum(9 * pow(10, (i - 1)));
  }
  // 自分の桁を足す
  ans += mySum(n - 9 * pow(10, (length - 2)));
  ans %= 998244353;

  cout << ans << endl;

  return 0;
}