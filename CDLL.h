/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _CDLL_H_
#define _CDLL_H_

#include "Storage.h"
#include <string>

template <typename T>
class CDLL : public Storage<T>
{
private:

    struct ListNode
	{
        T* item;
        ListNode *next;
        ListNode *prev;
    };

    ListNode* _tail;

    //Return pointer to where index is found.
    ListNode* traverseTo( int index) 
	{
        ListNode* cur;

		//If index is at top half
        if (index < getSize()/2) 
		{
            cur = _tail->next;	//Start from first node
            
			for ( int i = 1 ; i < index  ; ++i )
                cur = cur->next;	//Search forward
        }

		//If index is at bottom half
		else 
		{
            cur = _tail;		//Start from tail node
            
			for ( int i = 0 ; i < getSize() - index ; ++i )
                cur = cur->prev;	//Search Backwards
        }
		
        return cur;
    }

    //Sort By Revenue (Insertion sort)
	//Sorts revenue in descending order
	//Actual contents changes
    void SortByRevenue() 
	{
		ListNode *prev = _tail->next;
        ListNode *cur = _tail->next->next;
		
        while (cur != _tail->next)
		{
            // if cur is greater than prev
            if (cur->item->Revenue() > prev->item->Revenue())
			{
                ListNode *tmp = cur;
                T* holder;	//Temporary holder for item(Product)

				// Move cur item to the front
                for (holder = tmp->item ; prev != _tail && prev->item->Revenue() < holder->Revenue() ; tmp = prev, prev = prev->prev) 
				{
                         tmp->item = prev->item;
                }
                tmp->item = holder;
            }
            // Move on to next node
            prev = cur;
            cur  = cur->next;
        }
    }

public:
    
	CDLL() : Storage<T>() 
	{ 
		_tail = NULL; 
	}

    ~CDLL()
	{
        while ( !isEmpty() )
            delItem( getSize() );
    }

	//Returns Stock Quantity at index
	int getStockAtIndex ( int index )
	{
		return traverseTo(index)->item->getStock();
	}

	//Return index to where barcode is found
	int IndexOfBarcode( string barcode)
	{
		ListNode *cur = _tail->next ;

		for( int i = 1 ; i < getSize()+1 ; ++i )
		{
			if ( cur->item->getBarcode() == barcode )
			{
				return i;
			}

			cur = cur->next;
		}
		return -1;
	}

    void toFile(string filename)
	{
        ListNode* cur = _tail->next;

        ofstream outFile;
		outFile.open(filename);

        outFile << getSize() << endl << endl;	//number of products

        while (cur != _tail->next)
		{
            outFile << cur->item->toString() << endl;	//product by product
            cur = cur->next;
        }

		outFile.close();
    }

    bool addItem(T* newItem) 
	{
		//Initialize newNode
        ListNode* newNode = new ListNode;
        newNode->item = newItem;
		newNode->next = NULL;
        newNode->prev = NULL;
		
        //If it is an empty list
        if ( isEmpty() )
		{
			newNode->next = newNode;
            newNode->prev = newNode;
            _tail = newNode;
        }
		
		else 
		{
			//Links newNode to List
			newNode->next = _tail->next;
            newNode->prev = _tail;
            	
			//Links List to newNode
			_tail->next->prev = newNode;
			_tail->next = newNode; 
            
            _tail = newNode; //Update the new _tail
        }

        _size++;
        return true;
    }

    bool delItem(int index)
	{
        ListNode *cur;
        if ( (index < 1) || (index > getSize()) )
		{
            return false;
        } 
		
		//Deleting at tail
		if ( index == getSize() )
		{
            cur = _tail;
            _tail->prev->next = _tail->next;
            _tail->next->prev = _tail->prev;
            _tail = _tail->prev;	//Update tail
        }
		
		else
		{
            cur = traverseTo(index);	
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }

        delete cur;
        cur = NULL;
        _size--;
        return true;
    }

    void resetItem(int index)
	{
		traverseTo(index)->item->resetSold();
    }

    void updateStock(int index, int numStock)
	{
		traverseTo(index)->item->restock(numStock);
    }

    void updateSale(int index, int numSold)
	{
		traverseTo(index)->item->sale(numSold);
    }

    int checkExpiry(int index, string curDate)
	{
		return ( traverseTo(index)->item->Checkexpiry(curDate ) );
    }

	//------------------------------------------------------------------------------------/
    /************************************** STATISTICS ***********************************/
	//------------------------------------------------------------------------------------/
    string topXitem(int x) 
	{
		SortByRevenue();

		ostringstream oss;

        int count = 1;
        ListNode *cur = _tail->next;
		ListNode *prev = _tail;

        while (count <= x)
		{
            oss << cur->item->toString() << endl;

            if (cur->item->Revenue() != prev->item->Revenue())
                count++;
            prev = cur;
            cur = cur->next;
        }

		return oss.str();
    }

    string topCategoryItem(string category) 
	{
        ListNode *cur = _tail;
		double SameRevenueCheck = 0;

		//Sort by revenue
		SortByRevenue();

		ostringstream oss;


		//Continues checking until first top product found or end of list, whichever comes first.
		do
		{
			//First occurence of category is the top product in category
			if( cur->item->getCat() == category )
			{
				SameRevenueCheck = cur->item->Revenue();	//Stores revenue of top product
				oss << cur->item->toString();
			}

			cur = cur->next;

		}while( SameRevenueCheck == 0 && cur!= _tail );

		//Check if 2nd, 3rd, 4th... occurence matches the revenue of the top product
		bool AllTopProductsFound = false;

		while( !AllTopProductsFound && cur != _tail )
		{
			cur = cur->next;

			if( cur->item->getCat() == category )
			{
				if( cur->item->Revenue() == SameRevenueCheck )
				{
					oss << cur->item->toString() <<endl;
				}

				//If occurence found, but revenue does not match, All top products has been found.
				else
				{
					AllTopProductsFound = true;
				}
			}
		}

		return oss.str();
    }

    string topManufacturer()
	{		
		//Struture to hold manufacturer and its corresponding sales
		struct Manu_Record
		{
			string manufacturer;
			double sales;
		};
		
		string tempManufac;
		string BestManufac;

		double revenue = 0;
		double topRevenue = 0;

		double tempSales = 0;

		ListNode *cur = _tail;

		int count = 0;	//For temp array
		
		int size = getSize();
		Manu_Record *temp = new Manu_Record[size];	//Creates temp array

		//Step 1: Transfer data from CDLL to temp array
		//Putting all sales of same manufacturer together
		for ( int i = 0 ; i < getSize() ; ++i)
		{
			//Read in manufacturer and sales from CDLL to temp variable
			tempManufac = cur->item->getManufac();
			tempSales = cur->item->Revenue();

			bool SalesAdded = false;

			//Search through temp array
			//If have such manufacturer, add its sales
			for ( int j = 0 ; j < count ; ++j )
			{
				if( temp[j].manufacturer == tempManufac )
				{
					temp[j].sales += tempSales;
					SalesAdded = true;
				}
			}

			//If sales not added, add new manufacturer
			if( !SalesAdded )
			{
				temp[count].manufacturer = tempManufac;
				temp[count].sales = tempSales;
				count++ ;
			}
			
			//Move to next node
			cur = cur -> next;
		}

		//Step 2: After temp array is populated,
		//Search max sales in temp array
		for( int i = 0 ; i < count ; ++i )
		{	
			revenue = temp[i].sales;
				
			if( revenue > topRevenue )
			{
				topRevenue = revenue;
				BestManufac = temp[i].manufacturer;
			}
		}
		return BestManufac;

	}
		
	//------------------------------------------------------------------------------------/
	/************************************** SEARCHING ************************************/
	//------------------------------------------------------------------------------------/

    string searchByName( string name ) 
	{
		ListNode *cur = _tail;

		ostringstream oss;

		do
		{
			if ( cur->item->getName() == name )
			{
				oss << cur->item->toString() << endl;
			}

			cur = cur->next;

		}while( cur != _tail );

		return oss.str();
    }

    string searchByBarcode( string barcode ) 
	{
        ListNode *cur = _tail;
		bool found = false;

		ostringstream oss;

		do
		{
			if ( cur->item->getBarcode() == barcode )
			{
				oss << cur->item->toString();
				found = true;
			}

			cur = cur->next;

		}while( cur != _tail && !found );

		return oss.str();
    }

    string searchByCategory(string category) 
	{
		ListNode *cur = _tail;
       
		ostringstream oss;

        do 
		{
            if ( cur->item->getCat() == category)
			{
                oss << cur->item->toString()<< endl;
            }

            cur = cur->next;

        }while (cur != _tail);

        return oss.str();
    }

    string searchByManufacturer(string manufacturer) 
	{
		ListNode *cur = _tail;
        
		ostringstream oss;

        do 
		{
            if ( cur->item->getManufac() == manufacturer )
			{
                oss << cur->item->toString()<<endl;
            }

            cur = cur->next;

        }while (cur != _tail);

        return oss.str();
    }

	//------------------------------------------------------------------------------------/
	/************************** LAB 4 ADDITIONS: RESET STOCK *****************************/
	//------------------------------------------------------------------------------------/

	void resetStock(int index)
	{
		traverseTo(index)->item->resetStock();
    }

	//------------------------------------------------------------------------------------/

	//------------------------------------------------------------------------------------/
	/************************** LAB 5 ADDITIONS: NOT IMPLEMENTED *************************/
	//------------------------------------------------------------------------------------/

	virtual void SortByWorth() {}
	virtual void toSortedFile(string filename) {}

	//------------------------------------------------------------------------------------/
}; 

#endif