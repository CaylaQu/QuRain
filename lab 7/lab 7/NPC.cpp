//#include <iostream>
//#include <sstream>
//
//using namespace std;
//
//class NPC
//{
//private:
//	int HP, Dam;
//
//public:
//
//	NPC(int health, int damage)
//	{
//		HP = health;
//		Dam = damage;
//	}
//
//	int getHP() { return HP; }
//	int getDam() { return Dam; }
//	string toString()
//	{
//		stringstream ss;
//		ss << "==============================" << endl;
//		ss << "The NPC's health stat is: " << HP << endl;
//		ss << "The NPC's Damage stat is : " << Dam << endl;
//		ss << "=============================="  << endl;
//		return ss.str();
//	}
//
//};
//
//class Node
//{
//private:
//
//	
//
//public:
//	NPC* data;
//	Node* next;
//	Node(NPC* item)
//	{
//		data = item;
//		next = nullptr;
//	}
//
//
//};
//
//class Linkedlist
//{
//private:
//	Node* head;
//
//public:
//
//	Linkedlist()
//	{
//		head = nullptr;
//	}
//	void addLast(NPC* stuff)
//	{
//		Node* newNode = new Node(stuff);
//		if(head == NULL)
//		{
//			head = newNode;
//			return;
//		}
//		Node* curr = head;
//		while (curr->next != nullptr)
//		{
//			curr = curr->next;
//		}
//		curr->next = newNode;
//	}
//
//	void showAll()
//	{
//		Node* curr = head;
//		while (curr != nullptr)
//		{
//			cout << curr->data->toString();
//			curr = curr->next;
//		}
//		
//	}
//
//};
//
//int main()
//{
//
//
//	Linkedlist mll;
//	mll.addLast(new NPC(23, 34));
//	NPC* npc1 = new NPC(200, 12);
//	mll.addLast(npc1);
//	mll.showAll();
//
//
//
//
//	return 0;
//}