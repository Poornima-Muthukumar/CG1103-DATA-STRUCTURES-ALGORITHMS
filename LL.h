/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _LL_H_
#define _LL_H_

#include "Storage.h"
#include <string>
#include <sstream>

template <typename T>
class LL : public Storage<T>
{
private:

	struct ListNode
	{	
		T* item;
		ListNode *next;

	};

	ListNode* _head;
	ListNode* _tail;

	//Return pointer to where index is found.
	ListNode* traverseTo( int index) 
	{
		ListNode * curNode;
		curNode=_head;
		//Start from first node

		for ( int i = 0 ; i < index  ; ++i )
		{
			curNode = curNode->next;	//Search forward
		}

		return curNode;
	}

	//Function returns kth digit of a number
	//Returns 0 if k exceeds number size
	//Aids radix sort
	int digit( int number , int k )
	{
		int digit = 0 ;

		for( int i = 1 ; i <= k ; ++i )
		{
			digit = number%10 ;
			number = number/10;
		}

		return(digit);
	}

	//Finds number of digits of the largest stock quantity in the list.
	//Aids radix sort
	int large_dig_stock( ListNode *p )
	{
		int large = 0;
		int ndig = 0;

		while( p != NULL )
		{
			int Candidate = p->item->getStock();

			if( Candidate > large )
			{
				large = Candidate;	
			}

			p = p->next;
		}

		while( large != 0 )
		{
			ndig++;
			large = large/10;
		}

		return (ndig);
	}

	//Finds number of digits of the largest index in the list.
	//Aids radix sort
	int large_dig_index( ListNode *p )
	{
		int large = 0;
		int ndig = 0;

		while( p != NULL )
		{
			int Candidate = p->item->getIndex();

			if( Candidate > large )
			{
				large = Candidate;	
			}

			p = p->next;
		}

		while( large != 0 )
		{
			ndig++;
			large = large/10;
		}

		return (ndig);
	}

	//Finds number of digits of the largest worthRank in the list.
	//Aids radix sort
	int large_dig_worth( ListNode *p )
	{
		int large = 0;
		int ndig = 0;

		while( p != NULL )
		{
			int Candidate = p->item->getWorthRank();

			if( Candidate > large )
			{
				large = Candidate;	
			}

			p = p->next;
		}

		while( large != 0 )
		{
			ndig++;
			large = large/10;
		}

		return (ndig);
	}

	//Radix sort Stock
	void radix_sort_stock()
	{
		int maxdig = 0;
		int mindig = 0;
		int dig = 0;

		ListNode *p = _head , *rear[10] , *front[10];

		int least_sig = 1;
		int most_sig = large_dig_stock(p);

		//For every one pass,
		for( int k = least_sig ; k <= most_sig ; ++k )
		{
			/***Step 1: Reset every bucket to NULL******/
			for( int i = 0 ; i <= 9 ; ++i )
			{
				rear[i] = NULL;
				front[i] = NULL;
			}
			maxdig = 0 ;
			mindig = 9 ;
			p = _head;
			/*******************************************/

			/****************** Step 2: Inserting items into buckets *********/
			while( p != NULL )
			{
				dig = digit( p->item->getStock() , k );

				if( dig > maxdig ) { maxdig = dig; }
				if( dig < mindig ) { mindig = dig; }

				//Start linking to the 10 buckets

				if( front[dig] == NULL )	//Case: Linking for the first time
				{
					front[dig] = p;
				}
				else
				{
					rear[dig]->next = p;
				}

				rear[dig] = p;
				p = p->next;

			}//while( p! = NULL )
			/******************************************************************/

			/***************** Step 3: Merge the buckets together *************/

			_head = front[mindig];	//Our New appointed head!!
			_tail = rear[maxdig];

			for( int i = mindig ; i < maxdig ; ++i )
			{
				if( rear[i+1] != NULL )
				{
					rear[i]->next = front[i+1];
				}
				else
				{
					rear[i+1] = rear[i];
				}
			}
			rear[maxdig]->next = NULL;
			/******************************************************************/

		}//for( int k = least_sig ; k <= most_sig ; ++k )
	}//End Radix Stock


	//Radix sort Index
	void radix_sort_index()
	{
		int maxdig = 0;
		int mindig = 0;
		int dig = 0;

		ListNode *p = _head , *rear[10] , *front[10];

		int least_sig = 1;
		int most_sig = large_dig_index(p);

		//For every one pass,
		for( int k = least_sig ; k <= most_sig ; ++k )
		{
			/***Step 1: Reset every bucket to NULL******/
			for( int i = 0 ; i <= 9 ; ++i )
			{
				rear[i] = NULL;
				front[i] = NULL;
			}
			maxdig = 0 ;
			mindig = 9 ;
			p = _head;
			/*******************************************/

			/****************** Step 2: Inserting items into buckets *********/
			while( p != NULL )
			{
				dig = digit( p->item->getIndex() , k );

				if( dig > maxdig ) { maxdig = dig; }
				if( dig < mindig ) { mindig = dig; }

				//Start linking to the 10 buckets

				if( front[dig] == NULL )	//Case: Linking for the first time
				{
					front[dig] = p;
				}
				else
				{
					rear[dig]->next = p;
				}

				rear[dig] = p;
				p = p->next;

			}//while( p! = NULL )
			/******************************************************************/

			/***************** Step 3: Merge the buckets together *************/

			_head = front[mindig];	//Our New appointed head!!
			_tail = rear[maxdig];

			for( int i = mindig ; i < maxdig ; ++i )
			{
				if( rear[i+1] != NULL )
				{
					rear[i]->next = front[i+1];
				}
				else
				{
					rear[i+1] = rear[i];
				}
			}
			rear[maxdig]->next = NULL;
			/******************************************************************/

		}//for( int k = least_sig ; k <= most_sig ; ++k )
	}//End Radix Index


	//Radix sort worth
	void radix_sort_worth()
	{
		int maxdig = 0;
		int mindig = 0;
		int dig = 0;

		ListNode *p = _head , *rear[10] , *front[10];

		int least_sig = 1;
		int most_sig = large_dig_worth(p);

		//For every one pass,
		for( int k = least_sig ; k <= most_sig ; ++k )
		{
			/***Step 1: Reset every bucket to NULL******/
			for( int i = 0 ; i <= 9 ; ++i )
			{
				rear[i] = NULL;
				front[i] = NULL;
			}
			maxdig = 0 ;
			mindig = 9 ;
			p = _head;
			/*******************************************/

			/****************** Step 2: Inserting items into buckets *********/
			while( p != NULL )
			{
				dig = digit( p->item->getWorthRank() , k );

				if( dig > maxdig ) { maxdig = dig; }
				if( dig < mindig ) { mindig = dig; }

				//Start linking to the 10 buckets

				if( front[dig] == NULL )	//Case: Linking for the first time
				{
					front[dig] = p;
				}
				else
				{
					rear[dig]->next = p;
				}

				rear[dig] = p;
				p = p->next;

			}//while( p! = NULL )
			/******************************************************************/

			/***************** Step 3: Merge the buckets together *************/

			_head = front[mindig];	//Our New appointed head!!
			_tail = rear[maxdig];

			for( int i = mindig ; i < maxdig ; ++i )
			{
				if( rear[i+1] != NULL )
				{
					rear[i]->next = front[i+1];
				}
				else
				{
					rear[i+1] = rear[i];
				}
			}
			rear[maxdig]->next = NULL;
			/******************************************************************/

		}//for( int k = least_sig ; k <= most_sig ; ++k )
	}//End Radix worth

	//Merge sort by price
	ListNode* merge_price( ListNode *L_head , int size )
	{
		if(size <= 1)
		{
			return L_head;
		}

		int middle = size/2;
		int l,r;
		if( (size%2)==1 )
		{
			l=middle+1;
			r=middle;
		}
		else
		{
			l=middle;
			r=middle;
		}

		ListNode *R_head = L_head;

		//Finding head of right list
		for( int i = 0 ; i < l ; ++i )
		{
			R_head = R_head->next;
		}

		L_head = merge_price( L_head , l );	//Merge left list
		R_head = merge_price( R_head , r );	//Merge right list

		//merge
		return merge( L_head , R_head , l , r );

	}

	//Aids merge sort by price.
	ListNode* merge(ListNode *left , ListNode *right , int l_size , int r_size)
	{
		ListNode *cur_left = left;		//Use for traversing left list
		ListNode *cur_right = right;	//Use for traversing right list

		ListNode *head = NULL;

		//if smaller item is on the right..
		if( left->item->getPrice() > right->item->getPrice() )
		{
			head = right;
			cur_right = cur_right->next;
			r_size-- ;
		}
		else
		{
			head = left;
			cur_left = cur_left->next;
			l_size--;
		}

		ListNode *cur = head; //Indicates where I am current pointing to

		while( ! (l_size == 0 || r_size == 0 ) )
		{
			//If smaller item is on the left
			if( cur_left->item->getPrice() <= cur_right->item->getPrice() )
			{
				cur->next = cur_left;
				cur_left = cur_left->next;
				cur = cur->next;
				l_size--;
			}
			else
			{
				cur->next = cur_right;
				cur_right = cur_right->next;
				cur = cur->next;
				r_size--;
			}
		}

		if( l_size == 0 )
		{
			cur->next = cur_right;

			for( int i = 0 ; i < r_size ; ++i )
			{
				cur = cur->next;
			}
			cur->next = NULL;
			_tail = cur;
		}
		else
		{
			cur->next = cur_left;

			for( int i = 0 ; i < l_size ; ++i )
			{
				cur = cur->next;
			}
			cur->next = NULL;
			_tail = cur;
		}

		return head;
	}

public:

	LL() : Storage<T>() 
	{ 
		_head = NULL;
		_tail = NULL;
	}

	~LL()
	{
		while ( !isEmpty() )
			delItem( 1 );
	}

	int getStockAtIndex ( int index )
	{
		return traverseTo(index)->item->getStock();
	}

	//Return index to where barcode is found
	int IndexOfBarcode( string barcode)
	{
		ListNode *cur = _head;

		for( int i = 0 ; i < getSize() ; ++i )
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
		ListNode* cur = _head;

		ofstream outFile;
		outFile.open(filename);

		outFile << getSize() << endl << endl;	//number of products

		while (cur != NULL)
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


		//If it is an empty list
		if ( isEmpty() )
		{
			_head = newNode;
			_tail = newNode;
		}

		else 
		{
			//Links newNode to List
			_tail->next = newNode;
            _tail = newNode;
		}

		_size++;
		return true;
	}

	bool delItem(int index)
	{

		ListNode *cur,*prev;
		if ( (index < 1) || (index > getSize()) )
		{
			return false;
		} 

		if ( index == 1 )					//Deleting at head
		{
			cur = _head;
			_head=_head->next;
		}

		else
		{
			prev = traverseTo(index - 1);	
			cur=prev->next;					//Item to delete
			prev->next=cur->next;			//Links prev item to next item

			if ( index == getSize() )
			{
				_tail = prev;				//Deleting at tail: Need to update new tail
			}
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

	//--------------------------------------------------------------------------------/
	/***********************************Statistics************************************/
	//--------------------------------------------------------------------------------/

	string topXitem(int x) 
	{
		double*revenue=new double[getSize()];
		double*revenue2=new double[x];
	
		ostringstream os;

		bool flag=false;
		double max;
		ListNode*ptr;
		int c=0;
		for(ptr=_head;ptr!=NULL;ptr=ptr->next)
		{
			revenue[c++]=ptr->item->Revenue();
		}
		for(int j=0;j<x;j++)
		{
			max=-1;
			for(int i=0;i<c;i++)
			{
				if(revenue[i]>max)
				{
					flag=true;
					if(j!=0)//for case when there is no max,
							//for the first max to be added to revenue2
					{
					for(int k=0;k<j;k++)
						if(revenue[i]==revenue2[k])
							flag=false;
					}
					if(flag)
						max=revenue[i];
				}
			}
			revenue2[j]=max;
		}
		for(int i=0;i<x;i++)
		{
			for(ptr=_head;ptr!=NULL;ptr=ptr->next)
			{
				if(revenue2[i]==ptr->item->Revenue())
				{

					os << ptr->item->getName() <<endl; 
				}
			}
		}

		return os.str();
	}

	string topCategoryItem(string category)  
	{
		ListNode* ptr;
		ostringstream os;

		double temp_sales = 0;
		double max = 0 ;

		for( ptr = _head ; ptr!=NULL ; ptr=ptr->next)
		{
			if( ptr->item->getCat() == category )
			{
				temp_sales = ptr->item->Revenue();

				if( temp_sales >max)
					max= temp_sales ;
			}
		}

		ptr=_head; //skim  through the list again
		do
		{
			if( ptr->item->getCat() == category )
			{
				double currnum = ptr->item->Revenue();

				if( currnum == max )
				{
					os << ptr->item->toString() <<endl; 
				}
			}

			ptr = ptr ->next;
		}while(ptr!=NULL);
			
		return os.str(); 
	}

	string topManufacturer()
	{
		ListNode* ptr=_head;
		string*manufacturer=new string[getSize()];
		double *Mrevenue=new double [getSize()];
		
		double maxrevenue=0;
		ostringstream os;
		bool check;
		string manu;
		double rev;
		int c=0;
		int d=0;
		manufacturer[c++]=ptr->item->getManufac();
		Mrevenue[d++]=ptr->item->Revenue();
		for(ptr=_head->next;ptr!=NULL;ptr=ptr->next)
		{
			check =false;
			manu=ptr->item->getManufac();
			rev=ptr->item->Revenue();
			for(int i=0;i<c;i++)
			{
				if(manufacturer[i]==manu)
				{
					Mrevenue[i]+=rev;
					check=true;

				}

			}
			if(check!=true)
			{
				manufacturer[c++]=manu;
				Mrevenue[d++]=rev;
			}


		}

		for(int j=0;j<c;j++)
		{
			if(Mrevenue[j]>maxrevenue)
				maxrevenue=Mrevenue[j];
		}


		for(int j=0;j<c;j++)
		{
			if(Mrevenue[j]==maxrevenue)
				os<<manufacturer[j]<<endl;
		}

		return os.str();
	}

	//--------------------------------------------------------------------------------/
	/************************************Searching************************************/
	//--------------------------------------------------------------------------------/

	string searchByName( string name ) 
	{
		ListNode *cur = _head;
		bool found = false;

		ostringstream oss;

		do
		{
			if ( cur->item->getName() == name )
			{
				oss << cur->item->toString() << "\n";
				found = true;
			}

			cur = cur->next;

		}while( cur != NULL );

		return oss.str();
	}

	string searchByBarcode( string barcode ) 
	{
		ListNode *cur = _head;
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

		}while( cur != NULL && !found );

		return oss.str();
	}

	string searchByCategory(string category) 
	{
		ListNode *cur = _head;
		bool found = false;

		ostringstream oss;

		do 
		{
			if ( cur->item->getCat() == category)
			{
				oss << cur->item->toString() << "\n";
				found = true;
			}

			cur = cur->next;

		}while (cur != NULL );

		return oss.str();
	}

	string searchByManufacturer(string manufacturer) 
	{
		ListNode *cur = _head;
		bool found = false;

		ostringstream oss;

		do 
		{
			if ( cur->item->getManufac() == manufacturer )
			{
				oss << cur->item->toString() << "\n";
				found = true;
			}

			cur = cur->next;

		}while (cur != NULL);

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
	/******************************** LAB 5 ADDITIONS: ***********************************/
	//------------------------------------------------------------------------------------/

	void SortByWorth() 
	{
		//Initialize index
		ListNode *cur = _head;
		int index = 1;
		while( cur != NULL )
		{
			cur->item->setIndex(index++);
			cur = cur->next;
		}

		//Sort by stock
		radix_sort_stock();

		//Set StockRank
		cur = _head;
		index = 1;
		while( cur != NULL )
		{
			cur->item->setStockRank(index++);
			cur = cur->next;
		}

		//Sort by index
		radix_sort_index();

		//Sort by price
		_head = merge_price( _head , getSize() );

		//Set PriceRank
		cur = _head;
		index = 1;
		while( cur != NULL )
		{
			cur->item->setPriceRank(index++);
			cur = cur->next;
		}

		//Sort by Worth
		radix_sort_worth();
	}
	
	void toSortedFile(string filename)
	{
		ofstream outFile(filename);

		ListNode *cur = _head;
	
		while( cur != NULL )
		{
			outFile << cur->item->getBarcode() << "\n";
			cur = cur->next;
		}
		
		outFile.close();
	}
	//------------------------------------------------------------------------------------/
};

#endif
