/**
 *@author Gordon Restivo
 *@student number: 0971067
 *@last date modified: 11/29/2017
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "rule.h"
#include "addRemoveRule.h"
#include "BinarySearchTreeAPI.h"
#include "BSTFunctions.h"
#include "assistantFunctions.h"

int main (int argc, char **argv) {
  FILE *fPtr;
  char tempChoice[100];
  char *keyWord, *response;
  int choice = 0, breakCheck = 0, i = 0;
  Rule *r;

  /*Error test to see if there are the correct number of command line arguments, if not end program*/
  if (argc != 2) {
    printf("Error! Incorrect amount of command line arguments!\n");
    return -1;
  }

  /*Opens given file for reading*/
  fPtr = fopen(argv[1], "r");

  /*Sees if file opening was successful, if not end program*/
  if (fPtr == NULL) {
    printf("Error! Could not find the designated file.\n");
    return -1;
  }


  Tree *theTree = createBinTree(&compare, &deleteBSTNode, &printNode);
  keyWord = malloc (sizeof(char) * 50);
  response = malloc (sizeof(char) * 150);

  /*reads in file line by line and inputs it into the hash table*/
  while (fgets(keyWord, 50, fPtr) != NULL) {
    int length = strlen(keyWord);
    for (i = 0; i < length; i++) {
      if (keyWord[i] == '\n') {
        keyWord[i] = '\0';
      }
    }
    fgets(response, 150, fPtr);
    length = strlen(response);
    for (i = 0; i < length; i++) {
      if (response[i] == '\n') {
        response[i] = '\0';
      }
    }

    r = createRule(keyWord, response);
    r->userRating = 0.5;
    r->systemRating = 0.5;
    r->learningRate = 0.05;

    addToTree(theTree, r);
    keyWord = malloc(sizeof(char) * 50);
    response = malloc(sizeof(char) * 150);
  }

  /*Closes file pointer*/
  fclose(fPtr);

  /*Command loop to give user different dictionary function options*/
  while (true) {
    printf("1) Add a new rule\n");
    printf("2) Remove a rule\n");
    printf("3) Display rules\n");
    printf("4) Modify rule rating\n");
    printf("5) Discuss\n");
    printf("9) Quit\n");
    printf("Input choice: ");
    fgets(tempChoice, 100, stdin);
    tempChoice[1] = '\0';
    if (isdigit(tempChoice[0])) {
      choice = atoi(tempChoice);
      switch(choice) {
        case 1:
          addRule(theTree);
          break;
        case 2:
          removeRule(theTree);
          break;
        case 3:
          printf("Here are the rules: \n\n");
          printInOrder(theTree, NULL);
          printf("\n");
          break;
        case 4:
          modifyRule(theTree);
          break;
        case 5:
          discuss(theTree);
          break;
	      case 9:
	        breakCheck = 1;
	        break;
	      default:
          printf("\nInvalid input! Please try again!\n\n");
	        break;
      }
      if (breakCheck == 1) {
        break;
      }
    } else {
      printf("Invalid input! Must be a number between 1-5, or 9, please try again.\n");
    }
  }

destroyBinTree(theTree);
return 0;
}
