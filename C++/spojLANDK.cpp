
#include <bits/stdc++.h>
#define MAXN 2005
using namespace std;

stack<int> st;
int n, k, a[MAXN][MAXN], h[MAXN][MAXN], L[MAXN], R[MAXN];
long long s[MAXN][MAXN], sum[MAXN][MAXN];

long long getsum(int x, int y, int u, int v){
    return sum[u][v] - sum[x-1][v] - sum[u][y-1] + sum[x-1][y-1];
}

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    cin >> k >> n;
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j){
        cin >> a[i][j];
        sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + a[i][j];
    }

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            h[i][j] = h[i-1][j] + 1;
            s[i][j] = s[i-1][j] + a[i][j];
            while (s[i][j] > 2*k){
                s[i][j] -= a[i-h[i][j]+1][j];
                --h[i][j];
            }
            if (s[i][j] >= k){
                cout << j << " " << i - h[i][j] + 1 << " " << j << " " << i << endl;
                return 0;
            }
        }

        while (!st.empty()) st.pop();
        st.push(0);
        for (int j = 1; j <= n; ++j){
            while (st.size() > 1 && h[i][st.top()] >= h[i][j]) st.pop();
            L[j] = st.top();
            st.push(j);
        }

        while (!st.empty()) st.pop();
        st.push(n+1);
        for (int j = n; j >= 1; --j){
            while (st.size() > 1 && h[i][st.top()] >= h[i][j]) st.pop();
            R[j] = st.top();
            st.push(j);
        }

        for (int j = 1; j <= n; ++j)
        if (getsum(i-h[i][j]+1, L[j]+1, i, R[j]-1) >= k){
            int jleft = j, jright = j;
            while (jleft > L[j]+1 && getsum(i-h[i][j]+1, jleft, i, jright) < k) --jleft;
            while (jright < R[j]-1 && getsum(i-h[i][j]+1, jleft, i, jright) < k) ++jright;
            cout << jleft << " " << i-h[i][j]+1 << " " << jright << " " << i << endl;
            return 0;
        }
    }
    cout << "NIE" << endl;
    return 0;
}
