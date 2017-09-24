
#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;

int n, cnt;
int head[MAXN], adj[2*MAXN+1], nxt[2*MAXN+1], c[2*MAXN];
int child[MAXN], h[MAXN], par[MAXN], pos[MAXN], start[MAXN], edge[2*MAXN+1], p[MAXN][21], t[4*MAXN], vmax[MAXN];

void reset_all(){
    cnt = 0;
    for (int i = 0; i <= n+1; ++i){
        head[i] = 0;
        child[i] = 0;
        h[i] = 0;
        par[i] = 0;
        pos[i] = 0;
        start[i] = 0;
        edge[i] = 0;
        vmax[i] = 0;
    }
    for (int i = 0; i <= 4 * n; ++i) t[i] = 0;
    /*
    memset(head, 0, sizeof(head));
    memset(child, 0, sizeof(child));
    memset(h, 0, sizeof(h));
    memset(par, 0, sizeof(par));
    memset(pos, 0, sizeof(pos));
    memset(start, 0, sizeof(start));
    memset(edge, 0, sizeof(edge));
    memset(t, 0, sizeof(t));
    */
}

void add(int i, int u, int v, int w){
    nxt[i] = head[u];
    head[u] = i;
    adj[i] = v;
    c[i] = w;
}

void dfs1(int u, int parent){
    int j, v;

    child[u] = 1;
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent){
            edge[j/2] = v;
            par[v] = u;
            h[v] = h[u] + 1;
            dfs1(v, u);
            child[u] += child[v];
        }
        j = nxt[j];
    }
}

void dfs2(int u, int parent, bool mark){
    int j, v;

    pos[u] = ++cnt;
    if (mark == 0) start[u] = u;
    else start[u] = start[parent];

    j = head[u]; vmax[u] = 0;
    while (j != 0){
        v = adj[j];
        if (v != parent && child[v] > child[vmax[u]]) vmax[u] = v;
        j = nxt[j];
    }

    if (vmax[u] != 0) dfs2(vmax[u], u, 1);
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent && v != vmax[u]) dfs2(v, u, 0);
        j = nxt[j];
    }
}

void InitLCA(){
    int log2n = log(n)/log(2);

    for (int i = 1; i <= n; ++i){
        p[i][0] = par[i];
        for (int j = 1; j <= log2n; ++j) p[i][j] = -1;
    }

    for (int j = 1; j <= log2n; ++j)
        for (int i = 1; i <= n; ++i)
            if (p[i][j-1] != -1) p[i][j] = p[p[i][j-1]][j-1];
}

int LCA(int u, int v){
    if (u == v) return u;
    if (h[u] < h[v]) swap(u, v);

    int log2n = log(n)/log(2);

    for (int i = log2n; i >= 0; --i)
        if (p[u][i] != -1 && h[u] - (1 << i) >= h[v]) u = p[u][i];

    if (u == v) return u;

    for (int i = log2n; i >= 0; --i)
    if (p[u][i] != -1 && p[u][i] != p[v][i]){
        u = p[u][i];
        v = p[v][i];
    }
    return par[u];
}

void update(int k, int l, int r, int i, int v){
    if (i < l || r < i) return;
    if (l == r){
        t[k] = v;
        return;
    }
    int mid = (l+r)/2;
    update(2*k, l, mid, i, v);
    update(2*k+1, mid+1, r, i, v);
    t[k] = max(t[2*k], t[2*k+1]);
}

int get(int k, int l, int r, int u, int v){
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return t[k];
    int mid = (l+r)/2;
    return max(get(2*k, l, mid, u, v), get(2*k+1, mid+1, r, u, v));
}

void query1(int &u, int &v){
    update(1, 1, n, pos[edge[u]], v);
}

void query2(int &u, int &v){
    int lca = LCA(u, v), ans = 0;

    while (u != lca){
        if (pos[start[u]] <= pos[lca]) {
            ans = max(ans, get(1, 1, n, pos[vmax[lca]], pos[u]));
            u = lca;
        } else {
            ans = max(ans, get(1, 1, n, pos[start[u]], pos[u]));
            u = par[start[u]];
        }
    }

    while (v != lca){
        if (pos[start[v]] <= pos[lca]){
            ans = max(ans, get(1, 1, n, pos[vmax[lca]], pos[v]));
            v = lca;
        } else {
            ans = max(ans, get(1, 1, n, pos[start[v]], pos[v]));
            v = par[start[v]];
        }
    }
    printf("%d\n", ans);
}

int main(){
    int ntest, u, v, w;
    char s[5];

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &ntest);
    for (; ntest > 0; --ntest){
        scanf("%d", &n); reset_all();
        for (int i = 1; i <= n - 1; ++i){
            scanf("%d%d%d", &u, &v, &w);
            add(2*i, u, v, w);
            add(2*i+1, v, u, w);
        }

        dfs1(1, -1);
        dfs2(1, -1, 0);
        InitLCA();

        for (int i = 1; i <= n - 1; ++i) update(1, 1, n, pos[edge[i]], c[2*i]);

        scanf("%s", &s);
        while (s[0] != 'D'){
            scanf("%d%d", &u, &v);
            if (s[0] == 'C') query1(u, v);
            else query2(u, v);
            scanf("%s", &s);
        }
    }
    return 0;
}
