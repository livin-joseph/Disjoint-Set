#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct Node
{
   int data;
   int rank;
   Node* parent;

   Node(int d)
   {
      data = d;
      rank = 0;
      parent = NULL;
   }
}
node;

void makeset(int d,unordered_map<int,node*>& addressTable)
{
   node* t = new node(d);
   addressTable[d] = t;
}

int find(int d,unordered_map<int,node*>& addressTable)
{
   node* t = addressTable[d];
   while(t->parent != t)
      t = t->parent;
   return t->data;
}

void Union(int a,int b,unordered_map<int,node*>& addressTable)
{
   int repA = addressTable[a];
   int repB = addressTable[b];
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
      changeRep(addressTable,B->first,A->first->data);
      A->last->link = B->first;
      A->last = B->last;
      A->n = A->n + B->n;
      setHeads.erase(setHeads.begin() + posB);
      delete B;
   }
   else if(B->n > A->n)
   {
      changeRep(addressTable,A->first,B->first->data);
      B->last->link = A->first;
      B->last = A->last;
      B->n = A->n + B->n;
      setHeads.erase(setHeads.begin() + posA);
      delete A;
   }
}

void deleteElement(int d,unordered_map<int,node*>& addressTable)
{
   if(addressTable[d] == d)
   {
      for(int i = 0; i < setHeads.size(); i++)
      {
         head* ptr = setHeads[i];
         if(ptr->first->data == d)
         {
            node* p = ptr->first;
            if(p->link == NULL)
            {
               setHeads.erase(setHeads.begin() + i);
               delete p;
               delete ptr;
            }
            else
            {
               setHeads[i]->first = p->link;
               setHeads[i]->n = setHeads[i]->n - 1;
               addressTable[p->data] = 0;
               changeRep(addressTable,p->link,p->link->data);
            }
         }
      }
   }
   else
   {
      int rep = addressTable[d];
      for(int i = 0; i < setHeads.size(); i++)
      {
         head* ptr = setHeads[i];
         if(ptr->first->data == rep)
         {
            node* p = ptr->first;
            while(p->link->data != d)
            {
               p = p->link;
            }
            node* temp = p->link;
            p->link = p->link->link;
            delete temp;
            setHeads[i]->n = setHeads[i]->n - 1;
         }
      }
   }
}

void display(unordered_map<int,node*> addressTable)
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
   unordered_map<int,node*> addressTable;
   do
   {
      cout<<"==============="<<endl;
      cout<<"MAIN MENU"<<endl;
      cout<<"1. Make set"<<endl;
      cout<<"2. Find"<<endl;
      cout<<"3. Union"<<endl;
      cout<<"4. Delete an element"<<endl;
      cout<<"5. Display all sets"<<endl;
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
            makeset(d,addressTable);
            cout<<"Makeset is successful"<<endl;
            break;
         }
         case 2:
         {
            int d;
            cout<<"Enter the element: ";
            cin>>d;
            if(find(d,addressTable) != 0)
               cout<<"Representative element: "<< find(d,addressTable) <<endl;
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
            Union(a,b,setHeads,addressTable);
            cout<<"Makeset is successful"<<endl;
            break;
         }
         case 4:
         {
            int d;
            cout<<"Enter the element to be deleted: ";
            cin>>d;
            if(addressTable[d] != 0)
            {
               deleteElement(d,setHeads,addressTable);
               cout<<"Deletion is successful"<<endl;
            }
            else
               cout<<"Element not found"<<endl;
            break;
         }
         case 5:
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
   return 0;
}
