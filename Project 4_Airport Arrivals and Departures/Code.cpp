

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


// *********************** TASK 1: Enumeration Time Zones ***************************

enum struct TimeZone
{  ACT, CET, CST, EST, GMT, MSK, PST, UTC};



// *********************** TASK 2: Enumeration Arrival, Departure *******************

enum struct ArrivalDeparture
{  arrival, departure};



// *********************** TASK 3: Class LocalTime **********************************

class LocalTime
{
  private:
              int minutes;
              TimeZone TZ;
  public:
              //Standard Constructor
              LocalTime(){
              minutes=-1;
              TZ=TimeZone::CET;
              }

              //Overloaded Constructor
              LocalTime(int hour, int mins,TimeZone TZ){
                           TZ=TimeZone::CET;
                           set_time(hour, mins);
              }

              //Method set_time
              int set_time(int hour, int mins){
                 if ((hour>=0) && (hour<=24) && (mins>=0) && (mins<=60)){
                            return minutes=hour*60+mins;
                   }
                 else{
                            cout<<hour<<":"<<mins<<" !!! The time entered is not correct!!!"<<endl<<endl;
                            return minutes = -1;
                     }
                   };

             //Method get_hour
             int get_hour(){
                return minutes/60 ;
             };

             //Method get_minute
              int get_minute(){
                return  minutes%60 ;
             };

             //Method is_valid
             bool is_valid(){
               if (minutes<0) return false;
               else return true;
             }

             friend ostream& operator<<(ostream& out, LocalTime& lt);
};



// ********************** TASK 4: Output LocalTime ********************************

ostream& operator<<(ostream& out, LocalTime& lt)
{
   out<<setfill('0')<<right<<setw(2)<<lt.get_hour()<<":"<<setfill('0')<<right<<setw(2)<<lt.get_minute();
   return out;
}



// ********************* TASK 5: Class Flight (Only Prototypes) ********************

class Flight{
private:
         ArrivalDeparture arrivalOrDeparture;
         string  code, destination, gate, checkIn, comment;
         LocalTime expected;
public:
         //Prototype for constructor
         Flight(ArrivalDeparture iarrivalOrDeparture, string icode, string idestination, string igate, string icheckIn);

         //Prototype for destructor
         ~Flight();

          //Prototypes for Methods
          void set_expected(LocalTime iexpected);
          void set_comment(string icomment);

          LocalTime get_expected();
          string get_code();
          string get_destination();
          string get_gate();
          string get_checkIn();
          string get_comment();

          bool is_arrival();
          bool is_departure();

          void print(LocalTime ischeduled);
};


// ********************** TASK 6: Details for constructor, destructor, methods for class Flight ************************

//Flight constructor
Flight::Flight(ArrivalDeparture iarrivalOrDeparture, string icode, string idestination, string igate, string icheckIn):
                 arrivalOrDeparture(iarrivalOrDeparture),
                 code(icode),
                 destination(idestination),
                 gate(igate),
                 checkIn(icheckIn),
                 comment(" ")
              {}

//Flight destructor
Flight::~Flight()
{
     cout<<get_code();
}

//Methods/Functions
string Flight::get_code()
              {
              return code;
              };

string Flight::get_destination()
              {
              return destination;
              };

string Flight::get_gate()
              {
              return gate;
              };

string Flight::get_checkIn()
              {
              return checkIn;
              };

//Set comments and get comments
void Flight::set_comment(string icomment)
{
              comment=icomment;
};
string Flight::get_comment()
              {
              return comment;
              };

 //Set scheduled time and get scheduled time
void Flight::set_expected(LocalTime iexpected)
{
              expected=iexpected;
};
LocalTime Flight::get_expected()
              {
              return expected;
              };


//Type of flight: arrival or departure
bool Flight::is_arrival()
{
              if (arrivalOrDeparture==ArrivalDeparture::arrival) return true;
              else return false;
}
bool Flight::is_departure()
{
              if (arrivalOrDeparture==ArrivalDeparture::departure) return true;
              else return false;
}

//Function to print flight
void Flight::print(LocalTime ischeduled){
              cout<<setfill(' ')<<setw(9)<<left<<get_code();
              cout<<setfill(' ')<<setw(20)<<left<<get_destination();
              cout<<setfill(' ')<<setw(4)<<" "<<left<<ischeduled<<" ";
              LocalTime temp=this->get_expected();
              if (temp.is_valid()){
                  cout<<setfill(' ')<<setw(5)<<left<<temp<<setfill(' ')<<setw(5)<<left<<"";
              }
              else{
                    cout<<setfill(' ')<<setw(5)<<left<<" "<<setfill(' ')<<setw(5)<<left<<"";
                  }
              cout<<setfill(' ')<<setw(5)<<left<<get_gate();
              cout<<setfill(' ')<<setw(10)<<left<<get_checkIn();
              cout<<setfill(' ')<<setw(15)<<left<<get_comment()<<endl;
}





// ************************* TASK 7: CLASS AIRPORT ****************************************************

class Airport{
private:
      string name;
      Flight *slot[24][60]= { { nullptr} }; //every combination of row, column will be a flight corresponding to that hour/minute
public:
       Airport(string iname):
              name(iname)
              {}

       ~Airport()
        {
                            for (int i=0; i<24;i++)
                               {
                                  for (int j=0; j<60; j++)
                                     {
                                       if  (slot[i][j] != nullptr)
                                          {
                                               cout<<"flight ";
                                               delete slot[i][j];
                                               cout<<" deleted"<<endl;
                                         }
                                    }
                              }
        }

        void schedule(LocalTime lt1,  Flight *thisflight)
        {
                      int x=lt1.get_hour();
                      int y=lt1.get_minute();
                      slot[x-1][y-1]=thisflight;
        }

        void comment(LocalTime lt1,  string thiscomment)
        {
                      int x=lt1.get_hour();
                      int y=lt1.get_minute();
                      slot[x-1][y-1]->set_comment(thiscomment);
        }

        void delay(LocalTime lt1, LocalTime lt2 )
        {
                      int x=lt1.get_hour();
                      int y=lt1.get_minute();
                      slot[x-1][y-1]->set_expected(lt2);

        }

      void print(ArrivalDeparture ad)
       {
                     if (ad==ArrivalDeparture::arrival)
                      {
                            cout<<setw(9)<<left<<"Flight";
                            cout<<setw(20)<<left<<"From";
                            cout<<setw(10)<<left<<"Scheduled";
                            cout<<setw(10)<<left<<"Expected";
                            cout<<setw(5)<<left<<"Gate";
                            cout<<setw(10)<<left<<"Check-in";
                            cout<<setw(15)<<left<<"Comments"<<endl;
                            for (int i=0; i<24;i++)
                               {
                                  for (int j=0; j<60; j++)
                                     {
                                       if  ((slot[i][j] != nullptr) &&(slot[i][j]->is_arrival()))
                                          {
                                               LocalTime temp(i+1,j+1,TimeZone::CET);
                                               slot[i][j]->print(temp);
                                         }
                                    }
                              }
                      }

                     if (ad==ArrivalDeparture::departure)
                      {
                            cout<<setw(9)<<left<<"Flight";
                            cout<<setw(20)<<left<<"To";
                            cout<<setw(10)<<left<<"Scheduled";
                            cout<<setw(10)<<left<<"Expected";
                            cout<<setw(5)<<left<<"Gate";
                            cout<<setw(10)<<left<<"Check-in";
                            cout<<setw(15)<<left<<"Comments"<<endl;
                            for (int i=0; i<24;i++)
                               {
                                  for (int j=0; j<60; j++)
                                     {
                                       if  ((slot[i][j] != nullptr) && (slot[i][j]->is_departure()))
                                          {
                                               LocalTime temp(i+1,j+1,TimeZone::CET);
                                               slot[i][j]->print(temp);
                                         }
                                    }
                              }
                      }
       }
};


// *********************************** TASK 8: Main *****************************************
int main()
{
    //Set times for flights
    LocalTime  LH2010(12,40,TimeZone::CET);
    LocalTime  LH2010_delayed(13,5,TimeZone::CET);
    LocalTime  EW9347(14,50,TimeZone::CET);
    LocalTime  AF1307(9,10,TimeZone::CET);
    LocalTime  SU2537(10,40,TimeZone::CET);
    LocalTime  EW9466(11,15,TimeZone::CET);
    LocalTime  LH2011(13,25,TimeZone::CET);
    LocalTime  XQ959(14,55,TimeZone::CET);
    LocalTime  XQ959_delayed(15,20,TimeZone::CET);

    //Choose an airport
    Airport *airport=new Airport("DUSSELDORF AIRPORT");

    //Setting Flight "LH 2010"
    Flight *Flight_LH2010 = new Flight(ArrivalDeparture::arrival, "LH 2010 ", "Munich", "A04", " ");
    airport->schedule(LH2010,Flight_LH2010);
    airport->delay(LH2010,LH2010_delayed);

    //Setting Flight "LH 2010"
    Flight *Flight_EW9347 = new Flight(ArrivalDeparture::arrival, "EW 9347 ", "Manchester", "B04", " ");
    airport->schedule(EW9347,Flight_EW9347);

    //Setting Flight "AF 1307"
    Flight *Flight_AF1307 = new Flight(ArrivalDeparture::departure, "AF 1307 ", "Paris", "B51", "192-194");
    airport->schedule(AF1307,Flight_AF1307);
    string AF1307_comment= "departed";
    airport->comment(AF1307,AF1307_comment);

    //Setting Flight "SU 2537"
    Flight *Flight_SU2537 = new Flight(ArrivalDeparture::departure, "SU 2537 ", "Moscow", "C31", "252-255");
    airport->schedule(SU2537,Flight_SU2537);
    string SU2537_comment= "boarding";
    airport->comment(SU2537,SU2537_comment);

    //Setting Flight "EW 9466"
    Flight *Flight_EW9466 = new Flight(ArrivalDeparture::departure, "EW 9466 ", "London-Heathrow", "B35", "151-170");
    airport->schedule(EW9466,Flight_EW9466);

    //Setting Flight "LH 2011"
    Flight *Flight_LH2011 = new Flight(ArrivalDeparture::departure, "LH 2011 ", "Munich", "A40", "115-120");
    airport->schedule(LH2011,Flight_LH2011);
    string LH2011_comment= "Code sharing";
    airport->comment(LH2011,LH2011_comment);

    //Setting Flight "XQ 959"
    Flight *Flight_XQ959 = new Flight(ArrivalDeparture::departure, "XQ 959 ", "Izmir", "C45", "240-242");
    airport->schedule(XQ959,Flight_XQ959);
    airport->delay(XQ959,XQ959_delayed);


    cout<<"DUSSELDORF AIRPORT ARRIVALS"<<endl<<"==========================="<<endl;
    airport->print(ArrivalDeparture::arrival);
    cout<<endl<<endl;
    cout<<"DUSSELDORF AIRPORT DEPARTURES"<<endl<<"============================="<<endl;
    airport->print(ArrivalDeparture::departure);
    cout<<endl<<endl;

    delete airport;

    return 0;
}
