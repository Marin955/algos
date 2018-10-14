/* Napraviti counting sort kao primjer algoritma s ovisnosti O(n) */

#include <iostream>
#include <random>
#include <chrono>

//Program se srusi na Dev-CPPu iz ne znam kojeg razloga, na linuxu sve radi savrseno. Kod je ispravan. 

int arr1length=1000, arr2length=2000, arr3length=3000, arr4length=5000, arr5length=7000, arr6length=10000, arr7length=15000, arr8length=20000, arr9length=25000, arr10length=30000;

using namespace std;

int* generate_random_array(int num_of_elements) {
	int i;
	int* array = new int[num_of_elements];
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 mersenne(seed);
	uniform_int_distribution<int> dist(1, num_of_elements); //generianje random brojeva od 1 do neke duljine
	for (i=0; i<num_of_elements; i++) {
		array[i] = dist(mersenne);
	}
	return array;
}

void counting_sort(int* a_arr, int n, int k) { //kod prati pdf s predavanja
	int i, j;
	int* b_arr = new int[n];
	int* c_arr = new int[n];
	for (i=0; i<n; i++) {
		c_arr[i] = 0;
	}
	for (j=0; j<n; j++) {
		c_arr[a_arr[j]] = c_arr[a_arr[j]] + 1;
	}
	for (j=1; j<k; j++) {
		c_arr[j] = c_arr[j] + c_arr[j-1];
	}
	for (j=n; j>=0; j--) {
		b_arr[c_arr[a_arr[j]]] = a_arr[j];
		c_arr[a_arr[j]] = c_arr[a_arr[j]] - 1;
	}
}

float average_time(int length) {  //funkcija koja vraca prosjecno vrijeme 200 sortiranja
	int i;
	float result, sum=0;
	int* array = new int[length];
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	float* times = new float[200]; //polje u koje spremam pojedina trajanja sortiranja
	for (i=0; i<200; i++) {
		array = generate_random_array(length); //generiraj random array
		start = chrono::steady_clock::now(); //pocni mjerit vrijeme
		counting_sort(array, length, length);
		end = chrono::steady_clock::now(); //zaustavi vrijeme
		diff = end - start;
		times[i] = chrono::duration <float, std::milli> (diff).count(); //konvertiraj u milisekunde i spremi u array
	}
	for (i=0; i<200; i++) { //racunanje prosjeka i vracanje te vrijednosti
		sum = sum + times[i];
	}
	return sum/200;
}

int main () {
	cout << "|\tDuljina arraya \t|\t Prosjecno vrijeme trajanja countingSorta \t|" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "|\t" << arr1length << "\t\t|\t\t" << average_time(arr1length) << " ms \t\t\t|" << endl; 
	cout << "|\t" << arr2length << "\t\t|\t\t" << average_time(arr2length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr3length << "\t\t|\t\t" << average_time(arr3length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr4length << "\t\t|\t\t" << average_time(arr4length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr5length << "\t\t|\t\t" << average_time(arr5length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr6length << "\t\t|\t\t" << average_time(arr6length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr7length << "\t\t|\t\t" << average_time(arr7length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr8length << "\t\t|\t\t" << average_time(arr8length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr9length << "\t\t|\t\t" << average_time(arr9length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr10length << "\t\t|\t\t" << average_time(arr10length) << " ms \t\t\t|" << endl;
	return 0;
}
