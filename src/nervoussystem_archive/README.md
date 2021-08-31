# This is Jakson's project only - to create a stream combiner for the control panel.

It should be done with a soldered nano (breadboard will be used for prototyping) and should take six input streams (two joysticks, four streams; two buttons, two streams) and turn them into four output streams (joystick value, 2 streams; button value, 1 stream; whos turn, 1 stream) for the P1AM.

The nano should start on player 1's turn (use a boolean, `bool` is the variable initializer) and thus send only player 1's joystick input and button value. The who's turn stream should be set to the boolean, on or off.
When player 1's button is pressed, it should send the button value, wait 10 milliseconds (to make sure the P1AM got the message), and switch to player two.

Lawson and I are only allowed to help in the situation that Jakson **cannot find it himself using google**.
