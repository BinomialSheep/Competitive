#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;






int main() {
  string s;
  cin >> s;

  int l = s.length();

  // aが先頭にいくつ付いているか
  int initialA = 0;
  int i = 0;
  while(true) {
    if(s[i] != 'a') {
      initialA = i;
      break;
    }
    if(i == l - 1) {
      initialA = l;
      break;
    }
    i++;
  }

  // aが後方にいくつ付いているか
  int lastA = 0;
  i = l - 1;
  while(true) {
    if(s[i] != 'a') {
      lastA = l - i - 1;
      break;
    }
    if(i == 0) {
      lastA = l;
      break;
    }
    i--;
  }

  if(initialA > lastA) {
    cout << "No" << endl;
    return 0;
  }

  // 回文を判定するs
  string s2 = s.substr(initialA, l - lastA - initialA);
  string s3(s2);

  reverse(s3.begin(), s3.end());

  if(s2 == s3) cout << "Yes" << endl;
  else cout << "No" << endl;



  // debug
  // cout << l << " " << initialA << " " << lastA << " " << s2 << endl;


  return 0;
}