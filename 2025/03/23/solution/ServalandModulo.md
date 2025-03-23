首先有个结论如果存在这样一个数，那么一定 $k|sum_a - sum_b$ 。令 $sum = sum_a - sum_b$ 那么我们可以枚举 $sum$ 的因子，然后注意到题目最大范围的 $sum = 10^{10}$ 而其范围内的数最大因子数量是 $2304$ 这是很少的，所以可以直接 $O(n)$ 去检查满足条件否。时间复杂度 $O(n \cdot  d(sum)+\sqrt sum),d(x)$ 是 $x$ 的因子数量。我下面的写法来仿自 $jiangly$ ，官方题解的作法完全符合刚刚讨论的复杂度。 

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

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    if (a == b) {
        std::cout << 1000001 << "\n";
        return;
    }

    i64 suma = std::accumulate(a.begin(), a.end(), 0LL);
    i64 sumb = std::accumulate(b.begin(), b.end(), 0LL);
    i64 sum = suma - sumb;
    if (sum < 0) {
        std::cout << "-1\n";
        return;
    }

    auto check = [&](i64 k) -> int {
        if (k > 1E9) {
            return 0;
        }
        auto ta = a;
        for (auto &i : ta) {
            i %= k;
        }
        std::sort(ta.begin(), ta.end());
        return ta == b;
    };

    for (int i = 1; 1LL * i * i <= sum; ++i) {
        if (sum % i == 0) {
            if (check(i)) {
                std::cout << i << "\n";
                return;
            }
            if (check(sum / i)) {
                std::cout << sum / i << "\n";
                return;
            }
        }
    }
    std::cout << "-1\n";
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

