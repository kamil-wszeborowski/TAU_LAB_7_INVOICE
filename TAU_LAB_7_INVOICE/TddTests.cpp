#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Invoice.hpp"
#include "Db.hpp"
#include <iostream>

TEST_CASE("Check that getAll() method  is implemented") {
	//Given
	Db db = Db();
	
	//Then
	REQUIRE_NOTHROW(db.getAll());
}

TEST_CASE("Check that db without invoices in db method getAll() return empty vector") {
	//Given
	Db db = Db();

	//When
	std::vector<Invoice*> outcome = db.getAll();

	//Then
	REQUIRE(outcome.size() == 0);
}

TEST_CASE("Method getAll() should return correct number of elements in db") {
	//Given
	Db db = Db();
	Invoice *invoice1 = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice *invoice2 = new Invoice(200, 23, "Zaliczka do zlecenia.");
	
	//When
	db.create(invoice1);
	db.create(invoice2);
	std::vector<Invoice*> outcome = db.getAll();
	
	//Then
	REQUIRE(outcome.size() == 2);
}

TEST_CASE("Invoices object set test") {
	//Given
	Invoice *invoice = new Invoice(100, 23, "Faktura sprzedaży części.");
	/*
	int vatMark = invoice->vatMark;
	double brutto = invoice->brutto;
	double vat = invoice->vat;

	std::cout << vatMark << "\n";
	std::cout << brutto << "\n";
	std::cout << vat << "\n";
	*/
	//Then
	REQUIRE(invoice->description == "Faktura sprzedaży części.");
	REQUIRE(invoice->netto == 100);
	REQUIRE(invoice->vatMark == 23);
	REQUIRE(invoice->brutto == 123);
	REQUIRE(invoice->vat == 23);

}

TEST_CASE("Invoices creation() method test") {
	//Given
	Db db = Db();
	Invoice *invoice1 = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice *invoice2 = new Invoice(200, 23, "Zaliczka do zlecenia.");

	//When
	db.create(invoice1);
	db.create(invoice2);
	
	//Then
	REQUIRE(db.database[0]->id == 0);
	REQUIRE(db.database[0]->invoiceNumber == "FVT/2020/0");
	REQUIRE(db.database[0]->description == "Faktura sprzedaży części.");
	REQUIRE(db.database[0]->netto == 100);
	REQUIRE(db.database[0]->vatMark == 23);
	REQUIRE(db.database[0]->brutto == 123);
	REQUIRE(db.database[0]->vat == 23);

	REQUIRE(db.database[1]->id == 1);
	REQUIRE(db.database[1]->invoiceNumber == "FVT/2020/1");
	REQUIRE(db.database[1]->description == "Zaliczka do zlecenia.");
	REQUIRE(db.database[1]->netto == 200);
	REQUIRE(db.database[1]->vatMark == 23);
	REQUIRE(db.database[1]->brutto == 246);
	REQUIRE(db.database[1]->vat == 46);
}

TEST_CASE("Check that get() method is implemented") {
	//Given
	Db db = Db();
	Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzedaży części.");

	//When
	db.create(invoice0);

	//Then
	REQUIRE_NOTHROW(db.get(0));
	
}

TEST_CASE("Check that get() method can find and return correct invoice") {
	//Given
	Db db = Db();
	Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice *invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
	Invoice *invoice2 = new Invoice(300, 0, "Wymiana wycieraczek.");

	//When
	db.create(invoice0);
	db.create(invoice1);
	db.create(invoice2);

	//Then
	REQUIRE(db.get(2)->id == 2);
	REQUIRE(db.get(2)->invoiceNumber == "FVT/2020/2");
	REQUIRE(db.get(2)->description == "Wymiana wycieraczek.");
	REQUIRE(db.get(2)->netto == 300);
	REQUIRE(db.get(2)->vatMark == 0);
	REQUIRE(db.get(2)->brutto == 300);
	REQUIRE(db.get(2)->vat == 0);
}

TEST_CASE("Check that get() method return correct exception") {
	//Given
	Db db = Db();
	Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice *invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
	Invoice *invoice2 = new Invoice(300, 0, "Wymiana wycieraczek.");

	//When
	db.create(invoice0);
	db.create(invoice1);
	db.create(invoice2);

	//Then
	CHECK_THROWS(db.get(3));
}

TEST_CASE("Check that update() method can update invoice in db") {
	//Given
	Db db = Db();
	Invoice* invoiceToUpdate = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice* invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
	Invoice* newInvoice = new Invoice(300, 0, "Wymiana wycieraczek.");

	//When
	db.create(invoiceToUpdate);
	db.create(invoice1);
	db.create(newInvoice);

	db.update(newInvoice, 0);

	//Then
	REQUIRE(db.get(0)->id == 2);
	REQUIRE(db.get(0)->invoiceNumber == "FVT/2020/2");
	REQUIRE(db.get(0)->description == "Wymiana wycieraczek.");
	REQUIRE(db.get(0)->netto == 300);
	REQUIRE(db.get(0)->vatMark == 0);
	REQUIRE(db.get(0)->brutto == 300);
	REQUIRE(db.get(0)->vat == 0);
	
}


TEST_CASE("Check that remove() method delete invoice") {
	//Given
	Db db = Db();
	Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice *invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
	Invoice *invoice2 = new Invoice(300, 0, "Wymiana wycieraczek.");

	//When
	db.create(invoice0);
	db.create(invoice1);
	db.create(invoice2);
	db.remove(1);

	//Then
	CHECK_THROWS(db.get(1));
}

TEST_CASE("Check that remove() method delete correct number of invoice") {
	//Given
	Db db = Db();
	Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzedaży części.");
	Invoice *invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
	Invoice *invoice2 = new Invoice(300, 0, "Wymiana wycieraczek.");	

	//When
	db.create(invoice0);
	db.create(invoice1);
	db.create(invoice2);
	db.remove(2);
	std::vector<Invoice*> outcome = db.getAll();

	//Then
	REQUIRE(outcome.size() == 2);
}