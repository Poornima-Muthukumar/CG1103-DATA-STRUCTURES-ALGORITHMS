/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/

#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>
#include <iostream>
using namespace std;

class Timer
{
private:

    clock_t _startTime;
    clock_t _endTime;

public:

    Timer()
	{
		_startTime = clock();
	}

    ~Timer() 
	{
	}

    void print()
	{
        _endTime = clock(); 
        cout << "Elapsed time: ";
        cout << ((double) (_endTime - _startTime))/CLOCKS_PER_SEC * 1000.0 <<"ms"<<endl;
        system("pause");
    }
};

#endif