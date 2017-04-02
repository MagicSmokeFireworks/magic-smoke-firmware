# magic-smoke-firmware
This is the firmware running on the photon to control the Magic Smoke board and light up the sky.

This is how you build and flash the magicsmoke application:

1. First, make sure the server IP and wifi credentials are correct in the source. (user/applications/magicsmoke/application.cpp).
2. Change the firmwareVersion string in the code if necessary.
3. Also, make sure you have an external antenna connected when running this app, or change the setting, because we don't want to blow up the wifi chip.
4. Connect the photon via USB, put it in dfu mode (hold setup, hit reset, continue holding setup until yellow blinkies)
5. `cd main`
6. `make PLATFORM=photon APP=magicsmoke program-dfu`
7. After flashing, the photon will reset and be running the magic smoke application :D

