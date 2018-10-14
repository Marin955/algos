/*
 Ucitavanje stringa, spremanje svakog char-a u chained hash, vrijednost je redni broj u stringu, key je sam char
 */


#include <iostream>
#include <string>

using namespace std;

struct Element{  //jedan element tablice
    char key;  //char iz stringa
    int value;  //redni broj u stringu
    Element *next;
};

Element** hash_table = new Element*[10]; //array s pointerima na strukture (hash_table je pointer na array s pointerima na strukture)

void create_hash(string str, Element** table) {
    int index;
    bool check = false;
    for (int i=0; i<str.length(); i++) {
        index = (11*str[i])%10; //hash funkcija
        cout << str[i] << "\t" << index  << "\t "<< i << endl;
        if (table[index]->key == 0) {  //ako je prazna dodaj prvi element
            table[index]->key = str[i];
            table[index]->value = i;
            table[index]->next = NULL;
        }
        else {
            Element *iter = new Element; //iterator pointer za prolazak kroz vezanu listu
            iter = table[index];
            if (iter->key == str[i]) { //ako je prvi clan tablice ono sto trazimo
                iter->value = i;
            }
            else { //ako nije...
                while (iter->next != NULL) {  //prolazak kroz listu
                    if (iter->next->key == str[i]) { //ako neki element liste ima isti key kao onaj kojeg trazimo, zamijeni vrijednosti
                        check = true;
                        iter->next->value = i;
                        break;
                    }
                    iter = iter->next; //ako nema idi dalje
                }
                if (check == false) { //ako smo prosli kroz cijelu listu i nije bilo niceg, dodaj na kraj liste
                    Element *tmp = new Element;
                    iter->next = tmp;
                    tmp->key = str[i];
                    tmp->value = i;
                    tmp->next = NULL;
                }
            }
            check = false; //resetiranje provjere
        }
    }
}

int find_in_hash(Element** table, char x) {
    int index = (11*x)%10;
    bool check = false;
    cout << "Indeks od " << x << " je: " << index << endl;
    Element *iter = new Element;
    iter = table[index];
    if (iter->key == x) 
        cout << "Vrijednost je: " << iter->value << endl;
    else {
        while (iter->next != NULL) { //prolazak kroz listu i trazenje key-a
            iter = iter->next;
            if (iter->key == x) {
                check = true;
                cout << "Vrijednost je: " << iter->value << endl;
                break;
            }
        }
        if (check == false) {  //ako nema trazenog key-a
            cout << "Key nije pronaden" << endl;
        }
    }
}

int main() {
    string str;
    char x;
    cout << "Unos stringa: " << endl;
    getline(cin, str); //Ucitavanje stringa
    for (int i=0; i<10; i++) {
        hash_table[i] = new Element;
        hash_table[i]->key = 0; //postavljanje hash tablice na nula
    }
    cout << endl << "Key" << "\t" << "Index" << "\t" << "Value" << endl << endl;
    create_hash(str, hash_table);
    cout << "Key za pretrazivanje: " << endl;
    cin >> x;
    cout << endl;
    find_in_hash(hash_table, x);
    return 0;
}