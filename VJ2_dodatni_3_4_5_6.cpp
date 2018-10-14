/* Napisati osnovne operacije na stacku i testirati ih */

#include <iostream>
#include <chrono>
#include <random>

typedef struct neki_Stack {
	int broj;
	neki_Stack *next;
} neki_Stack;

void fill_stack(neki_Stack *p, int n) { //popunjavanje stacka brojevima od 1 do nekog
	int i;
	neki_Stack *filler = new neki_Stack;
	filler = p;
	for (i=0; i<n; i++) {
		filler->broj = i;
		filler->next = new neki_Stack;
		filler = filler->next;
	}
	filler = NULL; //zadnji element pokazuje na NULL
}

void print_stack(neki_Stack *p, int n) { //printanje cijelog stacka
	int i;
	neki_Stack *printer = new neki_Stack;
	printer = p;
	std::cout << "Cijeli stack: " << std::endl;
	for (i=0; i<n; i++) {
		std::cout << printer->broj << " ";
		printer = printer->next;
	}
	std::cout << std::endl << std::endl;
}

int StPop(neki_Stack *p) { //napravljeno razlicito od 2. vjezbe, tamo je bio zaseban pointer koji je pokazivao na prvi clan stacka, sad je prvi clan ujedno i pointer na vrh stacka
	int final; //funkcija mora vratit vrijednost prvog elementa
	final = p->broj;
	neki_Stack *temp = new neki_Stack;
	temp->broj = p->broj; 
	temp->next = p->next;
	p->broj = temp->next->broj;
	p->next = temp->next->next;
	delete(temp);
	return final;
}

int StPeek(neki_Stack *p) { //3. zadatak
	return p->broj;
}

void deleter(neki_Stack *p) { //4. zadatak
	neki_Stack *search = new neki_Stack;
	neki_Stack *temp = new neki_Stack;
	search = p;
	while (search->next->next->next != NULL) { //cilj je da se search pointer postavi na predzadnji element stacka
		search = search->next;
	}
	temp = search->next; //spremanje zadnjeg elementa u temp cisto da ga se moze obrisat s delete()
	search->next = NULL; //preusmjeravanje predzadnjeg na NULL sto ga cini zadnjim
	delete(temp);
}

void linked_list_swap(neki_Stack *p, int n) { //5. zadatak
	int i;
	neki_Stack *search = new neki_Stack; //cilj je search postavit na k-1 element stacka
	neki_Stack *temp1 = new neki_Stack; //za spremanje k-tog elementa
	neki_Stack *temp2 = new neki_Stack; //za spremanje k+1-og elementa
	neki_Stack *temp3 = new neki_Stack; //za spremanje k+2-og elementa
	search = p;
	for(i=0; i<n-1; i++) {
		search = search->next;
	}
	temp1 = search->next;
	temp2 = search->next->next;
	temp3 = search->next->next->next; //									 -----------------
	search->next = temp2; //preusmjeri k-1 na k+1							|				 |
	temp2->next = temp1; //presumjeri k+1 na k						k-1		k ----- k+1		k+2
	temp1->next = temp3; //presumjeri k na k+2						 |				 |
}								//									 ----------------

void fill_stack_random(neki_Stack *p, int n) { //isto kao i fill_stack() samo s random brojevima da trazenje max-a ima smisla
	int i;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 mersenne(seed);
	std::uniform_int_distribution<int> dist(1,100);
	neki_Stack *filler = new neki_Stack;
	filler = p;
	for (i=0; i<n; i++) {
		filler->broj = dist(mersenne);
		filler->next = new neki_Stack;
		filler = filler->next;
	}
	filler = NULL;
}

int get_max(neki_Stack *p) { //6. zadatak
	int max=0;
	neki_Stack *search = new neki_Stack;
	search = p;
	while (search->next != NULL) { //prodi cijelu listu
		if (search->broj > max) 
			max = search->broj;
			search = search->next;
	}
	return max;
}

int main() {
	int length, position;
	neki_Stack *top_of_stack = new neki_Stack;
	std::cout << "Duljina stacka: ";
	std::cin >> length;
	fill_stack(top_of_stack, length);
	print_stack(top_of_stack, length);
	std::cout << "Popped element: " << StPop(top_of_stack) << std::endl << std::endl;
	print_stack(top_of_stack, length-1);
	std::cout << "StPeek vrijednost: " << StPeek(top_of_stack) << std::endl << std::endl; //dodatni zadatak 3
	print_stack(top_of_stack, length-1);
	std::cout << "Deleting last..." << std::endl << std::endl; //dodatni zadatak 4
	deleter(top_of_stack);
	print_stack(top_of_stack, length-2); //brisanjem se zadnji element postavi na NULL, ako bi se isao ispisati sa length-1, program se srusi jer tamo vise nema nista (bar ja mislim da je do tog)
	std::cout << "Element stacka za zamjenu (izmedu 0 i " << length-2 << "): ";
	std::cin >> position;
	linked_list_swap(top_of_stack, position); //dodatni zadatak 5
	print_stack(top_of_stack, length-2);
	std::cout << "---Trazenje max vrijednosti u random stacku: ---" << std::endl << std::endl; //dodatni zadatak 6
	fill_stack_random(top_of_stack, length);
	print_stack(top_of_stack, length);
	std::cout << "Max vrijednost: " << get_max(top_of_stack) << std::endl << std::endl;
	return 0;
}


