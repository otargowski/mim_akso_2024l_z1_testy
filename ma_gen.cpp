#include <bits/stdc++.h>
#define eb emplace_back
#define ssize(A) int(ssize(A))
using namespace std;
typedef const int ci;
int main(int argc, char *argv[]) {
    ci cap = argc > 1 ? atoi(argv[1]) : int(1e5);
    printf("%d\n", cap);
    struct idk {
        int ind;
        int n, m, s;
    };
    vector<idk> automaty;
    random_device rd;
    mt19937 _r(rd());
    auto r = [&](ci p, ci k) {
        assert(p <= k);
        return int(_r() % (k - p + 1)) + p;
    };
    auto rozmgen = [&]() {
        if (!r(0, 15))
            return 0;
        if (!r(0, 3))
            return r(63, 64);
        return r(65, 127);
    };
    auto genciag = [&](ci rozm) {
        for (int a = 0; a < rozm; ++a)
            putchar(r('0', '1'));
        putchar('\n');
    };
    int ile = 0;
    ci acap = 20;
    int autnum = 0;
    auto ustwej = [&](ci p) {
        printf("I %d ", automaty[p].ind);
        genciag(automaty[p].n); // Ok dla zera, przetestuje EINVAL.
        ++ile;
    };
    auto chkout = [&](ci p) {
        if (ile < cap)
            printf("O %d\n", automaty[p].ind), ++ile;
    };
    while (ile < cap) {
        ci t = r(0, 25);
        if (t < 2) { // c/C
            if (ssize(automaty) == acap)
                continue;
            ci n = rozmgen(), m = rozmgen(), s = rozmgen();
            if (!t) { // c
                printf("c %d %d %d ", n, m, s);
                genciag(s);
                ++ile;
                if (m && s) {
                    automaty.eb(autnum, n, m, s);
                    chkout(ssize(automaty) - 1);
                }
                ++autnum;
            } else { // C
                printf("C %d %d\n", n, m);
                ++ile;
                if (m) {
                    automaty.eb(autnum, n, m, m);
                    chkout(ssize(automaty) - 1);
                }
                ++autnum;
            }
            continue;
        }
        if (t < 3) { // D
            if (automaty.empty())
                continue;
            ci p = r(0, ssize(automaty) - 1);
            printf("D %d\n", automaty[p].ind);
            automaty[p] = automaty.back();
            automaty.pop_back();
            continue;
        }
        if (t < 4) { // I
            if (automaty.empty())
                continue;
            ci p = r(0, ssize(automaty) - 1);
            ustwej(p);
        }
        if (t < 5) { // s
            if (automaty.empty())
                continue;
            ci p = r(0, ssize(automaty) - 1);
            printf("s %d ", automaty[p].ind);
            genciag(automaty[p].s);
            ++ile;
            chkout(p);
            continue;
        }
        if (t < 12) { // J
            if (automaty.empty())
                continue;
            ci in = r(0, ssize(automaty) - 1);
            ci out = r(0, ssize(automaty) - 1);
            ci dl = t < 9 ? r(1, 10) : r(1, 75); // ig
            ci instart = r(0, max(0, automaty[in].n - dl + 4));
            ci outstart = r(0, max(0, automaty[out].m - dl + 4));
            printf("J %d %d %d %d %d\n", automaty[in].ind, automaty[out].ind,
                   instart, outstart, dl);
            ++ile;
            continue;
        }
        if (t < 16) { // d
            if (automaty.empty())
                continue;
            ci in = r(0, ssize(automaty) - 1);
            ci dl = t < 14 ? r(1, 10) : r(1, 75); // ig
            ci instart = r(0, max(0, automaty[in].n - dl + 4));
            printf("d %d %d %d\n", automaty[in].ind, instart, dl);
            ++ile;
            continue;
        }
        if (t < 25) { // S
            if (automaty.empty())
                continue;
            int cnt = r(1, ssize(automaty));
            // TODO: no, wiadomo
            vector<int> wybrane(cnt), indv(ssize(automaty));
            iota(indv.begin(), indv.end(), 0);
            sample(indv.begin(), indv.end(), wybrane.begin(), cnt, _r);
            for (ci p : wybrane)
                if (ile < cap)
                    ustwej(p);
            if (ile == cap)
                continue;
            printf("S %d", cnt);
            for (ci p : wybrane)
                printf(" %d", automaty[p].ind);
            printf("\n");
            for (ci p : wybrane)
                if (ile < cap)
                    chkout(p);
        }
    }
}
