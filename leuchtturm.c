
#include <uTPlib.h>
//#include <WProgram.h>
#include "main.h"

// Animationsfunktion eines Leuchtturms v0.03, von Sven Jonetat, 2012
//
// Lichtkegel soll sich in verschiedenen Farben und Längen aufbauen
// und somit einen sich drehenden Lichtkegel auf beide Seiten simulieren.
// Darstellung des Leuchtturms an wechselnden Stellen möglich.
//
//  Matrix und Farbe
//    x aus 0..DISPLAY_WIDTH-1   DISPLAY_WIDTH derzeit 32, wird noch bis 48 ausgebaut, vorher SCRdx
//    y aus 0..SCRdy-1   SCRdy ist 8 (Null oben, sieben unten)
//    r,g,b (rot,gruen,blau) aus unsignbed char (0..255)
// .... kein Gelb. weiss = alle an! rot+gruen = gelb, eventuell ein bisschen blau


void leuchtturm()                                // Animationsfunktion Leuchtturm
{
    // Standard stuff

    int counter = 80;                                // runs 80 steps

    int xt = 0;                                      // Koordinaten (Abkuerzung t (Turm) an x und y)
    int yt = 7;
    //int pos = rnd_range (0,DISPLAY_WIDTH-6);   // Zufallsposition (mit Abzug, so dass Leuchtturm auch im Bild ist)
    //int pos = DISPLAY_WIDTH / 2 - 2;       // Untere linke Ecke des Turms = Lichtpositionlinks auf X, Haelfte der Matrix minus 2

    int pos = 3;

    int xl = 0;                                      // Koordinaten Licht (Abk. l(Licht) an x und y)
    int yl = 7;
    int liposre = pos + 3;                           // Anfang vom Lichtstrahl auf x (Position Turm + Turmmitte)
    int lirend = DISPLAY_WIDTH;          // Ende des Lichtstrahls rechts


    int r = 0;                                       // Farben rot, gruen, blau
    int g = 0;
    int b = 0;
    // oder int r,g,b;

    while (counter--) {                              // Animationsschleife
        delay_ms (50);                                 // one step is 50ms
        display_buffer_swap (1);                       // 0:NoClear 1:ClearScreen(black) 2:copyScreen


        r = 255;                                         // Farbzuweisung in der Schleife
        g = 255;
        b = 255;

        /* Anfang Farbtest               // Anfang Farbtest
        for ( int r=255; r>0; r--)
        {
          g--;
          b--;
          delay_ms (30);
        for ( int yt = 0; yt<SCRdy; yt++)
          {
          for ( int xt = 0; xt<DISPLAY_WIDTH; xt++)
            {
              display_pixel_set (xt, yt, display_color_from_rgb ( r, g, b ) );
            }
          }
        }
        */                       // Ende Farbtest


        // Beginn des Leuchtturmbaus
        // Zeichnet eine Linie fuer Fuss
        for ( int xt = pos; xt < pos + 5; xt++) {          // Position in der Matrix (Frage ob an Pos 15 oder 16 erster Paint)-->15 erster paint
            // mit zu zeichnender Laenge  5
            display_pixel_set (xt, yt, display_color_from_rgb ( r, 0, 0 ) );                   // Farbe rot
        }

        // Zeichnet erste Linie ueber Fuss (yt-1), da yt = 7 unten ist
        for ( int xt = pos + 1; xt < pos + 4; xt++) {   // Position in der Matrix)
            // mit zu zeichnender Laenge 4
            display_pixel_set (xt, yt - 1, display_color_from_rgb ( 128, 128, 128 ) );         // Farbe weiss
        }

        // Zeichnet zweite Linie ueber Fuss (yt-2)
        for ( int xt = pos + 1; xt < pos + 4; xt++) {    // Position in der Matrix (Frage wo begin mir Zeichen und demnach Länge)
            // mit zu zeichnender Laenge von 4
            display_pixel_set (xt, yt - 2, display_color_from_rgb ( r, 0, 0 ) );               // Farbe rot
        }

        // Zeichnet Linie drei und vier und sieben ueber Fuss (yt-3,-4,-7)
        for ( int xt = pos + 1; xt < pos + 4; xt++) {   // Position in der Matrix
            // mit zu zeichnender Laenge von 4
            display_pixel_set (xt, yt - 3, display_color_from_rgb ( 128, 128, 128 ) );         // yt-3 in Farbe weiss
            display_pixel_set (xt, yt - 4, display_color_from_rgb ( r, 0, 0 ) );               // yt-4 in Frabe rot
            display_pixel_set (xt, yt - 7, display_color_from_rgb ( r, 0, 0 ) );           // yt-7 in Farbe rot
        }

        // Zeichnet die beiden Turmlichtebenen (yt-5 und yt-6)
        for ( int xt = pos; xt < pos + 5; xt++) {       // Position in der Matrix
            // mit zu zeichnender Laenge von 5
            display_pixel_set (xt, yt - 5, display_color_from_rgb ( 128, 128, 128 ) );      // yt-5 Farbe weiss
            display_pixel_set (xt, yt - 6, display_color_from_rgb ( 128, 128, 128 ) );      // yt-6 Farbe weiss
        }                                              // Ende Leuchtturmbau


        // Meerwasser rechts von Leuchtturm
        for ( int xt = pos + 5; xt < DISPLAY_WIDTH; xt++) {     // bis Ende der Matrix
            display_pixel_set (xt, yt, display_color_from_rgb ( 0, 0, 128 ) );             // in Farbe blau
        }

        // Sand nach links vom Leuchtturm
        for ( int xt = pos - 1; xt > 0; xt--) {             // bis Anfang der Matrix
            display_pixel_set (xt, yt, display_color_from_rgb ( 255, 255, 128 ) );          // in Farbe Gelb
        }


        // Ab jetzt Leuchtanimation bzw. Lichtstrahl


        for ( int lirend = DISPLAY_WIDTH; lirend > liposre; lirend--) { // Lichtstrahllänge

            r = 255;                                            // Farbe definieren r,g,b (255,255,128) = gelb;
            g = 255;
            b = 128;


            // Zeichnet Lichtstrahl von Lichtpositionrechts
            for ( int xl = liposre; xl < lirend; xl++) {    // Beginnt an liposre und endet vor lirend / DISPLAY_WIDTH
                if (xl - liposre < 4) {                       // erster Teil des Lichtstrahles schmal
                    display_pixel_set (xl, yl - 5, display_color_from_rgb ( r, g, b ) );           // yl-5 Farbe
                    display_pixel_set (xl, yl - 6, display_color_from_rgb ( r, g, b ) );           // yl-6 Farbe
                } else {                                      // entfernter Teil des Lichtstrahls breiter
                    if (xl - liposre < 5) {         // Antialaising Schritt
                        display_pixel_set (xl, yl - 4, display_color_from_rgb ( r - 95, g - 95, b - 95 ) );     // yl-4 Farbe
                        display_pixel_set (xl, yl - 5, display_color_from_rgb ( r, g, b ) );                // yl-5 Farbe
                        display_pixel_set (xl, yl - 6, display_color_from_rgb ( r, g, b ) );                // yl-6 Farbe
                        display_pixel_set (xl, yl - 7, display_color_from_rgb ( r - 95, g - 95, b - 95) );      // yl-7 Farbe
                    } else {
                        // jetzt breiter
                        display_pixel_set (xl, yl - 4, display_color_from_rgb ( r, g, b ) );            // yl-4 Farbe
                        display_pixel_set (xl, yl - 5, display_color_from_rgb ( r, g, b ) );            // yl-5 Farbe
                        display_pixel_set (xl, yl - 6, display_color_from_rgb ( r, g, b ) );            // yl-6 Farbe
                        display_pixel_set (xl, yl - 7, display_color_from_rgb ( r, g, b ) );            // yl-7 Farben
                    }
                }

                display_buffer_swap (2);                    // Übertragung des Bildes
                delay_ms (150);                     // warten und dann schwarz malen
                /*
                 // schwarz malen

                                 // Schwarzmalen des Lichtstrahls
                if (xl-liposre<4)                              // erster Teil des Lichtstrahles schmal
                 {
                   display_pixel_set (xl, yl-5, display_color_from_rgb ( 0, 0, 0 ) );             // yl-5 Farbe
                   display_pixel_set (xl, yl-6, display_color_from_rgb ( 0, 0, 0 ) );             // yl-6 Farbe
                 }
                else                                          // entfernter Teil des Lichtstrahls breiter
                 {
                 if (xl-liposre<5)               // Antialaising Schritt
                   {
                display_pixel_set (xl, yl-4, display_color_from_rgb ( 0, 0, 0 ) );           // yl-4 Farbe
                display_pixel_set (xl, yl-5, display_color_from_rgb ( 0, 0, 0 ) );           // yl-5 Farbe
                display_pixel_set (xl, yl-6, display_color_from_rgb ( 0, 0, 0 ) );           // yl-6 Farbe
                display_pixel_set (xl, yl-7, display_color_from_rgb ( 0, 0, 0 ) );           // yl-7 Farbe
                   }
                 else
                   {                     // jetzt breiter
                display_pixel_set (xl, yl-4, display_color_from_rgb ( 0, 0, 0 ) );           // yl-4 Farbe
                display_pixel_set (xl, yl-5, display_color_from_rgb ( 0, 0, 0 ) );           // yl-5 Farbe
                display_pixel_set (xl, yl-6, display_color_from_rgb ( 0, 0, 0 ) );           // yl-6 Farbe
                display_pixel_set (xl, yl-7, display_color_from_rgb ( 0, 0, 0 ) );           // yl-7 Farben
                   }
                 }
                display_buffer_swap (2); */
            }
        }

    }                                                // Ende While
}                                                 // Ende void
// ENDE Animationsfunktion eines Leuchtturms