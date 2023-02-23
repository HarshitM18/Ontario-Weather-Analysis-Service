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
//						  MENU FUNCTIONS                        //
//////////////////////////////////////////////////////////////////

// SAFE-GUARD: 
#ifndef menu_h
#define menu_h

//////////////////////////////////////
// Module macro's 
//////////////////////////////////////

//Maxium length of name
#define NAME_LEN 15
#define REGION_LEN 9
#define MONTH_LEN 10

//view weather type
#define ALL 1
#define REGION 2
#define MONTH 3
#define LOCATION 4

//////////////////////////////////////
// Marco structures
//////////////////////////////////////

//Date: year & month
struct Date
{
	int year;
	int month;
};

//Location
struct Location
{
	int regionCode;
	char name[NAME_LEN];
};

//Record
struct WeatherRecord
{
	struct Date date;
	double precipAmt;
	char unit;
	struct Location location;
};

struct RegionalData
{
	int regionCode;
	char name[REGION_LEN];
	int precipAmt_mm;
};

struct MonthData
{
	char monthName[MONTH_LEN];
	int monthPrecip;
};

struct LocationData
{
	char name[NAME_LEN];
	int precipAmt;
};

//Weather
struct FinalWeather
{
	struct WeatherRecord* data;
	int maxRecords;
	struct RegionalData* regionalStat;
	int maxRegional;
	struct MonthData* monthdata;
	int maxMonth;
	struct LocationData* locationdata;
	int maxLocation;
};

//////////////////////////////////////
// MENU FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct FinalWeather* final);

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

void displayDataHeader(int viewtype);

void displayAllData(struct WeatherRecord* data);

void displayRegionData(struct RegionalData regionalStat[], int maxRegional);

void displayMonthData(struct MonthData monthdata[], int maxMonth);

void displayLocationData(struct LocationData locationdata[], int maxLocation);

//////////////////////////////////////
// VIEW FUNCTIONS
//////////////////////////////////////

void viewAllData(struct WeatherRecord data[], int max);

void viewByRegion(struct WeatherRecord data[], int max, struct RegionalData regionalStat[], int maxRegional);

void ViewByMonth(struct WeatherRecord data[], int max, struct MonthData monthdata[], int maxMonth);

void viewByLocation(struct WeatherRecord data[], int max, struct LocationData locationdata[], int maxLocation);

//////////////////////////////////////
// utility FUNCTIONS
//////////////////////////////////////

void sortDataByRegion(struct RegionalData regionalStat[], int maxRegional);

void sortDataByMonth(struct MonthData monthdata[], int maxmonth);

void CalculateMonthPrecip(struct WeatherRecord data[], int count, struct MonthData monthdata[], int maxMonth);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////
// 
// Import waether data from file into a WeatherRecord array (returns # of records read)
int importWeatherDataFile(FILE* fp, struct WeatherRecord* data, int max);

#endif// !me