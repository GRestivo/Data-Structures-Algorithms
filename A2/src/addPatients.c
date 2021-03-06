#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "addPatients.h"
#include "patient.h"
#include "PQueueAPI.h"

int originalPatients (FILE *fPtr, Queue *q) {
  char tempArray[100];
  char *clientID;
  char *symptom;
  int priority = 0;
  int processTime = 0;
  int entryPlace = 0;
  Patient *p;

  /*Reads in file line by line until the end of the file*/
  while (fgets(tempArray, 100, fPtr) != NULL) {
    clientID = malloc(sizeof(char) * 30);
    symptom = malloc(sizeof(char) * 2);
    sscanf(tempArray, "%s %d %s", clientID, &priority, symptom);/*Parses into seperate values*/

    /*if-else statements to designate process times*/
    if (strcmp(symptom, "CV") == 0 || strcmp(symptom, "MH") == 0 || strcmp(symptom, "NC") == 0) {
      processTime = 5;
    }
    else if (strcmp(symptom, "GI") == 0 || strcmp(symptom, "SK") == 0) {
      processTime = 2;
    }
    else if (strcmp(symptom, "RC") == 0 || strcmp(symptom, "EC") == 0) {
      processTime = 1;
    }
    else if (strcmp(symptom, "HN") == 0) {
      processTime = 3;
    }
    else if (strcmp(symptom, "EV") == 0) {
      processTime = 10;
    }
    else if (strcmp(symptom, "SA") == 0) {
      processTime = 7;
    }
    else if (strcmp(symptom, "TR") == 0) {
      processTime = 4;
    }
    entryPlace++;
    p = createPatient(clientID, priority, symptom, processTime, entryPlace);
    insertSortedQ(q, p);/*inserts new patient into queue*/
  }

return entryPlace;
}


int addNewPatient(Queue *q, int entryPlace) {
  char tempLine[100];
  char *clientID;
  char *symptom;
  int priority = 0, processTime = 0;
  Patient *p;
  clientID = malloc(sizeof(char) * 100);
  symptom = malloc(sizeof(char) * 100);


  /*statement that accepts and error checks a new client ID*/
  printf("Please input patient ID: ");
  fgets(tempLine, 100, stdin);
  while (strcmp(tempLine, "\n") == 0) {
    printf("Invalid Input! Please enter patient ID: ");
    fgets(tempLine, 100, stdin);
  }
  strncpy(clientID, tempLine, strlen(tempLine) - 1);

  /*Statement that accepts and error checks a new priority level*/
  printf("Please input priority level: ");
  fgets(tempLine, 100, stdin);
  while (true) {
    if (!isdigit(tempLine[0]) || strlen(tempLine) > 2) {
      printf("Invalid input, must be between 1 and 5! Please try again: ");
      fgets(tempLine, 100, stdin);
    } else {
      priority = atoi(tempLine);
      if (priority >=1 && priority <=5) {
        break;
      } else {
        printf("Invalid Number! Please input priority number: ");
        fgets(tempLine, 100, stdin);
      }
    }
  }

  /*Statement that accepts and error checks for a new symptom code and then designates a
  processing time*/
  printf("Please input a valid symptom code: ");
  fgets(symptom, 100, stdin);
  symptom[2] = '\0';
  do {
    if (strcmp(symptom, "CV") == 0 || strcmp(symptom, "MH") == 0 || strcmp(symptom, "NC") == 0) {
        processTime = 5;
     }
    else if (strcmp(symptom, "GI") == 0 || strcmp(symptom, "SK") == 0) {
      processTime = 2;
    }
    else if (strcmp(symptom, "RC") == 0 || strcmp(symptom, "EC") == 0) {
      processTime = 1;
    }
    else if (strcmp(symptom, "HN") == 0) {
      processTime = 3;
    }
    else if (strcmp(symptom, "EV") == 0) {
      processTime = 10;
    }
    else if (strcmp(symptom, "SA") == 0) {
      processTime = 7;
    }
    else if (strcmp(symptom, "TR") == 0) {
      processTime = 4;
    } else {
      printf("Invalid symptom code! Please input again: ");

      fgets(symptom, 100, stdin);
      symptom[2] = '\0';
    }
  } while (processTime == 0);
  entryPlace++;
  p = createPatient(clientID, priority, symptom, processTime, entryPlace);
  insertSortedQ(q,p);/*inserts new user defined patient into queue*/

return entryPlace;
}
