package de.deaod.jstormlib;

import java.util.EnumSet;

public class MPQVerifyFileFlags {
    public enum Flag {
        SECTOR_CRC(0x0001),
        FILE_CRC(0x0002),
        FILE_MD5(0x0004),
        RAW_MD5(0x0008);
        private int value;
        
        int getValue() {
            return this.value;
        }
        
        private Flag(int value) {
            this.value = value;
        }
    }
    
    private EnumSet<Flag> flags = EnumSet.noneOf(Flag.class);
    
    public void setFlags(EnumSet<Flag> flags) {
        this.flags = flags;
    }
    
    int getFlagsAsInt() {
        int result = 0;
        for (Flag f : this.flags) {
            result |= f.getValue();
        }
        return result;
    }
}
