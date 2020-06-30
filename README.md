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

# Hardware

A commercial PIR is required. There are affordable PIR modules out there, but I did not have them availables where I live so I used a commercial PIR to light under motion presence detection, open it, and hack the pcb in a resistor that comes from the algorithm controller IC toward a j-transistor that activate the Relay. In that way, we can procees the PIR signal from the IC into an external MCU, and follow the FSM above to activate it only when nobody is arround, and the WC has been used. 

![GitHub Logo](/PIR.jpg)


So one MCU pin is configured as input and connecte to the pcb track before the resistor, and another pin is configure as output and connected to the other pad of the removed resistor. An external resistor (10Mohm in my case) is soldered between the pin and the j-transistor base pcb pad. 

![GitHub Logo](/PIR_pcb.jpg)

To detect Door Open/Close status, a magnetic switch is being used, they are very common and a reed relay is activated when magnet installed on the door is near it. So one pin of MCU is used to send Vcc current (with a limit resistor) to the door switch, and the return signal (pull down) is normally 0 unless the door is close (High TTL value).

![GitHub Logo](/door_sensor.jpg)

# Versions

First version is the simplest one. FSM as diagram and T1,T2 and T3 predefined. New version is comming that ESP8266 will be accesible through wifi to allow Timers to be tuned and reconfigured, and perhaps, for logging.

A GREEN and RED leds will be used to indicate that WC is CLEAN or is pending a UVC light cleaning sesion, so is not recommended to be used.

Future upgrades will include an Ozone sensor, to avoid saturation of that gas, as also has contraindication for lungs and is not recommended to breath in high concentration.

# Conclusion

With current covid19 pandemia, is very difficult to mantain WC's clean after each use in public lavatorios like companies, sport installations, etc, so I think this project is quite useful.

Hope you like it and enhance!

@agnuca June 2020

