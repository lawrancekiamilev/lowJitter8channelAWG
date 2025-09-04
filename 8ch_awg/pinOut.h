#ifndef pinOut_H
#define pinOut_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/vreg.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "sync.pio.h"
#include "rst.pio.h"
#include "SVBsync.pio.h"
#include "dac0.pio.h"
#include "dac1.pio.h"
#include "dac2.pio.h"
#include "dac3.pio.h"
#include "dac4.pio.h"
#include "rstChan.pio.h"
#include "SVB.pio.h"

#define DATA_PIN_BASE 10    // 8-bit data output starts at GPIO 4
#define SIDESET_PIN_BASED01 0 // 3-bit side-set starts at GPIO 0
#define SIDESET_PIN_BASED23 5 
#define syncPin 18
#define rstsyncPin 22
#define DMAsyncPin 19
#define RSTsyncPin 20
#define SVBsyncPin 21

#define DATA_LEN 1024  // 200 values

#define I2C_PORT    i2c1
#define SDApin      26
#define SCLpin      27

#define DigitalSyncSM 0
#define RSTsync 1
#define SVBsync 2
#define SVBWsync 3

#define Chan0SM 0
#define Chan1SM 1
#define Chan2SM 2
#define Chan3SM 3

#define Chan4SM 0
#define RSTsm 1
#define SVBsm   2
#define SVBWsm  3

extern PIO pioDIGITAL = pio0;
extern PIO pio4SR = pio1;
extern PIO pioS = pio2;

void setupWaveformDma(uint Chan0DMA, uint Chan1DMA, uint Chan2DMA , uint Chan3DMA, uint Chan4DMA, uint ChanRstDMA, uint SVBDMA);
void setupSyncDma(uint DigitalSyncDMA, uint RSTDMA, uint SVBsyncDMA);
void dma_handler();
#endif
