#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


struct Node {
  int key;
  Node *parent, *left, *right;
};

Node *root, *NIL;

void insert(int k) {
  Node *y = NIL; // 暫定親
  Node *x = root; // 比較対象のNode
  Node *z; // 挿入するNode
  z = (Node *)malloc(sizeof(Node));
  z->key = k;
  z->left = NIL;
  z->right = NIL;

  while( x != NIL ) {
    y = x;
    if( z->key < x-> key ) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if( y == NIL ) {
    // 親yがいなかったらzがroot
    root = z;
  } else {
    // 親yがいるなら親との比較でyの左か右に付ける
    if( z->key < y->key ) {
      y->left = z;
    } else {
      y->right = z;
    }
  }
}

Node* find(Node *u, int k) {
  // 値が見つかるかNILに到達するまでループ
  while(u != NIL && k != u-> key ) {
    if(k < u->key ) u = u->left;
    else u = u-> right;
  }
  return u;
}

Node* treeMinimum(Node *x) {
  while( x->left != NIL ) x = x->left;
  return x;
}


// xの次節点（中間順でxの次の節点のこと）
Node* treeSuccessor(Node *x) {
  // xに右部分木があるなら、右部分木の1番左
  // xの代わりにxの左の子の親となるノードのアドレスとなる
  if( x->right != NIL ) return treeMinimum(x->right);
  // xに右部分木がないなら、xが誰かの左の子になる直前まで遡った時の親
  // 今回の削除ではここには到達しない
  Node *y = x->parent;
  while( y != NIL && x == y->right ) {
    x = y;
    y = y->parent;
  }
  return y;
}

void treeDelete(Node *z) {
  Node *y; // 削除する対象
  Node *x; // yの子

  // 削除する節点を求める
  // zの子が0か1ならzを削除。2ならzの右部分木の最小のノードを（zの位置に入れた上で. これは下の方で実装）削除
  if( z->left == NIL || z->right == NIL )  y = z;
  else y = treeSuccessor(z);

  // y の子 x を決める
  if( y->left != NIL ) x = y->left;
  else x = y->right;
  // yを削除するので、xの親はyの親になる
  if(x != NIL ) x->parent = y->parent;

  if(y->parent == NIL ) root = x; // yがrootの場合はxが次のrootとなる
  else if (y == y->parent->left) y->parent->left = x; // yが親の左の子だったらxは親の左の子
  else y->parent->right = x; // 右の子なら右の子

  if ( y != z ) z->key = y->key; // zの子が2人だった場合の親変更はここでようやく行う

  free(y);
}



void inorder(Node *u) {
  if( u == NIL) return;
  inorder(u->left);
  printf(" %d", u->key);
  inorder(u->right);
}
void preorder(Node *u) {
  if(u == NIL ) return;
  printf(" %d", u->key);
  preorder(u->left);
  preorder(u->right);
}

int main() {
  int n, x;
  string com;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    cin >> com;
    if( com == "insert" ) {
      scanf("%d", &x);
      insert(x);
    } else if (com == "print") {
      inorder(root); // insertの過程でrootが指すNodeは更新されている
      printf("\n");
      preorder(root);
      printf("\n");
    } else if (com == "find") {
      scanf("%d", &x);
      Node *t = find(root, x);
      if (t != NIL ) printf("yes\n");
      else printf("no\n");
    } else if (com == "delete") {
      scanf("%d", &x);
      treeDelete(find(root, x));
    }
  }

  return 0;
}