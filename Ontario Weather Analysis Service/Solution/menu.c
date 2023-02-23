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

//////////////////////////////////////////////////////////////////
/////////////// MENU FUNCTIONS//////////////////////////////////
//////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS

//call library
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//call hearder file
#include "menu.h"
#include "helper.h"

//////////////////////////////////////
// MENU FUNCTIONS
//////////////////////////////////////

//select function in Menu
void menuMain(struct FinalWeather* final)
{
    int selection;

    do {
        printf("=======================================================\n"
            "         Ontario Weather Analysis Service\n"
            "                  Year: 2021\n"
            "=======================================================\n"
            "1. View all data\n"
            "2. View by region (sorted DESCENDING by precip.)\n"
            "3. View by month (sorted ASCENDING by precip.)\n"
            "4. View by location name (sorted DESCENDING by precip.)\n"
            "-------------------------------------------------------\n"
            "0. Exit\n"
            "-------------------------------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Application Terminated!");
            break;
        case 1:
            viewAllData(final->data, final->maxRecords);
            break;
        case 2:
            viewByRegion(final->data, final->maxRecords, final->regionalStat, final->maxRegional);
            break;
        case 3:
            ViewByMonth(final->data, final->maxRecords, final->monthdata, final->maxMonth);
            break;
        case 4:
            viewByLocation(final->data, final->maxRecords, final->locationdata, final->maxLocation);
            break;
        }
    } while (selection);
}

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////
void displayDataHeader(int viewtype)
{
    switch (viewtype)
    {
    case 1:
        printf("Year Month Precip.Amt Unit Region Name\n"
            "---- ----- ---------- ---- ------ ---------------\n");
        break;
    case 2:
        printf("Region Name     Precip(mm)\n"
            "------ -------- ----------\n");
        break;
    case 3:
        printf("Month     Precip(mm)\n"
            "--------- ----------\n");
        break;
    case 4:
        printf("Location        Precip(mm)\n"
            "--------------- ----------\n");
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void displayAllData(struct WeatherRecord* data)
{
    if (data->date.month <= 9)
    {
        printf("%4d    %02d%11.1lf    %1c     %2d %s", data->date.year, data->date.month, data->precipAmt, data->unit, data->location.regionCode, data->location.name);
    }
    else
    {
        printf("%4d    %2d%11.1lf    %1c     %2d %s", data->date.year, data->date.month, data->precipAmt, data->unit, data->location.regionCode, data->location.name);
    }

}

void displayRegionData(struct RegionalData regionalStat[], int maxRegional)
{
    int i;
    int total = 0;
    double average = 0.00;

    for (i = 0; i < maxRegional; i++)
    {
        printf("%6d %-9s %9d\n", regionalStat[i].regionCode, regionalStat[i].name, regionalStat[i].precipAmt_mm);
        total += regionalStat[i].precipAmt_mm;
    }
    average = (double)total / maxRegional;

    printf("------ -------- ----------\n");
    printf("         Total: %10d\n", total);
    printf("       Average: %10.2f\n", average);
    printf("\n");
}

void displayMonthData(struct MonthData monthdata[], int maxMonth)
{
    int i;
    int total = 0;
    double average = 0.00;

    for (i = 0; i < maxMonth; i++)
    {
        printf("%-9s %10d\n", monthdata[i].monthName, monthdata[i].monthPrecip);
        total += monthdata[i].monthPrecip;
    }
    average = (double)total / maxMonth;

    printf("--------- ----------\n");
    printf("   Total: %10d\n", total);
    printf(" Average: %10.2f\n", average);
    printf("\n");
}

void displayLocationData(struct LocationData locationdata[], int maxLocation)
{
    int i;
    int total = 0;
    double average = 0.00;

    for (i = 0; i < maxLocation; i++)
    {
        printf("%15s %10d\n", locationdata[i].name, locationdata[i].precipAmt);
        total += locationdata[i].precipAmt;
    }
    average = (double)total / maxLocation;

    printf("--------------- ----------\n");
    printf("         Total: %10d\n", total);
    printf("       Average: %10.2f\n", average);
    printf("\n");
}

void viewAllData(struct WeatherRecord data[], int max)
{
    int i = 0;
    displayDataHeader(ALL);
    for (i = 0; i < max; i++)
    {

        if (data[i].date.year == 0)
        {
            ;
        }
        else
        {
            if (i % 15 == 0 && i > 0)
            {
                printf("\n");
                suspend();
            }
            displayAllData(&data[i]);
            printf("\n");

        }
    }
    printf("\n");
}


void viewByRegion(struct WeatherRecord data[], int max, struct RegionalData regionalStat[], int maxRegional)
{
    int i;
    int j = 0;
    int count = 0;

    //count the number of vaild data
    for (i = 0; i < max; i++)
    {
        if (data[i].precipAmt > 0.0)
        {
            count++;
        }

    }
    //display REGION Data Header
    displayDataHeader(REGION);

    //calculate the precip in mm for each region
    for (j = 0; j < maxRegional; j++)
    {

        for (i = 0; i < count; i++)
        {
            if (data[i].location.regionCode == regionalStat[j].regionCode)
            {
                if (data[i].unit == 'm')
                {
                    regionalStat[j].precipAmt_mm += data[i].precipAmt;
                }
                else
                {
                    regionalStat[j].precipAmt_mm += (data[i].precipAmt * 10);
                }
            }
        }
    }
    //sort data by region
    sortDataByRegion(regionalStat, maxRegional);

    //display regional data
    displayRegionData(regionalStat, maxRegional);

    //reset reginal data struct
    for (i = 0; i < maxRegional; i++)
    {
        regionalStat[i].precipAmt_mm = 0;
    }
}

void ViewByMonth(struct WeatherRecord data[], int max, struct MonthData monthdata[], int maxMonth)
{
    int i;
    int count = 0;

    for (i = 0; i < max; i++)
    {
        if (data[i].precipAmt > 0.0)
        {
            count++;
        }
    }
    // display Month data header
    displayDataHeader(MONTH);

    //LetterMonth(&monthdata);

    // Calculata each month precip(mm)
    CalculateMonthPrecip(data, count, monthdata, maxMonth);

    // Sort by data ascending
    sortDataByMonth(monthdata, maxMonth);

    // display Month data
    displayMonthData(monthdata, maxMonth);

    for (i = 0; i < maxMonth; i++)
    {
        monthdata[i].monthPrecip = 0.0;
        strcpy(monthdata[i].monthName, "\0");
    }
}

void viewByLocation(struct WeatherRecord data[], int max, struct LocationData LocationData[], int maxLocation)
{

    int i = 0, j = 0, k = 0;

    int count = 0;
    int nonStored; // 0 is stored, non-0 is not stored before


    for (i = 0; i < max; i++)
    {
        if (data[i].precipAmt > 0.0)
        {
            count++;
        }
    }

    //store location name to Location Data structure
    //j is the array index for Location Data structure
    for (j = 0; j < maxLocation; j++)
    {
        //search WeatherRecord database
        //i is the array index for WeatherRecord structure
        for (i = 0; i < count; i++)
        {
            //if the location name is not the same
            if (strcmp(data[i].location.name, LocationData[j].name) != 0)
            {
                //search Location Data structure
                //if the location name has stored before, beark the searching
                for (k = 0; k < maxLocation; k++)
                {
                    nonStored = strcmp(data[i].location.name, LocationData[k].name);
                    if (nonStored == 0) break;
                }

                //after searching the Location Data structure, if the location name has not stored before
                //copy the string to Location Data structure, and 
                if (nonStored != 0)
                {
                    strcpy(LocationData[j].name, data[i].location.name);
                    break;
                }
            }
        }
    }


    //calculate precip by location 
    for (j = 0; j < maxLocation; j++)
    {
        for (i = 0; i < max; i++)
        {
            if (strcmp(data[i].location.name, LocationData[j].name) == 0)
            {
                if (data[i].unit == 'c')
                {
                    LocationData[j].precipAmt += data[i].precipAmt * 10;
                }
                else
                {
                    LocationData[j].precipAmt += data[i].precipAmt;
                }
            }
        }
    }


    //sort the location data structure

    char tempLocationname[NAME_LEN];
    int tempPrecip;

    for (i = 0; i < maxLocation; i++)
    {
        for (j = i + 1; j < maxLocation; j++)
        {
            if (LocationData[i].precipAmt < LocationData[j].precipAmt)
            {
                strcpy(tempLocationname, LocationData[i].name);
                tempPrecip = LocationData[i].precipAmt;

                strcpy(LocationData[i].name, LocationData[j].name);
                LocationData[i].precipAmt = LocationData[j].precipAmt;

                strcpy(LocationData[j].name, tempLocationname);
                LocationData[j].precipAmt = tempPrecip;
            }
        }
    }

    // display location data header
    displayDataHeader(LOCATION);

    //display data
    displayLocationData(LocationData, maxLocation);

    //reset location data struct
    for (i = 0; i < maxLocation; i++)
    {
        LocationData[i].precipAmt = 0;
    }
}

// Utility functions
void sortDataByRegion(struct RegionalData regionalStat[], int maxRegional)
{
    int i = 0;
    int j = 0;
    int tempindex = 0;
    int tempint = 0;
    char tempString[REGION_LEN] = { 0 };

    for (i = 0; i < maxRegional; i++)
    {
        tempindex = i;

        for (j = i + 1; j < maxRegional; j++)
        {
            if (regionalStat[j].precipAmt_mm > regionalStat[tempindex].precipAmt_mm)
            {
                tempindex = j;
            }
        }
        if (tempindex != i)
        {
            strcpy(tempString, regionalStat[i].name);
            strcpy(regionalStat[i].name, regionalStat[tempindex].name);
            strcpy(regionalStat[tempindex].name, tempString);

            tempint = regionalStat[i].precipAmt_mm;
            regionalStat[i].precipAmt_mm = regionalStat[tempindex].precipAmt_mm;
            regionalStat[tempindex].precipAmt_mm = tempint;

            tempint = regionalStat[i].regionCode;
            regionalStat[i].regionCode = regionalStat[tempindex].regionCode;
            regionalStat[tempindex].regionCode = tempint;
        }
    }
}

void sortDataByMonth(struct MonthData monthdata[], int maxmonth)
{
    int i, j;
    char tempmonthname[MONTH_LEN] = { '\0' };
    int tempmonthprecip;

    for (i = 0; i < maxmonth; i++)
    {
        for (j = i + 1; j < maxmonth; j++)
        {
            if (monthdata[i].monthPrecip > monthdata[j].monthPrecip)
            {
                strcpy(tempmonthname, monthdata[i].monthName);
                tempmonthprecip = monthdata[i].monthPrecip;

                strcpy(monthdata[i].monthName, monthdata[j].monthName);
                monthdata[i].monthPrecip = monthdata[j].monthPrecip;

                strcpy(monthdata[j].monthName, tempmonthname);
                monthdata[j].monthPrecip = tempmonthprecip;
            }
        }
    }
}

void CalculateMonthPrecip(struct WeatherRecord data[], int count, struct MonthData monthdata[], int maxMonth)
{
    int i, flag = 0;
    double tempprecip;

    for (i = 0; i < count; i++)
    {

        if (data[i].unit == 'c')
        {
            tempprecip = data[i].precipAmt * 10;
        }
        else
        {
            tempprecip = data[i].precipAmt;
        }
        switch (data[i].date.month)
        {
        case 1:
            if (strcmp(monthdata[0].monthName, "\0") == 0)
            {
                strcpy(monthdata[0].monthName, "January");
            }
            monthdata[0].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 2:
            if (strcmp(monthdata[1].monthName, "\0") == 0)
            {
                strcpy(monthdata[1].monthName, "February");
            }
            monthdata[1].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 3:
            if (strcmp(monthdata[2].monthName, "\0") == 0)
            {
                strcpy(monthdata[2].monthName, "March");
            }
            monthdata[2].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 4:
            if (strcmp(monthdata[3].monthName, "\0") == 0)
            {
                strcpy(monthdata[3].monthName, "April");
            }
            monthdata[3].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 5:
            if (strcmp(monthdata[4].monthName, "\0") == 0)
            {
                strcpy(monthdata[4].monthName, "May");
            }
            monthdata[4].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 6:
            if (strcmp(monthdata[5].monthName, "\0") == 0)
            {
                strcpy(monthdata[5].monthName, "June");
            }
            monthdata[5].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 7:
            if (strcmp(monthdata[6].monthName, "\0") == 0)
            {
                strcpy(monthdata[6].monthName, "July");
            }
            monthdata[6].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 8:
            if (strcmp(monthdata[7].monthName, "\0") == 0)
            {
                strcpy(monthdata[7].monthName, "August");
            }
            monthdata[7].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 9:
            if (strcmp(monthdata[8].monthName, "\0") == 0)
            {
                strcpy(monthdata[8].monthName, "September");
            }
            monthdata[8].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 10:
            if (strcmp(monthdata[9].monthName, "\0") == 0)
            {
                strcpy(monthdata[9].monthName, "October");
            }
            monthdata[9].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 11:
            if (strcmp(monthdata[10].monthName, "\0") == 0)
            {
                strcpy(monthdata[10].monthName, "November");
            }
            monthdata[10].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        case 12:
            if (strcmp(monthdata[11].monthName, "\0") == 0)
            {
                strcpy(monthdata[11].monthName, "December");
            }
            monthdata[11].monthPrecip += ((int)(tempprecip * 10) / 10);
            break;
        }
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import waether data from file into a WeatherRecord array (returns # of records read)
int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max)
{

    int recs = 0;

    fp = fopen("weatherdata.txt", "r");

    if (fp != NULL)
    {
        while (recs < max &&
            fscanf(fp, "%d,%d,%lf,%c,%d,%15[^\n]\n",
                &data[recs].date.year, &data[recs].date.month,
                &data[recs].precipAmt, &data[recs].unit,
                &data[recs].location.regionCode,
                data[recs].location.name) == 6)

        {
            recs++;
        }

    }

    return recs;

}