////////////////////////////////////////////////////////
/*
*****************************************************************************
                              Reflection
                             Final Assessment
Full Name  : Harshit Gupta, Daiki Nagashima, Cheuk Lung Li
Student ID#: 157860214 , 113066211 , 149507212
Email      : hgupta16@myseneca.ca , dnagashima@myseneca.ca , cli259@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*/
////////////////////////////////////////////////////////


//call library
#include <stdio.h>
//call hearder file
#include "menu.h"
#include "helper.h"


#define MAX_RECORDS 250
#define REGION_DIVIDES 4
#define MONTH_NUMBERS 12
#define LOCATION_DIVIDES 8

int main(void)
{
    struct WeatherRecord data[MAX_RECORDS] = { {0} };

    struct RegionalData regionalStat[REGION_DIVIDES] = { { 10, "Western", 0},
                                                         { 20, "Northern", 0},
                                                         { 30, "Eastern", 0},
                                                         { 40, "Central", 0}
    };

    struct MonthData monthdata[MONTH_NUMBERS] = { {'\0', 0} };

    struct LocationData locationdata[LOCATION_DIVIDES] = { {0} };

    struct FinalWeather final = { data, MAX_RECORDS, regionalStat, REGION_DIVIDES, monthdata, MONTH_NUMBERS, locationdata, LOCATION_DIVIDES };


    FILE* fp = NULL;
    int recs = importWeatherDataFile(fp, data, MAX_RECORDS);

    menuMain(&final);

    return 0;
}