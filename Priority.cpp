#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>


class Priority
{
public:
    string name;
    int arrival ,burst , departure ,timeLeft ,finished, prior ,priorityCheck;

	Priority()
	{
		arrival =0;
		burst = 0;
		departure = 0;
		timeLeft = 0;
		finished = 0;
		prior = 0 ;
	}

	Priority( int a , int b , int p)
		{
			arrival = a;
			burst = b;
			prior = p;
		}

	double waiting_time()
	{
		return (double)(departure - arrival - burst) ;
	}

};

void Priority_calc (vector<Priority>& x , int p)
{
	int time =0 ,count =0 ,check =0;
	Priority* Current_process;
	Current_process = &x[0];
	while((*Current_process).arrival > time){time++;}
	cout << (*Current_process).name <<"("<< time << ")";
	while(count < sizee)
	{
		count = 0;
		check =0 ;
		if(p == 0)
		{
			for(int j=0; j< sizee ; j++)
			{
				if(x[j].arrival<= time &&  (*Current_process).finished ==1 && x[j].finished !=1)
				{
					Current_process = &x[j];
					check++;
					for (int k=0 ; k<sizee ; k++)
					{
						if(x[k].arrival<= time &&  x[k].priorityCheck < (*Current_process).priorityCheck)
						{
							Current_process = &x[k];
							check++;
						}

					}
				}
				if(x[j].finished ==1)
					count ++;
			}
		}
		if(p==1)
		{
			for(int j=0; j< sizee ; j++)
			{
				if(x[j].arrival<= time && x[j].priorityCheck < (*Current_process).priorityCheck )
				{
					Current_process = &x[j];
					check++;
				}
				if(x[j].finished ==1)
					count ++;

			}

			
		}
		if(check>0) cout << (*Current_process).name <<"("<< time << ")";


		if((*Current_process).finished == 1)
		{time++; continue;}

		if((*Current_process).timeLeft ==0  )
		{
			
			(*Current_process).finished = 1;
			(*Current_process).timeLeft = 999999999;
			(*Current_process).priorityCheck = 999999999;
			(*Current_process).departure = time ;
			time--;
		}

		else
		{
			(*Current_process).timeLeft--;
			cout << "*";
		}
		
		time++;
	}
	
	cout <<"("<< time-1 << ")" ;
	cout<<endl<<endl;
}

void PriorPrintAll(vector<Priority>& x)
{
	cout<< endl <<endl;
	cout <<"name \t"<< "Arrival\t" <<"Burst\t" <<"Departure\t"<<"Priority"<<endl ;
	for (int j=0 ; j<sizee ;j++)
		cout <<x[j].name<<"\t "<< x[j].arrival << "\t " <<x[j].burst <<"\t " <<x[j].departure <<"\t\t " <<x[j].prior <<endl ;

}

bool sortPriorByArrival(const Priority &lhs, const Priority &rhs) { return lhs.arrival < rhs.arrival; }

int Prioritymain()
{
	ifstream ip ("data.csv");
    int i=0 ,inputType , preemptive;
	string a,b,c;


    cout<<"Enter no. of processes\n";
    cin>>sizee ;
	cout<<"Enter 1 for input file OR enter 0 for CMD \n";
	cin>>inputType;
	cout<<"Enter 1 for preemptive OR enter 0 for Nonpreemptive \n";
	cin>>preemptive;

	vector<Priority> Sprocess(sizee);
    cout<<endl ;

	if (inputType==1)
	{
		while(ip.good() && i<sizee)
		{
			getline(ip,Sprocess[i].name,',');
			getline(ip,a,',');
			getline(ip,b,',');
			getline(ip,c,'\n');
			Sprocess[i].arrival = stoi(a);
			Sprocess[i].burst = stoi(b) ;
			Sprocess[i].prior = stoi(c) ;
			Sprocess[i].timeLeft = Sprocess[i].burst ;
			Sprocess[i].priorityCheck = Sprocess[i].prior ;
			i++;
		}
	}
	if (inputType==0)
	{

		for (vector<Priority>::size_type i = 0; i != sizee; ++i)
		{
			cout << "Process #" << i + 1 << " name: ";
			cin >> Sprocess[i].name;

			cout << "Process #" << i + 1 << " arrival time: ";
			cin >> Sprocess[i].arrival;

			cout << "Process #" << i + 1 << " burst time ";
			cin >> Sprocess[i].burst;
			Sprocess[i].timeLeft = Sprocess[i].burst ;

			cout << "Process #" << i + 1 << " Priority ";
			cin >> Sprocess[i].prior;
			Sprocess[i].priorityCheck = Sprocess[i].prior ;
	
		}
	}
    cout << "\n";


    // Sort by Arrival
    sort(Sprocess.begin(), Sprocess.end(), sortPriorByArrival);

	Priority_calc (Sprocess , preemptive);

	PriorPrintAll(Sprocess) ;
    
    cout << endl;
	cout <<"Average Waiting time = "<< avg_WTime(Sprocess) <<endl;
	
    return 0;
}
