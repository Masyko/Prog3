#include "pch.h"
#include "Cards.h"

namespace Prog3 {
	const char* msgs[] = { "0. Quit or select other coloda", "1. Add random card", "2. Add card", "3. Suit card by num", "4. Rang card by num" , "5. New group by suit", "6. Sort", "7. Print" };
	const char* cmsgs[] = { "0. Quit", "1. Empty constructor", "2. Constructor 2", "3. Constructor 3(by card)" };
	const char* msgsM[] = { "0. Quit", "1. Select coloda", "2. Add coloda", "3. Copy coloda", "4. Print all" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	const int NMsgsM = sizeof(msgsM) / sizeof(msgsM[0]);
	const int NcMsgs = sizeof(cmsgs) / sizeof(cmsgs[0]);
	int(*fptr[])(Cards&) = { NULL, D_Add_Card_R, D_Add_Card, D_Suit_card_by_num, D_Rang_card_by_num, NULL, D_Sort, D_Print };

	int Cards::find_card_from_coloda(int s, int r) {
		int k = 0;
		for (int i = 0; i < num; i++) {
			if (coloda[i].suit == s && coloda[i].rank == r) {
				k++;
			}
		}
		return k;
	}
	int D_Add_Card_R(Cards& cold) {
		cold.add_card_by_random();
		cold.print(std::cout);
		return 1;
	}

	int D_Add_Card(Cards& cold) {
		std::cout << "Your Card" << std::endl;
		bool ind = true;
		while (ind) {
			std::cout << "Input Suit" << std::endl;
			std::cout << "Suit : Heart - 1, Diamod - 2, Club - 3, Spade - 4" << std::endl;
			int b;
			while (getNum(b) < 0 || b < 1 || b > 4) {
				std::cout << "You are wrong. Please,try again!" << std::endl;
			}
			std::cout << "Input Rank" << std::endl;
			std::cout << "Rank : Two - 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace" << std::endl;
			int a;
			while (getNum(a) < 0 || a < 2 || a > 14) {
				std::cout << "You are wrong. Please,try again!" << std::endl;
			}
			ind = false;
			ind = cold.add_card_from_vvod(a, b);
		}
		cold.print(std::cout);
		return 1;
	}

	int D_Suit_card_by_num(Cards& cold) {
		int n;
		std::cout << "Please, put num of your card: " << std::endl;
		while (getNum(n) == -1 || n >= cold.getcnum()) {
			std::cout << "You are wrong. Please,try again!" << std::endl;
		}
		cold.suit_card_by_num(n);
		return 1;
	}

	int D_Rang_card_by_num(Cards& cold) {
		int n;
		std::cout << "Please, put num of your card: " << std::endl;
		while (getNum(n) == -1 || n >= cold.getcnum()) {
			std::cout << "You are wrong. Please,try again!" << std::endl;
		}
		cold.rang_card_by_num(n);
		return 1;
	}

	int D_New_group_by_suit(Cards& cold, Cards*& mas, int& num) {
		std::cout << "Set the suit that you interested in: " << std::endl;
		std::cout << "Suit : Heart - 1, Diamod - 2, Club - 3, Spade - 4" << std::endl;
		int s;
		while (getNum(s) == -1 || s > 4 || s < 1) {
			std::cout << "You are wrong. Please,try again!" << std::endl;
		}
		cold.new_group_by_suit(s, mas, num);
		delete& mas[num];
		return 1;
	}

	int D_Sort(Cards& cold) {
		cold.sort_by_suit_and_rank();
		cold.print(std::cout);
		return 1;
	}

	int D_Print(Cards& cold) {
		cold.print(std::cout);
		return 1;
	}

	int dialog(const char* msgs[], int N)
	{
		const char* errmsg = "";
		int i, n = 0;
		do {
			puts(errmsg);
			errmsg = "You're wrong. Repeat, please!";
			for (i = 0; i < N; ++i)
				puts(msgs[i]);
			puts("Make our choice: ");
			getNum(n);
		} while (n < 0 || n >= N);
		return n;
	}
	int select_constructor(Cards*& mas, int& num) {
		static Cards coloda_kart;
		int rc;
		rc = dialog(cmsgs, NcMsgs);
		if (rc == 0) {
			return 0;
		}
		if (rc == 1) {
			std::cout << "max size = " << coloda_kart.getMaxSize() << std::endl;
			coloda_kart.print(std::cout);
			mas[num] = coloda_kart;
			num++;
		}
		if (rc == 2) {
			std::cout << "Input count of cards you want-> " << std::endl;
			int inp;
			while (getNum(inp) < 0 || inp > coloda_kart.getMaxSize() || inp < 0)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			static Cards coloda_kart1(inp);
			mas[num].copy(coloda_kart1);
			mas[num].print(std::cout);
			num++;
			delete& coloda_kart1;
		}
		if (rc == 3){
			std::cout << "input Your one card-> " << std::endl;
			std::cout << "input Suit-> " << std::endl;
			Card c;
			while (getNum(c.suit) < 0 || c.suit < 1 || c.suit > 4)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			std::cout << "input Rank-> " << std::endl;
			while (getNum(c.rank) < 0 || c.rank < 2 || c.rank > 14)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			static Cards coloda_kart1(c);
			coloda_kart.copy(coloda_kart1);
			coloda_kart.print(std::cout);
			mas[num] = coloda_kart;
			num++;
			delete& coloda_kart1;
		}
		std::cout << std::endl;
		return 1;
	}
	int getNum(int& a)
	{
		std::cin >> a;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			return -1;
		}
		std::cin.clear();
		std::cin.ignore();
		return 1;
	}

	Cards::Cards() {
		coloda = new Card[SZ];
		int k = 0;
		num = 0;
		for (int i = 1; i < 5; i++) {
			for (int j = 2; j < 15; j++) {
				coloda[k].rank = j;
				coloda[k].suit = i;
				k++;
				num++;
			}
		}
	}  

	/*Cards::~Cards() {
		delete coloda;
		num = 0;
		std::cout << " Your coloda was destroyed" << std::endl;
	}*/

	Cards::Cards(int n) {
		coloda = new Card[SZ];
		num = 0;
		for (int i = 0; i < n; i++) {
			bool ind = true;
			while (ind) {
				coloda[i].suit = 1 + rand() % 4;
				coloda[i].rank = 2 + rand() % 13;
				ind = false;
				num++;
				int k = 0;
				for (int j = 0; j < i; j++) {
					if (coloda[j].rank == coloda[i].rank && coloda[j].suit == coloda[i].suit) {
						k++;
					}
				}
				if (k) {
					num--;
					ind = true;
				}
				else {
					ind = false;
				}
			}
		}
	}

	Cards::Cards(Card c) {
		coloda = new Card[1];
		num = 0;
		coloda[0] = c;
		num++;
	}

	void Cards::copy(Cards c) {
		delete coloda;
		coloda = new Card[c.num];
		for (int i = 0; i < c.num; i++) {
			coloda[i].rank = c.coloda[i].rank;
			coloda[i].suit = c.coloda[i].suit;
		}
		num = c.num;
	}

	bool Cards::add_card_from_vvod(int a, int b) {
		bool ind = false;
		num++;
		if (num >= SZ) {
			std::cout << "Overflow!" << std::endl;
			return false;
		}
		int k = find_card_from_coloda(b, a);
		if (k) {
			num--;
			ind = true;
			std::cout << "You are wrong. Please,try again!" << std::endl;
		}
		else {
			coloda[num - 1].suit = b;
			coloda[num - 1].rank = a;
			ind = false;
		}
		return ind;
	}

	void Cards::add_card_by_random() {
		std::cout << "Your Card: " << std::endl;
		if (num >= SZ) {
			std::cout << "Overflow!" << std::endl;
			return;
		}
		bool ind = true;
		while (ind)
		{
			int s;
			s = rand() % 4 + 1;
			int r;
			r = rand() % 13 + 2;
			ind = false;
			num++;
			int k = find_card_from_coloda(s, r);
			if (k) {
				ind = true;
				num--;
			}
			else {
				coloda[num - 1].suit = s;
				coloda[num - 1].rank = r;
				ind = false;
				break;
			}
			std::cout << "Suit: " << s << std::endl;
			std::cout << "Rank: " << r << std::endl;
		}

	}

	void Cards::suit_card_by_num(int n) const {
		std::cout << "Suit of your card is: " << coloda[n].suit << std::endl;
	}

	void Cards::rang_card_by_num(int n) const {
		std::cout << "Rank of your card is:" << coloda[n].rank << std::endl;
	}

	void Cards::new_group_by_suit(int s, Cards*& mas, int& num1) const {
		Cards coloda_new;
		coloda_new.num = 0;
		int k = 0;
		for (int i = 0; i < num; i++) {
			if (coloda[i].suit == s) {
				coloda_new.coloda[k] = coloda[i];
				coloda_new.num++;
				k++;
			}
		}
		std::cout << "Our cards: " << std::endl;
		for (int i = 0; i < coloda_new.num; i++) {
			std::cout << "(" << i << ")" << std::endl;
			std::cout << "Our suit: " << coloda_new.coloda[i].suit << std::endl;
			std::cout << "Our rank: " << coloda_new.coloda[i].rank << std::endl;
			std::cout << std::endl;
		}
		if (coloda_new.num != 0) {
			mas[num1] = coloda_new;
			num1++;
		}
	}

	void Cards::quicksort_suit(Card*& mas, int first, int last)
	{
		int mid, count;
		int f = first, l = last;
		mid = mas[(f + l) / 2].suit;
		do
		{
			while (mas[f].suit < mid) f++;
			while (mas[l].suit > mid) l--;
			if (f <= l)
			{
				count = mas[f].suit;
				mas[f].suit = mas[l].suit;
				mas[l].suit = count;
				f++;
				l--;
			}
		} while (f < l);
		if (first < l) quicksort_suit(mas, first, l);
		if (f < last) quicksort_suit(mas, f, last);
	}

	void Cards::quicksort_rank(Card*& mas, int first, int last)
	{
		int mid, count;
		int f = first, l = last;
		mid = mas[(f + l) / 2].rank;
		do
		{
			while (mas[f].rank > mid) f++;
			while (mas[l].rank < mid) l--;
			if (f <= l)
			{
				count = mas[f].rank;
				mas[f].rank = mas[l].rank;
				mas[l].rank = count;
				f++;
				l--;
			}
		} while (f < l);
		if (first < l) quicksort_rank(mas, first, l);
		if (f < last) quicksort_rank(mas, f, last);
	}

	void Cards::sort_by_suit_and_rank() {
		quicksort_suit(coloda, 0, num - 1);
		int k = 0;
		int m = 0;
		for (int i = 0; i < SZ; i++) {
			k++;
			if (i + 1 < SZ && coloda[i].suit != coloda[i + 1].suit || i + 1 == SZ) {
				quicksort_rank(coloda, m, k);
				m = k;
			}
		}
	}

	std::ostream& Cards::print_rank(std::ostream& s, int r) const {
		for (int i = 0; i < num; i++) {
			if (coloda[i].rank == r) {
				s << coloda[i].suit;
			}
		}
		return s;
	}
	std::ostream& Cards::print_suit(std::ostream& s, int st) const {
		for (int i = 0; i < num; i++) {
			if (coloda[i].suit == st) {
				s << coloda[i].rank;
			}
		}
		return s;
	}

	std::ostream& Cards::print(std::ostream& s) const {
		for (int i = 0; i < num; i++) {
			s << i << std::endl;
			const char* str_suit = NULL;
			const char* str_rank = NULL;
			if (coloda[i].suit == 1) {
				str_suit = "Hearts";
			}
			else if (coloda[i].suit == 2) {
				str_suit = "Diamonds";
			}
			else if (coloda[i].suit == 3) {
				str_suit = "Clubs";
			}
			else if (coloda[i].suit == 4) {
				str_suit = "Spades";
			}
			if (coloda[i].rank == 11) {
				str_rank = "Jack";
			}
			else if (coloda[i].rank == 12) {
				str_rank = "Queen";
			}
			else if (coloda[i].rank == 13) {
				str_rank = "King";
			}
			else if (coloda[i].rank == 14) {
				str_rank = "Ace";
			}
			s << "Our suit: " << str_suit << std::endl;
			if (str_rank == NULL) {
				s << "Our rank: " << coloda[i].rank << std::endl;
			}
			else
				s << "Our rank: " << str_rank << std::endl;
			s << std::endl;
		}
		return s;
	}
}

