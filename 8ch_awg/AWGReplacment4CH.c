#include "pinOut.h"
#include "patterns.h"




uint32_t calcReset(float delayTime){
    float RSTDelayfix = (.95*delayTime + 0.9);
    float delayFix = (delayTime - RSTDelayfix)*2;
    uint32_t RstDelayTime = (int)((delayTime*2.f)+delayFix);
    return RstDelayTime;

}


int main() {

    //set_sys_clock_khz(3000, true);
    stdio_init_all();
    vreg_set_voltage(VREG_VOLTAGE_1_20);
    set_sys_clock_khz(300000, true);

    
    for(int i = 0; i<8;i++){
        gpio_set_drive_strength(DATA_PIN_BASE + i, GPIO_DRIVE_STRENGTH_2MA);
        gpio_set_slew_rate(DATA_PIN_BASE + i, GPIO_SLEW_RATE_FAST);
        gpio_pull_down(DATA_PIN_BASE + i);
    }
    for(int i = 0; i<5; i++){
        gpio_set_drive_strength(SIDESET_PIN_BASED01 + i, GPIO_DRIVE_STRENGTH_2MA);
        gpio_set_drive_strength(SIDESET_PIN_BASED23 + i, GPIO_DRIVE_STRENGTH_2MA);
        gpio_set_slew_rate(SIDESET_PIN_BASED01 + i, GPIO_SLEW_RATE_FAST);
        gpio_set_slew_rate(SIDESET_PIN_BASED23 + i, GPIO_SLEW_RATE_FAST);
        gpio_pull_up(SIDESET_PIN_BASED01 + i);
        gpio_pull_up(SIDESET_PIN_BASED23 + i);
    }

    gpio_init(syncPin);
    gpio_set_dir(syncPin, GPIO_IN);
    
    //initDac0(pioDIGITAL, Chan0SM, 1.5f, DATA_PIN_BASE, SIDESET_PIN_BASED01, DMAsyncPin);
    //initDac1(pioDIGITAL, Chan1SM, 1.5f, DATA_PIN_BASE, SIDESET_PIN_BASED01);
    //initDac2(pioDIGITAL, Chan2SM, 1.5f, DATA_PIN_BASE, SIDESET_PIN_BASED23);
    //initDac3(pioDIGITAL, Chan3SM, 1.5f, DATA_PIN_BASE, SIDESET_PIN_BASED23);
    initdac4(pio4SR, Chan4SM, 1.5f, DATA_PIN_BASE,SIDESET_PIN_BASED01,DMAsyncPin);
    initrstChan(pio4SR, RSTsm, 1.5f, DATA_PIN_BASE,SIDESET_PIN_BASED01,RSTsyncPin);
    initSVB(pio4SR, SVBsm, 1.5f, DATA_PIN_BASE,SIDESET_PIN_BASED23,SVBsyncPin);
    initsync(pioS, DigitalSyncSM, 1.5f, syncPin, DMAsyncPin);
    initSVBsync(pioS, SVBsync, 1.5f, syncPin, SVBsyncPin);
    //initrst(pioS, RSTsync, 1.5f, syncPin, RSTsyncPin);
    pio_sm_put_blocking(pioS, SVBsync,calcReset(2000));
    pio_sm_put_blocking(pioS, SVBsync,calcReset(100));
    sleep_us(1);
    pio_sm_set_enabled(pioS, SVBsync,true);
    pio_sm_put(pio4SR, SVBsm, 255);
    sleep_us(1);
    pio_sm_set_enabled(pio4SR,SVBsm,true);
    sleep_us(1);
    pio_sm_clear_fifos(pio4SR,SVBsm);
    
    uint DigitalSyncDMA = dma_claim_unused_channel(true);
    uint RSTDMA = dma_claim_unused_channel(true);
    uint SVBsyncDMA = dma_claim_unused_channel(true);
    setupSyncDma(DigitalSyncDMA, RSTDMA, SVBsyncDMA);

    uint Chan0DMA = dma_claim_unused_channel(true);
    uint Chan1DMA = dma_claim_unused_channel(true);
    uint Chan2DMA = dma_claim_unused_channel(true);
    uint Chan3DMA = dma_claim_unused_channel(true);
    uint Chan4DMA = dma_claim_unused_channel(true);
    uint ChanRSTDMA = dma_claim_unused_channel(true);
    uint SVBDMA = dma_claim_unused_channel(true);
    setupWaveformDma(Chan0DMA, Chan1DMA, Chan2DMA, Chan3DMA, Chan4DMA, ChanRSTDMA,SVBDMA);

    sleep_ms(100);
    if(!gpio_get(syncPin)){
        while(gpio_get(syncPin)){
            tight_loop_contents();
        }
        while(!gpio_get(syncPin)){
            tight_loop_contents();
        }
        pio_sm_set_enabled(pio4SR, Chan0SM, true);
        pio_sm_set_enabled(pio4SR, RSTsm, true);
        pio_interrupt_clear(pio4SR, 0);

        
    }

    else if(gpio_get(syncPin)){
        while(!gpio_get(syncPin)){
            tight_loop_contents();
        }
        pio_sm_set_enabled(pio4SR, Chan0SM, true);
        pio_sm_set_enabled(pio4SR, RSTsm, true);
        pio_interrupt_clear(pio4SR, 0);
    }

 


    while (1) {
        tight_loop_contents();
    }
}
