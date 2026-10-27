// https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm
#include "hashmap.h"

struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;

int hashCode (char key){
    return key % SIZE;
}

struct DataItem *search(int key){
    //get the hash 
    int hashIndex = hashCode(key);

    // move in array until empty
    
    while(hashArray[hashIndex] != NULL){
        if (hashArray[hashIndex]->key == key )
            return hashArray[hashIndex];

        // go to next cell
        ++hashIndex;

        // wrap around the table 
        hashIndex %= SIZE;

    }
    assert(hashArray[hashIndex] != NULL  && "ERROR : Not found in hashmap\n");

    return NULL;
}

void insert(int key, char *data){
    struct DataItem *item = (struct DataItem*)malloc(sizeof(struct DataItem));
    item->data = data;
    item->key = key;

    // get the hash 
    int hashIndex = hashCode(key);

    // move in array until an empty or deleted cell 
    while (hashArray[hashIndex] != NULL && hashArray[hashIndex] ->key != -1){
        // go to cell 
        ++ hashIndex;

        // wrap arounf the table 
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}


struct DataItem *delete(struct DataItem *item){
    int key = item->key;

    // get the hash 
    int hashIndex = hashCode(key);

    //move i array until an empty 
    while(hashArray[hashIndex] != NULL){
        if (hashArray[hashIndex]->key == key){
            struct DataItem *temp = hashArray[hashIndex];
            // assign a dummy item at deleted position 
            hashArray[hashIndex] = dummyItem;
            return temp;
        }
        // go to cell 
        ++hashIndex;
        // wrap around the table 
        hashIndex %= SIZE;

    }
    return NULL;
}

void display(){
    // int i = 0;
    for (int i = 0; i < SIZE ; i++){
        if (hashArray[i] != NULL )
            printf("(%c,%s)",hashArray[i]->key,hashArray[i]->data);
        else 
            printf(" ~~ ");
    }
    printf("\n");
}
