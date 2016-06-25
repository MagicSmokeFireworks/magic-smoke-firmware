// MAGIC SMOKE

// includes
#include "application.h"
#include "stdarg.h"

// photon preproc setup stuff
PRODUCT_ID(PLATFORM_ID);
PRODUCT_VERSION(3);

#if Wiring_WiFi
STARTUP(System.enable(SYSTEM_FLAG_WIFITESTER_OVER_SERIAL1));
#endif

// semi auto system mode will connect to preconfigured wifi, but not cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// use external wifi antenna
STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

// define pin aliases
#define fire0 D3
#define fire1 D4
#define fire2 D5
#define fire3 D6
#define fire4 D2
#define fire5 D1
#define fire6 D0
#define fire7 TX

#define sense0 A0
#define sense1 A1
#define sense2 A2
#define sense3 A3
#define sense4 A4
#define sense5 A5
#define sense6 DAC
#define sense7 WKP

#define senseswitch RX

#define armsense D7

// initialize tcp server/client info
int serverPort = 8080;
byte serverIP[] = {192, 168, 0, 102};
TCPClient client;
TCPServer server = TCPServer(23);
TCPClient serverClient;

// initialize global status variables
int hwArm;
int res0;
int res1;
int res2;
int res3;
int res4;
int res5;
int res6;
int res7;

// initialize sw arm
int swArm = 0;

// function to turn off sense circuit
void senseOff()
{
    digitalWrite(senseswitch, HIGH);
}

// function to turn on sense circuit
void senseOn()
{
    digitalWrite(senseswitch, LOW);
}

// this function runs once on startup
void setup()
{
    // set the firing pins to output mode
    pinMode(fire0, OUTPUT);
    pinMode(fire1, OUTPUT);
    pinMode(fire2, OUTPUT);
    pinMode(fire3, OUTPUT);
    pinMode(fire4, OUTPUT);
    pinMode(fire5, OUTPUT);
    pinMode(fire6, OUTPUT);
    pinMode(fire7, OUTPUT);

    // set the firing pin outputs low
    digitalWrite(fire0, LOW);
    digitalWrite(fire1, LOW);
    digitalWrite(fire2, LOW);
    digitalWrite(fire3, LOW);
    digitalWrite(fire4, LOW);
    digitalWrite(fire5, LOW);
    digitalWrite(fire6, LOW);
    digitalWrite(fire7, LOW);

    // set the HW Arm sense pin to input pulldown mode
    pinMode(armsense, INPUT_PULLDOWN);

    // set the sense switch pin to output mode
    pinMode(senseswitch, OUTPUT);

    // set the sense switch pin high (sense off)
    senseOff();

    // set the sense pins to input mode
    pinMode(sense0, INPUT);
    pinMode(sense1, INPUT);
    pinMode(sense2, INPUT);
    pinMode(sense3, INPUT);
    pinMode(sense4, INPUT);
    pinMode(sense5, INPUT);
    pinMode(sense6, INPUT);
    pinMode(sense7, INPUT);
    pinMode(WKP, INPUT); // sense7

    // get the wifi connected
    while (!WiFi.ready())
    {
        Particle.process();
        WiFi.connect();
        while(WiFi.connecting()) {Particle.process();}
    }

    delay(100);

}

// this function loops forever
void loop()
{
    if (!serverClient.connected()) {
        serverClient = server.available();
    }

    if (serverClient.connected()) {
	String command = "";
        int x = 0;
        while (serverClient.available()) {
            x += 1;
            char c = serverClient.read();
            command.concat(String(c));
        }
        if (command.equals("arm")) {
            swArm = 1;
        } else if (command.equals("disarm")) {
            swArm = 0;
        } else if (command.startsWith("fire")) {
            for (int i = 4; i < command.length(); i++) {
                char channelNum = command.charAt(i);
                if (channelNum == '3') {
                    digitalWrite(fire3, HIGH);
                    delay(1000);
                    digitalWrite(fire3, LOW);
                    delay(200);
                }
            }
        }
        server.println(command);
        server.println("HTTP/1.0 200 OK");
        server.println("Content-Length: 0");
        server.println();
    }

    hwArm = digitalRead(armsense);

    senseOn();
    delay(200);
    res0 = analogRead(sense0);
    res1 = analogRead(sense1);
    res2 = analogRead(sense2);
    res3 = analogRead(sense3);
    res4 = analogRead(sense4);
    res5 = analogRead(sense5);
    res6 = analogRead(sense6);
    res7 = analogRead(sense7);
    senseOff();

    if (client.connect(serverIP, serverPort))
    {
        client.println("POST /status HTTP/1.0");
	client.println("Host: 192.168.0.102:8080");
        client.println("Content-Length: 140");
        client.println();
        client.println("SW Arm: " + String(swArm));
        if (hwArm == 0) {
            client.println("HW Arm: DISARMED");
        }
        else{
            client.println("HW Arm: ARMED");
        }
        client.println("R0: " + String(res0));
        client.println("R1: " + String(res1));
        client.println("R2: " + String(res2));
        client.println("R3: " + String(res3));
        client.println("R4: " + String(res4));
        client.println("R5: " + String(res5));
        client.println("R6: " + String(res6));
        client.println("R7: " + String(res7));
        client.println("wifi RSSI: " + String(WiFi.RSSI()));
        client.println("          ");
        client.println("          ");
        client.println("          ");
        client.println("          ");
        client.println("          ");
        client.println("          ");
    }
    while(1) {
    if (client.available())
    {
        char c = client.read();
    }

    if (!client.connected())
    {
        client.stop();
        break;
    }
    }

    delay(2000);
}

