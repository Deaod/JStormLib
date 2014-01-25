package de.deaod.jstormlib;


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
    
    private Flag[] flags = new Flag[0];
    
    public void setFlags(Flag... flags) {
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
