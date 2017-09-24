
#include <iostream>
using namespace std;

int n, a[1005], f[1005];

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    a[0] = -1000000007; a[n+1] = 1000000007;
    for (int i = 1; i <= n + 1; ++i)
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i]) f[i] = max(f[i], f[j] + 1);

    cout << f[n+1] - 1 << endl;
    return 0;
}
