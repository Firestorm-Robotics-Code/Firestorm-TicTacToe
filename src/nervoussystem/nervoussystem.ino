/* By Tyler Clarke
 *  Pulling-it-all-together file that allows a choice between any of my many tests.
 *  
 *  Instructions:
 *    Comment all "#define" statements. Commenting is done by appending "//" in front of any statement which doesn't have it already.
 *    Uncomment (remove the "//") the one referring to the file you want to test.
 *  
 *  Determining the one you want:
 *    Every name is in the format "Category_number", so a test #1 would be "#define TEST_1".
 *    Every name has an optional third part, the name. A Blorky test #1 would be "#define TEST_1_BLORKY".
 *  
 *  If you get an error during compilation, the first thing you need to do is make sure that exactly one is uncommented.
That might just be the issue, whether less than or more than.
 *  
 *  
 *  Safety:
 *    ALWAYS be ready to pull the barrel jack. The switch DOES NOT power down fast enough.
 *    NEVER run the bepro with the USB and the barrel jack in at the same time. I do not assume any responsibility for the consequences if you do.
 *    ALWAYS mark failed tests with "FAILURE" and comment them. An example: "// FAILURE #define TEST_1_TIMMY". This prevents them from compiling.
 *    NEVER leave tests not marked with "UTTERLY SAFE" running.
 *    ALWAYS make sure it zeroes. If it doesn't hit the switch and stops, there is something very wrong and you should pull the plug.
 *    NEVER run the BePro if you have changed the wiring, until you have verified the wiring against the pinouts described in the top part of the file.
 *    ALWAYS keep your hands away from the rails! It would not be a pretty scene if your finger is crushed and ground in the screw.
For assistance with this, call me up.
 *    NEVER let pride get in the way of these rules! I cannot stress this enough. It doesn't matter if you think you are right. Always assume that you are wrong.
 *    
 *    
 *  Extra instructions will be provided for different applications. These instructions will always be clear - if they aren't, ask!
 *    
 *    
 *  What you have read here is a minimal briefing on usage of this code. If you have questions, ask.
 *  I don't wish to hear that someone ruined the BePro because they didn't understand my instructions.
 */




 // !!!!!!!!! BY CROSSING THIS LINE you hereby acknowledge that anything that doesn't compile is most likely your fault. I have usually tested things.
 // If you haven't read the info piece above, you should do so. !!!!!!!!!!




 /*****   CONSEQUENCES OF FAILURE TO READ THE PREVIOUS COMMENTS, OR INDEED THIS ONE, ARE ENTIRELY YOUR FAULT!            *****/
 /*****   I ASSUME THAT YOU HAVE READ EVERYTHING CAREFULLY, AND ALL THE CODE BELOW IS NOT TO BE EDITED UNTIL YOU HAVE!   *****/




#define PRIMARY_1 // This one is known to work, but not very well - Auto only has one game, 1-player is broken, and 2-player is working thoroughly.

//#define TEST_1_FIXINGAI // Fixin' up the AI, part 1. This one will hopefully play 1-player.



#ifdef PRIMARY_1      // If you uncommented PRIMARY_1, this will add whatever code is between it and the next #endif to the file.
  #include "1.h"      // Thus, this file is included.
#endif                // Exits the if condition.
