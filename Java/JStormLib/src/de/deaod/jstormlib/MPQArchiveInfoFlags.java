package de.deaod.jstormlib;

enum MPQArchiveInfoFlags {
    ARCHIVE_NAME(1),
    ARCHIVE_SIZE(2),
    HASH_TABLE_SIZE(4),
    BLOCK_TABLE_SIZE(5),
    SECTOR_SIZE(6),
    HASH_TABLE(7),
    BLOCK_TABLE(8),
    NUM_FILES(9),
    STREAM_FLAGS(10);
    
    private int value;
    
    private MPQArchiveInfoFlags(int value) {
        this.value = value;
    }
    
    int getValue() {
        return this.value;
    }
}
