#include "pinOut.h"
#include "patterns.h"

void setupWaveformDma(uint Chan0DMA, uint Chan1DMA, uint Chan2DMA , uint Chan3DMA, uint Chan4DMA, uint ChanRstDMA, uint SVBDMA) {
    // DMA configuration
    dma_channel_config Chan0DMAconfig = dma_channel_get_default_config(Chan0DMA);
    channel_config_set_transfer_data_size(&Chan0DMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&Chan0DMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&Chan0DMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&Chan0DMAconfig, pio_get_dreq(pioDIGITAL, Chan0SM, true)); // PIO0 TX request
    channel_config_set_ring(&Chan0DMAconfig, false, 10);
    
    // Configure DMA channel
    dma_channel_configure(
        Chan0DMA, &Chan0DMAconfig,
        &pio0_hw->txf[Chan0SM], // Destination: PIO FIFO
        chan0Pattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );

  
    
    dma_channel_config Chan1DMAconfig = dma_channel_get_default_config(Chan1DMA);
    channel_config_set_transfer_data_size(&Chan1DMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&Chan1DMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&Chan1DMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&Chan1DMAconfig, pio_get_dreq(pioDIGITAL, Chan1SM, true)); // PIO0 TX request
    channel_config_set_ring(&Chan1DMAconfig, false, 10);

    // Configure DMA channel
    dma_channel_configure(
        Chan1DMA, &Chan1DMAconfig,
        &pio0_hw->txf[Chan1SM], // Destination: PIO FIFO
        chan1Pattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );
    
    dma_channel_config Chan2DMAconfig = dma_channel_get_default_config(Chan2DMA);
    channel_config_set_transfer_data_size(&Chan2DMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&Chan2DMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&Chan2DMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&Chan2DMAconfig, pio_get_dreq(pioDIGITAL, Chan2SM, true)); // PIO0 TX request
    channel_config_set_ring(&Chan2DMAconfig, false, 10);

    // Configure DMA channel
    dma_channel_configure(
        Chan2DMA, &Chan2DMAconfig,
        &pio0_hw->txf[Chan2SM], // Destination: PIO FIFO
        chan2Pattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );

    dma_channel_config Chan3DMAconfig = dma_channel_get_default_config(Chan3DMA);
    channel_config_set_transfer_data_size(&Chan3DMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&Chan3DMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&Chan3DMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&Chan3DMAconfig, pio_get_dreq(pioDIGITAL, Chan3SM, true)); // PIO0 TX request
    channel_config_set_ring(&Chan3DMAconfig, false, 10);

    // Configure DMA channel
    dma_channel_configure(
        Chan3DMA, &Chan3DMAconfig,
        &pio0_hw->txf[Chan3SM], // Destination: PIO FIFO
        chan3Pattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );

    dma_channel_config Chan4DMAconfig = dma_channel_get_default_config(Chan4DMA);
    channel_config_set_transfer_data_size(&Chan4DMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&Chan4DMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&Chan4DMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&Chan4DMAconfig, pio_get_dreq(pio4SR, Chan4SM, true)); // PIO0 TX request
    channel_config_set_ring(&Chan4DMAconfig, false, 10);

    // Configure DMA channel
    dma_channel_configure(
        Chan4DMA, &Chan4DMAconfig,
        &pio1_hw->txf[Chan4SM], // Destination: PIO FIFO
        chan4Pattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );


    dma_channel_config ChanRstDMAconfig = dma_channel_get_default_config(ChanRstDMA);
    channel_config_set_transfer_data_size(&ChanRstDMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&ChanRstDMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&ChanRstDMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&ChanRstDMAconfig, pio_get_dreq(pio4SR, RSTsm, true)); // PIO0 TX request
    channel_config_set_ring(&ChanRstDMAconfig, false, 1);

    // Configure DMA channel
    dma_channel_configure(
        ChanRstDMA, &ChanRstDMAconfig,
        &pio1_hw->txf[RSTsm], // Destination: PIO FIFO
        RSTpattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );

    dma_channel_config SVBDMAconfig = dma_channel_get_default_config(SVBDMA);
    channel_config_set_transfer_data_size(&SVBDMAconfig, DMA_SIZE_8); // 8-bit transfers
    channel_config_set_read_increment(&SVBDMAconfig, true); // Read from array sequentially
    channel_config_set_write_increment(&SVBDMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&SVBDMAconfig, pio_get_dreq(pio4SR, SVBsm, true)); // PIO0 TX request
    channel_config_set_ring(&SVBDMAconfig, false, 9);

    // Configure DMA channel
    dma_channel_configure(
        SVBDMA, &SVBDMAconfig,
        &pio1_hw->txf[SVBsm], // Destination: PIO FIFO
        SVBPattern,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );
}


void setupSyncDma(uint DigitalSyncDMA, uint RSTDMA, uint SVBsyncDMA){
        dma_channel_config DigitalSyncConfig = dma_channel_get_default_config(DigitalSyncDMA);
    static uint32_t data = DATA_LEN - 2;
    channel_config_set_transfer_data_size(&DigitalSyncConfig, DMA_SIZE_32); // 8-bit transfers
    channel_config_set_read_increment(&DigitalSyncConfig, false); // Read from array sequentially
    channel_config_set_write_increment(&DigitalSyncConfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&DigitalSyncConfig, DREQ_PIO2_TX0); // PIO0 TX request
    // Configure DMA channel
    dma_channel_configure(
        DigitalSyncDMA, &DigitalSyncConfig,
        &pio2_hw->txf[DigitalSyncSM], // Destination: PIO FIFO
        &data,    // Source: data array
        1,      // Transfer count
        true          // Start immediately
    );
    
    dma_channel_config RstDMAconfig = dma_channel_get_default_config(RSTDMA);
    uint32_t data1 = calcReset(100,50);
    channel_config_set_transfer_data_size(&RstDMAconfig, DMA_SIZE_32); // 8-bit transfers
    channel_config_set_read_increment(&RstDMAconfig, false); // Read from array sequentially
    channel_config_set_write_increment(&RstDMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&RstDMAconfig, DREQ_PIO0_TX1); // PIO0 TX request

    // Configure DMA channel
    dma_channel_configure(
        RSTDMA, &RstDMAconfig,
        &pio0_hw->txf[RSTsync], // Destination: PIO FIFO
        &data1,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );

    dma_channel_config SVBsyncDMAconfig = dma_channel_get_default_config(SVBsyncDMA);
    uint32_t SVBDATA = calcSVB(2000,50);
    channel_config_set_transfer_data_size(&SVBsyncDMAconfig, DMA_SIZE_32); // 8-bit transfers
    channel_config_set_read_increment(&SVBsyncDMAconfig, false); // Read from array sequentially
    channel_config_set_write_increment(&SVBsyncDMAconfig, false); // Write to PIO FIFO (fixed)
    channel_config_set_dreq(&SVBsyncDMAconfig, DREQ_PIO2_TX2); // PIO0 TX request

    // Configure DMA channel
    dma_channel_configure(
        SVBsyncDMA, &SVBsyncDMAconfig,
        &pio2_hw->txf[SVBsync], // Destination: PIO FIFO
        &SVBDATA,    // Source: data array
        0xffffffff,      // Transfer count
        true          // Start immediately
    );
}