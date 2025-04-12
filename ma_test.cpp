#ifdef NDEBUG
#undef NDEBUG
#endif

extern "C" {
#include "../ma.h"
#include "../memory_tests.h"
}
// TODO: malloc wrappers.
// #include "memory_tests.h"
#include <cassert>
#include <cstring>
#include <errno.h>
#include <ios>
#include <random>
#include <set>
#include <vector>

using namespace std;

typedef const int ci;
typedef const size_t csz;
typedef uint64_t u64;
typedef vector<u64> ciag;

int I() {
    int z;
    scanf("%d", &z);
    return z;
}

size_t SZ() {
    size_t z;
    scanf("%zu", &z);
    return z;
}

#define BLOK 64

ciag dejciag(const size_t cnt) {
    ciag v((cnt + BLOK - 1) / BLOK);
    if (!cnt)
        return v;
    int z;
    size_t rozm = 0;
    while (iswspace(z = getchar()))
        ;
    do {
        assert(z == '0' || z == '1');
        assert(rozm < cnt);
        v[rozm / BLOK] |= u64(z - '0') << (rozm % BLOK);
        ++rozm;
    } while (!iswspace(z = getchar()));
    assert(cnt == rozm);
    return v;
}

csz BCAP = 128;
u64 prztab[BCAP][BCAP][BCAP / BLOK];
u64 wyjtab[BCAP][BCAP][BCAP / BLOK];

void outfun(uint64_t *output, uint64_t const *state, size_t m, size_t s) {
    assert(output != NULL && state != NULL && m > 0 && s > 0);
    for (size_t i = 0; i < (m + BLOK - 1) / BLOK; ++i)
        output[i] = wyjtab[m][s][i];
    m = (m + BLOK - 1) / BLOK;
    s = (s + BLOK - 1) / BLOK;
    for (size_t i = 0; i < min(m, s); ++i)
        output[i] ^= state[i];
}

void transfun(uint64_t *next_state, uint64_t const *input,
              uint64_t const *state, size_t n, size_t s) {
    assert(next_state != NULL && input != NULL && state != NULL && s > 0);
    for (size_t i = 0; i < (s + BLOK - 1) / BLOK; ++i)
        next_state[i] = state[i] ^ prztab[n][s][i];
    n = (n + BLOK - 1) / BLOK;
    s = (s + BLOK - 1) / BLOK;
    for (size_t i = 0; i < min(n, s); ++i)
        next_state[i] ^= input[i];
}

int main() {
    { // prztab & wyjtab init
        mt19937_64 r((69420 ^ 1023456789) * 998244353ll);
        for (size_t i = 0; i < BCAP; ++i)
            for (size_t j = 0; j < BCAP; ++j)
                for (size_t k = 0; k < BCAP / BLOK; ++k) {
                    prztab[i][j][k] = r();
                    wyjtab[i][j][k] = r();
                }
    }
    int q = I();
    struct idk {
        moore_t *ma;
        size_t n, m, s;
        const u64 *out;
    };
    vector<idk> t;
    ma_delete(NULL);
    {
        moore_t *ma = NULL;
        errno = 0;
        assert(ma_step(&ma, 0) == -1 && errno == EINVAL);
    }
    {
        errno = 0;
        assert(ma_get_output(NULL) == NULL && errno == EINVAL);
    }
    auto chkind = [&](csz i) {
        assert(i < size(t) && t[i].ma != NULL && t[i].out != NULL);
    };
    memory_test_data_t *mtd = get_memory_test_data();
    random_device rd;
    mt19937 _r(rd());
    auto r = [&](ci p, ci k) { return int(_r() % (k - p + 1)) + p; };
    while (q--) {
        mtd->fail_counter = mtd->call_counter + r(1, 20);
        char z;
        scanf("\n%c", &z);
        if (z == 'O') {
            csz i = SZ();
            chkind(i);
            for (size_t a = 0; a < t[i].m; ++a)
                putchar('0' + (t[i].out[a / BLOK] >> (a % BLOK) & 1));
            putchar('\n');
            continue;
        }
        if (z == 'D') {
            csz i = SZ();
            chkind(i);
            assert(t[i].out == ma_get_output(t[i].ma));
            ma_delete(t[i].ma);
            t[i].ma = NULL;
            printf("1\n");
            continue;
        }
        if (z == 'S') {
            csz ile = SZ();
            vector<moore_t *> at(ile);
            set<size_t> s;
            for (size_t i = 0; i < ile; ++i) {
                csz p = SZ();
                assert(s.insert(p).second);
                chkind(p);
                at[i] = t[p].ma;
            }
            int res = 0;
            do {
                errno = 0;
                res = ma_step(at.data(), ile);
            } while (res == -1 && errno == ENOMEM);
            if (res != 0)
                assert(res == -1 && errno == EINVAL);
            printf(res == 0 ? "1\n" : "0\n");
            // Nie pozwalamy na ENOMEM przed EINVAL, bo tak.
            errno = 0;
            assert(ma_step(at.data(), 0) == -1 && errno == EINVAL);
            at.back() = NULL;
            errno = 0;
            assert(ma_step(at.data(), ile) == -1 && errno == EINVAL);
            errno = 0;
            assert(ma_step(NULL, ile) == -1 && errno == EINVAL);
            continue;
        }
        if (z == 'd') {
            csz inind = SZ(), instart = SZ(), count = SZ();
            chkind(inind);
            int res = 0;
            // do {
            //     errno=0;
            //     res=ma_disconnect(t[inind].ma, instart, count);
            // } while (res==-1&&errno == ENOMEM);
            errno = 0;
            res = ma_disconnect(t[inind].ma, instart, count);
            if (res != 0)
                assert(res == -1 && errno == EINVAL);
            printf(res == 0 ? "1\n" : "0\n");
            errno = 0;
            assert(ma_disconnect(NULL, instart, count) == -1 &&
                   errno == EINVAL);
            continue;
        }
        if (z == 'J') {
            csz inind = SZ(), outind = SZ(), instart = SZ(), outstart = SZ(),
                count = SZ();
            chkind(inind);
            chkind(outind);
            int res = 0;
            do {
                errno = 0;
                res = ma_connect(t[inind].ma, instart, t[outind].ma, outstart,
                                 count);
            } while (res == -1 && errno == ENOMEM);
            if (res != 0)
                assert(res == -1 && errno == EINVAL);
            printf(res == 0 ? "1\n" : "0\n");
            errno = 0;
            assert(ma_connect(NULL, instart, t[outind].ma, outstart, count) ==
                       -1 &&
                   errno == EINVAL);
            errno = 0;
            assert(ma_connect(t[inind].ma, instart, NULL, outstart, count) ==
                       -1 &&
                   errno == EINVAL);
            errno = 0;
            assert(ma_connect(NULL, instart, NULL, outstart, count) == -1 &&
                   errno == EINVAL);
            continue;
        }
        if (z == 'I') {
            csz i = SZ();
            chkind(i);
            const ciag c = dejciag(t[i].n);
            errno = 0;
            int res = ma_set_input(t[i].ma, c.data());
            assert(res == 0 || (res == -1 && errno == EINVAL));
            printf(res == 0 ? "1\n" : "0\n");
            errno = 0;
            assert(ma_set_input(t[i].ma, NULL) == -1 && errno == EINVAL);
            errno = 0;
            assert(ma_set_input(NULL, c.data()) == -1 && errno == EINVAL);
            continue;
        }
        if (z == 's') {
            csz i = SZ();
            chkind(i);
            const ciag c = dejciag(t[i].s);
            errno = 0;
            int res = ma_set_state(t[i].ma, c.data());
            assert(res == 0);
            printf(res == 0 ? "1\n" : "0\n");
            errno = 0;
            assert(ma_set_state(t[i].ma, NULL) == -1 && errno == EINVAL);
            errno = 0;
            assert(ma_set_state(NULL, c.data()) == -1 && errno == EINVAL);
            continue;
        }
        if (z == 'c') {
            const size_t n = SZ(), m = SZ(), s = SZ();
            assert(n < BCAP && m < BCAP && s < BCAP);
            const ciag c = dejciag(s);
            moore_t *res;
            do {
                errno = 0;
                res = ma_create_full(n, m, s, transfun, outfun, c.data());
            } while (res == NULL && errno == ENOMEM);
            if (res == NULL)
                assert(errno == EINVAL);
            printf(res != NULL ? "1\n" : "0\n");
            errno = 0;
            t.emplace_back(res, n, m, s, ma_get_output(res));
            assert(res == NULL || t.back().out != NULL);
            errno = 0;
            assert(ma_create_full(n, m, s, transfun, outfun, NULL) == NULL &&
                   errno == EINVAL);
            errno = 0;
            assert(ma_create_full(n, m, s, transfun, NULL, c.data()) == NULL &&
                   errno == EINVAL);
            errno = 0;
            assert(ma_create_full(n, m, s, NULL, outfun, c.data()) == NULL &&
                   errno == EINVAL);
            continue;
        }
        if (z == 'C') {
            const size_t n = SZ(), m = SZ(), s = m;
            assert(n < BCAP && m < BCAP && s < BCAP);
            moore_t *res;
            do {
                errno = 0;
                res = ma_create_simple(n, m, transfun);
            } while (res == NULL && errno == ENOMEM);
            if (res == NULL)
                assert(errno == EINVAL);
            printf(res != NULL ? "1\n" : "0\n");
            errno = 0;
            t.emplace_back(res, n, m, s, ma_get_output(res));
            assert(res == NULL || t.back().out != NULL);
            errno = 0;
            assert(ma_create_simple(n, m, NULL) == NULL && errno == EINVAL);
            continue;
        }
        assert(0);
    }
    for (idk &i : t)
        if (i.ma != NULL) {
            assert(i.out == ma_get_output(i.ma));
            ma_delete(i.ma);
            i.ma = NULL;
        }
}
