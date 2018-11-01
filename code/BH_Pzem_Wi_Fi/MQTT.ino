AsyncMqttClient mqttClient; 
Ticker mqttReconnectTimer;

void onMqttConnect(bool sessionPresent) {
    logger("[MQTT] Connected to MQTT.");
    mqttClient.publish(availableTopic.c_str(),0,true,"1");
    //TODO SUBSCRIVE TOPICS
    mqttClient.publish(("homeassistant/sensor/"+nodeId+"/voltage/config").c_str(),0,true,("{\"name\": \""+(String(HARDWARE)+"_"+nodeId)+"_voltage\", \"state_topic\": \""+(String(HARDWARE)+"/"+nodeId)+"/readings/status\", \"value_template\": \"{{ value_json.voltagem }}\", \"unit_of_measurement\": \"V\",\"icon\":\"mdi:power-socket-eu\"}").c_str());   
    mqttClient.publish(("homeassistant/sensor/"+nodeId+"/amperage/config").c_str(),0,true,("{\"name\": \""+(String(HARDWARE)+"_"+nodeId)+"_amperage\", \"state_topic\": \""+(String(HARDWARE)+"/"+nodeId)+"/readings/status\", \"value_template\": \"{{ value_json.amperagem }}\", \"unit_of_measurement\": \"A\",\"icon\":\"mdi:power-socket-eu\"}").c_str());
    mqttClient.publish(("homeassistant/sensor/"+nodeId+"/power/config").c_str(),0,true,("{\"name\": \""+(String(HARDWARE)+"_"+nodeId)+"_power\", \"state_topic\": \""+(String(HARDWARE)+"/"+nodeId)+"/readings/status\", \"value_template\": \"{{ value_json.potencia }}\", \"unit_of_measurement\": \"W\",\"icon\":\"mdi:power-socket-eu\"}").c_str());  
    mqttClient.publish(("homeassistant/sensor/"+nodeId+"/energy/config").c_str(),0,true,("{\"name\": \""+(String(HARDWARE)+"_"+nodeId)+"_energy\", \"state_topic\": \""+(String(HARDWARE)+"/"+nodeId)+"/readings/status\", \"value_template\": \"{{ value_json.contador }}\", \"unit_of_measurement\": \"kWh\",\"icon\":\"mdi:power-socket-eu\"}").c_str());  
    mqttClient.publish(("homeassistant/sensor/"+nodeId+"/getTempC/config").c_str(),0,true,("{\"name\": \""+(String(HARDWARE)+"_"+nodeId)+"_temp\", \"state_topic\": \""+(String(HARDWARE)+"/"+nodeId)+"/readings/status\", \"value_template\": \"{{ value_json.temperatura }}\", \"unit_of_measurement\": \"ºC\",\"icon\":\"mdi:power-socket-eu\"}").c_str());  
}

void connectToMqtt() {
  logger("[MQTT] Connecting to MQTT ["+mqttIpDns+"]...");
  mqttClient.connect();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  logger("[MQTT] Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  String topicStr = String(topic);
  logger("[MQTT] TOPIC: "+topicStr);
       String payloadStr = "";
  for (int i=0; i<len; i++) {
    payloadStr += payload[i];
  }
  logger("[MQTT] PAYLOAD: "+payloadStr);
  if(processMqttAction(topicStr,payloadStr)){
    logger("[MQTT] Valid message: "+ payloadStr);
    }else{
      logger("[MQTT] Invalid message: "+ payloadStr);
    }
}

void setupMQTT() {

  if(WiFi.status() != WL_CONNECTED || mqttIpDns.equals(""))return;
  mqttClient.disconnect();
  mqttClient.onConnect(onMqttConnect);
  mqttClient.setClientId((String(HARDWARE)+"_"+nodeId).c_str());
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.setCredentials(mqttUsername.c_str(),mqttPassword.c_str());
  mqttClient.setCleanSession(false);
  mqttClient.setWill(availableTopic.c_str(),0,true,"0");
  mqttClient.setServer( mqttIpDns.c_str(), MQTT_BROKER_PORT);
 connectToMqtt();
}

void publishOnMqtt(String topic,String payload, bool retain){
  if(!topic.startsWith("/")){
    topic = "/"+topic;
    }
    Serial.println(nodeId);
    Serial.println(baseTopic+topic);
  mqttClient.publish((baseTopic+topic).c_str(), 0,retain,payload.c_str());
 }

 bool processMqttAction(String topic, String payload){
 return false;
 }
