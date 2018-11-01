#include "static_site.h"
#include "static_css.h"
#include "static_js.h"
#include "static_fonts.h"

// SKETCH BEGIN
AsyncWebServer server(80);

void  setupWebserver(){
  MDNS.begin(hostname.c_str());
  MDNS.addService("http","tcp",80);
  events.onConnect([](AsyncEventSourceClient *client){
    client->send(wifiJSONStatus().c_str(),"wifi");
    
  });

  server.addHandler(&events);
  /** HTML  **/
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html,sizeof(index_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request){
    activateScan();
    request->send(200,  "application/json","{\"result\":\"OK\"}");
  });
  
  server.on("/dashboard.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", dashboard_html,sizeof(dashboard_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/emoncms.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", emoncms_html,sizeof(emoncms_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/firmware.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", firmware_html,sizeof(firmware_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/gpios.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", gpios_html,sizeof(gpios_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/mqtt.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", mqtt_html,sizeof(mqtt_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/node.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", node_html,sizeof(node_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/wifi.html", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", wifi_html,sizeof(wifi_html));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  /** JS    **/
  server.on("/js/adminlte.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "application/js", adminlte_min_js,sizeof(adminlte_min_js));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
  server.on("/js/GaugeMeter.js", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "application/js", GaugeMeter_js,sizeof(GaugeMeter_js));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
  server.on("/js/index.js", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "application/js", index_js,sizeof(index_js));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/js/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "application/js", jquery_min_js,sizeof(jquery_min_js));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
   
  /** CSS   **/
  server.on("/css/AdminLTE.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", AdminLTE_min_css,sizeof(AdminLTE_min_css));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });

  /** FONTS **/
    server.on("/fonts/fontawesome-webfont.eot", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "font/eot", fontawesome_webfont_eot,sizeof(fontawesome_webfont_eot));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
      server.on("/fonts/fontawesome-webfont.woff", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "font/woff", fontawesome_webfont_woff,sizeof(fontawesome_webfont_woff));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
      server.on("/fonts/fontawesome-webfont.woff2", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "font/woff2", fontawesome_webfont_woff2,sizeof(fontawesome_webfont_woff2));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
      server.on("/fonts/FontAwesome.otf", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse_P(200, "font/otf", FontAwesome_otf,sizeof(FontAwesome_otf));
    response->addHeader("Content-Encoding", "gzip");
    response->addHeader("Expires","Mon, 1 Jan 2222 10:10:10 GMT");
    request->send(response);
  });
  /** JSON **/ 

 server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  readStoredConfig().printTo(*response);
  request->send(response);
  });
   server.on("/saveconfig", HTTP_POST, [](AsyncWebServerRequest *request){
   String node = request->hasArg("nodeId") ? request->arg("nodeId") : nodeId;
   saveConfig(node,
   request->hasArg("notificationInterval") ? request->arg("notificationInterval").toInt() : notificationInterval,
   request->hasArg("directionCurrentDetection") ? request->arg("directionCurrentDetection").toInt() : directionCurrentDetection,
   request->hasArg("emoncmsApiKey") ? request->arg("emoncmsApiKey") : emoncmsApiKey,
   request->hasArg("emoncmsPrefix") ?request->arg("emoncmsPrefix") : emoncmsPrefix,
   request->hasArg("emoncmsUrl") ? request->arg("emoncmsUrl") : emoncmsUrl,
   request->hasArg("mqttIpDns") ? request->arg("mqttIpDns") : mqttIpDns,
   request->hasArg("mqttUsername") ? request->arg("mqttUsername") : mqttUsername,
   request->hasArg("mqttPassword") ? request->arg("mqttPassword") : mqttPassword,
   request->hasArg("wifiSSID") ? request->arg("wifiSSID") : wifiSSID,
   request->hasArg("wifiSecret") ? request->arg("wifiSecret") : wifiSecret,
   
   hostname,request->hasArg("emoncmsPort") ? request->arg("emoncmsPort").toInt() : emoncmsPort);
   request->redirect("http://"+String(HARDWARE)+"-"+node+".local");
  });
  
   server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request){
   shouldReboot = true;
   request->redirect("/");
  });
   server.on("/loaddefaults", HTTP_GET, [](AsyncWebServerRequest *request){
   requestToLoadDefaults();
   request->send(200);
  });
  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
    shouldReboot = !Update.hasError();
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", shouldReboot? "<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <title>Atualização</title> <style>body{background-color: rgb(34, 34, 34); color: white; font-size: 18px; padding: 10px; font-weight: lighter;}</style> <script type=\"text/javascript\">function Redirect(){window.location=\"/\";}document.write(\"Atualização com sucesso, vai ser redirecionado automaticamente daqui a 30 segundos. Aguarde...\"); setTimeout('Redirect()', 30000); </script></head><body></body></html>":"<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <title>Atualização</title> <style>body{background-color: #cc0000; color: white; font-size: 18px; padding: 10px; font-weight: lighter;}</style> <script type=\"text/javascript\">function Redirect(){window.location=\"/\";}document.write(\"Atualização falhou, poderá ser necessário fazer reset manualmente ao equipamento e tentar novamente.\"); setTimeout('Redirect()', 10000); </script></head><body></body></html>");
    response->addHeader("Connection", "close");
    request->send(response);
  },[](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index){
      logger("[FIRMWARE] Update Start:"+ filename);
      Update.runAsync(true);
      if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)){
        Update.printError(Serial);
      }
    }
    if(!Update.hasError()){
      if(Update.write(data, len) != len){
        Update.printError(Serial);
      }
    }
    if(final){
      if(Update.end(true)){
        logger("[FIRMWARE] Update Success: "+String( index+len));
      } else {
        Update.printError(Serial);
      }
    }
  });

server.onNotFound([](AsyncWebServerRequest *request) {
  if (request->method() == HTTP_OPTIONS) {
    request->send(200);
  } else {
    request->send(404);
  }
});

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
}


void publishOnEventSource(String topic, String payload){
   events.send(payload.c_str(), topic.c_str());
}


