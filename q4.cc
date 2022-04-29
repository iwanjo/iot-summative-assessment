#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#include "NodeMcu_ESP8266_Gmail_Sender_by_FMT.h"  

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "CANALBOX-0308";   // your network SSID (name) 
char pass[] = "1904358430";   // your network password
WiFiClient  client;


unsigned long myChannelId = 1719748;
const char * myWriteAPIKey = "VAH94TTF2XRQT5GI";
const char * myReadAPIKey = "J5YWSKVG2VA6L5JQ";


static const uint8_t D0 = 0;
static const uint8_t D2 = 2;

int fan = D2;
int DHT11_PIN = D0;

String recipientID;
String subject;
String body;

void CustomInfo(){ // function to set custom settings
  //replace the below three lines with your information
  recipientID = (String)"z.hiwa@alustudent.com"; // enter the email ID of the recipient
  subject = (String)"GreenHouse Moisture Value Alert"; // enter the subject of the email
  body = (String)"Moisture Values Have Dropped below minimum, please turn on irrigation system"; // enter the body of the email
  /*--------------------------------------------------------------*/
}

void setup(){
  
  Serial.begin(115200);
  pinMode(fan, OUTPUT);
  pinMode(A0,INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client); // Initialize ThingSpeak
}


void loop(){

  // Connect or reconnect to WiFi

  if(WiFi.status() != WL_CONNECTED){

    Serial.print("Attempting to connect to SSID: ");

    Serial.println("Connecting .... ");

    while(WiFi.status() != WL_CONNECTED){

      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network

      Serial.print(".");

      delay(5000);     

    } 

    Serial.println("\nConnected.");

  }
  
  
  // Read value from DHT pin
  DHT.read(DHT11_PIN);



  // Save values as variables
  float temp = DHT.temperature;
  
  Serial.print("Temp = ");
  Serial.println(temp);

  //read moisture
  float moisture = analogRead(A0);
  
  Serial.print("Moisture Value= ");
  Serial.println(moisture); 

  // Fan_Control
  if (temp > 27) {
    digitalWrite(fan, HIGH);
  }
  else if (temp < 27) {
    digitalWrite(fan, LOW);
  }

  //Email Control


  if (moisture < 25){
       Gsender *gsender = Gsender::Instance();
       CustomInfo();
       Serial.println("Email Sent");
  }

  
  // set the fields with the values
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, moisture);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelId, myWriteAPIKey);
  
  //read data that was previously added
  long dist = ThingSpeak.readLongField(myChannelId, 1, myReadAPIKey);
  
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(1000);
}
