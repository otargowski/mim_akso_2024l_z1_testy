#### Dokumentacja testów:
- `testy.md`
- `format.md`

#### Jak użyć?
Zklonować/rozpakować do osobnego folderu tam, gdzie mamy chociażby `ma.c`, tzn. rozpakowane pliki
muszą widzieć `../ma.h`, `../libma.so` i `../memory_test.h`.
Zbudować swoją libkę i w folderze z plikami testerki wywołać:
```sh
make run
```
Dla odważnych jest też:
```sh
make run_duzo
```

Do czyszczenia folderu służą cele `clean` i `clean_fr_fr` (usuwa też zkompresowane in'y i out'y).
