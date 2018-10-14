/* Napraviti quicksort koji koristi insertion sort za podnizove koji sadrze manje od 10 clanova i ispitati vrijeme sortiranja */


#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int arr1length = 1000, arr2length = 5000, arr3length = 10000, arr4length = 20000, arr5length = 50000, arr6length = 100000, arr7length = 200000, arr8length = 500000;

int* generate_random_array(int num_of_elements) { //generiranje random elemenata i vracanje arraya
	int i;
	int* array = new int[num_of_elements];
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 mersenne(seed);
	uniform_int_distribution<int> dist(1, 100);
	for (i=0; i<num_of_elements; i++) {
		array[i] = dist(mersenne);
	}
	return array;
}

void swaps(int *x, int *y) //funkcija koja mijenja vrijednosti dva pointera
{
    int temp = *y;
    *y = *x;
    *x = temp;
}

void insertion(int *niz, int m) { //treba za nizove manje od 10 u quicksortu
    int temp, j, i;
    for(i=1; i<m; i++)	{
        temp = niz[i];
        j = i-1;
        while(j>=0 && niz[j]>temp)
        {
            niz[j+1] = niz[j];
            j--;
        }
        niz[j+1] = temp;
    }
}

void quickSort(int *arr, int min, int max) //argumenti su: array za sortiranje, minimum tog arraya, maksimum tog arraya
{
    int i = min, j = max, k; //"i" i "j" prolaze kroz array i usporeduju sa pivotom
    int pivot = arr[(min+max)/2]; //pivot je neki broj sa sredine arraya
    while(i <= j) // sve dok se "i" i "j" ne sretnu negdje na sredini, radi sljedece...
    {
        while(arr[i] < pivot) //trazi "i" koji ce biti veci od pivota
            i++;
        while(arr[j] > pivot) //trazi "j" koji ce biti manji od pivota
            j--;
        if(i <= j)
        {
            swaps(&arr[i],&arr[j]); //kad ih nade, zamijeni
            i++; //pomakni i & j dalje
            j--;
        }
    }
    if(min + 10 < j) //ako je razmak izmedu minimuma i "j" veci od 10, posalji array tog razmaka u rekurziju
        quickSort(arr, min, j);
    else 
		insertion(&arr[min], j-min+1); //ako je manji napravi insertion sort
    if(i + 10 < max) //isto za drugu "polovicu" koja nastaje quicksortom
        quickSort(arr, i, max);
    else 
    	insertion(&arr[i], max-i+1);
}

double average_time(int length) { 
	int i;
	double result, sum=0;
	int* array = new int[length];
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	double* times = new double[1000]; //polje u koje spremam pojedina trajanja sortiranja
	for (i=0; i<1000; i++) {
		array = generate_random_array(length); //generiraj random array
		start = std::chrono::steady_clock::now(); //pocni mjerit vrijeme
		quickSort(array, 0, length); 
		end = std::chrono::steady_clock::now(); //zaustavi vrijeme
		diff = end - start;
		times[i] = chrono::duration <double, std::milli> (diff).count(); //konvertiraj u milisekunde i spremi u array
	}
	for (i=0; i<1000; i++) { //racunanje prosjeka i vracanje te vrijednosti
		sum = sum + times[i];
	}
	return sum/1000;
}

int main() {
	int i;
	cout << "|\tDuljina arraya \t|\t Prosjecno vrijeme trajanja quickSorta \t|" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "|\t" << arr1length << "\t\t|\t\t" << average_time(arr1length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr2length << "\t\t|\t\t" << average_time(arr2length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr3length << "\t\t|\t\t" << average_time(arr3length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr4length << "\t\t|\t\t" << average_time(arr4length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr5length << "\t\t|\t\t" << average_time(arr5length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr6length << "\t\t|\t\t" << average_time(arr6length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr7length << "\t\t|\t\t" << average_time(arr7length) << " ms \t\t\t|" << endl;
	cout << "|\t" << arr8length << "\t\t|\t\t" << average_time(arr8length) << " ms \t\t\t|" << endl;
	
	return 0;
}
