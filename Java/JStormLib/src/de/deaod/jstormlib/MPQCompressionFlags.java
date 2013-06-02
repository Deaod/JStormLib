package de.deaod.jstormlib;

public class MPQCompressionFlags {
    public enum Compression {
        /**
         * Don't compress in any way.
         */
        NONE(0x00),
        
        /**
         * Use Huffman compression.
         */
        HUFFMAN(0x01),
        
        /**
         * Use Huffman compression in combination with single channel IMA ADPCM.
         */
        HUFFMAN_ADPCM_MONO(0x41),
        
        /**
         * Use Huffman compression in combination with two channel IMA ADPCM.
         */
        HUFFMAN_ADPCM_STEREO(0x81),
        
        /**
         * Use the zlib compression library.
         */
        ZLIB(0x02),
        
        /**
         * Use bzip2 compression library.
         */
        BZIP2(0x10),
        
        /**
         * Use LZMA compression.
         */
        LZMA(0x12);
        
        private int value;
        
        int getValue() {
            return this.value;
        }
        
        private Compression(int value) {
            this.value = value;
        }
    }
    
    private Compression compression = Compression.NONE;
    
    public Compression getCompression() {
        return this.compression;
    }
    
    public void setCompression(Compression compression) {
        this.compression = compression;
    }
    
    private static final int COMPRESSION_PKWARE   = 0x08;
    private boolean          usePKWARECompression = false;
    
    public boolean isUsingPKWARECompression() {
        return this.usePKWARECompression;
    }
    
    public void setUsingPKWARECompression(boolean usePKWARE) {
        this.usePKWARECompression = usePKWARE;
    }
    
    private static final int COMPRESSION_SPARSE   = 0x20;
    private boolean          useSparseCompression = false;
    
    public boolean isUsingSparseCompression() {
        return this.useSparseCompression;
    }
    
    public void setUsingSparseCompression(boolean useSparse) {
        this.useSparseCompression = useSparse;
    }
    
    int getFlags() {
        int result = this.compression.getValue();
        if (this.compression == Compression.NONE
                || this.compression == Compression.ZLIB
                || this.compression == Compression.BZIP2) {
            
            if (isUsingPKWARECompression()) {
                result |= MPQCompressionFlags.COMPRESSION_PKWARE;
            }
            if (isUsingSparseCompression()) {
                result |= MPQCompressionFlags.COMPRESSION_SPARSE;
            }
        }
        return result;
    }
    
    static final int NEXT_SAME = 0xFFFFFFFF;
}
