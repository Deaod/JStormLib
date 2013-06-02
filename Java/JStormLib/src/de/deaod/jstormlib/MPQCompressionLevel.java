package de.deaod.jstormlib;

public enum MPQCompressionLevel {
    NONE(0),
    WAVE_MEDIUM(4),
    WAVE_LOW(2);
    
    private int value;
    
    int getValue() {
        return this.value;
    }
    
    private MPQCompressionLevel(int value) {
        this.value = value;
    }
}
