/* By Tyler Clarke, circa a.d. 2021
 *  
 *  Gives error management and etc to our projects.
 */

void hardfault(const char* position){
    Serial.print("HARDWARE FAULT DETECTED - DO NOT attempt to resolve this on your own; instead, contact us at https://firestormrobotics.org. Fault detected in ");
    Serial.println(position);
    Serial.println("Please consult the manual, if we happen to have given you one.");
}

void softfault(const char* message, const char* position){
  Serial.print("SOFTWARE FAULT DETECTED - ");
  Serial.print(message);
  Serial.print(" Fault detected in ");
  Serial.println(position);
  Serial.println("Please consult the manual, if we happen to have given you one.");
}

void unknownfault(const char* message, const char* position){
  Serial.print("UNKNOWN FAULT DETECTED - ");
  Serial.print(message);
  Serial.print(" Fault detected in ");
  Serial.println(position);
  Serial.println("Please consult the manual, if we happen to have given you one.");
}
