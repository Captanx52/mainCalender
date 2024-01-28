#include <stdio.h>
#include <stdlib.h>
#include <time.h>




int LastDayOfGregorianMonth(int month, int year) {
// Compute the last date of the month for the Gregorian calendar.
  
  switch (month) {
  case 2:
    if ((((year % 4) == 0) && ((year % 100) != 0))
        || ((year % 400) == 0))
      return 29;
    else
      return 28;
  case 4:
  case 6:
  case 9:
  case 11: return 30;
  default: return 31;
  }
}

int calcAbsGregorianDays(int d, int m, int y) {
 int N = d;
 for (int i = m - 1; i > 0; i--)
  N += LastDayOfGregorianMonth(i, y);

 return N + (y - 1) * 365
    + (y - 1) / 4
    - (y - 1) / 100
    + (y - 1) / 400;
}

int IsIslamicLeapYear(int year) {
// True if year is an Islamic leap year
  
  if ((((11 * year) + 14) % 30) < 11)
    return 1;
  else
    return 0;
}

int LastDayOfIslamicMonth(int month, int year) {
// Last day in month during year on the Islamic calendar.

  if (((month % 2) == 1) || ((month == 12) && IsIslamicLeapYear(year)))
    return 30;
  else
    return 29;
}

const int IslamicEpoch = 227014; // Absolute date of start of Islamic calendar

int IslamicDate(int month, int day, int year) {
 return (day                      // days so far this month
            + 29 * (month - 1)       // days so far...
            + month/2                //            ...this year
            + 354 * (year - 1)       // non-leap days in prior years
            + (3 + (11 * year)) / 30 // leap days in prior years
            + IslamicEpoch);                // days before start of calendar
}


void gregori_to_lunar(int y, int m, int d,int *Lyear ,int *Lmonth ,int *Lday){
 d = calcAbsGregorianDays(d, m, y);
 int month, day, year;

 // Search forward year by year from approximate year
 year = (d - IslamicEpoch) / 355;
 
 while (d >= IslamicDate(1, 1, year))
  year++;
 
 year--;
 // Search forward month by month from Muharram
 month = 1;
 while (d > IslamicDate(month, LastDayOfIslamicMonth(month, year), year))
  month++;
 
 day = d - IslamicDate(month, 1, year) + 1;

 *Lyear = year;
 *Lmonth = month;
 *Lday = day;
}

void lunar_to_gregori(int y, int m, int d,int *Lyear ,int *Lmonth ,int *Lday){
    int days = d -1 + IslamicDate(m, 1, y);

}

void jalali_to_gregori (int Jyear ,int Jmonth ,int Jday ,int *rGy ,int *rGm ,int *rGd ){
    //total days we have
    int days=0;

    //month days in normal year (jalali)
    int ULdays_J[12] = {31,31,31,
                        31,31,31,
                        30,30,30,
                        30,30,29};

    //month days in leap year(jalali)
    int Ldays_J[12] = {31,31,31,
                       31,31,31,
                       30,30,30,
                       30,30,29};

    //month days in normal year (gregori)
    int ULdays_G[12] = {31,30,31,
                        30,31,31,
                        30,31,30,
                        31,31,28};

    //month days in leap year(gregori)
    int Ldays_G[12] = {31,30,31,
                        30,31,31,
                        30,31,30,
                        31,31,29};
    
    //the gregori year is leap or not

    //yes
    if(Jyear%4 == 3){
        for (int i = 0; i < Jmonth-1; i++)
        {
            days += Ldays_J[i];
        }
        days += 19;
    }

    //no
    if(Jyear%4 != 3){
        for (int i = 0; i < Jmonth-1; i++)
        {
            days += ULdays_J[i];
        }
        days += 20;
    }

    //day of year
    days += Jday;

    //converting to gregori
    int Gyear = Jyear + 621;
    int Gmonth = 3;
    int Gday;
    
    int i = 0;

    //the gregori year is leap or not
    
    //yes
    if (Gyear % 4 == 1)
    {
        while (days > Ldays_G[i])
        {
            Gmonth += 1;
            days -= Ldays_G[i];
            i++;
        }
        
    }

    //no
    if (Gyear % 4 != 1)
    {
        while (days > ULdays_G[i])
        {
            Gmonth += 1;
            days -= ULdays_G[i];
            i++;
        }
        
    }


    Gday = days;
    
    //check the results and correct them
    if (Gmonth > 12)
    {
        Gmonth -= 12;
        Gyear += 1;
    }

    //output of function
    *rGy = Gyear;
    *rGm = Gmonth;
    *rGd = Gday;


                       
}


void gregori_to_jalali(int Gyear ,int Gmonth ,int Gday ,int *rJy ,int *rJm ,int *rJd ){
    //total days we have
    int days=0;

    //month days in normal year (gregori)
    int ULdays_G[12] = {31,28,31,
                 30,31,30,
                 31,31,30,
                 31,30,31};

    //month days in leap year(gregori)
    int Ldays_G[12] = {31,29,31,
                 30,31,30,
                 31,31,30,
                 31,30,31};
    
    //month days in normal year (jalali)
    int ULdays_J[12] = {30,30,29,
                  31,31,31,
                  31,31,31,
                  30,30,30};

    //month days in leap year(jalali)
    int Ldays_J[12] = {30,30,30,
                  31,31,31,
                  31,31,31,
                  30,30,30};

    //the gregori year is leap or not

    //yes
    if(Gyear%4 == 1){
        for (int i = 0; i < Gmonth-1; i++)
        {
            days += Ldays_G[i];
        }
        days += 11;
    }

    //no
    if(Gyear%4 != 1){
        for (int i = 0; i < Gmonth-1; i++)
        {
            days += ULdays_G[i];
        }
        days += 10;
    }

    //day of year
    days += Gday;

    //converting to jalali
    int Jyear = Gyear - 622;
    int Jmonth = 10;
    int Jday;
    
    int i = 0;

    //the gregori year is leap or not
    
    //yes
    if (Jyear % 4 == 3)
    {
        while (days > Ldays_J[i])
        {
            Jmonth += 1;
            days -= Ldays_J[i];
            i++;
        }
        
    }

    //no
    if (Jyear % 4 != 3)
    {
        while (days > ULdays_J[i])
        {
            Jmonth += 1;
            days -= ULdays_J[i];
            i++;
        }
        
    }

    Jday = days;
    
    //check the results and correct them
    if (Jmonth > 12)
    {
        Jmonth -= 12;
        Jyear += 1;
    }

    //output of function
    ///int rJy,rJm,rJd;
    *rJy = Jyear;
    *rJm = Jmonth;
    *rJd = Jday;
}



void Conversion(){
    int option;
    int iyear,imonth,iday;
    int oyear,omonth,oday;int luyear,lumonth,luday;
    int i = 0;
    int trust = 1;

    do
    {
        if (i == 0)
        {
            printf("____________________________\n");
            printf("___________\e[1;31moptions\e[0m__________\n");
            printf("| [0].       \e[1;32mQuit\e[0m          |\n");
            printf("| [1].   \e[1;32mGregori convert \e[0m  |\n");
            printf("| [2].   \e[1;32mJalali convert  \e[0m  |\n");
            printf("============================\n");
            printf(" > \e[1;33mSelect Option\e[0m : ");
            i++;            i++;
        }
        else
        {
            if (trust == 1){
            printf("\033[2J\033[1;1H");

            

            printf("____________________________\n");
            printf("___________\e[1;31moptions\e[0m__________\n");
            printf("| [0].       \e[1;32mQuit\e[0m          |\n");
            printf("| [1].   \e[1;32mGregori convert \e[0m  |\n");
            printf("| [2].   \e[1;32mJalali convert\e[0m    |\n");
            printf("============================\n");
            printf("          \e[1;33m<result>\e[0m          \n");
            printf("  Year  : %04d   --->  \e[1;32m%04d --- %04d\e[0m\n",iyear,oyear,luyear);
            printf("  Month :  %02d    --->   \e[1;32m%02d  ---  %02d\e[0m\n",imonth,omonth,lumonth);
            printf("  Day   :  %02d    --->   \e[1;32m%02d  ---  %02d\e[0m\n",iday,oday,luday);
            printf("============================\n");
            printf(" > \e[1;33mSelect Option\e[0m : ");
            }
            else
            {
                printf("\033[2J\033[1;1H");
                printf(" >> Please Enter \e[1;31mValid\e[0m Input\n");
                printf("____________________________\n");
                printf("___________\e[1;31moptions\e[0m__________\n");
                printf("| [0].       \e[1;32mQuit\e[0m          |\n");
                printf("| [1].   \e[1;32mGregori convert \e[0m  |\n");
                printf("| [2].   \e[1;32mJalali convert  \e[0m  |\n");
                printf("============================\n");
                printf(" > \e[1;33mSelect Option\e[0m : ");
            }
            

        }
        
        
        scanf(" %d",&option);
        switch (option)
        {
        case 0:
            printf("\033[2J\033[1;1H");
            break;
        case 1:
            printf("    \e[1;33m|Year\e[0m : ");
            scanf("%d",&iyear);
            if (iyear < 1){
                trust = 0;
                break;}
            printf("    \e[1;33m|Month\e[0m : ");
            scanf("%d",&imonth);
            if (imonth < 1 || imonth > 12){
                trust = 0;
                break;}
            printf("    \e[1;33m|Day\e[0m : ");
            scanf("%d",&iday);
            if (iday < 1 || iday > 31){
                trust = 0;
                break;}
            if (trust == 1){
            gregori_to_jalali(iyear ,imonth ,iday ,&oyear ,&omonth ,&oday );
            gregori_to_lunar(iyear ,imonth ,iday ,&luyear ,&lumonth ,&luday );
            }

            break;
        case 2:
            printf("    \e[1;33m|Year\e[0m : ");
            scanf("%d",&iyear);
            if (iyear < 1){
                trust = 0;
                break;}
            printf("    \e[1;33m|Month\e[0m : ");
            scanf("%d",&imonth);
            if (imonth < 1 || imonth > 12){
                trust = 0;
                break;}
            printf("    \e[1;33m|Day\e[0m : ");
            scanf("%d",&iday);
            if (iday < 1 || iday > 31){
                trust = 0;
                break;}
            if (trust == 1){
            jalali_to_gregori(iyear ,imonth ,iday ,&oyear ,&omonth ,&oday );
            gregori_to_lunar(oyear ,omonth ,oday ,&luyear ,&lumonth ,&luday );
            }
            break;

        // case 3:
        //     printf("    \e[1;33m|Year\e[0m : ");
        //     scanf("%d",&iyear);
        //     printf("    \e[1;33m|Month\e[0m : ");
        //     scanf("%d",&imonth);
        //     printf("    \e[1;33m|Day\e[0m : ");
        //     scanf("%d",&iday);
        //     gregorianToLunar(iyear ,imonth ,iday ,&oyear ,&omonth ,&oday );
        //     break;
        default:
            printf("\033[2J\033[1;1H");
            printf(" >> Please Enter \e[1;31mValid\e[0m Input\n");
            break;
        }
    }while (option !=0 );
}


void WDay(int Gyear ,int Gmonth ,int Gday,int *wday ){
    int sum;
    int key;

    if (Gyear % 4 == 3)
    {
        if (Gmonth == 1)
            key = 0;
        if (Gmonth == 2)
            key = 3;
        if (Gmonth == 3)
            key = 4;
        if (Gmonth == 4)
            key = 0;
        if (Gmonth == 5)
            key = 2;
        if (Gmonth == 6)
            key = 5;
        if (Gmonth == 7)
            key = 0;
        if (Gmonth == 8)
            key = 3;
        if (Gmonth == 9)
            key = 6;
        if (Gmonth == 10)
            key = 1;
        if (Gmonth == 11)
            key = 4;
        if (Gmonth == 12)
            key = 6;
    }
    else
    {
        if (Gmonth == 1)
            key = 1;
        if (Gmonth == 2)
            key = 4;
        if (Gmonth == 3)
            key = 4;
        if (Gmonth == 4)
            key = 0;
        if (Gmonth == 5)
            key = 2;
        if (Gmonth == 6)
            key = 5;
        if (Gmonth == 7)
            key = 0;
        if (Gmonth == 8)
            key = 3;
        if (Gmonth == 9)
            key = 6;
        if (Gmonth == 10)
            key = 1;
        if (Gmonth == 11)
            key = 4;
        if (Gmonth == 12)
            key = 6;
    }

    sum = (Gyear % 100)+((Gyear % 100) / 4) + key + Gday;

    if (Gyear >= 2000)
    {
        *wday = sum - 1;
    }
    else
    {
        *wday = sum;
    }
}

void JCA(int month ,int wday ,int leap ){
    int i;
    int mdays[12] ={31,31,31,
                     31,31,31,
                     30,30,30,
                     30,30,29};
    if (leap == 3)
    {
        mdays[11] = 30;   
    }
    if(month == 1)
        printf("\e[7;35m                 Farvardin\e[7;35m                 \e[0m\n");
    if(month == 2)
        printf("\e[7;35m                Ordibehesth\e[7;35m                \e[0m\n");
    if(month == 3)
        printf("\e[7;35m                  Khordad\e[7;35m                  \e[0m\n");
    if(month == 4)
        printf("\e[7;35m                    Tir\e[7;35m                    \e[0m\n");
    if(month == 5)
        printf("\e[7;35m                   Mordad\e[7;35m                  \e[0m\n");
    if(month == 6)
        printf("\e[7;35m                 Shahrivar\e[7;35m                 \e[0m\n");
    if(month == 7)
        printf("\e[7;35m                   Mehr\e[7;35m                    \e[0m\n");
    if(month == 8)
        printf("\e[7;35m                   Aban\e[7;35m                    \e[0m\n");
    if(month == 9)
        printf("\e[7;35m                   Azar\e[7;35m                    \e[0m\n");
    if(month == 10)
        printf("\e[7;35m                    Dey\e[7;35m                    \e[0m\n");
    if(month == 11)
        printf("\e[7;35m                  Bahman\e[7;35m                   \e[0m\n");
    if(month == 12)
        printf("\e[7;35m                  Esfand\e[7;35m                   \e[0m\n");




    printf("| shn | yek | duo | seh | chr | pan | Jom |\n");
    for (i=0; i < wday%7; i++)
    {
        printf("|     ");
    }
    
    i++;
    for (int j = 1; j < mdays[month]+1; j++)
    {
        if (j < 10){
            printf("|   %d ",j);
        }
        else {
        printf("|  %d ",j);
        }i++;
        if (i%7 == 1)
        {
            printf("|\n");
        }
        
        
    }
    printf("\n");
}


void GCA(int month ,int wday ,int leap ){
    int i;
    int mdays[12] ={31,28,31,
                     30,31,30,
                     31,31,30,
                     31,30,31};
    if (leap == 1)
    {
        mdays[1] = 29;   
    }
    if(month == 1)
        printf("\e[7;35m                  January\e[7;35m                  \e[0m\n");
    if(month == 2)
        printf("\e[7;35m                 February\e[7;35m                  \e[0m\n");
    if(month == 3)
        printf("\e[7;35m                   March\e[7;35m                   \e[0m\n");
    if(month == 4)
        printf("\e[7;35m                   April\e[7;35m                   \e[0m\n");
    if(month == 5)
        printf("\e[7;35m                   May\e[7;35m                     \e[0m\n");
    if(month == 6)
        printf("\e[7;35m                   June\e[7;35m                    \e[0m\n");
    if(month == 7)
        printf("\e[7;35m                   July\e[7;35m                    \e[0m\n");
    if(month == 8)
        printf("\e[7;35m                  August\e[7;35m                   \e[0m\n");
    if(month == 9)
        printf("\e[7;35m                 September\e[7;35m                 \e[0m\n");
    if(month == 10)
        printf("\e[7;35m                  October\e[7;35m                  \e[0m\n");
    if(month == 11)
        printf("\e[7;35m                 November\e[7;35m                  \e[0m\n");
    if(month == 12)
        printf("\e[7;35m                  December\e[7;35m                  \e[0m\n");



    printf("| sun | mon | tue | wed | thu | fri | sat |\n");
    for (i=0; i < (wday%7+6)%7; i++)
    {
        printf("|     ");
    }
    
    i++;
    for (int j = 1; j < mdays[month-1]+1; j++)
    {
        if (j < 10){
            printf("|   %d ",j);
        }
        else {
        printf("|  %d ",j);
        }i++;
        if (i%7 == 1)
        {
            printf("|\n");
        }
        
        
    }
    printf("\n");
    
}
void Calender(){
    int option;
    int iyear,imonth;
    int wday;
    int i = 0;

    do
    {
        if (i == 0)
        {
            printf("____________________________\n");
            printf("___________\e[1;31moptions\e[0m__________\n");
            printf("| [0].       \e[1;32mQuit\e[0m          |\n");
            printf("| [1].  \e[1;32mGregori Calender \e[0m  |\n");
            printf("| [2].   \e[1;32mJalali Calende  \e[0m  |\n");
            printf("============================\n");
            printf(" > \e[1;33mSelect Option\e[0m : ");
            i++;
        }
        else
        {
            printf("\033[2J\033[1;1H");

            

            printf("____________________________\n");
            printf("___________\e[1;31moptions\e[0m__________\n");
            printf("| [0].       \e[1;32mQuit\e[0m          |\n");
            printf("| [1].  \e[1;32mGregori Calender \e[0m  |\n");
            printf("| [2].   \e[1;32mJalali Calende  \e[0m  |\n");
            printf("============================\n");
            printf("          \e[1;33m<result>\e[0m          \n");
            if (option == 1)
                GCA(imonth ,wday ,iyear % 4 );
            if (option == 2)
                JCA(imonth ,wday ,iyear % 4 );
            
            

            printf("============================\n");
            printf(" > \e[1;33mSelect Option\e[0m : ");

        }
        
        
        scanf("%d",&option);
        switch (option)
        {
        case 0:
            printf("\033[2J\033[1;1H");
            break;
        case 1:
            printf("    \e[1;33m|Year\e[0m : ");
            scanf("%d",&iyear);
            printf("    \e[1;33m|Month\e[0m : ");
            scanf("%d",&imonth);
            WDay(iyear ,imonth ,1 ,&wday);
            
            break;
        case 2:
            int oyear,omonth,oday;
            printf("    \e[1;33m|Year\e[0m : ");
            scanf("%d",&iyear);
            printf("    \e[1;33m|Month\e[0m : ");
            scanf("%d",&imonth);
            jalali_to_gregori(iyear ,imonth ,1 ,&oyear ,&omonth ,&oday );
            WDay(oyear,omonth,oday,&wday);

            break;
        default:
            printf("\033[2J\033[1;1H");
            printf(" >> Please Enter \e[1;31Valid\e[0m Input\n");
            break;
        }
    }while (option !=0 );
}
void Age(){
    int validation=1;
    int birthSD;
    //b is for birth
    int bYear,bMonth,bDay;
    //o is for how old
    int oYear,oMonth,oDay;
    //t is for today
    int tYear,tMonth,tDay;
    int a,b,c;
    int i = 0;
    int m,n,o;
    int daysOld;
    time_t birthSecond,currentSecond;

    currentSecond = time(NULL);
    do
    {
        system("cls");
        if(i==0){
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].       \e[1;32mQuit\e[0m          |\n");
        printf("============================\n");
        i++;
        }
        else if(validation==0){
        printf(" >> Please Enter \e[1;31mValid\e[0m Input\n");
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].       \e[1;32mQuit\e[0m          |\n");
        printf("============================\n");
        i++;
        }else
        {
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].       \e[1;32mQuit\e[0m          |\n");
        printf("============================\n");
        //outputs
        printf("%d / %d / %d ---> ",m,n,o);
        printf("%d / %d / %d\n",a,b,c);
            
            if (birthSecond != 0)
            {
                printf("You born on ");

                if (birthSD % 7 == 0)
                    printf("Sun\n");
                if (birthSD % 7 == 1)
                    printf("Mon\n");
                if (birthSD % 7 == 2)
                    printf("Tue\n");
                if (birthSD % 7 == 3)
                    printf("Wed\n");
                if (birthSD % 7 == 4)
                    printf("Thu\n");
                if (birthSD % 7 == 5)
                    printf("Fri\n");
                if (birthSD % 7 == 6)
                    printf("Sat\n");

                printf("You have ");

                if (oYear != 0)
                {
                 if (oYear == 1)
                    {printf("%d year",oYear);}
                 else
                    {printf("%d years",oYear);}
                }
                if (oYear != 0 && (oMonth != 0 || oDay !=0))
                {
                printf(" & ");
                }
                if (oMonth != 0)
                {
                 if (oMonth == 1)
                    {printf("%d month",oMonth);}
                 else
                    {printf("%d months",oMonth);}
                }
                if (oMonth != 0 && oDay !=0)
                {
                printf(" & ");
                }
                if (oDay != 0)
                {
                 if (oDay == 1)
                    {printf("%d day",oDay);}
                 else
                    {printf("%d days",oDay);}
                }

                printf(" old !!!\n");

                printf("%d days you leaved on this pice of rock!\n",daysOld);
            }
            else
            {
                printf("You born today littly :>\n");
            }
            
            printf("============================\n");
        }
        

        printf("    \e[1;33m|Year\e[0m : ");
        scanf(" %d",&bYear);
        switch (bYear)
        {
        case 0:
            printf("\033[2J\033[1;1H");
            break;
        default:
            
            printf("    \e[1;33m|Month\e[0m : ");
            scanf("%d",&bMonth);
            printf("    \e[1;33m|Day\e[0m : ");
            scanf("%d",&bDay);
            
            printf("\033[2J\033[1;1H");
            m = bYear;
            n = bMonth;
            o = bDay;
           
            if (bYear <1410)
            {
                if ((bYear < 1300 || (bMonth < 1 || bMonth > 12)) || (bDay < 1 || bDay > 31) )
                {
                    printf("    \e[1;33m|Month\e[0m : ");
                    printf(" >> Please Enter \e[1;31mValid\e[0m Input\n");
                    validation = 0;
                    break;
                }
                
                jalali_to_gregori(bYear ,bMonth ,bDay , &bYear, &bMonth, &bDay);
                a = bYear;
                b = bMonth;
                c = bDay;
                

            }
            else
            {
                if ((bYear < 1900 || (bMonth < 1 || bMonth > 12)) || (bDay < 1 || bDay > 31) ){
                    printf("    \e[1;33m|Month\e[0m : ");
                    printf(" >> Please Enter \e[1;31mValid\e[0m Input\n");
                    validation = 0;
                    break;
                }
                gregori_to_jalali(bYear ,bMonth ,bDay , &a, &b, &c);
                if (a % 4 == 3)
                {
                    c ++;
                }
                
            }
            
            
            
            //finding the exact second of birth

            struct tm birth_time = {0};
            birth_time.tm_year = bYear-1900;
            birth_time.tm_mon = bMonth-1;
            birth_time.tm_mday = bDay;

            birthSecond = mktime(&birth_time);
            daysOld = (currentSecond-birthSecond)/(3600*24);

            //finding the today date

            struct tm current_time = *localtime(&currentSecond);
            tYear = current_time.tm_year+1900;
            tMonth = current_time.tm_mon+1;
            tDay = current_time.tm_mday;

            //finding old in general

            oYear = tYear - bYear;
            oMonth = tMonth - bMonth;

            if(oMonth < 0){oYear -= 1;oMonth += 12; }
            oDay = tDay - bDay;
            if(oDay < 0){oMonth -= 1;oDay += 30; }

            //wich day of wick?

            birthSD = birth_time.tm_wday;

            
            break;
        }
    }while (bYear !=0 );
}

void mainMenu_display(int option){
    system("cls");
    if (option ==0)
    {
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].\e[7;32m       Quit          \e[0m|\n");
        printf("| [1].       \e[1;32mAge\e[0m           |\n");
        printf("| [2].     \e[1;32mCalender\e[0m        |\n");
        printf("| [3].    \e[1;32mConversion\e[0m       |\n");
        printf("============================\n");
        printf(" > \e[1;33mSelect Option\e[0m : ");
    }
    if (option ==1)
    {
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].       \e[1;32mQuit\e[0m          |\n");
        printf("| [1].\e[7;32m       Age           \e[0m|\n");
        printf("| [2].     \e[1;32mCalender\e[0m        |\n");
        printf("| [3].    \e[1;32mConversion\e[0m       |\n");
        printf("============================\n");
        printf(" > \e[1;33mSelect Option\e[0m : ");
    }
    if (option ==2)
    {
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].       \e[1;32mQuit\e[0m          |\n");
        printf("| [1].       \e[1;32mAge\e[0m           |\n");
        printf("| [2].\e[7;32m     Calender        \e[0m|\n");
        printf("| [3].    \e[1;32mConversion\e[0m       |\n");
        printf("============================\n");
        printf(" > \e[1;33mSelect Option\e[0m : ");
    }
    if (option ==3)
    {
        printf("____________________________\n");
        printf("___________\e[1;31moptions\e[0m__________\n");
        printf("| [0].       \e[1;32mQuit\e[0m          |\n");
        printf("| [1].       \e[1;32mAge\e[0m           |\n");
        printf("| [2].     \e[1;32mCalender\e[0m        |\n");
        printf("| [3].\e[7;32m    Conversion       \e[0m|\n");
        printf("============================\n");
        printf(" > \e[1;33mSelect Option\e[0m : ");
    }
}
int main(){
    int option;
    int choice=256;

    do
    {
        mainMenu_display(choice % 4);
        option = getch();
        switch (option)
        {
        case 72:
             
            choice --;
            break;
        case 80:
             
            choice ++;
            break;
        case 49:
             
            choice = 1;
            Age();
            break;
        case 50:
            choice = 2;
            system("cls");
            Calender();
            break;
        case 51:
             
            choice = 3;
            system("cls");
            Conversion();
            break;
        case 13:
            switch (choice % 4)
            {
                
            case 0:
                option = 48 ;
                break;
            case 1:
                system("cls");
                Age();
                break;
            case 2:
                system("cls");
                Calender();
                break;
            case 3:
                system("cls");
                Conversion();
                break;
            default:
                break;
            }
            break;
        case 48:
            break;
        default:
            printf(" >> Please Enter \e[1;31mValid\e[0m Input\n");
            break;
        }
    } while (option != 48);
}