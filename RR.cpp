#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

class RR
{
public:
    string name;
    int arrival ,burst , departure ,timeLeft ,finished;

	RR()
	{
		arrival =0;
		burst = 0;
		departure = 0;
		timeLeft = 0;
		finished = 0;
	}

	RR( int a , int b)
		{
			arrival = a;
			burst = b;
		}

	double waiting_time()
	{
		return (double)(departure - arrival - burst) ;
	}

};

void RR_calc (vector<RR>& x , int q )
{
	int time =0 ,count =0 ,n=0 ,check =q , d = 0;
	RR* Current_process , *prevProcess = NULL;
	Current_process = &x[0];
	while((*Current_process).arrival > time){time++;}
	while(count < sizee)
	{
		check = q;
		count = 0;
		
		
			for(int j=0; j< sizee ; j++)
			{	
				if(x[j].finished ==1)
					count ++;
			}

		   if (x[(n+1)%sizee].arrival<= time && x[(n+1)%sizee].finished != 1 )
				{
					Current_process = &x[(n+1)%sizee];
					n++;
					if(prevProcess!= Current_process)
						cout << (*Current_process).name <<"("<< time << ")";
				}
		   else 
		   {n++; 
		   if (d<=sizee) 
		   {d++; continue;}
		   }
		d = 0;
		prevProcess = Current_process ;
		if((*Current_process).finished == 1)
		{time++; continue;}

		
		else
		{
			(*Current_process).timeLeft -=q;
			while((*Current_process).timeLeft < 0)
			{
				check --;
				time-- ;
				(*Current_process).timeLeft++ ;
			}
			for(int l=0 ; l<check ; l++)
			{cout << "*";}
		}
		time+=q;


		if((*Current_process).timeLeft == 0  )
		{
			
			(*Current_process).finished = 1;
			(*Current_process).departure = time ;
		}

	}
	cout << "("<< time << ")";
	cout <<endl<<endl;
}

bool sortRRByArrival(const RR &lhs, const RR &rhs) { return lhs.arrival < rhs.arrival; }

int RRmain()
{
	ifstream ip ("data.csv");
    int i=0 ,inputType , QTime;
	string a,b;


    cout<<"Enter no. of processes\n";
    cin>>sizee ;
	cout<<"Enter 1 for input file OR enter 0 for CMD \n";
	cin>>inputType;
	cout<<"Enter Time Quantum  \n";
	cin>>QTime;

	vector<RR> Sprocess(sizee);
    cout<<endl ;

	if (inputType==1)
	{
		while(ip.good() && i<sizee)
		{
			getline(ip,Sprocess[i].name,',');
			getline(ip,a,',');
			getline(ip,b,'\n');
			Sprocess[i].arrival = stoi(a);
			Sprocess[i].burst = stoi(b) ;
			Sprocess[i].timeLeft = Sprocess[i].burst ;
			i++;
		}
	}
	if (inputType==0)
	{

		for (vector<RR>::size_type i = 0; i != sizee; ++i)
		{
			cout << "Process #" << i + 1 << " name: ";
			cin >> Sprocess[i].name;

			cout << "Process #" << i + 1 << " arrival time: ";
			cin >> Sprocess[i].arrival;

			cout << "Process #" << i + 1 << " burst time ";
			cin >> Sprocess[i].burst;
			Sprocess[i].timeLeft = Sprocess[i].burst ;

	
		}
	}
    cout << "\n";

    // Sort by Arrival
    sort(Sprocess.begin(), Sprocess.end(), sortRRByArrival);

	RR_calc (Sprocess , QTime );

	printAll(Sprocess) ;
    
    cout << endl;
	cout <<"Average Waiting time = "<< avg_WTime(Sprocess) <<endl;

    return 0;
}
