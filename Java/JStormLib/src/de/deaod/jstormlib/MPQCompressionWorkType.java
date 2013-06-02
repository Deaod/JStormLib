package de.deaod.jstormlib;

public enum MPQCompressionWorkType {
    CHECKING_FILES(1),
    CHECKING_HASH_TABLE(2),
    COPYING_NON_MPQ_DATA(3),
    COMPACTING_FILES(4),
    CLOSING_ARCHIVE(5);
    
    private MPQCompressionWorkType(int value) {
        this.value = value;
    }
    
    private int value;
    
    static MPQCompressionWorkType fromInteger(int value) {
        for (MPQCompressionWorkType type : MPQCompressionWorkType.values()) {
            if (value == type.value)
                return type;
        }
        return null;
    }
}
