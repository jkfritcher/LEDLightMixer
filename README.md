# LED Light Mixer

## Description

LED Light Mixer is the firmware for an ATMEGA32U4 based device designed to control a RGB LED strip.

## Building

To build the LED Light Mixer, check-out the source tree

```
git clone git://github.com/jkfritcher/LEDLightMixer.git
```

Download or checkout a recent version of LUFA in the same directory that the Light Mixer source was checked out into.

```
git clone git://github.com/abcminiuser/lufa.git LUFA
git checkout LUFA-130303
```

Your source tree should look similiar to this

```
drwxr-xr-x  14 jkf  staff  476 Apr  7 18:31 LEDLightMixer
drwxr-xr-x  12 jkf  staff  408 Apr  7 18:27 LUFA
```

Build the code

```
cd LEDLightMixer
make
```

At the end of the build process, you will find .hex file ready to upload to the device.

