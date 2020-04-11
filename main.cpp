#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int sizee =0;

template<class T>
double avg_WTime(vector<T>& x )
{
	double sum = 0.0 ;
	for (int i =0 ; i<sizee ;i++)
		sum += x[i].waiting_time();
	return sum/sizee ;
	
	cout<< endl <<endl;
	cout <<"Name \t"<< "Arrival\t" <<"Burst\t" <<"Departure "<<endl ;
	for (int j=0 ; j<sizee ;j++)
		cout <<x[j].name<<"\t "<< x[j].arrival << "\t " <<x[j].burst <<"\t " <<x[j].departure <<endl ;
}

template<class T>
void printAll(vector<T>& x)
{
	cout<< endl <<endl;
	cout <<"Name \t"<< "Arrival\t" <<"Burst\t" <<"Departure "<<endl ;
	for (int j=0 ; j<sizee ;j++)
		cout <<x[j].name<<"\t "<< x[j].arrival << "\t " <<x[j].burst <<"\t " <<x[j].departure <<endl ;

}

int main()
{

	int x,y;
do {
	cout << "Enter \n   1  for (First Come First Served) \n   2  for (Shortest Job First) \n   3  for (Prority) \n   4  for (Round Robin) \n\n";
	cout <<" Type of scheduler =  "; cin >>x;
	cout<< endl;
    
    

	if ( x==1 )
	{ 
		cout<<"\n/////// First Come First served \\\\\\\\\\\\\\ \n\n"; 
		fcfs.FCFSmain();
	}
	if ( x==2 )
	{ 
		cout<<"\n/////// Shortest Job First \\\\\\\\\\\\\\ \n\n"; 
		SJFmain();
	}
	if ( x==3 )
	{ 
		cout<<"\n/////// Priority \\\\\\\\\\\\\\ \n\n"; 
		Prioritymain();
	}
	if ( x==4 )
	{ 
		cout<<"\n/////// Round Robin \\\\\\\\\\\\\\ \n\n"; 
		RRmain();
	}


	cout << "\n////////////////////////DONE//////////////////////////\n \nTo try again press 1 \n";
	cin>>y;
	cout<< endl <<endl;
} 

while (y == 1);

	return 0;
}
