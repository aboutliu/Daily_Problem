首先肯定一个贪心，将两种颜色降序，然后考虑枚举前 $i$ 个白色之和，然后对黑色去选出大于等于前 $i$ 的总和的最大值，这里可以先做一个前缀和，再做一个后缀 $max$ 。

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

 	std::vector<int> B(N), W(M);
 	for (int i = 0; i < N; ++i) {
 		std::cin >> B[i];
 	}   
 	for (int i = 0; i < M; ++i) {
 		std::cin >> W[i];
 	}

 	std::sort(B.rbegin(), B.rend());
 	std::sort(W.rbegin(), W.rend());

 	std::vector<i64> pref(N + 1);
 	for (int i = 0; i < N; ++i) {
 		pref[i + 1] = pref[i] + B[i];
 	}
 	std::vector<i64> dp(N + 2, -1E18);
 	for (int i = N - 1; i >= 0; --i) {
 		dp[i + 1] = std::max(pref[i + 1], dp[i + 2]);
 	}

 	i64 sum = 0LL, ans = std::max(0LL, *max_element(pref.begin() + 1, pref.end()));
 	for (int i = 0; i < std::min(N, M); ++i) {
 		sum += W[i];
 		ans = std::max(ans, sum + dp[i + 1]);
 	}

 	std::cout << ans;

    return 0;
}
```

