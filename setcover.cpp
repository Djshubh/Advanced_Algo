#include <iostream>
#include <set>
#include <iterator>

using namespace std;
#define MAX 10000001

int main(){
   set <int, greater <int> > U,R,s[10],I,solution;      // Balanced BST
   int n,i,j,nsubs,val;

   float cost[3]={5,10,3};
   cout<<"Enter No. of Elements in set U : ";
   cin >>n;
    cout<<"Enter Values in set U: ";
   for(i=0;i<n;i++){
        cin>>val;
        U.insert(val);
   }
   cout<<"Enter No. of Subsets: ";
   cin>>nsubs;
   for(i=0;i<nsubs;i++){
     R.insert(i);
     cout<<"Enter No. of Elements Subset: "<<i<<endl;
      cin>>n;
      cout<<"Enter Elements: \n"<<endl;
     for(j=0;j<n;j++){
        cin>>val;
        s[i].insert(val);
     }
   }
   set <int, greater <int> > :: iterator itr,itr2,x;
   float mincost,cpe;
   int cnt,minset=0;
   // execute
   while(I.size()!=U.size()){
        mincost = MAX;
        // loop to find minimal cost per element covered
        for(itr=R.begin();itr != R.end();++itr){
              //  cout<<"check1";
                cnt=0;
             // count the no. of Similar elements in s[i] & I
             for (itr2 = I.begin(); itr2 != I.end(); ++itr2){
                    if(s[*itr].count(*itr2)!=0)
                        cnt++;
            }
            cout<<"count similar ::"<<cnt<<" ";
              float sz = s[*itr].size();

             //cpe = cost[*itr]/(sz - (float)cnt);     // cost =>  given by user
             cpe = sz/(sz - (float)cnt);     // cost => no. of elements in subset

             cout<<"cpe: "<<cpe<<" subset_size: "<<sz<<endl;
             //cout<<"sub_cost : "<<cost[*itr];
              if(mincost>cpe){
                mincost= cpe;
                minset = *itr;
              //  *x = *itr;
              }

        }
         cout<<"\nset with min cost :"<<minset<<" "<<endl;
         solution.insert(minset);

        I.insert(s[minset].begin(),s[minset].end());

       int deleted =  R.erase(minset);
      // cout <<"\nDeleted Set No. : "<<deleted<<endl;
   }

     cout<<"\nGreedy Subset Cover ::";
   for(itr=solution.begin();itr!=solution.end();++itr)
   {
      cout<<"\nSubSet :"<<*itr<<" ::";
      for(itr2=s[*itr].begin();itr2!=s[*itr].end();itr2++){
        cout<<*itr2<<" ";
      }
      cout<<endl;
   }

}
