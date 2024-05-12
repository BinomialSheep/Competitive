#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; i++) {
    /* input */
    int n;
    cin >> n;
    vector<int> s(n);
    for (int j = 0; j < n; j++) cin >> s[j];
    /* solve */
    sort(s.begin(), s.end());
    int ans = 0;
    for (int j = 0; j < n; j++) {
      // cout << "debug:" << ans << " " << s[j] << endl;
      if (ans < s[j]) ans++;
    }

    cout << "Case #" << i + 1 << ": ";
    cout << ans << endl;
  }
  return 0;
}

