#include <iostream>
using namespace std;
class CircleLink
{
private:
	struct Node{
		Node(int data = 0):data_(data), next_(NULL){}
		int data_;
		Node* next_;
	};
	Node* head_;
	Node* tail_;	
public:
	CircleLink(){
		Node* head_ = new Node();
		tail_ = head_;
		head_->next_ = head_;
	}
	~CircleLink(){
		Node* p = head_->next_;
		while (p != head_){
			head_->next_ = p->next_;
			delete p;
			p = p->next_;
		}
		delete head_;
	}

public:
	void InsertTail(int val){
		Node* node = new Node(val);
		node->next_ = tail_->next_;
		tail_->next_ = node;
		tail_ = node;
	}
	void InsertHead(int val){
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		if (node->next_ == head_){
			tail_ = node;
		}
	}
	void RemoveHead(){
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;
	}
	void RemoveTail(){
		Node* q = head_;
		Node* p = head_->next_;
		while (p != tail_){
			p = p->next_;
			q = q->next_;
		}
		q->next_ = p->next_;
		delete p;
		tail_ = q;	
	}
	void Remove(int val){
		Node* p = head_;
		Node* q = head_->next_;
		while (p != head_){
			if (p->data_ == val){
				q->next_ = p->next_;
				delete p;
				if (p == tail_){
					tail_ = q;
				}
			}
			else{
				p = p->next_;
				q = q->next_;
			}
		}
	}
	void InsertPos(int pos, int val){
		if (pos < 0) return;
		int i = 1;
		Node* p = head_;
		while (p != tail_ && i < pos){
			p = p->next_;
			i++;
		}
		if (pos > i){
			return;
		}
		Node* node = new Node(val);
		if (p == tail_){
			node->next_ = p->next_;
			p->next_ = node;
			tail_ = node;
		}
		else{
			node->next_ = p->next_;
			p->next_ = node;	
		}
	}
};