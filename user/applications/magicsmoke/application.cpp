/*
 ******************************************************************************
  Copyright (c) 2015 Particle Industries, Inc.  All rights reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "application.h"
#include "stdarg.h"

PRODUCT_ID(PLATFORM_ID);
PRODUCT_VERSION(3);

#if Wiring_WiFi
STARTUP(System.enable(SYSTEM_FLAG_WIFITESTER_OVER_SERIAL1));
#endif

SYSTEM_MODE(SEMI_AUTOMATIC);

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

int serverPort = 8080;
byte serverIP[] = {192, 168, 0, 102};

TCPClient client;

TCPServer server = TCPServer(23);
TCPClient serverClient;

/* This function is called once at start up ----------------------------------*/
void setup()
{
    pinMode(D0, OUTPUT); // fire6
    pinMode(D1, OUTPUT); // fire5
    pinMode(D2, OUTPUT); // fire4
    pinMode(D3, OUTPUT); // fire0
    pinMode(D4, OUTPUT); // fire1
    pinMode(D5, OUTPUT); // fire2
    pinMode(D6, OUTPUT); // fire3
    pinMode(D7, INPUT_PULLDOWN); // armed
    pinMode(RX, OUTPUT); // senseSwitch
    pinMode(TX, OUTPUT); // fire7
    pinMode(A0, INPUT); // sense0
    pinMode(A1, INPUT); // sense1
    pinMode(A2, INPUT); // sense2
    pinMode(A3, INPUT); // sense3
    pinMode(A4, INPUT); // sense4
    pinMode(A5, INPUT); // sense5
    pinMode(DAC, INPUT); // sense6
    pinMode(WKP, INPUT); // sense7

    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(TX, LOW);

    digitalWrite(RX, HIGH);

    // get the wifi connected
    while (!WiFi.ready())
    {
        Particle.process();
        WiFi.connect();
        while(WiFi.connecting()) {Particle.process();}
    }


    delay(100);
}

int hwArm;
int res0;
int res1;
int res2;
int res3;
int res4;
int res5;
int res6;
int res7;

int swArm = 0;

/* This function loops forever --------------------------------------------*/
void loop()
{
    //This will run in a loop

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
        }
        server.println(command);
        server.println("HTTP/1.0 200 OK");
        server.println("Content-Length: 0");
        server.println();
    }

    hwArm = digitalRead(D7);

    digitalWrite(RX, LOW);
    delay(200);
    res0 = analogRead(A0);
    res1 = analogRead(A1);
    res2 = analogRead(A2);
    res3 = analogRead(A3);
    res4 = analogRead(A4);
    res5 = analogRead(A5);
    res6 = analogRead(DAC);
    res7 = analogRead(WKP);
    delay(200);
    digitalWrite(RX, HIGH);

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

