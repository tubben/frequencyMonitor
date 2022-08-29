// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onCloudFrequencyChange();
void onCloudVrmsChange();
void onCloudBTNChange();
void onCloudLoadChange();
void onCloudLoadOverwriteChange();

float cloudFrequency;
float cloudVrms;
bool cloudBTN;
bool cloudLoad;
bool cloudLoadOverwrite;

void initProperties(){

  ArduinoCloud.addProperty(cloudFrequency, READWRITE, ON_CHANGE, onCloudFrequencyChange);
  ArduinoCloud.addProperty(cloudVrms, READWRITE, ON_CHANGE, onCloudVrmsChange);
  ArduinoCloud.addProperty(cloudBTN, READWRITE, ON_CHANGE, onCloudBTNChange);
  ArduinoCloud.addProperty(cloudLoad, READWRITE, ON_CHANGE, onCloudLoadChange);
  ArduinoCloud.addProperty(cloudLoadOverwrite, READWRITE, ON_CHANGE, onCloudLoadOverwriteChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
