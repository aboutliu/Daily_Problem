把所有 $D$ 相关的排序放在一个集合就变成选与不选的问题，$dp$ 即可。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, D;
    std::cin >> N >> D;

    std::vector<int> A(N), cnt(1E6 + 1);
    for (int i = 0; i < N; ++i) {
    	std::cin >> A[i];
    	cnt[A[i]]++;
    }
    if (!D) {
    	int ans = 0;
    	for (int i = 0; i <= 1E6; ++i) {
    		ans += std::max(0, cnt[i] - 1);
    	}
    	std::cout << ans;
    	return 0;
    }

    std::vector<std::vector<int>> ord;
    std::vector<int> pre;
    for (int i = 0; i <= 1E6; ++i) {
    	for (int j = i; j <= 1E6; j += D) {
    		if (!cnt[j]) {
    			break;
    		}
    		pre.emplace_back(cnt[j]);
    		cnt[j] = 0;
    	}
    	if (!pre.empty()) {
    		ord.emplace_back(pre);
    		pre.clear();
    	}
    }

    int ans = 0;
    for (auto a : ord) {
    	int n = a.size();
    	std::vector<std::array<int, 2>> dp(n, std::array {N + 1, N + 1});
    	for (int i = 0; i < n; ++i) {
    		if (!i) {
    			dp[i][0] = 0;
    			dp[i][1] = a[i];
    		} else {
    			dp[i][0] = dp[i - 1][1];
    			dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + a[i];
    		}
    	}
    	ans += std::min(dp[n - 1][0], dp[n - 1][1]);
    }
    std::cout << ans;

    return 0;
}
```

