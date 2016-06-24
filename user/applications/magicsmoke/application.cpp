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

/* Function prototypes -------------------------------------------------------*/
int tinkerDigitalRead(String pin);
int tinkerDigitalWrite(String command);
int tinkerAnalogRead(String pin);
int tinkerAnalogWrite(String command);

#if Wiring_WiFi
STARTUP(System.enable(SYSTEM_FLAG_WIFITESTER_OVER_SERIAL1));
#endif

//SYSTEM_MODE(AUTOMATIC);
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
    //Setup the Tinker application here

    //Register all the Tinker functions
    //Particle.function("digitalread", tinkerDigitalRead);
    //Particle.function("digitalwrite", tinkerDigitalWrite);

    //Particle.function("analogread", tinkerAnalogRead);
    //Particle.function("analogwrite", tinkerAnalogWrite);

    while (!WiFi.ready())
    {
        Particle.process();
        WiFi.connect();
        while(WiFi.connecting()) {Particle.process();}
    }

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
        if (swArm == 0) {
            swArm = 1;
        }
        else {
            swArm = 0;
        }
        while (serverClient.available()) {
            serverClient.read();
        }
        server.println("HTTP/1.0 200 OK");
        server.println("Content-Length: 0");
        server.println();
    }

    hwArm = digitalRead(D7);

//    int sense0val = analogRead(A0);
    digitalWrite(RX, LOW);
    delay(10);
    res0 = analogRead(A0);
    res1 = analogRead(A1);
    res2 = analogRead(A2);
    res3 = analogRead(A3);
    res4 = analogRead(A4);
    res5 = analogRead(A5);
    res6 = analogRead(DAC);
    res7 = analogRead(WKP);
    digitalWrite(RX, HIGH);

    if (client.connect(serverIP, serverPort))
    {
//	client.print(sense0val);
//	client.print("HW Arm State:");
//        client.print(hwArm);
//	client.print("WiFi RSSI + 127:");
//        client.print(WiFi.RSSI()+127);
//	client.print(' ');
        client.println("POST /status HTTP/1.0");
	client.println("Host: 192.168.0.102:8080");
        client.println("Content-Length: 120");
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

/*******************************************************************************
 * Function Name  : tinkerDigitalRead
 * Description    : Reads the digital value of a given pin
 * Input          : Pin
 * Output         : None.
 * Return         : Value of the pin (0 or 1) in INT type
                    Returns a negative number on failure
 *******************************************************************************/
int tinkerDigitalRead(String pin)
{
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(pin.startsWith("D"))
    {
        pinMode(pinNumber, INPUT_PULLDOWN);
        return digitalRead(pinNumber);
    }
    else if (pin.startsWith("A"))
    {
        pinMode(pinNumber+10, INPUT_PULLDOWN);
        return digitalRead(pinNumber+10);
    }
#if Wiring_Cellular
    else if (pin.startsWith("B"))
    {
        if (pinNumber > 5) return -3;
        pinMode(pinNumber+24, INPUT_PULLDOWN);
        return digitalRead(pinNumber+24);
    }
    else if (pin.startsWith("C"))
    {
        if (pinNumber > 5) return -4;
        pinMode(pinNumber+30, INPUT_PULLDOWN);
        return digitalRead(pinNumber+30);
    }
#endif
    return -2;
}

/*******************************************************************************
 * Function Name  : tinkerDigitalWrite
 * Description    : Sets the specified pin HIGH or LOW
 * Input          : Pin and value
 * Output         : None.
 * Return         : 1 on success and a negative number on failure
 *******************************************************************************/
int tinkerDigitalWrite(String command)
{
    bool value = 0;
    //convert ascii to integer
    int pinNumber = command.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(command.substring(3,7) == "HIGH") value = 1;
    else if(command.substring(3,6) == "LOW") value = 0;
    else return -2;

    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, value);
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        digitalWrite(pinNumber+10, value);
        return 1;
    }
#if Wiring_Cellular
    else if(command.startsWith("B"))
    {
        if (pinNumber > 5) return -4;
        pinMode(pinNumber+24, OUTPUT);
        digitalWrite(pinNumber+24, value);
        return 1;
    }
    else if(command.startsWith("C"))
    {
        if (pinNumber > 5) return -5;
        pinMode(pinNumber+30, OUTPUT);
        digitalWrite(pinNumber+30, value);
        return 1;
    }
#endif
    else return -3;
}

/*******************************************************************************
 * Function Name  : tinkerAnalogRead
 * Description    : Reads the analog value of a pin
 * Input          : Pin
 * Output         : None.
 * Return         : Returns the analog value in INT type (0 to 4095)
                    Returns a negative number on failure
 *******************************************************************************/
int tinkerAnalogRead(String pin)
{
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(pin.startsWith("D"))
    {
        return -3;
    }
    else if (pin.startsWith("A"))
    {
        return analogRead(pinNumber+10);
    }
#if Wiring_Cellular
    else if (pin.startsWith("B"))
    {
        if (pinNumber < 2 || pinNumber > 5) return -3;
        return analogRead(pinNumber+24);
    }
#endif
    return -2;
}

/*******************************************************************************
 * Function Name  : tinkerAnalogWrite
 * Description    : Writes an analog value (PWM) to the specified pin
 * Input          : Pin and Value (0 to 255)
 * Output         : None.
 * Return         : 1 on success and a negative number on failure
 *******************************************************************************/
int tinkerAnalogWrite(String command)
{
    String value = command.substring(3);

    if(command.substring(0,2) == "TX")
    {
        pinMode(TX, OUTPUT);
        analogWrite(TX, value.toInt());
        return 1;
    }
    else if(command.substring(0,2) == "RX")
    {
        pinMode(RX, OUTPUT);
        analogWrite(RX, value.toInt());
        return 1;
    }

    //convert ascii to integer
    int pinNumber = command.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits

    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        analogWrite(pinNumber, value.toInt());
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        analogWrite(pinNumber+10, value.toInt());
        return 1;
    }
    else if(command.substring(0,2) == "TX")
    {
        pinMode(TX, OUTPUT);
        analogWrite(TX, value.toInt());
        return 1;
    }
    else if(command.substring(0,2) == "RX")
    {
        pinMode(RX, OUTPUT);
        analogWrite(RX, value.toInt());
        return 1;
    }
#if Wiring_Cellular
    else if (command.startsWith("B"))
    {
        if (pinNumber > 3) return -3;
        pinMode(pinNumber+24, OUTPUT);
        analogWrite(pinNumber+24, value.toInt());
        return 1;
    }
    else if (command.startsWith("C"))
    {
        if (pinNumber < 4 || pinNumber > 5) return -4;
        pinMode(pinNumber+30, OUTPUT);
        analogWrite(pinNumber+30, value.toInt());
        return 1;
    }
#endif
    else return -2;
}
