# Welcome to UVC_WC!

[UVC](https://en.wikipedia.org/wiki/Ultraviolet#UVC) is a special range of ultaviolet light with shorter wavelength than better known UVA (used in tanning beds to tan the skin). Normally UVC is absorved by atmospheric ozono, so do not reach us so we are protected during sunny days. [See differences](https://www.sungrubbies.com/blogs/news-articles/uva-uvb-radiation)

UVC bulbs and tubes are commercially available and has been extensivelly used for years to sanitize hospital sensible areas like surgery operating rooms,  and infectious patient area toilets. It is very efficient and, by ionizing air, produces also ozone gas, that helps also in the bacteria and virus cleaning process.

This is a hacking project to adapt a commercial PIR light controller, to change its behaviour at will and use it to sanitize and desinfect a room (i.e. restroom) after its use, only when nobody is there, using a UVC lamp that kill viruses and bacteria and generate ozone gas. Hacking was necessary due to lack of supply during lockdown but it can also be developed with standard arduino shields and modules. 

##### WARNING: UVC is a dangerous ultraviolet wavelength that can produce damage into you eyes. Use adequated glases while testing the installation. Ozone produced by UVC inonization of air should not be breath continuosly in a closed room, so, work in a ventilated environment.


![GitHub Logo](/images/uvc_wc_fsm.jpg)


As UVC light is dangerous to our eyes and skin, we need to prevent the PIR light controller logic and instead, behave as the above Finite-State Machine (FSM), using any MCU (a NodeMCU in my case, but any arduino-like will do)

# Behaviour

The above FSM diagram shows the different defined states and the events that change them, considering that PIR detection event only occure when someone moves around, but disapear when is static.
To avoid turning UVC light when someone is sitting for a while, a second sensor read the door closed signal. Safety rule is not to use UVC when the door is  closed, as that means someone is there

There are three timers that can be configured as:

T1 time after first presence event to consider that some is around with the door open. It takes into account that WC doors are normally open and people can be around for standar cleaing or washing hands. 

T2 time after door is open, to consider the last occupancy is gone

T3 UVC cleaning time, that can be interrupted by the presence of someone, so UVC is inmmediately turned off.

There are two different versions of logic, one that configure timers as constant in conde, and another more evolved, that allow its interactive reconfiguration via WiFi web form.

# Hardware

Several version has been developed:
- Commercial Hack (during lockdown, nodemcu)
- Minimal (ESP-01, Relay module)
- Standard no wifi (arduino uno family)

## Commercial Hack
(do not recommend, see other options and warning note)
A commercial PIR is required. There are affordable arduino PIR modules out there, but I did not have them availables where I live during lockdown, so I used a commercial PIR detector to switch light under motion presence detectio. We have to open it, hack the pcb by desoldering a resistor that comes from the algorithm controller IC toward a j-transistor that activate the Relay. In that way, we bypass the factory logic so we can procees the PIR signal from the IC into an external MCU, and follow the FSM above to activate it only when nobody is arround, and the WC has been used. 

![GitHub Logo](/images/PIR.jpg)

We need one MCU pin configured as input and connected to the pcb track before the resistor (green wire), and another MCU pin  configured as output and connected to the other pad of the removed resistor (yellow wire). An external resistor (10Mohm in my case) is soldered between the pin and the j-transistor base pcb pad.

With this configuration, we will detect motion activity with the green wire, and we will be able to switch on/off the relay with yellow wire, both connected to any MCU (I used a NodeMCU that was available at home during lockdown).

I tried to power NodeMCU from the commercial PIR module, but its circuit is not prepared to source to much current (do not use transformer psu but, to save money, it uses a capacitive power supply circuit similar to [this](https://www.brighthubengineering.com/diy-electronics-devices/77929-make-a-transformerless-power-supply/). It would have been very convenient, as we just should have added an MCU to the commercial PIR, but even switching off the NodeMCU module to avoid extra consumption, ESP crashed from time to time (not enough miliamps to drive it)

So finally we needed an external standard 5v charger power supply, and handle grounds with care as there are two sources, the commercial module capacity P.S. and the charger one, so we need to guess with a tester that we are using AC mains live and neutral in same side of both P.S.

I do not recommend this hack anymore, unless you know how to handle AC mains, as it can be dangerous. I was for several month in a lockdown so I decided to proceed, but..
##### WARNING: AC mains are dangerous and can kill you. I do not recommend to use this versión unless you are profesionally trained.


BEFORE
![GitHub Logo](/images/PIR_pcb.jpg)

HACKED
![GitHub Logo](/images/PIRrelayhack.jpg)

To detect Door Open/Close status, a magnetic switch is being used, they are very common and a reed relay is activated when magnet installed on the door is near it. So one pin of MCU is used to send Vcc current (with a limit resistor) to the door switch, and the return signal (pull down) is normally 0 unless the door is close (High TTL value).

![GitHub Logo](/images/door_sensor.jpg)

## Minimal (ESP-01, Relay module)
ESP-01 was the first module based on popular ESP8266. It still available and very cheap for providing wifi. It also has some interesting modules, like ESP-01 Relay module, that makes the hardware wide accessible and low cost. Unfortunatelly, ESP-01 is scarced in exposed  GPIO's. One can only really use GPIO0 for the relay output, and GPIO2 (led), as GPI1 and GPIO3 are used for TX and RX, unless we reuse them for sensors (PIR and door switch)

## Standard no wifi (arduino uno family)
Any arduino (UNO, mini, mega...) can be used with this code. We have just to decide with PIN to use for sensor (PIR, DOOR) and which ones for LEDS (GREEN, RED), and finally, one PIN output for commanding the Relay to switch on/off the UVC light.
The code is selfexplanatory and has just to be configured with 3 timers (T1, T2, T3) and the choosen PIN configuration.
There is not WiFi, so everything has to be hardcoded but, this is the easiest implementation for novices.

A GREEN and RED leds are used to indicate that WC is CLEAN or is DIRTY pending an UVC light cleaning sesion, so is not recommended to be used.

# Versions

Future upgrades will include an Ozone sensor, to avoid saturation of that gas, as also has contraindication for lungs and is not recommended to breath in high concentration.

# Conclusion

With current covid-19 pandemia, is very difficult to mantain WC's clean after each use in public lavatorios like companies, sport installations, etc, so I think this project is quite useful.

Hope you like it and enhance!

@agnuca June 2020



