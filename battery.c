/** Copyright 2019 Achim Pieters | StudioPieters®

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   Build upon: ESP-HomeKit - MIT License - Copyright (c) 2017 Maxim Kulkin
 **/

homekit_characteristic_t status_low_battery = HOMEKIT_CHARACTERISTIC_(STATUS_LOW_BATTERY, 0);


int low_battery_value;
float battery_value;

void battery_low_task(void *_args) {

        while (1) {
                battery_value = sdk_system_adc_read();
                printf ("ADC voltage is %.3f\n", 1.0 / 1024 * sdk_system_adc_read()* 4.2);
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                if (1.0 / 1024 * battery_value * 4.2 < 3.900) {
                printf ("Battery value is low.\n");
                low_battery_value = 1;
                }
                else{
                printf ("Battery value is not low.\n");
                }
                homekit_characteristic_notify(&status_low_battery, HOMEKIT_UINT8(low_battery_value));
                vTaskDelay(3000 / portTICK_PERIOD_MS);
        }
}
void battery_low_init() {
        xTaskCreate(battery_low_task, "Battery Low", 256, NULL, 2, NULL);
}

&status_low_battery,


battery_low_init();
