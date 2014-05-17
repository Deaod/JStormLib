package de.deaod.jstormlib.data;

public class MPQHetHeader extends MPQExtHeader {
    private int tableSize;
    private int entryCount;
    private int totalCount;
    private int nameHashBitSize;
    private int indexSizeTotal;
    private int indexSizeExtra;
    private int indexSize;
    private int indexTableSize;
    
    /**
     * @return the size of the entire HET table, including HET_TABLE_HEADER (in bytes)
     */
    public final int getTableSize() {
        return this.tableSize;
    }
    
    /**
     * @return the number of occupied entries in the HET table
     */
    public final int getEntryCount() {
        return this.entryCount;
    }
    
    /**
     * @return the total number of entries in the HET table
     */
    public final int getTotalCount() {
        return this.totalCount;
    }
    
    /**
     * @return the size of the name hash entry (in bits)
     */
    public final int getNameHashBitSize() {
        return this.nameHashBitSize;
    }
    
    /**
     * @return the total size of file index (in bits)
     */
    public final int getIndexSizeTotal() {
        return this.indexSizeTotal;
    }
    
    /**
     * @return the extra bits in the file index
     */
    public final int getIndexSizeExtra() {
        return this.indexSizeExtra;
    }
    
    /**
     * @return the effective size of the file index (in bits)
     */
    public final int getIndexSize() {
        return this.indexSize;
    }
    
    /**
     * @return the size of the block index subtable (in bytes)
     */
    public final int getIndexTableSize() {
        return this.indexTableSize;
    }
}
