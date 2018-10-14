/* Ucitati vrijednosti iz datoteke "num.dat" koja sadrzi kljuceve i dvije realne vrijednosti, zatim ucitati "keys.dat"
    i pronaci realne vrijednosti iz prve datoteke koje sadrze jedan od kljuceva iz druge datoteke. Koristiti binarno pretrazivanje. */

/*      Dobar dio ovog koda je nepotreban za konkretan zadatak, jer se u zadatku ne trazi da se zapravo nadu    *
 *      realne vrijednosti koje stoje uz "kljuc", nego da se samo prebroje usporedbe, sto se moze napraviti     *
 *      bez ikakvog uvodenja double varijabli (samo se pretrazi integere i broje se usporedbe).                 *
 *      Ovdje je napravljeno sve, u "found_real" poljima su zajednicke realne vrijednosti iz obje datoteke      */


#include <iostream>
#include <fstream>

using namespace std;

void scan_numdat_file_integers(int* integers) { //ucitavanje prvog stupca s integerima
    ifstream input("num.dat"); //prolazak kroz file, svaki put kad vidi "space" pomakne se
    double x;
    for (int i=0; i<3*50000; i++) { 
        if(i%3 == 0) { //nastimavanje da svaki treci put spremi vrijednost, kad je "i" na 0, 3, 6, 9, 12...
            input >> integers[i/3];
        }
        else input >> x; //kad je na realnim vrijednostima, spremi ih bezveze cisto da se pomakne input skener koji prolazi kroz file 
    }
}

void scan_numdat_file_real(double* arr, int column) { //argumenti funkcije su array za spremanje realnih brojeva i broj stupca cije elemente spremam
    ifstream input("num.dat");
    double x;
    for (int i=0; i<3*50000+column; i++) {
        if (i-column<0) 
            input >> x;
        else if ((i-column)%3 == 0) { //nastimavanje da svaki treci put spremi vrijednost, od kojeg broja pocinje ovisi o "column", npr za column=1 sprema za i=1, 4, 7, 10, 13...
            input >> arr[(i-column)/3];
        }
        else 
            input >> x;
    }
}

void scan_keys_file(int* arr) { //ucitavanje keys file-a
    ifstream input("keys.dat");
    for (int i=0; i<1000; i++) {
        input >> arr[i];
    }
}

int sequential_count(int* keys, int* integers, double* real1, double* real2) {
    int count, i, j=0;
    double* found_real1 = new double[1000]; //polja u koja se spremaju realni brojevi ako su zajednicki u oba file-a
    double* found_real2 = new double[1000];
    for (i=0; i<1000; i++) { //prolazak kroz sve kljuceve
        while ( j < 50000) { //prolazi od 0 do 50000 sve dok se ne nade broj koji odgovara, onda brake-aj
            if (keys[i] == integers[j])
                break;
            count++;
            j++;
        }
        if (j == 50000) { //ako je na kraju j=50000, onda nije pronaslo par, pisi 0
            found_real1[i] = 0;
            found_real2[i] = 0;
        }
        found_real1[i] = real1[j]; //ako je while prestao na manje od 50000, znaci da se naslo nesto, zapisi i resetiraj "j"
        found_real2[i] = real2[j];
        j=0;
        /*cout << keys[i] << " " << found_real1[i] << " " << found_real2[i] << endl;*/      // -> omoguciti ovu liniju koda za rezultat pretrazivanja za sequential count
    }
    return count;
}

void swaps(int *x, int *y, double *a, double *b, double *c, double *d) //zamjena tri podatka iz svakog stupca, potrebno za quicksort
{
    int temp = *y;
    *y = *x;
    *x = temp;
    double temp1 = *a;
    *a = *b;
    *b = temp1;
    double temp2 = *c;
    *c = *d;
    *d = temp2;
}

void quickSort(int *arr, double* real1, double* real2, int min, int max) //sortiranje iz 4. vjezbe
{
    int i = min, j = max; 
    int pivot = arr[(min+max)/2]; 
    while(i <= j) 
    {
        while(arr[i] < pivot) 
            i++;
        while(arr[j] > pivot) 
            j--;
        if(i <= j)
        {
            swaps(&arr[i], &arr[j], &real1[i], &real1[j], &real2[i], &real2[j]); //imamo tri podatka koja treba zamijeniti
            i++; 
            j--;
        }
    }
    if(min < j)
        quickSort(arr, real1, real2, min, j);
    if(i < max) 
        quickSort(arr, real1, real2, i, max);
}

void binary_search(int* keys, int* integers, double* real1, double* real2, double* found_real1, double* found_real2, int lo, int hi, int* count, int i) {
    int mid = (lo+hi)/2; //odrediti sredinu
    while (lo < hi || lo == hi) { //dokle god ima neki broj za provjeriti
        if (keys[i] == integers[mid]) { //ako (kljuc odgovara integeru s popisa) -> super zapisi i gasi
            count[0]++; //pomicanje brojaca
            found_real1[i] = real1[mid];
            found_real2[i] = real2[mid];
            break;
        }
        else if (keys[i] < integers[mid]) { //ako (kljuc manji od sredine popisa integera) -> rekurzija od lo do mid-1
            count[0]++;
            binary_search(keys, integers, real1, real2, found_real1, found_real2, lo, mid-1, count, i);
            break;
        }
        else if (keys[i] > integers[mid]) { //ako (kljuc veci od sredine popisa integera) -> rekurzija od mid+1 do hi
            count[0]++;
            binary_search(keys, integers, real1, real2, found_real1, found_real2, mid+1, hi, count, i);
            break;
        }
        else break;
    }
    if (lo > hi) { // ako se nista nije naslo, zapisi da se nista nije naslo i kraj funkcije
        count[0]++;
        found_real1[i] = 0;
        found_real2[i] = 0;
    }
}

int main() {
    int* integers = new int[50000]; //polje za prvi stupac s integerima
    double* real_values_1 = new double[50000]; //polje za drugi stupac s realnim brojevima
    double* real_values_2 = new double[50000]; //polje za treci stupac s realnim brojevima
    scan_numdat_file_integers(integers); //ucitavanje u polja
    scan_numdat_file_real(real_values_1, 1);
    scan_numdat_file_real(real_values_2, 2);
    int* key_integers = new int[1000]; //polje za kljuceve
    scan_keys_file(key_integers); //ucitavanje kljuceva
    cout << "Ukupan broj usporedbi za sekvencijalno pretrazivanje: " << sequential_count(key_integers, integers, real_values_1, real_values_2) << endl;
    quickSort(integers, real_values_1, real_values_2, 0, 50000-1); //sortiranje
    double* found_real1 = new double[1000]; //polja za zajednicke realne brojeve za binary_search()
    double* found_real2 = new double[1000];
    int* count = new int; //brojac usporedbi za binary_search()
    *count = 0;
    for (int i=0; i<1000; i++){ //prolazak kroz svih 1000 kljuceva
        binary_search(key_integers, integers, real_values_1, real_values_2, found_real1, found_real2, 0, 50000-1, count, i); //argumenti funkcije valjda jasni, sve to treba za search
        /*cout << key_integers[i] << " " << found_real1[i] << " " << found_real2[i] << endl;*/   // -> omoguciti ovu liniju koda za ispis zajednickih vrijednosti iz oba file-a
    }
    cout << "Ukupan broj usporedbi za binarno pretrazivanje: " << *count << endl;
    return 0;
}

