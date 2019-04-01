/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 0; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      //ORIGINAL Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
      //NEW
      Serial.printf("Adv: %6d %10s %4d %s \n", millis(), advertisedDevice.getName().c_str(), advertisedDevice.getRSSI(), 
      advertisedDevice.getAddress().toString().c_str());
      //NEW
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning....");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(),true); //want duplicates
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  //pBLEScan->setInterval(100);
  //pBLEScan->setWindow(99);  // less or equal setInterval value
  //NEW originally in loop()
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  //end NEW

}

void loop() {
  // put your main code here, to run repeatedly:
   pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}
