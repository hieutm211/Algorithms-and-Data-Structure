
#include <bits/stdc++.h>
using namespace std;

struct node{
    int u, v, t;
};

node make_node(int _u, int _v, int _t) {
        node a;
        a.u = _u; a.v = _v; a.t = _t;
        return a;
}

typedef pair<int, int> pii;
const int maxN = 100001;

int n, m, cnt, tin[maxN], tout[maxN];
node q[maxN];
stack<node> Stack;

bool cmp(node a, node b){
    if (a.t == b.t){
        if (a.u == b.u) return a.v < b.v;
        return a.u < b.u;
    }
    return a.t < b.t;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        int c;
        cin >> c >> q[i].u >> q[i].v;
        if (q[i].u < q[i].v) swap(q[i].u, q[i].v);
        switch(c){
            case 1 : q[i].t = -(i+1); break;
            case 2 : q[i].t = i+1; break;
            case 3 : q[i].t = m+1; break;
        }
    }

    sort(q, q+m, cmp);
    cnt = 0;
    for (int i = 0; i < m; ++i){
        if (q[i].t > 0 && q[i].t < m+1 && Stack.top().u == q[i].u && Stack.top().v == q[i].v){
            tin[cnt] = -Stack.top().t;
            tout[cnt] = q[i].t;
            ++cnt;
            Stack.pop();
        }
        if (q[i].t < 0) Stack.push(q[i]);
    }

    while (!Stack.empty()){
        tin[cnt] = Stack.top().t;
        tout[cnt] = m+1;
        ++cnt;
    }
    for (int i = 0; i < cnt; ++i){
        cout << tin[i] << " " << tout[i] << endl;
    }
    return 0;
}

