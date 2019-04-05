/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

//Create the BLE Device
  BLEDevice::init("ESP32 BLE Server");
  BLEServer *pServer = BLEDevice::createServer();                  //set the BLE as a server
  BLEService *pService = pServer->createService(SERVICE_UUID);     //create service for UUID defined earlier
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(           //set the characteristic
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |      //ie: read and write
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");            //anything you like (sensor reading, or state of a lamp)
  pService->start();                                 //Start the service!
  BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility* comment out if needed
//  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:        //refer to BLE_notify exammple to add something to happen when new client connects
  delay(2000);
}
