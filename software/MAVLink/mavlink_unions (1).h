#include <stdint.h>

typedef struct __mavlink_message_united {
	uint16_t checksum; ///< sent at end of packet
	uint8_t magic;   ///< protocol magic marker
	uint8_t len;     ///< Length of payload
	uint8_t seq;     ///< Sequence of packet
	uint8_t sysid;   ///< ID of message sender system/aircraft
	uint8_t compid;  ///< ID of the message sender component
	uint8_t msgid;   ///< ID of message in payload
	union pl {
	uint64_t payload64[32];
	uint8_t  payload8[256];	
	}__pl__;
}
mavlink_message_united_t;

