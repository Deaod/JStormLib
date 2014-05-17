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
        
        private final int value;
        
        int getValue() {
            return this.value;
        }
        
        private Result(final int value) {
            this.value = value;
        }
    }
    
    private MPQVerifyFileResults() {
    }

    private EnumSet<Result> results = EnumSet.noneOf(Result.class);
    
    static MPQVerifyFileResults fromInteger(final int value) {
        final MPQVerifyFileResults result = new MPQVerifyFileResults();
        result.results = EnumSet.noneOf(Result.class);
        for (final Result r : Result.values()) {
            if ((value & r.getValue()) != 0) {
                result.results.add(r);
            }
        }
        return result;
    }
    
    public EnumSet<Result> getResults() {
        return this.results;
    }
}
