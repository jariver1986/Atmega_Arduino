// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h> // the OBD2 library depends on the CAN library
#include <OBD2.h>

void setup() {
  Serial.begin(38400);
  Serial1.begin(9600);
  while (!Serial);

  //Serial.println(F("OBD2 data printer"));
  Serial1.println(F("OBD2 data printer"));
  while (true) 
  {
    //Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));
    Serial1.print(F("Attempting to connect to OBD2 CAN bus ... "));
    if (!OBD2.begin()) 
    {
      //Serial.println(F("failed!"));
      Serial1.println(F("failed!"));
      delay(1000);
    } else {
      //Serial.println(F("success"));
      Serial1.println(F("success"));
      break;
    }
  }

  Serial1.println();
  Serial1.print("VIN = ");
  Serial1.println(OBD2.vinRead());
  Serial1.print("ECU Name = ");
  Serial1.println(OBD2.ecuNameRead());
  Serial1.println();
}

void loop() {
  // loop through PIDs 0 to 95, reading and printing the values
  for (int pid = 0; pid < 96; pid++) {
    processPid(pid);
  }
  Serial1.println();

  // wait 5 seconds before next run
  delay(5000);
}

void processPid(int pid) {
  if (!OBD2.pidSupported(pid)) {
    // PID not supported, continue to next one ...
    return;
  }

  // print PID name
  Serial1.print(OBD2.pidName(pid));
  Serial1.print(F(" = "));

  if (OBD2.pidValueRaw(pid)) {
    // read the raw PID value
    unsigned long pidRawValue = OBD2.pidReadRaw(pid);

    Serial1.print(F("0x"));
    Serial1.print(pidRawValue, HEX);
  } else {
    // read the PID value
    float pidValue = OBD2.pidRead(pid);

    if (isnan(pidValue)) {
      Serial1.print("error");
    } else {
      // print value with units

      Serial1.print(pidValue);
      Serial1.print(F(" "));
      Serial1.print(OBD2.pidUnits(pid));
    }
  }

  Serial1.println();
}
