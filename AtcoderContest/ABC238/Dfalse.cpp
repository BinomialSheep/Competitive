#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
typedef long long ll;

int main() {
  int t;
  cin >> t;
  ll a, s;
  rep(i, t) {
    cin >> a >> s;
    bitset<61> abit(a);
    bitset<61> sbit(s);

    // cout << abit << " " << sbit << " " << endl;
    //  1番上のANDが1ならもう無理
    if (abit[60]) {
      cout << "No" << endl;
      continue;
    }
    //　下からチェック
    // ANDが1である限り、SUMは0でなければならない
    int flag = 0;
    for (int j = 0; j <= 60; j++) {
      if (!abit[j]) break;
      if (sbit[j]) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) {
      cout << "No" << endl;
      continue;
    }
    // indexをズラして上からチェック
    for (int j = 59; j >= 0; j--) {
      // cout << j << " " << abit[j] << " " << sbit[j + 1] << endl;
      // ANDの1が続く限り、SUMも続かなければならない
      // SUMが1でANDも1ならcontinue
      if (sbit[j + 1] && abit[j]) continue;
      // SUMが0でANDが0ならcontinue
      if (!sbit[j + 1] && !abit[j]) continue;
      // SUMが1でANDが0ならOK
      if (sbit[j + 1] && !abit[j]) break;
      // SUMが0でANDが1だとダメ
      flag = 1;
      break;
    }
    if (flag == 1) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }

  return 0;
}