#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int i = 0; i < t; i++) {
    /* input */
    vector<int> c(3);
    vector<int> m(3);
    vector<int> y(3);
    vector<int> k(3);
    for (int j = 0; j < 3; j++) cin >> c[j] >> m[j] >> y[j] >> k[j];
    /* solve */
    int cmin = 1001000;
    int mmin = 1001000;
    int ymin = 1001000;
    int kmin = 1001000;
    for (int j = 0; j < 3; j++) {
      cmin = min(cmin, c[j]);
      mmin = min(mmin, m[j]);
      ymin = min(ymin, y[j]);
      kmin = min(kmin, k[j]);
    }
    cout << "Case #" << i + 1 << ": ";
    if (cmin + mmin + ymin + kmin < 1000000) {
      cout << "IMPOSSIBLE" << endl;
      continue;
    }
    int cans = cmin;
    int mans = 0;
    int yans = 0;
    int kans = 0;
    int sum = cmin;
    if (sum < 1000000) {
      mans = min(mmin, 1000000 - sum);
      sum += mmin;
    }
    if (sum < 1000000) {
      yans = min(ymin, 1000000 - sum);
      sum += ymin;
    }
    if (sum < 1000000) {
      kans = min(kmin, 1000000 - sum);
      sum += kmin;
    }
    cout << cans << " " << mans << " " << yans << " " << kans << endl;
  }
  return 0;
}