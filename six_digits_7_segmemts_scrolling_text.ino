
    /*
    Project: Seven Segment Scrolling Texts using COMMON ANODES LEDs
     
    Written by: Anumbor Ogor (eocote2002@yahoo.com, +234-8036837259)
     
    Company: Hercules Technology.
    Address: OAU, New Central Mkt, Block 8, Office No. 11, Ile-Ife, Osun State, Nigeria
    Email:   eocote2002@yahoo.com
     
    Date:    15-Nov-2015, Sunday, 5.32 pm.
     
    Version: 1;
     
    The project uses:
    Six seven-segment (i.e. 2 units; one unit with 4 segments and the other unit with 2 segments)
     Arduino UNO R3 @16Mhz crystal and 20 I/O pins
    Bread board x1
    Jumper cables x20
    a 9V battery with battery clip and jack
     
    Pins:
    PORTD = data pins (pins 0, 1, 2, 3, 4, 5, 6, 7) though only seven is needed for segments. Pin 7 is optional
    PORTB = control pins (pins 8, 9, 10, 11, 12, 13).
     
    Project License:
    This project is released under creative common license (http://creativecommons.org/licenses/) type
    - Attribution CC BY - which allow others to distribute, remix, tweak, and build upon the authors work, even commercially, as long as they credit the author for the original creation. 
     
    Please note further, that the different projects published on this blog would use different licensing type, so readers of the blog are encouraged to read and understand the type of licenses projects are or would-be published and released, and to adhere strictly to the authors licensing specifications for each projects.
    */
     
    // display of seven segment modules
    // variables
    unsigned int frameRate = 0;
    unsigned int frameDelay = 0;
    unsigned int frameTemp = 0;
    unsigned int frameCount = 0;
    unsigned int multplxRate = 0;
    unsigned int sDelayCount = 0;
    unsigned int mulpxRate = 0;
     
    // array to hold screen buffer area
    String screenBufferString;
    int noOfSegments = 6;
     
    void setup() 
    {
      // put your setup code here, to run once:
        
       // pin declarations
       // for portd
       pinMode(0, OUTPUT); // A
       pinMode(1, OUTPUT); // B
       pinMode(2, OUTPUT); // C
       pinMode(3, OUTPUT); // D
       pinMode(4, OUTPUT); // E
       pinMode(5, OUTPUT); // F
       pinMode(6, OUTPUT); // G
     
       // for portb
       pinMode(8, OUTPUT); // A
       pinMode(9, OUTPUT); // B
       pinMode(10, OUTPUT); // C
       pinMode(11, OUTPUT); // D
       pinMode(12, OUTPUT); // E
       pinMode(13, OUTPUT); // F
       
       // Local Declarations
       mulpxRate = 2;
       frameRate = 1;
       
    } // end setup
     
    void loop() {
      screenBufferString = "1234567890  abcdefgh    hello there  this is hercules technology ";
     
      // put your main code here, to run repeatedly:
       leds_display();
    } // end loop for main code
     
    void leds_display()
    {
      int temp = screenBufferString.length();//sizeof(screenBufferString);
       while (temp != 0)
       {
          //printf("Inside display loop..\r\n");
          
          repeatFrame();
          
          rotateFrame();
          
          temp--;
       } // end while
    } // end display method
     
    void repeatFrame()
    {
      unsigned int temp = 50;
       displayScreenFrame();
       while(temp != 0) // wait until temp = 0
       {
          temp--;
       } // end while
    } // end repeatFrames
     
    void displayScreenFrame()
    {
      frameDelay = 30; // hex number
       
       while (frameDelay != 0)
       {
          frameTemp = 0x01;
          
          segmentScan();
          // moduleScan(); if using matrix LEDs
          
          // decrement by 1
          frameDelay--;
       } // end while
    } // end display screen frame
     
    void segmentScan()
    {
      // for 6 led 7 segments
       frameCount = noOfSegments; // use segmentCount
       
       // point to screen buffer location
       // portc is control signal byte***
       // portb is data    signal byte***   
       
       for (frameCount = 0; frameCount < noOfSegments; frameCount++)//while (frameCount != 0)
       {
          PORTB = 0x00; //(x'00');
          // use for statement to output
          
          //PORTB = B00111000;
          PORTD = getSegmentEquiv(screenBufferString[frameCount]);
          
          // send control signal to portc
          PORTB = frameTemp;
          
          // shift the bit to the right by 1
          frameTemp <<= 1; //frameTemp = frameTemp << 1;
          
          // clear last bit in frametemp
          bitClear(frameTemp, 0);
          
          // call shortdelay
          shortDelay();
          
          // clear portc control signal
          PORTB = 0x00;
          
       } // end for
          //--frameCount;
    } // end scan
     
    void rotateFrame() //once
    {
       int i; // character index pointer
       
       for (i = 0; i < screenBufferString.length(); i++)
       {
          // save current(old) data in present location
          char x = screenBufferString[i];
          
          // clear content of that present location
          screenBufferString[i] = ' '; // fill content with a white space
          
          // exchange data
          char y = x;
          
          // point to new location and pass data to new location
          screenBufferString[i-1] = y;      
          
       } // end for
       
    }// end function rotateFrame
     
    void shortDelay()
    {
       // Local Declarations
       int sDelayCount = 0;
       
       // Statements
       sDelayCount = mulpxRate;
       
       while(sDelayCount != 0)
       {
           delay(1);
          sDelayCount--;   
       } // end while
    } // end funcion sdelay
     
    int getSegmentEquiv(char value)
    {   
       int segValue = 0;
       
       // for common anode
            if (value == '0') segValue = 0x40;// 0x79; // end 0
       else if (value == '1') segValue = 0xF9;//0xF9; // 0x06;// end 1
       else if (value == '2') segValue = 0xA4;//0xA4; //0x5B;// end 2llkl
       else if (value == '3') segValue = 0xB0;//0xB0; // 0x4F;// end 3
       else if (value == '4') segValue = 0x99;//0x99; // 0x66;// end 4
       else if (value == '5') segValue = 0x92;//0x92; // 0x6D;// end 5
       else if (value == '6') segValue = 0x82;//0x82; // 0x7D;// end 6
       else if (value == '7') segValue = 0xF8;//0xF8; // 0x07;// end 7
       else if (value == '8') segValue = 0x80;//0x80; // 0x7F;// end 8
       else if (value == '9') segValue = 0x90;//0x90; // 0x6F;// end 9
       else if (value == ' ') segValue = 0xFF; // 0xFF;// end space
       else if (value == 'a') segValue = 0x20;
       else if (value == 'b') segValue = 0x03;
       else if (value == 'c') segValue = 0x27;
       else if (value == 'd') segValue = 0x21;
       else if (value == 'e') segValue = 0x04;
       else if (value == 'f') segValue = 0x0E;
       else if (value == 'g') segValue = 0x10;
       else if (value == 'h') segValue = 0x0B;
       else if (value == 'i') segValue = 0x7B;
       else if (value == 'j') segValue = 0x71;
       else if (value == 'k') segValue = 0xFF;
       else if (value == 'l') segValue = 0x47;
       else if (value == 'm') segValue = 0xFF;
       else if (value == 'n') segValue = 0x2B;
       else if (value == 'o') segValue = 0x23;
       else if (value == 'q') segValue = 0xFF;
       else if (value == 'r') segValue = 0x2F;
       else if (value == 's') segValue = 0x92;
       else if (value == 't') segValue = 0x07;
       else if (value == 'u') segValue = 0x63;
       else if (value == 'v') segValue = 0xFF;
       else if (value == 'w') segValue = 0xFF;
       else if (value == 'x') segValue = 0xFF;
       else if (value == 'y') segValue = 0x91;
       else if (value == 'z') segValue = 0xFF;
       else segValue = 0xFF; // use  ' '
       
       return segValue;
    } // end function segment Equivalent
