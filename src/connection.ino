#include <Wire.h>
#include <WiFi.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

// WiFi network info.
const char *ssid =  "name";     // Enter your WiFi Name
const char *pass =  "pass"; // Enter your WiFi Password
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.println("Wrote to IMU");
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address is : ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop() {
  mpu_read();
  WiFiClient client = server.available();
  if (client) {                             
    Serial.println("new client");          
    String currentLine = "";                   //Storing the incoming data in the string
    while (client.connected()) {            
      if (client.available()) {                 // if there is some client data available                
        char c = client.read();                // read a byte
          if (c == '\n') {                      // check for newline character,                       
            if (currentLine.length != 0) {
              client.print("<html><title> ESP32 WebServer</title></html>");
              client.print("<body bgcolor=\"#E6E6FA\"><h1 style=\"text-align: center; color: blue\"> ESP32 WebServer </h1>");
              client.print("<p style=\"text-align: left; color: red; font-size:150% \">Accelerometer Values: ");
              client.print("<p style=\"text-align: left; font-size:150% \">AcX: ");
              client.print(AcX);
              client.print("<br/>AcY: ");
              client.print(AcY);
              client.print("<br/>AcZ: ");
              client.print(AcZ);
              client.print("<p style=\"text-align: left; color: red; font-size:150% \">Gyroscope Values: ");
              client.print("<p style=\"text-align: left; font-size:150% \">GyX: ");
              client.print(GyX);
              client.print("<br/>GyY: ");
              client.print(GyY);
              client.print("<br/>GyZ: ");
              client.print(GyZ);
              client.print("</p></body>");        
              break;  // break out of the while loop:
            } else {
              currentLine = "";
            }
          }
          else if ((c != '\r') {
            currentLine += c
          }
      }
    }
  }
}

void mpu_read() {
  void mpu_read(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  //Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("Accelerometer Values: \n");
  Serial.print("AcX: "); Serial.print(AcX); Serial.print("\nAcY: "); Serial.print(AcY); Serial.print("\nAcZ: "); Serial.print(AcZ);   
  //Serial.print("\nTemperature: " );  Serial.print(Tmp);
  Serial.print("\nGyroscope Values: \n");
  Serial.print("GyX: "); Serial.print(GyX); Serial.print("\nGyY: "); Serial.print(GyY); Serial.print("\nGyZ: "); Serial.print(GyZ);
  Serial.print("\n");
  delay(3000);
 }
}
