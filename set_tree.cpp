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
      parent = this;
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
   if(t == NULL)
      return 0;
   while(t->parent != t)
      t = t->parent;
   return t->data;
}

void Union(int a,int b,unordered_map<int,node*>& addressTable)
{
   node* A = addressTable[a];
   node* B = addressTable[b];
   while(A->parent != A || B->parent != B)
   {
      A = A->parent;
      B = B->parent;
   }
   if(A->rank >= B->rank)
   {
      B->parent = A;
      if(A->rank == B->rank)
         A->rank = A->rank + 1;
   }
   else
   {
      A->parent = B;
   }
}

void display(unordered_map<int,node*> addressTable)
{
   vector<int> v;
   for(auto i : addressTable)
   {
      if(i.second->parent == i.second)
         v.push_back(i.first);
   }
   for(int j : v)
   {
      cout<<"----------"<<endl;
      cout<< j <<endl;
      for(auto k : addressTable)
      {
         if(find(k.first,addressTable) == j && k.first != j)
            cout<< k.first <<endl;
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
            Union(a,b,addressTable);
            cout<<"Union is successful"<<endl;
            break;
         }
         case 4:
         {
            display(addressTable);
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
