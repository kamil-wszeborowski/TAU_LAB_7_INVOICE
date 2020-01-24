#include "Invoice.hpp"
#include "math.h"

Invoice::Invoice(double netto, int vatMark, std::string description) {
	this->netto = netto;
	this->vatMark = vatMark;
	switch (vatMark) {
	case 23:
		this->brutto = roundf((netto * 1.23)* 100.0) / 100.0;
		this->vat = roundf((netto * 0.23)* 100.0) / 100.0;
		break;
	case 8:
		this->brutto = roundf((netto * 1.08)* 100.0) / 100.0;
		this->vat = roundf((netto * 0.8)* 100.0) / 100.0;
		break;
	case 5:
		this->brutto = roundf((netto * 1.05)* 100.0) / 100.0;
		this->vat = roundf((netto * 0.5)* 100.0) / 100.0;
		break;
	case 0:
		this->brutto = netto;
		this->vat = 0;
		break;
	}
	this->description = description;
}