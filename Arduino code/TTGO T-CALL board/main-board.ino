
#define BLYNK_TEMPLATE_ID "TMPLhRC0sI06"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "NFb8ouL4H7N-iTbm0HJ4kVvca1ONu7ZU"

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space



// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
// #define BLYNK_HEARTBEAT 30

// Please select the corresponding model

#define SIM800L_IP5306_VERSION_20190610
// #define SIM800L_AXP192_VERSION_20200327
// #define SIM800C_AXP192_VERSION_20200609
// #define SIM800L_IP5306_VERSION_20200811

#include "utilities.h"
#include <Wire.h>



#define relay5 12

#define relay1 14 // Valve 1

#define relay2 25 //Valve 2

#define relay3 33 //Pump 1

#define relay4 32 //Auto mode


// Select your modem:
#define TINY_GSM_MODEM_SIM800

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// See all AT commands, if wanted
//#define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon

// set GSM PIN, if any
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[] = "airtelgprs.com";  // search for apn of your network provider on Google
const char gprsUser[] = "";
const char gprsPass[] = "";


#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
TinyGsmClient client(modem);

int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag1_previous_II = 0;
int switch_ON_Flag1_previous_III = 0;
int switch_ON_Flag1_previous_IV = 0;

int y3 = 0;
int m3 = 0;
int d3 = 0;
int h3 = 0;
int min3 = 0;
int s3 = 0;
float timezone = 0;

int d=0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
const char auth[] = "NFb8ouL4H7N-iTbm0HJ4kVvca1ONu7ZU";

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay5, !pinValue);
  Serial.println("v0");
  DBG("relay5", pinValue);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay1, !pinValue);
  DBG("relay1", pinValue);
     
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay2, !pinValue);
  
  
  // process received value
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay3, !pinValue);
  
  
  // process received value
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(relay4, !pinValue);
  
  
  // process received value
}

BLYNK_WRITE(V5)
{
  int a1 = param.asInt();// assigning incoming value from pin V1 to a variable
  //digitalWrite(a1, !pinValue);
   DBG("a1", a1);
  Wire.beginTransmission(1);
  if(a1 == 1)
  {
    DBG("HI");
   Wire.write(88); 
   Wire.endTransmission();
  }
  if(a1 == 0)
  {
    DBG("H");
   Wire.write(89); 
   Wire.endTransmission();
  }
  
  
  // process received value
}

void setup()
{

  // Set console baud rate
  SerialMon.begin(115200);

  pinMode(relay5, OUTPUT);

  pinMode(relay1, OUTPUT);

  pinMode(relay2, OUTPUT);

  pinMode(relay3, OUTPUT);

  pinMode(relay4, OUTPUT);


  digitalWrite(relay5, HIGH);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);



  delay(10);

  setupModem();

  SerialMon.println("Wait...");

  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);

  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  Blynk.begin(auth, modem, apn, gprsUser, gprsPass);
  Wire.begin();
  
}


int a=0;
int a1 = 0;
void loop()
{
 
  
  Blynk.run();
  time();
  Default();
  Auto();
  DBG("Test:", h3);
  
  delay(1000);
 // Switch();
}

void time()
{

    if (modem.getNetworkTime(&y3, &m3, &d3, &h3, &min3, &s3,
                             &timezone)) {
    /*  DBG("Year:", y3, "\tMonth:", m3, "\tDay:", d3);
      DBG("Hour:", h3, "\tMinute:", min3, "\tSecond:", s3);
      DBG("Timezone:", timezone); */
      
    } else {
      DBG("Couldn't get network time, retrying in 15s.");
      delay(15000L);
    }
  }

void Auto()
{
  if(digitalRead(relay5) == LOW)
  {
   // Blynk.virtualWrite(V0, 1);
    if ((d3 == 28) && (h3 == 19))
    { 
      digitalWrite(relay1, LOW); 
      Blynk.virtualWrite(V1, 1); 
      delay(2000); 
      digitalWrite(relay2, LOW); 
      Blynk.virtualWrite(V2, 1); 
      delay(2000); 
      digitalWrite(relay1, HIGH); 
      Blynk.virtualWrite(V1, 0); 
      delay(2000); 
      digitalWrite(relay3, LOW); 
      Blynk.virtualWrite(V3, 1); 
      delay(2000); 
      digitalWrite(relay2, HIGH); 
      Blynk.virtualWrite(V2, 0); 
      delay(2000); 
      digitalWrite(relay4, LOW); 
      Blynk.virtualWrite(V4, 1); 
      delay(2000); 
      digitalWrite(relay3, HIGH); 
      Blynk.virtualWrite(V3, 0); 
      delay(2000); 
      digitalWrite(relay4, HIGH); 
      Blynk.virtualWrite(V4, 0);

      digitalWrite(relay5, HIGH);
      Blynk.virtualWrite(V0, 0);
    } 
  }
} 


   
void Default()
{
  if (a==0)
  {
   a = 1;
   Serial.println("entered the loop");
 
   Blynk.virtualWrite(V1, 0);
  
   Blynk.virtualWrite(V2, 0);
  
   Blynk.virtualWrite(V3, 0);
  
   Blynk.virtualWrite(V4, 0);

   Blynk.virtualWrite(V5, 0); //Auto mode
  
 } 
}

void Check()
{
  if (digitalRead(relay1) == LOW)
  {
    Serial.println("in");
    if (digitalRead(((relay2) == LOW) || ((relay3) == LOW) || ((relay4)) == LOW))
    {
      //delay(10000);
      digitalWrite(relay2, HIGH);
      Blynk.virtualWrite(V2, 0);
      digitalWrite(relay3, HIGH);
      Blynk.virtualWrite(V3, 0);
      digitalWrite(relay4, HIGH);
      Blynk.virtualWrite(V4, 0);
    }
  }
  if (digitalRead(relay2) == LOW)
  {
    if (digitalRead(((relay1) == LOW) || ((relay3) == LOW) || ((relay4)) == LOW))
    {
      Serial.println("its in");
      //delay(10000);
      digitalWrite(relay1, HIGH);
      Blynk.virtualWrite(V1, 0);
      digitalWrite(relay3, HIGH);
      Blynk.virtualWrite(V3, 0);
      digitalWrite(relay4, HIGH);
      Blynk.virtualWrite(V4, 0);
    }
  }
  if (digitalRead(relay3) == LOW)
  {
    if (digitalRead(((relay1) == LOW) || ((relay2) == LOW) || ((relay4)) == LOW))
    {
      //delay(10000);
      digitalWrite(relay1, HIGH);
      Blynk.virtualWrite(V1, 0);
      digitalWrite(relay2, HIGH);
      Blynk.virtualWrite(V2, 0);
      digitalWrite(relay4, HIGH);
      Blynk.virtualWrite(V4, 0);
    }
  } 
  if (digitalRead(relay4) == LOW)
  {
    if (digitalRead(((relay1) == LOW) || ((relay2) == LOW) || ((relay3)) == LOW))
    {
      //delay(10000);
      digitalWrite(relay1, HIGH);
      Blynk.virtualWrite(V1, 0);
      digitalWrite(relay2, HIGH);
      Blynk.virtualWrite(V2, 0);
      digitalWrite(relay3, HIGH);
      Blynk.virtualWrite(V3, 0);
    }
  }   
}
