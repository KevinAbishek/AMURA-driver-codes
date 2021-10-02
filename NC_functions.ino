void func (char ch)
{
  if  (ch ==  'B')                                                                                              //  Backlash compensation toggle
  {
    switch  (Serial.parseInt())
    {
      case  0:  blc = 0 ; break ;
      case  1:  blc = 1 ; break ;
      default:  Serial.print  ('E') ; break ;
    }
  }
  else if  (ch ==  'b')                                                                                              //  Backlash compensation toggle
  {
      buzz_count (3, 100)  ;
  }
  else if (ch  ==  'd')                                                                                         //  Delay
  {
    del =  Serial.parseInt  () ;
  }
  else if (ch  ==  'H')                                                                                        //  Home position
  {
    switch  (Serial.parseInt())
    {
      case  0:  home_pos  () ; break ;
      case  1:  home_eject ()  ; break ;
      default:  Serial.print  ('E') ; break ;
    }
  }
  else if (ch  ==  'L')                                                                                        //  Light 1
  {
    inten = Serial.parseInt() ;
    if  ((inten  < 0)||(inten  > 254))
    inten = 0 ;
    analogWrite (LED1, inten)  ;
  }
  else if (ch ==  'M')                                                                                         //  Motor enable toggle
  {
    switch  (Serial.parseInt())
    {
      case  0:   buzz_count (2, 500)  ;  Xstepper.set_enable (false) ;  Ystepper.set_enable  (false) ; break ;
      case  1:  enable_lock () ; buzz_count (1, 1000)  ; break ;
      default:  buzz_count (1, 1000)  ; Xstepper.set_enable (false)  ; Ystepper.set_enable  (false) ; Serial.print  ('E') ; break  ;
    }
  }
  else if (ch  ==  'P')                                                                                        //  Program driver
  {
    prog  ()  ;
  }
  else if (ch  ==  'S')                                                                                        //  Program driver
  {
    Xstepper.set_enable (false) ;  Ystepper.set_enable  (false) ; analogWrite (LED1, 0)  ;
  }
  else if (ch  ==  'X')                                                                                        //  X step
  {
    SCX = Serial.parseInt () ;
    if  (SCX > 0)
    dirX = 1 ;
    else
    {dirX = 0  ; SCX  = -SCX ;}
  }
  else if (ch  ==  'Y')                                                                                        //  Y step
  {
    SCY = Serial.parseInt () ;
    if  (SCY > 0)
    dirY = 1 ;
    else
    {dirY = 0  ; SCY  = -SCY ;}
  }
  else
  {Serial.print ('E')  ;}
}
