/* 
 * File:   main.h
 * Author: KIKI
 *
 * Created on 2019년 10월 30일 (수), 오후 10:03
 */

#ifndef _MAIN_H_
#define	_MAIN_H_

#include <xc.h>
#include <p32xxxx.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <sys/kmem.h>

#define _XTAL_FREQ 40000000UL

#define SS_TRIS     TRISBbits.TRISB2
#define SS_PIN      LATBbits.LATB2
#define DC_TRIS     TRISBbits.TRISB13
#define DC_PIN      LATBbits.LATB13
#define RST_TRIS    TRISBbits.TRISB12
#define RST_PIN     LATBbits.LATB12

#endif	/* __MAIN_H */

