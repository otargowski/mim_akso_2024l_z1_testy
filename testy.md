1. Rozmiary ciągów: losowe od 63 do 128 + 0.
2. Utrzymujemy wszystko "określone".
A więc przed ma_step ustalamy wszystkie modyfikowane.
3. Funkcje przejść/wyjść:
- na początku zfillowane randem (mt19937_64((69420 ^ 1023456789) * 998244353))
  2 zestawy tablic [128][128], wszędzie walnięte 128bitów, bo czemu nie.
- wynik := tablica[n/s][s/m] ^ (przejście ? input ^ stan : stan).
- nie przekraczamy w tych xorach granic bloków 64-bitowych.
4. Sprawdzane wyjście: NIEUŻYWANE BITY MAJĄ BYĆ WYZEROWANE,
NAWET JEŻELI FUNKCJE UŻYTKOWNIKA SĄ ZDURNIAŁE (jak tu).
Zapytałem na forum odnośnie tego, jak doczekam się odpowiedzi to może zmienię
to zachowanie.
5. Malloc itp. zpatchowane z jakąś 1/7 szans ig na zfailowanie.
6. Wykonywane operacje:
- "(O)" znaczy że sprawdzamy output
- "(A)" znaczy że jak ENOMEM to powtarzamy do skutku.
- (O) (A) stwórz automat zwykły/simple o losowych rozmiarach,
  zfilluj randem stan (jak nie simple). Zapamiętaj n,m,s oraz ma_get_output.
- ma_delete losowego - sprawdzić przy okazji czy ma_get_output takie samo.
  Na początku ma_delete z NULLem bo czemu nie, na końcu nieusunięte też usuwamy.
- ma_connect losowy do losowego (1/2 szans na krótki przedział typu 1-10, inaczej zupełnie
  losowy).
- (O) ma_set_state losowego na losowy
- (O) ma_set_input losowego na losowy
- (A) (O) ma_set_input i potem ma_step losowego podzbioru.
7. Dla (przeważnie) każdego argumentu będącego wskaźnikiem, przed daną operacją,
   próbujemy wywołać się z resztą dobrą, ale z danym argiem równym NULLowi.
8. Nieobejmowane przypadki:
potencjalnie jakieś wynikające z nieutrzymywania stanu zdefniowania wejścia,
a na pałę jego zapewnianie.
