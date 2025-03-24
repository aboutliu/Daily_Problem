注意到 $a_i$ 是正数，所以最大值只会越来越大，那么我们可以考虑枚举最小值，然后用两边的值去构成最大值。然后发现，假设当前 $i$ ，但是 $[1,i)$ 无法 $k$ 次合并，但是两边的加起来依旧可以 $k$ 次合并，这样依旧可以利用到左边的值，右边同理。

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

    std::vector<int> a(n);
    std::vector<i64> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        pref[i + 1] += pref[i] + a[i];
    }

    std::vector<i64> ans(n);
    std::vector l(n + 1, std::vector<i64>(n)), r(n + 2, std::vector<i64>(n));
    for (int k = 0; k < n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (i + k <= n) {
                l[i][k] = std::max(l[i - 1][k], pref[i + k] - pref[i - 1]);
            }
        }
        for (int i = n; i >= 1; --i) {
            if (i - k >= 1) {
                r[i][k] = std::max(r[i + 1][k], pref[i] - pref[i - k - 1]);
            }
        }
        i64 max = 0;
        for (int i = 0; i < n; ++i) {
        	if (i - k > 0) {
        		max = std::max(max, l[i - k][k]);
        	} else if (std::max(0, i - 1) + std::max(0, n - i - 2) >= k) {
        		max = std::max(max, pref[i]);
        	}
            ans[k] = std::max(ans[k], max - a[i]);
        }
        max = 0;
        for (int i = n - 1; i >= 0; --i) {
        	if (i + k + 2 <= n) {
        		max = std::max(max, r[i + k + 2][k]);
        	} else if (std::max(0, i - 1) + std::max(0, n - i - 2) >= k) {
        		max = std::max(max, pref[n] - pref[i + 1]);
        	}
            ans[k] = std::max(ans[k], max - a[i]);
        }
    }
    ans[n - 1] = 0;

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " \n"[i == n - 1];
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

