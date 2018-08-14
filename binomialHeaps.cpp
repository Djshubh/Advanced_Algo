// please setup GraphViz package in your system before implementing.

#include <bits/stdc++.h>
#include <climits>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;
ofstream outfile;

struct bionode {
 int key;
 int deg;
 bionode *parent;
 bionode *lchild;
 bionode *rsib;

};

void drawHeap(bionode *h);

bionode *createHeap(){
    bionode *mynode;
    mynode = new bionode;

    mynode->key = -1;
    mynode->deg= 0;
    mynode->parent = NULL;
    mynode->lchild = NULL;
    mynode->rsib = NULL;
    return mynode;
}

void insertNode(bionode *H,int newkey){
    bionode *mynode;
    mynode = new bionode;

    mynode->key = newkey;
    mynode->deg= 0;
    mynode->parent = NULL;
    mynode->lchild = NULL;
    mynode->rsib = H->rsib;
    H->rsib = mynode;

}

void uniteHeap(bionode *x){
  bionode *prev,*next;
  //  cout<<"::1";
  while(x->rsib!=NULL){
     prev = x;
     x= x->rsib;
   //  cout<<"::101";
    if(x->rsib!=NULL){

       next = x->rsib;
    //     cout<<"::2";
        if(x->deg==next->deg && (next->rsib==NULL ||next->rsib->deg!= x->deg))
       {
      //     cout<<"::3";
           if(x->key<=next->key)      //case 3
           {
        //      cout<<"::301";
               x->rsib = next->rsib;
               next->parent= x;
               x->deg +=1;

               next->rsib = x->lchild;
               x->lchild = next;
            }
           else
           if(x->key>=next->key)
           {
          //     cout<<"::302";
                prev->rsib= next;
                x->parent = next;
                next->deg +=1;

                x->rsib= next->lchild;
                next->lchild = x;
                x = next;
           }
           x = prev;
       }
    }
    }
}

void rooTraversal(bionode *H){
    cout<<"\n";
    while(H!=NULL){
        cout<<" "<<H->key;
        H = H->rsib;
    }
}

void decreaseKey(bionode *H,int x,int lowkey ){
    if(H!=NULL){
        if(H->key==x){
            H->key=lowkey;
            while(H->parent!=NULL){
                if(H->parent->key > H->key)
                {
                    int temp;
                    temp = H->key;
                    H->key = H->parent->key;
                    H->parent->key = temp;
                }
                H= H->parent;
            }
        }else
        {
            decreaseKey(H->lchild,x,lowkey);
            decreaseKey(H->rsib,x,lowkey);
        }
    }
}



void heapTraversal(bionode *H){

    if(H!=NULL){
            cout<<"("<<H->key<<", "<<H->deg<<") ";
        if(H->parent!=NULL){
            outfile<<H->key<<"->"<<H->parent->key<<"\n";
        }
        if(H->lchild!=NULL){
            outfile<<H->key<<"->"<<H->lchild->key<<"\n";
            heapTraversal(H->lchild);
        }
        if(H->rsib!=NULL){
            outfile<<H->key<<"->"<<H->rsib->key<<"\n";
            heapTraversal(H->rsib);
        }
    }
}

bionode *unionHeap(bionode *p,bionode *q){
     bionode *x,*y;
     x = createHeap();
     y = x;
     p = p->rsib;
     q = q->rsib;
     //drawHeap(q);

     while(p!=NULL||q!=NULL){
        bionode *z;
        z = new bionode;
        if(p==NULL){
              //  cout<<"PNULL ";
            z = q;
            x->rsib = z;
            q = q->rsib;
        }else
        if(q==NULL){
             //   cout<<"QNULL ";
            z= p;
            x->rsib = z;
            p = p->rsib;
        }
        else{
          if(q->deg<=p->deg){
             //  cout<<"Q ";
            z = q;
            x->rsib = z;
            q = q->rsib;
          }else
          if(q->deg>p->deg){
             //  cout<<"P ";
            z = p;
            x->rsib = z;
            p = p->rsib;
          }
        }

        x = x->rsib;
        // cout<<x->key<<" ";
    }
    //rooTraversal(y);

    uniteHeap(y);
    //drawHeap(y);
    cout<<"\n";
    return y;
}

int findMin(bionode *H){

    int minval = INT_MAX;
    if(H->rsib==NULL)
        cout<<"::EMPTY HEAP::";
    else
        H = H->rsib;
    while(H!=NULL){
        if(H->key<minval)
            minval = H->key;
        H = H->rsib;
    }
return minval;
}

bionode *revhd;
int reverseList(bionode *x){
  if(x->rsib!=NULL){
     reverseList(x->rsib);
     (x->rsib)->rsib = x;

  }else{
    revhd = x;
  }
  return 0;
}

bionode* extractMin(bionode *head){

      int minkey =findMin(head);
      bionode *prev,*cur,*newhead;
      cur = head;
      while(cur->key!=minkey){
        prev = cur;
        cur = cur->rsib;
      }
      prev->rsib = cur->rsib;
      if(cur->lchild!=NULL){
      newhead = cur;
      cur = cur->lchild;
      newhead->key = -1;
      newhead->lchild = NULL;

      bionode *x = cur;
      //make parents null of all roots.. reuse cur
      while(cur!=NULL){
        cur->parent =NULL;
        cur = cur->rsib;
      }

      reverseList(x);
      newhead->rsib = revhd;
      x->rsib=NULL;

      rooTraversal(newhead);
      newhead = unionHeap(head,newhead);
      cout<<"Heap After deleting MINIMUM : "<<minkey<<"\n";
      //drawHeap(newhead);
      return newhead;
      }
      else{
        delete cur;
        return head;
      }
}

void drawHeap(bionode * head){
    outfile.open("binotree.dot", ofstream::out | ofstream::trunc);
    outfile.close();
    //Now open file in append mode.
    outfile.open("binotree.dot", ios_base::app);
    outfile<<"digraph G {";
    heapTraversal(head);
    outfile<<"}";
    outfile.close();
    cout<<"\nYour Tree is saved in binotree.png file. Thanks for using GraphViz.\n";
      char cmd[] = "dot -Tpng binotree.dot -o binotree.png";
      system(cmd);
      system("binotree.png");
}

bionode* deleteNode(bionode *head,int val){
        decreaseKey(head,val,INT_MIN);
        head =  extractMin(head);
        return head;
}
// IP : 3, 5, 1, 2, 14, 15, 11, 12.
// IP : 7,18,38,24, 17, 23, 21, 39, 41, 26, 46, 30, 52, 35.
int main(){

    bionode *head1,*head2,*uheap;
    head1 = createHeap();
    head2 = createHeap();
   // H = createHeap();
    int binkey1[] = {7,18,38,24, 17, 23, 21, 39,41,26, 46, 30, 52, 35},n1=14;
    int binkey2[] = {11, 5, 1, 12, 14, 15, 3,2}, n2=8;
    //cout<<"No. of values :"<<n<<endl;

    cout<<"\nProcessing...heap1....\n";
     for(int i =0;i<n1;i++){
        insertNode(head1,binkey1[i]);
        cout<<"INSERTED KEY : "<<head1->rsib->key<<"\n";
        uniteHeap(head1);
        drawHeap(head1);
        cout<<" ..";
        cout<<"heap size :\n"<<i+1<< "\n Press any key to continue...\n";
        getch();

           // heapTraversal(head);
     }
     cout<<"\nProcessing...heap2....\n";
     for(int i =0;i<n2;i++){
        insertNode(head2,binkey2[i]);
        cout<<head2->rsib->key;
        uniteHeap(head2);
        cout<<" ..";
           // heapTraversal(head);
     }
     cout <<"\nEnter the options :\n 1. print heap 1\n";
     cout <<"2. print heap 2\n";
     cout <<"3. find Minimum Value \n";
     cout <<"4. Decrease key - x\n";
     cout <<"5. Extract Minimum\n";
     cout<<"6. UNION of two heaps \n";
     cout<<"7. Delete Node with key value\n";

     int choice,cnt=1;
      int x,k;
      //x = 39 ; k = 10;

     while(cnt>0){
        cin >> choice;
        switch(choice){
        case 1 :    drawHeap(head1);
                    break;
        case 2 :    drawHeap(head2);
                    break;
        case 3 :    cout<<"Heap 1 Minimum : \n"<<findMin(head1);
                    cout<<"Heap 2 Minimum : \n"<<findMin(head2);
                    break;
        case 4 :    cout<<"\n Enter KEY to be decreased and decreased key value from heap 1 : ";
                    cin >> x >> k;
                    decreaseKey(head1,x,k);
                    drawHeap(head1);
                    break;
        case 5 :    head1 = extractMin(head1);
                    drawHeap(head1);
                    break;
        case 6 :    uheap = unionHeap(head1,head2);
                    drawHeap(uheap);
                    break;
        case 7 :    cout <<"Enter value to be deleted from heap 1";
                    cin >> x;
                    head1 = deleteNode(head1,x);
                    drawHeap(head1);
                    break;
        default :   cout<<"Wrong input";

        }
        cout<<"\nDo you wish to continue? (1 == yes | 0 == No)";
        cin >>cnt;
     }
  return 0;
}
