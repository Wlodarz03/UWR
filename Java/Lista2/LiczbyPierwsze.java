public final class LiczbyPierwsze {

    private final static int POTEGA2 = 21;
    private final static int[] SITO = new int[1 << POTEGA2]; // bit shift 1 w lewo o 21 -> 2^21

    // SITO[i] - najmniejszy pierwszy dzielnik liczby i => SITO[liczba pierwsza] = ta sama liczba pierwsza

    // statyczny blok inicjalizacyjny sita
    static {
        SITO[0] = 0;
        SITO[1] = 1;
        for (int i = 2; i < SITO.length; i++) {
            if (SITO[i] == 0) {
                SITO[i] = i;
                for (int j = 2 * i; j < SITO.length; j += i) {
                    if (SITO[j] == 0) {
                        SITO[j] = i;
                    }
                }
            }
        }
    }

    public static boolean czyPierwsza(long x){
        if (x <= 1){
            return false; // 0 i 1 nie są pierwsze
        }
        else if ( x > SITO.length){
            long sqrtx = (long)Math.sqrt(x) + 1;
            for (int i = 2; i <= sqrtx; i++){
                if (x % i == 0){
                    return false;
                }
            }
            return true;
        }
        else{
            return SITO[(int)x] == x;
        }
    }

    public static long[] naCzynnikiPierwsze(long n){
        long[] wynik = new long[65];

        if (n == 0 || n == 1 || n == -1) {
            long[] wynik2 = new long[1];
            wynik2[0] = n;
            return wynik2;
        }

        int i = 0;

        if (n < 0){
            wynik[0] = -1;

            if (n == Long.MIN_VALUE){
                n /= 2;
                wynik[1] = 2;
                i = 2;
                n = -n;
            }
            else{
                n = -n;
                i = 1;
            }
        }

        if (n < SITO.length){
            while (n > 1){
                wynik[i] = SITO[(int)n];
                n /= SITO[(int)n];
                i++;
            }
        }

        if (n > SITO.length){
            long dzielnik = 2;
            long sqrtn = (long) Math.sqrt(n) + 1;
            while (dzielnik <= sqrtn){
                if (n % dzielnik == 0){
                    wynik[i] = dzielnik;
                    n /= dzielnik;
                    i++;
                }
                else{
                    dzielnik++;
                }
            }
            if (n > 1){
                wynik[i] = n;
                i++;
            }
        }

        // żeby zwracać tablicę tylko z dzielnikami 
        long[] wynik2 = new long[i];
        for (int j = 0; j < i; j++){
            wynik2[j] = wynik[j];
        }
        return wynik2;
    }


    public static void main(String[] args){

        if (args.length == 0){
            System.err.println("Nie podano argumentow!");
        }

        long x;
        for (String a : args){
            try{
                x = Long.parseLong(a);
            }
            catch (NumberFormatException e){
                System.err.println("Zle podany argument");
                continue;
            }
            String wynik = "";
            for (long y : naCzynnikiPierwsze(x)){
                wynik += y + " * ";
            }
            wynik = wynik.substring(0, wynik.length()-2 );
            System.out.print(x + " = " + wynik);
            System.out.println("");
        }
    }
}

// java LiczbyPierwsze -1 0 1 −9223372036854775808  9223372036854775783 -> z treści
// java LiczbyPierwsze    -> error
// java LiczbyPierwsze 9223372036854775808 -> wykracza longa
// java LiczbyPierwsze 10 11 12 13 14 15 20 21 22 23 61 64 -> git