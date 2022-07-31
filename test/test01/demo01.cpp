#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <algorithm>
using namespace std;
class CircleLink
{
private:
	struct Node{
		Node(int data = 0): data_(data), next_(NULL){}
		Node* next_;
		int data_;
	};
	Node* head_;
	Node* tail_;
public:
	CircleLink(){
		head_ = new Node();
		tail_ = head_;
		tail_->next_ = head_;
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
		if (node->next_ = head_){
			tail_ = node;
		}
	}
	void RemoveTail(){
		Node* q = head_;
		Node* p = head_->next_;
		while (p != tail_){
			q = q->next_;
			p = p->next_;
		}
		q->next_ = p->next_;
		delete p;
		tail_ = q;
	}
	void RemoveHead(){
		Node* p = head_->next_;
		head_->next_ = p->next_;
		delete p;	
	}
	void Remove(int val){
		Node* q = head_;
		Node* p = head_->next_;
		while (p != head_){
			if (p->data_ == val){
				q->next_ = p->next_;
				delete p;
				if (q->next_ == head_){
					tail_ = q;
				}
			}
			else{
				q = q->next_;
				p = p->next_;
			}
		}
	}
};

struct Node{
	Node(int data = 0): data_(data), next_(NULL){}
	Node* next_;
	int data_;
};


void Joseph(Node* head, int k, int m){
	Node* p = head;
	Node* q = head;
	for (int i = 1; i < k; i++){
		q = p;
		p = p->next_;
	}
	while (true){
		for (int i = 1; i < m; i++){
			q = p;
			p = p->next_;
		}
		cout << p->data_ << " ";
		if (p == q){
			delete p;
			break;
		}
		q->next_ = p->next_;
		delete p;
		p = q->next_;
	}
}