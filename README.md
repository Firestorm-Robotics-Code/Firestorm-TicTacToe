# Firestorm-TicTacToe

Arduino code and documentation for Firestorm Robotics's tic-tac-toe board

## For Arduino samples (motor control, logic, etc) use the samples directory from the main branch.
## If you find a good link to an article/tutorial/documentation, add it in the documentation section in this file (README.md)
## If you find good wiring diagrams, add them to the wiring_diagrams directory in the main branch
## And of course, for actual source code, use the code directory. Lets try and keep this multifile, where each file's job is to do one thing and thats it, to avoid wonky github. Its absolutely evil when github wonks.

BTW, this was written in Markdown. Github flavoured markdown information [here](https://docs.github.com/en/free-pro-team@latest/github/writing-on-github).

# Good articles/tutorials/documentation (links - just copy/paste the url)

DM556 Motor controller datasheet (the big one, not the normal-size one)
http://www.leadshine.com/UploadFile/Down/DM556m.pdf

Automation Direct DM322E, which is probably different in some arcane way than the other motor controller link (nothing a nice floom couldn't take care of)
https://cdn.automationdirect.com/static/manuals/leadshinestepper/dm322e.pdf

Gigantic PSU which will sadly be bigger than the Arduino
https://cdn.automationdirect.com/static/manuals/psxinstall/PSB24-480S.pdf

Shopping catalog entry of the same PSU
https://www.automationdirect.com/adc/shopping/catalog/power_products_(electrical)/dc_power_supplies/rhino_select_(din_rail)/psb-s_series/psb24-480s

Documentation for AccelStepper Arduino library (the library we're supposed to be using to drive the stepper motor - we could also just hack it up ourselves if that would be more fun)
https://www.pjrc.com/teensy/td_libs_AccelStepper.html

Completely off-topic ultrasonic sensor project on the Arduino forums
https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
