package de.deaod.jstormlib;

public enum MPQFileOpenScope {
    MPQ(0x00000000),
    LOCAL_FILE(0xFFFFFFFF);
    
    private int value;
    
    int getValue() {
        return this.value;
    }
    
    private MPQFileOpenScope(int value) {
        this.value = value;
    }
}
