# esphome-weider_wp

This is a component for ESPHome that allows to communicate with a Weider Heat Pump over the RS232 port. An RS232 level shifter is required!

Weider protocol and hardware documentation: [WEIDER Heizungsregelung](https://community.symcon.de/uploads/short-url/uwwaSRbpOMsEBgVUlF7s6QHBrOI.pdf)

So far, only automatic mode is supported since polling mode does not seem to deliver different, more or better data.

## Hardware setup

Connect your ESP via RS232 to the heat pump according to the docs of Weider. I use an SP3232 level shifter and connected the DTR/DSR signals to ESP inputs/outputs. This allows controlling PC or modem mode, but is not a strict requirements. If left floating, the heat pump is in PC mode automatically. The RTS/CTS signal is bridged at my DB9 connector, I'm not sure if this is required (the Weider docs use hardware flow control, so I assumed yes).

## Software setup

See the provided example file. You can rename or omit any of the sensors. The supported sensors are based on what my heat pump, an SW210, reports. Reading inputs and error codes is WiP.