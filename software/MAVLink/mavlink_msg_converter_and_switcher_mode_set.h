// MESSAGE CONVERTER_AND_SWITCHER_MODE_SET PACKING

#define MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET 187

typedef struct __mavlink_converter_and_switcher_mode_set_t
{
 uint8_t mode; /*<  Conversion mode defined in CVBS_TO_SDI_CONVERTER_MODES enum or switcher mode*/
 uint8_t data_1; /*<  Video switcher or converter data */
 uint8_t data_2; /*<  Video switcher or converter data */
 uint8_t data_3; /*<  Video switcher or converter data */
} mavlink_converter_and_switcher_mode_set_t;

#define MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN 4
#define MAVLINK_MSG_ID_187_LEN 4

#define MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC 88
#define MAVLINK_MSG_ID_187_CRC 88



#define MAVLINK_MESSAGE_INFO_CONVERTER_AND_SWITCHER_MODE_SET { \
	"CONVERTER_AND_SWITCHER_MODE_SET", \
	4, \
	{  { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_converter_and_switcher_mode_set_t, mode) }, \
         { "data_1", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_converter_and_switcher_mode_set_t, data_1) }, \
         { "data_2", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_converter_and_switcher_mode_set_t, data_2) }, \
         { "data_3", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_converter_and_switcher_mode_set_t, data_3) }, \
         } \
}


/**
 * @brief Pack a converter_and_switcher_mode_set message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode  Conversion mode defined in CVBS_TO_SDI_CONVERTER_MODES enum or switcher mode
 * @param data_1  Video switcher or converter data 
 * @param data_2  Video switcher or converter data 
 * @param data_3  Video switcher or converter data 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_converter_and_switcher_mode_set_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t mode, uint8_t data_1, uint8_t data_2, uint8_t data_3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN];
	_mav_put_uint8_t(buf, 0, mode);
	_mav_put_uint8_t(buf, 1, data_1);
	_mav_put_uint8_t(buf, 2, data_2);
	_mav_put_uint8_t(buf, 3, data_3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#else
	mavlink_converter_and_switcher_mode_set_t packet;
	packet.mode = mode;
	packet.data_1 = data_1;
	packet.data_2 = data_2;
	packet.data_3 = data_3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
}

/**
 * @brief Pack a converter_and_switcher_mode_set message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode  Conversion mode defined in CVBS_TO_SDI_CONVERTER_MODES enum or switcher mode
 * @param data_1  Video switcher or converter data 
 * @param data_2  Video switcher or converter data 
 * @param data_3  Video switcher or converter data 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_converter_and_switcher_mode_set_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t mode,uint8_t data_1,uint8_t data_2,uint8_t data_3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN];
	_mav_put_uint8_t(buf, 0, mode);
	_mav_put_uint8_t(buf, 1, data_1);
	_mav_put_uint8_t(buf, 2, data_2);
	_mav_put_uint8_t(buf, 3, data_3);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#else
	mavlink_converter_and_switcher_mode_set_t packet;
	packet.mode = mode;
	packet.data_1 = data_1;
	packet.data_2 = data_2;
	packet.data_3 = data_3;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
}

/**
 * @brief Encode a converter_and_switcher_mode_set struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param converter_and_switcher_mode_set C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_converter_and_switcher_mode_set_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_converter_and_switcher_mode_set_t* converter_and_switcher_mode_set)
{
	return mavlink_msg_converter_and_switcher_mode_set_pack(system_id, component_id, msg, converter_and_switcher_mode_set->mode, converter_and_switcher_mode_set->data_1, converter_and_switcher_mode_set->data_2, converter_and_switcher_mode_set->data_3);
}

/**
 * @brief Encode a converter_and_switcher_mode_set struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param converter_and_switcher_mode_set C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_converter_and_switcher_mode_set_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_converter_and_switcher_mode_set_t* converter_and_switcher_mode_set)
{
	return mavlink_msg_converter_and_switcher_mode_set_pack_chan(system_id, component_id, chan, msg, converter_and_switcher_mode_set->mode, converter_and_switcher_mode_set->data_1, converter_and_switcher_mode_set->data_2, converter_and_switcher_mode_set->data_3);
}

/**
 * @brief Send a converter_and_switcher_mode_set message
 * @param chan MAVLink channel to send the message
 *
 * @param mode  Conversion mode defined in CVBS_TO_SDI_CONVERTER_MODES enum or switcher mode
 * @param data_1  Video switcher or converter data 
 * @param data_2  Video switcher or converter data 
 * @param data_3  Video switcher or converter data 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_converter_and_switcher_mode_set_send(mavlink_channel_t chan, uint8_t mode, uint8_t data_1, uint8_t data_2, uint8_t data_3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN];
	_mav_put_uint8_t(buf, 0, mode);
	_mav_put_uint8_t(buf, 1, data_1);
	_mav_put_uint8_t(buf, 2, data_2);
	_mav_put_uint8_t(buf, 3, data_3);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, buf, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, buf, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
#else
	mavlink_converter_and_switcher_mode_set_t packet;
	packet.mode = mode;
	packet.data_1 = data_1;
	packet.data_2 = data_2;
	packet.data_3 = data_3;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, (const char *)&packet, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, (const char *)&packet, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_converter_and_switcher_mode_set_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t mode, uint8_t data_1, uint8_t data_2, uint8_t data_3)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, mode);
	_mav_put_uint8_t(buf, 1, data_1);
	_mav_put_uint8_t(buf, 2, data_2);
	_mav_put_uint8_t(buf, 3, data_3);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, buf, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, buf, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
#else
	mavlink_converter_and_switcher_mode_set_t *packet = (mavlink_converter_and_switcher_mode_set_t *)msgbuf;
	packet->mode = mode;
	packet->data_1 = data_1;
	packet->data_2 = data_2;
	packet->data_3 = data_3;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, (const char *)packet, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET, (const char *)packet, MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE CONVERTER_AND_SWITCHER_MODE_SET UNPACKING


/**
 * @brief Get field mode from converter_and_switcher_mode_set message
 *
 * @return  Conversion mode defined in CVBS_TO_SDI_CONVERTER_MODES enum or switcher mode
 */
static inline uint8_t mavlink_msg_converter_and_switcher_mode_set_get_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field data_1 from converter_and_switcher_mode_set message
 *
 * @return  Video switcher or converter data 
 */
static inline uint8_t mavlink_msg_converter_and_switcher_mode_set_get_data_1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field data_2 from converter_and_switcher_mode_set message
 *
 * @return  Video switcher or converter data 
 */
static inline uint8_t mavlink_msg_converter_and_switcher_mode_set_get_data_2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field data_3 from converter_and_switcher_mode_set message
 *
 * @return  Video switcher or converter data 
 */
static inline uint8_t mavlink_msg_converter_and_switcher_mode_set_get_data_3(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Decode a converter_and_switcher_mode_set message into a struct
 *
 * @param msg The message to decode
 * @param converter_and_switcher_mode_set C-struct to decode the message contents into
 */
static inline void mavlink_msg_converter_and_switcher_mode_set_decode(const mavlink_message_t* msg, mavlink_converter_and_switcher_mode_set_t* converter_and_switcher_mode_set)
{
#if MAVLINK_NEED_BYTE_SWAP
	converter_and_switcher_mode_set->mode = mavlink_msg_converter_and_switcher_mode_set_get_mode(msg);
	converter_and_switcher_mode_set->data_1 = mavlink_msg_converter_and_switcher_mode_set_get_data_1(msg);
	converter_and_switcher_mode_set->data_2 = mavlink_msg_converter_and_switcher_mode_set_get_data_2(msg);
	converter_and_switcher_mode_set->data_3 = mavlink_msg_converter_and_switcher_mode_set_get_data_3(msg);
#else
	memcpy(converter_and_switcher_mode_set, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_CONVERTER_AND_SWITCHER_MODE_SET_LEN);
#endif
}
