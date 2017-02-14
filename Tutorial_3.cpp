#include <iostream>
#include<stdio.h>
#include<stdlib.h>
// #include <conio.h>
using namespace std;
 
struct Range                       // interval representing node
{
    int lower , higher;
};
 
struct Node
{
    Range *i;  
    int max;
    Node *left, *right;    //  self referencial structure.
};
 
Node * newNode(Range i)        // function to create new node.
{
    Node *temp = new Node;
    temp->i = new Range(i);
    temp->max = i.higher;
    temp->left = temp->right = NULL;
};

Node *insert(Node *root, Range i)
{
    if (root == NULL)
        return newNode(i);
 
    // Get low value of Range at root
    int l = root->i->lower;
 
    if (i.lower < l)
        root->left = insert(root->left, i);    // recursive call to insert to the left.
 
    else
        root->right = insert(root->right, i);  // recursive call to insert to the right.
 
    if (root->max < i.higher)
        root->max = i.higher;          // updating max value of root node.
 
    return root;
}
 
// A utility function to check if given two Ranges overlap
bool doOVerlap(Range i1, Range i2)
{
    if (i1.lower <= i2.higher && i2.lower <= i1.higher)
        return true;
    else    
   		return false;
}

struct Node * minimumNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}


Node* deleteNode(Node* root, Range x)
{
    if (root == NULL) return root;
 
    if (x.lower < root->i->lower)                  //checking range for left part.
        root->left = deleteNode(root->left, x);
 
    else if (x.lower > root->i->lower)          // checking range for right part.
        root->right = deleteNode(root->right, x);
 
    else                                        // root is desired node.
    {
        if (root->left == NULL)                // root having one child i.e right.
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)         // root having one child i.e left
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
 
        struct Node* temp = minimumNode(root->right);    // root having two child.

        root->i->lower = temp->i->lower;
 
        root->right = deleteNode(root->right, x);
     
    }

    return root;
}
/*
Range *Search(Node *root, Range i) 
{
	if (root == NULL)         // if tree is empty.
		return NULL; 
	
	if (root->i->lower == i.lower && root->i->higher == i.higher)
		return root->i; 
		
	if(root->i->lower > i.lower)
	    return Search(root->left, i);
	
	if(root->i->lower < i.lower)
	    return Search(root->right, i);	
		else 
		return NULL;	
}
*/ 
Range *overlapSearch(Node *root, Range i)   //function to search for range.
{
    
    if (root == NULL)         // if tree is empty.
		return NULL; 
 
    
    if (doOVerlap(*(root->i), i))     // if Range overlaps with root.
        return root->i;
 
    if (root->left != NULL && root->left->max >= i.lower)   //if left child of root is present & 
   		                                                   // max(left)>= Range.lower
        return overlapSearch(root->left, i);
 
    return overlapSearch(root->right, i);
}
 
void display(Node *root)    // display output of tree
{
    if (root == NULL) return;
 
    display(root->left);
 
    cout << root->i->lower << ", " << root->i->higher << " and max = " << root->max << endl;
 
    display(root->right);
}
 
int main()
{
    Range arr[] = { {15, 20}, {10, 30}, {17, 19},{5, 20}, {12, 15}, {30, 40} };
    int n = sizeof(arr)/sizeof(arr[0]);
    Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);
 
    cout << "Present tree is\n";
    display(root);
	//	cout<< "deleted node is "<< delnode->i->lower << " ,"<< delnode->i->higher ;  
	// cout << "Present Tree is\n";
   // display(root);
    Range x ;
    cout<<"input the range to check"<<endl;
    cin>> x.lower >> x.higher ;
    cout << "\nchecking " << x.lower << "," << x.higher ;
    Range *res = overlapSearch(root, x);
   // Range *res = Search(root, x);
    if (res == NULL)
        cout << "\nGiven range dont overlap ";
    else
        cout << "\nGiven range overlap with " << res->lower << ", " << res->higher ;
    
    Range x1 ;
    cout<<"\ninput the range to delete"<<endl;
    cin>> x1.lower >> x1.higher ;
    deleteNode(root, x1);
   // maxadjust(root,x1);
    display(root);
    
    //Node *delnode = NULL;    
     
    return 0;
}
