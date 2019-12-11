#include <iostream>
#include "..\StaticLibCards\Cards.h"

using namespace Prog3;
int main()
{
	int num = 0;
	Cards* mas = new Cards[1000];
	int rv;
	/*std::cout << "Please select the constructor" << std::endl;
	if (!select_constructor(mas, num)) {
		return 0;
	}*/
	Cards cld;
	mas[num] = cld;
	num++;
	int rc;
	Cards* coloda_kart = nullptr;
	int temp = -1;
	while (rc = dialog(msgsM, NMsgsM)) {
		if (rc == 1) {
			std::cout << "Input index number of coloda from 0 to " << num - 1 << std::endl;
			int i;
			while (getNum(i) < 0 || i < 0 || i > num - 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			coloda_kart = &mas[i];
			temp = i;
		}
		if (rc == 2) {
			if (num >= 1000) {
				std::cout << "Overflow" << std::endl;
			}
			bool ind = true;
			while (ind) {
				/*std::cout << "Select the constructor" << std::endl;
				if (!select_constructor(mas, num)) {
					return 0;
				}*/
				static Cards cld1;
				mas[num] = cld1;
				num++;
				std::cout << "Do you want to continue? 1-yes, 0-no" << std::endl;
				int l;
				while (getNum(l) < 0 || l != 0 && l != 1)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (!l)
					ind = false;
			}
			continue;
		}
		if (rc == 3) {
			bool ind = true;
			while (ind) {
				if (num < 2) {
					std::cout << "You have only 1 coloda. Repeat please" << std::endl;
					ind = false;
					continue;
				}
				else {
					std::cout << "Choose wherefrom to copy :from 0 to " << num - 1 << std::endl;
					int i;
					while (getNum(i) < 0 || i < 0 || i > num)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					std::cout << "Choose where to copy :from 0 to " << num - 1 << std::endl;
					int j;
					while (getNum(j) < 0 || j < 0 || j > num)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					mas[j].copy(mas[i]);
				}
				std::cout << "Do you want to continue? 1-yes, 0-no" << std::endl;
				int l;
				while (getNum(l) < 0 || l != 0 && l != 1)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
					delete& mas[num];
				}
				if (!l)
					ind = false;
			}
			continue;
		}
		if (rc == 4) {
			for (int i = 0; i < num; i++) {
				std::cout << "(" << i << ") ";
				std::cout << std::endl;
				mas[i].print(std::cout);
				std::cout << std::endl;
			}
			continue;
		}
		while (rc = dialog(msgs, NMsgs)) {
			if (rc == 5) {
				int t = D_New_group_by_suit(*coloda_kart, mas, num);
			}
			else if (!fptr[rc](*coloda_kart))
				break;
		}
	}
	return 0;
}
