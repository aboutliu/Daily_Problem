注意到 $b$ 的 $0$ 可以移动到同奇偶性的位置，$a$ 的 $1$ 也只跟 $b$ 的某一个奇偶性转换。

时间复杂度 $O(n)$ 。

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

	std::string a, b;
	std::cin >> a >> b;

	std::array<int, 2> cnt {};
	for (int i = 0; i < n; ++i) {
		cnt[i & 1] += b[i] == '0';
	}
	for (int i = 0; i < n; ++i) {
		if (a[i] == '1') {
			cnt[i & 1 ^ 1]--;
		}
	}

	auto ans = cnt[0] >= 0 & cnt[1] >= 0 ? "YES": "NO";
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

