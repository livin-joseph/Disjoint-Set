#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct Node
{
   int data;
   Node* link;

   Node(int d)
   {
      data = d;
      link = NULL;
   }
}
node;

typedef struct Head
{
   int n;
   node* first;
   node* last;

   Head()
   {
      n = 0;
      first = last = NULL;
   }
}
head;

void makeset(int d,vector<head*>& setHeads,unordered_map<int,int>& repTable)
{
   node* t = new node(d);
   head* h = new head();
   h->n = 1;
   h->first = h->last = t;
   setHeads.push_back(h);
   repTable[d] = d;
}

int find(int d,unordered_map<int,int>& repTable)
{
   return repTable[d];
}

void changeRep(unordered_map<int,int>& repTable,node* ptr,int rep)
{
   while(ptr != NULL)
   {
      repTable[ptr->data] = rep;
      ptr = ptr->link;
   }
}

void Union(int a,int b,vector<head*>& setHeads,unordered_map<int,int>& repTable)
{
   int repA = repTable[a];
   int repB = repTable[b];
   head* A = NULL;
   head* B = NULL;
   int posA, posB;
   for(int i = 0; i < setHeads.size(); i++)
   {
      head* ptr = setHeads[i];
      if(ptr->first->data == repA)
      {
         A = ptr;
         posA = i;
      }
      else if(ptr->first->data == repB)
      {
         B = ptr;
         posB = i;
      }
   }
   if(A->n >= B->n)
   {
      changeRep(repTable,B->first,A->first->data);
      A->last->link = B->first;
      A->last = B->last;
      A->n = A->n + B->n;
      setHeads.erase(setHeads.begin() + posB);
      delete B;
   }
   else if(B->n > A->n)
   {
      changeRep(repTable,A->first,B->first->data);
      B->last->link = A->first;
      B->last = A->last;
      B->n = A->n + B->n;
      setHeads.erase(setHeads.begin() + posA);
      delete A;
   }
}

void deleteElement(int d,vector<head*>& setHeads,unordered_map<int,int>& repTable)
{
   if(repTable[d] == d)
   {
      for(int i = 0; i < setHeads.size(); i++)
      {
         head* ptr = setHeads[i];
         if(ptr->first->data == d)
         {
            node* p = ptr->first;
            if(p->link == NULL)
            {
               //Incomplete
               delete ptr;
            }
         }
      }
   }
}

void display(vector<head*> setHeads)
{
   for(head* ptr : setHeads)
   {
      cout<<"----------"<<endl;
      cout<<"Set size: "<< ptr->n <<endl;
      cout<<"Set representative: "<< ptr->first->data <<endl;
      cout<<"Elements of set"<<endl;
      node* p = ptr->first;
      while(p != NULL)
      {
         cout<< p->data <<endl;
         p = p->link;
      }
      cout<<"----------"<<endl;
   }
}

int main()
{
   int choice;
   vector<head*> setHeads;
   unordered_map<int,int> repTable;
   do
   {
      cout<<"==============="<<endl;
      cout<<"MAIN MENU"<<endl;
      cout<<"1. Make set"<<endl;
      cout<<"2. Find"<<endl;
      cout<<"3. Union"<<endl;
      cout<<"4. Display all sets"<<endl;
      cout<<"0. Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>choice;
      cout<<"==============="<<endl;
      switch(choice)
      {
         case 1:
         {
            int d;
            cout<<"Enter the element: ";
            cin>>d;
            makeset(d,setHeads,repTable);
            cout<<"Makeset is successful"<<endl;
            break;
         }
         case 2:
         {
            int d;
            cout<<"Enter the element: ";
            cin>>d;
            if(find(d,repTable) != 0)
               cout<<"Representative element: "<< find(d,repTable) <<endl;
            else
               cout<<"Element is not found"<<endl;
            break;
         }
         case 3:
         {
            int a,b;
            cout<<"Enter the first element: ";
            cin>>a;
            cout<<"Enter the second element: ";
            cin>>b;
            Union(a,b,setHeads,repTable);
            cout<<"Makeset is successful"<<endl;
            break;
         }
         case 4:
         {
            display(setHeads);
            break;
         }
         case 0:
         {
            break;
         }
         default:
         {
            cout<<"Invalid choice"<<endl;
         }
      }
   }
   while(choice != 0);
}
