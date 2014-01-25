package de.deaod.jstormlib;

/**
 * Enum to be used in conjunction with the MPQCompression class. Indicated the level of compression to use when
 * compressing WAVE files.
 * 
 * @author Deaod <deaod@deaod.de>
 * 
 */
public enum MPQCompressionLevel {
    /**
     * Highest quality, but worst compression ratio.
     */
    NONE(0),
    
    /**
     * Medium quality, and average compression ratio.
     */
    WAVE_MEDIUM(4),
    
    /**
     * Lowest quality, but best compression ratio.
     */
    WAVE_LOW(2);
    
    private int value;
    
    int getValue() {
        return this.value;
    }
    
    private MPQCompressionLevel(int value) {
        this.value = value;
    }
}
