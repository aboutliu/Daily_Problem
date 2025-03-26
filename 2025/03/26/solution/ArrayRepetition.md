把每次操作后的三元组 $(长度, b, 尾数)$ 处理出来，如果超出 $1E18$ 就可以加 $1$ 即可，一定要有因为虽然超出了不会算做答案，但是会影响答案的更新。

对于每个 $k$ 二分找到大于等于 $k$ 的，如果长度刚好是 $k$ 直接输出尾数，反之，则一定当前这个操作一定是 $b=2$ ，然后导致大于 $k$ 的。那么当前 $k$ 处于 $(prev.len,cur.len)$  之间，如果 $k \% prev.len =0$ 那么答案就是 $prev.尾数$ 。如果不是的话直接 $k \% prev.尾数$ 。重复下去是 $log$ 级的。

时间复杂度 $O(q \cdot log(1E18))$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
	int n, q;
	std::cin >> n >> q;

	const i64 inf = 1E18;
	i64 now = 0, back;
	std::vector<std::tuple<i64, int, int>> ord;
	for (int i = 0; i < n; ++i) {
		int b, x;
		std::cin >> b >> x;

		if (b & 1) {
			now++;
			back = x;
			ord.emplace_back(std::tuple {now, 1, back});
		} else {
			if (now > inf / (x + 1)) {
				now = inf + i;
			} else {
				now *= x + 1;
			}
			ord.emplace_back(std::tuple {now, 2, back});
		}
	}

	for (int i = 0; i < q; ++i) {
		i64 k;
		std::cin >> k;

		int c = 0;
		while (1) {
			c++;
			auto y = std::lower_bound(ord.begin(), ord.end(), std::tuple {k, 0, 0});
			auto [a, b, c] = *y;
			if (a == k) {
				std::cout << c << " \n"[i == q - 1];
				break;
			}
			auto [a1, b1, c1] = *std::prev(y);
			if (k % a1 == 0) {
				std::cout << c1 << " \n"[i == q - 1];
				break;
			}
			k %= a1;
		}
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

