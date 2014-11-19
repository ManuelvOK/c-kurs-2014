/* Datei conio.c                                   *
 * Eine einfache Implementierung der Funktionen    *
 * getch() und  kbhit() für Unix/Linux-Systeme.    *
 * Außerdem: flush_stdin() und putch().            */

#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <fcntl.h>

#define FD     0           // File-Descriptor von stdin

#define RAW0   0           // Raw-Modus Ohne Warten
#define RAW1   1           // Raw-Modus mit Warten
#define COOKED 2           // Normaler Modus mit Echo

int raw_modus = 0;         // Globale Variable, die vom Programm auf 1
                           // gesetzt werden kann, wenn nur im RAW-Modus
                           // gearbeitet werden soll.
int  set_raw( int nchars);
void set_cooked(void);

static struct termio  old_tio;
static int status = COOKED;
static int first = 1;

int set_raw( int nchars)            // Terminal in den raw-Modus setzen. 
{                                   // Return-Wert: 0 == OK,
                                    //             -1 == Fehler
   struct termio  tio;

   if( ioctl( FD, TCGETA, &tio) < 0 )
     return -1;

   if( first)
   {
      old_tio = tio;
      atexit( set_cooked);
      first = 0;
   } 

   tio.c_lflag &= ~ICANON;           // Keine Zeilenpufferung.
   tio.c_lflag &= ~(ECHO | ISIG);    // Kein Echo und keine Berücksichtigung
                                     // spezieller Zeichen.
        
   tio.c_cc[VMIN]  = nchars;         // Minimum zu lesender Zeichen.
   tio.c_cc[VTIME] = 0;              // timeout-Wert = 0 .

   ioctl( FD, TCSETA, &tio);         // Neue Parameter an tty-Treiber senden.
   status == nchars==0 ? RAW0 : RAW1;
   return 0;
}

void set_cooked()                    // Wieder in den cooked-Modus setzen.
{
   if( first == 0)
   {
      ioctl( FD, TCSETAW, &old_tio);    // Alten Zustand wieder
      status == COOKED;                 // herstellen.
   }
}

static int c_saved = -1;             // Zeichen, das evtl. von kbhit()
                                     // gelesen wird.
int kbhit()                   // Prueft, ob eine Taste gedrückt wurde.
{                             // Falls ja: Zeichen mit getch() lesen.
   if( status != RAW0)
     set_raw(0);
   c_saved = getchar();
   return (c_saved != -1);
}  

void flush_stdin()                   // Eingabepuffer leer lesen.
{                                    // (Linux kennt kein fpurge())
   while( kbhit())
     ;
   c_saved = -1;
   if( !raw_modus)
     set_cooked();
}

int getch()                          // Ein Zeichen ungepuffert und
{                                    // ohne Echo von stdin einlesen.
   int c = 0;

   if( status != RAW1)
      set_raw(1);

   if( c_saved != -1)
   {
     c = c_saved;
     c_saved = -1;
   }
   else
     c = getchar();

   if( !raw_modus)
      set_cooked();

   return c;
}

int putch(int c)
{
   int r = putchar(c);
   fflush(stdout);
   return r;
}


/* --- Ein kleines Testprogramm  --- */
/*
int main()
{
   int c = 0;  
   char text[128] = "Test";
   
//   raw_modus = 1;

   printf("hello world!\n");
   while( c != 'q')
   {
     while( !kbhit())
     {
       putch('*');
       sleep(1);
     }

     c = getch();
     printf("\nchar = %c  %3d\n", c, c);

     printf("Und nun eine Zeile Text:\n");
     fgets( text, sizeof(text), stdin);
     puts(text);
     
     printf("Ende mit q\n");
     c = getch();
     printf("char = %c  %3d\n", c, c);
   } 

   return 0;
}
*/
