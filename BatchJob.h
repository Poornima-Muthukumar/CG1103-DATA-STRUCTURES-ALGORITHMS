/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/
#ifndef _BATCH_JOB_
#define _BATCH_JOB_

#include <iostream>
#include <string>

using namespace std;

class BatchJob
{
private:

	string _user;
	int _jobtype;
	string _name;
	string _category;
	string _barcode;
	double _price;
	string _manufacturer;
	int _QtytoUpdate;
	string _expiry;

public:

	BatchJob() {}
	~BatchJob() {}

	/*********************** ACCESSORS *****************/
	string getUser()			{ return _user;			}
	int getJobtype()			{ return _jobtype;		}
	string getName()			{ return _name;			}
	string getCategory()		{ return _category;		}
	string getBarcode()			{ return _barcode;		}
	double getPrice()			{ return _price;		}
	string getManufacturer()	{ return _manufacturer;	}
	int getQtytoUpdate()		{ return _QtytoUpdate;	}
	string getExpiry()			{ return _expiry;		}
	/***************************************************/

	/*********************** MUTATORS **********************/
	void setUser(string a)			{  _user		= a;	}
	void setJobtype(int a)			{  _jobtype		= a;	}
	void setName(string a)			{  _name		= a;	}
	void setCategory(string a)		{  _category	= a;	}
	void setBarcode(string a)		{  _barcode		= a;	}
	void setPrice(double a)			{  _price		= a;	}
	void setManufacturer(string a)	{  _manufacturer= a;	}
	void setQtytoUpdate(int a)		{  _QtytoUpdate	= a;	}
	void setExpiry(string a)		{  _expiry		= a;	}
	/*******************************************************/

};
#endif