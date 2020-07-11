/*
 *	btlehrservice - Bluetooth-Low-Energy heart rate service
 *	Copyright (C) 2019-2020 Johannes Bauer
 *
 *	This file is part of btlehrservice.
 *
 *	btlehrservice is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; this program is ONLY licensed under
 *	version 3 of the License, later versions are explicitly excluded.
 *
 *	btlehrservice is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with btlehrservice; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	Johannes Bauer <JohannesBauer@gmx.de>
 */

#ifndef __UUIDS_H__
#define __UUIDS_H__

#define BT_CHARID_AerobicHeartRateLowerLimit						0x2a7e	// org.bluetooth.characteristic.aerobic_heart_rate_lower_limit
#define BT_CHARID_AerobicHeartRateUpperLimit						0x2a84	// org.bluetooth.characteristic.aerobic_heart_rate_upper_limit
#define BT_CHARID_AerobicThreshold									0x2a7f	// org.bluetooth.characteristic.aerobic_threshold
#define BT_CHARID_Age												0x2a80	// org.bluetooth.characteristic.age
#define BT_CHARID_Aggregate											0x2a5a	// org.bluetooth.characteristic.aggregate
#define BT_CHARID_AlertCategoryID									0x2a43	// org.bluetooth.characteristic.alert_category_id
#define BT_CHARID_AlertCategoryIDBitMask							0x2a42	// org.bluetooth.characteristic.alert_category_id_bit_mask
#define BT_CHARID_AlertLevel										0x2a06	// org.bluetooth.characteristic.alert_level
#define BT_CHARID_AlertNotificationControlPoint						0x2a44	// org.bluetooth.characteristic.alert_notification_control_point
#define BT_CHARID_AlertStatus										0x2a3f	// org.bluetooth.characteristic.alert_status
#define BT_CHARID_Altitude											0x2ab3	// org.bluetooth.characteristic.altitude
#define BT_CHARID_AnaerobicHeartRateLowerLimit						0x2a81	// org.bluetooth.characteristic.anaerobic_heart_rate_lower_limit
#define BT_CHARID_AnaerobicHeartRateUpperLimit						0x2a82	// org.bluetooth.characteristic.anaerobic_heart_rate_upper_limit
#define BT_CHARID_AnaerobicThreshold								0x2a83	// org.bluetooth.characteristic.anaerobic_threshold
#define BT_CHARID_Analog											0x2a58	// org.bluetooth.characteristic.analog
#define BT_CHARID_AnalogOutput										0x2a59	// org.bluetooth.characteristic.analog_output
#define BT_CHARID_ApparentWindDirection								0x2a73	// org.bluetooth.characteristic.apparent_wind_direction
#define BT_CHARID_ApparentWindSpeed									0x2a72	// org.bluetooth.characteristic.apparent_wind_speed
#define BT_CHARID_Appearance										0x2a01	// org.bluetooth.characteristic.gap.appearance
#define BT_CHARID_BarometricPressureTrend							0x2aa3	// org.bluetooth.characteristic.barometric_pressure_trend
#define BT_CHARID_BatteryLevel										0x2a19	// org.bluetooth.characteristic.battery_level
#define BT_CHARID_BatteryLevelState									0x2a1b	// org.bluetooth.characteristic.battery_level_state
#define BT_CHARID_BatteryPowerState									0x2a1a	// org.bluetooth.characteristic.battery_power_state
#define BT_CHARID_BloodPressureFeature								0x2a49	// org.bluetooth.characteristic.blood_pressure_feature
#define BT_CHARID_BloodPressureMeasurement							0x2a35	// org.bluetooth.characteristic.blood_pressure_measurement
#define BT_CHARID_BodyCompositionFeature							0x2a9b	// org.bluetooth.characteristic.body_composition_feature
#define BT_CHARID_BodyCompositionMeasurement						0x2a9c	// org.bluetooth.characteristic.body_composition_measurement
#define BT_CHARID_BodySensorLocation								0x2a38	// org.bluetooth.characteristic.body_sensor_location
#define BT_CHARID_BondManagementControlPoint						0x2aa4	// org.bluetooth.characteristic.bond_management_control_point
#define BT_CHARID_BondManagementFeatures							0x2aa5	// org.bluetooth.characteristic.bond_management_feature
#define BT_CHARID_BootKeyboardInputReport							0x2a22	// org.bluetooth.characteristic.boot_keyboard_input_report
#define BT_CHARID_BootKeyboardOutputReport							0x2a32	// org.bluetooth.characteristic.boot_keyboard_output_report
#define BT_CHARID_BootMouseInputReport								0x2a33	// org.bluetooth.characteristic.boot_mouse_input_report
#define BT_CHARID_BSSControlPoint									0x2b2b	// GATT Characteristic UUID
#define BT_CHARID_BSSResponse										0x2b2c	// GATT Characteristic UUID
#define BT_CHARID_CGMFeature										0x2aa8	// org.bluetooth.characteristic.cgm_feature
#define BT_CHARID_CGMMeasurement									0x2aa7	// org.bluetooth.characteristic.cgm_measurement
#define BT_CHARID_CGMSessionRunTime									0x2aab	// org.bluetooth.characteristic.cgm_session_run_time
#define BT_CHARID_CGMSessionStartTime								0x2aaa	// org.bluetooth.characteristic.cgm_session_start_time
#define BT_CHARID_CGMSpecificOpsControlPoint						0x2aac	// org.bluetooth.characteristic.cgm_specific_ops_control_point
#define BT_CHARID_CGMStatus											0x2aa9	// org.bluetooth.characteristic.cgm_status
#define BT_CHARID_ClientSupportedFeatures							0x2b29	// GATT Characteristic UUID
#define BT_CHARID_CrossTrainerData									0x2ace	// org.bluetooth.characteristic.cross_trainer_data
#define BT_CHARID_CSCFeature										0x2a5c	// org.bluetooth.characteristic.csc_feature
#define BT_CHARID_CSCMeasurement									0x2a5b	// org.bluetooth.characteristic.csc_measurement
#define BT_CHARID_CurrentTime										0x2a2b	// org.bluetooth.characteristic.current_time
#define BT_CHARID_CyclingPowerControlPoint							0x2a66	// org.bluetooth.characteristic.cycling_power_control_point
#define BT_CHARID_CyclingPowerFeature								0x2a65	// org.bluetooth.characteristic.cycling_power_feature
#define BT_CHARID_CyclingPowerMeasurement							0x2a63	// org.bluetooth.characteristic.cycling_power_measurement
#define BT_CHARID_CyclingPowerVector								0x2a64	// org.bluetooth.characteristic.cycling_power_vector
#define BT_CHARID_DatabaseChangeIncrement							0x2a99	// org.bluetooth.characteristic.database_change_increment
#define BT_CHARID_DatabaseHash										0x2b2a	// GATT Characteristic UUID
#define BT_CHARID_DateofBirth										0x2a85	// org.bluetooth.characteristic.date_of_birth
#define BT_CHARID_DateofThresholdAssessment							0x2a86	// org.bluetooth.characteristic.date_of_threshold_assessment
#define BT_CHARID_DateTime											0x2a08	// org.bluetooth.characteristic.date_time
#define BT_CHARID_DateUTC											0x2aed	// org.bluetooth.characteristic.date_utc
#define BT_CHARID_DayDateTime										0x2a0a	// org.bluetooth.characteristic.day_date_time
#define BT_CHARID_DayofWeek											0x2a09	// org.bluetooth.characteristic.day_of_week
#define BT_CHARID_DescriptorValueChanged							0x2a7d	// org.bluetooth.characteristic.descriptor_value_changed
#define BT_CHARID_DewPoint											0x2a7b	// org.bluetooth.characteristic.dew_point
#define BT_CHARID_Digital											0x2a56	// org.bluetooth.characteristic.digital
#define BT_CHARID_DigitalOutput										0x2a57	// org.bluetooth.characteristic.digital_output
#define BT_CHARID_DSTOffset											0x2a0d	// org.bluetooth.characteristic.dst_offset
#define BT_CHARID_Elevation											0x2a6c	// org.bluetooth.characteristic.elevation
#define BT_CHARID_EmailAddress										0x2a87	// org.bluetooth.characteristic.email_address
#define BT_CHARID_EmergencyID										0x2b2d	// GATT Characteristic UUID
#define BT_CHARID_EmergencyText										0x2b2e	// GATT Characteristic UUID
#define BT_CHARID_ExactTime100										0x2a0b	// org.bluetooth.characteristic.exact_time_100
#define BT_CHARID_ExactTime256										0x2a0c	// org.bluetooth.characteristic.exact_time_256
#define BT_CHARID_FatBurnHeartRateLowerLimit						0x2a88	// org.bluetooth.characteristic.fat_burn_heart_rate_lower_limit
#define BT_CHARID_FatBurnHeartRateUpperLimit						0x2a89	// org.bluetooth.characteristic.fat_burn_heart_rate_upper_limit
#define BT_CHARID_FirmwareRevisionString							0x2a26	// org.bluetooth.characteristic.firmware_revision_string
#define BT_CHARID_FirstName											0x2a8a	// org.bluetooth.characteristic.first_name
#define BT_CHARID_FitnessMachineControlPoint						0x2ad9	// org.bluetooth.characteristic.fitness_machine_control_point
#define BT_CHARID_FitnessMachineFeature								0x2acc	// org.bluetooth.characteristic.fitness_machine_feature
#define BT_CHARID_FitnessMachineStatus								0x2ada	// org.bluetooth.characteristic.fitness_machine_status
#define BT_CHARID_FiveZoneHeartRateLimits							0x2a8b	// org.bluetooth.characteristic.five_zone_heart_rate_limits
#define BT_CHARID_FloorNumber										0x2ab2	// org.bluetooth.characteristic.floor_number
#define BT_CHARID_CentralAddressResolution							0x2aa6	// org.bluetooth.characteristic.gap.central_address_resolution
#define BT_CHARID_DeviceName										0x2a00	// org.bluetooth.characteristic.gap.device_name
#define BT_CHARID_PeripheralPreferredConnectionParameters			0x2a04	// org.bluetooth.characteristic.gap.peripheral_preferred_connection_parameters
#define BT_CHARID_PeripheralPrivacyFlag								0x2a02	// org.bluetooth.characteristic.gap.peripheral_privacy_flag
#define BT_CHARID_ReconnectionAddress								0x2a03	// org.bluetooth.characteristic.gap.reconnection_address
#define BT_CHARID_ServiceChanged									0x2a05	// org.bluetooth.characteristic.gatt.service_changed
#define BT_CHARID_Gender											0x2a8c	// org.bluetooth.characteristic.gender
#define BT_CHARID_GlucoseFeature									0x2a51	// org.bluetooth.characteristic.glucose_feature
#define BT_CHARID_GlucoseMeasurement								0x2a18	// org.bluetooth.characteristic.glucose_measurement
#define BT_CHARID_GlucoseMeasurementContext							0x2a34	// org.bluetooth.characteristic.glucose_measurement_context
#define BT_CHARID_GustFactor										0x2a74	// org.bluetooth.characteristic.gust_factor
#define BT_CHARID_HardwareRevisionString							0x2a27	// org.bluetooth.characteristic.hardware_revision_string
#define BT_CHARID_HeartRateControlPoint								0x2a39	// org.bluetooth.characteristic.heart_rate_control_point
#define BT_CHARID_HeartRateMax										0x2a8d	// org.bluetooth.characteristic.heart_rate_max
#define BT_CHARID_HeartRateMeasurement								0x2a37	// org.bluetooth.characteristic.heart_rate_measurement
#define BT_CHARID_HeatIndex											0x2a7a	// org.bluetooth.characteristic.heat_index
#define BT_CHARID_Height											0x2a8e	// org.bluetooth.characteristic.height
#define BT_CHARID_HIDControlPoint									0x2a4c	// org.bluetooth.characteristic.hid_control_point
#define BT_CHARID_HIDInformation									0x2a4a	// org.bluetooth.characteristic.hid_information
#define BT_CHARID_HipCircumference									0x2a8f	// org.bluetooth.characteristic.hip_circumference
#define BT_CHARID_HTTPControlPoint									0x2aba	// org.bluetooth.characteristic.http_control_point
#define BT_CHARID_HTTPEntityBody									0x2ab9	// org.bluetooth.characteristic.http_entity_body
#define BT_CHARID_HTTPHeaders										0x2ab7	// org.bluetooth.characteristic.http_headers
#define BT_CHARID_HTTPStatusCode									0x2ab8	// org.bluetooth.characteristic.http_status_code
#define BT_CHARID_HTTPSSecurity										0x2abb	// org.bluetooth.characteristic.https_security
#define BT_CHARID_Humidity											0x2a6f	// org.bluetooth.characteristic.humidity
#define BT_CHARID_IDDAnnunciationStatus								0x2b22	// org.bluetooth.characteristic.idd_annunciation_status
#define BT_CHARID_IDDCommandControlPoint							0x2b25	// org.bluetooth.characteristic.idd_command_control_point
#define BT_CHARID_IDDCommandData									0x2b26	// org.bluetooth.characteristic.idd_command_data
#define BT_CHARID_IDDFeatures										0x2b23	// org.bluetooth.characteristic.idd_features
#define BT_CHARID_IDDHistoryData									0x2b28	// org.bluetooth.characteristic.idd_history_data
#define BT_CHARID_IDDRecordAccessControlPoint						0x2b27	// org.bluetooth.characteristic.idd_record_access_control_point
#define BT_CHARID_IDDStatus											0x2b21	// org.bluetooth.characteristic.idd_status
#define BT_CHARID_IDDStatusChanged									0x2b20	// org.bluetooth.characteristic.idd_status_changed
#define BT_CHARID_IDDStatusReaderControlPoint						0x2b24	// org.bluetooth.characteristic.idd_status_reader_control_point
#define BT_CHARID_IEEE11073_20601RegulatoryCertificationDataList	0x2a2a	// org.bluetooth.characteristic.ieee_11073-20601_regulatory_certification_data_list
#define BT_CHARID_IndoorBikeData									0x2ad2	// org.bluetooth.characteristic.indoor_bike_data
#define BT_CHARID_IndoorPositioningConfiguration					0x2aad	// org.bluetooth.characteristic.indoor_positioning_configuration
#define BT_CHARID_IntermediateCuffPressure							0x2a36	// org.bluetooth.characteristic.intermediate_cuff_pressure
#define BT_CHARID_IntermediateTemperature							0x2a1e	// org.bluetooth.characteristic.intermediate_temperature
#define BT_CHARID_Irradiance										0x2a77	// org.bluetooth.characteristic.irradiance
#define BT_CHARID_Language											0x2aa2	// org.bluetooth.characteristic.language
#define BT_CHARID_LastName											0x2a90	// org.bluetooth.characteristic.last_name
#define BT_CHARID_Latitude											0x2aae	// org.bluetooth.characteristic.latitude
#define BT_CHARID_LNControlPoint									0x2a6b	// org.bluetooth.characteristic.ln_control_point
#define BT_CHARID_LNFeature											0x2a6a	// org.bluetooth.characteristic.ln_feature
#define BT_CHARID_LocalEastCoordinate								0x2ab1	// org.bluetooth.characteristic.local_east_coordinate
#define BT_CHARID_LocalNorthCoordinate								0x2ab0	// org.bluetooth.characteristic.local_north_coordinate
#define BT_CHARID_LocalTimeInformation								0x2a0f	// org.bluetooth.characteristic.local_time_information
#define BT_CHARID_LocationandSpeedCharacteristic					0x2a67	// org.bluetooth.characteristic.location_and_speed
#define BT_CHARID_LocationName										0x2ab5	// org.bluetooth.characteristic.location_name
#define BT_CHARID_Longitude											0x2aaf	// org.bluetooth.characteristic.Longitude
#define BT_CHARID_MagneticDeclination								0x2a2c	// org.bluetooth.characteristic.magnetic_declination
#define BT_CHARID_MagneticFluxDensity_2D							0x2aa0	// org.bluetooth.characteristic.Magnetic_flux_density_2D
#define BT_CHARID_MagneticFluxDensity_3D							0x2aa1	// org.bluetooth.characteristic.Magnetic_flux_density_3D
#define BT_CHARID_ManufacturerNameString							0x2a29	// org.bluetooth.characteristic.manufacturer_name_string
#define BT_CHARID_MaximumRecommendedHeartRate						0x2a91	// org.bluetooth.characteristic.maximum_recommended_heart_rate
#define BT_CHARID_MeasurementInterval								0x2a21	// org.bluetooth.characteristic.measurement_interval
#define BT_CHARID_MeshProvisioningDataIn							0x2adb	// GATT Characteristic UUID
#define BT_CHARID_MeshProvisioningDataOut							0x2adc	// GATT Characteristic UUID
#define BT_CHARID_MeshProxyDataIn									0x2add	// GATT Characteristic UUID
#define BT_CHARID_MeshProxyDataOut									0x2ade	// GATT Characteristic UUID
#define BT_CHARID_ModelNumberString									0x2a24	// org.bluetooth.characteristic.model_number_string
#define BT_CHARID_Navigation										0x2a68	// org.bluetooth.characteristic.navigation
#define BT_CHARID_NetworkAvailability								0x2a3e	// org.bluetooth.characteristic.network_availability
#define BT_CHARID_NewAlert											0x2a46	// org.bluetooth.characteristic.new_alert
#define BT_CHARID_ObjectActionControlPoint							0x2ac5	// org.bluetooth.characteristic.object_action_control_point
#define BT_CHARID_ObjectChanged										0x2ac8	// org.bluetooth.characteristic.object_changed
#define BT_CHARID_ObjectFirst_Created								0x2ac1	// org.bluetooth.characteristic.object_first_created
#define BT_CHARID_ObjectID											0x2ac3	// org.bluetooth.characteristic.object_id
#define BT_CHARID_ObjectLast_Modified								0x2ac2	// org.bluetooth.characteristic.object_last_modified
#define BT_CHARID_ObjectListControlPoint							0x2ac6	// org.bluetooth.characteristic.object_list_control_point
#define BT_CHARID_ObjectListFilter									0x2ac7	// org.bluetooth.characteristic.object_list_filter
#define BT_CHARID_ObjectName										0x2abe	// org.bluetooth.characteristic.object_name
#define BT_CHARID_ObjectProperties									0x2ac4	// org.bluetooth.characteristic.object_properties
#define BT_CHARID_ObjectSize										0x2ac0	// org.bluetooth.characteristic.object_size
#define BT_CHARID_ObjectType										0x2abf	// org.bluetooth.characteristic.object_type
#define BT_CHARID_OTSFeature										0x2abd	// org.bluetooth.characteristic.ots_feature
#define BT_CHARID_PLXContinuousMeasurementCharacteristic			0x2a5f	// org.bluetooth.characteristic.plx_continuous_measurement
#define BT_CHARID_PLXFeatures										0x2a60	// org.bluetooth.characteristic.plx_features
#define BT_CHARID_PLXSpot_CheckMeasurement							0x2a5e	// org.bluetooth.characteristic.plx_spot_check_measurement
#define BT_CHARID_PnPID												0x2a50	// org.bluetooth.characteristic.pnp_id
#define BT_CHARID_PollenConcentration								0x2a75	// org.bluetooth.characteristic.pollen_concentration
#define BT_CHARID_Position2D										0x2a2f	// org.bluetooth.characteristic.position_2d
#define BT_CHARID_Position3D										0x2a30	// org.bluetooth.characteristic.position_3d
#define BT_CHARID_PositionQuality									0x2a69	// org.bluetooth.characteristic.position_quality
#define BT_CHARID_Pressure											0x2a6d	// org.bluetooth.characteristic.pressure
#define BT_CHARID_ProtocolMode										0x2a4e	// org.bluetooth.characteristic.protocol_mode
#define BT_CHARID_PulseOximetryControlPoint							0x2a62	// org.bluetooth.characteristic.pulse_oximetry_control_point
#define BT_CHARID_Rainfall											0x2a78	// org.bluetooth.characteristic.rainfall
#define BT_CHARID_RCFeature											0x2b1d	// org.bluetooth.characteristic.rc_feature
#define BT_CHARID_RCSettings										0x2b1e	// org.bluetooth.characteristic.rc_settings
#define BT_CHARID_ReconnectionConfigurationControlPoint				0x2b1f	// org.bluetooth.characteristic.reconnection_configuration_control_point
#define BT_CHARID_RecordAccessControlPoint							0x2a52	// org.bluetooth.characteristic.record_access_control_point
#define BT_CHARID_ReferenceTimeInformation							0x2a14	// org.bluetooth.characteristic.reference_time_information
#define BT_CHARID_RegisteredUserCharacteristic						0x2b37	// GATT Characteristic UUID
#define BT_CHARID_Removable											0x2a3a	// org.bluetooth.characteristic.removable
#define BT_CHARID_Report											0x2a4d	// org.bluetooth.characteristic.report
#define BT_CHARID_ReportMap											0x2a4b	// org.bluetooth.characteristic.report_map
#define BT_CHARID_ResolvablePrivateAddressOnly						0x2ac9	// org.bluetooth.characteristic.resolvable_private_address_only
#define BT_CHARID_RestingHeartRate									0x2a92	// org.bluetooth.characteristic.resting_heart_rate
#define BT_CHARID_RingerControlpoint								0x2a40	// org.bluetooth.characteristic.ringer_control_point
#define BT_CHARID_RingerSetting										0x2a41	// org.bluetooth.characteristic.ringer_setting
#define BT_CHARID_RowerData											0x2ad1	// org.bluetooth.characteristic.rower_data
#define BT_CHARID_RSCFeature										0x2a54	// org.bluetooth.characteristic.rsc_feature
#define BT_CHARID_RSCMeasurement									0x2a53	// org.bluetooth.characteristic.rsc_measurement
#define BT_CHARID_SCControlPoint									0x2a55	// org.bluetooth.characteristic.sc_control_point
#define BT_CHARID_ScanIntervalWindow								0x2a4f	// org.bluetooth.characteristic.scan_interval_window
#define BT_CHARID_ScanRefresh										0x2a31	// org.bluetooth.characteristic.scan_refresh
#define BT_CHARID_ScientificTemperatureCelsius						0x2a3c	// org.bluetooth.characteristic.scientific_temperature_celsius
#define BT_CHARID_SecondaryTimeZone									0x2a10	// org.bluetooth.characteristic.secondary_time_zone
#define BT_CHARID_SensorLocation									0x2a5d	// org.bluetooth.characteristic.sensor_location
#define BT_CHARID_SerialNumberString								0x2a25	// org.bluetooth.characteristic.serial_number_string
#define BT_CHARID_ServerSupportedFeatures							0x2b3a	// GATT Characteristic UUID
#define BT_CHARID_ServiceRequired									0x2a3b	// org.bluetooth.characteristic.service_required
#define BT_CHARID_SoftwareRevisionString							0x2a28	// org.bluetooth.characteristic.software_revision_string
#define BT_CHARID_SportTypeforAerobicandAnaerobicThresholds			0x2a93	// org.bluetooth.characteristic.sport_type_for_aerobic_and_anaerobic_thresholds
#define BT_CHARID_StairClimberData									0x2ad0	// org.bluetooth.characteristic.stair_climber_data
#define BT_CHARID_StepClimberData									0x2acf	// org.bluetooth.characteristic.step_climber_data
#define BT_CHARID_String											0x2a3d	// org.bluetooth.characteristic.string
#define BT_CHARID_SupportedHeartRateRange							0x2ad7	// org.bluetooth.characteristic.supported_heart_rate_range
#define BT_CHARID_SupportedInclinationRange							0x2ad5	// org.bluetooth.characteristic.supported_inclination_range
#define BT_CHARID_SupportedNewAlertCategory							0x2a47	// org.bluetooth.characteristic.supported_new_alert_category
#define BT_CHARID_SupportedPowerRange								0x2ad8	// org.bluetooth.characteristic.supported_power_range
#define BT_CHARID_SupportedResistanceLevelRange						0x2ad6	// org.bluetooth.characteristic.supported_resistance_level_range
#define BT_CHARID_SupportedSpeedRange								0x2ad4	// org.bluetooth.characteristic.supported_speed_range
#define BT_CHARID_SupportedUnreadAlertCategory						0x2a48	// org.bluetooth.characteristic.supported_unread_alert_category
#define BT_CHARID_SystemID											0x2a23	// org.bluetooth.characteristic.system_id
#define BT_CHARID_TDSControlPoint									0x2abc	// org.bluetooth.characteristic.tds_control_point
#define BT_CHARID_Temperature										0x2a6e	// org.bluetooth.characteristic.temperature
#define BT_CHARID_TemperatureCelsius								0x2a1f	// org.bluetooth.characteristic.temperature_celsius
#define BT_CHARID_TemperatureFahrenheit								0x2a20	// org.bluetooth.characteristic.temperature_fahrenheit
#define BT_CHARID_TemperatureMeasurement							0x2a1c	// org.bluetooth.characteristic.temperature_measurement
#define BT_CHARID_TemperatureType									0x2a1d	// org.bluetooth.characteristic.temperature_type
#define BT_CHARID_ThreeZoneHeartRateLimits							0x2a94	// org.bluetooth.characteristic.three_zone_heart_rate_limits
#define BT_CHARID_TimeAccuracy										0x2a12	// org.bluetooth.characteristic.time_accuracy
#define BT_CHARID_TimeBroadcast										0x2a15	// org.bluetooth.characteristic.time_broadcast
#define BT_CHARID_TimeSource										0x2a13	// org.bluetooth.characteristic.time_source
#define BT_CHARID_TimeUpdateControlPoint							0x2a16	// org.bluetooth.characteristic.time_update_control_point
#define BT_CHARID_TimeUpdateState									0x2a17	// org.bluetooth.characteristic.time_update_state
#define BT_CHARID_TimewithDST										0x2a11	// org.bluetooth.characteristic.time_with_dst
#define BT_CHARID_TimeZone											0x2a0e	// org.bluetooth.characteristic.time_zone
#define BT_CHARID_TrainingStatus									0x2ad3	// org.bluetooth.characteristic.training_status
#define BT_CHARID_TreadmillData										0x2acd	// org.bluetooth.characteristic.treadmill_data
#define BT_CHARID_TrueWindDirection									0x2a71	// org.bluetooth.characteristic.true_wind_direction
#define BT_CHARID_TrueWindSpeed										0x2a70	// org.bluetooth.characteristic.true_wind_speed
#define BT_CHARID_TwoZoneHeartRateLimit								0x2a95	// org.bluetooth.characteristic.two_zone_heart_rate_limit
#define BT_CHARID_TxPowerLevel										0x2a07	// org.bluetooth.characteristic.tx_power_level
#define BT_CHARID_Uncertainty										0x2ab4	// org.bluetooth.characteristic.uncertainty
#define BT_CHARID_UnreadAlertStatus									0x2a45	// org.bluetooth.characteristic.unread_alert_status
#define BT_CHARID_URI												0x2ab6	// org.bluetooth.characteristic.uri
#define BT_CHARID_UserControlPoint									0x2a9f	// org.bluetooth.characteristic.user_control_point
#define BT_CHARID_UserIndex											0x2a9a	// org.bluetooth.characteristic.user_index
#define BT_CHARID_UVIndex											0x2a76	// org.bluetooth.characteristic.uv_index
#define BT_CHARID_VO2Max											0x2a96	// org.bluetooth.characteristic.vo2_max
#define BT_CHARID_WaistCircumference								0x2a97	// org.bluetooth.characteristic.waist_circumference
#define BT_CHARID_Weight											0x2a98	// org.bluetooth.characteristic.weight
#define BT_CHARID_WeightMeasurement									0x2a9d	// org.bluetooth.characteristic.weight_measurement
#define BT_CHARID_WeightScaleFeature								0x2a9e	// org.bluetooth.characteristic.weight_scale_feature
#define BT_CHARID_WindChill											0x2a79	// org.bluetooth.characteristic.wind_chill

#endif
