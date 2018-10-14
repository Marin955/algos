/* Napisati algoritme sortiranja koji imaju ovisnost O(n^2) i testirati broj usporedbi i zamjena za svaki */

#include <iostream>
#include <random>
#include <chrono> //treba za vrijeme, odnosno random generiranje

int n=30000; //public varijabla, koristi se svugdje

void generate_array(int *arr) {
	int i;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //broj u nanosekundama koji se mijenja kako bi se dobili random brojevi
	std::mt19937 mersenne(seed); //njega se ubacuje u mersenne algoritam
	std::uniform_int_distribution<int> dist(1,10000000);
	for (i=0; i<n; i++) { //punjenje array-a s random brojevima
		arr[i] = dist(mersenne);
	} 
}

void counting_sort(int niz[]) {
	int order [n]; //polje koje biljezi na kojem mjestu se treba u konacnom poretku nalaziti broj iz random arraya
	int i, j, count_usporedbe=0, count_swap=0;
	for (i=0; i<n; i++) { //postavljanje svega na nulu
		order[i] = 0;
	}
	for (i=n; i>=0; i--) { //"i" ide od kraja arraya do pocetka, predstavlja broj kojeg se usporeduje sa svim ostalima
		for (j=0; j<i-1; j++) { //"j" prolazi kroz array...
		count_usporedbe++;
		if (niz[i] <= niz [i-j-1]){ //ako ima nesto vece od broja "i", povecaj tom necem poziciju za jedan
			++order[i-j-1];
		}
		else { //ako nema povecaj "i" broju poziciju za jedan
			++order[i];
		}
	}
	}
	int sorted_array [n];
	for (i=1; i<n; i++) { //"i" ide od 1 do 30,000
		for (j=0; j<n; j++) {
			if (order[j] == i){ //kad u arrayu s pozicijama nade poziciju i...
				sorted_array[i-1] = niz[j]; //...popuni sortirani niz s brojem s te pozicije
			}
		}
		count_swap++;
	}
	std::cout << "------------------" << std::endl << "Counting sort" << std::endl << "------------------" << std::endl << "Prvih 10 elemenata: " << std::endl;
	for (i=0; i<10; i++) {
		std::cout << sorted_array[i] << " ";
	}
	std::cout << std::endl << std::endl << "Broj usporedbi: " << count_usporedbe << std::endl << "Broj zamjena: " << count_swap << "\t" << "(iako tehnicki nije bilo zamjena, nego stvaranje novog polja)" << std::endl;
}

void bubble(int niz[]) {
	int i, j, temp, count_usporedbe=0, count_swap=0;
	for (i=n; i>=0; i--) { //i se smanjuje jer zadnji element uvijek uvijek ispadne sortiran nakon prolaska j varijable kroz array
		for (j=1; j<i; j++) { //prolazak kroz array
			if (niz[j] < niz[j-1]){ //usporedba susjedna dva clana
				temp = niz[j-1]; //swap
				niz[j-1] = niz[j];
				niz[j] = temp;
				count_swap++;
			}
			count_usporedbe++; //svaki prolazak je usporedba
		}
	}
	std::cout << std::endl << "------------------" << std::endl << "Bubble sort" << std::endl << "------------------" << std::endl << "Prvih 10 elemenata: " << std::endl;
	for (i=0; i<10; i++) {
		std::cout << niz[i] << " ";
	}
	std::cout << std::endl << std::endl << "Broj usporedbi: " << count_usporedbe << std::endl << "Broj zamjena: " << count_swap << std::endl << std::endl;
}

void insertion(int niz[]) {
	int i, j, k, temp, count_usporedbe=0, count_swap=0, swap_check;
	for (i=1; i<=n; i++) { // "i" predstavlja element arraya koji se provjerava i kojeg treba ubaciti u ostatak arraya
		swap_check = niz[i]; //treba za brojanje zamjena, ako nakon prolaska kroz sljedece petlje ovaj broj ostane nepromijenjen, znaci da se nije dogodila zamjena
		for (j=0; j<i; j++) { //prolazak kroz array do tog elementa
			if (niz[i] < niz[j]) { //kad se nade neki clan koji je veci, pomakni sve za jedno mjesto i zamijeni
				temp = niz[i]; //swap
				for (k=i-1; k>=j; k--) { //pomicanje svega za jedno mjesto
					niz[k+1] = niz[k];
					count_swap++;
				}
				niz[j] = temp;
				count_swap++;
			}
			count_usporedbe++;
		}
		if (swap_check == niz[i]) count_swap--; //nije doslo do zamjene, oduzmi brojacu 1
	}
	std::cout <<  std::endl << "------------------" << std::endl << "Insertion sort" << std::endl << "------------------" << std::endl << "Prvih 10 elemenata: " << std::endl;
	for (i=0; i<10; i++) {
		std::cout << niz[i] << " ";
	}
	std::cout << std::endl << std::endl << "Broj usporedbi: " << count_usporedbe << std::endl << "Broj zamjena: " << count_swap << std::endl << std::endl;
}

void selection(int *niz) {
	int i, min, min_check, mjesto, temp, j, count_swap=0, count_usporedbe=0;
	for (i=0; i<n-1; i++) { //"i" predstavlja prvi nesortirani clan
		min = i; //prvi clan za pocetak najmanji
		min_check = min; //treba za provjeru zamjene, ako je nakon petlji prvi broj i dalje ostao najmanji, nema zamjene
		for (j=i+1; j<n; j++) { //prolazak kroz array
			count_usporedbe++;
			if (niz[j] < niz[min]) { //ako ima nesto manje od trenutnog minimuma, to je sad novi minimum
				min = j;
			}
		}
		count_swap++;
		if (min_check == min) {
			count_swap--; //ako nije bilo zamjene, oduzmi brojacu 1
		}
                if (i != min) {
		temp = niz[i]; //swap
		niz[i] = niz[mjesto];
		niz[mjesto] = temp;
                }
	}
	std::cout << std::endl << "------------------" << std::endl << "Selection sort" <<std::endl << "------------------" << std::endl << "Prvih 10 elemenata: " << std::endl;
	for (i=0; i<10; i++) {
		std::cout << niz[i] << " ";
	}
	std::cout << std::endl << std::endl << "Broj usporedbi: " << count_usporedbe << std::endl << "Broj zamjena: " << count_swap << std::endl;
}

int main() {
	int *array = new int[n]; //array s 30,000 mjesta koji se salje u funkcije
	generate_array(array); //generiranje random brojeva za array
	counting_sort(array);
	generate_array(array);
	bubble(array);
	generate_array(array);
	insertion(array);
	generate_array(array);
	selection(array);
	return 0;
}

