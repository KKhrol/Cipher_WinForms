#include "Agency.h"
#include <clocale>
#include  <algorithm>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <sstream>


using std::endl;
using std::cout;
using std::cin;

void Concert::get_info(std::string info)
{
	auto pos = 0;
	std::string subs[4];

	for (auto i = 0; i < 3; i++)
	{
		pos = info.find(';');
		subs[i] = info.substr(0, pos);
		info.erase(0, pos + 1);
	}

	subs[3] = info;

	Name = subs[0];
	amount = std::stol(subs[1]);
	tickets_left = std::stol(subs[2]);
	std::stringstream ss(subs[3]);
	ss >> std::get_time(&time, "%Y-%m-%d %H:%M");
}



void List_Of_Events::add_concert(std::string info)
{

	Concert buf{};

	buf.get_info(info);

	events.push_back(buf);

}

int List_Of_Events::Get_Concert_Amount() const
{
	return events.size();
}

Concert& List_Of_Events::operator[] (const int index)
{
	return events[index];
}

std::ostream & operator <<(std::ostream &out, const List_Of_Events &c)
{
	for (const auto& d : c.events)
	{
		out << d.Name << ";" << d.amount << ";" << d.tickets_left << ";" << std::put_time(&d.time, "%Y-%m-%d %H:%M") << std::endl;
	}

	return out;
}

std::istream & operator >>(std::istream &in, List_Of_Events &c)
{
	std::string str;

	std::getline(in, str);

	auto pos = 0;
	std::string parts[4];

	for (auto i = 0; i < 3; i++)
	{
		pos = str.find(';');
		parts[i] = str.substr(0, pos);
		str.erase(0, pos + 1);
	}
	parts[3] = str;

	Concert d;
	d.Name = parts[0].c_str();
	d.amount = std::stol(parts[1]);
	d.tickets_left = std::stol(parts[2]);


	std::stringstream ss(parts[3]);
	ss >> std::get_time(&(d.time), "%Y-%m-%d %H:%M");

	c.events.push_back(d);

	return in;
}

void List_Of_Events::Sort_via_Name()
{
	//std::sort(info, info + amount, [](const Data x, const Data y) -> bool
	std::sort(events.begin(), events.end(), [](const Concert x, const Concert y) -> bool
	{
		return x.Name < y.Name;
	});
}

void List_Of_Events::Sort_via_Date()
{
	//std::sort(info, info + amount, [](Data x, Data y) -> bool
	std::sort(events.begin(), events.end(), [](Concert x, Concert y) -> bool
	{
		return mktime(&(x.time)) < mktime(&(y.time));
	});
}

bool List_Of_Events::Book_Ticket(unsigned int count, unsigned int number)
{

	if (events[count].tickets_left == 0)
	{
		cout << endl << "No tickets left!" << endl;
		return false;
	}
	events[count].tickets_left--;
	return true;
}


std::vector<Concert>::iterator List_Of_Events::begin()
{
	return events.begin();
}

std::vector<Concert>::iterator List_Of_Events::end()
{
	return events.end();
}



std::vector<Concert>List_Of_Events::find_first_name(std::string const& c_name)
{
	std::vector<Concert>::iterator temp = std::find_if(events.begin(), events.end(), [&c_name](Concert const& c)
	{
		int len1 = c.Name.length(), len2 = c_name.length();
		int min_len = len1 <= len2 ? len1 : len2;

		return c.Name.substr(0, min_len) == c_name.substr(0, min_len);

	});

	std::vector<Concert> found_concerts;

	while (temp != events.end())
	{
		found_concerts.push_back(*temp);

		temp = std::find_if(++temp, events.end(), [&c_name](Concert const& c)
		{
			int len1 = c.Name.length(), len2 = c_name.length();
			int min_len = len1 <= len2 ? len1 : len2;

			return c.Name.substr(0, min_len) == c_name.substr(0, min_len);
		});
	}
	return found_concerts;
}



std::vector<Concert> List_Of_Events::find_first_date_between(tm const& date1, tm const& date2)
{
	tm d1 = date1, d2 = date2;

	std::vector<Concert>::iterator temp = std::find_if(events.begin(), events.end(), [&d1, &d2](Concert & c)
	{
		return (mktime(&d1) <= mktime(&c.time)) && (mktime(&c.time) <= mktime(&d2));
	});

	std::vector<Concert> found_concerts;

	while (temp != events.end())
	{
		found_concerts.push_back(*temp);

		temp = std::find_if(++temp, events.end(), [&d1, &d2](Concert & c)
		{
			return (mktime(&d1) <= mktime(&c.time)) && (mktime(&c.time) <= mktime(&d2));
		});
	}
	return found_concerts;
}