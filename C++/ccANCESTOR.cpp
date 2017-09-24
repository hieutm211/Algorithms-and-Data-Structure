
#include <bits/stdc++.h>
#define MAXN 500005
using namespace std;

int n, cnt;
int head[MAXN], adj[2*MAXN], nxt[2*MAXN];
int child[MAXN], par[MAXN], pos[MAXN], start[MAXN], vmax[MAXN], t[MAXN], ans[MAXN];

void reset_all(){
    cnt = 0;
    for (int i = 0; i <= n+1; ++i){
        head[i] = 0;
        child[i] = 0;
        par[i] = 0;
        pos[i] = 0;
        start[i] = 0;
        vmax[i] = 0;
        t[i] = 0;
    }
}

void add(int i, int u, int v){
    nxt[i] = head[u];
    head[u] = i;
    adj[i] = v;
}

void dfs1(int u, int parent){
    int j, v;

    child[u] = 1;
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent){
            par[v] = u;
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

void update(int i, int v){
    while (i <= n){
        t[i] += v;
        i += i & -i;
    }
}

int get(int i){
    int ans = 0;
    while (i > 0){
        ans += t[i];
        i -= i & -i;
    }
    return ans;
}

void findans(int u){
    ans[u] = 0;
    int v = u;
    while (v != 0){
        ans[u] += get(pos[v]) - get(pos[start[v]]-1);
        v = par[start[v]];
    }
}

void dfs(int u, int parent){
    int j, v;

    findans(u);
    update(pos[u], 1);
    j = head[u];
    while (j != 0){
        v = adj[j];
        if (v != parent) dfs(v, u);
        j = nxt[j];
    }
    update(pos[u], -1);
}

int main(){
    int testcase, u, v;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> testcase;
    for (; testcase > 0; --testcase){
        cin >> n; reset_all();
        for (int i = 1; i <= n-1; ++i){
            cin >> u >> v;
            add(2*i, u, v);
            add(2*i+1, v, u);
        }
        dfs1(1, -1);
        dfs2(1, -1, 0);

        memset(head, 0, sizeof(head)); // reset tree
        for (int i = 1; i <= n-1; ++i){
            cin >> u >> v;
            add(2*i, u, v);
            add(2*i+1, v, u);
        }
        dfs(1, -1);
        for (int i = 1; i <= n; ++i) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
