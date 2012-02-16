#include "main.h"

#include <uTPlib.h>

// Animationsfunktion eines Leuchtturms v0.01
//
// Lichtkegel soll sich in verschiedenen Farben und Längen aufbauen
// und somit einen sich drehenden Lichtkegel simulieren.
// Darstellung des Leuchtturms an wechselnden Stellen
//
//  Matrix und Farbe
//    x aus 0..SCRdx-1   SCRdx derzeit 32, wird noch bis 48 ausgebaut
//    y aus 0..SCRdy-1   SCRdy ist 8
//    r,g,b (rot,grün,blau) aus unsignbed char (0..255)
// .... kein Gelb??? Weiß = alle an?! r+g = gelb

void leuchtturm()                                // Animationsfunktion Leuchtturm
{
    // Standard stuff

    int counter = 80;                                // runs 80 steps
    int xt = 0;                                    // Koordinaten (Abkürzung t an x und y)
    int yt = 7;
    int pos = DISPLAY_WIDTH / 2 - 2;                                     // Untere Linke Ecke des Turms = Lichtpositionlinks auf X
    int liposre = pos + 3;                            // Anfang vom Lichtstrahl auf X (Position Turm + Turmbreite)
    int xl = 0, yl = 0;                                    // Koordinaten Licht (Abk. l an x und y)
    int r = 0, g = 0, b = 0;                                // Frage zur Variablendeklaration: Außerhalb der Schleife?

    while (counter--) {                              // Animationsschleife
        delay_ms (50);                                  // one step is 50ms
        display_buffer_swap (1);                                // 0:NoClear 1:ClearScreen(black)

        r = g = b = 255;                                    // Frage zur Variablendeklaration: Wertzuweisung ohne int?

        // Beginn des Leuchtturmbaus
        // Zeichnet eine Linie für Fuß
        for ( int xt = pos; xt < pos + 5; xt++) {          // Position in der Matrix (Frage ob an Pos 15 oder 16 erster Paint)-->15 erster paint
            // mit zu zeichnender Länge  5
            display_pixel_set (xt, yt, display_color_from_rgb ( r, 0, 0 ) );                   // Frabe rot
        }

        // Zeichnet erste Linie über Fuß (yt+1)
        for ( int xt = pos + 1; xt < pos + 3; xt++) {    // Position in der Matrix (Frage wo begin mir Zeichen und demnach Länge)
            // mit zu zeichnender Länge von 3 oder 4
            display_pixel_set (xt, yt - 1, display_color_from_rgb ( 255, 255, 255 ) );         // Farbe weiß
        }

        // Zeichnet zweite Linie über Fuß (yt+2)
        for ( int xt = pos + 1; xt < pos + 3; xt++) {    // Position in der Matrix (Frage wo begin mir Zeichen und demnach Länge)
            // mit zu zeichnender Länge von 3 oder 4
            display_pixel_set (xt, yt - 2, display_color_from_rgb ( r, 0, 0 ) );            // Farbe rot
        }

        // Zeichnet Linie drei und vier und sieben über Fuß (yt+3,+4,+7)
        for ( int xt = pos + 1; xt < pos + 3; xt++) {    // Position in der Matrix (Frage wo begin mir Zeichen und demnach Länge)
            // mit zu zeichnender Länge von 3 oder 4
            display_pixel_set (xt, yt - 3, display_color_from_rgb ( 255, 255, 255 ) );         // yt+3 in Farbe weiß
            display_pixel_set (xt, yt - 4, display_color_from_rgb ( r, 0, 0 ) );             // yt+4 in Frabe rot
            display_pixel_set (xt, yt - 7, display_color_from_rgb ( r, 0, 0 ) );       // yt+7 in Farbe weiß
        }

        // Zeichnet die beiden Turmlichtebenen (yt+5 und yt+6)
        for ( int xt = pos; xt < pos + 4; xt++) {          // Position in der Matrix (Frage ob an Pos 15 oder 16 erster Paint)
            // mit zu zeichnender Länge von 4 oder 5
            display_pixel_set (xt, yt - 5, display_color_from_rgb ( 255, 255, 255 ) );         // yt+5 Farbe weiß
            display_pixel_set (xt, yt - 6, display_color_from_rgb ( 255, 255, 255 ) );      // yt+6 Farbe weiß
        }                                                // Ende Leuchtturmbau

        // Ab jetzt Leuchtanimation bzw. Lichtstrahl

        r = 255;                                             // Farbe definieren rot + grün = gelb;
        g = 255;
        b = 128;

        // Zeichnet Lichtstrahl rechts vom Turm, Lichtpositionrechts
        for ( int xl = liposre; xl < DISPLAY_WIDTH; xl++) {    // Beginnt an liposre und endet vor SCRdx
            if (xl - liposre < 5) {                          // erster Teil des Lichtstrahles schmal
                display_pixel_set (xl, yl - 5, display_color_from_rgb ( r, g, b ) );              // yl+5 Farbe
                display_pixel_set (xl, yl - 6, display_color_from_rgb ( r, g, b ) );              // yl+6 Farbe
            } else {                                        // entfernter Teil des Lichtstrahls breiter
                display_pixel_set (xl, yl - 4, display_color_from_rgb ( r, g, b ) );             // yl+4 Farbe
                display_pixel_set (xl, yl - 5, display_color_from_rgb ( r, g, b ) );             // yl+5 Farbe
                display_pixel_set (xl, yl - 6, display_color_from_rgb ( r, g, b ) );             // yl+6 Farbe
                display_pixel_set (xl, yl - 7, display_color_from_rgb ( r, g, b ) );             // yl+7 Farbe
            }
        }                                                // Ende While
    }                                                // Ende void
}
// ENDE Animationsfunktion eines Leuchtturms
