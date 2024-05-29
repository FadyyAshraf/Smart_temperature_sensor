/*
 * macros.h
 *
 * Created: 5/25/2024 2:07:56 AM
 *  Author: Fady Ashraf
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define Set_Bit(REG,BIT) (REG |= (1<<BIT))
#define Clear_Bit(REG,BIT) (REG &= (~(1<<BIT)))
#define Toggle_Bit(REG,BIT) (REG ^= (1<<BIT))


#endif /* MACROS_H_ */