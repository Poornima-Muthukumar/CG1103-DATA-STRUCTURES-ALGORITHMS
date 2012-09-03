/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _UI_H_
#define _UI_H_

#include <string>
#include <iostream>
#include "Timer.h"
#include "Controller.h"

class UI
{
private:

	enum
	{
		eExit = 0,			//[0] Bye Bye
		eAddProduct,		//[1] Add New Product
		eDelProduct,		//[2] Delete Product			
		eResetSales,		//[3] Reset Product Sales		
		eSaleRestockTrans,	//[4] Sale/Restock Transaction
		eGenerateStats,		//[5] Generate Statistics		
		eSearchProduct,		//[6] Search Products			
		eCheckExpiry,		//[7] Check Expiry Date		
		eBatchProcessing,	//[8] Batch Processing       
		eSortByWorth		//[9] Sort By Worth			
	};

	Controller control;	//Controller object

	string Name;		//Name
	string Cat;			//Category
	string Barcode;		//Barcode
	double price;		//Price
	string Manufac;		//Manufacturer
	int Stock;			//Num Stock
	int	Sold;			//Num Sold
	string expiry;		//Expiry date
	int discount;		//Discount %

	string currentDate;	//Today's date( user input )

	string rubbish;		//To throw \n

public:

	UI();

	void Start();				//Main will call Start to load user interface.

	//-------------------------------------------------------------------------/
	/***************************** DISPLAY PURPOSES ***************************/
	//-------------------------------------------------------------------------/

	int UI_OpeningScreen();		//Hello World!

	void UI_AddPdt();			//Choice 1
	void UI_DelPdt();			//Choice 2
	void UI_ResetPdt();			//Choice 3

	int UI_UpdateTrans();		//Choice 4
	void UI_UpdateSales();		//Choice 4(a)
	void UI_UpdateRestock();	//Choice 4(b)

	int UI_GenerateStats();		//Choice 5
	void UI_TopXselling();		//Choice 5(a)
	void UI_BSPcategory();		//Choice 5(b)
	void UI_BSmanufacturer();	//Choice 5(c)

	//-------------------------------------------------------------------------/
};

#endif