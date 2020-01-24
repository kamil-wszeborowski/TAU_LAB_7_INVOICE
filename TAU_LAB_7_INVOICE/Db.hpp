#pragma once
#include "Invoice.hpp"
#include <map>
#include <vector>

class Db
{
public:
	Invoice* get(int id);
	std::vector<Invoice*> getAll();
	void create(Invoice *invoice);
	void update(Invoice* invoice, int id);
	void remove(int id); 

	std::map<int, Invoice*> database;
private:
	int invoice_count = 0;
	std::vector<Invoice*> outcome;
};

