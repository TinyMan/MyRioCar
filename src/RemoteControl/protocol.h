/*
 * protocol.h
 *
 *  Created on: 11 févr. 2016
 *      Author: TinyMan
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

typedef enum {
	MESSAGE_CMD,
	MESSAGE_SATE,
	MESSAGE_HELLO,
	MESSAGE_CNFG,
	MESSAGE_CUSTOM
} remote_message_type;

typedef struct{
	remote_message_type type;
	uint32_t length;
} remote_message_header;

typedef struct {
	float speed; /* speed in % of maximal speed */
	bool forward; /* moving forward or backward */
	float angle; /* angle of the front wheels from -45 to 45 in degree */
} remote_command;

typedef struct {
	float us_ppd; /* sets the ultra sounds detection precision per degree (should be between 0 and 1) */
} remote_cnfg;

typedef struct {
	float angle;
	uint8_t distance;
} us_point;
typedef struct {
	uint16_t npoints; /* number of us_point detected */
	//us_point * points; /* filled with us_point structures when decoding the network buffer */
} us_state;

typedef struct{
	us_state us_detection; /* ultra sound detection state */
} remote_state;


/* STATE MESSAGE
 * *************************************************************************
 * header
 * remote_state
 * *	us_state
 * *	*	point 1
 * *	*	point 2
 * *	*	...
 * ***********************************************************************
 */
#endif /* PROTOCOL_H_ */
