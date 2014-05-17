package de.deaod.jstormlib.data;

public class MPQBetTable {
    private MPQBetHeader header;
    private byte[]       fileTable;
    
    /**
     * Reads bits for an entry in the BET table.
     * 
     * @param entry the index of the entry that should be read
     * @param bitIndex the index of the entry's property that should be read
     * @param bitLength the length of the entry's property. Maximum of 64.
     * @return the entry's property.
     * @throws IllegalArgumentException If entry, bitIndex or bitLength are negative.<br>
     *             If entry exceeds the number of entries indicated by the header.<br>
     *             If bitIndex would lead to accessing data beyond the entry's bounds.<br>
     *             If bitLength is greater than 64.
     */
    private long readBits(final int entry, final int bitIndex, int bitLength) {
        if (bitLength < 0) {
            throw new IllegalArgumentException("bit length too short");
        } else if (bitLength > 64) {
            throw new IllegalArgumentException("bit length too long");
        }
        
        if (bitIndex < 0) {
            throw new IllegalArgumentException("bit index negative");
        } else if ((bitIndex + bitLength) > this.header.getTableEntrySize()) {
            throw new IllegalArgumentException("bit index beyond entry bounds");
        }
        
        if (entry < 0) {
            throw new IllegalArgumentException("entry index negative");
        } else if (entry >= this.header.getEntryCount()) {
            throw new IllegalArgumentException("entry index beyond bounds");
        }
        
        //
        final int bitOffset = ((entry * this.header.getTableEntrySize()) + bitIndex);
        // the byte index that contains the first bits we want to grab
        int byteOffset = bitOffset / 8;
        // the amount of bits starting from the most significant bit that should be discarded from the current byte.
        final int bitsLeft = bitOffset - (byteOffset << 3);
        long result;
        
        // put all remaining bits of the current byte into result
        // this might put too much into result, but we'll take care of that later
        result = this.fileTable[byteOffset++] & ((1 << bitsLeft) - 1);
        bitLength -= bitsLeft;
        
        while (bitLength >= 8) {
            bitLength -= 8;
            result = (result << 8) | this.fileTable[byteOffset++];
        }
        
        if (bitLength < 0) {
            // the only way we can reach this is when we initialized result we put too much into it.
            // So now just shift the excess bits out again.
            result >>= (-bitLength); // also, we can use >> because
        } else if (bitLength > 0) {
            result = (result << bitLength) | (this.fileTable[byteOffset] >>> (8 - bitLength));
        }
        
        return result;
    }
    
    /**
     * 
     * @param entry
     * @return
     */
    public long readEntryFilePos(final int entry) {
        return readBits(entry, this.header.getBitIndexFilePos(), this.header.getBitCountFilePos());
    }
    
    /**
     * 
     * @param entry
     * @return
     */
    public long readEntryFileSize(final int entry) {
        return readBits(entry, this.header.getBitIndexFileSize(), this.header.getBitCountFileSize());
    }
    
    /**
     * 
     * @param entry
     * @return
     */
    public long readEntryCompressedSize(final int entry) {
        return readBits(entry, this.header.getBitIndexCompressedSize(), this.header.getBitCountCompressedSize());
    }
    
    /**
     * 
     * @param entry
     * @return
     */
    public long readEntryFlagIndex(final int entry) {
        return readBits(entry, this.header.getBitIndexFlagIndex(), this.header.getBitCountFlagIndex());
    }
    
    /**
     * 
     * @param entry
     * @return
     */
    public long readEntryUnknown(final int entry) {
        return readBits(entry, this.header.getBitIndexUnknown(), this.header.getBitCountUnknown());
    }
    
}
