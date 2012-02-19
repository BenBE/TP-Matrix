
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

static void draw_leuchtturm(coord_t pos);
static void draw_light(coord_t lipos_start, coord_t lipos_end);

static void draw_leuchtturm(coord_t pos) {
    color_t r = 255;                                         // Farbzuweisung in der Schleife

    int yt = 7;                                      // Koordinaten (Abkuerzung t (Turm) an x und y)

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
    for ( int xt = pos - 1; xt > 0; xt--) {            // bis Anfang der Matrix
        display_pixel_set (xt, yt, display_color_from_rgb ( 255, 255, 128 ) );          // in Farbe Gelb
    }
}

static void draw_light(coord_t lipos_start, coord_t lipos_end) {
    const coord_t yl = 7;

    int r,g,b;
    b = (1 + (r = g = 255)) / 2;                                         // Farbzuweisung in der Schleife

    int swapped;
    // Zeichnet Lichtstrahl von Lichtpositionrechts
    if( (swapped = (lipos_start > lipos_end)) ) {
        //Swap values
        lipos_start ^= lipos_end;
        lipos_end ^= lipos_start;
        lipos_start ^= lipos_end;
    }

    for ( coord_t x = lipos_start; x <= lipos_end; x++) {    // Beginnt an liposre und endet vor lirend / DISPLAY_WIDTH
        coord_t d = swapped ? lipos_end - x : x - lipos_start;

        if (d < 4) {                       // erster Teil des Lichtstrahles schmal
            display_pixel_set (x, yl - 5, display_color_from_rgb ( r, g, b ) );           // yl-5 Farbe
            display_pixel_set (x, yl - 6, display_color_from_rgb ( r, g, b ) );           // yl-6 Farbe
        } else if (d < 5) {         // Antialaising Schritt
            display_pixel_set (x, yl - 4, display_color_from_rgb ( r - 95, g - 95, b - 95 ) );     // yl-4 Farbe
            display_pixel_set (x, yl - 5, display_color_from_rgb ( r, g, b ) );                // yl-5 Farbe
            display_pixel_set (x, yl - 6, display_color_from_rgb ( r, g, b ) );                // yl-6 Farbe
            display_pixel_set (x, yl - 7, display_color_from_rgb ( r - 95, g - 95, b - 95) );      // yl-7 Farbe
        } else {
            // jetzt breiter
            display_pixel_set (x, yl - 4, display_color_from_rgb ( r, g, b ) );            // yl-4 Farbe
            display_pixel_set (x, yl - 5, display_color_from_rgb ( r, g, b ) );            // yl-5 Farbe
            display_pixel_set (x, yl - 6, display_color_from_rgb ( r, g, b ) );            // yl-6 Farbe
            display_pixel_set (x, yl - 7, display_color_from_rgb ( r, g, b ) );            // yl-7 Farben
        }
    }
}

void leuchtturm()                                // Animationsfunktion Leuchtturm
{
    // Standard stuff

    int counter = 5;                                // runs 80 steps

    const int pos = random_range (0, DISPLAY_WIDTH-6);   // Zufallsposition (mit Abzug, so dass Leuchtturm auch im Bild ist)
    const int double_rot = random_range(0, 2);
    //int pos = DISPLAY_WIDTH / 2 - 2;       // Untere linke Ecke des Turms = Lichtpositionlinks auf X, Haelfte der Matrix minus 2

    //int pos = 3;

    const int liposre = pos + 3;                           // Anfang vom Lichtstrahl auf x (Position Turm + Turmmitte)
    const int liposli = pos + 1;
//    int lirend = DISPLAY_WIDTH;          // Ende des Lichtstrahls rechts


    display_buffer_write_set(0);
    display_clear_black();
    display_buffer_active_set(0);
    display_buffer_write_set(1);

    display_clear_black();
    draw_leuchtturm(pos);

    display_buffer_write_set(0);

    if(!double_rot) {
        while (counter--) {                              // Animationsschleife
            // Ab jetzt Leuchtanimation bzw. Lichtstrahl
            for ( int lirend = liposre; lirend < DISPLAY_WIDTH; lirend++) { // Lichtstrahllänge
                display_buffer_copy(1, 0);
                draw_light( liposre, lirend );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                delay_ms (50);                     // warten und dann schwarz malen
            }

            for ( int lirend = DISPLAY_WIDTH; lirend > liposre; lirend--) { // Lichtstrahllänge
                display_buffer_copy(1, 0);
                draw_light( liposre, lirend );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                delay_ms (50);                     // warten und dann schwarz malen
            }


            for ( int lilend = liposli; lilend >= 0; lilend--) { // Lichtstrahllänge
                display_buffer_copy(1, 0);
                draw_light( liposli, lilend );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                delay_ms (50);                     // warten und dann schwarz malen
            }

            for ( int lilend = 0; lilend < liposli; lilend++) { // Lichtstrahllänge
                display_buffer_copy(1, 0);
                draw_light( liposli, lilend );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                delay_ms (50);                     // warten und dann schwarz malen
            }
        }                                                // Ende While
    } else {
        while (counter--) {                              // Animationsschleife
            // Ab jetzt Leuchtanimation bzw. Lichtstrahl

            for ( int n = 0; n < DISPLAY_WIDTH; n++) { // Lichtstrahllänge
                display_buffer_copy(1, 0);
                draw_light( liposli, liposli < n ? 0 : liposli - n );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                draw_light( liposre, liposre + n );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                delay_ms (50);                     // warten und dann schwarz malen
            }

            for ( int n = DISPLAY_WIDTH; n >= 0; n--) { // Lichtstrahllänge
                display_buffer_copy(1, 0);
                draw_light( liposli, liposli < n ? 0 : liposli - n );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                draw_light( liposre, liposre + n );            // Zeichnet Lichtstrahl von Lichtpositionrechts
                delay_ms (50);                     // warten und dann schwarz malen
            }
        }
    }
}                                                 // Ende void
// ENDE Animationsfunktion eines Leuchtturms
