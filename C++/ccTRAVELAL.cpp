
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, long long> pill;
const int MAXN = 1000005;

vector<pill> adj[MAXN];
int n, m;
int x[MAXN], y[MAXN];
int pxmin, pxmax, pymin, pymax;
bool mark[MAXN];

void add_edge(int u, int v){
    long long c = max(abs((long long)x[u] - x[v]), abs((long long)y[u] - y[v]));
    adj[u].push_back(pill(v, c));
    adj[v].push_back(pill(u, c));
}

void dfs(int u, long long D){
    mark[u] = 1;
    for (auto i = 0; i < adj[u].size(); ++i)
    if (!mark[adj[u][i].first] && adj[u][i].second >= D) dfs(adj[u][i].first, D);
}

bool check(long long D){
    memset(mark, 0, sizeof(mark));

    dfs(1, D);
    for (int i = 1; i <= n; ++i)
        if (!mark[i]) return 0;
    return 1;
}

void solve(){
    long long L, R, mid, ans;

    L = 0;
    R = 2e9;
    while (L <= R){
        mid = (L + R) / 2;
        if (check(mid)){
            ans = mid;
            L = mid + 1;
        } else R = mid - 1;
    }
    cout << ans << endl;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t, u, v;
    pxmin = pymin = n+1;
    pxmax = pymax = 0;
    x[0] = y[0] = -2e9-1;
    x[n+1] = y[n+1] = 2e9+1;

    cin >> t;
    while (t--){
        cin >> n; m = 0;
        for (int i = 1; i <= n; ++i){
            cin >> u >> v;
            x[i] = u + v;
            y[i] = u - v;
            if (x[i] > x[pxmax]) pxmax = i;
            if (x[i] < x[pxmin]) pxmin = i;
            if (y[i] > y[pymax]) pymax = i;
            if (y[i] < y[pymin]) pymin = i;
        }
        for (int i = 1; i <= n; ++i){
            if (i != pxmax) add_edge(i, pxmax);
            if (i != pxmin) add_edge(i, pxmin);
            if (i != pymax) add_edge(i, pymax);
            if (i != pymin) add_edge(i, pymin);
        }
        solve();
    }
}
