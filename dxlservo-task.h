#pragma once
#include <stdint.h>


#define DXL_MAKEWORD(a, b)  ((uint16_t)(((uint8_t)(((uint64_t)(a)) & 0xff)) | ((uint16_t)((uint8_t)(((uint64_t)(b)) & 0xff))) << 8))
#define DXL_MAKEDWORD(a, b) ((uint32_t)(((uint16_t)(((uint64_t)(a)) & 0xffff)) | ((uint32_t)((uint16_t)(((uint64_t)(b)) & 0xffff))) << 16))
#define DXL_LOWORD(l)       ((uint16_t)(((uint64_t)(l)) & 0xffff))
#define DXL_HIWORD(l)       ((uint16_t)((((uint64_t)(l)) >> 16) & 0xffff))
#define DXL_LOBYTE(w)       ((uint8_t)(((uint64_t)(w)) & 0xff))
#define DXL_HIBYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 8) & 0xff))

#define TXPACKET_MAX_LEN    (1*1024)
#define RXPACKET_MAX_LEN    (1*1024)

#define PKT_HEADER0             0
#define PKT_HEADER1             1
#define PKT_HEADER2             2
#define PKT_RESERVED            3
#define PKT_ID                  4
#define PKT_LENGTH_L            5
#define PKT_LENGTH_H            6
#define PKT_INSTRUCTION         7
#define PKT_PARAMETER0          8
#define PKT_ERROR               8

/* Instruction for DXL Protocol */
#define INST_PING           1
#define INST_READ           2
#define INST_WRITE          3
#define INST_REG_WRITE      4
#define INST_ACTION         5
#define INST_FACTORY_RESET  6
#define INST_SYNC_WRITE     131     // 0x83
#define INST_BULK_READ      146     // 0x92
#define INST_REBOOT         8
#define INST_CLEAR          16      // 0x10
#define INST_STATUS         85      // 0x55
#define INST_SYNC_READ      130     // 0x82
#define INST_BULK_WRITE     147     // 0x93

// Communication Result
#define COMM_SUCCESS        0       // tx or rx packet communication success
#define COMM_PORT_BUSY      -1000   // Port is busy (in use)
#define COMM_TX_FAIL        -1001   // Failed transmit instruction packet
#define COMM_RX_FAIL        -1002   // Failed get status packet
#define COMM_TX_ERROR       -2000   // Incorrect instruction packet
#define COMM_RX_WAITING     -3000   // Now recieving status packet
#define COMM_RX_TIMEOUT     -3001   // There is no status packet
#define COMM_RX_CORRUPT     -3002   // Incorrect status packet
#define COMM_NOT_AVAILABLE  -9000   //

typedef struct
{
	uint8_t*	data_write;
	uint8_t*	data_read;
	uint8_t*	tx_packet;
	uint8_t* 	rx_packet;
	uint8_t		error;
	int			communication_result;
	uint8_t*	broadcast_ping_id_list;
} PacketData;


// UART_HandleTypeDef* huart;

// Port Handling
init_uart_interface();

// Packet Handling
void			init_packet_handler	();
unsigned short	update_crc			(unsigned short crc_accum, unsigned char* data_blk_ptr, unsigned short data_blk_size);
const char*		getTXRxResult		(int result);
const char*		getRxPacketError	(uint8_t error);
void			setDataWrite		(uint16_t data_length, uint16_t data_pos, uint32_t data);
uint32_t		getDataRead			(uint16_t data_length, uint16_t data_pos);
void			removeStuffing		(uint8_t* packet);
void			txPacket			();
void			readRXPacket		();

// Low Level Functions
void			ping				(uint8_t id);
void			read				(uint8_t id, uint16_t address, uint8_t data_length);
void			write				(uint8_t id, uint16_t address, uint8_t data_length, uint8_t data);
void			factory_reset		(uint8_t id, uint8_t option);
void			reboot				(uint8_t id);
void			sync_read			(uint16_t start_address, uint16_t data_length, uint16_t param_length);
void			sync_write			(uint16_t start_address, uint16_t data_length, uint16_t param_length);
void			bulk_read			(uint16_t param_length);
void			bulk_write			(uint16_t param_length);