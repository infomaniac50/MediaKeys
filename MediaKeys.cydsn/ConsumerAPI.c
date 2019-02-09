/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// https://github.com/NicoHood/HID/blob/9c4eee90eda53d44bbf7c7cf0e1a46cb3e445973/src/SingleReport/SingleConsumer.cpp#L26
//
// static const uint8_t _hidSingleReportDescriptorConsumer[] PROGMEM = {
//   /* Consumer Control (Sound/Media keys) */
//   0x05, 0x0C,                 /* usage page (consumer device) */
//   0x09, 0x01,                 /* usage -- consumer control */
//   0xA1, 0x01,                 /* collection (application) */
//   /* 4 Media Keys */
//   0x15, 0x00,                 /* logical minimum */
//   0x26, 0xFF, 0x03,               /* logical maximum (3ff) */
//   0x19, 0x00,                 /* usage minimum (0) */
//   0x2A, 0xFF, 0x03,               /* usage maximum (3ff) */
//   0x95, 0x04,                 /* report count (4) */
//   0x75, 0x10,                 /* report size (16) */
//   0x81, 0x00,                 /* input */
//   0xC0 /* end collection */
// };

#include <device.h>
#include <ConsumerAPI.h>

HID_ConsumerControlReport_Data_t _report;
void ConsumerAPI_SendReport(void* data, int length) {
    USBFS_1_LoadInEP(1, data, length);
}

void ConsumerAPI_begin(void) {
	// release all buttons
	ConsumerAPI_end();
}

void ConsumerAPI_end(void) {
	memset(&_report, 0, sizeof(_report));
	ConsumerAPI_SendReport(&_report, sizeof(_report));
}

void ConsumerAPI_write(enum ConsumerKeycode m) {
	ConsumerAPI_press(m);
	ConsumerAPI_release(m);
}

void ConsumerAPI_press(enum ConsumerKeycode m) {
	// search for a free spot
	for (uint8 i = 0; i < sizeof(HID_ConsumerControlReport_Data_t) / 2; i++) {
		if (_report.keys[i] == HID_CONSUMER_UNASSIGNED) {
			_report.keys[i] = m;
			break;
		}
	}
	ConsumerAPI_SendReport(&_report, sizeof(_report));
}

void ConsumerAPI_release(enum ConsumerKeycode m) {
	// search and release the keypress
	for (uint8 i = 0; i < sizeof(HID_ConsumerControlReport_Data_t) / 2; i++) {
		if (_report.keys[i] == m) {
			_report.keys[i] = HID_CONSUMER_UNASSIGNED;
			// no break to delete multiple keys
		}
	}
	ConsumerAPI_SendReport(&_report, sizeof(_report));
}

void ConsumerAPI_releaseAll(void) {
	ConsumerAPI_end();
}
/* [] END OF FILE */
