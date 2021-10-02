void do_stepX (byte dir)
{
  if  (p_dirX !=  dir &&  blc ==  1)
  {
    for (int i = 0 ; i < (int)((blX)*s/256.0) ; i++)
    {
      digitalWrite (XDIRpin, dir) ;
      digitalWrite (XSTEPpin, HIGH) ;
      delayMicroseconds (2) ;
      digitalWrite (XSTEPpin, LOW) ;
      delayMicroseconds (100*256/s) ;
    }
  }
  digitalWrite (XDIRpin, dir) ;
  digitalWrite (XSTEPpin, HIGH) ;
  delayMicroseconds (2) ;
  digitalWrite (XSTEPpin, LOW) ;
  p_dirX  = dir ;
}

void do_stepY (byte dir)
{
  if  (p_dirY !=  dir &&  blc ==  1)
  {
    for (int i=0 ; i < (int)((blY)*s/256.0) ; i++)
    {
      digitalWrite (YDIRpin, dir) ;
      digitalWrite (YSTEPpin, HIGH) ;
      delayMicroseconds (2) ;
      digitalWrite (YSTEPpin, LOW) ;
      delayMicroseconds (100*256/s) ;
    }
  }
  digitalWrite (YDIRpin, dir) ;
  digitalWrite (YSTEPpin, HIGH) ;
  delayMicroseconds (2) ;
  digitalWrite (YSTEPpin, LOW) ;
  p_dirY  = dir ;
}

void prog ()
{
  /*
 * Function to reprogram the stepper motor drivers to required settings
 */
  Xstepper.set_enable (false) ;
  Ystepper.set_enable (false) ;
  delay (10) ;
  if(Serial.read  ()  ==  'r')
  {s=Serial.parseInt  ()  ;}
  if(Serial.read  ()  ==  'i')
  {i  = Serial.parseInt () ;}
  Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
  Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
  delay (10) ;
  Xstepper.set_enable (true) ;
  Ystepper.set_enable (true) ;
  delay (10) ;
}

void home_pos ()
{
  /*
 * Function to return slide table to home position
 */
  xpos  = 0  ;
  ypos  = 0 ;
  int del1 = 500 ;
  int s1 = s,  i1 = i  ;
  s = 32  ; i = 3 ;
  Xstepper.set_enable (false) ;
  Ystepper.set_enable (false) ;
  delay (10) ;
  Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
  Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
  delay (10) ;
  Xstepper.set_enable (true) ;
  Ystepper.set_enable (true) ;
  delay (10) ;
  while (digitalRead  (xLIM))
  { 
    do_stepX  (0)  ;
    delayMicroseconds (del1)  ;
    xpos--  ;
  }
  for(int gap = 0 ; gap < 500  ; gap++)
  {
    do_stepX  (1);
    delayMicroseconds (del1) ;
  }
  xpos = (xpos  + 500) ;
  while (digitalRead  (yLIM))
  { 
    do_stepY  (1)  ;
    delayMicroseconds (del1)  ;
    ypos++  ;
  }
  for(int gap = 0 ; gap < 500  ; gap++)
  {
    do_stepY  (0);
    delayMicroseconds (del1) ;
  }
  ypos = (ypos - 500) ;
  Xstepper.set_enable (false) ;
  Ystepper.set_enable (false) ;
  s = s1  ; i = i1  ;
  delay (10) ;
  Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
  Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
  delay (10) ;
  Xstepper.set_enable (true) ;
  Ystepper.set_enable (true) ;
  delay (10) ;
}

void  enable_lock ()
{   
  /*
 * Function to actively hold/lock the steppers 
 */
    int s1 = s,  i1 = i  ;
    s = 256 ; i = 3 ;
    Xstepper.set_enable (false) ;
    Ystepper.set_enable  (false) ;
    Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
    Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
    delay (10) ;
    Xstepper.set_enable (true) ;
    Ystepper.set_enable  (true) ;
    delay (10) ;
    SCX=1000;SCY=1000;dirX=1;dirY=1;move_line (1000)  ;
    SCX=1000;SCY=1000;dirX=0;dirY=0;move_line (1000)  ;
    Xstepper.set_enable (false) ;
    Ystepper.set_enable  (false) ;
    s = s1  ; i = i1  ;
    delay (10) ;
    Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
    Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
    Xstepper.set_enable (true) ;
    Ystepper.set_enable  (true) ;
    delay (10) ;    
}

void  home_eject ()
{ 
  /*
 * Function to navigate slide table to eject position allowing user to swap slides/samples to be scanned
 */
    home_pos  ()  ;
    int s1 = s,  i1 = i  ;
    s = 32 ; i = 3 ;
    Xstepper.set_enable (false) ;
    Ystepper.set_enable  (false) ;
    Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
    Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
    delay (10) ;
    Xstepper.set_enable (true) ;
    Ystepper.set_enable  (true) ;
    delay (10) ;
    SCX = 7500  ; dirX  = 1 ; SCY = 10600 ; dirY  = 0 ;
    move_line (200)  ;
    while(Serial.read() != 'H'){}
    SCX = 1750  ; dirX  = 0 ; SCY = 8375  ; dirY  = 1 ;
    move_line (200)  ;
    Xstepper.set_enable (false) ;
    Ystepper.set_enable  (false) ;
    s = s1  ; i = i1  ;
    delay (10) ;
    Xstepper.begin (60, s, 2, 0, 1, 0, i) ;
    Ystepper.begin (60, s, 2, 0, 1, 0, i) ;
    Xstepper.set_enable (true) ;
    Ystepper.set_enable  (true) ;
    delay (10) ;    
}

void  move_line (int  del1)
{
  /*
 * Function to move the slide in a linear motion wrt the objective lens (camera)
 */
  while ((SCX  !=  0) || (SCY  !=  0))
  {
    if  (SCX  !=  0)
    {
      do_stepX (dirX)  ;
      delayMicroseconds (del1)  ;
      SCX-- ;
      if  ((SCX  ==  0) &&  (SCY ==  0))
      {Serial.println ('F')  ;}
    }
    if  (SCY  !=  0)
    {
      do_stepY (dirY)  ;
      delayMicroseconds (del1)  ;
      SCY-- ;
      if  ((SCY  ==  0) &&  (SCX ==  0))
      {Serial.println ('F')  ;}
    }
  }
}

void buzz_count (int  x,  int del)
{
  for(int i = 0;  i < x;  i++)
    {
      analogWrite  (buzz,  255)  ;
      delay (del) ;
      analogWrite (buzz,  0)  ;
      delay (del) ;
    }
}
