package de.deaod.jstormlib;

public enum MPQWorkType {
    CHECKING_FILES(1),
    CHECKING_HASH_TABLE(2),
    COPYING_NON_MPQ_DATA(3),
    COMPACTING_FILES(4),
    CLOSING_ARCHIVE(5);
    
    private MPQWorkType(int value) {
        this.value = value;
    }
    
    private int value;
    
    MPQWorkType getFromInt(int which) {
        for (MPQWorkType type : MPQWorkType.values()) {
            if (which == type.value)
                return type;
        }
        return null;
    }
}
