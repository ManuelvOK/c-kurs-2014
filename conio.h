/* Header-Datei conio.h zur Quelldatei getch.c     * 
 *                                                 *
 * getch.c enthält eine einfache Implementierung   *
 * der Funktionen getch() und kbhit()              *
 * für Unix/Linux-Systeme.                         */

#if !defined _CONIO_H_
#define _CONIO_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int raw_modus;  // Globale Variable, die vom Programm auf 1
                       // gesetzt werden kann, wenn nur im RAW-Modus
                       // gearbeitet werden soll.
int kbhit(void);
int getch(void);
int putch(int c);

void flush_stdin();    // Eingabepuffer leer lesen.
// Anmerkung zu Unix:  fflush(stdin) leert nicht den Eingabepuffer.
// Linux kennt kein fpurge().

#ifdef __cplusplus
}
#endif

#endif  /* _CONIO_H_ */
