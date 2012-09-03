/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _PERISHABLE_H_
#define _PERISHABLE_H_

#include "Product.h"
using namespace std;

class Perishable : public Product
{

private:

	string _expiryDate;
	double _discount;

public:

	Perishable() {}
	Perishable(string name, string category, string barcode, double price, string manufacturer, int numStock, int numSold, string expiryDate, double discount);
	~Perishable() {}


	string getExpiryDate()		{ return _expiryDate; }
	double getDiscount()		{ return _discount;	  }
	virtual double getPrice()	{ return _price * (100-_discount)/100.0 ;		 }
	virtual double Revenue()	{ return _price * _Sold * (100-_discount)/100.0; }

	virtual string toString();

	/******************************* CHECK EXPIRY FUNCTION ****************************/
	virtual int Checkexpiry(string currentDate);
	/**********************************************************************************/
}; 

#endif 