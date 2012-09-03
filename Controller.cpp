/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#include "Controller.h"


Controller::Controller()
{
	/**************************************************************************/
	/// HELLO, CHOOSE YOUR STORAGE TYPE HERE BY ADDING AND REMOVING COMMENTS ///

	
	//_List = new CDLL<Product>;		//Circular Double linked list storage
	_List = new LL<Product>;			//Linked List Storage
	//_List = new ArrayList<Product>;	//Dynamic Array Storage

	_AllJobs = new myStack< myQueue<BatchJob>* >;
	/**************************************************************************/
}

Controller::~Controller()
{
    delete _List;
	delete _AllJobs;
}

bool Controller::ReadFile()
{
	string filename;
	cin >> filename;

    int N = 0; //Total number of products
    
	string name; 
	string category;
	string barcode;
	string manufac;
	string rubbish;
	string expiry;
    double price;
	double discount;
    int numStock;
	int numSold;

    Product* newProduct;


		/***************************** TIME CHECK ********************************/
										Timer t;
		/*************************************************************************/

    ifstream inFile(filename);

	//Error Check if unable to open file
	if( !inFile.is_open() )
	{
		return false;
	}

    inFile >> N;	

    getline(inFile, rubbish); // Discard empty spaces on 1st line
    getline(inFile, rubbish); // Discard empty spaces on 2nd line

    // Start reading information to _productList
    for( int i = 0  ;  i < N  ;  ++i )
	{
		getline(inFile, name);
        getline(inFile, category);
		getline(inFile, barcode);
        inFile >> price;
        getline(inFile, rubbish); // Discard empty spaces after using normal cin.
        getline(inFile, manufac);
        inFile >> numStock;
        inFile >> numSold;
        getline(inFile, rubbish); // Discard empty spaces after using normal cin.
        
        // Get expiry if there is. If not, it will be an empty string(implies Normal Good)
        getline(inFile, expiry);

		//Account for normal product
        if ( expiry.empty() )	//If it is not perishable, create normal product
		{
            newProduct = new Product(name, category, barcode, price, manufac, numStock, numSold);
            _List->addItem(newProduct);

        } 
		
		//Account for Perishable product
		else	//This would execute if there were actually contents in expiry.
		{
            inFile >> discount;
            getline(inFile, rubbish); // Discard empty spaces after using normal cin.
            getline(inFile, rubbish); // Discard empty line

            newProduct = new Perishable(name, category, barcode, price, manufac, numStock, numSold, expiry, discount);
            _List->addItem(newProduct);
        }
    }

    inFile.close();


		/***************************** TIME CHECK ********************************/
										t.print();
		/*************************************************************************/
	return true;
}

void Controller::BackupFile(string filename) 
{
    _List->toFile(filename);
}

//--------------------------------------------------------------------------------------------------------/
/********************************************* BASIC METHODS *********************************************/
//--------------------------------------------------------------------------------------------------------/

bool Controller::CheckSalePossible ( int index , int numSold )
{
	return ( _List->getStockAtIndex( index ) >= numSold );
}

int Controller::CheckBarcodeExist(string barcode)
{
	return _List->IndexOfBarcode(barcode);
}

void Controller::Add(string Name, string Cat, string Barcode, double price, string Manufac, int Stock, int Sold, string expiry, double discount)
{
	Product *newProduct;

	if( expiry.empty() ) //If expiry is empty, it is a normal good
	{
		newProduct = new Product(Name, Cat, Barcode, price, Manufac, Stock, Sold);
		_List->addItem(newProduct);
	}

	else	//If expiry contains data, it is a perishable good
	{
		newProduct = new Perishable(Name, Cat, Barcode, price, Manufac, Stock, Sold, expiry, discount);
		_List->addItem(newProduct);
	}
}

void Controller::Del(int Index)
{
	_List->delItem(Index);
}

void Controller::Reset(int Index)
{
	_List->resetItem(Index);
}

void Controller::saleProduct(int Index , int numSold)
{

	_List->updateSale(Index , numSold);
	_List->updateStock(Index , -numSold);
}

void Controller::restockProduct(int Index , int numStock)
{
	_List->updateStock(Index, numStock);
}

int Controller::CheckExpiry( int Index , string currentDate )
{
	return _List->checkExpiry(Index , currentDate);
}

//--------------------------------------------------------------------------------------------------------/
/************************************************ STATISTICS *********************************************/
//--------------------------------------------------------------------------------------------------------/

string Controller::topXproduct(int X)
{
	return _List->topXitem(X);
}

string Controller::BestInCategory(string category)
{
	return _List->topCategoryItem(category);
}

string Controller::BestManufac()
{
	return _List->topManufacturer();
}

//--------------------------------------------------------------------------------------------------------/
/*********************************************** SEARCH **************************************************/
//--------------------------------------------------------------------------------------------------------/

string Controller::SearchByName(string name)
{
	return _List->searchByName(name);
}
    
string Controller::SearchByBarcode(string barcode)
{
	return _List->searchByBarcode(barcode);
}
   
string Controller::SearchByCategory(string category)
{
	return _List->searchByCategory(category);
}

string Controller::SearchByManufac(string manufacturer)
{
	return _List->searchByManufacturer(manufacturer);
}

//--------------------------------------------------------------------------------------------------------/
/******************************************** BATCH PROCESSING *******************************************/
//--------------------------------------------------------------------------------------------------------/


void Controller::ResetStock(int Index)
{
	_List->resetStock(Index);
}

//Read in filename to do batch processing.
//Post: _AllJobs( A stack of jobs ) will contain jobs in order
//eg. Job 1 , Job 2 , Job 3 , ...
void Controller::ReadBatchJob(string BatchFileName)
{
	string user;
	string jobtype;
	string name;
	string category;
	string barcode;
	double price = 0;
	string manufacturer;
	int QtytoUpdate = 0;
	string expiry;

	string rubbish;

	int NumUser = 0;
	int NumJobs_PerUser = 0;

	BatchJob J;
	
	//Open file for ifstream
	ifstream readJob(BatchFileName);

	//Read in total number of users
	readJob >> NumUser;
	getline(readJob, rubbish);

	for( int i = 0 ; i < NumUser ; ++i )	//Process user by user
	{
		myQueue<BatchJob> *Q = new myQueue<BatchJob>;

		getline(readJob, rubbish);
		getline(readJob, user);

		//Read in number of jobs of one user
		readJob >> NumJobs_PerUser;
		getline(readJob, rubbish);

		//Process jobs of one individual user
		for( int j = 0 ; j < NumJobs_PerUser ; ++j)	
		{
			getline(readJob, rubbish);

			J.setUser(user);

			getline(readJob, jobtype);

			if( jobtype == "ADD" )
			{
				//Read in Data
				getline(readJob, name);
				getline(readJob, category);
				getline(readJob, barcode);
				readJob >> price;
				getline(readJob, rubbish);
				getline(readJob, manufacturer);
				readJob >> QtytoUpdate;
				getline(readJob, rubbish);

				//Sets the data into tempArray
				J.setJobtype(1);
				J.setName(name);
				J.setCategory(category);
				J.setBarcode(barcode);
				J.setPrice(price);
				J.setManufacturer(manufacturer);
				J.setQtytoUpdate(QtytoUpdate);
			}

			if( jobtype == "DELETE" )
			{
				getline(readJob, barcode);

				J.setJobtype(2);
				J.setBarcode(barcode);
			}

			if( jobtype == "RESTOCK" )
			{
				getline(readJob, barcode);
				readJob >> QtytoUpdate;
				getline(readJob, rubbish);

				J.setJobtype(3);
				J.setBarcode(barcode);
				J.setQtytoUpdate(QtytoUpdate);
			}

			if( jobtype == "DISPOSE" )
			{
				getline( readJob , barcode );
				getline( readJob , expiry );

				J.setJobtype(4);
				J.setBarcode(barcode);
				J.setExpiry(expiry);
			}

			if( jobtype == "SALE" )
			{
				getline( readJob , barcode );
				readJob >> QtytoUpdate;
				getline(readJob, rubbish);

				J.setJobtype(5);
				J.setBarcode(barcode);
				J.setQtytoUpdate(QtytoUpdate);
			}

			Q->push(J);
		}//End of temp storing 1 user's job(s)

		//Stores 1 user into ultimate stack.
		_AllJobs->push( Q );

	}//End of processing 1 user's requests

	readJob.close();
}//End of ReadBatchJob

void Controller::PerformBatchJob()
{
	BatchJob J;	// A temp variable to process information of one job.
	myQueue<BatchJob> *Q;

	ofstream writeLog("log.txt");

	while( !_AllJobs->empty() )
	{
		Q = _AllJobs->top() ;
		_AllJobs->pop() ;

		while( !Q->empty() )
		{
			J = Q->front();
			Q->pop();

			int Index = CheckBarcodeExist( J.getBarcode() );

			switch( J.getJobtype() )
			{

			case 1:	//Add
			
				if( Index != -1 )
				{
					writeLog << J.getBarcode() << " ADD " << J.getUser() << "\n" ;
				}

				else
				{
					Add( J.getName() , J.getCategory() , J.getBarcode() , J.getPrice() , J .getManufacturer() , J.getQtytoUpdate() , 0 , "" , 0 );
				}

				break;

			case 2:	//Delete

				if( Index == -1 )
				{
					writeLog << J.getBarcode() << " DELETE " << J.getUser() << "\n" ;
				}

				else
				{
					Del(Index);
				}

				break;

			case 3: //Restock

				if( Index == -1 )
				{
					writeLog << J.getBarcode() << " RESTOCK " << J.getUser() << "\n" ;
				}

				else
				{
					restockProduct(Index , J.getQtytoUpdate() );
				}

				break;

			case 4:	//Dispose

				if( Index == -1 || CheckExpiry(Index , J.getExpiry()) != 0 )
				{
					writeLog << J.getBarcode() << " DISPOSE " << J.getUser() << "\n" ;
				}

				else
				{
					ResetStock(Index);
				}

				break;

			case 5:	//Sale

				if( Index == -1 || !CheckSalePossible(Index , J.getQtytoUpdate()) )
				{
					writeLog << J.getBarcode() << " SALE " << J.getUser() << "\n" ;
				}

				else
				{
					saleProduct( Index , J.getQtytoUpdate() );
				}

				break;
			}// Switch Job type
		}//while queue not empty
	}//while not all jobs empty

	writeLog.close();

}//End of PerformBatchJob

//--------------------------------------------------------------------------------------------------------/
/****************************************** LAB 5: SORT BY WORTH *****************************************/
//--------------------------------------------------------------------------------------------------------/

void Controller::SortByWorth()
{
	_List->SortByWorth();

}

void Controller::toSortedFile(string filename)
{
	_List->toSortedFile(filename);
}

//--------------------------------------------------------------------------------------------------------/