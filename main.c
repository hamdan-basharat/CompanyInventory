/* *******************************************************
HamdanBasharat_400124515_Oct31st2018_Lab3_Variant2_Q1
******************************************************* */
#include <stdio.h>
#include <stdlib.h>
typedef struct{ //structure that holds all the variables for item objects
    int itemID; //the ID of the item in the inventory
    char itemname[25]; //array for the item name that can be up to 25 characters long
    float price; //the price of the item
    int number; //the number of all articles with a certain ID
}item;

item **create_items_list(int *noP){ //function to allocate the memory necessary to store the list of items
    printf("Enter the number of items in the inventory: ");
    scanf("%d", &(*noP)); //sets the first integer entered as the number of items
    item **inventory=calloc(*noP, sizeof(item*)); //allocates memory for the list
    printf("Enter the information of the items (ID Name Price Quantity): \n");
    for(int i=0;i<(*noP);i++){ //runs for the number of items
        inventory[i]=(item*)malloc(sizeof(item)); //allocates memory for the individual items in the list
        scanf("%d %s %f %d", &inventory[i]->itemID, &inventory[i]->itemname, &inventory[i]->price, &inventory[i]->number); //assigns the input information to the variable of the list indice
    }
    return inventory;
}

void print_list(item **list, int number){ //prints the inventory list
    for(int i=0;i<number;i++){ //runs for the number of items
        printf("ID: %d; item name: %s; price: %0.1f; number of articles in this category: %d\n", list[i]->itemID, list[i]->itemname, list[i]->price, list[i]->number); //prints by calling the pointers of from the object
    }
}

void remove_item(int idNo, item **list, int *noP){ //removes an item from the inventory
    int flag=0;
    for(int i=0;i<*noP;i++){ //checks to see if the ID number exists in the inventory
        if(list[i]->itemID==idNo){
            flag=1; //if it exists it is flagged
        }
        else{continue;}
    }
    if(flag==0){
        printf("\nThe item with ID %d is not in the inventory.\n", idNo); //if the ID number wasnt flagged, the user is told the item does not exist
    }
    else{
        if(idNo==(*noP-1)){ //if the ID number is in the last index it is deleted without having to shift the other indices
            free(list[idNo]); //memory for that indice is freed
            (*noP)--; //number of items is decremented
        }
        else{
            for(int i=idNo;i<(*noP-1);i++){ //all the variables from the object are shifted left by assigning their values from the indice on their right
                list[i]->itemID=list[i+1]->itemID;
                list[i]->number=list[i+1]->number;
                list[i]->price=list[i+1]->price;
                for(int j=0;j<25;j++){ //the characters from the name are shifted left
                    (list[i]->itemname)[j]=(list[i+1]->itemname)[j];
                }
            }
            free(list[(*noP-1)]); //memory for the last indice is freed
            (*noP)--; //number of items is decremented
        }
    }
    flag=0;
}

void deallocate_list(item **list, int *noP){ //frees the memory used by the array of pointers
    for(int i=0;i<(*noP);i++){
        free(list[i]); //frees the memory from each individual indice
    }
    *noP=0; //sets the number of items to zero
    free(list); //frees the memory used by the list
}

int main()
{
    int n; //to store the number of items in the list
    item **itemsList=create_items_list(&n); //creates the list
    printf("\nThe company has %d items in its inventory.\n\n", n);
    //series of function calls to test all the methods
    print_list(itemsList, n);
    remove_item(55, itemsList, &n);
    remove_item(45, itemsList, &n);
    printf("\nThe item with ID: %d was removed from the inventory.\n", 45);
    print_list(itemsList, n);
    deallocate_list(itemsList, &n);
    printf("\nThe inventory memory was deallocated.\n");
    printf("The company has %d items in its inventory.\n", n);
    return 0;
}//end of main
