#include <main.h>
// #include <SoftwareSerial.h>

int current_ledState = LOW;
int last_ledState = LOW;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

// SoftwareSerial zigbeeSerial(16, 17); // RX: GPIO16, TX: GPIO17

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_to_broker() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "IoTtest";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str()/*, MQTT_USER, MQTT_PASSWORD*/)) {
      Serial.println("connected");
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}
  
void callback(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");
  Serial.write(payload, length);
  Serial.println();
  
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Message content: ");
  Serial.println(message);
  
  if (message.equals("batden")) {  // Sửa thành "batden"
      // Code để bật đèn LED
      digitalWrite(22, HIGH); // Thay LED_BUILTIN bằng chân kết nối đèn LED
      
    }
  else if (message.equals("tatden")){
      digitalWrite(22, LOW); 
    }
  // zigbeeSerial.println(message);
  if (*payload == '1') current_ledState = HIGH;
  if (*payload == '0') current_ledState = LOW;
}

void setup() {
  pinMode(22, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();
}



void loop() {
  client.loop();
  if (!client.connected()) {
    connect_to_broker();
  }
  // if (zigbeeSerial.available()) {
  //   char buttonState = zigbeeSerial.read();
  //   if (buttonState == '0') {
  //     client.publish(MQTT_TOPIC, "Button Zigbee Pressed");
  //   }
  // }
  // if (last_ledState != current_ledState) {
  //   last_ledState = current_ledState;
  //   digitalWrite(22, current_ledState);
  //   Serial.println(current_ledState);
  // }
}
