#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  rep(i, n) { scanf("%d", &a[i]); }

  // 初期化
  int num = a[0];
  vector<int> count(n + 1);
  vector<int> output(n);
  count[0] = 1;
  int ans = 1;
  output[0] = ans;

  // シミュレーション
  for (int i = 1; i < n; i++) {
    if (a[i] == num) {
      count[i] = count[i - 1] + 1;
      if (count[i] == num) {
        // まとめて消えるとこ
        ans -= a[i];
        num = a[ans];
        count[i] = count[ans];
        a[i] = a[ans];
      }
    } else {
      // 値が直前の値と異なる場合
      num = a[i];
      count[i] = 1;
    }
    ans++;
    output[i] = ans;
  }

  rep(i, n) cout << output[i] << endl;

  return 0;
}