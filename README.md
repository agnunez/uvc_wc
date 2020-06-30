# Welcome to UVC_WC!

This is a hacking project to adapt a commercial PIR light controller, to change its behaviour at will and use it to sanitize and desinfect a room (i.e. restroom) after its use, only when nobody is there, using a UVC lamp that kill viruses and bacteria and generate ozone gas. WARNING: UVC is a dangerous ultraviolet wavelength that can produce damage into you eyes. Use adequated glases while testing the installation

![GitHub Logo](/uvc_wc_fsm.JPG)

As UVC light is dangerous to our eyes and skin, the PIR light controller is change to behave as the above Finite-State Machine (FSM), using any MCU (an ESP8266 in my case, but any arduino-like will do

# Behaviour

The above FSM diagram shows the different defined states and the events that change them, considering that PIR detection event only occure when someone moves around, but disapear when is static.
To avoid turning UVC light when someone is sitting for a while, a second sensor read the door closed signal. Safety rule is not to use UVC when the door is  closed, as that means someone is there

There are three timers that can be configured as:

T1 time after first presence event to consider that some is around with the door open. It takes into account that WC doors are normally open and people can be around for standar cleaing or washing hands. 

T2 time after door is open, to consider the last occupancy is gone

T3 UVC cleaning time, that can be interrupted by the presence of someone, so UVC is inmmediately turned off.

# Versions

First version is the simplest one. FSM as diagram and T1,T2 and T3 predefined. New version is comming that ESP8266 will be accesible through wifi to allow Timers to be tuned and reconfigured, and perhaps, for logging.

A GREEN and RED leds will be used to indicate that WC is CLEAN or is pending a UVC light cleaning sesion, so is not recommended to be used.

Future upgrades will include an Ozone sensor, to avoid saturation of that gas, as also has contraindication for lungs and is not recommended to breath in high concentration.

# Conclusion

With current covid19 pandemia, is very difficult to mantain WC's clean after each use in public lavatorios like companies, sport installations, etc, so I think this project is quite useful.

Hope you like it and enhance!

@agnuca June 2020

