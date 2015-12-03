// MESSAGE ONBOARD_ECU_DATA PACKING

#define MAVLINK_MSG_ID_ONBOARD_ECU_DATA 184

typedef struct __mavlink_onboard_ecu_data_t
{
 uint64_t time_usec; /*<  Timestamp (time boot microseconds since UNIX epoch)*/
 int16_t temp_sensor_1; /*< Temperature sensor (ext air temperature) in celsius int16_max if not present*/
 int16_t temp_sensor_2; /*< Temperature sensor (engine sensor 1) in celsius     int16_max if not present*/
 int16_t temp_sensor_3; /*< Temperature sensor (engine sensor 2) in celsius     int16_max if not present */
 uint16_t engine_rpm; /*<  Engine rotations  per minute 0xFFFF if not present*/
 uint16_t fuel_flow_meter_momentary; /*<  Momentary fuel conspusion in mililitre per hour uint16_max if not present */
 uint16_t fuel_flow_meter_average; /*<    Average fuel conspusion in mililitre per hour uint16_max if not present*/
 uint16_t generator_voltage; /*< Generator DC voltage in 0.1 Volts  uint16_max if not present*/
 uint16_t generator_current; /*< Generator DC current in 0.1 Ampers uint16_max if not present*/
 uint8_t error; /*< errors 0 - ok , not 0 - errors*/
 uint8_t fuel_sensor_1; /*< Fuel level from sensor 1 in  precents 0xFF if not present */
 uint8_t fuel_sensor_2; /*< Fuel level from sensor 2 in  precents 0xFF if not present */
} mavlink_onboard_ecu_data_t;

#define MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN 27
#define MAVLINK_MSG_ID_184_LEN 27

#define MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC 112
#define MAVLINK_MSG_ID_184_CRC 112



#define MAVLINK_MESSAGE_INFO_ONBOARD_ECU_DATA { \
	"ONBOARD_ECU_DATA", \
	12, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_onboard_ecu_data_t, time_usec) }, \
         { "temp_sensor_1", NULL, MAVLINK_TYPE_INT16_T, 0, 8, offsetof(mavlink_onboard_ecu_data_t, temp_sensor_1) }, \
         { "temp_sensor_2", NULL, MAVLINK_TYPE_INT16_T, 0, 10, offsetof(mavlink_onboard_ecu_data_t, temp_sensor_2) }, \
         { "temp_sensor_3", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_onboard_ecu_data_t, temp_sensor_3) }, \
         { "engine_rpm", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_onboard_ecu_data_t, engine_rpm) }, \
         { "fuel_flow_meter_momentary", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_onboard_ecu_data_t, fuel_flow_meter_momentary) }, \
         { "fuel_flow_meter_average", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_onboard_ecu_data_t, fuel_flow_meter_average) }, \
         { "generator_voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_onboard_ecu_data_t, generator_voltage) }, \
         { "generator_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_onboard_ecu_data_t, generator_current) }, \
         { "error", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_onboard_ecu_data_t, error) }, \
         { "fuel_sensor_1", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_onboard_ecu_data_t, fuel_sensor_1) }, \
         { "fuel_sensor_2", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_onboard_ecu_data_t, fuel_sensor_2) }, \
         } \
}


/**
 * @brief Pack a onboard_ecu_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec  Timestamp (time boot microseconds since UNIX epoch)
 * @param error errors 0 - ok , not 0 - errors
 * @param fuel_sensor_1 Fuel level from sensor 1 in  precents 0xFF if not present 
 * @param fuel_sensor_2 Fuel level from sensor 2 in  precents 0xFF if not present 
 * @param temp_sensor_1 Temperature sensor (ext air temperature) in celsius int16_max if not present
 * @param temp_sensor_2 Temperature sensor (engine sensor 1) in celsius     int16_max if not present
 * @param temp_sensor_3 Temperature sensor (engine sensor 2) in celsius     int16_max if not present 
 * @param engine_rpm  Engine rotations  per minute 0xFFFF if not present
 * @param fuel_flow_meter_momentary  Momentary fuel conspusion in mililitre per hour uint16_max if not present 
 * @param fuel_flow_meter_average    Average fuel conspusion in mililitre per hour uint16_max if not present
 * @param generator_voltage Generator DC voltage in 0.1 Volts  uint16_max if not present
 * @param generator_current Generator DC current in 0.1 Ampers uint16_max if not present
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint8_t error, uint8_t fuel_sensor_1, uint8_t fuel_sensor_2, int16_t temp_sensor_1, int16_t temp_sensor_2, int16_t temp_sensor_3, uint16_t engine_rpm, uint16_t fuel_flow_meter_momentary, uint16_t fuel_flow_meter_average, uint16_t generator_voltage, uint16_t generator_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int16_t(buf, 8, temp_sensor_1);
	_mav_put_int16_t(buf, 10, temp_sensor_2);
	_mav_put_int16_t(buf, 12, temp_sensor_3);
	_mav_put_uint16_t(buf, 14, engine_rpm);
	_mav_put_uint16_t(buf, 16, fuel_flow_meter_momentary);
	_mav_put_uint16_t(buf, 18, fuel_flow_meter_average);
	_mav_put_uint16_t(buf, 20, generator_voltage);
	_mav_put_uint16_t(buf, 22, generator_current);
	_mav_put_uint8_t(buf, 24, error);
	_mav_put_uint8_t(buf, 25, fuel_sensor_1);
	_mav_put_uint8_t(buf, 26, fuel_sensor_2);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#else
	mavlink_onboard_ecu_data_t packet;
	packet.time_usec = time_usec;
	packet.temp_sensor_1 = temp_sensor_1;
	packet.temp_sensor_2 = temp_sensor_2;
	packet.temp_sensor_3 = temp_sensor_3;
	packet.engine_rpm = engine_rpm;
	packet.fuel_flow_meter_momentary = fuel_flow_meter_momentary;
	packet.fuel_flow_meter_average = fuel_flow_meter_average;
	packet.generator_voltage = generator_voltage;
	packet.generator_current = generator_current;
	packet.error = error;
	packet.fuel_sensor_1 = fuel_sensor_1;
	packet.fuel_sensor_2 = fuel_sensor_2;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ONBOARD_ECU_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
}

/**
 * @brief Pack a onboard_ecu_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec  Timestamp (time boot microseconds since UNIX epoch)
 * @param error errors 0 - ok , not 0 - errors
 * @param fuel_sensor_1 Fuel level from sensor 1 in  precents 0xFF if not present 
 * @param fuel_sensor_2 Fuel level from sensor 2 in  precents 0xFF if not present 
 * @param temp_sensor_1 Temperature sensor (ext air temperature) in celsius int16_max if not present
 * @param temp_sensor_2 Temperature sensor (engine sensor 1) in celsius     int16_max if not present
 * @param temp_sensor_3 Temperature sensor (engine sensor 2) in celsius     int16_max if not present 
 * @param engine_rpm  Engine rotations  per minute 0xFFFF if not present
 * @param fuel_flow_meter_momentary  Momentary fuel conspusion in mililitre per hour uint16_max if not present 
 * @param fuel_flow_meter_average    Average fuel conspusion in mililitre per hour uint16_max if not present
 * @param generator_voltage Generator DC voltage in 0.1 Volts  uint16_max if not present
 * @param generator_current Generator DC current in 0.1 Ampers uint16_max if not present
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint8_t error,uint8_t fuel_sensor_1,uint8_t fuel_sensor_2,int16_t temp_sensor_1,int16_t temp_sensor_2,int16_t temp_sensor_3,uint16_t engine_rpm,uint16_t fuel_flow_meter_momentary,uint16_t fuel_flow_meter_average,uint16_t generator_voltage,uint16_t generator_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int16_t(buf, 8, temp_sensor_1);
	_mav_put_int16_t(buf, 10, temp_sensor_2);
	_mav_put_int16_t(buf, 12, temp_sensor_3);
	_mav_put_uint16_t(buf, 14, engine_rpm);
	_mav_put_uint16_t(buf, 16, fuel_flow_meter_momentary);
	_mav_put_uint16_t(buf, 18, fuel_flow_meter_average);
	_mav_put_uint16_t(buf, 20, generator_voltage);
	_mav_put_uint16_t(buf, 22, generator_current);
	_mav_put_uint8_t(buf, 24, error);
	_mav_put_uint8_t(buf, 25, fuel_sensor_1);
	_mav_put_uint8_t(buf, 26, fuel_sensor_2);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#else
	mavlink_onboard_ecu_data_t packet;
	packet.time_usec = time_usec;
	packet.temp_sensor_1 = temp_sensor_1;
	packet.temp_sensor_2 = temp_sensor_2;
	packet.temp_sensor_3 = temp_sensor_3;
	packet.engine_rpm = engine_rpm;
	packet.fuel_flow_meter_momentary = fuel_flow_meter_momentary;
	packet.fuel_flow_meter_average = fuel_flow_meter_average;
	packet.generator_voltage = generator_voltage;
	packet.generator_current = generator_current;
	packet.error = error;
	packet.fuel_sensor_1 = fuel_sensor_1;
	packet.fuel_sensor_2 = fuel_sensor_2;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ONBOARD_ECU_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
}

/**
 * @brief Encode a onboard_ecu_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param onboard_ecu_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_onboard_ecu_data_t* onboard_ecu_data)
{
	return mavlink_msg_onboard_ecu_data_pack(system_id, component_id, msg, onboard_ecu_data->time_usec, onboard_ecu_data->error, onboard_ecu_data->fuel_sensor_1, onboard_ecu_data->fuel_sensor_2, onboard_ecu_data->temp_sensor_1, onboard_ecu_data->temp_sensor_2, onboard_ecu_data->temp_sensor_3, onboard_ecu_data->engine_rpm, onboard_ecu_data->fuel_flow_meter_momentary, onboard_ecu_data->fuel_flow_meter_average, onboard_ecu_data->generator_voltage, onboard_ecu_data->generator_current);
}

/**
 * @brief Encode a onboard_ecu_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param onboard_ecu_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_onboard_ecu_data_t* onboard_ecu_data)
{
	return mavlink_msg_onboard_ecu_data_pack_chan(system_id, component_id, chan, msg, onboard_ecu_data->time_usec, onboard_ecu_data->error, onboard_ecu_data->fuel_sensor_1, onboard_ecu_data->fuel_sensor_2, onboard_ecu_data->temp_sensor_1, onboard_ecu_data->temp_sensor_2, onboard_ecu_data->temp_sensor_3, onboard_ecu_data->engine_rpm, onboard_ecu_data->fuel_flow_meter_momentary, onboard_ecu_data->fuel_flow_meter_average, onboard_ecu_data->generator_voltage, onboard_ecu_data->generator_current);
}

/**
 * @brief Send a onboard_ecu_data message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec  Timestamp (time boot microseconds since UNIX epoch)
 * @param error errors 0 - ok , not 0 - errors
 * @param fuel_sensor_1 Fuel level from sensor 1 in  precents 0xFF if not present 
 * @param fuel_sensor_2 Fuel level from sensor 2 in  precents 0xFF if not present 
 * @param temp_sensor_1 Temperature sensor (ext air temperature) in celsius int16_max if not present
 * @param temp_sensor_2 Temperature sensor (engine sensor 1) in celsius     int16_max if not present
 * @param temp_sensor_3 Temperature sensor (engine sensor 2) in celsius     int16_max if not present 
 * @param engine_rpm  Engine rotations  per minute 0xFFFF if not present
 * @param fuel_flow_meter_momentary  Momentary fuel conspusion in mililitre per hour uint16_max if not present 
 * @param fuel_flow_meter_average    Average fuel conspusion in mililitre per hour uint16_max if not present
 * @param generator_voltage Generator DC voltage in 0.1 Volts  uint16_max if not present
 * @param generator_current Generator DC current in 0.1 Ampers uint16_max if not present
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_onboard_ecu_data_send(mavlink_channel_t chan, uint64_t time_usec, uint8_t error, uint8_t fuel_sensor_1, uint8_t fuel_sensor_2, int16_t temp_sensor_1, int16_t temp_sensor_2, int16_t temp_sensor_3, uint16_t engine_rpm, uint16_t fuel_flow_meter_momentary, uint16_t fuel_flow_meter_average, uint16_t generator_voltage, uint16_t generator_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int16_t(buf, 8, temp_sensor_1);
	_mav_put_int16_t(buf, 10, temp_sensor_2);
	_mav_put_int16_t(buf, 12, temp_sensor_3);
	_mav_put_uint16_t(buf, 14, engine_rpm);
	_mav_put_uint16_t(buf, 16, fuel_flow_meter_momentary);
	_mav_put_uint16_t(buf, 18, fuel_flow_meter_average);
	_mav_put_uint16_t(buf, 20, generator_voltage);
	_mav_put_uint16_t(buf, 22, generator_current);
	_mav_put_uint8_t(buf, 24, error);
	_mav_put_uint8_t(buf, 25, fuel_sensor_1);
	_mav_put_uint8_t(buf, 26, fuel_sensor_2);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, buf, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, buf, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
#else
	mavlink_onboard_ecu_data_t packet;
	packet.time_usec = time_usec;
	packet.temp_sensor_1 = temp_sensor_1;
	packet.temp_sensor_2 = temp_sensor_2;
	packet.temp_sensor_3 = temp_sensor_3;
	packet.engine_rpm = engine_rpm;
	packet.fuel_flow_meter_momentary = fuel_flow_meter_momentary;
	packet.fuel_flow_meter_average = fuel_flow_meter_average;
	packet.generator_voltage = generator_voltage;
	packet.generator_current = generator_current;
	packet.error = error;
	packet.fuel_sensor_1 = fuel_sensor_1;
	packet.fuel_sensor_2 = fuel_sensor_2;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, (const char *)&packet, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, (const char *)&packet, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_onboard_ecu_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint8_t error, uint8_t fuel_sensor_1, uint8_t fuel_sensor_2, int16_t temp_sensor_1, int16_t temp_sensor_2, int16_t temp_sensor_3, uint16_t engine_rpm, uint16_t fuel_flow_meter_momentary, uint16_t fuel_flow_meter_average, uint16_t generator_voltage, uint16_t generator_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int16_t(buf, 8, temp_sensor_1);
	_mav_put_int16_t(buf, 10, temp_sensor_2);
	_mav_put_int16_t(buf, 12, temp_sensor_3);
	_mav_put_uint16_t(buf, 14, engine_rpm);
	_mav_put_uint16_t(buf, 16, fuel_flow_meter_momentary);
	_mav_put_uint16_t(buf, 18, fuel_flow_meter_average);
	_mav_put_uint16_t(buf, 20, generator_voltage);
	_mav_put_uint16_t(buf, 22, generator_current);
	_mav_put_uint8_t(buf, 24, error);
	_mav_put_uint8_t(buf, 25, fuel_sensor_1);
	_mav_put_uint8_t(buf, 26, fuel_sensor_2);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, buf, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, buf, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
#else
	mavlink_onboard_ecu_data_t *packet = (mavlink_onboard_ecu_data_t *)msgbuf;
	packet->time_usec = time_usec;
	packet->temp_sensor_1 = temp_sensor_1;
	packet->temp_sensor_2 = temp_sensor_2;
	packet->temp_sensor_3 = temp_sensor_3;
	packet->engine_rpm = engine_rpm;
	packet->fuel_flow_meter_momentary = fuel_flow_meter_momentary;
	packet->fuel_flow_meter_average = fuel_flow_meter_average;
	packet->generator_voltage = generator_voltage;
	packet->generator_current = generator_current;
	packet->error = error;
	packet->fuel_sensor_1 = fuel_sensor_1;
	packet->fuel_sensor_2 = fuel_sensor_2;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, (const char *)packet, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ONBOARD_ECU_DATA, (const char *)packet, MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ONBOARD_ECU_DATA UNPACKING


/**
 * @brief Get field time_usec from onboard_ecu_data message
 *
 * @return  Timestamp (time boot microseconds since UNIX epoch)
 */
static inline uint64_t mavlink_msg_onboard_ecu_data_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field error from onboard_ecu_data message
 *
 * @return errors 0 - ok , not 0 - errors
 */
static inline uint8_t mavlink_msg_onboard_ecu_data_get_error(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field fuel_sensor_1 from onboard_ecu_data message
 *
 * @return Fuel level from sensor 1 in  precents 0xFF if not present 
 */
static inline uint8_t mavlink_msg_onboard_ecu_data_get_fuel_sensor_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field fuel_sensor_2 from onboard_ecu_data message
 *
 * @return Fuel level from sensor 2 in  precents 0xFF if not present 
 */
static inline uint8_t mavlink_msg_onboard_ecu_data_get_fuel_sensor_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  26);
}

/**
 * @brief Get field temp_sensor_1 from onboard_ecu_data message
 *
 * @return Temperature sensor (ext air temperature) in celsius int16_max if not present
 */
static inline int16_t mavlink_msg_onboard_ecu_data_get_temp_sensor_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  8);
}

/**
 * @brief Get field temp_sensor_2 from onboard_ecu_data message
 *
 * @return Temperature sensor (engine sensor 1) in celsius     int16_max if not present
 */
static inline int16_t mavlink_msg_onboard_ecu_data_get_temp_sensor_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  10);
}

/**
 * @brief Get field temp_sensor_3 from onboard_ecu_data message
 *
 * @return Temperature sensor (engine sensor 2) in celsius     int16_max if not present 
 */
static inline int16_t mavlink_msg_onboard_ecu_data_get_temp_sensor_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int16_t(msg,  12);
}

/**
 * @brief Get field engine_rpm from onboard_ecu_data message
 *
 * @return  Engine rotations  per minute 0xFFFF if not present
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_get_engine_rpm(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field fuel_flow_meter_momentary from onboard_ecu_data message
 *
 * @return  Momentary fuel conspusion in mililitre per hour uint16_max if not present 
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_get_fuel_flow_meter_momentary(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field fuel_flow_meter_average from onboard_ecu_data message
 *
 * @return    Average fuel conspusion in mililitre per hour uint16_max if not present
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_get_fuel_flow_meter_average(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field generator_voltage from onboard_ecu_data message
 *
 * @return Generator DC voltage in 0.1 Volts  uint16_max if not present
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_get_generator_voltage(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field generator_current from onboard_ecu_data message
 *
 * @return Generator DC current in 0.1 Ampers uint16_max if not present
 */
static inline uint16_t mavlink_msg_onboard_ecu_data_get_generator_current(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  22);
}

/**
 * @brief Decode a onboard_ecu_data message into a struct
 *
 * @param msg The message to decode
 * @param onboard_ecu_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_onboard_ecu_data_decode(const mavlink_message_t* msg, mavlink_onboard_ecu_data_t* onboard_ecu_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	onboard_ecu_data->time_usec = mavlink_msg_onboard_ecu_data_get_time_usec(msg);
	onboard_ecu_data->temp_sensor_1 = mavlink_msg_onboard_ecu_data_get_temp_sensor_1(msg);
	onboard_ecu_data->temp_sensor_2 = mavlink_msg_onboard_ecu_data_get_temp_sensor_2(msg);
	onboard_ecu_data->temp_sensor_3 = mavlink_msg_onboard_ecu_data_get_temp_sensor_3(msg);
	onboard_ecu_data->engine_rpm = mavlink_msg_onboard_ecu_data_get_engine_rpm(msg);
	onboard_ecu_data->fuel_flow_meter_momentary = mavlink_msg_onboard_ecu_data_get_fuel_flow_meter_momentary(msg);
	onboard_ecu_data->fuel_flow_meter_average = mavlink_msg_onboard_ecu_data_get_fuel_flow_meter_average(msg);
	onboard_ecu_data->generator_voltage = mavlink_msg_onboard_ecu_data_get_generator_voltage(msg);
	onboard_ecu_data->generator_current = mavlink_msg_onboard_ecu_data_get_generator_current(msg);
	onboard_ecu_data->error = mavlink_msg_onboard_ecu_data_get_error(msg);
	onboard_ecu_data->fuel_sensor_1 = mavlink_msg_onboard_ecu_data_get_fuel_sensor_1(msg);
	onboard_ecu_data->fuel_sensor_2 = mavlink_msg_onboard_ecu_data_get_fuel_sensor_2(msg);
#else
	memcpy(onboard_ecu_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ONBOARD_ECU_DATA_LEN);
#endif
}
