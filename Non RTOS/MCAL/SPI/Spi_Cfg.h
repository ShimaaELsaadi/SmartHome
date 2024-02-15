#ifndef MCAL_SPI_SPI_CFG_H_
#define MCAL_SPI_SPI_CFG_H_

#define SPI_MASTER 	0
#define SPI_SLAVE	1

#define SPI_MODE	SPI_MASTER


#define LSB_FIRST	0
#define MSB_FIRST	1

#define SPI_DORD	MSB_FIRST

/*
 * 		SAMPLE_0 : sample on rising setup on failing
 * 		SAMPLE_1 : sample on faling setup on rising
 * 		SAMPLE_2 : setup on rising sample on failing
 * 		SAMPLE_3 : setup on rising sample on failing
 *
 * */
#define SPI_SAMPLE_0	0
#define SPI_SAMPLE_1	1
#define SPI_SAMPLE_2	2
#define SPI_SAMPLE_3	3

#define SPI_SAMPLE_MODE SPI_SAMPLE_0


#define PRE_4 	0
#define PRE_16 	1
#define PRE_64 	2
#define PRE_128 3
#define PRE_2 	4	// 0 SPI2x = 1
#define PRE_8 	5	// 1 SPI2x = 1
#define PRE_32 	6	// 2 SPI2x = 1
//#define PRE_64 	7	// 3 SPI2x = 1

#define SPI_CLOCK PRE_64

#define SPI_INTERRUPT 1


// clock phase // polarity

#endif /* MCAL_SPI_SPI_CFG_H_ */
