# MediaKeys

Implements HID consumer control inputs on the FreeSoC2. Consumer Control inputs are things like multimedia keys and browser back/forward.

Some of this code is derived from https://github.com/NicoHood/HID

## FreeSoC2

This board is from Sparkfun and the one they list is newer than my board. Mine was built on the v11 revision https://www.sparkfun.com/products/retired/13229. So this is the revision I will be referencing here.

The device selection in PSoC Creator should be CY8C5888AXI-LP096.

This project uses the USB component. This component has very tight clock requirements. The following is a list of clock settings required for USB. This list does not nescessarily include all clocks.

- ILO
  - [x] 1 kHz
  - [ ] 33 kHz
  - [x] 100 kHz
  - Route: 100 kHz
- IMO: 24 MHz +-0.25%
  - [x] Osc
- USB: IMOx2 - 48 MHz
  - [ ] Divide by 2

## Debugging

  **You can't do it.**

  Debugging the main chip stops all activity. There is no way around this unless someone at Cypress updates the debugger to not interfere with the USB component.

  The report rate for this project is 10 milliseconds. If the USB device does not respond with that time then the host will disconnect the device. If you try this anyway then the device will connect and then immediately disconnect. Windows will tell you there is a problem with the device. After that Windows won't talk to the device anymore. To fix it you have to stop the debugger and then unplug and reinsert the target usb cable.

  If you must debug the target then you have to disable all USB related code. This includes the USBFS component on the design schematic. You can disable components by right-clicking on the symbol and selecting Disable. This will remove the "Application API" code, so you will have to comment out the function calls in your source files.