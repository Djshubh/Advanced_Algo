// C++ program to us prioritid_queue to implement Min Heap
// for user defined class
#include <bits/stdc++.h>
using namespace std;

// User defined class, Machine
class Machine
{
    int load;
    int id;
public:
   Machine(){
     load = 0;
     id = -1;
   }
   Machine(int _load, int _id)
   {
      load = _load;
      id = _id;
   }
   int getload() const { return load; }
   int getid() const { return id; }
   void addload(int _load){ load += _load;}
   void setid(int _id) {id = _id;}
};

// To compare two Machines
class midComparator
{
public:
    int operator() (const Machine& l1, const Machine& l2)
    {
        return l1.getload() > l2.getload();
    }
};

// Driver code
int main ()
{
    // Creates a Min heap of Machines (order bid load coordinate)
    priority_queue <Machine, vector<Machine>, midComparator > pq;

    // Insert Machines into the min heap
    //pq.push(Machine(10, 2));
    //pq.push(Machine(2, 1));
    //pq.push(Machine(1, 5));

    // One bid one eloadtract items from min heap
    /*while (pq.empty() == false)
    {
        Machine p = pq.top();
        cout << "(" << p.getload() << ", " << p.getid() << ")";
        cout << endl;
        pq.pop();
    }
    */
    //No. of jobs - m
    // No. of Machines - n
    int m,n,*jobtime,*A,i,j;
    cout <<"Enter No. of jobs & machines:\n";
    cin >> m >>n;
    Machine mac[100];
    //Machine temp;
    //mac = (Machine *)malloc(sizeof(Machine)*n);
    jobtime =  new int[m];
    A = new int[m];

    cout<<"Please enter the job sequence:\n";
    for(j=0;j<m;j++){
        cin>>jobtime[j];
    }
    // Start with no jobs assigned.
    for(i=0;i<n;i++){
        mac[i].setid(i);
       // mac[i].setload(0);
        pq.push(mac[i]);
    }
    for(j=0;j<m;j++){
        A[j]= -1;
    }

    for(j=0;j<m;j++){
        Machine temp(pq.top());
        pq.pop();
        int x = temp.getid();
        //cout<<mac[x].getload()<<" "<<jobtime[j]<<"\n";
        mac[x].addload(jobtime[j]);
        A[j]=x;
        pq.push(mac[x]);
    }
    cout<<"Machines with final load.\n:";
     for(i=0;i<n;i++){
        cout<<i<<" ";
    }
    cout<<"\n:";
    for(i=0;i<n;i++){
        cout<<mac[i].getload()<<" ";
    }
    cout<<"\nSeq. No. ,Jobs(time) and assigned machines\n";
    for(j=0;j<m;j++){
        cout<<j<<":\t"<<jobtime[j]<<"\t"<<A[j]<<"\n";
    }
    return 0;
}
