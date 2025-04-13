### Ostatnia poprawka testów: sobota, 22:07-22:32.

#### Dokumentacja testów:
- `testy.md`
- `format.md`
- `ma_gen.cpp`: kod źródłowy generatorki

#### Jak użyć?
1. Mieć zainstalowane narzędzie `zstd` do (de)kompresji.
2. Zklonować/rozpakować do osobnego folderu __**poniżej**__ testowanego `ma.c`.
**Rozpakowane pliki muszą widzieć `../ma.h`, `../libma.so` oraz `../memory_tests.h`.**
3. Zbudować swoją libkę.
4. Przecztytać `makefile` (opcjonalne, ale zalecane).
5. Wywołać
```sh
make run
```
Dla odważnych jest też:
```sh
make run_duzo
```
Jeżeli nie widać żadnych zfailowanych assertów ani niepustych diffów to jest dobrze.

Do czyszczenia folderu służą cele `clean` i `clean_fr_fr` (usuwa też zkompresowane in'y i out'y).
**Tej drugiej komendy należy użyć w przypadku poprawek testów**.
