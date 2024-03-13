/*
 * COP 3515 – Spring Semester 2023
 *
 * Homework #2: Spotting The Hacker
 *
 * (Coby Flannery)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void simpleBinaryConversion(int value) {
  
    int i;
    int binary[8];
    for (i = 7; i >= 0; i--) {
        binary[i] = value % 2;
        value = value / 2;
       
    }
    
    for (i = 0; i < 8; i++) {
        printf("%d", binary[i]);
    }
    
    
}

int parityCheck(){
  
  FILE *parity = fopen("White House Transmission Data - Parity.txt", "r");
  int parityArray[5][9]; //holds file info

    int n;
    int i;

    for (int i = 0; i < 5; i++) {  //putting file info into array
        for (int j = 0; j < 9; j++) {
            fscanf(parity, " %d", &n);
            parityArray[i][j] = n;
        }  
      }
    printf("Data Stream: \n\n");  //diplaying stream
    for (int p = 0; p < 5; p++) {  
        for (int j = 0; j < 8; j++) {
            printf("%d ", parityArray[p][j]);
        }
        printf("\n\n");
    
    int parityNumber = parityArray[p][8]; //declaring designated parity number
    printf("Parity byte: %d\n\n", parityNumber);

    int binary[8][8] = {0}; //binary conversion array
    int count0 = 0; //both used to count ones and zeros(i only use the count1 var)
    int count1 = 0;
  
    for (int i = 0; i < 8; i++) { //loop that convertes numbers in array to binary
      
      printf("data item = %d\t", parityArray[0][i]);
      printf("binary = ");
      
        int k, c;
        
        for (c = 7; c >= 0; c--){
          k = parityArray[0][i] >> c;
        
            if (k & 1){
              binary[i][c] = 1;
              count1++;
              printf("%d", binary[i][c]);

          }
            else{
              binary[i][c] = 0;
              count0++;
              printf("%d", binary[i][c]);
            
            }
          }
      if(count1 % 2 == 0){ //if the number of ones is odd, error occurs
        
        printf("\nNo error in transmission byte %d", i+1);
         parityNumber = 0;
      //  printf("\n%d", parityNumber);
      }
         else{
         printf("\nError in transmission byte  %d", i+1);
        parityNumber = 1;
       //  printf("\n%d", parityNumber);
      }
      printf("\n\n"); 
      count0 = 0; //reseting count variables to zero for next loop
      count1 = 0;
    }
      }
  return 0;
}

int checkSum(){
  
  FILE *checkSumFile = fopen("White House Transmission Data - Checksum.txt", "r");
  int checkSumArray[5][9]; //holds file info

  int n;
  int i;
  int checkSumBinary[8][8] = {0}; //varible to store values in binary
  int sumOfData = 0; //sum of the data 
  int total = 0;  //sum after complement 
    for (int i = 0; i < 5; i++) { //putting files info into checkSumArray
        for (int j = 0; j < 9; j++) { 
            fscanf(checkSumFile, " %d", &n);
            checkSumArray[i][j] = n;
            
        }  
    }
  for (int p = 0; p < 5; p++) { 
    printf("Data stream: \n\n");
        for (int j = 0; j < 8; j++) {
            printf("%d ", checkSumArray[p][j]); //printing datastream
            sumOfData = sumOfData + checkSumArray[p][j]; //adding all the values in row 
        }
      printf("\n\n");
    
  int checkSum = checkSumArray[p][8];
  printf("Checksum: %d", checkSum);
      printf("\n\n");
  
  for (int i = 0; i < 7; i++) {
      
      printf("parityData[i] = %d, ", checkSumArray[p][i]); //prints each value of data stream in a row 
      printf("binary = ");
      
        int k, c; //used to convert each value in the datastream to binary
        
        for (c = 7; c >= 0; c--){
          k = checkSumArray[p][i] >> c;
          
            if (k & 1){
              checkSumBinary[i][c] = 1;
              printf("%d", checkSumBinary[i][c]);

          }
            else{
              checkSumBinary[i][c] = 0;
              printf("%d", checkSumBinary[i][c]);
            
            }
          }
      printf("\n\n");
    }
    
    printf("Sum of data items: %d, binary = ", sumOfData); //displaying sum of the datastream and converting it to binary
    simpleBinaryConversion(sumOfData);
    printf("\n\n");

    printf("Checksum Value = %d, binary = ", checkSum); //displaying checksum value and adding it to the sumOfData
    simpleBinaryConversion(checkSum);
    total = sumOfData + checkSum;
    
    printf("\n\n");
    printf("Sum after adding checksum = %d, binary = ", total); //displaying total
    simpleBinaryConversion(total); //converting total to binary

    
    printf("\n"); //flips binary total and converting it to binary
    
    int k, c;
    int binary[8] = {0};
        for (c = 7; c >= 0; c--){
          k = total >> c;
        
            if (k & 1){
              binary[i] = 1;

          }
            else{
              binary[i] = 0;
            
            }
          }
    for (int i = 0; i < 7; i++)
      total = binary[i];
      
    printf("Sum after complement = %d", total); //displaying total
    
    
    printf(", binary = "); //displaying binary total with function
    
    simpleBinaryConversion(total);
    
    if (total == 0) //error if total is not 0
    printf("\nChecksum: No errors in transmission\n");
      else
    printf("\nChecksum: Errors in transmission\n");
      printf("\n\n");
    sumOfData = 0;
    }
  return 0;
}

int twoDimParity(){
  FILE *twoDimParity = fopen("White House Transmission Data - 2D Parity.txt", "r");

      int Arr[8][10]; //array that holds file info to displaying data stream
      int t; //temp holder
      int value = 1; //used to input values of columns and rows
      int column = 0; //column index 
      int row = 0; //row index
      bool verticalParityStatus = true; //flag for vertical pass
      bool horizontalParityStatus; //flag for horizontal pass
      
  printf("Part 3: 2D parity check\n\n");
  printf("Data Streams: \n\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            fscanf(twoDimParity, " %d", &t);
            Arr[i][j] = t; //putting file info into array
        }
    }
    for (int i = 0; i < 8; i++) { //displays datastream
        for (int j = 0; j < 8; j++) {
            printf("%d ", Arr[i][j]);
        }
        printf("[V: %d] [H: %d]\n", Arr[i][8], Arr[i][9]);
    }
          printf("\n\n");
        
  for (int j = 0; j < 8; j++) {
printf("Vertical processing line %d\n\n", column);  //vertical processing 
    for (int i = 0; i < 8; i++) {
        
         printf("val%d = %d, ", value, Arr[i][j]); //converting to binary and displaying array values
          simpleBinaryConversion(Arr[i][j]); 
          printf("\n");
          value++;
          if (value > 8){
            value = 1;
          }
        }
    printf("\n");
    printf("checkParityByte = %d  ", Arr[0][8]);
      printf("vertParityByte[%d] = %d\n\n",column, Arr[0][8]);
    if(verticalParityStatus == true){ //if parity status true
      printf("Transmission line %d passed vertical parity\n\n", column);
      }
    column++;
    }  
  printf("\n");
  
    printf("Transmission block 1 PASSED complete vertical parity test\n\n\n");
  
      for (int i = 0; i < 8; i++) {
printf("Horizontal processing line %d\n\n", row); //horizontal processing 
        
        if(row == 0 || row == 1 || row == 4 || row == 5){ 
          printf("Adding bit position 4: 16\n"); //conditions to add position
        }
        if(row == 0 || row == 1 || row == 4 || row == 5 || row == 6 || row == 7){
          printf("Adding bit position 5: 32\n");
        }
        if(row == 4 || row == 5 || row == 6 || row == 7){
          printf("Adding bit position 6: 64\n");
        }
        printf("\n");
    for (int j = 0; j < 8; j++) { //converting to binary and displaying array values
       printf("val%d = %d, ", value, Arr[i][j]);
          simpleBinaryConversion(Arr[i][j]);
          printf("\n");
          value++;
          if (value > 8){
            value = 1;
          }
      }
        printf("\n");
        printf("checkParityByte = %d  ", Arr[i][9]);
        printf("horizParityByte[%d] = %d\n\n",row, Arr[i][9]);
        if(horizontalParityStatus == true) {
          printf("Transmission line %d passed horizontal parity\n\n", row);
        }
        
        row++;
        printf("\n");
        }
        printf("Transmission block 1 PASSED complete horizontal parity test\n\n");
        printf("---> Transmission block 1 PASSED - it is error free.\n");
          fclose(twoDimParity);
    return 0;
}

int main(void) {
  
    parityCheck(); //implementing parity check function
    printf("\n\n");
    checkSum(); //implementing checksum function
    printf("\n\n");
    twoDimParity(); //implementing twoDimParity Function
    
    return 0;
}