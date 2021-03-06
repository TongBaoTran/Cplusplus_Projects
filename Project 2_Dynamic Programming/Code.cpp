
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;



//===================TASK 1: DEFINE A POINT STRUCTURE========================================================
struct point
{
              string pointName;
              float  x;
              float  y;
              float d;
              struct point *next;
};

point *head=nullptr;

//Function prototype
float Distance(point *p1, point *p2);
point *sortedList(point **head, point *newpoint);
point* NearestPoint(point  **head, point *thispoint);
void Outputting(point** head);
void deleteAllPoints(point **head);

//===================TASK 7: MAIN FUNCTION==================================================================
int main()
{
 //Input to the list
  string pname="";
  float x,y;
  while(pname.compare("end")!=0)
      {
      //Create new point
      cout << "string describing obstacle (\"end\" for end of input): ";
      cin>>pname;
      if (pname.compare("end")==0) break;
      cout<<"x and y coordinate: ";
      cin>>x>>y;
      point *newpoint=new point;
      newpoint->pointName=pname;
      newpoint->x=x;
      newpoint->y=y;
      newpoint->d=sqrt(x*x+y*y);
      //adding new point to the list and sort the list
      head = sortedList(&head,newpoint);
       }

  //Outputting the list
       Outputting(&head);

  //Delete the list
       deleteAllPoints(&head);
  return 0;
}


//===================TASK 2. CALCULATE THE EUCLIDIAN DISTANCE BETWEEN TWO POINTS============================
float Distance(point *p1, point *p2){
return sqrt((p1->x-p2->x)*(p1->x-p2->x)+(p1->y-p2->y)*(p1->y-p2->y));
}

//===================TASK 3: FIND THE NEAREST POINT OF A SPECIFIC POINT=====================================
point* NearestPoint(point **head, point *thispoint){
   point* temp=*head;
   point* nearestPoint;
   float min;
   int countlist=0;
  //find nearest distance
       if (thispoint==*head){
            min=Distance((*head)->next,thispoint);
            nearestPoint=(*head)->next;
       }
       else {
              min=Distance(*head,thispoint);
              nearestPoint=*head;
       }


       while (temp!=nullptr)
          {
              countlist+=1;
                if (Distance(temp,thispoint)>0 and Distance(temp,thispoint)<min)
                 {
                  min=Distance(temp,thispoint);
                  nearestPoint=temp;
                 }
              temp=temp->next;
          }
   if (countlist==1)  return nullptr;
   else return nearestPoint;
}

//===================TASK 4: INSERT NEW POINT AND SORT THE LIST OF POINTS===================================
point *sortedList(point **head, point *newpoint){
//insert new point to beginning of the list
     newpoint->next = *head;
    *head = newpoint;
//Sort the list
    int swapped;
    point* current;
    point* next = nullptr;
    do
    {
        swapped = 0;
        current = *head;
        while (current->next != next)
        {
            if (current->d > current->next->d)
            {
                 //Swap name
                  string tempname = current->pointName;
                  current->pointName = current->next->pointName;
                  current->next->pointName = tempname;
                 //Swap coordinate x,y
                  float tempx = current->x;
                  current->x = current->next->x;
                  current->next->x = tempx;

                  float tempy = current->y;
                  current->y = current->next->y;
                  current->next->y = tempy;

                 //Swap distance
                  float temp = current->d;
                  current->d = current->next->d;
                  current->next->d = temp;
                swapped = 1;
            }
            current = current->next;
        }
        next = current;
    }
    while (swapped);
 return *head;
}

//===================TASK 5: OUTPUT THE LIST OF POINTS======================================================
void Outputting(point** head){
 point* current = *head;
 while (current != nullptr)
   {
     cout<<fixed<<setprecision(2)<<"obstacle "<<current->pointName;
     cout<<": ("<<fixed<<setprecision(2)<<setw(6)<<current->x<<", "<<setw(6)<<current->y;
     cout<<"), distance:"<<setw(6)<<current->d<<"m";
     cout<<", nearest to this: "<<NearestPoint(head,current)->pointName<<endl;
     current = current->next;
   }
}

//===================TASK 6: DELETE ALL POINTS IN THE LIST==================================================
void deleteAllPoints(point** head)
{
      point* current = *head;
      point* next;
      cout<<"delete: ";
      while (current != nullptr)
          {
              cout<<current->pointName<<" ";
              next = current->next;
              delete current;
              current = next;
          }
     *head = nullptr;
}

