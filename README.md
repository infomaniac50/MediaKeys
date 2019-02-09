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
