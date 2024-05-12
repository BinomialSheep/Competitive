#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


int n, pos;
vector<int> pre, in, post; // preorder, inorder, postorderで辿った時の番号順の節点

void rec(int left, int right) {
  if(left >= right ) return;
  // preorderの（今考えてる）先頭が（今考えてる木の）rootで、inorderでrootが現れる位置までが（今考えてる木の）部分左木
  int root = pre[pos++];
  int middle = distance(in.begin(), find(in.begin(), in.end(), root));
  rec(left, middle); // 左側部分木
  rec(middle + 1, right); // 右側部分木
  post.push_back(root); // postorderなので、左と右を辿ったあとでrootを入れる
}

void solve() {
  pos = 0;
  rec(0, pre.size());
  for(int i = 0; i < n; i++) {
    if(i) cout << " ";
    cout << post[i];
  }
  cout << endl;
}




int main() {
  int k;
  cin >> n;

  for(int i = 0; i < n; i++ ) {
    cin >> k;
    pre.push_back(k);
  }
    for(int i = 0; i < n; i++ ) {
    cin >> k;
    in.push_back(k);
  }


  solve();

  
  return 0;
}