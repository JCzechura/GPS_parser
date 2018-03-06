# GPS module Library

Niniejsze repozytorium zawiera bibliotekę stworzoną do obsługi modułu GPS podłączonego do mikrokontrolera. Dane odbierane są przez moduł szeregowo w postaci znaków ASCII. Tworzą sentencje o powtarzającym się schemacie i długości nie większej niż 82 znaki. Każde zdanie rozpoczyna się znakiem ‘$’, po nim następuje wysłanie przedrostka charakteryzującego typ urządzenia a następnie odpowiedniego identyfikatora, który określa zawartość wiadomości. Po nim przesyłane są dane oddzielone od siebie przecinkami. Na końcu znajduje się suma kontrolna oraz znaki <CR><LF> (carriage return, line feed).

W niniejszym projekcie wykorzystano następujące rodzaje zdań: 

- GGA (Fix information) - zdanie to zawiera informację o położeniu geograficznym, czasie ostatniego pozycjonowania oraz jego precyzji.

  Przykład:  $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

- RMC (recommended minimum data for gps)  -  zdanie zawierające minimalną informację GPS potrzebną do określenia położenia obiektu.
 
  Przykład: $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,A*6A
 
