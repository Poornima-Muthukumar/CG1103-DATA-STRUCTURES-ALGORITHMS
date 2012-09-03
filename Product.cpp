/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#include "Product.h"

Product::Product()
{
}

Product::Product(string name, string category, string barcode, double price, string manufacturer, int numStock, int numSold)
{
    _name         = name;
    _category     = category;
    _barcode      = barcode;
    _price        = price;
    _manufac	  = manufacturer;
    _Stock		  = numStock;
    _Sold		  = numSold;
}

string Product::toString()
{
    ostringstream oss;

    oss << _name			<< "\n";
	oss	<< _category		<< "\n";
	oss	<< _barcode			<< "\n";
    oss << setprecision(2)	<< fixed << _price << "\n";
    oss << _manufac			<< "\n";
	oss << _Stock			<< "\n";
    oss << _Sold			<< "\n";

    return oss.str();
}