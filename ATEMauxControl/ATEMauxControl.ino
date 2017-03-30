#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>


// MAC address and IP address for this *particular* Ethernet Shield!
// MAC address is printed on the shield
// IP address is an available address you choose on your subnet where the switcher is also present:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xE8, 0xE9 };    // <= arudino mac
IPAddress ip(192, 168, 0, 55);        // <= arudino ip
IPAddress switcherIp(192, 168, 0, 50);     // <= SETUP!  IP address of the ATEM Switcher

// Include ATEM library and make an instance:
#include <ATEMbase.h>

#include <ATEMstd.h>
ATEMstd AtemSwitcher;




//aux hold
int AuxSelect = 1;

/////////////////////////button input settings ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


//select pin numbers 

int buttonPC = 7;
int PCread = 0;

int buttonCam2 = 6;
int Cam2read = 0;

int buttonPGM = 5;
int PGMread = 0;


int buttonAux1 = 45;
int Aux1read = 0;

int buttonAux3 = 35;
int Aux2read = 0;

int buttonAux4 = 25;
int Aux3read = 0;


int button1 = 49;
int source1read = 0;

int button2 = 39;
int source2read = 0;

int button3 = 29;
int source3read = 0;

// led pin numbers
    const int ledAux1 =  22;
    const int ledAux2 =  24;
    const int ledAux3 =  26;





///////////////////////////////////////////////////////////////////////////////////////






////////////////////////setup runs once////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void setup() { 

//indicators
  pinMode(ledAux1, OUTPUT);
  pinMode(ledAux2, OUTPUT);
  pinMode(ledAux3, OUTPUT);


//buttons
pinMode(buttonPC,   INPUT_PULLUP);//pc       aux 2
pinMode(buttonCam2, INPUT_PULLUP);//cam2     aux 2
pinMode(buttonPGM,  INPUT_PULLUP);//PGM      aux 2


pinMode(buttonAux1,   INPUT_PULLUP);//pc       aux 1
pinMode(buttonAux3,   INPUT_PULLUP);//cam2     aux 3
pinMode(buttonAux4,   INPUT_PULLUP);//PGM      aux 4


pinMode(button1,   INPUT_PULLUP);//pc       Source 1
pinMode(button2,   INPUT_PULLUP);//cam2     Source 2
pinMode(button3,   INPUT_PULLUP);//PGM      Source 3

  
  delay(1000); //allows ethernet too boot up
  
  // Start the Ethernet, Serial (debugging) and UDP:
  Ethernet.begin(mac,ip);

  //starts serial debugger
  //Serial.begin(9600); //****reenable Serial.print for Debuging 

  // Initialize a connection to the switcher:
  AtemSwitcher.begin(switcherIp);
  AtemSwitcher.serialOutput(0x80);
  AtemSwitcher.connect();
}

///////////////////////////////////objects/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////



///////////////////////////Main Loop///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void loop() {
// On ATEM 1M/E: Black (0), 1 (1), 2 (2), 3 (3), 4 (4), 5 (5), 6 (6), 7 (7), 8 (8), Bars (9), Color1 (10), Color 2 (11), Media 1 (12), Media 1 Key (13), Media 2 (14), Media 2 Key (15), Program (16), Preview (17), Clean1 (18), Clean 2 (19)

     
  // Check for packets, respond to them etc. Keeping the connection alive DO NOT REMOVE!
  AtemSwitcher.runLoop();
  //////////////////////////////////////////////////////////////////////////////////////




  //example ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // first value is the aux second value is the output
  // On ATEM 1M/E: Black (0), 1 (1), 2 (2), 3 (3), 4 (4), 5 (5), 6 (6), 7 (7), 8 (8), Bars (9), Color1 (10), Color 2 (11), Media 1 (12), Media 1 Key (13), Media 2 (14), Media 2 Key (15), Program (16), Preview (17), Clean1 (18), Clean 2 (19)
  //AtemSwitcher.changeAuxState(2,2);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //switches aux 1 to PC

 ////READING PINS/////////////////////////////////////////////////////

  
  // Aux 2 Source Select 
  PCread = digitalRead(buttonPC);
  Cam2read = digitalRead(buttonCam2);
  PGMread = digitalRead(buttonPGM);

/////////////////////////////////////////////////////////////////////////////////////
  //aux select 
  Aux1read = digitalRead(buttonAux1);
  Aux2read = digitalRead(buttonAux3);
  Aux3read = digitalRead(buttonAux4);



  source1read = digitalRead(button1);
  source2read = digitalRead(button2);
  source3read = digitalRead(button3);

// slows down program prevents overloading the switcher
//delay(100);
  
  
  if(Aux1read == 0){
    AuxSelect = 1;
    //Serial.println("AUX 1");
  }


  ////////////////////////////////////////////////////////
 
  if(Aux2read == 0){
    AuxSelect = 3;
    //Serial.println("AUX 3");
  }


  ////////////////////////////////////////////////////////
  
  if(Aux3read == 0){
    AuxSelect = 4;
    //Serial.println("AUX 4");
  }


  //Source select 
  


//Serial.println(AuxSelect);

          if((source1read == 0)&&(AtemSwitcher.getAuxState(AuxSelect) !=  1)){
          AtemSwitcher.changeAuxState(AuxSelect,1);
          //Serial.println("source 1    ");
          
          }
          if((source2read == 0)&&(AtemSwitcher.getAuxState(AuxSelect) !=  3)){
          AtemSwitcher.changeAuxState(AuxSelect,3);
          //Serial.println("source 2  ");
          
          }
          if((source3read == 0)&&(AtemSwitcher.getAuxState(AuxSelect) !=  10010)){
          AtemSwitcher.changeAuxState(AuxSelect,10010);
          //Serial.println("source 3   ");
          //Serial.print("AUX 4");
          }
  
 

/////////////////////////////////////////////////////////////////////
     
                    if ((PCread == 0)&&(AtemSwitcher.getAuxState(2) !=  1)){
                    //Serial.println("AUX 2 to PC");
                    AtemSwitcher.changeAuxState(2,1);
                    }
                    
                    if ((Cam2read == 0)&&(AtemSwitcher.getAuxState(2) !=  3)){
                    //Serial.println("AUX 2 to Cam2");
                    AtemSwitcher.changeAuxState(2,3);
                    }

                    if ((PGMread == 0)&&(AtemSwitcher.getAuxState(2) !=  10010)){
                    //Serial.println("AUX 2 to PGM");
                    AtemSwitcher.changeAuxState(2,10010);
                    }
                    /*
                    Serial.println("Last AUX") + (AuxSelect);
                    Serial.println(AuxSelect);
                    delay (100);*/
 

/////////////////////////////////////////////////////////////////////
//indicators 


switch (AuxSelect) {
    case 1:
      digitalWrite(ledAux1, HIGH);
      
      digitalWrite(ledAux2, LOW);
      digitalWrite(ledAux3, LOW);
      break;
    case 3:
      digitalWrite(ledAux2, HIGH);
      
      digitalWrite(ledAux1, LOW);
      digitalWrite(ledAux3, LOW);
      break;
    case 4:
      digitalWrite(ledAux3, HIGH);
      
      digitalWrite(ledAux1, LOW);
      digitalWrite(ledAux2, LOW);
      
      break;
    default: 
      digitalWrite(ledAux1, LOW);
      digitalWrite(ledAux2, LOW);
      digitalWrite(ledAux3, LOW);
    break;
  }












}

//end of program

/*

    case 0:  // Black
      return 0;
    case 1:  // Input 1
      return 1;
    case 2:  // Input 2
      return 2;
    case 3:  // Input 3
      return 3;
    case 4:  // Input 4
      return 4;
    case 5:  // Input 5
      return 5;
    case 6:  // Input 6
      return 6;
    case 7:  // Input 7
      return 7;
    case 8:  // Input 8
      return 8;
    case 9:  // Input 9
      return 9;
    case 10:  // Input 10
      return 10;
    case 11:  // Input 11
      return 11;
    case 12:  // Input 12
      return 12;
    case 13:  // Input 13
      return 13;
    case 14:  // Input 14
      return 14;
    case 15:  // Input 15
      return 15;
    case 16:  // Input 16
      return 16;
    case 17:  // Input 17
      return 17;
    case 18:  // Input 18
      return 18;
    case 19:  // Input 19
      return 19;
    case 20:  // Input 20
      return 20;
    case 1000:  // Color Bars
      return 21;
    case 2001:  // Color 1
      return 22;
    case 2002:  // Color 2
      return 23;
    case 3010:  // Media Player 1
      return 24;
    case 3011:  // Media Player 1 Key
      return 25;
    case 3020:  // Media Player 2
      return 26;
    case 3021:  // Media Player 2 Key
      return 27;
    case 4010:  // Key 1 Mask
      return 28;
    case 4020:  // Key 2 Mask
      return 29;
    case 4030:  // Key 3 Mask
      return 30;
    case 4040:  // Key 4 Mask
      return 31;
    case 5010:  // DSK 1 Mask
      return 32;
    case 5020:  // DSK 2 Mask
      return 33;
    case 6000:  // Super Source
      return 34;
    case 7001:  // Clean Feed 1
      return 35;
    case 7002:  // Clean Feed 2
      return 36;
    case 8001:  // Auxilary 1
      return 37;
    case 8002:  // Auxilary 2
      return 38;
    case 8003:  // Auxilary 3
      return 39;
    case 8004:  // Auxilary 4
      return 40;
    case 8005:  // Auxilary 5
      return 41;
    case 8006:  // Auxilary 6
      return 42;
    case 10010:  // ME 1 Prog
      return 43;
    case 10011:  // ME 1 Prev
      return 44;
    case 10020:  // ME 2 Prog
      return 45;
    case 10021:  // ME 2 Prev
      return 46;
    default:
      return 0;
  }
}
*/
