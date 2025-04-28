很容易想到用 $set$ ，但如果只用 $set$ 的对于 $all-permission$ 的查询会被卡时间，所以另外开一个数组存是否 $all-permission$ 即可。


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

    int N, M, Q;
    std::cin >> N >> M >> Q;

    std::vector<std::set<int>> can(N);
    std::vector<int> all(N);
    while (Q--) {
    	int op;
    	std::cin >> op;

    	if (op == 1) {
    		int X, Y;
    		std::cin >> X >> Y;
    		X--;
    		Y--;

    		if (!all[X]) {
    			can[X].emplace(Y);
    		}
    	} else if (op == 2) {
    		int X;
    		std::cin >> X;
    		X--;

    		all[X] = 1;
    	} else {
    		int X, Y;
    		std::cin >> X >> Y;
    		X--;
    		Y--;

    		if (all[X] || can[X].contains(Y)) {
    			std::cout << "Yes\n";
    		} else {
    			std::cout << "No\n";
    		}
    	}
    }

    return 0;
}
```

