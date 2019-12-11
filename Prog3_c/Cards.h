#pragma once
#ifndef _PROG3H_H_
#define _PROG3H_H_
#include "pch.h"
#include <iostream>
//сдано
/*перегрузить ввод-вывод
 перегрузить прибавление карты к колоде
перегрузить colode[!].
вернуть копию колоды
для поиска уже существующих карт в колоде(если существует, изменить)....*/

namespace Prog3 {

	//enum suit { Heart, Bubi, Cross, Peaks };
	//enum rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

	struct Card {
		int rank; // ранг карты от 2 до 14
		int suit; // от 1 до 4
	};

	class Cards {
	private:
		static const int SZ = 52;
		Card* coloda;
		int num; //количество карт в колоде
	public:
		Cards(); 
		//~Cards();
		Cards(int n);
		Cards(Card c);
		bool add_card_from_vvod(int, int);
		void add_card_by_random();
		void suit_card_by_num(int) const;
		void rang_card_by_num(int) const;
		void new_group_by_suit(int, Cards*&, int&) const;
		void sort_by_suit_and_rank();
		void copy(Cards);
		std::ostream& print_suit(std::ostream&, int r) const;
		std::ostream& print_rank(std::ostream&, int st) const;
		std::ostream& print(std::ostream&) const;
		int getMaxSize() const { return SZ; }
		int getcnum() const { return num; }
		int find_card_from_coloda(int s, int r);
		void quicksort_rank(Card*& mas, int first, int last);
		void quicksort_suit(Card*& mas, int first, int last);
	};

	int D_Add_Card_R(Cards&),
		D_Add_Card(Cards&),
		D_Suit_card_by_num(Cards&),
		D_Rang_card_by_num(Cards&),
		D_New_group_by_suit(Cards&, Cards*& mas, int& num),
		D_Sort(Cards&),
		D_Print(Cards&);
	extern int(*fptr[])(Cards&);
	int dialog(const char* msgs[], int);
	int select_constructor(Cards*& mas, int& num);
	int getNum(int& a);
	extern const char* msgs[];
	extern const char* cmsgs[];
	extern const char* msgsM[];
	extern const int NMsgs;
	extern const int NcMsgs;
	extern const int NMsgsM;
}
#endif
