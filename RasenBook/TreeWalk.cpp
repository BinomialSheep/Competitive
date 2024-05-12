#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 26
#define NIL -1

struct Tree {
  int id;
  int left;
  int right;
};

Tree tree[MAX];


void preorderTreeWalk(int node) {
  if(node == NIL) return;
  printf(" %d", node);
  preorderTreeWalk(tree[node].left);
  preorderTreeWalk(tree[node].right);
}

void inorderTreeWalk(int node) {
  if(node == NIL) return;
  inorderTreeWalk(tree[node].left);
  printf(" %d", node);
  inorderTreeWalk(tree[node].right);
}

void postorderTreeWalk(int node) {
  if(node == NIL) return;
  postorderTreeWalk(tree[node].left);
  postorderTreeWalk(tree[node].right);
  printf(" %d", node);
}




int main() {
  // 入力
  int n;
  cin >> n;
  for(int i = 0; i < MAX; i++) tree[i].id = tree[i].left = tree[i].right = NIL;
  for(int i = 0; i < n; i++ ) {
    int id, left, right;
    cin >> id >> left >> right;
    tree[id].id = id;
    tree[id].left = left;
    tree[id].right = right;
 }

 // rootを求める。節点を1とするリストを作り、誰かの子どもなら0に書き換える（節点でも子でもないなら-1）
 int nodeList[MAX];
 int root;
 for(int i = 0; i < MAX; i++ ) nodeList[i] = -1;
 for(int i = 0; i < MAX; i++ ){ if(tree[i].id != NIL) nodeList[tree[i].id] = 1;}
 for(int i = 0; i < MAX; i++ ) {
   if(tree[i].left != -1) nodeList[tree[i].left] = 0;
   if(tree[i].right != -1) nodeList[tree[i].right] = 0;
 }
 for(int i = 0; i < n; i++){
   if(nodeList[i] == 1) root = i;
 }
 //zcout << "root: " << root << endl;

 // 先行順巡回(Preorder Tree Walk)
cout << "Preorder" << endl;
preorderTreeWalk(root);
cout << endl;

 // 中間順巡回(Inorder Tree Walk)
 cout << "Inorder" << endl;
 inorderTreeWalk(root);
cout << endl;


 // 後行順巡回(Postorder Tree Walk)
 cout << "Postorder" << endl;
 postorderTreeWalk( root);
 cout << endl;


  return 0;
}