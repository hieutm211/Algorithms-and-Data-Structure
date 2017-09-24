
#include <bits/stdc++.h>
#define MAXN 10005
#define oo 1000000007
using namespace std;

int n, cnt, cntnum;
int head[MAXN], adj[2*MAXN+1], nxt[2*MAXN+1], e[2*MAXN+1];
int par[MAXN], h[MAXN], p[MAXN][20], edge[MAXN], child[MAXN], vmax[MAXN], start[MAXN], pos[MAXN], t[4*MAXN], f[4*MAXN], num[MAXN], tail[MAXN];

void reset_all(){
    cnt = 0; cntnum = 0;
    for (int i = 0; i <= n; ++i){
        head[i] = 0;
        e[i] = 0;
        par[i] = 0;
        h[i] = 0;
        edge[i] = 0;
        child[i] = 0;
        vmax[i] = 0;
        start[i] = 0;
        pos[i] = 0;
        num[i] = 0;
        tail[i] = 0;
    }
    for (int i = 0; i <= 4 * n; ++i){
        t[i] = -oo;
        f[i] = 1;
    }
}

void add(int i, int u, int v, int w){
    nxt[i] = head[u];
    head[u] = i;
    adj[i] = v;
}

void dfs(int u, int parent){
    int j, v;
    num[u] = ++cntnum;
    child[u] = 1;

    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent){
            edge[j/2] = v;
            par[v] = u;
            h[v] = h[u]+1;
            dfs(v, u);
            if (child[v] > child[vmax[u]]) vmax[u] = v;
            child[u] += child[v];
        }
        j = nxt[j];
    }
    tail[u] = cntnum;
}

void InitHLD(){
    for (int i = 1; i <= n; ++i)
    if (vmax[par[i]] != i){
        int v = i;
        while (v != 0){
            start[v] = i;
            pos[v] = ++cnt;
            v = vmax[v];
        }
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
    if (h[u] < h[v]) swap(u, v);

    int log2n = log(n)/log(2);

    for (int i = log2n; i >= 0; --i)
        if (h[u] - (1 << i) >= h[v]) u = p[u][i];

    if (u == v) return u;

    for (int i = log2n; i >= 0; --i)
    if (p[u][i] != -1 && p[u][i] != p[v][i]){
        u = p[u][i];
        v = p[v][i];
    }
    return par[u];
}


void down(int k){
    if (t[2*k] != -oo){
        t[2*k] *= f[k];
        f[2*k] *= f[k];
    }
    if (t[2*k+1] != -oo){
        t[2*k+1] *= f[k];
        f[2*k+1] *= f[k];
    }
    f[k] = 1;
}

void update(int k, int l, int r, int i, int v){
    if (i < l || r < i) return;
    if (l == r){
        t[k] = v;
        return;
    }
    down(k);
    int mid = (l+r)/2;
    update(2*k, l, mid, i, v);
    update(2*k+1, mid+1, r, i, v);
    t[k] = max(t[2*k], t[2*k+1]);
}

void update2(int k, int l, int r, int u, int v, int val){
    if (v < l || r < u) return;
    if (u <= l && r <= v){
        t[k] *= val;
        f[k] *= val;
        down(k);
        return;
    }
    down(k);
    int mid = (l+r)/2;
    update2(2*k, l, mid, u, v, val);
    update2(2*k+1, mid+1, r, u, v, val);
    t[k] = max(t[2*k], t[2*k+1]);
}

int get(int k, int l, int r, int u, int v){
    if (v < l || r < u) return -oo;
    if (u <= l && r <= v) return t[k];
    down(k);
    int mid = (l+r)/2;
    int get1 = get(2*k, l, mid, u, v);
    int get2 = get(2*k+1, mid+1, r, u, v);
    return max(get1, get2);
}

void query1(int u, int v){
    update(1, 1, n, pos[edge[u]], v);
}

void query2(int u, int v){
    int lca = LCA(u, v);
    while (u != lca){
        //if (num[start[u]] <= num[lca] && tail[start[u]] >= tail[lca])
        if (pos[start[u]] <= pos[lca] && pos[lca] <= pos[u]){
            update2(1, 1, n, pos[vmax[lca]], pos[u], -1);
            u = lca;
        } else {
            update2(1, 1, n, pos[start[u]], pos[u], -1);
            u = par[start[u]];
        }
    }
    while (v != lca){
        //if (num[start[v]] <= num[lca] && tail[start[v]] >= tail[lca])
        if (pos[start[v]] <= pos[lca] && pos[lca] <= pos[v]){
            update2(1, 1, n, pos[vmax[lca]], pos[v], -1);
            v = lca;
        } else {
            update2(1, 1, n, pos[start[v]], pos[v], -1);
            v = par[start[v]];
        }
    }
}

void query3(int u, int v){
    if (u == v){
        cout << 0 << endl;
        return;
    }

    int lca = LCA(u, v), ans = -oo;
    while (u != lca){
        //if (num[start[u]] <= num[lca] && tail[start[u]] >= tail[lca])
        if (pos[start[u]] <= pos[lca] && pos[lca] <= pos[u]){
            ans = max(ans, get(1, 1, n, pos[vmax[lca]], pos[u]));
            u = lca;
        } else {
            ans = max(ans, get(1, 1, n, pos[start[u]], pos[u]));
            u = par[start[u]];
        }
    }
    while (v != lca){
        //if (num[start[v]] <= num[lca] && tail[start[v]] >= tail[lca])
        if (pos[start[v]] <= pos[lca] && pos[lca] <= pos[v]){
            ans = max(ans, get(1, 1, n, pos[vmax[lca]], pos[v]));
            v = lca;
        } else {
            ans = max(ans, get(1, 1, n, pos[start[v]], pos[v]));
            v = par[start[v]];
        }
    }
    cout << ans << endl;
}

int main(){
    int testcase, u, v, w;
    char q[6];

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> testcase;
    for (; testcase > 0; --testcase){
        cin >> n; reset_all();
        for (int i = 1; i <= n-1; ++i){
            cin >> u >> v >> w;
            add(2*i, u, v, w);
            add(2*i+1, v, u, w);
            e[i] = w;
        }
        dfs(1, 0);
        InitHLD();
        InitLCA();

        update(1, 1, n, pos[1], -oo);
        for (int i = 1; i <= n-1; ++i) update(1, 1, n, pos[edge[i]], e[i]);

        cin >> q;
        while (q[0] != 'D'){
            cin >> u >> v;
            if (q[0] == 'C') query1(u, v);
            else if (q[0] == 'N') query2(u, v);
            else query3(u, v);
            cin >> q;
        }
    }
    return 0;
}
