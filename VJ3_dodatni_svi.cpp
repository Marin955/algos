/* Vise zadataka u jednom kodu, ne izgleda lijepo i nije optimizirano. Neki od zadataka su ispitivanje koji je sort bolji za nizove 
 s padajucim elementima, napisati shell sort, ispitati vrijeme sortiranja za razlicite podjele intervala za shell sort itd. */

#include <iostream>
#include <chrono>
#include <random>
#include <cmath>

int n = 50000;

void generate_array_all_same(int *arr) {
	int i;
	for (i=0; i<=n; i++) {
		arr[i] = 234;
	}
}

void generate_array_descending(int *arr) {
	int i;
	for (i=0; i<n; i++) {
		arr[i] = n-i;
	}
}

void generate_array_random(int *arr, int length) {
	int i;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //broj u nanosekundama koji se mijenja kako bi se dobili random brojevi
	std::mt19937 mersenne(seed); //njega se ubacuje u mersenne algoritam
	std::uniform_int_distribution<int> dist(1,10000000);
	for (i=0; i<length; i++) { //punjenje array-a s random brojevima
		arr[i] = dist(mersenne);
	}
}

void selection(int niz[], int m) {
	int i, min, mjesto, temp, j;
	for (i=0; i<m; i++) { //"i" predstavlja prvi nesortirani clan
		min = niz[i]; //prvi clan za pocetak najmanji
		for (j=i; j<m; j++) { //prolazak kroz array
			if (niz[j] < min) { //ako ima nesto manje od trenutnog minimuma, to je sad novi minimum
				min = niz[j];
				mjesto=j;
			}
		}
		temp = niz[i]; //swap
		niz[i] = niz[mjesto];
		niz[mjesto] = temp;
	}
}

void insertion(int niz[], int m) { //m je duljina niza
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

void shell_sort(int niz[], int chunks[]) { //chunks polje su zapravo razmaci (gaps) koji su generirani pomocu funkcije ispod
	int g, i, j, temp, chunk_size, counter=0, new_n=n;
	for (g=sizeof(chunks)/sizeof(chunks[0]); g>=0; g--) { //sizeof cijelo polje / sizeof jedan element mi daje broj elemenata u polju. Prolazak kroz chunks polje
		chunk_size = chunks[g];
		for(int i=chunk_size; i<n; i=i+chunk_size) // i je element s kojim se usporeduje
		{
			temp=niz[i];
			for(j=i-chunk_size; j>=0 && niz[j]>temp; j=j-chunk_size) //j prolazi kroz niz i usporeduje sa i
			{
				niz[j+chunk_size]=niz[j]; //swap
			}
			niz[j+chunk_size]=temp; //swap
		}
	}
}

int* generate_gaps_case(int case_num) { //funkcija koja generira razmake za shellsort, treba za 5. zadatak
	int *case_p;
	int m=1, i, j, counter=0;
	int* working_p = new int[n];
	switch (case_num) { //razliciti slucajevi za nizove iz zadatka
		case 1: 		//N/2
			m=n/2;
			while (m>0) {
				working_p[counter] = m;
				m=m/2;
				counter++;
			}
			case_p = new int[counter];
			for (i=0; i<counter; i++) {
				case_p[i] = working_p[counter-i-1];
			}
			break;
		case 2:			//n^3-1 / 2
			while (m<n/3) {
				m = (pow(3, counter)-1)/2;
				working_p[counter] = m;
				counter++;
			}
			case_p = new int[counter];
			for (i=0; i<counter-1; i++) {
				case_p[i] = working_p[i+1];
			}
			break;
		case 3: 		//2^n - 1
			while (m<n) {
				m = pow(2,counter+1) - 1;
				working_p[counter] = m;
				counter++;
			}
			case_p = new int[counter];
			for (i=0; i<counter-1; i++) {
				case_p[i] = working_p[i];
			}
			break;
		case 4:			//p^i * q^j
			float x;
			for (i=0; i<17; i++) {
				for (j=0; j<16; j++) {
					x = (pow(2,i) * pow(3,j));
					if (x < n) {
						working_p[counter] = pow(2,i) * pow(3,j);
						counter++;
					}
				}
			}
			insertion(working_p, counter);
			case_p = new int[counter];
			for (i=0; i<counter; i++) {
				case_p[i] = working_p[i];
			}
			break;
		case 5: 			//prekomplicirana funkcija, samo sam dao clanove za niz od 50000 clanova
			int working_array [8] = {1, 8, 23, 77, 281, 1073, 4193, 16577};
			case_p = working_array;
			break;
	}
	return case_p;
}

int main () {
	int array [n];
	int f, e, size_counter;
	
	std::cout << "1. Koji je brzi, selection ili insertion za array s istim clanovima?" << std::endl << std::endl; //dodatni zadatak 1
	generate_array_all_same(array);
	
	auto start_insertion = std::chrono::steady_clock::now(); //auto tip varijable prepusta kompajleru da odredi koji tip varijable upotrijebiti, ne znam sta se koristi za mjerenje vremena...
	insertion(array, n);
	auto end_insertion = std::chrono::steady_clock::now();
	auto diff_insertion = end_insertion - start_insertion;
	std::cout << "Vrijeme potrebno za insertion: " << std::chrono::duration <double, std::milli> (diff_insertion).count() << " ms" << std::endl;
	
	auto start_selection = std::chrono::steady_clock::now();
	selection(array, n);
	auto end_selection = std::chrono::steady_clock::now();
	auto diff_selection = end_selection - start_selection;
	std::cout << "vrijeme potrebno za selection: " << std::chrono::duration <double, std::milli> (diff_selection).count() << " ms" << std::endl << std::endl;
	if (diff_selection > diff_insertion)
		std::cout << "Insertion je brzi. " << std::endl << std::endl;
	else std::cout << "Selection je brzi." << std::endl << std::endl;
	std::cout << "Insertion ne usporeduje sa svim elementima kad vidi da su dva susjedna ista" << std::endl << std::endl;
	
	std::cout << "2. Koji je brzi, selection ili insertion za array sa silaznim clanovima?" << std::endl << std::endl; //dodatni zadatak 2
	generate_array_descending(array);
	
	auto start_insertion2 = std::chrono::steady_clock::now(); //auto tip varijable prepusta kompajleru da odredi koji tip varijable upotrijebiti, ne znam sta se koristi za mjerenje vremena...
	insertion(array, n);
	auto end_insertion2 = std::chrono::steady_clock::now();
	auto diff_insertion2 = end_insertion2 - start_insertion2;
	std::cout << "Vrijeme potrebno za insertion: " << std::chrono::duration <double, std::milli> (diff_insertion2).count() << " ms" << std::endl;
	
	generate_array_descending(array);
	auto start_selection2 = std::chrono::steady_clock::now();
	selection(array, n);
	auto end_selection2 = std::chrono::steady_clock::now();
	auto diff_selection2 = end_selection2 - start_selection2;
	std::cout << "vrijeme potrebno za selection: " << std::chrono::duration <double, std::milli> (diff_selection2).count() << " ms" << std::endl << std::endl;
	if (diff_selection2 > diff_insertion2)
		std::cout << "Insertion je brzi." << std::endl << std::endl;
	else std::cout << "Selection je brzi." << std::endl << std::endl;
	std::cout << "(Razlika je znacajna, selection ce napraviti jako malo zamjena, dok insertion svaki put pomice cijeli array za jedan)" << std::endl << std::endl;
	
	std::cout << "3. Ne znam tocno. Pretpostavka je da je nepotrebno konstantno usporedivanje sa svim elementima, sto radi selection sort. " << std::endl;
	std::cout << "4. Radnik treba odabrati sort koji ima najmanje zamjena za neki random array, a to je selection sort." << std::endl << std::endl;
	
	std::cout << "5. Niz s kojim se usporeduje: ((n^3 - 1) / 2)" << std::endl;
	generate_array_random(array, n);
	auto start_shell_2nd_case = std::chrono::steady_clock::now();
	shell_sort(array, generate_gaps_case(2));
	auto end_shell_2nd_case = std::chrono::steady_clock::now();
	auto diff_shell_2nd_case = end_shell_2nd_case - start_shell_2nd_case;
	std::cout << "Vrijeme potrebno za shellsort: " << std::chrono::duration <double, std::milli> (diff_shell_2nd_case).count() << " ms" << std::endl << std::endl;
	std::cout << "Ostali nizovi: " << std::endl << std::endl;
	generate_array_random(array, n);
	auto start_shell_1st_case = std::chrono::steady_clock::now();
	shell_sort(array, generate_gaps_case(1));
	auto end_shell_1st_case = std::chrono::steady_clock::now();
	auto diff_shell_1st_case = end_shell_1st_case - start_shell_1st_case;
	std::cout << "Vrijeme potrebno za shellsort N/2: " << std::chrono::duration <double, std::milli> (diff_shell_1st_case).count() << " ms" << std::endl;
	generate_array_random(array, n);
	auto start_shell_3rd_case = std::chrono::steady_clock::now();
	shell_sort(array, generate_gaps_case(3));
	auto end_shell_3rd_case = std::chrono::steady_clock::now();
	auto diff_shell_3rd_case = end_shell_3rd_case - start_shell_3rd_case;
	std::cout << "Vrijeme potrebno za shellsort 2^n - 1: " << std::chrono::duration <double, std::milli> (diff_shell_3rd_case).count() << " ms" << std::endl;
	generate_array_random(array, n);
	auto start_shell_4th_case = std::chrono::steady_clock::now();
	shell_sort(array, generate_gaps_case(4));
	auto end_shell_4th_case = std::chrono::steady_clock::now();
	auto diff_shell_4th_case = end_shell_4th_case - start_shell_4th_case;
	std::cout << "Vrijeme potrebno za shellsort p^i * q^j: " << std::chrono::duration <double, std::milli> (diff_shell_4th_case).count() << " ms" << std::endl;
	generate_array_random(array, n);
	auto start_shell_5th_case = std::chrono::steady_clock::now();
	shell_sort(array, generate_gaps_case(5));
	auto end_shell_5th_case = std::chrono::steady_clock::now();
	auto diff_shell_5th_case = end_shell_5th_case - start_shell_5th_case;
	std::cout << "Vrijeme potrebno za shellsort (1, 8, 23...): " << std::chrono::duration <double, std::milli> (diff_shell_5th_case).count() << " ms" << std::endl << std::endl;
	
	std::cout << "Ne znam koji je zakljucak ovdje, prvi niz je jedan od optimalnijih za shellsort. p^i * q^j ispada najoptimalniji." << std::endl << "(generiranje nizova mi ulazi u vrijeme izvodenja sorta, nije mi se dalo to vaditi u posebnu funkciju, to malo utjece na vrijeme izvodenja)" << std::endl << std::endl;
	
	int N;
	std::cout << "6. zadatak" << std::endl << std::endl;
	auto ins_start = std::chrono::steady_clock::now(); //uvodenje svih varijabli koje su potrebne
	auto ins_end = std::chrono::steady_clock::now();
	auto sel_start = std::chrono::steady_clock::now();
	auto sel_end = std::chrono::steady_clock::now();
	auto diff_insN = ins_end - ins_start;
	auto diff_ins2N = ins_end - ins_start;
	auto diff_selN = sel_end - sel_start;
	auto diff_sel2N = sel_end - sel_start;
	float ratio_ins, ratio_sel;
	std::cout << "|\t N |\t selection (N) \t|\t insertion (N) \t|\t Omjer ins (2N/N) \t|\t Omjer sel (2N/N)" << std::endl;
	for (N=1000; N<=32000; N*=2) {
		int ins_sel_array [N];
		
		generate_array_random(ins_sel_array, N);
		ins_start = std::chrono::steady_clock::now();
		insertion(ins_sel_array, N);
		ins_end = std::chrono::steady_clock::now();
		diff_insN = ins_end - ins_start;
		
		generate_array_random(ins_sel_array, 2*N);
		ins_start = std::chrono::steady_clock::now();
		insertion(ins_sel_array, 2*N);
		ins_end = std::chrono::steady_clock::now();
		diff_ins2N = ins_end - ins_start;
		
		ratio_ins = (std::chrono::duration <double, std::milli> (diff_insN).count()) / (std::chrono::duration <double, std::milli> (diff_ins2N).count());
		
		generate_array_random(ins_sel_array, N);
		sel_start = std::chrono::steady_clock::now();
		selection(ins_sel_array, N);
		sel_end = std::chrono::steady_clock::now();
		diff_selN = sel_end - sel_start;
		
		generate_array_random(ins_sel_array, 2*N);
		sel_start = std::chrono::steady_clock::now();
		selection(ins_sel_array, 2*N);
		sel_end = std::chrono::steady_clock::now();
		diff_sel2N = sel_end - sel_start;
		
		ratio_sel = (std::chrono::duration <double, std::milli> (diff_selN).count()) / (std::chrono::duration <double, std::milli> (diff_sel2N).count());
		std::cout << "|\t" << N << "\t|\t" << std::chrono::duration <double, std::milli> (diff_selN).count() << " ms" << "\t|\t" << std::chrono::duration <double, std::milli> (diff_insN).count() << " ms"  << "\t|\t" << ratio_ins << "\t|\t" << ratio_sel << "|" << std::endl;
	}
	std::cout << std::endl << "Kao omjer dobijemo 1/4. To je zato jer omjer kvadratnih vremenskih kompleksnosti daje taj rezultat: " << std::endl << "(n)^2 / (2n)^2 = 1/4" << std::endl << std::endl;
	
	std::cout << "7. zadatak zahtjeva mijenjanje svih funkcija iz int u float jer funkcije za distribucije tako zahtjevaju, not in the mood" << std::endl;
	/* ----Samo kao primjer funkcije za kreiranje gauss distribucije----
	void generate_array_random_gauss(int *arr, int length) {
	int i;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //broj u nanosekundama koji se mijenja kako bi se dobili random brojevi
	std::mt19937 mersenne(seed); //njega se ubacuje u mersenne algoritam
	std::normal_distribution<double> dist(1.0,9.0);
	for (i=0; i<length; i++) { //punjenje array-a s random brojevima
		arr[i] = dist(mersenne);
	}
	}
 	*/
	return 0;
}
