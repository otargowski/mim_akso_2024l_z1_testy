Format wejścia:
- Liczba w pierwszej linii - liczba operacji.
- Zakładamy (assertujemy :), że rozważane automaty istnieją.
- Każda następna linia to odrębna operacja.
  Typ operacji definiuje pierwsze (jednoliterowe) słowo w linii.
  Każda powinna wypisać dokładnie jedną linię (łatwiej przeglądać wyjście).
- "Q ind": należy wypisać ciąg binarny (jako znaki '0'/'1')
  stanowiący wyjście automatu o numerze ind,
  ~~a jeżeli takowy nie istnieje to -1.~~ (chyba niepotrzebne)
- "c n m s CIĄG": należy stworzyć automat zwykły
  o stanie zadanym przez s-znakowy CIĄG binarny ('0'/'1').
  Na wyjście należy wypisać w osobnej linii '0'/'1'.
  '1' wtw automat został utworzony, czyli nie zwrócił EINVAL.
  Automat niezależnie od tego, czy został stworzony,
  otrzymuje swój własny numer. Te przydzielane są po kolei od 0.
- "C n m": jak wyżej, ale bez ciągu binarnego, gdyż stworzony
  ma zostać automat prosty.
- "I ind CIĄG": należy wywołać ma_set_input na automacie nr
  ind podając mu CIĄG. Na wyjście wypisać 0/1 jak wyżej.
- "s ind CIĄG": należy wywołać ma_set_state na automacie nr
  ind podając mu CIĄG. Na wyjście wypisać 1.
- "J inind outind instart outstart count":
  ma_connect, wypisać 0/1 jak wyżej.
- "d inind instart count":
  ma_disconnect, wypisać 0/1 jak wyżej.
- "D ind": ma_delete. wypisać 1.
- "S count ind1 ind2 ...":
  count >= 1; ma_step z `count` automatami o opisanych (różnych!) indeksach.
  wypisać 0/1.
