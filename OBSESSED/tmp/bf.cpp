#include <cstdio>
static const int MAXN = 100007;
static const int INF = 0x3fffffff;

int n, m;
int a[MAXN] = { 0 };    // 0 = Empty, 1 = Don, 2 = Katsu

inline void don(int x) { a[x] = 1; }
inline void katsu(int x) { a[x] = 2; }
inline void invert(int l, int r) {
    for (; l <= r; ++l) if (a[l]) a[l] = 3 - a[l];
}
inline int inspect(int l, int r) {
    int ans = INF;
    int last[3] = { -INF, -INF, -INF };
    for (; l <= r; ++l) if (a[l]) {
        if (ans > l - last[a[l]]) ans = l - last[a[l]];
        last[a[l]] = l;
    }
    return (ans == INF ? -1 : ans);
}

int main()
{
    scanf("%d%d", &n, &m);

    char op[16];
    int arg1, arg2;
    for (int i = 0; i < m; ++i) {
        scanf("%s%d", op, &arg1);
        if (op[0] == 'D') don(arg1);
        else if (op[0] == 'K') katsu(arg1);
        else {
            scanf("%d", &arg2);
            if (op[2] == 'v') invert(arg1, arg2);
            else printf("%d\n", inspect(arg1, arg2));
        }
    }

    return 0;
}

