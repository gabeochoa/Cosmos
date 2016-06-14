#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>

const int numdealers = 10;
const std::string valid_dealers[] = {"DB","JPM","UBS","RBC","BARX","MS","CITI","BOFA","RBS","HSBC"};
const int numcommodities = 5;
const std::string valid_commodity[] = {"GOLD", "SILV", "PORK", "OIL", "RICE"};

//Not used
const int numsides = 2;
const std::string valid_sides[] = {"BUY", "SELL"};

#endif // GRAMMAR_H