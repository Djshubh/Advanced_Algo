#include<stdio.h>
#include<stdlib.h>


typedef struct point {
    int xc;
    int yc;
    int ptr;
}point;

// An AVL tree AVLNode
struct AVLNode
{
    point start;
    point end;
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
}seg[100];


point xsort[200],scat[200] = {
    {8, 4,0}, {10, 11,0},
    {9,19,1}, {14, 16,1},
    {2, 4,2}, {7,  10,2},
    {10,2,3}, {19, 6 ,3},
    {3, 7,4}, {12, 9 ,4},
    {6,14,5}, {17, 17,5},
    {12,5,6}, {18, 4 ,6},
    {15,7,7}, {20, 12,7},
    {16,10,8},{21, 5 ,8},
    };

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

// A utility function to get the height of the tree
int height(struct AVLNode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
int min(int a, int b)
{
    return (a < b)? a : b;
}

/* Helper function that allocates a new AVLNode with the given key and
    NULL left and right pointers. */
void newAVLNode(point p1,point p2,int i)
{
    seg[i].start = p1;
    seg[i].end = p2;
    seg[i].key = p1.yc;
    seg[i].left   = NULL;
    seg[i].right  = NULL;
    seg[i].height = 1;  // new AVLNode is initially added at leaf
}

struct AVLNode *rightRotate(struct AVLNode *y)
{
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}


struct AVLNode *leftRotate(struct AVLNode *x)
{
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

int getBalance(struct AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct AVLNode* insert(struct AVLNode* AVLNode, int i)
{
    /* 1.  Perform the normal BST insertion */

    if (AVLNode == NULL){
             printf("inserted::");
        AVLNode = &seg[i];

    }
    if (seg[i].key < AVLNode->key)
        AVLNode->left  = insert(AVLNode->left, i);
    else if (seg[i].key > AVLNode->key)
        AVLNode->right = insert(AVLNode->right, i);
    else // Equal keys are not allowed in BST
        return AVLNode;

    /* 2. Update height of this ancestor AVLNode */
    AVLNode->height = 1 + max(height(AVLNode->left),
                           height(AVLNode->right));

    int balance = getBalance(AVLNode);
    // Left Left Case
    if (balance > 1 && seg[i].key < AVLNode->left->key)
        return rightRotate(AVLNode);

    // Right Right Case
    if (balance < -1 && seg[i].key > AVLNode->right->key)
        return leftRotate(AVLNode);

    // Left Right Case
    if (balance > 1 && seg[i].key > AVLNode->left->key)
    {
        AVLNode->left =  leftRotate(AVLNode->left);
        return rightRotate(AVLNode);
    }

    // Right Left Case
    if (balance < -1 && seg[i].key < AVLNode->right->key)
    {
        AVLNode->right = rightRotate(AVLNode->right);
        return leftRotate(AVLNode);
    }

    /* return the (unchanged) AVLNode pointer */
    return AVLNode;
}
/* Given a non-empty binary search tree, return the
   AVLNode with minimum key value found in that tree.
 */
struct AVLNode * minValueAVLNode(struct AVLNode* AVLNode)
{
    struct AVLNode* current = AVLNode;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
// Recursive function to delete a AVLNode with given key
struct AVLNode* deleteAVLNode(struct AVLNode* root, int i)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( seg[i].key < root->key )
        root->left = deleteAVLNode(root->left, i);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( seg[i].key > root->key )
        root->right = deleteAVLNode(root->right, i);

    // if key is same as root's key, then This is
    // the AVLNode to be deleted
    else
    {
        // AVLNode with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct AVLNode *temp = root->left ? root->left :
                                             root->right;

            // No child case
            if (temp == NULL)
            {
                root = NULL;
            }
            else // One child case
            *root = *temp;
            // Copy the contents of the non-empty child
            temp=NULL;
        }
        else
        {
            // AVLNode with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct AVLNode* temp = minValueAVLNode(root->right);

            // Copy the inorder successor's data to this AVLNode
            root->start = temp->start;
            root->end = temp->end;
            root->key = temp->key;
           // printf(" INOS ::%d\n",temp->key);
            // Delete the inorder successor
            root->right = deleteAVLNode(root->right, temp->start.ptr);
        }
    }

    // If the tree had only one AVLNode then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT AVLNode
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS AVLNode (to
    // check whether this AVLNode became unbalanced)
    int balance = getBalance(root);

    // If this AVLNode becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
int onSegment(point *p, point *q, point *r)
{
    if (q->xc <= max(p->xc, r->xc) && q->xc >= min(p->xc, r->xc) &&
        q->yc <= max(p->yc, r->yc) && q->yc >= min(p->yc, r->yc))
       return 1;

    return 0;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(point *p, point *q, point *r)
{

    //printPoint(r);
    int val = ((q->yc - p->yc) * (r->xc - q->xc) -
              (q->xc - p->xc) * (r->yc - q->yc));
    //printf("val ::%d\n",val);
    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
int intersect(struct AVLNode* a,struct AVLNode* b)
{
    point *p1,*p2,*q1,*q2;
    if(b==NULL||a==NULL){
        printf("only one line available");
        return 0;
    }
    p1 = &(a->start);
    q1 = &(a->end);
    p2 = &(b->start);
    q2 = &(b->end);

     printf("\nintersecting::");
     /*   printPoint(p1);
           printPoint(q1);
              printPoint(p2);
                 printPoint(q2);
    */
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
      printf("checked Orientation::");
    // General case
    if (o1 != o2 && o3 != o4)
        return 1;

    // Special Cases
    // p1, p2 and p3 are colinear and p3 lies on segment p1p2
    if (o1 == 0 && onSegment(p1, p2, q1)) return 1;
    if (o2 == 0 && onSegment(p1, q2, q1)) return 1;
    if (o3 == 0 && onSegment(p2, p1, q2)) return 1;
    if (o4 == 0 && onSegment(p2, q1, q2)) return 1;
     printf(" NOT Intersected::");
    return 0;
}

struct AVLNode* pred(struct AVLNode *node){
    if(node==NULL||node->left==NULL)
        return NULL;
    else {
        node=node->left;
        while(node->right!=NULL){
            node = node->right;
        }
        return node;
    }
}
struct AVLNode* succ(struct AVLNode *node){
   if(node==NULL||node->right==NULL)
        return NULL;
    else {
        node=node->right;
        while(node->left!=NULL){
            node = node->left;
        }
        return node;
    }
}

int isleft(int i){
    int loc = scat[i].ptr;
    // printf(":loc %d %d:\n",scat[i],seg[loc].start.yc);
    if(seg[loc].start.xc==scat[i].xc && seg[loc].start.yc==scat[i].yc )
            return 1;
    else
        return 0;
}
int isright(int i){
    int loc = scat[i].ptr;
    //  printf(":loc %d %d:\n",scat[i],seg[loc].end.yc);
    if(seg[loc].end.xc==scat[i].xc && seg[loc].end.yc==scat[i].yc)
            return 1;
    else
        return 0;
}

void printPoint(point *p){
  printf("{%d, %d} (%d)\n",p->xc,p->yc,p->ptr );
}
void preOrder(struct AVLNode *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/*Segments for reference :: {
    {8, 4,0},{12, 5,0},
    {9, 19,1},{14, 16,1},
    {2, 4,2},{8, 9,2},
    {10, 2,3},{19, 6,3},
    {3, 7,4},{12, 9,4},
    {6, 14,5},{17, 17,5},
    {15, 10,6},{18, 4,6}};
*/
int main()
{
  struct AVLNode *root = NULL;
  int size = 9,i,j,count;

   for(i=0;i<=2*size-1;i++){
    printPoint(&scat[i]);
  }
  j=0;
  for(i=0;i<=size-1;i++){
    newAVLNode(scat[2*i],scat[2*i+1],i);
  }

  printf("\n::SORTED::\n");
  sort(0, size*2-1);
  //printf("**%d**%\n",scat[1].ptr);
  for(i=0;i<=2*size-1;i++){
    printPoint(&scat[i]);
  }

  count =0;
  for(i=0;i<=size*2-1;i++){
         //printf("left::%d",isleft(i));
         //printf("right::%d",isright(i));
         int loc = scat[i].ptr;
    if(isleft(i))
    {
        printf("\n:leftloc %d %d:\n",scat[i].xc,scat[i].yc);
        root = insert(root,scat[i].ptr);
        //printPoint(&(root->start));
        //check intersection with succesor
        if(intersect(root,succ(root)))
        {
            printf(" lines segments ::%d %d\n",root->start.ptr,root->right->start.ptr);

        }

        //check intersection with predecessor
        if(intersect(root,pred(root)))
         {
           printf(" lines segments ::%d %d\n",root->start.ptr,root->left->start.ptr);

         }
          //   printf("No. of Intersections : %d\n",count);
    }
    else
    if(isright(i))
    {
        printf("\n:rightloc %d %d:\n",scat[i].xc,scat[i].yc);
        if(intersect(pred(root),succ(root)))
         {
             printf(" lines segments ::%d %d\n",root->left->start.ptr,root->right->start.ptr);

         }

         if(root->left!=NULL || root->right==NULL)
         {
              if(intersect(root,root->left))
              {
               printf(" lines segments ::%d %d\n",root->start.ptr,root->left->start.ptr);
              }
         /*}
         if(root->left==NULL && root->right!=NULL)
         {
          */ if(intersect(root,root->right))
             {
                printf(" lines segments ::%d %d\n",root->start.ptr,root->right->start.ptr);

             }
         }

        root = deleteAVLNode(root,scat[i].ptr);
        //  printf("No. of Intersections : %d\n",count);
    }
    printf("\n predorder::");
    preOrder(root);
  }
   // printf("No. of Intersections : %d\n",count);

  return 0;
}
