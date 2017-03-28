#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#define BUFFER_SIZE 102

int main (void)
{
    void WaitFor(void);
    int i, checkif;
    char buffer[BUFFER_SIZE], nubuf[BUFFER_SIZE];
    HWND handle;

    //Getting window's name from user and getting rid of newline char.
    printf ("Introduce the title of the program window:\n(Up to 100 characters)\n\n");
    gets  (buffer);
    for (i = 0; buffer[i] != '\0' && buffer[i] != 92; ++i){
            nubuf[i] = buffer[i];
    }
    nubuf[i] = '\0';

    //Converting ASCII string to UNICODE string.
    size_t len = strlen (nubuf);
    WCHAR unistring[len + 1];
    checkif = MultiByteToWideChar (CP_OEMCP, 0, nubuf, -1, unistring, len + 1);
    if (!checkif)
        printf ("Conversion failed\n");

    //Getting window by it's title.
    handle = FindWindowW (NULL, unistring);
    if (handle == NULL)
        printf ("Couldn't get window.\n");
    else
        WaitFor();
        printf ("Closing %s...\n", nubuf);
        SendMessage (handle, WM_CLOSE, 0, 0);

    return 0;
}

void WaitFor(void)
{
    struct tm thisTime;
    struct tm *PtrToCT;
    PtrToCT = malloc (sizeof (&thisTime));
    int convertTime (struct tm *tm2Convert);
    unsigned int timetowait;
    char newlinebuf, response;

    printf ("Introduce how much time should pass before closing the program:\n(If you have no use for a particular unit of time you can just introduce a 0)\n\n");
    printf ("(hh:mm:ss) "); scanf ("%i:%i:%i", &PtrToCT->tm_hour, &PtrToCT->tm_min, &PtrToCT->tm_sec);
    #ifdef DEBUG
        printf ("DEBUG: Everything okay up to this point.\n");
        printf ("Hours: %i Minutes: %i Seconds %i\n\n", PtrToCT->tm_hour, PtrToCT->tm_min, PtrToCT->tm_sec);
    #endif // DEBUG
    scanf ("%c", &newlinebuf);
    #ifdef DEBUG
        printf ("DEBUG: Next word %c should be in next line.\n", newlinebuf);
    #endif // DEBUG

    if ((PtrToCT->tm_hour > 23 || PtrToCT->tm_hour < 0) || (PtrToCT->tm_min > 59 || PtrToCT->tm_min < 0) || (PtrToCT->tm_sec > 59 || PtrToCT->tm_sec < 0)){
        printf ("Error:\n-Hours must range from 0 to 23\n-Minutes must range from 0 to 59\n-Seconds must range from 0 to 59\n");
        printf ("Would you like to try again? (press y/n the press Enter)\n");
        scanf ("%c", &response);

        if (response == 'y'){
            printf ("Introduce how much should pass before closing the program:\n(If you have no use for a particular unit of time just introduce a '0')\n\n");
            printf ("(hh:mm:ss): "); scanf ("%i:%i:%i", &thisTime.tm_hour, &PtrToCT->tm_min, &PtrToCT->tm_sec);
            scanf ("%c", &newlinebuf);
        }
        else if (response == 'n'){
            printf ("Ok. Closing program...\n");
            exit (0);
        }
        else{
            printf ("Answer must be 'y' or 'n'. Wrong input or unexpected behavior happened.\nClosing program...\n");
            exit (0);
        }
    }

    printf ("\nProgram will be closed in ");
    if (PtrToCT->tm_hour)
        printf ("%i hour/s", PtrToCT->tm_hour);
    if (PtrToCT->tm_min){
        if (PtrToCT->tm_hour)
            printf (", %i minute/s", PtrToCT->tm_min);
        else
            printf ("%i minute/s", PtrToCT->tm_min);
    }
    if (PtrToCT->tm_sec){
        if (PtrToCT->tm_hour || PtrToCT->tm_min)
            printf(" and %i second/s.\n", PtrToCT->tm_sec);
        else
            printf ("%i second/s.\n", PtrToCT->tm_sec);
    }
    timetowait = convertTime(PtrToCT);
    free (PtrToCT);
    sleep(timetowait);
}

int convertTime (struct tm *tm2Convert)
{
    int secInHr, secInMin, totaltime;

    secInHr = tm2Convert->tm_hour;
    secInHr *= 3600;
    #ifdef DEBUG
        printf ("DEBUG: secInHr = %i\n", secInHr);
    #endif // DEBUG

    secInMin = tm2Convert->tm_min * 60;
    #ifdef DEBUG
        printf ("DEBUG: secInMin = %i\n", secInMin);
    #endif // DEBUG

    totaltime = secInHr + secInMin + tm2Convert->tm_sec;
    #ifdef DEBUG
        printf ("DEBUG: %i is the time returned\n", totaltime);
    #endif // DEBUG
    return totaltime;
}



