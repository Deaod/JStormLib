package de.deaod.jstormlib;

public final class MPQCompression {
    
    private MPQCompression() {
    }
    
    public static native byte[] implode(byte[] inBuffer, int inBufferOffset, int inBufferLength);
    
    public static byte[] implode(byte[] inBuffer) {
        return MPQCompression.implode(inBuffer, 0, inBuffer.length);
    }
    
    public static native byte[] explode(byte[] inBuffer, int inBufferOffset, int inBufferLength, int outBufferLength);
    
    public static byte[] explode(byte[] inBuffer, int outBufferLength) {
        return MPQCompression.explode(inBuffer, 0, inBuffer.length, outBufferLength);
    }
    
    private static native byte[] compress(byte[] inBuffer, int inBufferOffset, int inBufferLength, int compressionMask,
            int cmpLevel);
    
    public static byte[] compress(byte[] inBuffer, int offset, int length, MPQCompressionFlags compression,
            MPQCompressionLevel compressionLevel) {
        return MPQCompression.compress(inBuffer, offset, length, compression.getFlags(), compressionLevel.getValue());
    }
    
    public static byte[] compress(byte[] inBuffer, int offset, int length, MPQCompressionFlags compression) {
        return MPQCompression.compress(inBuffer, offset, length, compression, MPQCompressionLevel.NONE);
    }
    
    public static byte[] compress(byte[] inBuffer, MPQCompressionFlags compression, MPQCompressionLevel compressionLevel) {
        return MPQCompression.compress(inBuffer, 0, inBuffer.length, compression, compressionLevel);
    }
    
    public static byte[] compress(byte[] inBuffer, MPQCompressionFlags compression) {
        return MPQCompression.compress(inBuffer, 0, inBuffer.length, compression);
    }
    
    public static native byte[] decompress(byte[] inBuffer, int inBufferOffset, int inBufferLength, int outBufferLength);
    
    public static byte[] decompress(byte[] inBuffer, int outBufferLength) {
        return MPQCompression.decompress(inBuffer, 0, inBuffer.length, outBufferLength);
    }
}
