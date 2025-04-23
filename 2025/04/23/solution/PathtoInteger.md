考虑到 $N$ 很小，二进制枚举。容易看出来是 $meet-in-middle$ 。

从起点到每个副对角线的点，将对应路径结果存在副对角线的点 $\rightarrow f$（主对角线同理 $\rightarrow g$）。

预处理一下$A_{ij} \rightarrow A_{ij} \times 10^{2N-2-i-j} \% M$ ，因为走到终点时都是对应点的值就是这个。

将 $f,g$ 排序，枚举 $f$ ，从 $g$ 找最优解。

- $f_i+g_i<M$ ，双指针。
- $f_i+g_i \ge M$ ，直接选择 $g_i$ 最大的值。


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

 	int N, M;
 	std::cin >> N >> M;

    auto power = [&](i64 a, i64 b) -> i64 {
        i64 res {1};
        for (; b; b /= 2, a = a * a % M) {
            if (b % 2) {
                res = res * a % M;
            }
        }
        return res;
    };

 	std::vector A(N, std::vector<int>(N));
 	for (int i = 0; i < N; ++i) {
 		for (int j = 0; j < N; ++j) {
 			std::cin >> A[i][j];
 			A[i][j] = 1LL * A[i][j] * power(10LL, 2 * N - 2 - i - j) % M;
 		}
 	}

 	std::vector<std::vector<int>> f(N), g(N);
 	for (int i = 0; i < (1 << N - 1); ++i) {
 		int x = 0, y = 0, s = 0;
 		for (int j = 0; j < N - 1; ++j) {
 			s = (s + A[x][y]) % M;
 			x += i >> j & 1;
 			y += i >> j & 1 ^ 1;
 		}
        s = (s + A[x][y]) % M;
 		f[x].emplace_back(s);
 	}
 	for (int i = 0; i < (1 << N - 1); ++i) {
 		int x = N - 1, y = N - 1, s = 0;
 		for (int j = 0; j < N - 1; ++j) {
 			s = (s + A[x][y]) % M;
 			x -= i >> j & 1;
 			y -= i >> j & 1 ^ 1;
 		}
 		g[x].emplace_back(s);
 	}

 	int ans = 0;
 	for (int i = 0; i < N; ++i) {
 		std::sort(f[i].begin(), f[i].end());
 		std::sort(g[i].begin(), g[i].end());
 		for (int r = 0, l = int(g[i].size() - 1); r < f[i].size(); ++r) {
 			while (l - 1 >= 0 && g[i][l] + f[i][r] >= M) {
 				l--;
 			}
            while (l + 1 < g[i].size() && g[i][l + 1] + f[i][r] < M) {
                l++;
            }
 			ans = std::max({ans, (f[i][r] + g[i].back()) % M, (f[i][r] + g[i][l]) % M});
 		}
 	}
 	std::cout << ans;

    return 0;
}
```

