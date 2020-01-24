#pragma once
#include <string>

class Invoice
{
public:
 int id;
 std::string invoiceNumber;
 double netto;
 double brutto;
 double vat;
 int vatMark;
 std::string description;

 //Invoice(std::string invoiceNumber, double netto, int vatMark, std::string description);
 Invoice(double netto, int vatMark, std::string description);
 ~Invoice();
};

