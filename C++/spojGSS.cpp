
#include <iostream>
#include <cstdio>
#define MAXN 500005
#define INF 1000000007

using namespace std;

struct node{
    long long ans, sum, pre, suf;
};

int n, m, a[MAXN];
node t[4*MAXN];

node CombineIT(node left, node right){
    node ans;
    ans.sum = left.sum + right.sum;
    ans.pre = max(left.pre, left.sum + right.pre);
    ans.suf = max(right.suf, left.suf + right.sum);
    ans.ans = max(max(left.ans, right.ans), left.suf + right.pre);
    return ans;
}

void Build(int k, int left, int right){
    if (left == right) {
        t[k].ans = a[left];
        t[k].sum = a[left];
        t[k].pre = a[left];
        t[k].suf = a[left];
        return;
    }
    int mid = (left + right) / 2;
    Build(2*k, left, mid);
    Build(2*k+1, mid+1, right);
    t[k] = CombineIT(t[2*k], t[2*k+1]);
}

node Get(int k, int l, int r, int u, int v){
    if (r < u || v < l) {
        node tmp;
        tmp.sum = 0;
        tmp.pre = -INF;
        tmp.suf = -INF;
        tmp.ans = -INF;
        return tmp;
    }
    if (u <= l && r <= v) return t[k];
    int mid = (l + r) / 2;
    return CombineIT(Get(2*k, l, mid, u, v), Get(2*k+1, mid+1, r, u, v));
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    Build(1, 1, n);

    scanf("%d", &m);
    while (m > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", Get(1, 1, n, l, r).ans);
        --m;
    }
    return 0;
}
