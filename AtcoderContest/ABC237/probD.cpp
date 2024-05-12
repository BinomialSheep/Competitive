#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
 
typedef long long ll;
 
 
 
 
int main() {
  list<int> lst{0};
  list<int>::iterator itr = lst.begin();
 
  int n;
  cin >> n;
  string s;
  cin >> s;
  int l = s.length();
  rep(i, l) {
    if(s[i] == 'L') {
      itr = lst.insert(itr, i+1);
    } else {
      itr = lst.insert(++itr, i+1);
    }
  }
 
  // 出力
  for(auto v : lst) {
    cout << v << " ";
  }
  cout << endl;
  
  
}