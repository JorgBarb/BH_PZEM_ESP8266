/*

BH FIRMWARE

Copyright (C) 2017-2018 by Bruno Horta <brunohorta82 at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/



#include "Config.h"
void checkServices(){
  if(laodDefaults){
    SPIFFS.format();
    shouldReboot = true;
  }

  if(wifiUpdated){
    saveConfig();
    reloadWiFiConfig();
    wifiUpdated = false;
    }
  if(needScan()){
      scanNewWifiNetworks();
   }
   if(reloadMqttConfiguration){
     setupMQTT();
   }
}

void setup() {
  Serial.begin(115200);
  loadStoredConfiguration();
  setupWiFi(); 
  setupWebserver(); 
  setupBHPzem();
  setupDisplay();
  
}

void loop() {
   MDNS.update();
   if(autoUpdate){
    autoUpdate = false;
    actualUpdate();
    }
  
  if(adopted){
   saveConfig();
   shouldReboot = true;
   adopted = false;
  }
   if(shouldReboot){
    logger("Rebooting...");
    shouldReboot = false;
    ESP.restart();
    return;
  }
  
    loopBHPzem();
  
  loopWiFi();
  checkServices();
  mqttMsgDigest();
  
}

void actualUpdate(){
  WiFiClient client;
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, updateUrl);
 
}
