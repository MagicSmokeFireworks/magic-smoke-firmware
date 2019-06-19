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
SYSTEM_MODE(MANUAL);

// use external wifi antenna
STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

// define the software watchdog (runs in high-priority thread)
// will reset the system if status function doesnt check in within 60 seconds
// automatic check-in occurs each time we exit loop()
ApplicationWatchdog wd(60000, System.reset);

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

// define this firmware version (reported in status)
String firmwareVersion = "3.1";

// initialize tcp server/client info
int serverPort = 8080;
byte serverIP[] = {192, 168, 0, 100};
String hostString = "Host: 192.168.0.100:8080";
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

// initialize retained status variables (in SRAM)
retained int firecount0 = 0;
retained int firecount1 = 0;
retained int firecount2 = 0;
retained int firecount3 = 0;
retained int firecount4 = 0;
retained int firecount5 = 0;
retained int firecount6 = 0;
retained int firecount7 = 0;
retained int firetime0 = 0;
retained int firetime1 = 0;
retained int firetime2 = 0;
retained int firetime3 = 0;
retained int firetime4 = 0;
retained int firetime5 = 0;
retained int firetime6 = 0;
retained int firetime7 = 0;
retained int cmdcount = 0;
retained int packetId = 0;

// initialize sw arm (retain in SRAM)
retained int swArm = 0;

// initialize warm boot count (retain in SRAM)
retained int bootCount = 0;

// record the last time since boot we got a command
int lastCmdTime = 0;

bool timeSet = false;

// definitions for status rates
#define lowRateStatus 10000
#define highRateStatus 1000
#define quickStatusRate 100

bool highRate = true;

bool quickStatusRequested = false;
bool quickStatusSent = false;


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

// function to collect status, called on timer
void getStatus()
{

    // correct timer period after quick status timer
    if (quickStatusRequested) {
        quickStatusSent = true;
    }

    // don't try to send status if the WiFi isn't up
    // (main loop should handle WiFi problems)
    if(!WiFi.ready()) {
        return;
    }

    // read the HW Arm pin
    hwArm = digitalRead(armsense);

    // Read the match channels (1 ms delay to energize the sense resistors)
    senseOn();
    delay(1);
    res0 = analogRead(sense0);
    res1 = analogRead(sense1);
    res2 = analogRead(sense2);
    res3 = analogRead(sense3);
    res4 = analogRead(sense4);
    res5 = analogRead(sense5);
    res6 = analogRead(sense6);
    res7 = analogRead(sense7);
    senseOff();

    // connect to server and dump the status
    if (client.connect(serverIP, serverPort))
    {

        packetId++;

        client.println("POST /status HTTP/1.0");
        client.println(hostString);
        client.println("ID: " + System.deviceID());
        client.println("FVer: " + firmwareVersion);
        client.println("BC: " + String(bootCount));
        client.println("PID: " + String(packetId));
        client.println("MICROS: " + String(micros()));
    	client.println("PTIME: " + String(Time.now()));
        client.println("SW_ARM: " + String(swArm));
        if (hwArm == 0) {
            client.println("HW_ARM: DISARMED");
        }
        else{
            client.println("HW_ARM: ARMED");
        }
        client.println("R0: " + String(res0));
        client.println("R1: " + String(res1));
        client.println("R2: " + String(res2));
        client.println("R3: " + String(res3));
        client.println("R4: " + String(res4));
        client.println("R5: " + String(res5));
        client.println("R6: " + String(res6));
        client.println("R7: " + String(res7));
        client.println("FC0: " + String(firecount0));
        client.println("FC1: " + String(firecount1));
        client.println("FC2: " + String(firecount2));
        client.println("FC3: " + String(firecount3));
        client.println("FC4: " + String(firecount4));
        client.println("FC5: " + String(firecount5));
        client.println("FC6: " + String(firecount6));
        client.println("FC7: " + String(firecount7));
        client.println("LFT0: " + String(firetime0));
        client.println("LFT1: " + String(firetime1));
        client.println("LFT2: " + String(firetime2));
        client.println("LFT3: " + String(firetime3));
        client.println("LFT4: " + String(firetime4));
        client.println("LFT5: " + String(firetime5));
        client.println("LFT6: " + String(firetime6));
        client.println("LFT7: " + String(firetime7));
        client.println("CC: " + String(cmdcount));
        client.println("WIFI_RSSI: " + String(WiFi.RSSI()));
        client.println("Content-Length: 0");
        client.println();
    }
    
    // read the response back from the server (and do nothing with it)
    while(1)
    {
        if (client.available())
        {
            // important to read to clear buffer, but we arent doing anything with it atm
            char c = client.read();
        }

        if (!client.connected())
        {
            client.stop();
            break;
        }
    }
}


// set up software timer for sending status
Timer statusTimer(highRateStatus, getStatus);

// functions to stop firing, called on timers
void stopFire0()
{
    digitalWrite(fire0, LOW);
}
void stopFire1()
{
    digitalWrite(fire1, LOW);
}
void stopFire2()
{
    digitalWrite(fire2, LOW);
}
void stopFire3()
{
    digitalWrite(fire3, LOW);
}
void stopFire4()
{
    digitalWrite(fire4, LOW);
}
void stopFire5()
{
    digitalWrite(fire5, LOW);
}
void stopFire6()
{
    digitalWrite(fire6, LOW);
}
void stopFire7()
{
    digitalWrite(fire7, LOW);
}

// set up 'one_shot' software timers for stopping firing
Timer stopFire0Timer(1000, stopFire0, true);
Timer stopFire1Timer(1000, stopFire1, true);
Timer stopFire2Timer(1000, stopFire2, true);
Timer stopFire3Timer(1000, stopFire3, true);
Timer stopFire4Timer(1000, stopFire4, true);
Timer stopFire5Timer(1000, stopFire5, true);
Timer stopFire6Timer(1000, stopFire6, true);
Timer stopFire7Timer(1000, stopFire7, true);


// function to stop identify LED
void stopIdentify()
{
    RGB.control(false);
}

// set up 'one_shot' software timer to stop identify
Timer stopIdentifyTimer(2000, stopIdentify, true);

// this function runs once on startup
void setup()
{

    // increment the boot count
    bootCount += 1;

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

    WiFi.on();
    WiFi.clearCredentials();
    WiFi.setCredentials("blarg","cantspellconvalescence");
    // get the wifi connected
    while (!WiFi.ready())
    {
        Particle.process();
        WiFi.connect();
        while(WiFi.connecting()) {Particle.process();}
    }

    delay(100);

    // start the status collection timer
    statusTimer.start();
}

//// COMMAND FUNCTIONS

// software arm/disarm
bool arm(bool arm) {
    if (arm) {
        swArm = 1;
    }
    else {
        swArm = 0;
    }
    return true;
}

// telemetry reporting rate
bool rate(uint rate) {
    if (rate == 0) {
        if (highRate) {
            highRate = false;
            statusTimer.changePeriod(lowRateStatus);
        }
        return true;
    }
    else if (rate == 1) {
        if (!highRate) {
            highRate = true;
            statusTimer.changePeriod(highRateStatus);
        }
        return true;
    }
    else {
        return false;
    }
}

// identify LED
bool identify() {
    // control the rgb led to go red and blue for 2 seconds
    RGB.control(true);
    RGB.color(255,0,255);
    stopIdentifyTimer.start();
    return true;
}

// fire command
bool fire(String chanString) {

    // only fire if swArm is 1
    if (swArm != 1) {
        return false;
    }

    // reset the status timer so that status is not collected during firing
    //statusTimer.reset();

    // determine the channels to fire
    char chanChars[3];
    chanString.toCharArray(chanChars, 3);
    int chans = strtol(chanChars, NULL, 16);

    int firetime = Time.now();

    // fire commanded channels
    if (chans & 0x01) {
        digitalWrite(fire0, HIGH);
        stopFire0Timer.start();
        firecount0++;
        firetime0 = firetime;
    }
    if (chans & 0x02) {
        digitalWrite(fire1, HIGH);
        stopFire1Timer.start();
        firecount1++;
        firetime1 = firetime;
    }
    if (chans & 0x04) {
        digitalWrite(fire2, HIGH);
        stopFire2Timer.start();
        firecount2++;
        firetime2 = firetime;
    }
    if (chans & 0x08) {
        digitalWrite(fire3, HIGH);
        stopFire3Timer.start();
        firecount3++;
        firetime3 = firetime;
    }
    if (chans & 0x10) {
        digitalWrite(fire4, HIGH);
        stopFire4Timer.start();
        firecount4++;
        firetime4 = firetime;
    }
    if (chans & 0x20) {
        digitalWrite(fire5, HIGH);
        stopFire5Timer.start();
        firecount5++;
        firetime5 = firetime;
    }
    if (chans & 0x40) {
        digitalWrite(fire6, HIGH);
        stopFire6Timer.start();
        firecount6++;
        firetime6 = firetime;
    }
    if (chans & 0x80) {
        digitalWrite(fire7, HIGH);
        stopFire7Timer.start();
        firecount7++;
        firetime7 = firetime;
    }

    return true;
}

// ping command
bool ping() {
    return true;
}


// this function loops forever
void loop()
{

    // if a quick status cycle was requested and sent, set the status rate back to normal
    if (quickStatusRequested && quickStatusSent) {
        quickStatusRequested = false;
        if (highRate) {
            statusTimer.changePeriod(highRateStatus);
        }
        else {
            statusTimer.changePeriod(lowRateStatus);
        }
    }

    while (!WiFi.ready())
    {
        Particle.process();
        WiFi.connect();
        while(WiFi.connecting()) {Particle.process();}
    }
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

        bool commanded = false;
        bool cmdTimeValid = false;
        bool cmdValid = false;

        char cmdId = 'F';
        int cmdTime = 0;
        String cmdChans = "00";

        if (command.startsWith(".") && (command.length() > 15) ) {
            commanded = true;
            cmdId = command.charAt(1);
            cmdChans = command.substring(3,5);
            cmdTime = command.substring(6).toInt();
        }

        if (commanded) {
            if (!timeSet) {
                Time.setTime(cmdTime);
                timeSet = true;
            }
            else if (cmdTime > Time.now()) {
                Time.setTime(cmdTime);
            }
            
            if ( (cmdTime > Time.now()) || ( (Time.now()-cmdTime) < 5) ) {
                cmdTimeValid = true;
            }
        }

        if (commanded) {

            // reset the status timer for quick status collection
            if ( (cmdId != '2') && (cmdId != '3') ) {
                statusTimer.reset();
                quickStatusRequested = true;
                quickStatusSent = false;
                statusTimer.changePeriod(quickStatusRate);
            }

            // 0: arm
            if (cmdId == '0') {
                if (cmdTimeValid) {
                    cmdValid = arm(true);
                }
            }

            // 1: disarm (even if command is late)
            else if (cmdId == '1') {
                cmdValid = arm(false);
            }

            // 2: low
            else if (cmdId == '2') {
                if (cmdTimeValid) {
                    cmdValid = rate(0);
                }
            }

            // 3: high
            else if (cmdId == '3') {
                if (cmdTimeValid) {
                    cmdValid = rate(1);
                }
            }

            // 4: identify
            else if (cmdId == '4') {
                cmdValid = identify();
            }

            // 5: reset
            else if (cmdId == '5') {
                System.reset(); // maybe not great to do this?
            }

            // 6: ping
            else if (cmdId == '6') {
                cmdValid = ping();
            }

            // 9: fire
            else if (cmdId == '9') {
                if (cmdTimeValid) {
                    cmdValid = fire(cmdChans);
                }
            }
        }

        if (commanded) {
            lastCmdTime = millis();
            cmdcount++;

            server.println(command+"."+String(cmdcount)+"."+String(cmdTimeValid)+"."+String(cmdValid));
            server.println("HTTP/1.0 200 OK");
            server.println("Content-Length: 0");
            server.println();
        }
        else {
            if (command != "") {
                server.println(command);
                server.println("HTTP/1.0 400 Bad Request");
                server.println("Content-Length: 0");
                server.println();
            }
        }
    }
    if ((millis() - lastCmdTime) > 30000) {
        if (timeSet) {
            System.reset();
        }
    }
}

