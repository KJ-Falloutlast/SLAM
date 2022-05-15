#include <iostream>
using namespace std;
template<class T>
class MyArray{
	private:
		T *pAddress;
		int m_Size;
		int m_Capacity;
	public:
		MyArray(int capacity){
			m_Capacity = capacity;
			m_Size = 0;
			pAddress = new T[m_Capacity];
		}
		MyArray(const MyArray &arr){
			m_Capacity = arr.m_Capacity;
			m_Size = arr.m_Size;
			pAddress = new T[m_Capacity];
			for (int i = 0; i < m_Size; i++){
				pAddress[i] = arr.pAddress[i];
			}

		}
		MyArray& operator= (const MyArray &arr){
			if (pAddress != NULL){
				delete[] pAddress;
				pAddress = NULL;
			}
			m_Capacity = arr.m_Capacity;
			m_Size = arr.m_Size;
			pAddress = new T[m_Capacity];
			for (int i = 0; i < m_Size; i++){
				pAddress[i] = arr.pAddress[i];
			}
			return *this;
		}

		~MyArray(){
			if (pAddress != NULL){
				delete[] pAddress;
				pAddress = NULL;		
			}
			
		}

		T& operator[] (int index){
			return pAddress[index];
		}	
		
		void pushBack(const T &obj){
			if (m_Size == m_Capacity){
				return
			}
			pAddress[m_Size] = obj;
			m_Size++;
		}

		void popBack(){
			if (m_Size == 0){
				return;
			}
			m_Size--;
			
		}
	
		int getCapacity(){
			return m_Capacity;			
		}
	
		int getSize(){
			return m_Size;
		}
};