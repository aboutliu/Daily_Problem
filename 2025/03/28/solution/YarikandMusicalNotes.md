首先注意到相同的数一定是满足条件的，然后打表发现 $1,2$ 互相满足。

时间复杂度 $O(nlogv)$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
	int n;
	std::cin >> n;

	i64 ans = 0;
	std::map<int, int> map;
	for (int i = 0; i < n; ++i) {
		int u;
		std::cin >> u;

		if (u == 1) {
			ans += map[1] + map[2];
		} else if (u == 2) {
			ans += map[1] + map[2];
		} else {
			ans += map[u];
		}
		map[u]++;
	}
	std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```

