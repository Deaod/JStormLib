package de.deaod.jstormlib.data;

public class MPQBetHeader extends MPQExtHeader {
    private int tableSize;
    private int entryCount;
    private int unknown;
    private int tableEntrySize;
    private int bitIndexFilePos;
    private int bitIndexFileSize;
    private int bitIndexCompressedSize;
    private int bitIndexFlagIndex;
    private int bitIndexUnknown;
    private int bitCountFilePos;
    private int bitCountFileSize;
    private int bitCountCompressedSize;
    private int bitCountFlagIndex;
    private int bitCountUnknown;
    private int bitTotalNameHash2;
    private int bitExtraNameHash2;
    private int bitCountNameHash2;
    private int nameHashArraySize;
    private int flagCount;
    
    /**
     * @return the size of the entire BET table, including the header (in bytes)
     */
    public final int getTableSize() {
        return this.tableSize;
    }
    
    /**
     * @return the number of entries in the BET table. Must match HET_TABLE_HEADER::dwEntryCount
     */
    public final int getEntryCount() {
        return this.entryCount;
    }
    
    /**
     * @return the unknown
     */
    public final int getUnknown() {
        return this.unknown;
    }
    
    /**
     * @return the size of one table entry (in bits)
     */
    public final int getTableEntrySize() {
        return this.tableEntrySize;
    }
    
    /**
     * @return the bit index of the file position (within the entry record)
     */
    public final int getBitIndexFilePos() {
        return this.bitIndexFilePos;
    }
    
    /**
     * @return the bit index of the file size (within the entry record)
     */
    public final int getBitIndexFileSize() {
        return this.bitIndexFileSize;
    }
    
    /**
     * @return the bit index of the compressed size (within the entry record)
     */
    public final int getBitIndexCompressedSize() {
        return this.bitIndexCompressedSize;
    }
    
    /**
     * @return the bit index of the flag index (within the entry record)
     */
    public final int getBitIndexFlagIndex() {
        return this.bitIndexFlagIndex;
    }
    
    /**
     * @return the bit index of the ??? (within the entry record)
     */
    public final int getBitIndexUnknown() {
        return this.bitIndexUnknown;
    }
    
    /**
     * @return the bit size of file position (in the entry record)
     */
    public final int getBitCountFilePos() {
        return this.bitCountFilePos;
    }
    
    /**
     * @return the bit size of file size (in the entry record)
     */
    public final int getBitCountFileSize() {
        return this.bitCountFileSize;
    }
    
    /**
     * @return the bit size of compressed file size (in the entry record)
     */
    public final int getBitCountCompressedSize() {
        return this.bitCountCompressedSize;
    }
    
    /**
     * @return the bit size of flags index (in the entry record)
     */
    public final int getBitCountFlagIndex() {
        return this.bitCountFlagIndex;
    }
    
    /**
     * @return the bit size of ??? (in the entry record)
     */
    public final int getBitCountUnknown() {
        return this.bitCountUnknown;
    }
    
    /**
     * @return the total bit size of the NameHash2
     */
    public final int getBitTotalNameHash2() {
        return this.bitTotalNameHash2;
    }
    
    /**
     * @return the extra bits in the NameHash2
     */
    public final int getBitExtraNameHash2() {
        return this.bitExtraNameHash2;
    }
    
    /**
     * @return the effective size of NameHash2 (in bits)
     */
    public final int getBitCountNameHash2() {
        return this.bitCountNameHash2;
    }
    
    /**
     * @return the size of NameHash2 table, in bytes
     */
    public final int getNameHashArraySize() {
        return this.nameHashArraySize;
    }
    
    /**
     * @return the number of flags in the following array
     */
    public final int getFlagCount() {
        return this.flagCount;
    }
}
