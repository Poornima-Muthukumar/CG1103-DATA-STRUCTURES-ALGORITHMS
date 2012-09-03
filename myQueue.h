/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/


#ifndef _QUEUE_H_
#define _QUEUE_H_

using namespace std;

template <typename T>
class myQueue
{

private:

	struct QueueNode
	{
		T item;
		QueueNode *next;
	};

	QueueNode *_tail;
	int _size;

public:

	myQueue() 
	{
		_size = 0 ;
		_tail = NULL;
	}

	~myQueue() 
	{
		while( !empty() )
			pop();
	}

	bool empty() { return _size == 0; }
	
	T& front()
	{
		return _tail->next->item;
	}

	void push(const T& newItem)
	{
		QueueNode *newPtr = new QueueNode; 
		newPtr->item = newItem;

		if ( empty() )
		{
			newPtr->next = newPtr;
			_tail = newPtr;
		}

		else
		{
			newPtr->next = _tail->next;
			_tail->next = newPtr;
			_tail = newPtr;
		}

		_size++ ;
	}

	void pop()
	{
		if( empty() )
		{
			return;
		}
		else
		{
			QueueNode *curPtr = _tail->next;
			_tail->next = curPtr->next;

			delete curPtr;
			curPtr = NULL;
			_size-- ;
		}
	}

};

#endif