struct node {
   int cnt;
   node *lc, *rc;
   node (int val, node *left, node *right) {
      this->cnt = val;
      this->lc = left;
      this->rc = right;
   }
   node* insert(int l, int r, int x, int val);
};

node *null, *root[MAX];

void init() {
   null = new node(0, NULL, NULL);
   null->lc = null;
   null->rc = null;
   root[0] = null;
}

//Complexity: O(n logn)
node* node::insert(int l, int r, int x, int val) {
   if (l > x || r < x) return this;
   else if (l == r) {
      return new node(this->cnt + val, null, null);
   }
   int mid = (l+r)/2;
   return new node(this->cnt + val, this->lc->insert(l, mid, x, val), this->rc->insert(mid+1, r, x, val));
}

//Complexity : O(log n)
int query(node *a, node *b, int l, int r, int k) {
   if (l == r) return l;
   int total = b->lc->cnt - a->lc->cnt, mid = (l+r)/2;
   if (total >= k) return query(a->lc, b->lc, l, mid, k);
   return query(a->rc, b->rc, mid+1, r, k-total);
}

//Sample "print function" for debugging
void traverse(node *a) {
   if (a == null) return;
   printf("%d ", a->cnt);
   traverse(a->lc);
   traverse(a->rc);
}
