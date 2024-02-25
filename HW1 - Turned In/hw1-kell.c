// **********************************************
// Program1: Temperature calculation
// Course: CS451
// Student Name: Madison Kell
// Instructor: Il-Hyung Cho
// Date of submission: 2/8/23
// Program Description: 
//  -Computing temperature data - Finding the year, average 
//  -coldest month, hottest month, and average temp of each month
//  -from listed year data in a .txt file.
// **********************************************

#include <stdio.h>
#include <stdlib.h>

//struct holding all information for a year 
struct YearData {
   float temps[12]; 
   int year;                     
   float avg;
   int coldestI, hottestI;
};

//declaring functions to find average, coldest, and hottest month
float findAvg(float[]);
int findCold(float[]);
int findHot(float[]);

//pointer for struct
struct YearData* yearList;

//declaring function that finds the average temp of each month for all years
int findTempAvg(struct YearData data[], int numOfYears);

int main(){
    //declaring iterators
    int i, j;
    //storing first line of code to determine how many years are in the file
    int numOfYears;
    //to store year (given before the temperatures)
    int year;
    //creating a char * for the months of the year
    const char *months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    
    //asking user to input file
    char file_name[100];
    printf("Enter temperature file name:");
   
    //scanning the file
    scanf("%s", file_name);
    
    //ensuring the file is valid (got from slides)
    FILE* ptr = fopen(file_name, "r");
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }

    //finding number of years in file
    fscanf(ptr, "%d", &numOfYears); 
     
    //dynamic array using info from slides
    yearList = malloc(numOfYears *(sizeof(struct YearData *)));

    //Printing the header
    printf("%s%12s%22s%16s%20s", "\nYear",  "Average", "Coldest Month", "Hottest Month", "\n==== \t ======= \t ============= \t ============ \n");
    
    //looping through the file however many times that the number of years tells me to
    for(i = 0; i < numOfYears; i++){
        //scanning for the year
        fscanf(ptr, "%d\n", &year);

        //scanning each years temperatures
        for (j = 0; j < 12; j++) {
            fscanf(ptr, "%f", &yearList[i].temps[j]);
        }

        //calling the functions
        yearList[i].year = year;
        yearList[i].avg = findAvg(yearList[i].temps);
        yearList[i].coldestI =  findCold(yearList[i].temps);
        yearList[i].hottestI = findHot(yearList[i].temps);
        
        //printing the results
      printf("%d%10.1f%15s (%.1f)%10s (%.1f)\n", yearList[i].year, yearList[i].avg, months[yearList[i].coldestI], yearList[i].temps[yearList[i].coldestI], months[yearList[i].hottestI], yearList[i].temps[yearList[i].hottestI]);
    }

    //printing title
    printf("\nAverage temperature\n");
    //looping through the months, printing out header
    for(i=0; i<12; i++){
        printf("%s\t ", months[i]);  
    }
    
    //calling final function: calculate the average of each month
    findTempAvg(yearList, numOfYears);
}

//finding the average of temperature of each year
float findAvg(float data[]){
    int i;
    float sum = 0.0;
    for(i=0; i<12; i++){
        sum += data[i];
    }
    return (sum/12);
}

//finding the coldest temperature of each year
int findCold(float data[]){
    int i;
    int min = 0;
    for(i=0; i<12; i++){
        if(data[i] < data[min]){
            min = i;
        }
    }
    return min;
}

//find the hottest temperature of each year
int findHot(float data[]){
    int i;
    int max = 0;
    for(i=0; i<12; i++){
        if(data[i] > data[max]){
            max = i;
        }
    }
    return max;
}

//fnding the average temperature of each month of all years
int findTempAvg(struct YearData data[], int numOfYears){
    int i, j;
    float average[12];
    //ensuring all averages are set to 0
    for(i=0; i<12; i++){
        average[i] = 0;
    }

    //looping through the temperature of each month, of each year
    for(i=0; i<numOfYears; i++){
        for(j=0; j<12; j++){
            average[j] += data[i].temps[j];
        }
    }

    //new line for formatting temp on next line
    printf("\n");

    //printing the result
    for(i=0; i<12; i++){
        printf("%.1f\t ", (average[i]/numOfYears));
    }
 
}
