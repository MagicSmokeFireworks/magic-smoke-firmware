# magic-smoke-firmware
This is the firmware running on the photon to control the Magic Smoke board and light up the sky.

This is how you build and flash the magicsmoke application:

1. First, this assumes the wifi credentials are already configured. Maybe this will change.
2. Also, make sure you have an external antenna connected when running this app, or change the setting, because we don't want to blow up the wifi chip.
3. Connect the photon via USB, put it in dfu mode (hold setup, hit reset, continue holding setup until yellow blinkies)
4. `cd main`
5. `make PLATFORM=photon APP=magicsmoke program-dfu`
6. After flashing, the photon will reset and be running the magic smoke application :D

