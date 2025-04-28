考虑 $dp$ 。

- $N=a+b$ ，正常转移。
- $N=a \times b$ ，转移时需要考虑左右两边需不需要加 $()$ 。考虑还原数组 $pre$ 需要记录一个二元组 $(u,v)$ ，$u$ 代表从哪转移过来，$v$ 代表是 $+/ \times$ 操作。
- 最后需要注意 $1,11,111,1111$ 已经是最小长度。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

constexpr int M = 2E3;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> dp(M + 1, 1E9);
    std::vector<std::array<int, 2>> pre(M + 1);
    dp[0] = 0;
    dp[1] = 1;
    dp[11] = 2;
    dp[111] = 3;
    dp[1111] = 4;
    pre[1] = pre[11] = pre[111] = pre[1111] = std::array {0, 1};
    for (int i = 1; i <= N; ++i) {
    	for (int j = 1; j <= N; ++j) {
			int t = 1;
    		if (i + j <= N) {
    			if (dp[i + j] > dp[i] + dp[j]) {
    				dp[i + j] = dp[i] + dp[j] + t;
    				pre[i + j] = std::array {j, 0};
    			}
    		}
			if (i * j <= N) {
				t += !pre[i][1] * 2 + !pre[j][1] * 2;
				if (dp[i * j] > dp[i] + dp[j] + t) {
					dp[i * j] = dp[i] + dp[j] + t;
					pre[i * j] = std::array {j, 1};
				}
			}
    	}
    }

    std::vector<std::string> f(M + 1);
    f[1] = "1";
    f[11] = "11";
    f[111] = "111";
    f[1111] = "1111";

    auto dfs = [&](auto &&self, int u) -> std::string {
    	if (!u) {
    		return "";
    	}
    	if (!f[u].empty()) {
    		return f[u];
    	}
    	auto [x, y] = pre[u];
    	if (y) {
    		int a = x, b = u / x;
    		std::string res {};
    		res += pre[a][1] ? self(self, a) : ("(" + self(self, a) + ")");
    		res += "*";
    		res += pre[b][1] ? self(self, b) : ("(" + self(self, b) + ")");
    		f[u] = res;
    		return f[u];
    	} else {
    		int a = x, b = u - x;
    		std::string res {};
    		res += self(self, a) + "+" + self(self, b);
    		f[u] = res;
    		return f[u];
    	}
    };

    auto ans = dfs(dfs, N);
    std::cout << ans;

    return 0;
}
```

