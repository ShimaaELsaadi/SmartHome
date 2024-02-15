#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(PORT , x)		PORT |= (1<<(x))
#define CLEAR_BIT(PORT , x)		PORT &=~(1<<(x))
#define TOGGLE_BIT(PORT , x)	PORT ^= (1<<(x))

#define SET_HIGH_NIPPLE(PORT , n)		PORT |= 0xf0
#define CLEAR_HIGH_NIPPLE(PORT , n)		PORT&= 0x0f

#define SET_LOW_NIPPLE(PORT , n)		PORT |= 0x0f
#define CLEAR_LOW_NIPPLE(PORT , n)		PORT&= 0xf0

#define GET_BIT(PORT , x)		((PORT & (1 << (x)))>>(x))


#endif /* BIT_MATH_H_ */
