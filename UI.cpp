/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#include "UI.h"

UI::UI()
{
}

void UI::Start()
{
	//Text to ask user to input name of file.
	cout << "Enter textfile to load(Format: data-s.txt): " ;

	if( !control.ReadFile() )
	{
		cout << "File not loaded" <<endl;
		system("pause");
	}

	int choice = 0;
	int Index = 0;	
	
	do
	{
		/**********************************************************************************************/
		/************************************** OPENING SCREEN ****************************************/
		/**********************************************************************************************/


		choice = UI_OpeningScreen();	//Display Opening screen

		switch( choice )
		{
	
		/**********************************************************************************************/
		/**************************************** ADD PRODUCT *****************************************/
		/**********************************************************************************************/

		case eAddProduct:
			
			UI_AddPdt();	//Display Add product screen

			Index = control.CheckBarcodeExist(Barcode);

			if( Index != -1 )	//Checks if barcode already exist in database
			{
				cout << endl << "Barcode already exist!" << endl;
				system("pause");
			}

			else	//Ready to add
			{
				/***************************** TIME CHECK ********************************/
												Timer t;
				/*************************************************************************/

				control.Add(Name, Cat, Barcode, price, Manufac, Stock, Sold, expiry, discount);
				cout << endl << "Product added!" << endl;

				/***************************** TIME CHECK ********************************/
												t.print();
				/*************************************************************************/
			}

			break;

		/**********************************************************************************************/
		/************************************** DELETE PRODUCT ****************************************/
		/**********************************************************************************************/

		case eDelProduct:
			
			UI_DelPdt();	//Display Del Product screen

			Index = control.CheckBarcodeExist(Barcode);	//Returns index where barcode is found

			if( Index != -1 )	//If barcode exists, confirm with user if he wants to delete.
			{
				char AreYouSure = ' ';

				cout << endl << "Are You Sure you want to delete product? [Y]/[N]" << endl;
				cin >> AreYouSure;

				if( AreYouSure == 'Y' || AreYouSure == 'y' )
				{

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					control.Del(Index);
					cout << endl << "Product deleted!" << endl;

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
				}

				else
				{
					cout << endl << "Product not deleted!" << endl;
					system("pause");
				}
			}

			else	//If index == -1 , Barcode does not exist in database
			{
				cout << "Barcode does not exist!" <<endl;
				system("pause");
			}

			break;

		/************************************************************************************************/
		/*********************************** RESET PRODUCT SALES COUNTER ********************************/
		/************************************************************************************************/

		case eResetSales:	
			
			UI_ResetPdt();	//Display Reset screen

			Index = control.CheckBarcodeExist(Barcode);	//Returns index where barcode is found

			if( Index != -1 )	//If barcode exists, confirm with user if he wants to delete.
			{
				char AreYouSure = ' ';

				cout << endl << "Are You Sure you want to reset sales? [Y]/[N]" << endl;
				cin >> AreYouSure;

				if( AreYouSure == 'Y' || AreYouSure == 'y' )
				{

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					control.Reset(Index);
					cout << endl << "Sales have been reset!" << endl;

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
				}

				else
				{
					cout << endl << "Sales have NOT been reset" << endl;
					system("pause");
				}
			}

			else	//If index == -1 , Barcode does not exist in database
			{
				cout << "Barcode does not exist!" <<endl;
				system("pause");
			}
			
			break;

		/************************************************************************************************/
		/************************* DISPLAY SCREEN TO ASK SALES OR QTY RESTOCK ***************************/
		/************************************************************************************************/

		case eSaleRestockTrans:	
			
			choice = UI_UpdateTrans();	//Display Sales or qty restock screen
			
			switch( choice )
			{

			/************************ UPDATE SALES QUANTITY **********************************/
			case 1:	

				UI_UpdateSales();	//Display screen to update sales

				Index = control.CheckBarcodeExist(Barcode);	//Returns index where barcode is found

				if ( !control.CheckSalePossible ( Index ,  Sold ) )
				{
					cout << endl << "Not enough Quantity in Stock to perform Sales" << endl;
					system("pause");
					break;
				}

				if( Index != -1 )	//If barcode exists, continue to perform update Sales
				{

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					control.saleProduct( Index , Sold );
					cout << endl << "Sales have been updated!" << endl;

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
				}

				else
				{
					cout << "Barcode does not exist!" <<endl;
					system("pause");
				}

				break;

			/**************************** UPDATE RESTOCK QUANTITY ******************************/
			case 2:	

				UI_UpdateRestock();	//Display screen to update stock

				int Index = control.CheckBarcodeExist(Barcode);	//Returns index where barcode is found

				if( Index != -1 )	//If barcode exists, continue to perform update Stock
				{
						
					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					control.restockProduct( Index , Stock );
					cout << endl << "Stock has been added!" << endl;

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
				}

				else
				{
					cout << "Barcode does not exist!" <<endl;
					system("pause");
				}
				
				
				break;
			}

			break;	//Break for ROOT case 4(Sales or restock?)

		/****************************************************************************************************/
		/*************************************** GENERATE STATISTICS ****************************************/
		/****************************************************************************************************/

		case eGenerateStats:	

			choice = UI_GenerateStats();	//Display Generate statistics screen
			
			switch( choice )
			{
			
			/***************************** TOP X SELLING PRODUCT (LIST) *************************/
			case 1:	
			{
				UI_TopXselling();	//Display Top X selling product screen

				int X = 0;
				cin >> X;
				

				cout << endl << "Top " << X << " Selling Products are : " << endl;

				/***************************** TIME CHECK ********************************/
												Timer t;
				/*************************************************************************/

				cout << control.topXproduct(X);

				/***************************** TIME CHECK ********************************/
												t.print();
				/*************************************************************************/

				break;
			}

			/************************ BEST SELLING PRODUCT IN CATEGORY **************************/
			case 2:	
			{
				UI_BSPcategory();	//Display Best selling in category screen
				getline( cin , rubbish );	//Clears the \n 
				getline( cin , Cat );

				cout << endl << "Best selling Product in " << Cat << " is : " << endl;

				/***************************** TIME CHECK ********************************/
												Timer t;
				/*************************************************************************/

				cout << control.BestInCategory(Cat) << endl;

				/***************************** TIME CHECK ********************************/
												t.print();
				/*************************************************************************/

				break;
			}

			/*************************** BEST SELLING MANUFACTURER ******************************/
			case 3:	

				UI_BSmanufacturer();	//Display Best Manufacturer screen

				/***************************** TIME CHECK ********************************/
												Timer t;
				/*************************************************************************/

				cout << control.BestManufac() << endl;

				/***************************** TIME CHECK ********************************/
												t.print();
				/*************************************************************************/

				break;
			}

			break;	//Break for ROOT case 5 (Generate statistics)

		/****************************************************************************************************/
		/******************************************* SEARCH *************************************************/
		/****************************************************************************************************/

		case eSearchProduct:	
			
			system("cls");

			cout << "==============================================================================" << endl;
			cout << "                             SEARCH PRODUCTS BY:                              " << endl;
			cout << "==============================================================================" << endl;

			cout << "[1] Product Name" << endl;
			cout << "[2] Barcode" << endl;
			cout << "[3] Category" << endl;
			cout << "[4] Manufacturer" << endl;

			cout << "Enter choice: " <<endl;
			cin >> choice;

			switch(choice)
			{
				//By product
				case 1:
				{
						
					cout << "Enter product name: " ;
					getline( cin , rubbish );	//Clears the \n 
					getline( cin , Name );

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					cout << endl << control.SearchByName(Name);

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
					break;
				}
				//By barcode
				case 2:
				{

					cout << "Enter barcode number: " ;
					cin >> Barcode;

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					cout << endl << control.SearchByBarcode(Barcode);

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
					break;
				}
				//By category
				case 3:
				{
					cout << "Enter Category name: " ;
					getline( cin , rubbish );	//Clears the \n 
					getline( cin , Cat );

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					cout << endl << control.SearchByCategory(Cat);

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
					break;
				}
				//By Manufacturer
				case 4:
				{
					cout << "Enter Manufacturer name: " ;
					getline( cin , rubbish );	//Clears the \n 
					getline( cin , Manufac );

					/***************************** TIME CHECK ********************************/
													Timer t;
					/*************************************************************************/

					cout << endl << control.SearchByManufac(Manufac);

					/***************************** TIME CHECK ********************************/
													t.print();
					/*************************************************************************/
					break;
				}
			}

			break;	//Break for root case 6 ( Search by.. )

		/***********************************************************************************************/
		/******************************************* CHECK EXPIRY **************************************/
		/***********************************************************************************************/

		case eCheckExpiry:
		{

			system("cls");

			cout << "Enter today's date (DDMMYYYY): " ;
			cin >> currentDate;

			cout << endl << "Enter barcode of product you wish to check: ";
			cin >> Barcode;

			Index = control.CheckBarcodeExist(Barcode);

			if ( Index == -1 )
			{
				cout << endl << "Barcode Does Not Exist" << endl;
				system("pause");
				break;
			}

			/***************************** TIME CHECK ********************************/
											Timer t;
			/*************************************************************************/

			int WhatExpiryAmI = control.CheckExpiry( Index , currentDate );

			if( WhatExpiryAmI == -1 )
			{
				cout << endl << "This Product is not Perishable (It does not have expiry)" << endl;
			}

			if( WhatExpiryAmI == 0 )
			{
				cout << endl << "Product Expired" << endl;
			}

			if( WhatExpiryAmI == 1 )
			{
				cout << endl << "Product is alive and kicking!" << endl;
			}

			/***************************** TIME CHECK ********************************/
											t.print();
			/*************************************************************************/
			break;
		}

		/***********************************************************************************************/
		/*************************************** BATCH PROCESSING **************************************/
		/***********************************************************************************************/

		case eBatchProcessing:
		{
			system("cls");

			string BatchFileName;

			cout << "Enter name of batchfile to load( Format: batchjobs-m.txt ): " ;
			cin >> BatchFileName;

			/***************************** TIME CHECK ********************************/
											Timer t;
			/*************************************************************************/

			control.ReadBatchJob(BatchFileName);
			control.PerformBatchJob();

			/***************************** TIME CHECK ********************************/
											t.print();
			/*************************************************************************/
		}

		case eSortByWorth:
		{
			/***************************** TIME CHECK ********************************/
											Timer t;
			/*************************************************************************/

			control.SortByWorth();

			/***************************** TIME CHECK ********************************/
											t.print();
			/*************************************************************************/

			control.toSortedFile("sorted.txt");
		}

		case eExit:	//Bye Bye
			break;

		}//Root's Switch

	}while(choice != 0 );


	system("cls");

	cout <<"BYE BYE" <<endl;
	cout <<"Please relax while we save your data. =) Muacks"<<endl;

	string backup = "backup.txt";

	/***************************** TIME CHECK ********************************/
									Timer t;
	/*************************************************************************/

	control.BackupFile(backup);

	/***************************** TIME CHECK ********************************/
									t.print();
	/*************************************************************************/
}

int UI::UI_OpeningScreen()
{
	int choice = 0;
	bool ValidChoice = false;

	while( !ValidChoice )	//Continue until Valid Choice is Entered
	{

		system("cls");	//Clears the screen

		//Header
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "            CEG Hypermarket Inventory Control and Management System            " << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		//Main Menu
		cout << endl << endl;

		cout <<	"[1] Add New Product"			<< endl;
		cout << "[2] Delete Product"			<< endl;
		cout << "[3] Reset Product Sales"		<< endl;
		cout << "[4] Sale/Restock Transaction"  << endl;
		cout << "[5] Generate Statistics"		<< endl;
		cout << "[6] Search Products"			<< endl;
		cout << "[7] Check Expiry Date"			<< endl;
		cout << "[8] Batch Processing"          << endl;
		cout << "[9] Sort By Worth"				<< endl;
		cout << "[0] Bye Bye"					<< endl;

		//Ask for User's Choice
		cout << endl << "What would you like to do? [Please enter number] : ";
		cin >> choice;
		
		//If choice is valid, return the choice for implementation
		if( choice > -1 && choice<10 )
			return choice;
	
		cout << endl << "Invalid Choice." << endl;	//This would execute if choice is nt btw 0 to 8 inclusive.
		system("pause");
	}
	return 0;	//Just for removing warning:Not all control paths return a value (It will never execute)
}

void UI::UI_AddPdt()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                               Add New Product                                " << endl;
	cout << "==============================================================================" << endl;

	char IamPerishable;	

	cout<<"Is it a Perishable Food [Y]/[N] ";
	cin >> IamPerishable;
	getline( cin , rubbish );
		
	cout << endl << endl << "Please enter Product details" << endl;

	cout << endl << "Product Name: ";
	getline( cin , Name );

	cout << endl << "Product Category: ";
	getline( cin , Cat );

	cout << endl << "Product Barcode Number: ";
	cin >> Barcode;

	cout << endl << "Product Price: ";
	cin >> price;
	getline( cin , rubbish);

	cout << endl << "Product Manufacturer: ";
	getline( cin , Manufac );

	cout << endl << "Product Stock: " ;
	cin >> Stock;

	cout << endl << "Product Sold: " ;
	cin >> Sold;
	getline(cin , expiry); //Stores nothing if it is not perishable

	if( IamPerishable =='y'|| IamPerishable =='Y' )	//If it is a Perishable Food
	{
		cout << endl <<"Enter expiry date ( DDMMYYYY ) " ;
		getline(cin, expiry);

		cout << endl <<"Enter discount percentage " ;
		cin >> discount;
	}
}

void UI::UI_DelPdt()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                             Delete Product                                   " << endl;
	cout << "==============================================================================" << endl;
		
	cout << endl << "Please enter Product barcode you wish to remove: ";
	cin >> Barcode;
}

void UI::UI_ResetPdt()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                            Reset Product Sales                               " << endl;
	cout << "==============================================================================" << endl;


	cout<< "Enter Barcode number to reset its Sales Counter to zero: ";
	cin >> Barcode;
}

int UI::UI_UpdateTrans()
{
	int OptionChoice = 0;

	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                          Sales/Restock Update                                " << endl;
	cout << "==============================================================================" << endl;
		
	cout << endl << endl;
	cout << "[1] Sales Update" << endl;
	cout << "[2] Restock Update" << endl;
		
	cout << endl << "Please enter your option: ";
	cin >> OptionChoice;
	
	return OptionChoice;
}

void UI::UI_UpdateSales()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                              Sales Update                                    " << endl;
	cout << "==============================================================================" << endl;
			
	cout << endl << "Please enter Product barcode: ";
	cin >> Barcode;
	cout << endl << "Please enter Quantity Sold: ";
	cin >> Sold;
}

void UI::UI_UpdateRestock()
{
	system("cls");
	
	cout << "==============================================================================" << endl;
	cout << "                             Restock Update                                   " << endl;
	cout << "==============================================================================" << endl;
			
	cout << endl << "Please enter Product barcode: ";
	cin >> Barcode;
	cout << endl << "Please enter Quantity Restocked: ";
	cin >> Stock;
}

int UI::UI_GenerateStats()
{
	int OptionChoice = 0;

	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                             Generate Statistics                              " << endl;
	cout << "==============================================================================" << endl;
		
	cout << endl << endl;

	cout << "[1] Top X selling products" << endl;
	cout << "[2] Best selling product in one Category" << endl;
	cout << "[3] Best selling manufacturer" << endl;
	cout << endl << "Please enter your option: ";

	cin >> OptionChoice;
	return OptionChoice;
}

void UI::UI_TopXselling()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                           Top X Selling Products                             " << endl;
	cout << "==============================================================================" << endl;
			
	cout << "Please enter value of X: ";
}

void UI::UI_BSPcategory()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                     Best Selling Product In A Category                       " << endl;
	cout << "==============================================================================" << endl;
			
	cout << endl << "Please enter a category of your choice: ";
}

void UI::UI_BSmanufacturer()
{
	system("cls");

	cout << "==============================================================================" << endl;
	cout << "                          Best Selling Manufacturer                           " << endl;
	cout << "==============================================================================" << endl;

	cout << endl << "Best selling Manufacturer is : " ; 
}