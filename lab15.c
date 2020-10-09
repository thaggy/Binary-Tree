#include "lab15.h"

Employee ** readRecord(FILE * fp)
{
    //creating temp pointer that will be returned to calling program as the array of employees
    Employee ** temp;
    //Creating a number that will be the number of elements in the array which is stored in the very first slot of the CSV file but since we have not read the file yet, the numElems is 0
    int numElems=0;
    
    //Testing if the File is NULL just in case
    if(!fp)
    {
        printf("The file doesn't exist! Returning NULL\n");
        return NULL;
    }
    //Since the file is not NULL, we read the first element of the file to find the total number of students
    fscanf(fp,"%d",&numElems);
    //Creating the array based on the number found
    temp = (Employee **)malloc(numElems*sizeof(Employee*));
    //Incase the malloc fails we return NULL
    if(!temp)
    {
        printf("Malloc has failed, returning NULL\n");
        return NULL;
    }
    //Now based on the numElems, we malloc each item of the temp array so that the structures can store memory
    for(int i=0;i<numElems;i++)
    {
        temp[i] = (Employee *)malloc(sizeof(Employee));
        //If malloc fails at some point, we don't want to return a broken array so we return NULL
        if(!temp[i])
        {
            printf("Malloc has failed return NULL\n");
            return NULL;
        }
    }
    //Getting Every employee data into array by a simple for loop with a fscanf based on the numElems
    for(int i=0;i<numElems;i++)
    {
        fscanf(fp,"%d,%f,%d\n",&temp[i]->ID,&temp[i]->salary,&temp[i]->ssn);
    }
    //Return the array
    return temp;
}
int comparison(void * a,void * b)
{
    //We create two pointers two employee structs
    Employee * AComp;
    Employee * BComp;
    //We then set the comparison structs equal to a and b so that we can compare the contents of A and B
    AComp = a;
    BComp = b;
    //Case 1: The first comparison is larger than the second, we return 1
    if(AComp->ssn > BComp->ssn)
    {
        return 1;
    }
    //Case 2 : The second comparison is larger, we return -1;
    else if(AComp->ssn < BComp->ssn)
    {
        return -1;
    }
    //Case 3: Neither is true and they are equal, then we return 0
    return 0;
}
Node * insertBST(Node * tree, Employee * insert)
{
    //If there is no tree data at the present location, we return a node created based on insert
    if(!tree)
    {
        Node * temp = (Node *)malloc(sizeof(Node));
        temp->data = insert;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    //We create an integer that will be used to show the result of the comparison function
    int compare = comparison((void*)tree->data,(void*)insert);
    //We use 2 if statements to cover the three possibilities of the comparison function
    //Case 1 : the comparison functon returns 1
    if(compare == 1)
    {
        //This means that the desired insertion is smaller than the current node, so we go to a smaller node, and since this tree is in descending order, that means to the right
        tree->right = insertBST(tree->right, insert);
    }
    //Case 2 : The comparison function returns -1
    else if(compare == -1)
    {
        //In this case; That means that the desired insertion is greater than the current tree position, in which case we go to the left and insert there because it is in descending order
        tree->left = insertBST(tree->left, insert);
    }
    //If it is equal, that means that the desired insertion is already there, so we can just return tree and no information is lost
    return tree;
}
Employee* searchBST(Node * root,int search)
{
    //If the root becomes NULL, that means that search went to a branch that is NULL so no search was found
    if(root==NULL)
    {
        printf("%d was not in the BST, returning NULL\n",search);
        return NULL;
    }
    if(root->data->ssn == search)
    {
        //If the ssn is equal to the search, then the data was found
        printf("%d is in the node\n",search);
        //We then return the data to the main function
        return root->data;
    }
    else if(root->data->ssn > search)
    {
        //If the root data is bigger than the search, we go right because it is in descending order
        return searchBST(root->right, search);
    }
    else if(root->data->ssn < search)
    {
        //If the root data is smaller than the search, we go left because it is in descending order
        return searchBST(root->left, search);
    }
    //If none of the conditions are somehow met, then that means that the search is not found in the BST so we return NULL
    printf("%d was not found in the BST, returning NULL\n",search);
    return NULL;
}
void deleteTree(Node * tree)
{
    //If there is no memory, then we return, this will make it so we do not access into bad memory and since we return, we will go back to another function because of the recursion
    if(!tree)
    {
        return;
    }
    //We need to go down all left options first
    deleteTree(tree->left);
    //And then we will go down all right options, and because of how recursion works and since we also went down all left options, we will go down all possible options
    deleteTree(tree->right);
    //we free the memory at each option with the free function here, because it is called recursively, this will free every node
    free(tree);
    //Printing where we freed the memory so the user knows each pointer being freed is unique
    printf("Freed memory at %p\n",tree);

}
