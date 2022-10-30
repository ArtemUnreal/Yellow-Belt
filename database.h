#pragma once

#include "date.h"
#include "event_set.h"

#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct Entry 
{
	Date date;
	string event;
};

ostream& operator << (ostream& os, const Entry& en);
bool operator == (const Entry& lhs, const Entry& rhs);

class Database
{
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	Entry Last(const Date& date) const;

	template <class Predicate>
	int RemoveIf(Predicate predicate)
	{
		int result = 0;
		for (auto& a : data_)
		{
			const Date& date = a.first;
			result += a.second.RemoveIf([=](const string& event)
				{
					return predicate(date, event);
				});
		}

		for (auto it = data_.begin(); it != data_.end(); )
		{
			if (it->second.GetAll().empty())
			{
				data_.erase(it++);
			}
			else
			{
				++it;
			}
		}

		return result;
	}

	template <class Predicate>
	vector <Entry> FindIf(Predicate predicate) const 
	{
		vector <Entry> result;
		for (auto& a : data_)
		{
			for (const auto& event : a.second.GetAll())
			{
				if (predicate(a.first, event))
				{
					result.push_back(Entry{ a.first, event });
				}
			}
		}

		return result;
	}

private:
	map <Date, EventSet> data_;
};

void TestDatabaseAddAndPrint();
void TestDatabaseFind();
void TestDatabaseRemove();
void TestDatabaseLast();