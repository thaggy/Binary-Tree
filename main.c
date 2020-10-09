#include <stdio.h>
#include "lab15.h"
int main(void)
{
    FILE * fp = fopen("employee.csv","r");
    Employee ** array = readRecord(fp);
    for(int i=0; i<10000;i++)
    {
        printf("%d %f %d\n",array[i]->ID,array[i]->salary,array[i]->ssn);
    }
    Node * root = NULL;
    root = insertBST(root, array[4]);
    root = insertBST(root, array[6]);
    root = insertBST(root, array[5]);
    root = insertBST(root, array[2]);
    root = insertBST(root, array[1]);
    printf("root = %d\n",root->left->right->data->ssn);
    
    searchBST(root, array[1]->ssn);
    
    deleteTree(root);
}
