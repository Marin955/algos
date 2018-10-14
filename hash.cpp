/* 
 Unijeti ključeve

E A S Y Q U T I O N
tim redoslijedom u početno praznu hash tablicu duljine M = 15, koristeći linear probing metodu. Koristite hash funkciju

11*k % M
za transformiranje k-tog slova abecede u indeks tablice.
 */

#include <iostream>
#include <string>

using namespace std;

int M = 15;

void create_hash(char* table, int x) {
    int index = (11*x)%M; //hash funkcija
    cout << index << " ";
    if (table[index] == 0) {
        table[index] = (char)x+64; //ako je prazno polje dodaj char na to mjesto
    }
    else {  //ako nije trazi koje je prazno
        while (table[index] != 0) {
            index++;
            if (index == M)  //ako dode do kraja arraya resetiraj se na nulu
                index = 0;
        }
        table[index] = (char)x+64;
    }
}

int main() {
    string str = "EASYQUTION";
    char* hash_table = new char[M];
    for (int i=0; i<M; i++) {
        hash_table[i] = 0;
    }
    cout << "Indeksi polja za svako slovo iz EASYQUTION: ";
    for (int i=0; i<str.length(); i++) {  
        create_hash(hash_table, (int)str[i]-64); //kreiranje hash tablice, argumenti su polje charova i integer vrijednost nekog slova (A=65)
    }
    cout << endl << "Indeks" << "\t" << "Kljuc" << endl;
    for (int i=0; i<M; i++) {
        cout << i << "\t" << hash_table[i] << endl;
    }
    return 0;
}