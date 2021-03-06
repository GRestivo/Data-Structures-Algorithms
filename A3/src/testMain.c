#include <stdio.h>
#include <string.h>

#include "hashData.h"
#include "hashFunction.h"
#include "HashTableAPI.h"

int main (int argc, char **argv) {
  int i;
  char word[100];

  char **testString = malloc(sizeof(char*) * 20);
  for (i = 0; i < 20; i++) {
    testString = malloc(sizeof(char) * 50);
  }
  i = 0;

  /*This is the test main*/
  printf("|||||BEGIN TESTING|||||\n\n");

/*||||||||||||||||||||||||||||||||||||||||||||||||||*/
  printf("BEGIN TESTING FOR CREATETABLE\n");
  printf("Testing with NULL input values for function pointer parameters\n");
  /*HTable *nullHashTable = createTable(26,NULL,NULL,NULL);*/
  printf("Function will fail program attempts to use the function pointers!\n");
  printf("Testing with proper function pointers.\n");
  HTable *hashTable = createTable(26, &hashNode, &destroyNodeData,&printKeyData);
  printf("If returned hash table = NULL print 'NULL' on next line, else print 'Exists'\n");
  if (hashTable == NULL) {
    printf("NULL\n");
  } else {
    printf("Exists\n");
  }
  printf("TESTING SUCCESSFUL\n\n");

/*|||||||||||||||||||||||||||||||||||||||||||||||||*/
  printf("BEGIN TESTING FOR INSERTDATA\n");
  printf("Test by adding a value while no values are in the table.\n");

  testString[i] = "InsertTest1";
  HashData *d = createHashData(testString[i], hashTable->hashFunction(hashTable->size, testString[i]));
  insertData(hashTable, d->key, d);
  i++;
  printf("Displaying table: \n");
  printHashTable(hashTable);
  printf("Test by adding a value when values already exist in the table.\n");
  testString[i] = "InsertTest2";
  d = createHashData(testString[i], hashTable->hashFunction(hashTable->size, testString[i]));
  insertData(hashTable, d->key, d);
  i++;
  printf("Displaying table:\n");
  printHashTable(hashTable);
  printf("Testing by sending function a non pointer for the data.\n");
  /*hashData *h = createHashData("heyall",6);*/
  printf("This test causes a segmentation fault!\n");
  printf("TESTING SUCCESSFUL\n\n");

/*|||||||||||||||||||||||||||||||||||||||||||||*/
  printf("BEGIN TESTING FOR LOOKUPDATA\n");
  printf("Testing with trying to find data that exists (InsertTest1)\n");
  testString[i] = "InsertTest1";
  d = createHashData(testString[i],hashTable->hashFunction(hashTable->size, testString[i]));
  d = findData(hashTable, d);
  i++;
  printf("Returned result: %d | %s\n", d->key, d->word);
  printf("Testing with trying to find data that does not exist(InsertTest3)\n");
  printf("Returned result: \n");
  testString[i] = "InsertTest3";
  d = createHashData(testString[i], hashTable->hashFunction(hashTable->size, testString[i]));
  d = findData(hashTable, d);
  i++;
  if (d == NULL) {
    printf("No data found.\n");
  }
  printf("TESTING SUCCESSFUL\n\n");

  printf("Inserting new data ('InsertTest3' & 'Test4')\n");
  testString[i] = "Test4";
  d = createHashData(testString[i],hashTable->hashFunction(hashTable->size, testString[i]));
  insertData(hashTable, d->key, d);
  i++;
  testString[i] = "InsertTest3";
  d = createHashData(testString[i],hashTable->hashFunction(hashTable->size, testString[i]));
  insertData(hashTable, d->key, d);
  i++;

/*|||||||||||||||||||||||||||||||||||||||||||||*/
  printf("BEGIN TESTING FOR REMOVENODE\n");
  printf("Should remove specific node data\n");
  printf("List before removal:\n");
  printHashTable(hashTable);
  printf("List after removing 'InsertTest3'");
  removeNode(hashTable, d);
  printHashTable(hashTable);
  printf("Testing removing a value that does not exist (InsertTest4)\n");
  strcpy(word, "InsertTest4");
  testString[i] = word;
  d = createHashData(testString[i], hashTable->hashFunction(hashTable->size, testString[i]));
  removeNode(hashTable, d);
  i++;
  printf("List after test: \n");
  printHashTable(hashTable);
  printf("Does nothing because value does not exist\n");
  printf("TESTING SUCCESSFUL\n\n");

/*|||||||||||||||||||||||||||||||||||||||||||||||*/
  printf("BEGIN TESTING FOR REMOVEKEYDATA\n");
  printf("Testing by removing whole list at index %d (letters that start with 'i')\n", d->key);
  removeKeyData(hashTable, d->key);
  printf("Hash table after removal: \n");
  printHashTable(hashTable);
  printf("Testing by removing whole list of index that has no values\n");
  removeKeyData(hashTable, 0);
  printf("Displaying table after removal of non existing value: \n");
  printHashTable(hashTable);
  printf("Nothing changed.\n");

  printf("TESTING SUCCESSFUL\n\n");

/*|||||||||||||||||||||||||||||||||||||||||||||||*/
  printf("BEGIN TESTING FOR DESTROYTABLE\n");
  printf("Table before destruction:\n");
  printHashTable(hashTable);
  printf("Table after destruction: \n");
  destroyTable(hashTable);
  /*printHashTable(hashTable);*/
  printf("Nothing is displayed because hash table no long exists");
  printf("TESTING SUCCESSFUL\n\n");

  printf("|||||TESTING COMPLETE|||||\n");

return 0;
}
