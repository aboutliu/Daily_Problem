考虑到 $N$ 很小，去掉 $1,N$ 之后就只剩 $8$ 个数了，所以直接全排列，枚举每个点即可，全排列一定会把所有情况枚举出来，所以我们一直连边就行了，当断开的时候就 $break$ ，当然对于每个点都要考虑用它来连接 $N$ 号点。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

   	std::vector g(N, std::vector<i64>(N, -1));
   	for (int i = 0; i < M; ++i) {
   		int u, v;
   		i64 w;
   		std::cin >> u >> v >> w;
   		u--;
   		v--;
   		g[u][v] = g[v][u] = w;
   	}

   	std::vector<int> p;
   	for (int i = 1; i < N - 1; ++i) {
   		p.emplace_back(i);
   	}

   	i64 ans = g[0][N - 1] == -1 ? (1LL << 60) : g[0][N - 1];
   	do {
   		int pre = 0;
   		i64 tans = 0LL;
   		for (int i = 0; i < N - 2; ++i) {
   			if (g[pre][p[i]] == -1) {
   				break;
   			}
   			tans ^= g[pre][p[i]];
   			if (g[p[i]][N - 1] != -1) {
   				ans = std::min(ans, tans ^ g[p[i]][N - 1]);
   			}
   			pre = p[i];
   		}
   	} while (std::next_permutation(p.begin(), p.end()));

   	std::cout << ans;

    return 0;
}
```

