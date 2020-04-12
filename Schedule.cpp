#include<iostream>
#include<limits>
#include <iomanip>
#include<fstream>
using namespace std;

int sumWaitingTime = 0;
int sumTurnAroundTime = 0;
int TimeSum = 0;
int sumResponseTime = 0;
int sumCompletionTime = 0;
int currentTime = 0;
int timeQuantum;
int numOfProcesses;
    
class ProcessScheduling
{
public:
  string processName;
  int arrivalTime;
  int burstTime;
  int priority;

  bool isComplete;

  int responseTime;
  int completionTime;
  int remainingTime;
        
  int waitingTime;
  int turnAroundTime;
        
  void initializing()
  {
    isComplete = false;
    remainingTime = burstTime;
    waitingTime = 0;
    responseTime = 0;
    turnAroundTime = 0;
  }
        
};

//disyplay the average turnAroundTime and average waitingTime
double display(double numPro, double turn , double around)
{
  cout << fixed << setprecision(2);
    
  cout << "Average turn-around time = " << (float) turn/numPro;
  cout << ", Average waiting time = " << (float) around/numPro;
  cout << endl;
}

//FCFS main 
void FCFSmain()
{
  ///////////////////////////////////////////////
  int numOfProcesses = 8;
  ProcessScheduling processes[8];
  ifstream fin;
  int i = 0;
  fin.open("processes.txt");
  fin >>processes[i].processName;
  while(fin)
    {
      fin >>processes[i].arrivalTime;
      fin >>processes[i].burstTime;
      cout <<processes[i].processName<<"\t";
      cout <<processes[i].arrivalTime<<"\t";
      cout<<processes[i].burstTime<<"\t"<<endl;
      i++;
      fin >>processes[i].processName;
    }
  ///////////////////////////////////////////////
  for(int i=0; i < numOfProcesses; i++)
   {
     processes[i].waitingTime = TimeSum;
     processes[i].completionTime =  processes[i].waitingTime + processes[i].burstTime;
     if(i == 0)
       {
	 processes[i].responseTime = 0;
       }
     else
       {
	 processes[i].responseTime = processes[i-1].completionTime;
       }
     
     processes[i].turnAroundTime = processes[i].completionTime; 
     
     cout << processes[i].processName << ": ";
     cout << "Waiting Time: " << processes[i].waitingTime;
     cout << ", Turn Around Time: " << processes[i].turnAroundTime << endl;
     
     sumWaitingTime = sumWaitingTime + processes[i].waitingTime;
     sumTurnAroundTime =sumTurnAroundTime +  processes[i].turnAroundTime;
     
     TimeSum = TimeSum + processes[i].burstTime;
   }
  display(numOfProcesses, sumTurnAroundTime, sumWaitingTime);//display the turn and wait
} // end of FCFS 

//SCFS main
void SJFmain()
{  
  int numOfProcesses = 8;
  ProcessScheduling processes[8];
  
  ifstream fin;
  int i = 0;
  fin.open("processes.txt");
  fin >>processes[i].processName;
  while(fin)
    {
      fin >>processes[i].arrivalTime;
      fin >>processes[i].burstTime;
      cout <<processes[i].processName<<"\t";
      cout <<processes[i].arrivalTime<<"\t";
      cout<<processes[i].burstTime<<"\t"<<endl;
      i++;
      fin >>processes[i].processName;
    }

  for(int i=0; i<numOfProcesses; i++)
    {
      processes[i].processName = "T" + to_string(i+1) ;
      processes[i].arrivalTime = 0;
      
      processes[i].initializing();
    }
  cout << "\n" << endl;

  for(int i=0;i<numOfProcesses-1;i++)
    {
      for(int j=i+1;j<numOfProcesses;j++)
        {
	  if(processes[j].arrivalTime < processes[i].arrivalTime)
            {
	      ProcessScheduling temp = processes[j];
	      processes[j] = processes[i];
	      processes[i] = temp;
            }
        }
    }//end for loop

  while(true)
    {
      int currentShortestJobIndex = -1; 
      int currentShortestJobRemainingTime = numeric_limits<int>::max();

      bool isAllCompleted = true;

      for(int i=0;i<numOfProcesses;i++)
	{
	  if(!processes[i].isComplete)
	    {
	      isAllCompleted = false;
	      if(processes[i].arrivalTime <= currentTime)
                {
		  if(processes[i].burstTime < currentShortestJobRemainingTime)
                    {
		      currentShortestJobRemainingTime = processes[i].burstTime;
		      currentShortestJobIndex = i;
		    }//end if
                }//end if
	    }//end if
	}//end of for loop

      if(isAllCompleted)
	{
	  break;
	}

      processes[currentShortestJobIndex].responseTime = currentTime;

      currentTime += processes[currentShortestJobIndex].burstTime;
      processes[currentShortestJobIndex].isComplete = true;

      processes[currentShortestJobIndex].completionTime = currentTime;
    }//end of while loop

  for(int i=0;i<numOfProcesses;i++)
    {
      cout << processes[i].processName << ": ";
      processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
      processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
      cout << "Waiting Time: " << processes[i].waitingTime;
      cout << ", Turn Around Time: " << processes[i].turnAroundTime << endl;

      sumWaitingTime = sumWaitingTime + processes[i].waitingTime;
      sumTurnAroundTime = sumTurnAroundTime + processes[i].turnAroundTime;
    } //end of for loop
  display(numOfProcesses, sumTurnAroundTime, sumWaitingTime);//display the turn and wait
}//end of SJF 

void Prioritymain() //Priority
{
  int numOfProcesses = 8;

  ProcessScheduling processes[numOfProcesses];

  ifstream fin;
  int i = 0;
  fin.open("processes.txt");
  fin >>processes[i].processName;
  while(fin)
    {
      fin >>processes[i].priority;
      fin >>processes[i].burstTime;
      cout <<processes[i].processName<<"\t";
      cout <<processes[i].priority<<"\t";
      cout<<processes[i].burstTime<<"\t"<<endl;
      i++;
      fin >>processes[i].processName;
    }


  for(int i=0;i < numOfProcesses; i++)
    {
      processes[i].processName = "T" + to_string(i + 1);
      processes[i].arrivalTime = 0;
      processes[i].initializing();
    }

  cout << "\n" << endl;

  for(int i=0 ;i < numOfProcesses-1; i++)
    {
      for(int j=i+1;j<numOfProcesses;j++)
        {
	  if(processes[j].arrivalTime < processes[i].arrivalTime)
            {
	      ProcessScheduling temp = processes[j];
	      processes[j] = processes[i];
	      processes[i] = temp;
            }
        }
    }

  while(true)
    {

      int currentHighestPriorityIndex = -1;
      int currentHighestPriority = numeric_limits<int>::max();

      bool isAllCompleted = true;

      for(int i=0;i<numOfProcesses;i++)
	{
	  if(processes[i].remainingTime > 0)
	    {
	      isAllCompleted = false;
	      if(processes[i].arrivalTime <= currentTime)
                {
		  if(processes[i].priority < currentHighestPriority)
                    {
		      currentHighestPriority = processes[i].priority;
		      currentHighestPriorityIndex = i;
                    }
                }
	      
	    }
	}

      if(isAllCompleted)
	{
	  break;
	}
      
      processes[currentHighestPriorityIndex].responseTime = currentTime;
      processes[currentHighestPriorityIndex].remainingTime = 0;
      currentTime = currentTime + processes[currentHighestPriorityIndex].burstTime;
      processes[currentHighestPriorityIndex].completionTime = currentTime; 
    }//end of while loop

  for(int i=0;i<numOfProcesses;i++)
    {
      cout << processes[i].processName << ": ";
      processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
      processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
      cout << "Waiting Time: " << processes[i].waitingTime;
      cout << ", Turn Around Time: " << processes[i].turnAroundTime << endl;

      sumResponseTime = sumResponseTime + processes[i].responseTime;
      sumCompletionTime = sumCompletionTime + processes[i].completionTime;
      sumWaitingTime = sumWaitingTime + processes[i].waitingTime;
      sumTurnAroundTime = sumTurnAroundTime + processes[i].turnAroundTime;
    }
  display(numOfProcesses, sumTurnAroundTime, sumWaitingTime);//display the turn and wait
    
}//Prioritymain()


void RRmain() // Round Robin
{
  cout << "\nEnter Time Quantum: ";
  cin >> timeQuantum;

  int numOfProcesses = 8;

  ProcessScheduling processes[numOfProcesses];

  ifstream fin;
  int i = 0;
  fin.open("processes.txt");
  fin >>processes[i].processName;
  while(fin)
    {
      fin >>processes[i].priority;
      fin >>processes[i].burstTime;
      cout <<processes[i].processName<<"\t";
      cout <<processes[i].priority<<"\t";
      cout<<processes[i].burstTime<<"\t"<<endl;
      i++;
      fin >>processes[i].processName;
    }

  for(int i=0;i<numOfProcesses;i++)
    {
      processes[i].processName = "T" + to_string(i+1);
      processes[i].arrivalTime = 0;

      processes[i].initializing();
    }

  cout << "\n" << endl;

  currentTime = processes[0].arrivalTime;
  int remainingProcesses = numOfProcesses;

  for(int i=0;i<numOfProcesses;i=(i+1)%numOfProcesses)
    {
      if(processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime)
        {
	  if(processes[i].remainingTime == processes[i].burstTime)
	    {
	      processes[i].responseTime = currentTime;
	    }

	  if(processes[i].remainingTime <= timeQuantum)
	    {
	      currentTime += processes[i].remainingTime;
	      processes[i].completionTime = currentTime;
	      processes[i].remainingTime = 0;
	      remainingProcesses--;
	    }
	  else
	    {
	      currentTime += timeQuantum;
	      processes[i].remainingTime -= timeQuantum;
	    }

        }

      if(remainingProcesses == 0)
        {
	  break;
        }
    }//end for loop

  for(int i=0; i<numOfProcesses; i++)
    {
      cout << processes[i].processName << ": ";
      processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
      processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
      cout << "Waiting Time: " << processes[i].waitingTime;
      cout << ", Turn Around Time: " << processes[i].turnAroundTime << endl;
        
        
      sumResponseTime = sumResponseTime + processes[i].responseTime;
      sumCompletionTime = sumCompletionTime + processes[i].completionTime;
      sumWaitingTime = sumWaitingTime + processes[i].waitingTime;
      sumTurnAroundTime = sumTurnAroundTime + processes[i].turnAroundTime;
    } //end for-loop
  display(numOfProcesses, sumTurnAroundTime, sumWaitingTime);//display the turn and wait
}//end of RRmain


//main program! 
int main() 
{
  int x,y;
  cout << "1. (First Come First Served) \n";
  cout << "2. (Shortest Job First)\n";
  cout << "3. (Prority)\n";
  cout << "4. (Round Robin)\n";
  
  cout <<" Type of scheduler =  "; 
  cin >>x;
  cout<< endl;

  //selection options
  if ( x==1 )
    { 
      cout<<"\n*****  First Come First served ***** \n\n"; 
      FCFSmain();
    }
  if ( x==2 )
    { 
      cout<<"\n***** Shortest Job First ***** \n\n"; 
      SJFmain();
    }
  if ( x==3 )
    { 
      cout<<"\n***** Priority ***** \n\n"; 
      Prioritymain();
    }
  if ( x==4 )
    { 
      cout<<"\n***** Round Robin ***** \n\n"; 
      RRmain();
    }
  return 0;
}//end main
