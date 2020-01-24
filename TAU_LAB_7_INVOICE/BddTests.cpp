
#include "catch.hpp"
#include "Db.hpp"
#include "Invoice.hpp"

SCENARIO("Check size of db after use remove() method for two invoice") {

	GIVEN("Database of six invoices") {
		Db db = Db();
		Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzeda¿y czêœci.");
		Invoice *invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
		Invoice *invoice2 = new Invoice(300, 0, "Wymiana wycieraczek.");
		Invoice *invoice3 = new Invoice(100, 23, "Faktura sprzeda¿y czêœci.");
		Invoice *invoice4 = new Invoice(200, 23, "Zaliczka do zlecenia.");
		Invoice *invoice5 = new Invoice(300, 0, "Wymiana wycieraczek.");
		db.create(invoice0);
		db.create(invoice1);
		db.create(invoice2);
		db.create(invoice3);
		db.create(invoice4);
		db.create(invoice5);

		WHEN("Two invoices was removed from the database") {
			db.remove(0);
			db.remove(3);
			std::vector<Invoice*> outcome = db.getAll();

			THEN("Database should contain only four invoices") {
				REQUIRE(outcome.size() == 4);
			}
		}
	}
}

SCENARIO("Check that remove() method will remove invoice") {

	GIVEN("Database of invoices") {
		Db db = Db();
		Invoice *invoice0 = new Invoice(100, 23, "Faktura sprzeda¿y czêœci.");
		Invoice *invoice1 = new Invoice(200, 23, "Zaliczka do zlecenia.");
		db.create(invoice0);
		db.create(invoice1);
		CHECK_NOTHROW(db.get(0));

		WHEN("Invoice is removed from the database") {
			db.remove(0);

			THEN("Database do not contain removed invoice") {
				CHECK_THROWS(db.get(0));
			}
		}
	}
}


