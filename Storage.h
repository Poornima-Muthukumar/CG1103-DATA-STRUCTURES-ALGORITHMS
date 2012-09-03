/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <fstream>
using namespace std;

template <typename T>
class Storage
{
protected:

    int _size;

public:
    Storage() { _size = 0; }
    virtual ~Storage() {};

    int getSize()  { return _size; }
    bool isEmpty() { return _size == 0; }

	//-----------------------------------------------------------------------------------/
	/********************************** BASIC METHODS ***********************************/
	//-----------------------------------------------------------------------------------/

	virtual int getStockAtIndex ( int index ) = 0;
	//Returns Stock Quantity at index
	//Aids: CheckSalesPossible which in turn,
	//helps Update sales function

	virtual int IndexOfBarcode( string barcode) = 0;
	//Returns index to where barcode is found
	// -1 is returned when barcode is not found

    virtual void toFile(string filename) = 0;
	//Copies data to filename
	//Beginning with N ( Total number of products )
	//Each product is separated by a blank line

    virtual bool addItem(T* newItem) = 0;
	//Creates a newNode and stores newItem inside.
	//newItem are added to the tail for CDLL
	//Returns true if successfully added

    virtual bool delItem(int index) = 0;
	//Takes in index where product is found.
	//Remove the node/element at that index

    virtual void resetItem(int index) = 0;
	//Takes in index where product is found
	//Reset sales counter to zero

	virtual void updateStock(int index, int numStock) = 0;
	//Takes in index where product is found
	//Update Stock by numStock

    virtual void updateSale(int index, int numSold) = 0;
	//Takes in index where product is found
	//Update Sale by numSold

	virtual int checkExpiry(int index, string curDate) = 0;
	//Returns 1 if product is not expired
	//Return 0 if product is expired
	//Returns -1 if product is not persishable
	//Same Date considered NOT expired yet.

	//-----------------------------------------------------------------------------------/
    /*********************************** STATISTICS *************************************/
	//-----------------------------------------------------------------------------------/

    virtual string topXitem(int x) = 0;
    virtual string topCategoryItem(string category) = 0;
    virtual string topManufacturer() = 0;

	//-----------------------------------------------------------------------------------/
    /************************************ SEARCH ****************************************/
	//-----------------------------------------------------------------------------------/

    virtual string searchByName(string name) = 0;
    virtual string searchByBarcode(string barcode) = 0;
    virtual string searchByCategory(string category) = 0;
    virtual string searchByManufacturer(string manufacturer) = 0;

	//------------------------------------------------------------------------------------/
	/************************** LAB 4 ADDITIONS: RESET STOCK *****************************/
	//------------------------------------------------------------------------------------/

	virtual void resetStock(int index) = 0;
	//Takes in index where product is found
	//Reset Stock Counter to zero

	//------------------------------------------------------------------------------------/
	/********************************** LAB 5 ADDITIONS **********************************/
	//------------------------------------------------------------------------------------/

	virtual void SortByWorth() = 0;
	virtual void toSortedFile(string filename) = 0;

	//------------------------------------------------------------------------------------/
};

#endif