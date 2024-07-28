# ESPHome SNMP component for APC UPS

This is an external ESPHome component that enables support for SNMP protocol for APC UPS. The protocol is widely used in network management and network monitoring.

> [!WARNING]
> This external component only works together with the `esphome-apc-ups`component!

## esphome-apc-ups component

[@syssi esphome-apc-ups](https://github.com/syssi/esphome-apc-ups)<br>
[@samoswall esphome-apc-ups](https://github.com/samoswall/esphome-apc-ups)

## ESPHome SNMP component for APC UPS
This is description of the external ESPHome component that enables support for SNMP protocol for APC UPS. The protocol is widely used in network management and network monitoring.
This component requires Wi-Fi enabled. It supports version 2c of the protocol. All items are read only.

> [!Note]
> SNMP is not supported for Ethernet.

# Example configuration entry
```yaml
snmp:
  contact: Joe
  location: Basement
```
# Configuration variables
`contact` Value for sysContact (1.3.6.1.2.1.1.4) OID.<br>
`location` Value for sysLocation (1.3.6.1.2.1.1.6) OID.

Installation
Add the following section to your ESPHome YAML configuration file:
```yaml
external_components:
    # SNMP component
    - source: github://samoswall/esphome-snmp-apc-ups@main
```
## APC UPS OID List
|Oid|Variable snmp|Type|variable of the esphome-aps-ups component|
|---|-------------|----|-----------------------------------------|  
|.1.3.6.1.4.1.318.1.1.1.2.2.8.0|upsAdvBatteryActualVoltage|Integer|battery_voltage|
|.1.3.6.1.4.1.318.1.1.1.2.2.2.0|upsAdvBatteryTemperature|Integer|internal_temperature|
|.1.3.6.1.4.1.318.1.1.1.3.2.1.0|upsAdvInputLineVoltage|Integer|grid_voltage|
|.1.3.6.1.4.1.318.1.1.1.5.2.2.0|upsAdvConfigHighTransferVolt|Integer|max_grid_voltage|
|.1.3.6.1.4.1.318.1.1.1.5.2.3.0|upsAdvConfigLowTransferVolt|Integer|min_grid_voltage|
|.1.3.6.1.4.1.318.1.1.1.4.2.1.0|upsAdvOutputVoltage|Integer|ac_output_voltage|
|.1.3.6.1.4.1.318.1.1.1.4.2.3.0|upsAdvOutputLoad|Integer|ac_output_load|
|.1.3.6.1.4.1.318.1.1.1.11.1.1.0|upsBasicStateOutputState|Integer|status_bitmask|
|.1.3.6.1.4.1.318.1.1.1.7.2.6.0|upsAdvTestCalibrationResults|String|self_test_results|
|.1.3.6.1.4.1.318.1.1.1.1.2.1.0|upsAdvIdentFirmwareRevision|String|firmware_revision|
|.1.3.6.1.4.1.318.1.1.1.1.1.2.0|upsBasicIdentName|String|local_identifier|
|.1.3.6.1.4.1.318.1.1.1.2.2.1.0|upsAdvBatteryCapacity|Integer|state_of_charge|
|.1.3.6.1.4.1.318.1.1.1.2.2.3.0|upsAdvBatteryRunTimeRemaining|Integer|estimated_runtime|
|.1.3.6.1.4.1.318.1.1.1.1.2.2.0|upsAdvIdentDateOfManufacture|String|manufacture_date|
|.1.3.6.1.4.1.318.1.1.1.1.2.3.0|upsAdvIdentSerialNumber|String|serial_number|
|.1.3.6.1.4.1.318.1.1.1.2.1.3.0|upsBasicBatteryLastReplaceDate|String|last_battery_change_date|
|.1.3.6.1.4.1.318.1.1.1.1.1.1.0|upsBasicIdentModel|String|model_name|

## APC UPS System OID List

|Oid|Variable snmp|
|---|-------------|
|.1.3.6.1.2.1.1.1.0	|sysDescr|
|.1.3.6.1.2.1.1.2.0	|sysObjectID|
|.1.3.6.1.2.1.1.3.0	|sysUpTime|
|.1.3.6.1.2.1.1.4.0	|sysContact|
|.1.3.6.1.2.1.1.5.0	|sysName|
|.1.3.6.1.2.1.1.6.0	|sysLocation|
|.1.3.6.1.2.1.2.2.1.6.0.2	|ifPhysAddress|
|.1.3.6.1.2.1.25.1.1.0	|hrSystemUptime|

## CUSTOM OID

|Oid|Variable|
|---|--------|
|.1.3.9999.4.1.0|	RSSI|
|.1.3.9999.4.2.0|	BSSID|
|.1.3.9999.4.3.0|	SSID|
|.1.3.9999.4.4.0|	IP|
|.1.3.9999.2.1.0|	esp32 or esp8266|
|.1.3.9999.2.2.0|	CpuFreqMHz|
|.1.3.9999.2.3.0|	ChipModel|
|.1.3.9999.2.4.0|	ChipCores|
|.1.3.9999.2.5.0|	ChipRevision|



**Documentation:** https://aquaticus.info/snmp.html


