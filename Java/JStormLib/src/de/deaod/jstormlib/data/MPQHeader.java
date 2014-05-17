package de.deaod.jstormlib.data;

public class MPQHeader {
    // verison 1
    private final byte[]     signature = new byte[] { 'M', 'P', 'Q', 0x1A };
    private int              headerSize;
    private int              archiveSize;
    private MPQFormatVersion formatVersion;
    private int              sectorSize;
    private int              hashTablePosition;
    private int              blockTablePosition;
    private int              hashTableSize;
    private int              blockTableSize;
    // version 2
    private long             highBlockTablePosition;
    private short            hashTablePositionHigh;
    private short            blockTablePositionHigh;
    // version 3
    private long             archiveSize64;
    private long             betTablePosition;
    private long             hetTablePosition;
    // version 4
    private long             hashTableSize64;
    private long             blockTableSize64;
    private long             highBlockTableSize;
    private long             hetTableSize;
    private long             betTableSize;
    
    private int              rawChunkSize;
    
    private byte[]           md5BLockTable;
    private byte[]           md5HashTable;
    private byte[]           md5HighBlockTable;
    private byte[]           md5BetTable;
    private byte[]           md5HetTable;
    private byte[]           md5MpqHeader;
    
    public enum MPQFormatVersion {
        /**
         * Format 1 (up to The Burning Crusade)
         */
        VERSION_1(0),
        /**
         * Format 2 (The Burning Crusade and newer)
         */
        VERSION_2(1),
        /**
         * Format 3 (WoW - Cataclysm beta or newer)
         */
        VERSION_3(2),
        /**
         * Format 4 (WoW - Cataclysm beta or newer)
         */
        VERSION_4(3);
        
        private final int id;
        
        public final int getId() {
            return this.id;
        }
        
        private MPQFormatVersion(final int id) {
            this.id = id;
        }
        
        public static MPQFormatVersion fromInteger(final int id) {
            for (final MPQFormatVersion formatVersion : MPQFormatVersion.values()) {
                if (formatVersion.getId() == id) {
                    return formatVersion;
                }
            }
            return null;
        }
    }
    
    /**
     * @return the ID_MPQ ('MPQ\x1A') signature
     */
    public final byte[] getSignature() {
        return this.signature;
    }
    
    /**
     * @return the size of the archive header
     */
    public final int getHeaderSize() {
        return this.headerSize;
    }
    
    /**
     * This field is deprecated in the Burning Crusade MoPaQ format, and the size of the archive is calculated as the
     * size from the beginning of the archive to the end of the hash table, block table, or hi-block table (whichever is
     * largest).
     * 
     * @return the 32-bit size of MPQ archive
     */
    public final int getArchiveSize() {
        return this.archiveSize;
    }
    
    /**
     * @return the format version of the MPQ
     */
    public final MPQFormatVersion getFormatVersion() {
        return this.formatVersion;
    }
    
    /**
     * Power of two exponent specifying the number of 512-byte disk sectors in each file sector in the archive. The size
     * of each file sector in the archive is 512 * 2 ^ wSectorSize.
     * 
     * @return the sector size
     */
    public final int getSectorSize() {
        return this.sectorSize;
    }
    
    /**
     * @return the offset to the beginning of the hash table, relative to the beginning of the archive.
     */
    public final int getHashTablePosition() {
        return this.hashTablePosition;
    }
    
    /**
     * @return the offset to the beginning of the block table, relative to the beginning of the archive.
     */
    public final int getBlockTablePosition() {
        return this.blockTablePosition;
    }
    
    /**
     * Number of entries in the hash table. Must be a power of two, and must be less than 2^16 for the original MoPaQ
     * format, or less than 2^20 for the Burning Crusade format.
     * 
     * @return the number of entries in the hash table
     */
    public final int getHashTableSize() {
        return this.hashTableSize;
    }
    
    /**
     * @return the number of entries in the block table
     */
    public final int getBlockTableSize() {
        return this.blockTableSize;
    }
    
    /**
     * @return the offset to the beginning of array of 16-bit high parts of file offsets.
     */
    public final long getHighBlockTablePosition() {
        return this.highBlockTablePosition;
    }
    
    /**
     * @return the high 16 bits of the hash table offset for large archives.
     */
    public final short getHashTablePositionHigh() {
        return this.hashTablePositionHigh;
    }
    
    /**
     * @return the high 16 bits of the block table offset for large archives.
     */
    public final short getBlockTablePositionHigh() {
        return this.blockTablePositionHigh;
    }
    
    /**
     * @return the 64-bit version of the archive size
     */
    public final long getArchiveSize64() {
        return this.archiveSize64;
    }
    
    /**
     * @return the 64-bit position of the BET table
     */
    public final long getBetTablePosition() {
        return this.betTablePosition;
    }
    
    /**
     * @return the 64-bit position of the HET table
     */
    public final long getHetTablePosition() {
        return this.hetTablePosition;
    }
    
    /**
     * @return the compressed size of the hash table
     */
    public final long getHashTableSize64() {
        return this.hashTableSize64;
    }
    
    /**
     * @return the compressed size of the block table
     */
    public final long getBlockTableSize64() {
        return this.blockTableSize64;
    }
    
    /**
     * @return the compressed size of the hi-block table
     */
    public final long getHighBlockTableSize() {
        return this.highBlockTableSize;
    }
    
    /**
     * @return the compressed size of the HET block
     */
    public final long getHetTableSize() {
        return this.hetTableSize;
    }
    
    /**
     * @return the compressed size of the BET block
     */
    public final long getBetTableSize() {
        return this.betTableSize;
    }
    
    /**
     * Size of raw data chunk to calculate MD5. MD5 of each data chunk follows the raw file data.
     * 
     * @return the size of raw data chunk to calculate MD5.
     */
    public final int getRawChunkSize() {
        return this.rawChunkSize;
    }
    
    /**
     * @return the MD5 of the block table before decryption
     */
    public final byte[] getMd5BLockTable() {
        return this.md5BLockTable;
    }
    
    /**
     * @return the MD5 of the hash table before decryption
     */
    public final byte[] getMd5HashTable() {
        return this.md5HashTable;
    }
    
    /**
     * @return the MD5 of the hi-block table
     */
    public final byte[] getMd5HighBlockTable() {
        return this.md5HighBlockTable;
    }
    
    /**
     * @return the MD5 of the BET table before decryption
     */
    public final byte[] getMd5BetTable() {
        return this.md5BetTable;
    }
    
    /**
     * @return the MD5 of the HET table before decryption
     */
    public final byte[] getMd5HetTable() {
        return this.md5HetTable;
    }
    
    /**
     * @return the MD5 of the MPQ header from signature to (including) MD5_HetTable
     */
    public final byte[] getMd5MpqHeader() {
        return this.md5MpqHeader;
    }
}
