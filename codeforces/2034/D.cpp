#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;

#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
#define dbg(x) cout << #x << " = " << x << ", "
#define dbg2(x) cout << #x << " = " << x << endl

template<typename T> void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

int buf[42];
template<typename T> void write(T x) {
    int p = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar('0'), void();
    while(x) {
        buf[p++] = x % 10;
        x /= 10;
    }
    for (int i = p - 1; i >= 0; i--) putchar(buf[i] + '0');
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    array<int, 3> cnt = {0, 0, 0};
    for (int i = 0; i < n; i++) cnt[a[i]]++;

    // 0 in [0, cnt[0])
    // 1 in [cnt[0], cnt[0] + cnt[1])
    // 2 in [cnt[0] + cnt[1], n)
    vector<pii> ans;
    int now = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != 1) continue;
        if (cnt[0] <= i && i < cnt[0] + cnt[1]) continue;
        now = i; break;
    }
    
    if (now == -1) {
        for (int i = 0; i < n; i++) if (a[i] == 1) {
            int tgt = -1;
            if (cnt[0] == cnt[2] && cnt[0] == 0) {
                for (int i = 1; i < n; i++) {
                    assert(a[i-1] <= a[i]);
                }
                return cout << 0 << "\n", void();
            }
            for (int j = 0; j < cnt[0]; j++) {
                if (i == j) continue;
                if (a[j] == 2) {
                    tgt = j; break;
                }
            }
            for (int j = cnt[0] + cnt[1]; j < n; j++) {
                if (i == j) continue;
                if (a[j] == 0) {
                    tgt = j; break;
                }
            }
            if (tgt == -1) {
                for (int i = 1; i < n; i++) {
                    assert(a[i-1] <= a[i]);
                }
                return cout << 0 << '\n', void();
            }
            assert(abs(a[i] - a[tgt]) == 1);
            ans.eb(i, tgt);
            swap(a[i], a[tgt]);
            now = tgt;
            break;
        }
    }

    int now0 = n - 1, now2 = 0;
    while (now0 >= cnt[0] + cnt[1] && now2 < cnt[0]) {
        while (now0 >= cnt[0] + cnt[1] && a[now0] != 0) now0--;
        while (now2 < cnt[0] && a[now2] != 2) now2++;

        if (now0 < cnt[0] + cnt[1] || now2 >= cnt[0]) break;

        // in 0 zone.
        if (now < cnt[0]) {
            assert(abs(a[now] - a[now0]) == 1);
            ans.eb(now, now0);
            swap(a[now], a[now0]);
            now = now0;
        }
        // in 2 zone.
        else {
            assert(abs(a[now] - a[now2]) == 1);
            ans.eb(now, now2);
            swap(a[now], a[now2]);
            now = now2;
        }
    }

    // find which zone is no 0/2
    bool ok0 = true, ok2 = true;
    for (int i = 0; i < cnt[0]; i++) {
        if (a[i] == 2) { ok0 = false; break;}
    }
    for (int i = cnt[0] + cnt[1]; i < n; i++) {
        if (a[i] == 0) { ok2 = false; break;}
    }

    auto solve0 = [&]() {
        for (int i = 0; i < cnt[0]; i++) {
            if (a[i] != 1) continue;
            while (now0 >= cnt[0] && a[now0] != 0) now0--;
            if (now0 < cnt[0]) break;
            assert(abs(a[i] - a[now0]) == 1);
            ans.eb(i, now0);
            swap(a[i], a[now0]);
        }
    };

    auto solve2 = [&]() {
        for (int i = n - 1; i >= cnt[0] + cnt[1]; i--) {
            if (a[i] != 1) continue;
            while (now2 < cnt[0] + cnt[1] && a[now2] != 2) now2++;
            if (now2 >= cnt[0] + cnt[1]) break;
            assert(abs(a[i] - a[now2]) == 1);
            ans.eb(i, now2);
            swap(a[i], a[now2]);
        }
    };

    if (ok0) solve0();
    solve2();
    if (!ok0) solve0();

    for (int i = 1; i < n; i++) {
        assert(a[i-1] <= a[i]);
    }

    assert(SZ(ans) <= n);

    cout << (int)SZ(ans) << '\n';
    for (int i = 0; i < SZ(ans); i++) {
        cout << ans[i].fi + 1 << ' ' << ans[i].se + 1 << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}