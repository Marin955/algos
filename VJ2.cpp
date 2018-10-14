/* Rijesiti unos matematickog izraza oblika (a+(b*c)), npr. (7*(6-(2/2))) koristeci stack */


#include <iostream>
#include <string>

typedef struct Brojevi { //element stacka s brojevima
	double num;
	Brojevi *next;
} Brojevi;

typedef struct Operatori { //element stacka s operatorima
	char operatorx;
	Operatori *next;
} Operatori;

void StPushNum (double x, Brojevi *Sp) {
	Brojevi *tmp;
	tmp = new Brojevi; //pravi se novi element stacka koji još s nicim nije povezan
	tmp->num = x; //daje mu se vrijednost
	tmp->next = Sp->next; //kidanje veze izmedu Sp(vrha stacka) i onog na sta Sp pokazuje, prvo se temp poveze na isto ono na sto je povezan Sp... 
	Sp->next = tmp; // Sp se povezuje sa tempom
					// Prije: Sp -> nesto --- Sad: Sp -> temp -> nesto
}

void StPushOp (char x, Operatori *Sp) {
	Operatori *tmp;
	tmp = new Operatori; //isto kao i kod StPushNum()
	tmp->operatorx = x;
	tmp->next = Sp->next;
	Sp->next = tmp;
}

void StPopNum (Brojevi *Sp) {
	Brojevi *tmp; //cilj je prijeci sa       Sp -> 1. element -> 2. element       na       Sp -> 2.element
	tmp = Sp->next; //1. element nazivam tmp (njegov "next" clan pokazuje na 2. element)
	Sp->next = tmp->next;  //Sad Sp pokazuje na 2. clan
	delete(tmp); //dealociranje memorije 1. elementa (brisanje)
}

void StPopOp (Operatori *Sp) {
	Operatori *tmp;  // isto kao i StPopNum()
	tmp = Sp->next;
	Sp->next = tmp->next;
	delete(tmp);
}

void solve (std::string str) {
	int i;
	char char_value_of_string;
	double result, integer_value_of_string;
	Brojevi *number_stack_top; //pointer na stack s brojevima
	Operatori *operator_stack_top; //pointer na stack s operatorima
	number_stack_top = new Brojevi; //alokacija memorije za pointer na brojeve
	operator_stack_top = new Operatori; //alokacija memorije za pointer na operatore
	number_stack_top->next = NULL; //pocinjemo s praznim stackom, dakle vrh stacka pokazuje na NULL
	operator_stack_top->next = NULL; //same
	for (i=0; i<str.length(); i++) { //prolazak kroz string i slucajevi
		if (str.at(i) == '('); //ne treba nista radit --- str.at(i) pristupa i-tom elementu stringa
		else if (str.at(i) == ' '); //ne treba nista radit
		else if (isdigit(str.at(i))){ //spremanje broja u stack s brojevima --- isdigit je boolean za provjeru broja
			integer_value_of_string = (double)str.at(i) - 48; //konverzija char-a u int (brojevi pocinju od 48, double je zbog funkcije StPushNum() 
															  //koja ce nekad morat ubacivat double vrijednosti...zbog moguceg dijeljenja dva broja)
			StPushNum(integer_value_of_string, number_stack_top);
	}
		else if (str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '/' || str.at(i) == '*' ){ //dodavanje u stack s operatorima
			char_value_of_string = str.at(i);
			StPushOp(char_value_of_string, operator_stack_top);
		}
		else if (str.at(i) == ')') { //izvrsavanje operacije (razdvojeno na 4. slucaja)
			if (operator_stack_top->next->operatorx == '+') { //ako je zadnja stvar na stacku +...
				result = number_stack_top->next->num + number_stack_top->next->next->num; //zbroji zadnje dvije stvari na stacku s brojevima...
				StPopNum(number_stack_top);
				StPopNum(number_stack_top);
				StPopOp(operator_stack_top); //obrisi zadnja dva broja i jedan operator...
				StPushNum(result, number_stack_top); //zapisi rezultat u stack s brojevima
			}
			else if (operator_stack_top->next->operatorx == '-') { //same
				result = number_stack_top->next->num - number_stack_top->next->next->num;
				StPopNum(number_stack_top);
				StPopNum(number_stack_top);
				StPopOp(operator_stack_top);
				StPushNum(result, number_stack_top);
			}
			else if (operator_stack_top->next->operatorx == '*') { //same
				result = number_stack_top->next->num * number_stack_top->next->next->num;
				StPopNum(number_stack_top);
				StPopNum(number_stack_top);
				StPopOp(operator_stack_top);
				StPushNum(result, number_stack_top);
			}
			else if (operator_stack_top->next->operatorx == '/') { //same
				result = number_stack_top->next->num / number_stack_top->next->next->num;
				StPopNum(number_stack_top);
				StPopNum(number_stack_top);
				StPopOp(operator_stack_top);
				StPushNum(result, number_stack_top);
			}
		}
		else std::cout << "Nepravilno upisan izraz" << std::endl;
	}
	std::cout << "Rezultat: " << number_stack_top->next->num;
}

int main() {
	std::string unos;
	std::getline(std::cin,unos); //ucitavanje stringa
	solve(unos);
	return 0;
}
