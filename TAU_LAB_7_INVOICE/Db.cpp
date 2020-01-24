#include "Db.hpp"
#include <string> 

Invoice* Db::get(int id) {
	return database.at(id);
}

std::vector<Invoice*> Db::getAll() {
	outcome.clear();

	for (auto i : database)	{
		outcome.push_back(i.second);
	}

	return outcome;
}

void Db::create(Invoice *invoice) {
	invoice->id = invoice_count;
	invoice->invoiceNumber = "FVT/2020/" + std::to_string(invoice->id);
	database.insert(std::make_pair(invoice_count, invoice));
	invoice_count++;
}

void Db::update(Invoice *invoice, int id) {
	database[id] = invoice;
}

void Db::remove(int id) {
	database.erase(id);
}


