/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#include "Perishable.h"


Perishable::Perishable(string name, string category, string barcode, double price, string manufacturer, int numStock, int numSold, string expiryDate, double discount):Product(name, category, barcode, price, manufacturer, numStock, numSold)
{
    _expiryDate = expiryDate;
    _discount = discount;
}

string Perishable::toString() 
{
    ostringstream oss;

    oss << Product::toString();
	oss << _expiryDate	<< "\n";
    oss << _discount	<< "\n";

    return oss.str();
}

//------------------------------------------------------------------------------------------------------/
/********************************* FUNCTION TO DEAL WITH EXPIRY ****************************************/
//------------------------------------------------------------------------------------------------------/

//Returns 0 if product's date is larger than current date
//That is: the product has expired if the function returns 0.
//Returns 1 if product has not expired.
int Perishable::Checkexpiry(string currentDate)
{
	string dd1,mm1,yy1,mm2,dd2,yy2;

	//Sets Product Date
	string PdtDate = getExpiryDate();

	dd1=currentDate.substr(0,2);
	mm1=currentDate.substr(2,2);
	yy1=currentDate.substr(4,4);

	dd2=PdtDate.substr(0,2);
	mm2=PdtDate.substr(2,2);
	yy2=PdtDate.substr(4,4);
	
	//If year of Product is greater
	if(yy2>yy1)
	{
		return 1;
	}
	
	//If year is equal
	else if(yy2==yy1)
	{
		//If Product's Month is greater
		//or ( Month is equal and Product's Date is greater )
		if((mm2>mm1)||((mm2==mm1)&&(dd2>=dd1)))
		{
			return 1;
		}			
	}
	
	//Else, Current Date has to be greater than Product Date (Expired)
	return 0;
}

//------------------------------------------------------------------------------------------------------/