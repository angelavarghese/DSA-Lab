#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10000

unsigned int hash(const char*key){
    unsigned long int value = 0; 
    unsigned int i = 0;
    unsigned int key_len = strlen(key);
    
    for(; i < key_len; i++){
        value = value*37 + key[i];
    }
    value = value % TABLE_SIZE;

    return value;
}

int main(int argc, char ** argv){

    return 0;
}
