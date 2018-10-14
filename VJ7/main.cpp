/* Napraviti jednostavno povezano stablo (tree) strukturu podataka i pretrazivanje po stablu. Vrijednosti ucitane iz datoteka. */
 
/* Nije direktno dodavanje u stablo, nego se prvo ucitava u polje pa onda ide konstrukcija stabla */

#include <iostream>
#include <fstream>

struct Node {  //jedan element stabla
    int integer_value;
    double real1;
    double real2;
    Node* left;
    Node* right;
};

using namespace std;

int usporedbe_konstrukcija=0, usporedbe_pretrazivanje=0; //globalne varijable za broj usporedbi

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

Node* insert(Node* root, int integer_value, double real1, double real2) {
    usporedbe_konstrukcija++;
    if (root  ==  NULL){  //ako nema nista dodaj novi element stabla
        Node  *temp =  new Node;
        temp->integer_value  =  integer_value;
        temp->real1 = real1;
        temp->real2 = real2;
        temp->left  =NULL;
        temp->right  =  NULL;
        root = temp;
     }
    else if ( integer_value <=  root->integer_value) {  //ako je vrijednost koju dodajemo manja od elemnta stabla, idi lijevo
         root->left  =  insert( root->left, integer_value, real1, real2);
     }
    else root->right  =  insert( root->right, integer_value, real1, real2); // ako je veca idi desno
     return root;
}

int findtree( Node* root, int num){ //pretrazivanje po stablu
    usporedbe_pretrazivanje++;
    if (root->integer_value == num) return num;
    else if (root->left !=NULL && num<root->integer_value) {
        findtree(root->left, num);
    }
    else if (root->right !=NULL && num>root->integer_value) {
        findtree(root->right, num);
    }
    else return 0;
}

int main() {
    Node* root = new Node;
    root = NULL;
    int* integers = new int[50000]; //polje za prvi stupac s integerima
    double* real_values_1 = new double[50000]; //polje za drugi stupac s realnim brojevima
    double* real_values_2 = new double[50000]; //polje za treci stupac s realnim brojevima
    scan_numdat_file_integers(integers); //ucitavanje u polja
    scan_numdat_file_real(real_values_1, 1);
    scan_numdat_file_real(real_values_2, 2);
    for (int i=0; i<50000; i++) { //konstrukcija stabla
        root = insert(root, integers[i], real_values_1[i], real_values_2[i]);
    }
    int* key_integers = new int[1000]; //polje za kljuceve
    scan_keys_file(key_integers); //ucitavanje kljuceva
    int* found = new int[1000];
    for (int i=0; i<1000; i++) { //pretrazivanje
        found[i] = findtree(root, key_integers[i]); //polje found sadrzi pronadene vrijednosti, ali ne treba za zadatak
    }
    cout << "Usporedbe za konstrukciju stabla: " << usporedbe_konstrukcija << endl;
    cout << "Usporedbe za pretrazivanje stabla: " << usporedbe_pretrazivanje << endl;
    cout << "Ukupno usporedbi: " << usporedbe_konstrukcija + usporedbe_pretrazivanje << endl;
    return 0;
}

