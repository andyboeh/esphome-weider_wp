# TODO

  * Split into hub and individual components
  * Sensor components represent internal states, including binary sensors
  * Climate component allows to set temperatures - maybe one for T-Vorlauf and one for T-Raumsoll?
  * With automations we could control the pumps
  * Convert from Auto-Mode to polling mode -> wait 7 seconds, if nothing received -> poll mode; otherwise, switch mode
  * Implement Queue for event processing, is basically a vector with the strings to send; timer adds new poll commands to the queue if required, processing always waits for next command - should be implemented first
