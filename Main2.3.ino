//Initialize end stp switches

/*
 * Main2.3 added buzzer, hardware shutdown
 * Variables added:
 * hpos_status  = 0       -       int, while loop exit condition after both axes home, assume not home initially
 * xpos = 0               -       long, count steps along X dir from starting pos upto end stp, equal to 0 when starting, in 1/32 stpres, xrange  = 20000 (32)
 * ypos = 0               -       long, count steps along Y dir from starting pos upto end stp, equal to 0 when starting, in 1/32 stpres, yrange  = 12000 (32)
 * Y EJECT -10000 FROM HOME
 * X EJECT 7000 FROM HOME
 */


#include <DRV8711.h>
#include <EEPROM.h>

#define DRV8711_EEPROM_ADDR 0x100 // leave 256 bytes untouched


#  define XCSpin    37
#  define XSTEPpin  36
#  define XDIRpin   35
#  define XRESETpin 34
#  define YCSpin    25
#  define YSTEPpin  24
#  define YDIRpin   23
#  define YRESETpin 22
#  define LED1 5
#  define B1  2
#  define B2  3
# define  xLIM  6
# define  yLIM  7
# define  buzz  45

int del = 500, SCX = 0, SCY = 0, dirX = 1,  dirY  = 1,  inten =  0,  p_dirX  = dirX, p_dirY  = dirY  ;
int i = 3, blc = 1, blX = 750,  blY = 750,  xpos  = 0,  ypos  = 0  ;  //Normalized to 1/256 step resolution
bool up = false ;
float s = 256 ;

DRV8711 Xstepper  (XCSpin) ;
DRV8711 Ystepper  (YCSpin)  ;

void loop ()
{
    while (Serial.available  ())
    {
      char ch =  Serial.read  () ;
      func  (ch)  ;
    }
    if  (!digitalRead (B1))
    {
      delay (500)  ;
      do_stepX (0) ;
      do_stepY (0) ;
      if  (SCX  !=  0 ||  SCY !=  0)
    {
      SCX = 0 ;
      SCY = 0 ;
    }
    }
    else if (!digitalRead  (B2))
    {
      delay (500)  ;
      do_stepX (1) ;
      do_stepY (1) ;
      if  (SCX  !=  0 ||  SCY !=  0)
    {
      SCX = 0 ;
      SCY = 0 ;
    }
    }
    move_line (del)  ;
}
