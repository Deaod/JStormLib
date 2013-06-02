/**
 * 
 */
package de.deaod.jstormlib.utility;

import java.io.ByteArrayInputStream;
import java.nio.ByteOrder;

/**
 * This class extends <code>ByteArrayInputStream</code> with the capability to read integer values from a byte array.
 * 
 * @author Deaod <deaod@deaod.de>
 * @version 1.0
 * @see ByteArrayInputStream
 */
public class ArrayDataReader extends ByteArrayInputStream {
    private ByteOrder byteOrder = ByteOrder.nativeOrder();
    
    /**
     * Creates an <code>ArrayDataReader</code> so that it uses <code>buf</code> as its buffer array. The buffer array is
     * not copied. The initial value of <code>pos</code> is 0 and the initial value of <code>count</code> is the length
     * of <code>buf</code>.
     * 
     * @param buf the input buffer.
     * @see java.io.ByteArrayInputStream
     */
    public ArrayDataReader(byte[] buf) {
        super(buf);
    }
    
    /**
     * Creates <code>ByteArrayInputStream</code> that uses <code>buf</code> as its buffer array. The initial value of
     * <code>pos</code> is <code>offset</code> and the initial value of <code>count</code> is the minimum of
     * <code>offset+length</code> and <code>buf.length</code>. The buffer array is not copied. The buffer's mark is set
     * to the specified offset.
     * 
     * @param buf the input buffer.
     * @param offset the offset in the buffer of the first byte to read.
     * @param length the maximum number of bytes to read from the buffer.
     * @see java.io.ByteArrayInputStream
     */
    public ArrayDataReader(byte[] buf, int offset, int length) {
        super(buf, offset, length);
    }
    
    /**
     * Creates an <code>ArrayDataReader</code> so that it uses <code>buf</code> as its buffer array. The buffer array is
     * not copied. The initial value of <code>pos</code> is 0 and the initial value of <code>count</code> is the length
     * of <code>buf</code>.
     * 
     * @param buf the input buffer.
     * @param byteOrder the default byte order with which to read from the array.
     * @see java.io.ByteArrayInputStream
     */
    public ArrayDataReader(byte[] buf, ByteOrder byteOrder) {
        super(buf);
        this.byteOrder = byteOrder;
    }
    
    /**
     * Creates <code>ByteArrayInputStream</code> that uses <code>buf</code> as its buffer array. The initial value of
     * <code>pos</code> is <code>offset</code> and the initial value of <code>count</code> is the minimum of
     * <code>offset+length</code> and <code>buf.length</code>. The buffer array is not copied. The buffer's mark is set
     * to the specified offset.
     * 
     * @param buf the input buffer.
     * @param offset the offset in the buffer of the first byte to read.
     * @param length the maximum number of bytes to read from the buffer.
     * @param byteOrder the default byte order with which to read from the array.
     * @see java.io.ByteArrayInputStream
     */
    public ArrayDataReader(byte[] buf, int offset, int length, ByteOrder byteOrder) {
        super(buf, offset, length);
        this.byteOrder = byteOrder;
    }
    
    //
    
    /**
     * Returns the default byte order with which to read from the array. After constructing an instance of
     * ArrayDataReader, the default byte order is the native one.
     * 
     * @return The default byte order with which to read from the array.
     * @see #readShort()
     * @see #readInt()
     * @see #readLong()
     * @see #readFloat()
     * @see #readDouble()
     * @see ByteOrder
     */
    public ByteOrder getByteOrder() {
        return this.byteOrder;
    }
    
    /**
     * Changes the default byte order to the specified one.
     * 
     * @param byteOrder the new default byte order
     * @see #readShort()
     * @see #readInt()
     * @see #readLong()
     * @see #readFloat()
     * @see #readDouble()
     * @see ByteOrder
     */
    public void setByteOrder(ByteOrder byteOrder) {
        this.byteOrder = byteOrder;
    }
    
    //
    
    /**
     * Reads a 16-bit integer from the array buffer with Little Endian byte order.
     * 
     * @return The 16-bit integer value read from the array buffer.
     */
    public short readShortLE() {
        assert available() >= 2 : "Too few bytes remaining on byte array buffer.";
        short result = 0;
        result |= (this.read() << 0) & 0x00FF;
        result |= (this.read() << 8) & 0xFF00;
        return result;
    }
    
    /**
     * Reads a 16-bit integer from the array buffer with Big Endian byte order.
     * 
     * @return The 16-bit integer value read from the array buffer.
     */
    public short readShortBE() {
        assert available() >= 2 : "Too few bytes remaining on byte array buffer.";
        short result = 0;
        result |= (this.read() << 8) & 0xFF00;
        result |= (this.read() << 0) & 0x00FF;
        return result;
    }
    
    /**
     * Reads a 16-bit integer from the array buffer with the default byte order.
     * 
     * @return The 16-bit integer value read from the array buffer.
     * @see #getByteOrder()
     * @see #setByteOrder(ByteOrder)
     */
    public short readShort() {
        if (this.byteOrder == ByteOrder.BIG_ENDIAN) {
            return readShortBE();
        } else {
            return readShortLE();
        }
    }
    
    //
    
    /**
     * Reads a 32-bit integer from the array buffer with Little Endian byte order.
     * 
     * @return The 32-bit integer value read from the array buffer.
     */
    public int readIntLE() {
        assert available() >= 4 : "Too few bytes remaining on byte array buffer.";
        int result = 0;
        result |= (this.read() << 0) & 0x000000FF;
        result |= (this.read() << 8) & 0x0000FF00;
        result |= (this.read() << 16) & 0x00FF0000;
        result |= (this.read() << 24) & 0xFF000000;
        return result;
    }
    
    /**
     * Reads a 32-bit integer from the array buffer with Big Endian byte order.
     * 
     * @return The 32-bit integer value read from the array buffer.
     */
    public int readIntBE() {
        assert available() >= 4 : "Too few bytes remaining on byte array buffer.";
        int result = 0;
        result |= (this.read() << 24) & 0xFF000000;
        result |= (this.read() << 16) & 0x00FF0000;
        result |= (this.read() << 8) & 0x0000FF00;
        result |= (this.read() << 0) & 0x000000FF;
        return result;
    }
    
    /**
     * Reads a 32-bit integer from the array buffer with the default byte order.
     * 
     * @return The 32-bit integer value read from the array buffer.
     * @see #getByteOrder()
     * @see #setByteOrder(ByteOrder)
     */
    public int readInt() {
        if (this.byteOrder == ByteOrder.BIG_ENDIAN) {
            return readIntBE();
        } else {
            return readIntLE();
        }
    }
    
    //
    
    /**
     * Reads a 64-bit integer from the array buffer with Little Endian byte order.
     * 
     * @return The 64-bit integer value read from the array buffer.
     */
    public long readLongLE() {
        assert available() >= 8 : "Too few bytes remaining on byte array buffer.";
        long result = 0;
        result |= ((long) this.read() << 0L) & 0x00000000000000FFL;
        result |= ((long) this.read() << 8L) & 0x000000000000FF00L;
        result |= ((long) this.read() << 16L) & 0x0000000000FF0000L;
        result |= ((long) this.read() << 24L) & 0x00000000FF000000L;
        result |= ((long) this.read() << 32L) & 0x000000FF00000000L;
        result |= ((long) this.read() << 40L) & 0x0000FF0000000000L;
        result |= ((long) this.read() << 48L) & 0x00FF000000000000L;
        result |= ((long) this.read() << 56L) & 0xFF00000000000000L;
        return result;
    }
    
    /**
     * Reads a 64-bit integer from the array buffer with Big Endian byte order.
     * 
     * @return The 64-bit integer value read from the array buffer.
     */
    public long readLongBE() {
        assert available() >= 8 : "Too few bytes remaining on byte array buffer.";
        long result = 0;
        result |= ((long) this.read() << 56L) & 0xFF00000000000000L;
        result |= ((long) this.read() << 48L) & 0x00FF000000000000L;
        result |= ((long) this.read() << 40L) & 0x0000FF0000000000L;
        result |= ((long) this.read() << 32L) & 0x000000FF00000000L;
        result |= ((long) this.read() << 24L) & 0x00000000FF000000L;
        result |= ((long) this.read() << 16L) & 0x0000000000FF0000L;
        result |= ((long) this.read() << 8L) & 0x000000000000FF00L;
        result |= ((long) this.read() << 0L) & 0x00000000000000FFL;
        return result;
    }
    
    /**
     * Reads a 64-bit integer from the array buffer with the default byte order.
     * 
     * @return The 64-bit integer value read from the array buffer.
     * @see #getByteOrder()
     * @see #setByteOrder(ByteOrder)
     */
    public long readLong() {
        if (this.byteOrder == ByteOrder.BIG_ENDIAN) {
            return readLongBE();
        } else {
            return readLongLE();
        }
    }
    
    //
    
    public float readFloatLE() {
        return Float.intBitsToFloat(readIntLE());
    }
    
    public float readFloatBE() {
        return Float.intBitsToFloat(readIntBE());
    }
    
    public float readFloat() {
        return Float.intBitsToFloat(readInt());
    }
    
    //
    
    public double readDoubleLE() {
        return Double.longBitsToDouble(readLongLE());
    }
    
    public double readDoubleBE() {
        return Double.longBitsToDouble(readLongBE());
    }
    
    public double readDouble() {
        return Double.longBitsToDouble(readLong());
    }
}
