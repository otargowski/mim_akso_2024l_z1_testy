### Ostatnia poprawka testów: sobota, 22:07 (mało, średnio), 22:32 (dużo)

#### Dokumentacja testów:
- `testy.md`
- `format.md`
- `ma_gen.cpp`: kod źródłowy generatorki

#### Jak użyć?
Zklonować/rozpakować do osobnego folderu tam, gdzie mamy chociażby `ma.c`, tzn. rozpakowane pliki
muszą widzieć `../ma.h`, `../libma.so` i `../memory_test.h`.
Oczywiście warto przed odpaleniem poniższych komend przecztytać `makefile`.
Po zbudowaniu swojej libki, w folderze z plikami testerki należy wywołać:
```sh
make run
```
Dla odważnych jest też:
```sh
make run_duzo
```

Do czyszczenia folderu służą cele `clean` i `clean_fr_fr` (usuwa też zkompresowane in'y i out'y). **Tej drugiej komendy należy użyć w przypadku poprawek testów**.
