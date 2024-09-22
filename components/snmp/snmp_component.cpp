#ifdef USE_ARDUINO

#include "snmp_component.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/version.h"
#include "esphome/components/wifi/wifi_component.h"
#include "esphome/core/component.h"
#include "esphome.h"

namespace esphome {
namespace snmp {

//using namespace apc_ups;

#define CUSTOM_OID ".1.3.9999."

static const char *const TAG = "snmp";

/// @brief Returns network uptime
/// @return time in hundreds of seconds
/// @warning 
/// Function returns real value if @c wifi_connected_timestamp() function
/// was implemented in WiFi module.
uint32_t SNMPComponent::get_net_uptime() {
#ifdef WIFI_CONNECTED_TIMESTAMP_AVAILABLE
  return (millis() - wifi::global_wifi_component->wifi_connected_timestamp()) / 10;
#else
  return 0; //not available
#endif
}

//SNMPComponent::SNMPComponent(text_sensor::TextSensor *snmp_model_name):
//    snmp_model_name_(snmp_model_name) {}

void SNMPComponent::setup_apc_ups_mib_() {

snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.1.1.1.0",  get_text_sensor_state(*snmp_model_name_));
snmp_agent_.addDynamicReadOnlyStringHandler(".1.3.6.1.4.1.318.1.1.1.1.1.2.0", get_text_sensor_state(*snmp_model_name_));


/*
snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.1.1.2.0", get_text_sensor_state("APC local identifier"));
snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.1.2.1.0", get_text_sensor_state("APC firmware revision"));
snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.1.2.2.0", get_text_sensor_state("APC manufacture date"));
snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.1.2.3.0", get_text_sensor_state("APC serial number"));
snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.2.1.3.0", get_text_sensor_state("APC last battery change date"));
snmp_agent_.addReadOnlyStaticStringHandler(".1.3.6.1.4.1.318.1.1.1.7.2.6.0", get_text_sensor_state("APC self test results"));

snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.2.2.1.0",  get_sensor_state("APC state of charge"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.2.2.2.0",  get_sensor_state("APC internal temperature"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.2.2.3.0",  get_sensor_state("APC estimated runtime"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.2.2.8.0",  get_sensor_state("APC battery voltage"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.3.2.1.0",  get_sensor_state("APC grid voltage"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.4.2.1.0",  get_sensor_state("APC ac output voltage"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.4.2.3.0",  get_sensor_state("APC ac output load"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.5.2.2.0",  get_sensor_state("APC max grid voltage"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.5.2.3.0",  get_sensor_state("APC min grid voltage"));
snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.11.1.1.0", get_sensor_state("APC status bitmask"));                    // отдельная функция
*/
//snmp_agent_.addDynamicIntegerHandler(".1.3.6.1.4.1.318.1.1.1.2.2.4.0", replace_battery);                    // 0 | 1

}



void SNMPComponent::setup_system_mib_() {
  // sysDescription
  const char *desc_fmt = "ESPHome version " ESPHOME_VERSION " compiled %s, Board " ESPHOME_BOARD;
  char description[128];
  snprintf(description, sizeof(description), desc_fmt, App.get_compilation_time().c_str());
  snmp_agent_.addReadOnlyStaticStringHandler(RFC1213_OID_sysDescr, description);
  // sysName
  snmp_agent_.addDynamicReadOnlyStringHandler(RFC1213_OID_sysName, []() -> std::string { return App.get_name(); });
  // sysServices
  snmp_agent_.addReadOnlyIntegerHandler(RFC1213_OID_sysServices, 64 /*=2^(7-1) applications*/);
  // sysObjectID
  snmp_agent_.addOIDHandler(RFC1213_OID_sysObjectID,
#ifdef USE_ESP32
                            CUSTOM_OID "Esp32"
#else
                            CUSTOM_OID "Esp8266"
#endif
  );
  // sysContact
  snmp_agent_.addReadOnlyStaticStringHandler(RFC1213_OID_sysContact, contact_);
  // sysLocation
  snmp_agent_.addReadOnlyStaticStringHandler(RFC1213_OID_sysLocation, location_);
}


std::string SNMPComponent::get_bssid() {
  ESP_LOGI(TAG, "get_bssid");
  char buf[30];
  wifi::bssid_t bssid = wifi::global_wifi_component->wifi_bssid();
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
  return buf;
}

std::string SNMPComponent::get_text_sensor_state(text_sensor::TextSensor text_sensor_name) {

  ESP_LOGI(TAG, "get_text_sensor_state");
//  ESP_LOGI(TAG, "get_text_sensor_state: %s", *text_sensor_name.get_state());
  char buff[30];
  sprintf(buff, "%s", text_sensor_name.get_state().c_str());
  ESP_LOGI(TAG, "get_text_sensor_state: %s", buff);
  return text_sensor_name.get_state();
}


void SNMPComponent::setup_chip_mib_() {
  // esp32/ esp8266
#if ESP32
  snmp_agent_.addReadOnlyIntegerHandler(CUSTOM_OID "2.1.0", 32);
#endif
#if ESP8266
  snmp_agent_.addReadOnlyIntegerHandler(CUSTOM_OID "2.1.0", 8266);
#endif
  // CPU clock
  snmp_agent_.addDynamicIntegerHandler(CUSTOM_OID "2.2.0", []() -> int { return ESP.getCpuFreqMHz(); });  // NOLINT
  // chip model
#if ESP32
  snmp_agent_.addDynamicReadOnlyStringHandler(CUSTOM_OID "2.3.0", []() -> std::string { return ESP.getChipModel(); });
#endif
#ifdef USE_ESP8266
  snmp_agent_.addDynamicReadOnlyStringHandler(CUSTOM_OID "2.3.0",
                                              []() -> std::string { return ESP.getCoreVersion().c_str(); });  // NOLINT
#endif
  // number of cores
#if USE_ESP32
  snmp_agent_.addDynamicIntegerHandler(CUSTOM_OID "2.4.0", []() -> int { return ESP.getChipCores(); });
#endif
#if USE_ESP8266
  snmp_agent_.addReadOnlyIntegerHandler(CUSTOM_OID "2.4.0", 1);
#endif
  // chip id
#if ESP32
  snmp_agent_.addDynamicIntegerHandler(CUSTOM_OID "2.5.0", []() -> int { return ESP.getChipRevision(); });
#endif
#if ESP8266
  snmp_agent_.addReadOnlyIntegerHandler(CUSTOM_OID "2.5.0", 0 /*no data for ESP8266*/);
#endif
}


void SNMPComponent::setup_wifi_mib_() {
  // RSSI
  snmp_agent_.addDynamicIntegerHandler(CUSTOM_OID "4.1.0",
                                       []() -> int { return wifi::global_wifi_component->wifi_rssi(); });
  // BSSID
  snmp_agent_.addDynamicReadOnlyStringHandler(CUSTOM_OID "4.2.0", get_bssid);
  // SSID
  snmp_agent_.addDynamicReadOnlyStringHandler(CUSTOM_OID "4.3.0",
                                              []() -> std::string { return wifi::global_wifi_component->wifi_ssid(); });
  // IP
  snmp_agent_.addDynamicReadOnlyStringHandler(
      CUSTOM_OID "4.4.0", []() -> std::string { 
        const auto& ip_array = wifi::global_wifi_component->wifi_sta_ip_addresses();
        return ip_array.size() ? wifi::global_wifi_component->wifi_sta_ip_addresses()[0].str() : ""; } );
}


void SNMPComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SNMP...");

  this->snmp_model_name_->add_on_state_callback([this](const std::string &value) { this->publish_state(value); });
  if (snmp_model_name_->has_state()) {
    LOG_TEXT_SENSOR(TAG, "-Copy Sensor", this);
    this->publish_state(this->snmp_model_name_->get_state());
  }
  // sysUpTime
  // this is uptime of network management part of the system
  // WARNING: Only available if wifi_connected_timestamp() function was implemented
  // in WiFi module.
  // By default returns always 0
  snmp_agent_.addDynamicReadOnlyTimestampHandler(RFC1213_OID_sysUpTime, get_net_uptime);
  // hrSystemUptime
  snmp_agent_.addDynamicReadOnlyTimestampHandler(".1.3.6.1.2.1.25.1.1.0", get_uptime);

  setup_system_mib_();
  setup_apc_ups_mib_();
  setup_chip_mib_();
  setup_wifi_mib_();

  snmp_agent_.sortHandlers();  // for walk to work properly
  snmp_agent_.setUDP(&udp_);
  snmp_agent_.begin();
}


void SNMPComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "SNMP Config:");
  ESP_LOGCONFIG(TAG, "  Contact: \"%s\"", contact_.c_str());
  ESP_LOGCONFIG(TAG, "  Location: \"%s\"", location_.c_str());
  ESP_LOGCONFIG(TAG, "  TextSensor name: %s", this->snmp_model_name_->get_name().c_str());
}


void SNMPComponent::loop() { snmp_agent_.loop(); }

}  // namespace snmp
}  // namespace esphome

#endif  // USE_ARDUINO
