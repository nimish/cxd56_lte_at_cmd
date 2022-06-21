You'll need to enable LTE in the SDK along with extensions. This requires that the `alt1250` daemon is started with `lte_sysctl start` 

Usage: `lte_at_cmd AT+COPS` or `lte_at_cmd AT%GETACFG`

AT+ commands are the standard [3GPP 27.007 commands](https://www.etsi.org/deliver/etsi_ts/127000_127099/127007/13.03.00_60/ts_127007v130300p.pdf)

AT% commands are proprietary ones for the Murata 1SC-DM module.

