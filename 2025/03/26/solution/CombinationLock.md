$1$ 需要移动 $0$ 次到达 $1$ ，$2$ 需要移动 $1$ 次 $...n$ 需要移动 $n-1$ 次。猜测偶数不行。

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

	if (n % 2 == 0) {
		std::cout << "-1\n";
		return;
	}

	int t = 0;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		int p = (i + t) % n;
		a[p] = i;
		t++;
	}

	for (int i = 0; i < n; ++i) {
		std::cout << a[i] + 1 << " \n"[i == n - 1];
	}
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

