注意到最靠前的最小值的位置 $y$ ，如果 $y$ 及后面的数不满足非递减，那答案一定是 $-1$ ，反之就是前面的数的个数。

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

	int id = 0, min = 1E9;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];

		if (a[i] < min) {
			min = a[i];
			id = i;
		}
	}

	std::vector<int> ord;
	for (int i = id; i < n; ++i) {
		ord.emplace_back(a[i]);
	}
	if (std::is_sorted(ord.begin(), ord.end())) {
		std::cout << id << "\n";
	} else {
		std::cout << "-1\n";
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

