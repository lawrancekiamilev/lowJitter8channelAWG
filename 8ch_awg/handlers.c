#include "pinOut.h"
#include "patterns.h"
void dma_handler() {
    dma_channel_acknowledge_irq0(Chan0DMA); // Acknowledge IRQ
    dma_channel_abort(Chan0DMA);
    dma_channel_set_read_addr(Chan0DMA, chan0Pattern, true);

    dma_channel_abort(Chan1DMA);
    dma_channel_set_read_addr(Chan1DMA, chan1Pattern, true);

    
}
