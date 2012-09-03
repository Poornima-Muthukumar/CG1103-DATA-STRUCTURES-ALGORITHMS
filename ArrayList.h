/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include "Storage.h"
#include <string>

template <typename T>
class ArrayList : public Storage<T>
{
private:
	
	int  MAX_LIST;
    T** good;

    void swap(int i, int j)
	{
        T* temp;
        temp    = good[i];
        good[i] = good[j];
        good[j] = temp;
    }

    //Quicksort by Price(Unstable)
    void QSortPrice(int left, int right) 
	{
        int last;
        if (left >= right) return ;

        swap(left, (left+right)/2);
        last = left;
        for (int i = left+1; i <= right; i++)
            if (good[i]->getPrice() < good[left]->getPrice())
                swap(++last, i);
        swap(left, last);

        QSortPrice(left, last-1);
        QSortPrice(last+1, right);
    }

	//Quicksort by Stock(Unstable)
	void QSortStock(int left, int right) 
	{
        int last;
        if (left >= right) return ;

        swap(left, (left+right)/2);
        last = left;
        for (int i = left+1; i <= right; i++)
			if (good[i]->getStock() < good[left]->getStock())
				swap(++last, i);
		swap(left, last);
		
        QSortStock(left, last-1);
        QSortStock(last+1, right);
    }

	//Quicksort by worth (unstable)
	void QSortWorth(int left, int right) 
	{
        int last;
        if (left >= right) return ;

        swap(left, (left+right)/2);
        last = left;
        for (int i = left+1; i <= right; i++)
            if (good[i]->getWorthRank() < good[left]->getWorthRank())
                swap(++last, i);
        swap(left, last);

        QSortWorth(left, last-1);
        QSortWorth(last+1, right);
    }

	//Aids RekeyStock , RekeyPrice
	//sorts selected items from start to end
	//Bubblesort: in ascending orders of index
	void sortIndex( int start , int end )
	{
		for( int i = start ; i < end ; ++i )
		{
			for( int j = i+1 ; j < end+1 ; ++j )
			{
				if( good[i]->getIndex() > good[j]->getIndex() )
				{
					swap( i , j );
				}
			}
		}
	}

	//Aids RekeyWorth
	//sorts selected items from start to end
	//Bubblesort: in ascending orders of PriceRank
	void sortPriceRank( int start , int end )
	{
		for( int i = start ; i < end ; ++i )
		{
			for( int j = i+1 ; j < end+1 ; ++j )
			{
				if( good[i]->getPriceRank() > good[j]->getPriceRank() )
				{
					swap( i , j );
				}
			}
		}
	}

	//Pre: Quicksorted(unstable)
	//Post: Reorders similar Stock qty based on their original index
	void rekeyStock()
	{
		for(int i = 0 ; i < getSize() - 1 ; ++i )
		{
			int begin = 0 ;
			int stop = 0 ;

			if( good[i]->getStock() == good[i+1]->getStock() )
			{
				begin = i;

				for( int j = i+1 ; j < getSize() ;  ++j )
				{
					if( j == getSize() - 1 )
					{
						stop = j;
						i = j ;
						sortIndex( begin , stop );
						break;
					}

					if( good[j]->getStock() != good[j+1]->getStock() )
					{
						stop = j;
						i = j ;
						sortIndex( begin , stop );
						break;
					}
				}		
			}
		}
	}

	//Pre: Quicksorted(unstable)
	//Post: Reorders similar Price based on their original index
	void rekeyPrice()
	{
		for(int i = 0 ; i < getSize() - 1 ; ++i )
		{
			int begin = 0 ;
			int stop = 0 ;

			if( good[i]->getPrice() == good[i+1]->getPrice() )
			{
				begin = i;

				for( int j = i+1 ; j < getSize() ;  ++j )
				{
					if( j == getSize() - 1 )
					{
						stop = j;
						i = j ;
						sortIndex( begin , stop );
						break;
					}

					if( good[j]->getPrice() != good[j+1]->getPrice() )
					{
						stop = j;
						i = j ;
						sortIndex( begin , stop );
						break;
					}
				}		
			}
		}
	}

	//Pre: Quicksorted(unstable)
	//Post: Reorders similar worth based on their PriceRank
	void rekeyWorth()
	{
		for(int i = 0 ; i < getSize() - 1 ; ++i )
		{
			int begin = 0 ;
			int stop = 0 ;

			if( good[i]->getWorthRank() == good[i+1]->getWorthRank() )
			{
				begin = i;

				for( int j = i+1 ; j < getSize() ; ++j )
				{
					if( j == getSize() - 1 )
					{
						stop = j;
						i = j ;
						sortPriceRank( begin , stop );
						break;
					}

					if( good[j]->getWorthRank() != good[j+1]->getWorthRank() )
					{
						stop = j;
						i = j ;	
						sortPriceRank( begin , stop );
						break;
					}
				}	
			}
		}
	}

public:
    
	ArrayList() : Storage<T>() 
	{ 
		MAX_LIST=1000;
		good=new T*[MAX_LIST];
	}

	~ArrayList()
	{
		delete []good;
    }

	int getStockAtIndex ( int index )
	{
		return good[index]->getStock();
	}

    //Return index to where barcode is found
	int IndexOfBarcode( string barcode )
	{
        for( int i = 0 ; i < getSize() ; ++i )
        {
			if( good[i]->getBarcode() == barcode )
				return i;
        }
		return -1;
	}

    void toFile(string filename)
	{
		ofstream outFile;
		outFile.open(filename);

        outFile << getSize() << endl << endl;	//number of products
	
		for ( int i = 0 ; i < getSize() ; ++i )
		{
			outFile << good[i]->toString() << endl;
		}
		
		outFile.close();
    }

    bool addItem(T* newItem) 
	{
		if( getSize() >= MAX_LIST )
		{
			//create the new dynamic array with double size
			//a common strategy is whenever we run out of space
			T** newArray = new T*[MAX_LIST * 2]; 

			for (int i = 0; i < getSize(); i++) //copy elements
			{ 
				newArray[i] = good[i];
			}
				delete []good;   //remove old array
				good = newArray; //point new array to the newly allocated array
                    
				MAX_LIST *= 2; //update the maxsize
			
		 }

		good[ getSize() ] = newItem;
		_size++;

        return true;
	}

    bool delItem(int index)
	{
		if(index>=getSize() || index<0)
		{
			return false;
		}

		T* cur = good[index];
        delete cur;
		cur = NULL;
        good[index] = NULL;

		for( int i=index ; i < getSize() - 1 ; ++i )
		{
			good[i]=good[i+1];
		}
			
		_size--;
		return true;
  
    }

    void resetItem(int index)
	{
		good[index]->resetSold();
    }

    void updateStock(int index, int numStock)
	{
		good[index]->restock(numStock);
    }

    void updateSale(int index, int numSold)
	{
		good[index]->sale(numSold);
    }

    int checkExpiry(int index, string curDate)
	{
		return ( good[index]->Checkexpiry(curDate ) );
	}
	
	//--------------------------------------------------------------------------------/
    /***********************************Statistics************************************/
	//--------------------------------------------------------------------------------/

	//Creates a temp array of x size which stores the top x revenue.
	//Goes through the original list repeatedly to compare with (x , x-1 ,...)revenue 
    string topXitem(int x) 
	{
		double*revenue2=new double[x];

		ostringstream os;
		double temp = 0;
		bool flag=false;
		double max;

		for(int j=0;j<x;j++)
		{
			max=-1;
			for(int i=0 ; i<getSize() ; i++)
			{
				if(good[i]->Revenue()>max)
				{
					flag=true;
					if(j!=0)//for case when there is no max,
							//for the first max to be added to revenue2
					{
						for(int k=0;k<j;k++)
							if(good[i]->Revenue()==revenue2[k])
						flag=false;
					}

					if(flag)
						max=good[i]->Revenue();
				}
			}
			revenue2[j]=max;
		}

		for(int i=0;i<x;i++)
		{	
			for( int j = 0 ; j < getSize() ; ++j )
			{
				if(revenue2[i]==good[j]->Revenue())
				{
					os << good[j]->toString() <<endl; 
				}
			}
		}

		return os.str();
    }

    string topCategoryItem(string category) 
	{
		ostringstream os;

		double temp_sales = 0;
		double max = 0 ;

		//First find the max sales in category
		for( int i = 0 ; i < getSize() ; ++i )
		{
			if( good[i]->getCat() == category )
			{
				temp_sales = good[i]->Revenue();

				if( temp_sales >max)
					max= temp_sales ;
			}
		}

		//Then, skim  through the list again
		//And output all product in this category with same revenue as the max
		for( int i = 0 ; i < getSize() ; ++i )
		{
			if( good[i]->getCat() == category )
			{
				double currnum = good[i]->Revenue();

				if( currnum == max )
				{
					os << good[i]->toString() <<endl; 
				}
			}
		}
			
		return os.str(); 
	}
		
    string topManufacturer()
	{
		string result;

		struct manu
		{
			string name;
			double money;
		};

		manu *max=new manu[MAX_LIST];
		max[0].name=good[0]->getManufac();
		max[0].money=good[0]->Revenue();
      
		for(int i=0;i<_size;i++)
		{
			max[i].name=good[i]->getManufac();
			max[i].money=good[i]->Revenue();       
		}

		for(int i=0;i<_size;i++)
		{
			for(int j=i+1;j<_size;j++)
			{
				if(max[i].name==max[j].name)
					max[i].money+=max[j].money;
			}
		}
		//sorting
		double m=0;
		for(int i=0;i<_size;i++)
		{
			if(m<max[i].money)
			{
				m=max[i].money;
				result=max[i].name;
			}
		}
              
		return result;
    }

	//--------------------------------------------------------------------------------/
	/************************************Searching************************************/
	//--------------------------------------------------------------------------------/

    string searchByName( string name ) 
	{
		ostringstream oss;

		for(int i=0;i<getSize();i++)
		{
			if(good[i]->getName()==name)
				oss << good[i]->toString() << endl;
		}

		return oss.str();
    }

    string searchByBarcode( string barcode ) 
	{
		ostringstream oss;

        for(int i=0;i< getSize() ;i++)
        {
			if(good[i]->getBarcode()==barcode)
                oss << good[i]->toString();
        }

		return oss.str();
    }

    string searchByCategory(string category) 
	{
		ostringstream oss;

		for(int i=0;i<getSize();i++)
		{
			if(good[i]->getCat()==category)
				oss << good[i]->toString() << endl;
		}

		return oss.str();
    }

    string searchByManufacturer(string manufacturer) 
	{
		ostringstream oss;

		for(int i=0;i<getSize();i++)
		{
			if(good[i]-> getManufac()==manufacturer)
				oss << good[i]->toString() << endl;
		}

		return oss.str();
    }

	//------------------------------------------------------------------------------------/
	/************************** LAB 4 ADDITIONS: RESET STOCK *****************************/
	//------------------------------------------------------------------------------------/

	void resetStock(int index)
	{
		good[index]->resetStock();
    }

	//------------------------------------------------------------------------------------/
	/************************* LAB 5 ADDITIONS: TESTING PURPOSES *************************/
	//------------------------------------------------------------------------------------/

	void SortByWorth()
	{
		//Initialize index
		for( int i = 1 ; i < getSize()+1 ; ++i )
		{
			good[i-1]->setIndex(i);
		}

		//Quicksort by stock(unstable)
		QSortStock( 0 , getSize()-1 );

		rekeyStock();	//Make stable based on Index

		//Set StockRank
		for( int i = 1 ; i < getSize()+1 ; ++i )
		{
			good[i-1]->setStockRank(i);
		}

		//QuickSort by price(unstable)
		QSortPrice( 0 , getSize()-1 );

		rekeyPrice();	//Make stable based on Index

		//SetPriceRank
		for( int i = 1 ; i < getSize()+1 ; ++i )
		{
			good[i-1]->setPriceRank(i);
		}

		//QuickSort by worth
		QSortWorth( 0 , getSize()-1 );

		rekeyWorth();	//Make stable based on PriceRank
	}
	
	void toSortedFile(string filename) 
	{
		ofstream outFile(filename);
	
		for ( int i = 0 ; i < getSize() ; ++i )
		{
			outFile << good[i]->getBarcode() << endl;
		}
		
		outFile.close();
	}

	//------------------------------------------------------------------------------------/
}; 

#endif
