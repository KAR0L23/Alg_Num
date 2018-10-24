#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double potega(long double x, long double y);
long double silnia(long double n);
long double funkcjaWbudowana(long double x);
long double sinusPrzod(int n, long double x);
long double cosinusPrzod(int n, long double x);
long double sinusTyl(int n, long double x);
long double cosinusTyl(int n, long double x);
long double sinusPoprzedniPrzod(int n, long double x);
long double cosinusPoprzedniPrzod(int n, long double x);
long double sinusPoprzedniTyl(int n, long double x);
long double cosinusPoprzedniTyl(int n, long double x);
long double bladWzgledny(long double x, long double y);
long double bladBezwzgledny(long double x, long double y);

#define POCZATEK -4.0
#define KONIEC 4.0
#define SKOK 0.001
#define N 25


int main() {
    // Sposób 1
    FILE *f = fopen("wyniki-1.csv", "w+");
    if (f == NULL) {
        printf("Błąd przy otwieraniu pliku!\n");
        exit(1);
    }
    
    fprintf(f, "%s, %s, %s, %s, %s\n", "x", "Wbudowana", "Moja", "Blad bezwzgledny", "Blad wzgledny");
    for(long double i = POCZATEK; i<= KONIEC; i += SKOK) {
        long double wbudowana = funkcjaWbudowana(i);
        long double moja = sinusPrzod(N, cosinusPrzod(N, i));
        fprintf(f, "%0.6Lf, %.20Lf, %.20Lf, %.20Lf, %.20Lf", i, wbudowana, moja, bladBezwzgledny(wbudowana, moja), bladWzgledny(wbudowana, moja));
        fprintf(f, "\n");
    }
    
    fclose(f);

    //sposob 2
    FILE *f1 = fopen("wyniki-2.csv", "w+");
    if (f1 == NULL) {
        printf("Błąd przy otwieraniu pliku!\n");
        exit(1);
    }
    
    fprintf(f1, "%s, %s, %s, %s, %s\n", "x", "Wbudowana", "Moja", "Blad bezwzgledny", "Blad wzgledny");
    for(long double i = POCZATEK; i<= KONIEC; i += SKOK) {
        long double wbudowana = funkcjaWbudowana(i);
        long double moja = sinusTyl(N, cosinusTyl(N, i));
        fprintf(f1, "%0.6Lf, %.20Lf, %.20Lf, %.20Lf, %.20Lf", i, wbudowana, moja, bladBezwzgledny(wbudowana, moja), bladWzgledny(wbudowana, moja));
        fprintf(f1, "\n");
    }
    
    fclose(f1);

    //sposob 3
    FILE *f2 = fopen("wyniki-3.csv", "w+");
    if (f2 == NULL) {
        printf("Błąd przy otwieraniu pliku!\n");
        exit(1);
    }
    
    
    fprintf(f2, "%s, %s, %s, %s, %s\n", "x", "Wbudowana", "Moja", "Blad bezwzgledny", "Blad wzgledny");
    for(long double i = POCZATEK; i<= KONIEC; i += SKOK) {
        long double wbudowana = funkcjaWbudowana(i);
        long double moja = sinusPoprzedniPrzod(N, cosinusPoprzedniPrzod(N, i));
        fprintf(f2, "%0.6Lf, %.20Lf, %.20Lf, %.20Lf, %.20Lf", i, wbudowana, moja, bladBezwzgledny(wbudowana, moja), bladWzgledny(wbudowana, moja));
        fprintf(f2, "\n");
    }
    
    fclose(f2);

    //sposob 4
    FILE *f3 = fopen("wyniki-4.csv", "w+");
    if (f3 == NULL) {
        printf("Błąd przy otwieraniu pliku!\n");
        exit(1);
    }
    
    fprintf(f3, "%s, %s, %s, %s, %s\n", "x", "Wbudowana", "Moja", "Blad bezwzgledny", "Blad wzgledny");
    for(long double i = POCZATEK; i<= KONIEC; i += SKOK) {
        long double wbudowana = funkcjaWbudowana(i);
        long double moja = sinusPoprzedniTyl(N, cosinusPoprzedniTyl(N, i));
        fprintf(f3, "%0.6Lf, %.20Lf, %.20Lf, %.20Lf, %.20Lf", i, wbudowana, moja, bladBezwzgledny(wbudowana, moja), bladWzgledny(wbudowana, moja));
        fprintf(f3, "\n");
    }
    
    fclose(f3);

    return 0;
}

long double funkcjaWbudowana(long double x) {
    return sin(cos(x));
}

long double potega(long double x, long double y) {
    if (y == 0) {
        return 1;
    } 
    
    return x *= potega(x, --y);
}


long double silnia(long double n) {
    if (n == 0) return 1;
    
    return n * silnia(n - 1);
}

long double cosinusPrzod(int n, long double x) {
    long double wynik = 0;

    for(int i = 0; i <= n; i++) {
        wynik += potega(-1, i) * (potega(x, 2 * i) / silnia(2  * i));
    }

    return wynik;
}

long double sinusPrzod(int n, long double x) {
    long double wynik = 0;

    for(int i = 0; i <= n; i++) {
        wynik += potega(-1, i) * (potega(x, 2 * i + 1) / silnia(2  * i + 1));
    }

    return wynik;
}

long double cosinusTyl(int n, long double x) {
    long double wynik = 0;

    for(int i = n; i >= 0; i--) {
        wynik += potega(-1, i) * (potega(x, 2 * i) / silnia(2  * i));
    }

    return wynik;
}

long double sinusTyl(int n, long double x) {
    long double wynik = 0;

    for(int i = n; i >= 0; i--) {
        wynik += potega(-1, i) * (potega(x, 2 * i + 1) / silnia(2  * i + 1));
    }

    return wynik;
}

long double cosinusPoprzedniPrzod(int n, long double x) {
    long double wynik = 1;
    long double pierwszy = 1;

    for(int i = 1; i < n ; i++) {
        pierwszy *=  (-1) *  ((potega(x, 2)) / ((2 * i) * (2 * i - 1)));
        wynik += pierwszy;
    }

    return wynik;
}

long double sinusPoprzedniPrzod(int n, long double x) {
    long double wynik = x;
    long double pierwszy = x;

    for (int i = 1; i < n; i++)
    {
        pierwszy *= ((-1) * (potega(x, 2))) / (2 * i * (2 * i + 1));
        wynik += pierwszy;
    }

    return wynik;
}

long double cosinusPoprzedniTyl(int n, long double x) {
    long double wynik = 0;
    long double tabPomocnicza[n];
    tabPomocnicza[0] = 1;
    int iteracja = 0;

    for (int i = 1; i < n; i++) {
        tabPomocnicza[i] =  (tabPomocnicza[i-1] * (-1) * (potega(x, 2))) / ((2 * i) * (2 * i - 1));
        iteracja++;
    }

    for (int i = iteracja - 1; i >= 0; i--) {
        wynik += tabPomocnicza[i];
    }

    return wynik;
}

long double sinusPoprzedniTyl(int n, long double x)  {
    long double wynik = 0;
    long double tabPomocnicza[n];
    tabPomocnicza[0] = x;
    int iteracja = 0;

    for (int i = 1; i < n; i++) {
        tabPomocnicza[i] = (tabPomocnicza[i-1] * (-1) * (potega(x, 2))) / (2 * i * (2 * i + 1));
        iteracja++;
    }

    for (int i = iteracja -1; i >= 0; i--) {
        wynik += tabPomocnicza[i];
    }

    return wynik;
}

long double bladBezwzgledny(long double x, long double y) {
    return fabsl(y-x);
}

long double bladWzgledny(long double x, long double y) {
    return bladBezwzgledny(x, y)/fabsl(x);
}

