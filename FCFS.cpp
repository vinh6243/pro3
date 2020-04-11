#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

class FCFS
{
public:
    string name;
    int arrival ,burst , departure ;

	FCFS()
	{
		arrival =0;
		burst = 0;
		departure = 0;
	}

	FCFS( int a , int b)
		{
			arrival = a;
			burst = b;
		}

	double waiting_time()
	{
		return (double)(departure - arrival - burst) ;
	}
};

void calc_departure(vector<FCFS>& x )
{
	int start , time = 0 ;
		for (int j=0 ; j<sizee ;j++)
	{
		while((x[j].arrival > time)){time++;}
		start = x[j].burst ;
		cout << x[j].name <<"("<< time << ")";
		for( start ; start> 0 ;start--)
		{
			time++;
			cout << "*" ;
		}

		x[j].departure = time ;
	}
		cout <<"("<< time << ")";
		cout<<endl ;

}

bool sortFCFSByArrival(const FCFS &lhs, const FCFS &rhs) 
    { 
        return lhs.arrival < rhs.arrival; 
    }

int FCFSmain()
{
	ifstream ip ("schedule.txt");
    int i=0 ,inputType;
	string a,b;

	cout<<"Enter no. of processes\n";
    cin>>sizee ;
	cout<<"Enter 1 for input file OR enter 0 for CMD \n";
	cin>>inputType;

	vector<FCFS> process(sizee);
    cout<<endl ;

	//Reading From File

	if(inputType == 1)
	{
		while(ip.good() && i<sizee)
		{
			getline(ip,process[i].name,',');
			getline(ip,a,',');
			getline(ip,b,'\n');
			process[i].arrival = stoi(a);
			process[i].burst = stoi(b) ;
			i++;
		}
	}

	//Reading from CMD

	if (inputType==0)
	{
		for (vector<FCFS>::size_type i = 0; i != sizee; ++i)
		{
			cout << "Process #" << i + 1 << " name: ";
			cin >> process[i].name;

			cout << "Process #" << i + 1 << " arrival time: ";
			cin >> process[i].arrival;

			cout << "Process #" << i + 1 << " burst time ";
			cin >> process[i].burst;
	
    }
	}
    cout << "\n";


    // Sort by arrival
    sort(process.begin(), process.end(), sortFCFSByArrival);

	calc_departure(process);

	printAll(process) ;
    
    cout << endl;
	cout <<"Average Waiting time = "<< avg_WTime(process) <<endl;
    return 0;
}
