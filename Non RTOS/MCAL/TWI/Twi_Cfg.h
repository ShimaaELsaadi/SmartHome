#ifndef MCAL_TWI_TWI_CFG_H_
#define MCAL_TWI_TWI_CFG_H_

#define _PRE_1_		0
#define _PRE_4_		1
#define _PRE_16_	2
#define _PRE_64_	3

#define TWI_PRESCALER _PRE_1_
#define SYSTEM_CLOCK 16000000UL
#define SCL_SCL		100000

#define TWI_ADDRESS	0x54

// Status Codes for master transmitting mode
#define SC_MT_START_SENT			0x08
#define SC_MT_REPETED_START_SENT	0x10
#define SC_MT_ADDRESS_SENT_ACK		0x18
#define SC_MT_ADDRESS_SENT_NACK		0x20
#define SC_MT_DATA_SENT_ACK			0x28
#define SC_MT_DATA_SENT_NACK		0x30
#define SC_MT_ARBIT_LOST			0x38
// Status Codes for master receiving mode
#define SC_MR_ADDRESS_SENT_ACK		0x40
#define SC_MR_ADDRESS_SENT_NACK		0x48
#define SC_MR_DATA_SENT_ACK			0x50
#define SC_MR_DATA_SENT_NACK		0x58
// Status Codes for slave receiving mode
#define SC_SR_ADDRESS_ACK			0x60
#define SC_SR_ADDRESS_ACK			0x60

#endif /* MCAL_TWI_TWI_CFG_H_ */
