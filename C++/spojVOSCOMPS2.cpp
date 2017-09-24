
#include <bits/stdc++.h>
using namespace std;

struct node{
    int u, v, t;
    node(int _u, int _v, int _t){
        u = _u; v = _v; t = _t;
    }
};

typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> ppi;

const int maxN = 100005;

multimap<pii, int > mulmap;
int n, m, q12, q3, tin[maxN], tout[maxN];
vector<node> q;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        int c, u, v;
        cin >> c >> u >> v;
        if (u > v) swap(u, v);
        switch(c){
            case 1 : {
                mulmap.insert(ppi(pii(u, v), i+1));
                break;
            }
            case 2 : {
                auto it = mulmap.find(pii(u, v));
                if (it != mulmap.end()){
                    tin[q12] = it->second;
                    tout[q12] = i+1;
                    mulmap.erase(it);
                    ++q12;
                }
            }
            break;

            case 3 :
                q.push_back(node(u, v, i+1));
                break;
        }
    }
    while (!mulmap.empty()){
        auto it = mulmap.begin();
        tin[q12] = it->second;
        tout[q12] = m+1;
        mulmap.erase(it);
        ++q12;
    }
    return 0;
}
