package de.deaod.jstormlib.data;

public abstract class MPQExtHeader {
    private byte[] signature;
    private int    version;
    private int    dataSize;
    
    /**
     * @return 'HET\x1A' or 'BET\x1A'
     */
    public final byte[] getSignature() {
        return this.signature;
    }
    
    /**
     * @return the version. Seems to be always 1
     */
    public final int getVersion() {
        return this.version;
    }
    
    /**
     * @return the size of the contained table
     */
    public final int getDataSize() {
        return this.dataSize;
    }
    
}
