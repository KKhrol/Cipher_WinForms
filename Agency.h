#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <Windows.h>
#include <iomanip>
#include <algorithm>
#include <ctime>


#ifndef _CONCERT_
#define _CONCERT_


#define K 100
#define L 40

struct Concert {
	std::string Name;
	int tickets_left{};
	int amount{};
	tm time;

	void get_info(std::string info);
};

class List_Of_Events
{
public:
	using vector_t = std::vector<Concert>;
	vector_t events;

	void add_concert(std::string info);

	using iterator = vector_t::iterator;

	List_Of_Events() = default;

	List_Of_Events(List_Of_Events const&) = delete;

	List_Of_Events(List_Of_Events&&) = delete;
	bool Book_Ticket(unsigned int ind, unsigned int num);
	int Get_Concert_Amount() const;

	void Sort_via_Name();
	void Sort_via_Date();

	std::vector<Concert> find_first_name(std::string const&);
	std::vector<Concert> find_first_date_between(tm const& date1, tm const& date2);

	Concert& operator[] (const int index);

	std::vector<Concert>::iterator begin();
	std::vector<Concert>::iterator end();

	friend std::ostream& operator <<(std::ostream&, const List_Of_Events&c);
	friend std::istream& operator >>(std::istream&, List_Of_Events&);

};

#endif


