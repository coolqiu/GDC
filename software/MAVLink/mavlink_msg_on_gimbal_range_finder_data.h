// MESSAGE ON_GIMBAL_RANGE_FINDER_DATA PACKING

#define MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA 185

typedef struct __mavlink_on_gimbal_range_finder_data_t
{
 uint64_t time_usec; /*< Timestamp (microseconds since UNIX epoch)*/
 uint16_t distance_1; /*<  First distance in 0.5m  */
 uint16_t distance_2; /*<  Third distance in 0.5m  */
 uint16_t min_distance; /*< Range window minimum distance*/
 uint16_t max_distance; /*< Range window maximum distance*/
 uint8_t status; /*<  Status byte correspond enum RANGEFINDER_STATUS enum*/
} mavlink_on_gimbal_range_finder_data_t;

#define MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN 17
#define MAVLINK_MSG_ID_185_LEN 17

#define MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC 66
#define MAVLINK_MSG_ID_185_CRC 66



#define MAVLINK_MESSAGE_INFO_ON_GIMBAL_RANGE_FINDER_DATA { \
	"ON_GIMBAL_RANGE_FINDER_DATA", \
	6, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_on_gimbal_range_finder_data_t, time_usec) }, \
         { "distance_1", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_on_gimbal_range_finder_data_t, distance_1) }, \
         { "distance_2", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_on_gimbal_range_finder_data_t, distance_2) }, \
         { "min_distance", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_on_gimbal_range_finder_data_t, min_distance) }, \
         { "max_distance", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_on_gimbal_range_finder_data_t, max_distance) }, \
         { "status", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_on_gimbal_range_finder_data_t, status) }, \
         } \
}


/**
 * @brief Pack a on_gimbal_range_finder_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds since UNIX epoch)
 * @param distance_1  First distance in 0.5m  
 * @param distance_2  Third distance in 0.5m  
 * @param status  Status byte correspond enum RANGEFINDER_STATUS enum
 * @param min_distance Range window minimum distance
 * @param max_distance Range window maximum distance
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, uint16_t distance_1, uint16_t distance_2, uint8_t status, uint16_t min_distance, uint16_t max_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 8, distance_1);
	_mav_put_uint16_t(buf, 10, distance_2);
	_mav_put_uint16_t(buf, 12, min_distance);
	_mav_put_uint16_t(buf, 14, max_distance);
	_mav_put_uint8_t(buf, 16, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#else
	mavlink_on_gimbal_range_finder_data_t packet;
	packet.time_usec = time_usec;
	packet.distance_1 = distance_1;
	packet.distance_2 = distance_2;
	packet.min_distance = min_distance;
	packet.max_distance = max_distance;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
}

/**
 * @brief Pack a on_gimbal_range_finder_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds since UNIX epoch)
 * @param distance_1  First distance in 0.5m  
 * @param distance_2  Third distance in 0.5m  
 * @param status  Status byte correspond enum RANGEFINDER_STATUS enum
 * @param min_distance Range window minimum distance
 * @param max_distance Range window maximum distance
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,uint16_t distance_1,uint16_t distance_2,uint8_t status,uint16_t min_distance,uint16_t max_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 8, distance_1);
	_mav_put_uint16_t(buf, 10, distance_2);
	_mav_put_uint16_t(buf, 12, min_distance);
	_mav_put_uint16_t(buf, 14, max_distance);
	_mav_put_uint8_t(buf, 16, status);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#else
	mavlink_on_gimbal_range_finder_data_t packet;
	packet.time_usec = time_usec;
	packet.distance_1 = distance_1;
	packet.distance_2 = distance_2;
	packet.min_distance = min_distance;
	packet.max_distance = max_distance;
	packet.status = status;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
}

/**
 * @brief Encode a on_gimbal_range_finder_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param on_gimbal_range_finder_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_on_gimbal_range_finder_data_t* on_gimbal_range_finder_data)
{
	return mavlink_msg_on_gimbal_range_finder_data_pack(system_id, component_id, msg, on_gimbal_range_finder_data->time_usec, on_gimbal_range_finder_data->distance_1, on_gimbal_range_finder_data->distance_2, on_gimbal_range_finder_data->status, on_gimbal_range_finder_data->min_distance, on_gimbal_range_finder_data->max_distance);
}

/**
 * @brief Encode a on_gimbal_range_finder_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param on_gimbal_range_finder_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_on_gimbal_range_finder_data_t* on_gimbal_range_finder_data)
{
	return mavlink_msg_on_gimbal_range_finder_data_pack_chan(system_id, component_id, chan, msg, on_gimbal_range_finder_data->time_usec, on_gimbal_range_finder_data->distance_1, on_gimbal_range_finder_data->distance_2, on_gimbal_range_finder_data->status, on_gimbal_range_finder_data->min_distance, on_gimbal_range_finder_data->max_distance);
}

/**
 * @brief Send a on_gimbal_range_finder_data message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds since UNIX epoch)
 * @param distance_1  First distance in 0.5m  
 * @param distance_2  Third distance in 0.5m  
 * @param status  Status byte correspond enum RANGEFINDER_STATUS enum
 * @param min_distance Range window minimum distance
 * @param max_distance Range window maximum distance
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_on_gimbal_range_finder_data_send(mavlink_channel_t chan, uint64_t time_usec, uint16_t distance_1, uint16_t distance_2, uint8_t status, uint16_t min_distance, uint16_t max_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 8, distance_1);
	_mav_put_uint16_t(buf, 10, distance_2);
	_mav_put_uint16_t(buf, 12, min_distance);
	_mav_put_uint16_t(buf, 14, max_distance);
	_mav_put_uint8_t(buf, 16, status);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, buf, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, buf, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
#else
	mavlink_on_gimbal_range_finder_data_t packet;
	packet.time_usec = time_usec;
	packet.distance_1 = distance_1;
	packet.distance_2 = distance_2;
	packet.min_distance = min_distance;
	packet.max_distance = max_distance;
	packet.status = status;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, (const char *)&packet, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, (const char *)&packet, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_on_gimbal_range_finder_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, uint16_t distance_1, uint16_t distance_2, uint8_t status, uint16_t min_distance, uint16_t max_distance)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_uint16_t(buf, 8, distance_1);
	_mav_put_uint16_t(buf, 10, distance_2);
	_mav_put_uint16_t(buf, 12, min_distance);
	_mav_put_uint16_t(buf, 14, max_distance);
	_mav_put_uint8_t(buf, 16, status);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, buf, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, buf, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
#else
	mavlink_on_gimbal_range_finder_data_t *packet = (mavlink_on_gimbal_range_finder_data_t *)msgbuf;
	packet->time_usec = time_usec;
	packet->distance_1 = distance_1;
	packet->distance_2 = distance_2;
	packet->min_distance = min_distance;
	packet->max_distance = max_distance;
	packet->status = status;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, (const char *)packet, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA, (const char *)packet, MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE ON_GIMBAL_RANGE_FINDER_DATA UNPACKING


/**
 * @brief Get field time_usec from on_gimbal_range_finder_data message
 *
 * @return Timestamp (microseconds since UNIX epoch)
 */
static inline uint64_t mavlink_msg_on_gimbal_range_finder_data_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field distance_1 from on_gimbal_range_finder_data message
 *
 * @return  First distance in 0.5m  
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_get_distance_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field distance_2 from on_gimbal_range_finder_data message
 *
 * @return  Third distance in 0.5m  
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_get_distance_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field status from on_gimbal_range_finder_data message
 *
 * @return  Status byte correspond enum RANGEFINDER_STATUS enum
 */
static inline uint8_t mavlink_msg_on_gimbal_range_finder_data_get_status(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field min_distance from on_gimbal_range_finder_data message
 *
 * @return Range window minimum distance
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_get_min_distance(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field max_distance from on_gimbal_range_finder_data message
 *
 * @return Range window maximum distance
 */
static inline uint16_t mavlink_msg_on_gimbal_range_finder_data_get_max_distance(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Decode a on_gimbal_range_finder_data message into a struct
 *
 * @param msg The message to decode
 * @param on_gimbal_range_finder_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_on_gimbal_range_finder_data_decode(const mavlink_message_t* msg, mavlink_on_gimbal_range_finder_data_t* on_gimbal_range_finder_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	on_gimbal_range_finder_data->time_usec = mavlink_msg_on_gimbal_range_finder_data_get_time_usec(msg);
	on_gimbal_range_finder_data->distance_1 = mavlink_msg_on_gimbal_range_finder_data_get_distance_1(msg);
	on_gimbal_range_finder_data->distance_2 = mavlink_msg_on_gimbal_range_finder_data_get_distance_2(msg);
	on_gimbal_range_finder_data->min_distance = mavlink_msg_on_gimbal_range_finder_data_get_min_distance(msg);
	on_gimbal_range_finder_data->max_distance = mavlink_msg_on_gimbal_range_finder_data_get_max_distance(msg);
	on_gimbal_range_finder_data->status = mavlink_msg_on_gimbal_range_finder_data_get_status(msg);
#else
	memcpy(on_gimbal_range_finder_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_ON_GIMBAL_RANGE_FINDER_DATA_LEN);
#endif
}
