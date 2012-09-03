/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <fstream>
#include <string>

#include "Product.h"
#include "Perishable.h"
#include "Storage.h"
#include "ArrayList.h"
#include "LL.h"
#include "CDLL.h"

#include "Timer.h"

#include "BatchJob.h"
#include "myStack.h"
#include "myQueue.h"

using namespace std;

class Controller
{
private:

	Storage<Product> *_List ;

	myStack< myQueue<BatchJob>* > *_AllJobs;

public:

	Controller();
	//REMOVE OR SHOW COMMENTS IN CPP FILE TO SWITCH BETWEEN STORAGE TYPE. ^^

    ~Controller();

	bool ReadFile();
	//Function: Populates Data into chosen storage

	void BackupFile(string filename);
	//Function: Writes data into chosen filename
	//Currently called when user exits program (Known as backup.txt)
	//This function could be called again if user wants to save halfway


    /**************************** BASIC METHODS *************************/

	bool CheckSalePossible ( int index , int numSold );
	//Returns true if Stock at index is more than number to be sold
	//That is, sale is possible.
	//Aids Update sale function

	int CheckBarcodeExist(string barcode);
	//Takes in barcode, return -1 if match is not found
	//Returns index if match is found

    void Add(string Name, string Cat, string Barcode, double price, string Manufac, int Stock, int Sold, string expiry, double discount);
	//Takes in Data, creates either perishable or normal product,
	//Stores created product inside _List ( Storage<Product> )

    void Del(int Index);
	//Pre-check of barcode existing in database already done.
	//Takes in index where barcode is found.
	//DESTROY THE PRODUCT FOR GOOD!

    void Reset(int Index);
	//Pre-check of barcode existing in database already done.
	//Takes in index where barcode is found.
	//Reset the sales counter of that particular product

    void saleProduct(int Index ,  int numSold);
	//Pre-check of barcode existing in database already done.
	//Takes in index where barcode is found.
	//Reads in quantity sold
	//Update quantity sold of that particular product accordingly
	//Reduce Num in Stock by equivalent amount

    void restockProduct(int Index , int numStock);
	//Pre-check of barcode existing in database already done.
	//Takes in index where barcode is found.
	//Reads in quantity to restock
	//Update quantity restock of that particular product accordingly

	int CheckExpiry(int Index , string currentDate);

    /****************************** STATISTICS ******************************/

    string topXproduct(int X);
	//Takes in X, which is the number X in "top X product"
	//for eg. X = 5 means top 5 products
	//Function would return a string of products which qualify for top products

    string BestInCategory(string category);
	//Takes in category
	//Function would return a string of products which qualify for top products

    string BestManufac();
	//Function would return the name of the best manufacturer

    /****************************** SEARCHING ********************************/

    string SearchByName(string name);
	//Takes in name
	//Function would return a string of products with the same name

    string SearchByBarcode(string Barcode);
	//Takes in barcode
	//Function would return details of that particular product
	//Barcode is unique, hence only one product will be displayed

    string SearchByCategory(string category);
	//Takes in category
	//Function would return a string of products belonging to the same category

    string SearchByManufac(string manufacturer);
	//Takes in manufacturer
	//Function would return a string of products belonging to the same manufacturer


	/***************************************** BATCH PROCESSING *************************************/

	void ResetStock(int Index);

	void ReadBatchJob(string BatchFileName);
	void PerformBatchJob();

	/*************************************** LAB 5 ADDITIONS ****************************************/

	void SortByWorth();
	void toSortedFile(string filename);

	/************************************************************************************************/
};

#endif