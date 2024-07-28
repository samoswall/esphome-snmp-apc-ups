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
## OID List




**Documentation:** https://aquaticus.info/snmp.html


