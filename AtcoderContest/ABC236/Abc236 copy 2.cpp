#include <bits/stdc++.h>

using namespace std;

typedef long long ll;






int main() {
  string s;
  int a, b;
  cin >> s >> a >> b;

  char c1, c2;

  c1 = s[a - 1];
  c2 = s[b - 1];

  string s1 = {c1};
  string s2 = {c2};

  s.replace(a - 1, 1, s2);
  s.replace(b - 1, 1, s1);

  cout << s << endl;


  return 0;
}




int main() {
  int n;
  cin >> n;
  int n4 = 4 * n - 1;
  int A[n4];
  for(int i = 0; i < n4; i++ ) cin >> A[i];

  int B[n + 1];
  for(int i = 1; i <= n; i++) B[i] = 0;
  for(int i = 0; i < n4; i++) B[A[i]]++;

  int ans;
  for(int i = 1; i <= n; i++) {
    if(B[i] == 3){
      ans = i;
      break;
    }
  }


  cout << ans << endl;



  return 0;
}




int main() {
  int n, m;
  cin >> n >> m;
  string s[n], t[m];
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < m; i++) cin >> t[i];

  string ans[n];
  for (int i = 0; i < n; i++) ans[i] = "No";

  int j = 0;
  for (int i = 0; i < m; i++) {
    while(true) {
      if(t[i] == s[j]) {
        ans[j] = "Yes";
        j++;
        break;
      }
      j++;
    }
  }

  for(int i = 0; i < n; i++) cout << ans[i] << endl;

  return 0;
}