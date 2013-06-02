package de.deaod.jstormlib;

public enum MPQFileInfoFlags {
    HASH_INDEX(100),
    CODENAME1(101),
    CODENAME2(102),
    LOCALEID(103),
    BLOCKINDEX(104),
    FILE_SIZE(105),
    COMPRESSED_SIZE(106),
    FLAGS(107),
    POSITION(108),
    KEY(109),
    KEY_UNFIXED(110),
    FILETIME(111);
    
    private int value;
    
    int getValue() {
        return this.value;
    }
    
    private MPQFileInfoFlags(int value) {
        this.value = value;
    }
}
