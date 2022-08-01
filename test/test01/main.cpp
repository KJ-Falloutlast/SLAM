#include <iostream>
using namespace std;
struct Node
{
	Node(int data = 0): data_(data), next_(NULL), pre_(NULL){}
	int data_;
	Node* next_;
	Node* pre_;
};
class CircleLink
{
private:
	Node* head_;
public:
	CircleLink()
	{
		head_ = new Node();				
	}
	~CircleLink()
	{
		Node* p = head_;
		while (p != NULL)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}				
	}
	void InsertTail(int val)
	{
		Node* p = head_;
		while (p->next_ != NULL)
		{
			p = p->next_;
		}		
		Node* node = new Node(val);
		p->next_ = node;
		node->pre_ = p->next_;
	}
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		node->pre_ = head_;
		if (head_->next_ != NULL)
		{
			head_->next_->pre_ = node;
		}
		head_->next_ = node;
	}	
	void InsertPos(int pos, int val)
	{
		
	}
};