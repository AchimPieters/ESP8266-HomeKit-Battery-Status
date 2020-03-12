
homekit_characteristic_t status_low_battery = HOMEKIT_CHARACTERISTIC_(STATUS_LOW_BATTERY, 0);

void battery_status_low_task(void *_args) {

    uint8_t battery_status_value;
    while (1) {
         battery_status_value = sdk_system_adc_read();
         printf ("ADC voltage is %.3f", 1.0 / 1024 * sdk_system_adc_read()); // 4.2V = (((1.0/1024)*1024)*4.2) (Ratio 4.20)
         if (battery_status_value < 770){  // 3.158V = (((1.0/1024)*700)*4.2) Don't let the battery drop below 3.0V (Ratio 4.20)
           status_low_battery = true;
         }
         else{
           status_low_battery = false;
         }
            homekit_characteristic_notify(&status_low_battery, HOMEKIT_UINT8(battery_status_value));
            vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void battery_status_low_init() {
    xTaskCreate(battery_status_low_task, "Status Low Battery", 256, NULL, 2, NULL);
}

 	    &status_low_battery,

    battery_status_low_init();












    /**
     Defines that the accessory contains a battery that can be monitored.

     Required Characteristics:
     - BATTERY_LEVEL
     - CHARGING_STATE
     - STATUS_LOW_BATTERY

     Optional Characteristics:
     - NAME
     */
    #define HOMEKIT_SERVICE_BATTERY_SERVICE HOMEKIT_APPLE_UUID2("96")

#define HOMEKIT_CHARACTERISTIC_BATTERY_LEVEL HOMEKIT_APPLE_UUID2("68")
#define HOMEKIT_DECLARE_CHARACTERISTIC_BATTERY_LEVEL(_value, ...) \
    .type = HOMEKIT_CHARACTERISTIC_BATTERY_LEVEL, \
    .description = "Battery Level", \
    .format = homekit_format_uint8, \
    .unit = homekit_unit_percentage, \
    .permissions = homekit_permissions_paired_read \
                 | homekit_permissions_notify, \
    .min_value = (float[]) {0}, \
    .max_value = (float[]) {100}, \
    .min_step = (float[]) {1}, \
    .value = HOMEKIT_UINT8_(_value), \
    ##__VA_ARGS__


#define HOMEKIT_CHARACTERISTIC_CHARGING_STATE HOMEKIT_APPLE_UUID2("8F")
#define HOMEKIT_DECLARE_CHARACTERISTIC_CHARGING_STATE(_value, ...) \
    .type = HOMEKIT_CHARACTERISTIC_CHARGING_STATE, \
    .description = "Charging State", \
    .format = homekit_format_uint8, \
    .permissions = homekit_permissions_paired_read \
                 | homekit_permissions_notify, \
    .min_value = (float[]) {0}, \
    .max_value = (float[]) {2}, \
    .min_step = (float[]) {1}, \
    .valid_values = { \
        .count = 3, \
        .values = (uint8_t[]) { 0, 1, 2 }, \
    }, \
    .value = HOMEKIT_UINT8_(_value), \
    ##__VA_ARGS__


#define HOMEKIT_CHARACTERISTIC_STATUS_LOW_BATTERY HOMEKIT_APPLE_UUID2("79")
#define HOMEKIT_DECLARE_CHARACTERISTIC_STATUS_LOW_BATTERY(_value, ...) \
      .type = HOMEKIT_CHARACTERISTIC_STATUS_LOW_BATTERY, \
      .description = "Status Low Battery", \
      .format = homekit_format_uint8, \
      .permissions = homekit_permissions_paired_read \
                   | homekit_permissions_notify, \
      .min_value = (float[]) {0}, \
      .max_value = (float[]) {1}, \
      .min_step = (float[]) {1}, \
      .valid_values = { \
          .count = 2, \
          .values = (uint8_t[]) { 0, 1 }, \
      }, \
      .value = HOMEKIT_UINT8_(_value), \
      ##__VA_ARGS__


#define HOMEKIT_CHARACTERISTIC_NAME HOMEKIT_APPLE_UUID2("23")
#define HOMEKIT_DECLARE_CHARACTERISTIC_NAME(name, ...) \
      .type = HOMEKIT_CHARACTERISTIC_NAME, \
      .description = "Name", \
      .format = homekit_format_string, \
      .permissions = homekit_permissions_paired_read, \
      .value = HOMEKIT_STRING_(name), \
      ##__VA_ARGS__
