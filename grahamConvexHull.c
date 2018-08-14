#include <stdio.h>

#define max 1000

typedef struct point {
    int xc;
    int yc;
}point;

struct node
{
    point pt;
    struct node *link;
}*top = NULL;

#define MAX 500

// function prototypes
void push(point);
void pop();
void empty();
void stack_full();
int st_count();
void destroy();
void print_top();
void sort(int low, int high);
void merging(int low, int mid, int high);
int xProduct(point,point,point);

point xsort[1000];
point scat[1000] = {{-1,-1},{12, 5},{8, 5},{9, 19},{2, 4},{12, 9},{14, 16},{19, 6},
{14, 5},{3, 9},{8, 9},{11, 16},{13, 18},{15, 10},{6, 14},{10, 9}};

int main() {
   int i,size = 15;
   if(size<=3) printf("Convex HULL NOT POSSIBLE");
   else
   {
       printf("List before sorting\n");

       for(i = 0; i < size; i++)
        printf("{%d,%d}, ",scat[i].xc,scat[i].yc);

        sort(0, size);

       printf("\nList after sorting\n");
       for(i = 0; i < size; i++)
          printf("{%d,%d}, ",scat[i].xc,scat[i].yc);

       push(scat[0]);
       push(scat[1]);
       push(scat[2]);
       int cnt = 3;
       for(i=3;i<=size;i++){
            while(xProduct(top->pt,top->link->pt,scat[i])<0 && cnt>=3)
                pop();
            push(scat[i]);
        }
        printf("\n");
       struct node *top1 = top;
       top=NULL;
       push(scat[0]);
       push(scat[1]);
       push(scat[2]);
       cnt = 3;
       for(i=3;i<=size;i++){
            while(xProduct(top->pt,top->link->pt,scat[i])>0 && cnt>=3){
                pop();
                cnt--;

            }
            push(scat[i]);
            cnt++;

        }

       struct node *cur;
       cur = top1;
       printf("Convex HULL vertices : UPPER\n ");
       while(cur!=NULL){
        printf("{%d,%d} ",cur->pt.xc,cur->pt.yc);
        cur = cur->link;
       }
        printf("\nLOWER\n");
       cur = top;
        while(cur!=NULL){
        printf("{%d,%d} ",cur->pt.xc,cur->pt.yc);
        cur = cur->link;
       }
   }
   return 0;
}

xProduct(point aa,point bb,point cc){
    return (bb.xc - aa.xc)*(cc.yc - aa.yc) - (bb.yc - aa.yc)*(cc.xc - aa.xc);
}

void merging(int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(scat[l1].xc <= scat[l2].xc)
       {
         xsort[i] = scat[l1++];
       }
      else
         xsort[i] = scat[l2++];
   }

   while(l1 <= mid)
      xsort[i++] = scat[l1++];

   while(l2 <= high)
      xsort[i++] = scat[l2++];

   for(i = low; i <= high; i++)
      scat[i] = xsort[i];
}

void sort(int low, int high) {
   int mid;

   if(low < high) {
      mid = (low + high) / 2;
      sort(low, mid);
      sort(mid+1, high);
      merging(low, mid, high);
   } else {
      return;
   }
}


// to insert elements in stack
void push(point val)
{
    int count;
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));

    count = st_count();
    if (count <= MAX - 1)
    {
        //printf("\nEnter value which you want to push into the stack :\n");
        //scanf("%d",&val);
        temp->pt = val;
        temp->link = top;
        top = temp;
    }
    else
        printf("WARNING: STACK FULL\n");
}

// to delete elements from stack
void pop()
{
    struct node *temp;
    if (top == NULL)
        printf("**Stack is empty**\n");
    else
    {
        temp = top;
        printf("Value popped out is {%d,%d}\n",temp->pt.xc,temp->pt.yc);
        top = top->link;
        free(temp);
    }
}

// to check if stack is empty
void empty()
{
    if (top == NULL)
        printf("STACK IS EMPTY\n");
    else
        printf("elements are present, stack is not empty \n");
}

// to check if stack is full
void stack_full()
{
    int count;

    count = st_count();
    if (count == MAX)
    {
        printf("stack  full\n");
    }
    else
        printf("stack not full \n");
}

// to count the number of elements

int st_count()
{
    int count = 0;
    struct node *temp;
    temp = top;
    while (temp!= NULL)
    {
        temp = temp->link;
        count++;
    }
    return count;
}

// to empty and destroy the stack
void destroy()
{
    struct node *temp;
    temp = top;
    while (temp!= NULL)
    {
        pop();
        temp = temp->link;
    }
    printf("stack destroyed\n");
}

// to print top element of stack
void print_top()
{
    if (top == NULL)
        printf("\n**Already EMPTY stack**\n");
    else
        printf("\nTop of the stack is %d %d\n",top->pt.xc,top->pt.yc);
}

