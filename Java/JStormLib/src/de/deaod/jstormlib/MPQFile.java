package de.deaod.jstormlib;

import java.nio.ByteOrder;

public class MPQFile implements AutoCloseable {
    
    private static final ByteOrder DATA_BYTE_ORDER = ByteOrder.LITTLE_ENDIAN;
    
    private long                   fileHandle      = 0;
    private MPQArchive             mpqArchive      = null;
    private String                 archivedName    = null;
    
    //
    
    /**
     * Opens an existing file with the specified name inside the given MPQ.
     * 
     * @param mpq the MPQ to look search through
     * @param name the name of the file to open
     * @param flags the scope to search through
     */
    MPQFile(final MPQArchive mpq, final String name, final MPQFileOpenScope flags) {
        open(mpq, name, flags);
    }
    
    /**
     * Creates a new file inside the given MPQ with the specified name.
     * 
     * @param mpq the MPQ to create the file in
     * @param archivedName the name of the new file
     * @param fileTime a date-time value that will be stored in the "(attributes)" file
     * @param fileSize size of the file. The exact amount specified here must be written to the MPQ later on
     * @param locale the locale of the file
     * @param flags the flags to use when adding the file
     */
    MPQFile(final MPQArchive mpq, final String archivedName, final long fileTime, final int fileSize,
        final MPQLocale locale, final MPQFileFlags flags) {
        create(mpq, archivedName, fileTime, fileSize, locale, flags);
    }
    
    //
    
    long getFileHandle() {
        return this.fileHandle;
    }
    
    //
    
    /**
     * Returns the MPQ archive this file is contained in.
     * 
     * @return the MPQ archive this file is contained in
     */
    public MPQArchive getContainingArchive() {
        return this.mpqArchive;
    }
    
    //
    
    private static native String getFileName(long file);
    
    private static native void renameFile(long mpq, String oldFileName, String newFileName);
    
    /**
     * Changes the name of this file
     * 
     * @param newName the new name for the file
     */
    public void setArchivedName(final String newName) {
        MPQFile.renameFile(this.mpqArchive.getMpqHandle(), this.archivedName, newName);
        this.archivedName = newName;
    }
    
    /**
     * Returns the name of this file.
     * 
     * @return the name of this file
     */
    public String getArchivedName() {
        return MPQFile.getFileName(this.fileHandle);
    }
    
    //
    
    private static native void removeFile(long mpq, String fileName, int searchScope);
    
    /**
     * Removes this file from the containing MPQ archive.
     */
    public void removeFromArchive() {
        MPQFile.removeFile(this.mpqArchive.getMpqHandle(), this.archivedName, 0);
    }
    
    //
    
    private static native long getFileSize(long file);
    
    /**
     * Returns the uncompressed size of the file.
     * 
     * @return the uncompressed size of the file
     */
    public long getSize() {
        return MPQFile.getFileSize(this.fileHandle);
    }
    
    //
    
    private static native long setFilePointer(long file, long newPosition, int moveMethod);
    
    /**
     * Changes the position in a currently open file.
     * 
     * @param newPosition offset from the anchor
     * @param moveAnchor the anchor for the new position
     * @return the new position
     */
    public long setFilePointer(final long newPosition, final MPQFileMoveAnchor moveAnchor) {
        return MPQFile.setFilePointer(this.fileHandle, newPosition, moveAnchor.getValue());
    }
    
    //
    
    private static native int readFile(long file, byte[] buffer, int offset, int bytesToRead);
    
    /**
     * Reads data starting from the current position of the file.
     * 
     * @param buffer the buffer to read the data into
     * @param offset the offset inside the buffer where to write the data to
     * @param length the length of the data you want to read
     * @return the amount of bytes that have been read.
     */
    public int readFile(final byte[] buffer, final int offset, final int length) {
        return MPQFile.readFile(this.fileHandle, buffer, offset, length);
    }
    
    /**
     * Reads data starting from the current position of the file. Fills the buffer passed to this function.
     * 
     * @param buffer the buffer to read data into
     * @return the amount of bytes that have been read.
     */
    public int readFile(final byte[] buffer) {
        return this.readFile(buffer, 0, buffer.length);
    }
    
    //
    
    private static native void writeFile(long file, byte[] data, int offset, int length, int compression);
    
    /**
     * Writes the specified data to the current position of the file.
     * 
     * @param data buffer containing data to write
     * @param offset offset of the data to write
     * @param length length of the data to write
     * @param compression compression to use for the data written, ignored if the file does not specify the COMPRESSED
     *            flag.
     */
    public void write(final byte[] data, final int offset, final int length, final MPQCompressionFlags compression) {
        MPQFile.writeFile(this.fileHandle, data, offset, length, compression.getFlags());
    }
    
    /**
     * Writes all data contained in the spcified buffer to the current position of the file.
     * 
     * @param data buffer containing data to write
     * @param compression compression to use for the data written, ignored if the file does not specify the COMPRESSED
     *            flag.
     */
    public void write(final byte[] data, final MPQCompressionFlags compression) {
        this.write(data, 0, data.length, compression);
    }
    
    //
    
    private static native boolean closeFile(long file);
    
    @Override
    public void close() {
        if (this.fileHandle != 0) {
            MPQFile.closeFile(this.fileHandle);
        }
        this.fileHandle = 0;
        this.mpqArchive = null;
        this.archivedName = null;
    }
    
    //
    
    private static native int getHashIndexN(long file);
    
    private static native int getCodename1N(long file);
    
    private static native int getCodename2N(long file);
    
    private static native MPQLocale getLocaleN(long file);
    
    private static native int getBlockIndexN(long file);
    
    private static native int getFileSizeN(long file);
    
    private static native int getCompressedSizeN(long file);
    
    private static native MPQFileFlags getFlagsN(long file);
    
    private static native int getPositionN(long file);
    
    private static native int getKeyN(long file);
    
    private static native int getKeyUnfixedN(long file);
    
    private static native long getFileTimeN(long file);
    
    /**
     * @return the hash-table index of this file within the MPQ.
     */
    public int getHashIndex() {
        return getHashIndexN(this.fileHandle);
    }
    
    /**
     * @return the first hash of the name of this file.
     */
    public int getNameHash1() {
        return getCodename1N(this.fileHandle);
    }
    
    /**
     * @return the second hash of the name of this file.
     */
    public int getNameHash2() {
        return getCodename2N(this.fileHandle);
    }
    
    /**
     * @return the locale of this file.
     */
    public MPQLocale getLocale() {
        return getLocaleN(this.fileHandle);
    }
    
    /**
     * @return the block-table index of this file within the MPQ.
     */
    public int getBlockIndex() {
        return getBlockIndexN(this.fileHandle);
    }
    
    /**
     * @return the uncompressed size of this file.
     */
    public int getFileSize() {
        return getFileSizeN(this.fileHandle);
    }
    
    /**
     * @return the compressed size of this file.
     */
    public int getCompressedSize() {
        return getCompressedSizeN(this.fileHandle);
    }
    
    /**
     * @return the flags associated with this file.
     */
    public MPQFileFlags getFlags() {
        return getFlagsN(this.fileHandle);
    }
    
    /**
     * @return the offset of this file relative to the beginning of the MPQ archive.
     */
    public int getByteOffset() {
        return getPositionN(this.fileHandle);
    }
    
    /**
     * @return the key used for encrypting this file in the MPQ.
     */
    public int getEncryptionKey() {
        return getKeyN(this.fileHandle);
    }
    
    /**
     * @return the raw key used for encrypting this file in the MPQ.
     */
    public int getEncryptionKeyRaw() {
        return getKeyUnfixedN(this.fileHandle);
    }
    
    /**
     * @return the time associated with this file within the MPQ.
     */
    public long getFileTime() {
        return getFileTimeN(this.fileHandle);
    }
    
    //
    
    private static native void setFileLocale(long file, int newLocale);
    
    /**
     * Changes the locale of the file.
     * 
     * @param locale the new locale
     */
    public void setLocale(final MPQLocale locale) {
        MPQFile.setFileLocale(this.fileHandle, locale.getValue());
    }
    
    //
    
    private static native long createFile(long mpq, String archivedName, long fileTime, int fileSize, int locale,
        int flags);
    
    void create(final MPQArchive mpq, final String archivedName, final long fileTime, final int fileSize,
        final MPQLocale locale, final MPQFileFlags flags) {
        close();
        this.mpqArchive = mpq;
        this.fileHandle = 
            MPQFile.createFile(mpq.getMpqHandle(),
                archivedName,
                fileTime,
                fileSize,
                locale.getValue(),
                flags.getFlags());
        this.archivedName = getArchivedName();
    }
    
    //
    
    private static native long openFile(long mpq, String name, int scope);
    
    void open(final MPQArchive mpq, final String name, final MPQFileOpenScope flags) {
        close();
        this.mpqArchive = mpq;
        this.fileHandle = MPQFile.openFile(mpq.getMpqHandle(), name, flags.getValue());
        this.archivedName = getArchivedName();
    }
    
    void open(final MPQArchive mpq, final String name) {
        this.open(mpq, name, MPQFileOpenScope.MPQ);
    }
    
    void open(final String name) {
        this.open(this.mpqArchive, name, MPQFileOpenScope.MPQ);
    }
    
}
