/*---------------------------------------------------------
CG1103 G-Lab 5
Discussion Group: C04-2
Poornima D/O Muthukumar	A0077472X
Tran Minh Thy			A0074353H
Chang Shu Heng			A0072437E
----------------------------------------------------------*/
#ifndef _STACK_H_
#define _STACK_H_

using namespace std;

template <typename T>
class myStack
{
		
private:

	struct StackNode
	{
		T jobs;
		StackNode *next;
	};

	StackNode *head;

public:

	myStack()
	{
		head=NULL;
	}
	
	~myStack()
	{
		while( !empty() )
			pop();
	}

	bool empty()
	{
		return (head==NULL);
	}

	void push(const T& newItem )
	{
		StackNode* newPtr=new StackNode;

		newPtr->jobs=newItem;
	
		newPtr->next=head;
		head=newPtr;
	}

	void pop()
	{
		if( empty() )
		{
			return;
		}
		else
		{
			StackNode *cur=head;
			head=head->next;
			delete cur;
			cur=NULL;
		}	
	}

	T& top()
	{
		return head->jobs;
	}

};
#endif
