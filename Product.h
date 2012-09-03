/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Product
{

protected:
   
	string _name;			//Name
	string _category;		//Category
	string _barcode;		//Barcode Number
	double _price;			//Price
	string _manufac;		//Manufacturer
	int _Stock;				//Quantity Stock
	int _Sold;				//Quantity Sold

	/************ G LAB 5 ADDITIONS ************/
	int _Index;
	int _PriceRank;
	int _StockRank;
	/*******************************************/

public:
	
	Product();
	Product(string name, string category, string barcode, double price, string manufacturer, int numStock, int numSold);
	~Product() {}

	virtual string toString();

	/*~~~~~~~~~~~~~~~~~~~~~~~ Accessors ~~~~~~~~~~~~~~~~~~~~~~~*/

	string getName()			{ return _name;			}
	string getCat()				{ return _category;		}
	string getBarcode()			{ return _barcode;		}
	virtual double getPrice()	{ return _price;		}
	string getManufac()			{ return _manufac;		}
	int	getStock()				{ return _Stock;		}
	int getSold()				{ return _Sold;			}
	virtual double Revenue()	{ return _price * _Sold;}

	//-------------------- LAB 5 ADDITIONS---------------------//
	int getIndex()			{ return _Index;					}
	int getPriceRank()		{ return _PriceRank;				}
	int getStockRank()		{ return _StockRank;				}
	int getWorthRank()		{ return _PriceRank + _StockRank;	}
	//---------------------------------------------------------//

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	/*~~~~~~~~~~~~~~~~~~ Mutators ~~~~~~~~~~~~~~~~~*/

    void resetSold()	{ _Sold  = 0;			    }
    void restock(int i)	{ _Stock = getStock() + i ; }
	void sale(int i)	{ _Sold  = getSold() + i  ; }

	//----For Lab 4: Aids ResetStock for DISPOSE---//
	void resetStock()	{ _Stock = 0;				}
	//---------------------------------------------//

	//-------------- LAB 5 ADDITIONS --------------//
	void setIndex(int i)		{ _Index = i ;		}
	void setPriceRank(int i)	{ _PriceRank = i;	}
	void setStockRank(int i)	{ _StockRank = i;	}
	//---------------------------------------------//

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/************************************ CHECK EXPIRY FUNCTION **************************************/
	/******************************* TO BE IMPLEMENTED BY PERISHABLE *********************************/
	virtual int Checkexpiry(string currentDate)
	{
		return -1;	//Serves as an indicator that this product is not perishable when checking expiry.
	}
	/*************************************************************************************************/
};

#endif