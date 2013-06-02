package de.deaod.jstormlib;

import java.util.EnumSet;

public class MPQVerifyFileResults {
    public enum Result {
        OPEN_ERROR(0x0001),
        READ_ERROR(0x0002),
        HAS_SECTOR_CRC(0x0004),
        SECTOR_CRC_ERROR(0x0008),
        HAS_CHECKSUM(0x0010),
        CHECKSUM_ERROR(0x0020),
        HAS_MD5(0x0040),
        MD5_ERROR(0x0080),
        HAS_RAW_MD5(0x0100),
        RAW_MD5_ERROR(0x0200);
        
        private int value;
        
        int getValue() {
            return this.value;
        }
        
        private Result(int value) {
            this.value = value;
        }
    }
    
    private EnumSet<Result> results = EnumSet.noneOf(Result.class);
    
    void fromInteger(int value) {
        this.results = EnumSet.noneOf(Result.class);
        for (Result r : Result.values()) {
            if ((value & r.getValue()) != 0)
                this.results.add(r);
        }
    }
    
    public EnumSet<Result> getResults() {
        return this.results;
    }
}
