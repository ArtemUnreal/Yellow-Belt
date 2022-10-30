#include "database.h"

#include <algorithm>
#include <stdexcept>
#include <tuple>

using namespace std;

void Database::Add(const Date& date, const string& event)
{
	data_[date].Add(event);
}

void Database::Print(ostream& os) const
{
	for (const auto& a : data_)
	{
		for (const auto& event : a.second.GetAll())
		{
			os << a.first << ' ' << event << endl;
		}
	}
}

Entry Database::Last(const Date& date) const
{
	auto it = data_.upper_bound(date);
	if (it == data_.begin())
	{
		throw invalid_argument("Enry database::Last in databse.cpp");
	}
	--it;

	return { it->first, it->second.GetAll().back() };
}

ostream& operator << (ostream& os, const Entry& en)
{
	return os << en.date << " " << en.event;
}

bool operator == (const Entry& lhs, const Entry& rhs)
{
	return tie(lhs.date, lhs.event) == tie(rhs.date, rhs.event);
}