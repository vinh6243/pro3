#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class SJF
{
public:
    string name;
    int arrival ,burst , departure ,timeLeft ,finished;

	SJF()
	{
		arrival =0;
		burst = 0;
		departure = 0;
		timeLeft = 0;
		finished = 0;
	}

	SJF( int a , int b)
		{
			arrival = a;
			burst = b;
		}

	double waiting_time()
	{
		return (double)(departure - arrival - burst) ;
	}

};


void sjf_calc (vector<SJF>& x , int p)
{
	int time =0 ,count =0 ,check =0;
	SJF* Current_process;
	Current_process = &x[0];
	while((*Current_process).arrival > time){time++;}
	cout << (*Current_process).name <<"("<< time << ")";
	while(count < sizee)
	{
		count = 0;
		check =0 ;

		//Non-Preemptive
		if(p == 0)
		{
			for(int j=0; j< sizee ; j++)
			{
				if(x[j].arrival<= time &&  (*Current_process).finished ==1)
				{

					if(x[j].finished !=1)
					{Current_process = &x[j];}

					for(int l=j ; l < sizee ; l++)
					{
						if(x[l].arrival<= time && x[l].timeLeft < (*Current_process).timeLeft)
							if(x[l].finished !=1)
							{Current_process = &x[l];}
					}
					
					check++;

				}
				if(x[j].finished ==1)
					count ++;

			}

		}

		//Preemptive

		if(p==1)
		{
			for(int j=0; j< sizee ; j++)
			{
				if(x[j].arrival<= time && x[j].timeLeft < (*Current_process).timeLeft)
				{
					Current_process = &x[j];
					check ++;
					
				}
				if(x[j].finished ==1)
					count ++;

			}

		}


		if((*Current_process).finished == 1) 
		{time++; continue;}

		if(check >0) cout << (*Current_process).name <<"("<< time << ")"; //printing gauntt chart

		if((*Current_process).timeLeft ==0  )
		{
			
			(*Current_process).finished = 1;
			(*Current_process).timeLeft = 999999999;
			(*Current_process).departure = time ;
			time--;
			
		}

		else
		{
			(*Current_process).timeLeft--;
			cout << "*" ;
		}
		time++;
		
	}
		cout <<"("<< time-1 << ")";
	cout<<endl<<endl;
}

bool sortSJFByArrival(const SJF &lhs, const SJF &rhs) { return lhs.arrival < rhs.arrival; }

int SJFmain()
{
	ifstream ip ("data.csv");
    int i=0 ,inputType , preemptive;
	string a,b;


    cout<<"Enter no. of processes\n";
    cin>>sizee ;
	cout<<"Enter 1 for input file OR enter 0 for CMD \n";
	cin>>inputType;
	cout<<"Enter 1 for preemptive OR enter 0 for Nonpreemptive \n";
	cin>>preemptive;

	vector<SJF> Sprocess(sizee);
    cout<<endl ;

	if (inputType==1)
	{
		while(ip.good()&& i<sizee)
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

		for (vector<SJF>::size_type i = 0; i != sizee; ++i)
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
    sort(Sprocess.begin(), Sprocess.end(), sortSJFByArrival);


	sjf_calc (Sprocess , preemptive);

	printAll(Sprocess) ;
    
    cout << endl;
	cout <<"Average Waiting time = "<< avg_WTime(Sprocess) <<endl;


    return 0;
}
