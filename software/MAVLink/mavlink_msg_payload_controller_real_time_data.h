// MESSAGE PAYLOAD_CONTROLLER_REAL_TIME_DATA PACKING

#define MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA 188

typedef struct __mavlink_payload_controller_real_time_data_t
{
 uint64_t time_usec; /*< Timestamp (microseconds since UNIX epoch)*/
 int32_t UAV_lat; /*< Latitude, expressed as * 1E7*/
 int32_t UAV_lon; /*< Longitude, expressed as * 1E7*/
 int32_t UAV_alt; /*< Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)*/
 int32_t UAV_relative_alt; /*< Altitude above ground in meters, expressed as * 1000 (millimeters)*/
 int32_t target_lat; /*< Latitude in (deg * 1E7)*/
 int32_t target_lng; /*< Longitude in (deg * 1E7)*/
 float target_alt_msl; /*< Altitude Absolute (meters AMSL)*/
 float target_alt_rel; /*< Altitude Relative (meters above HOME location)*/
 float roll; /*< Camera Roll angle (earth frame, degrees, +-180)*/
 float pitch; /*< Camera Pitch angle (earth frame, degrees, +-180)*/
 float yaw; /*< Camera Yaw (earth frame, degrees, 0-360, true)*/
 float horiz_view_angle; /*< Horizontal angle of view for current camera in degrees*/
 float vert_view_angle; /*< Vertical angle of view for current camera in degrees*/
 uint16_t UAV_hdg; /*< Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX*/
 uint16_t flags; /*< See CAMERA_FEEDBACK_FLAGS enum for definition of the bitmask*/
 uint8_t current_cam_idx; /*<  Current active camera ID*/
 uint8_t camera_model[24]; /*< Human readable field of current camera model*/
} mavlink_payload_controller_real_time_data_t;

#define MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN 89
#define MAVLINK_MSG_ID_188_LEN 89

#define MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC 245
#define MAVLINK_MSG_ID_188_CRC 245

#define MAVLINK_MSG_PAYLOAD_CONTROLLER_REAL_TIME_DATA_FIELD_CAMERA_MODEL_LEN 24

#define MAVLINK_MESSAGE_INFO_PAYLOAD_CONTROLLER_REAL_TIME_DATA { \
	"PAYLOAD_CONTROLLER_REAL_TIME_DATA", \
	18, \
	{  { "time_usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_payload_controller_real_time_data_t, time_usec) }, \
         { "UAV_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 8, offsetof(mavlink_payload_controller_real_time_data_t, UAV_lat) }, \
         { "UAV_lon", NULL, MAVLINK_TYPE_INT32_T, 0, 12, offsetof(mavlink_payload_controller_real_time_data_t, UAV_lon) }, \
         { "UAV_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_payload_controller_real_time_data_t, UAV_alt) }, \
         { "UAV_relative_alt", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_payload_controller_real_time_data_t, UAV_relative_alt) }, \
         { "target_lat", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_payload_controller_real_time_data_t, target_lat) }, \
         { "target_lng", NULL, MAVLINK_TYPE_INT32_T, 0, 28, offsetof(mavlink_payload_controller_real_time_data_t, target_lng) }, \
         { "target_alt_msl", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_payload_controller_real_time_data_t, target_alt_msl) }, \
         { "target_alt_rel", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_payload_controller_real_time_data_t, target_alt_rel) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_payload_controller_real_time_data_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_payload_controller_real_time_data_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_payload_controller_real_time_data_t, yaw) }, \
         { "horiz_view_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_payload_controller_real_time_data_t, horiz_view_angle) }, \
         { "vert_view_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_payload_controller_real_time_data_t, vert_view_angle) }, \
         { "UAV_hdg", NULL, MAVLINK_TYPE_UINT16_T, 0, 60, offsetof(mavlink_payload_controller_real_time_data_t, UAV_hdg) }, \
         { "flags", NULL, MAVLINK_TYPE_UINT16_T, 0, 62, offsetof(mavlink_payload_controller_real_time_data_t, flags) }, \
         { "current_cam_idx", NULL, MAVLINK_TYPE_UINT8_T, 0, 64, offsetof(mavlink_payload_controller_real_time_data_t, current_cam_idx) }, \
         { "camera_model", NULL, MAVLINK_TYPE_UINT8_T, 24, 65, offsetof(mavlink_payload_controller_real_time_data_t, camera_model) }, \
         } \
}


/**
 * @brief Pack a payload_controller_real_time_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time_usec Timestamp (microseconds since UNIX epoch)
 * @param UAV_lat Latitude, expressed as * 1E7
 * @param UAV_lon Longitude, expressed as * 1E7
 * @param UAV_alt Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param UAV_relative_alt Altitude above ground in meters, expressed as * 1000 (millimeters)
 * @param UAV_hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @param current_cam_idx  Current active camera ID
 * @param target_lat Latitude in (deg * 1E7)
 * @param target_lng Longitude in (deg * 1E7)
 * @param target_alt_msl Altitude Absolute (meters AMSL)
 * @param target_alt_rel Altitude Relative (meters above HOME location)
 * @param roll Camera Roll angle (earth frame, degrees, +-180)
 * @param pitch Camera Pitch angle (earth frame, degrees, +-180)
 * @param yaw Camera Yaw (earth frame, degrees, 0-360, true)
 * @param horiz_view_angle Horizontal angle of view for current camera in degrees
 * @param vert_view_angle Vertical angle of view for current camera in degrees
 * @param camera_model Human readable field of current camera model
 * @param flags See CAMERA_FEEDBACK_FLAGS enum for definition of the bitmask
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint64_t time_usec, int32_t UAV_lat, int32_t UAV_lon, int32_t UAV_alt, int32_t UAV_relative_alt, uint16_t UAV_hdg, uint8_t current_cam_idx, int32_t target_lat, int32_t target_lng, float target_alt_msl, float target_alt_rel, float roll, float pitch, float yaw, float horiz_view_angle, float vert_view_angle, const uint8_t *camera_model, uint16_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int32_t(buf, 8, UAV_lat);
	_mav_put_int32_t(buf, 12, UAV_lon);
	_mav_put_int32_t(buf, 16, UAV_alt);
	_mav_put_int32_t(buf, 20, UAV_relative_alt);
	_mav_put_int32_t(buf, 24, target_lat);
	_mav_put_int32_t(buf, 28, target_lng);
	_mav_put_float(buf, 32, target_alt_msl);
	_mav_put_float(buf, 36, target_alt_rel);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, horiz_view_angle);
	_mav_put_float(buf, 56, vert_view_angle);
	_mav_put_uint16_t(buf, 60, UAV_hdg);
	_mav_put_uint16_t(buf, 62, flags);
	_mav_put_uint8_t(buf, 64, current_cam_idx);
	_mav_put_uint8_t_array(buf, 65, camera_model, 24);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#else
	mavlink_payload_controller_real_time_data_t packet;
	packet.time_usec = time_usec;
	packet.UAV_lat = UAV_lat;
	packet.UAV_lon = UAV_lon;
	packet.UAV_alt = UAV_alt;
	packet.UAV_relative_alt = UAV_relative_alt;
	packet.target_lat = target_lat;
	packet.target_lng = target_lng;
	packet.target_alt_msl = target_alt_msl;
	packet.target_alt_rel = target_alt_rel;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.horiz_view_angle = horiz_view_angle;
	packet.vert_view_angle = vert_view_angle;
	packet.UAV_hdg = UAV_hdg;
	packet.flags = flags;
	packet.current_cam_idx = current_cam_idx;
	mav_array_memcpy(packet.camera_model, camera_model, sizeof(uint8_t)*24);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
}

/**
 * @brief Pack a payload_controller_real_time_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time_usec Timestamp (microseconds since UNIX epoch)
 * @param UAV_lat Latitude, expressed as * 1E7
 * @param UAV_lon Longitude, expressed as * 1E7
 * @param UAV_alt Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param UAV_relative_alt Altitude above ground in meters, expressed as * 1000 (millimeters)
 * @param UAV_hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @param current_cam_idx  Current active camera ID
 * @param target_lat Latitude in (deg * 1E7)
 * @param target_lng Longitude in (deg * 1E7)
 * @param target_alt_msl Altitude Absolute (meters AMSL)
 * @param target_alt_rel Altitude Relative (meters above HOME location)
 * @param roll Camera Roll angle (earth frame, degrees, +-180)
 * @param pitch Camera Pitch angle (earth frame, degrees, +-180)
 * @param yaw Camera Yaw (earth frame, degrees, 0-360, true)
 * @param horiz_view_angle Horizontal angle of view for current camera in degrees
 * @param vert_view_angle Vertical angle of view for current camera in degrees
 * @param camera_model Human readable field of current camera model
 * @param flags See CAMERA_FEEDBACK_FLAGS enum for definition of the bitmask
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint64_t time_usec,int32_t UAV_lat,int32_t UAV_lon,int32_t UAV_alt,int32_t UAV_relative_alt,uint16_t UAV_hdg,uint8_t current_cam_idx,int32_t target_lat,int32_t target_lng,float target_alt_msl,float target_alt_rel,float roll,float pitch,float yaw,float horiz_view_angle,float vert_view_angle,const uint8_t *camera_model,uint16_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int32_t(buf, 8, UAV_lat);
	_mav_put_int32_t(buf, 12, UAV_lon);
	_mav_put_int32_t(buf, 16, UAV_alt);
	_mav_put_int32_t(buf, 20, UAV_relative_alt);
	_mav_put_int32_t(buf, 24, target_lat);
	_mav_put_int32_t(buf, 28, target_lng);
	_mav_put_float(buf, 32, target_alt_msl);
	_mav_put_float(buf, 36, target_alt_rel);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, horiz_view_angle);
	_mav_put_float(buf, 56, vert_view_angle);
	_mav_put_uint16_t(buf, 60, UAV_hdg);
	_mav_put_uint16_t(buf, 62, flags);
	_mav_put_uint8_t(buf, 64, current_cam_idx);
	_mav_put_uint8_t_array(buf, 65, camera_model, 24);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#else
	mavlink_payload_controller_real_time_data_t packet;
	packet.time_usec = time_usec;
	packet.UAV_lat = UAV_lat;
	packet.UAV_lon = UAV_lon;
	packet.UAV_alt = UAV_alt;
	packet.UAV_relative_alt = UAV_relative_alt;
	packet.target_lat = target_lat;
	packet.target_lng = target_lng;
	packet.target_alt_msl = target_alt_msl;
	packet.target_alt_rel = target_alt_rel;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.horiz_view_angle = horiz_view_angle;
	packet.vert_view_angle = vert_view_angle;
	packet.UAV_hdg = UAV_hdg;
	packet.flags = flags;
	packet.current_cam_idx = current_cam_idx;
	mav_array_memcpy(packet.camera_model, camera_model, sizeof(uint8_t)*24);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
}

/**
 * @brief Encode a payload_controller_real_time_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param payload_controller_real_time_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_payload_controller_real_time_data_t* payload_controller_real_time_data)
{
	return mavlink_msg_payload_controller_real_time_data_pack(system_id, component_id, msg, payload_controller_real_time_data->time_usec, payload_controller_real_time_data->UAV_lat, payload_controller_real_time_data->UAV_lon, payload_controller_real_time_data->UAV_alt, payload_controller_real_time_data->UAV_relative_alt, payload_controller_real_time_data->UAV_hdg, payload_controller_real_time_data->current_cam_idx, payload_controller_real_time_data->target_lat, payload_controller_real_time_data->target_lng, payload_controller_real_time_data->target_alt_msl, payload_controller_real_time_data->target_alt_rel, payload_controller_real_time_data->roll, payload_controller_real_time_data->pitch, payload_controller_real_time_data->yaw, payload_controller_real_time_data->horiz_view_angle, payload_controller_real_time_data->vert_view_angle, payload_controller_real_time_data->camera_model, payload_controller_real_time_data->flags);
}

/**
 * @brief Encode a payload_controller_real_time_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param payload_controller_real_time_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_payload_controller_real_time_data_t* payload_controller_real_time_data)
{
	return mavlink_msg_payload_controller_real_time_data_pack_chan(system_id, component_id, chan, msg, payload_controller_real_time_data->time_usec, payload_controller_real_time_data->UAV_lat, payload_controller_real_time_data->UAV_lon, payload_controller_real_time_data->UAV_alt, payload_controller_real_time_data->UAV_relative_alt, payload_controller_real_time_data->UAV_hdg, payload_controller_real_time_data->current_cam_idx, payload_controller_real_time_data->target_lat, payload_controller_real_time_data->target_lng, payload_controller_real_time_data->target_alt_msl, payload_controller_real_time_data->target_alt_rel, payload_controller_real_time_data->roll, payload_controller_real_time_data->pitch, payload_controller_real_time_data->yaw, payload_controller_real_time_data->horiz_view_angle, payload_controller_real_time_data->vert_view_angle, payload_controller_real_time_data->camera_model, payload_controller_real_time_data->flags);
}

/**
 * @brief Send a payload_controller_real_time_data message
 * @param chan MAVLink channel to send the message
 *
 * @param time_usec Timestamp (microseconds since UNIX epoch)
 * @param UAV_lat Latitude, expressed as * 1E7
 * @param UAV_lon Longitude, expressed as * 1E7
 * @param UAV_alt Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 * @param UAV_relative_alt Altitude above ground in meters, expressed as * 1000 (millimeters)
 * @param UAV_hdg Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 * @param current_cam_idx  Current active camera ID
 * @param target_lat Latitude in (deg * 1E7)
 * @param target_lng Longitude in (deg * 1E7)
 * @param target_alt_msl Altitude Absolute (meters AMSL)
 * @param target_alt_rel Altitude Relative (meters above HOME location)
 * @param roll Camera Roll angle (earth frame, degrees, +-180)
 * @param pitch Camera Pitch angle (earth frame, degrees, +-180)
 * @param yaw Camera Yaw (earth frame, degrees, 0-360, true)
 * @param horiz_view_angle Horizontal angle of view for current camera in degrees
 * @param vert_view_angle Vertical angle of view for current camera in degrees
 * @param camera_model Human readable field of current camera model
 * @param flags See CAMERA_FEEDBACK_FLAGS enum for definition of the bitmask
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_payload_controller_real_time_data_send(mavlink_channel_t chan, uint64_t time_usec, int32_t UAV_lat, int32_t UAV_lon, int32_t UAV_alt, int32_t UAV_relative_alt, uint16_t UAV_hdg, uint8_t current_cam_idx, int32_t target_lat, int32_t target_lng, float target_alt_msl, float target_alt_rel, float roll, float pitch, float yaw, float horiz_view_angle, float vert_view_angle, const uint8_t *camera_model, uint16_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN];
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int32_t(buf, 8, UAV_lat);
	_mav_put_int32_t(buf, 12, UAV_lon);
	_mav_put_int32_t(buf, 16, UAV_alt);
	_mav_put_int32_t(buf, 20, UAV_relative_alt);
	_mav_put_int32_t(buf, 24, target_lat);
	_mav_put_int32_t(buf, 28, target_lng);
	_mav_put_float(buf, 32, target_alt_msl);
	_mav_put_float(buf, 36, target_alt_rel);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, horiz_view_angle);
	_mav_put_float(buf, 56, vert_view_angle);
	_mav_put_uint16_t(buf, 60, UAV_hdg);
	_mav_put_uint16_t(buf, 62, flags);
	_mav_put_uint8_t(buf, 64, current_cam_idx);
	_mav_put_uint8_t_array(buf, 65, camera_model, 24);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, buf, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, buf, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
#else
	mavlink_payload_controller_real_time_data_t packet;
	packet.time_usec = time_usec;
	packet.UAV_lat = UAV_lat;
	packet.UAV_lon = UAV_lon;
	packet.UAV_alt = UAV_alt;
	packet.UAV_relative_alt = UAV_relative_alt;
	packet.target_lat = target_lat;
	packet.target_lng = target_lng;
	packet.target_alt_msl = target_alt_msl;
	packet.target_alt_rel = target_alt_rel;
	packet.roll = roll;
	packet.pitch = pitch;
	packet.yaw = yaw;
	packet.horiz_view_angle = horiz_view_angle;
	packet.vert_view_angle = vert_view_angle;
	packet.UAV_hdg = UAV_hdg;
	packet.flags = flags;
	packet.current_cam_idx = current_cam_idx;
	mav_array_memcpy(packet.camera_model, camera_model, sizeof(uint8_t)*24);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, (const char *)&packet, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, (const char *)&packet, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_payload_controller_real_time_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t time_usec, int32_t UAV_lat, int32_t UAV_lon, int32_t UAV_alt, int32_t UAV_relative_alt, uint16_t UAV_hdg, uint8_t current_cam_idx, int32_t target_lat, int32_t target_lng, float target_alt_msl, float target_alt_rel, float roll, float pitch, float yaw, float horiz_view_angle, float vert_view_angle, const uint8_t *camera_model, uint16_t flags)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, time_usec);
	_mav_put_int32_t(buf, 8, UAV_lat);
	_mav_put_int32_t(buf, 12, UAV_lon);
	_mav_put_int32_t(buf, 16, UAV_alt);
	_mav_put_int32_t(buf, 20, UAV_relative_alt);
	_mav_put_int32_t(buf, 24, target_lat);
	_mav_put_int32_t(buf, 28, target_lng);
	_mav_put_float(buf, 32, target_alt_msl);
	_mav_put_float(buf, 36, target_alt_rel);
	_mav_put_float(buf, 40, roll);
	_mav_put_float(buf, 44, pitch);
	_mav_put_float(buf, 48, yaw);
	_mav_put_float(buf, 52, horiz_view_angle);
	_mav_put_float(buf, 56, vert_view_angle);
	_mav_put_uint16_t(buf, 60, UAV_hdg);
	_mav_put_uint16_t(buf, 62, flags);
	_mav_put_uint8_t(buf, 64, current_cam_idx);
	_mav_put_uint8_t_array(buf, 65, camera_model, 24);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, buf, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, buf, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
#else
	mavlink_payload_controller_real_time_data_t *packet = (mavlink_payload_controller_real_time_data_t *)msgbuf;
	packet->time_usec = time_usec;
	packet->UAV_lat = UAV_lat;
	packet->UAV_lon = UAV_lon;
	packet->UAV_alt = UAV_alt;
	packet->UAV_relative_alt = UAV_relative_alt;
	packet->target_lat = target_lat;
	packet->target_lng = target_lng;
	packet->target_alt_msl = target_alt_msl;
	packet->target_alt_rel = target_alt_rel;
	packet->roll = roll;
	packet->pitch = pitch;
	packet->yaw = yaw;
	packet->horiz_view_angle = horiz_view_angle;
	packet->vert_view_angle = vert_view_angle;
	packet->UAV_hdg = UAV_hdg;
	packet->flags = flags;
	packet->current_cam_idx = current_cam_idx;
	mav_array_memcpy(packet->camera_model, camera_model, sizeof(uint8_t)*24);
#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, (const char *)packet, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA, (const char *)packet, MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE PAYLOAD_CONTROLLER_REAL_TIME_DATA UNPACKING


/**
 * @brief Get field time_usec from payload_controller_real_time_data message
 *
 * @return Timestamp (microseconds since UNIX epoch)
 */
static inline uint64_t mavlink_msg_payload_controller_real_time_data_get_time_usec(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field UAV_lat from payload_controller_real_time_data message
 *
 * @return Latitude, expressed as * 1E7
 */
static inline int32_t mavlink_msg_payload_controller_real_time_data_get_UAV_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  8);
}

/**
 * @brief Get field UAV_lon from payload_controller_real_time_data message
 *
 * @return Longitude, expressed as * 1E7
 */
static inline int32_t mavlink_msg_payload_controller_real_time_data_get_UAV_lon(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  12);
}

/**
 * @brief Get field UAV_alt from payload_controller_real_time_data message
 *
 * @return Altitude in meters, expressed as * 1000 (millimeters), AMSL (not WGS84 - note that virtually all GPS modules provide the AMSL as well)
 */
static inline int32_t mavlink_msg_payload_controller_real_time_data_get_UAV_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field UAV_relative_alt from payload_controller_real_time_data message
 *
 * @return Altitude above ground in meters, expressed as * 1000 (millimeters)
 */
static inline int32_t mavlink_msg_payload_controller_real_time_data_get_UAV_relative_alt(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field UAV_hdg from payload_controller_real_time_data message
 *
 * @return Compass heading in degrees * 100, 0.0..359.99 degrees. If unknown, set to: UINT16_MAX
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_get_UAV_hdg(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  60);
}

/**
 * @brief Get field current_cam_idx from payload_controller_real_time_data message
 *
 * @return  Current active camera ID
 */
static inline uint8_t mavlink_msg_payload_controller_real_time_data_get_current_cam_idx(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  64);
}

/**
 * @brief Get field target_lat from payload_controller_real_time_data message
 *
 * @return Latitude in (deg * 1E7)
 */
static inline int32_t mavlink_msg_payload_controller_real_time_data_get_target_lat(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Get field target_lng from payload_controller_real_time_data message
 *
 * @return Longitude in (deg * 1E7)
 */
static inline int32_t mavlink_msg_payload_controller_real_time_data_get_target_lng(const mavlink_message_t* msg)
{
	return _MAV_RETURN_int32_t(msg,  28);
}

/**
 * @brief Get field target_alt_msl from payload_controller_real_time_data message
 *
 * @return Altitude Absolute (meters AMSL)
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_target_alt_msl(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field target_alt_rel from payload_controller_real_time_data message
 *
 * @return Altitude Relative (meters above HOME location)
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_target_alt_rel(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field roll from payload_controller_real_time_data message
 *
 * @return Camera Roll angle (earth frame, degrees, +-180)
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_roll(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field pitch from payload_controller_real_time_data message
 *
 * @return Camera Pitch angle (earth frame, degrees, +-180)
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_pitch(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field yaw from payload_controller_real_time_data message
 *
 * @return Camera Yaw (earth frame, degrees, 0-360, true)
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_yaw(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field horiz_view_angle from payload_controller_real_time_data message
 *
 * @return Horizontal angle of view for current camera in degrees
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_horiz_view_angle(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field vert_view_angle from payload_controller_real_time_data message
 *
 * @return Vertical angle of view for current camera in degrees
 */
static inline float mavlink_msg_payload_controller_real_time_data_get_vert_view_angle(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field camera_model from payload_controller_real_time_data message
 *
 * @return Human readable field of current camera model
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_get_camera_model(const mavlink_message_t* msg, uint8_t *camera_model)
{
	return _MAV_RETURN_uint8_t_array(msg, camera_model, 24,  65);
}

/**
 * @brief Get field flags from payload_controller_real_time_data message
 *
 * @return See CAMERA_FEEDBACK_FLAGS enum for definition of the bitmask
 */
static inline uint16_t mavlink_msg_payload_controller_real_time_data_get_flags(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  62);
}

/**
 * @brief Decode a payload_controller_real_time_data message into a struct
 *
 * @param msg The message to decode
 * @param payload_controller_real_time_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_payload_controller_real_time_data_decode(const mavlink_message_t* msg, mavlink_payload_controller_real_time_data_t* payload_controller_real_time_data)
{
#if MAVLINK_NEED_BYTE_SWAP
	payload_controller_real_time_data->time_usec = mavlink_msg_payload_controller_real_time_data_get_time_usec(msg);
	payload_controller_real_time_data->UAV_lat = mavlink_msg_payload_controller_real_time_data_get_UAV_lat(msg);
	payload_controller_real_time_data->UAV_lon = mavlink_msg_payload_controller_real_time_data_get_UAV_lon(msg);
	payload_controller_real_time_data->UAV_alt = mavlink_msg_payload_controller_real_time_data_get_UAV_alt(msg);
	payload_controller_real_time_data->UAV_relative_alt = mavlink_msg_payload_controller_real_time_data_get_UAV_relative_alt(msg);
	payload_controller_real_time_data->target_lat = mavlink_msg_payload_controller_real_time_data_get_target_lat(msg);
	payload_controller_real_time_data->target_lng = mavlink_msg_payload_controller_real_time_data_get_target_lng(msg);
	payload_controller_real_time_data->target_alt_msl = mavlink_msg_payload_controller_real_time_data_get_target_alt_msl(msg);
	payload_controller_real_time_data->target_alt_rel = mavlink_msg_payload_controller_real_time_data_get_target_alt_rel(msg);
	payload_controller_real_time_data->roll = mavlink_msg_payload_controller_real_time_data_get_roll(msg);
	payload_controller_real_time_data->pitch = mavlink_msg_payload_controller_real_time_data_get_pitch(msg);
	payload_controller_real_time_data->yaw = mavlink_msg_payload_controller_real_time_data_get_yaw(msg);
	payload_controller_real_time_data->horiz_view_angle = mavlink_msg_payload_controller_real_time_data_get_horiz_view_angle(msg);
	payload_controller_real_time_data->vert_view_angle = mavlink_msg_payload_controller_real_time_data_get_vert_view_angle(msg);
	payload_controller_real_time_data->UAV_hdg = mavlink_msg_payload_controller_real_time_data_get_UAV_hdg(msg);
	payload_controller_real_time_data->flags = mavlink_msg_payload_controller_real_time_data_get_flags(msg);
	payload_controller_real_time_data->current_cam_idx = mavlink_msg_payload_controller_real_time_data_get_current_cam_idx(msg);
	mavlink_msg_payload_controller_real_time_data_get_camera_model(msg, payload_controller_real_time_data->camera_model);
#else
	memcpy(payload_controller_real_time_data, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_PAYLOAD_CONTROLLER_REAL_TIME_DATA_LEN);
#endif
}
