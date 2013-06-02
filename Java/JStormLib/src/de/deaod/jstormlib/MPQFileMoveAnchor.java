package de.deaod.jstormlib;

public enum MPQFileMoveAnchor {
    BEGIN(0),
    CURRENT(1),
    END(2);
    
    private int value;
    
    int getValue() {
        return this.value;
    }
    
    private MPQFileMoveAnchor(int value) {
        this.value = value;
    }
}
