很明显的 $dp$ ，假设 $dp_{i,j}$ 表示方案数，那么从上层往下层转移只需考虑欧氏距离即可，但是考虑到还有同层转移，但是我们上面定义的 $dp$ 状态表示的方案数，有个限制条件是最多一层只选两个 $hold$ ，所以同层不能直接转移，因为 $dp$ 状态有包含了同层已经两个的情况。

重新设计，$dp1_{i,j}$ 表示只选一个 $hold$ 的方案数，$dp2_{i,j}$ 表示方案数。

转移：$dp1_{i,j}= \sum_{k=0}^{m-1}[\sqrt{(i-1-i)^2+(j-k)^2} \leq d]dp2_{i-1,k}$ ，$dp2_{i,j}= \sum_{k=0}^{m-1}[|j-k| \leq d]dp1_{i,k}$ 。

很显然我们需要 $O(nm)$ 的枚举，所以这多出来的 $\sum$ 就需要用前缀和去优化，第二个很好理解前缀和，第一个转移用二分很好确定左右端点，但是其实用双指针可以代替。

时间复杂度 $O(nm \cdot logm)$ 。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

template<class T>
constexpr T power(T a, i64 b) {
    T res {1};
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<i64 P>
struct MInt {
    i64 x;
    constexpr MInt() : x {0} {}
    constexpr MInt(i64 x) : x {norm(x % getMod())} {}

    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};

const int mod1 = 998244353, mod2 = 1E9 + 7;

template<>
i64 MInt<0>::Mod = mod1;

constexpr int P = mod1;
using Z = MInt<P>;

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }

    void init(int m) {
        m = std::min<i64>(m, Z::getMod() - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

void solve() {
	int n, m, d;
	std::cin >> n >> m >> d;

	std::vector<std::string> s(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> s[i];
	}

	std::vector dp1(n + 1, std::vector<Z>(m + 1));
	std::vector dp2(n + 1, std::vector<Z>(m + 1));
	std::vector pref(n + 1, std::vector<Z>(m + 1));
	for (int i = 0; i < m; ++i) {
		dp1[1][i + 1] = s[0][i] == 'X';
	}
	for (int i = 0; i < m; ++i) {
		if (s[0][i] == '#') {
			continue;
		}
		dp2[1][i + 1] = dp1[1][i + 1];
		for (int j = 0; j < m; ++j) {
			if (std::hypot(i - j, 0) <= d && i != j) {
				dp2[1][i + 1] += dp1[1][j + 1];
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		pref[1][i + 1] += pref[1][i] + dp2[1][i + 1];
	}

	auto check = [&](int l1, int r1, int l2, int r2) -> int {
		return std::hypot(l1 - l2, r1 - r2) <= d;
	};

	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '#') {
				continue;
			}
			int lo = 0, hi = j, res1 = j;
			while (lo <= hi) {
				int mid = (lo + hi) / 2;
				if (check(i - 1, mid, i, j)) {
					res1 = mid;
					hi = mid - 1;
				} else {
					lo = mid + 1;
				}
			}
			lo = j;
			hi = m - 1;
			int res2 = j;
			while (lo <= hi) {
				int mid = (lo + hi) / 2;
				if (check(i - 1, mid, i, j)) {
					res2 = mid;
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			dp1[i + 1][j + 1] += pref[i][res2 + 1] - pref[i][res1];
		}
		std::vector<Z> tpref(m + 1);
		for (int j = 0; j < m; ++j) {
			tpref[j + 1] += tpref[j] + dp1[i + 1][j + 1];
		}
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '#') {
				continue;
			}
			int l = std::max(0, j - d), r = std::min(j + d + 1, m);
			dp2[i + 1][j + 1] = tpref[r] - tpref[l];
		}
		for (int j = 0; j < m; ++j) {
			pref[i + 1][j + 1] += pref[i + 1][j] + dp2[i + 1][j + 1];
		}
	}

	Z ans = pref[n][m];
	std::cout << ans << "\n";
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

