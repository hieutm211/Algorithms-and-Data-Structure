
#include <cstdio>
using namespace std;

const int maxN = 100005;
int n, q;
long long sum[maxN];

int main(){
	freopen("sumquery.inp", "r", stdin);
	freopen("sumquery.ans", "w", stdout);

	int x, u, v;

	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i){
		scanf("%d", &x);
		sum[i] = sum[i-1] + x;
	}

	while (q--){
		scanf("%d%d", &u, &v);
		printf("%lld\n", sum[v] - sum[u-1]);
	}

	return 0;
}