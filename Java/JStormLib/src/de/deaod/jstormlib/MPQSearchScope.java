package de.deaod.jstormlib;

public enum MPQSearchScope {
    MPQ(0x00000000),
    LOCAL_FILE(0xFFFFFFFF);
    
    private MPQSearchScope(int value) {
        this.value = value;
    }
    
    private int value;
    
    int getValue() {
        return this.value;
    }
}
