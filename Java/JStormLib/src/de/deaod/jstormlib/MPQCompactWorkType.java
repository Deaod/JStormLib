package de.deaod.jstormlib;

/**
 * Enum representing the type of working currently being carried out while compacting an MPQ archive.
 * 
 * @author Deaod <deaod@deaod.de>
 */
public enum MPQCompactWorkType {
    /**
     * Checking if all files in the archive are known.
     */
    CHECKING_FILES(1),
    
    /**
     * Checking hash table of the archive.
     */
    CHECKING_HASH_TABLE(2),
    
    /**
     * Copying over data in front of MPQ data.
     */
    COPYING_NON_MPQ_DATA(3),
    
    /**
     * Writing files to the new MPQ.
     */
    COMPACTING_FILES(4),
    
    /**
     * Closing the archive.
     */
    CLOSING_ARCHIVE(5);
    
    private MPQCompactWorkType(int value) {
        this.value = value;
    }
    
    private int value;
    
    static MPQCompactWorkType fromInteger(int value) {
        for (MPQCompactWorkType type : MPQCompactWorkType.values()) {
            if (value == type.value)
                return type;
        }
        return null;
    }
}
