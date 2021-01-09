// ESP32 Lite Pack Library -

#include "hardware.h"
#include "config.h"



/*********************************************************************/
// Global Variables
/*********************************************************************/
#define VERSION "0.1.0 openWB_EV-Simulator"



#ifdef ESP32 == true

#include <WiFi.h>
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = 34;
#endif



#ifdef ESP8266 == true

#include <ESP8266WiFi.h>
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = A0;

#endif

Pangodream_18650_CL BL( 34, 1.0);



// Replace with your network credentials
const char* ssid = "FRITZ!Box 7590 GM";
const char* password = "57943311541073535284";

//const char* Hostname = "SuperSoco";
const char* Hostname = "VW-ID-3";
//const char* Hostname = "TeslaModel-3";


// Set web server port number to 80
WiFiServer server(80);


// variable for storing the potentiometer value
int     potValue = 0;
long    previousMillis = 0;
long    interval = 5*1000;
long    LadeZaelerZeit = 0;
long    previousLadeZaelerMillis = 0;
double  LadeZaelerKWh = 0.0;
long    chageCurrent=0.0;

// Variable to store the HTTP request
String header;
String result = "";


// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;




void myCodeSetup()
{

  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);

#ifdef ESP32 == true  
 WiFi.setHostname( Hostname );
 WiFi.begin(ssid, password);
#endif

#ifdef ESP8266 == true 
  WiFi.begin((char*)ssid, (char*)password);
  WiFi.hostname( Hostname );
#endif

//  WiFi.begin((char*)ssid, (char*)password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}




String getplugstat()
{
  return "1";  
}

String getchargestat()
{
  return "1";  
}

String getAkkuSoC()
{
  return "51";  
}

String getBatSoC()
{
  return "61";  
}

String  getLadeleistung()
{
    return String( chageCurrent * 230);
}





String getLadeZaelerKWh()
{
  // / 3600 -> Wh
  // / 1000 -> KWh
  return String(LadeZaelerKWh);  
}

String  getLadeStromL1()
{
  return String(chageCurrent);  
}

String  getLadeStromL2()
{
  return "0";  
}

String  getLadeStromL3()
{
  return "0";  
}





void  sendNumber()
{
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
   // Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";
    result = "";                                  // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') 
        {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
//            Serial.println("Header = "+ header + "\n\r");
 
          
          
          if (currentLine.length() == 0) 
          {
              client.println("HTTP/1.1 200 OK");
              client.println("Connection: close");
              client.println();
    
              if (header.indexOf("GET /plugstat") >= 0) {
                result = getplugstat();
                Serial.println("plugstat = " + result  );
              
              } else if (header.indexOf("GET /chargestat") >= 0) {
                result = getchargestat();
                Serial.println("chargestat = " + result );
              
              } else if (header.indexOf("GET /SoC") >= 0) {
                result = getAkkuSoC();
                Serial.println("SoC = " + result + " %" );
 
              } else if (header.indexOf("GET /socBat") >= 0) {
                result = getBatSoC();
                Serial.println("socBat = " + result + " %" );
               
              } else if ( header.indexOf("GET /setcurrent?current=") >= 0) {
                int pos = header.indexOf('='); //finds location of first =
                Serial.print("pos = " );
                Serial.println( pos );
                result = header.substring(pos+1);   //captures first data String
                chageCurrent = result.toInt();
                if( chageCurrent > 6.5) chageCurrent = 6.5;
                Serial.print("Value = " );
                Serial.println( chageCurrent );
                
                Serial.println( "/setcurrent?current ************************************************************** = "+ result );

              } else if (header.indexOf("/Ladeleistung") >= 0) {
                result = getLadeleistung();
                Serial.println("Ladeleistung = " + result +" W" );


              } else if (header.indexOf("/LadeZaehlerKWh") >= 0) {
                result = getLadeZaelerKWh();
                Serial.println("LadeZaelerKWh = " + result +"KWh Zeit:" + LadeZaelerZeit );
              
              } else if (header.indexOf("/LadeStromL1") >= 0) {
                result = getLadeStromL1();
                Serial.println("LadeStromL1 = " + result +" A" );
              
              } else if (header.indexOf("/LadeStromL2") >= 0) {
                result = getLadeStromL2();
                Serial.println("LadeStromL2 = " + result +" A" );

              } else if (header.indexOf("/LadeStromL3") >= 0) {
                result = getLadeStromL3();
                Serial.println("LadeStromL3 = " + result +" A" );
              } 

          
              
              if(result != ""){
                 client.print( result  );
              } 
              
            
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
   // Serial.println("Client disconnected.");
    Serial.println("");

  }

  
}
double  mymap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



void setup()
{
  myCodeSetup();

  Serial.println("16 channel PWM test!");
 
  pwm1.begin();
  pwm1.setPWMFreq(50);  // This is the maximum PWM frequency
 
}





void loop()
{
 
 // orginalCode();
 // myCode();
    sendNumber();
  //aRESTLoop();
 unsigned long currentMillis = millis();

   if(currentMillis - previousLadeZaelerMillis > 1000) {
     previousLadeZaelerMillis = currentMillis;  
     LadeZaelerZeit++;
 
   
     double  LadeZaelerWs = chageCurrent * 230.0  ;

      //   Serial.println("LadeZaelerWs = " + String(LadeZaelerWs)  );
  
      double  LadeZaelerWh = LadeZaelerWs / 3600.0;

      // Serial.println("LadeZaelerWh = " + String(LadeZaelerWh)  );

      LadeZaelerKWh = LadeZaelerKWh + LadeZaelerWh / 1000.0; 

      
      
      pwm1.setPWM( 0, 1024, 3072);


   
   } 


 if(currentMillis - previousMillis > interval) {
   // save the last time you blinked the LED
   previousMillis = currentMillis;  
   
  potValue = analogRead(potPin);
  Serial.print("----------------------------potValue =" );
  Serial.println(potValue);

  double Voltage = mymap( potValue, 0.0 , 4095.0 , 0.2 , 3.1);

  Serial.print("Voltage  Map pin        : ");
  Serial.println( Voltage );
  
  Serial.print("Average value from pin: ");
  Serial.println(BL.pinRead());
  Serial.print("Volts                 : ");
  Serial.println(BL.getBatteryVolts());
  Serial.print("Charge level          : ");
  Serial.println(BL.getBatteryChargeLevel());
  Serial.println("");
  Serial.println("");
  
 
 
 
 }
  
 
}  
