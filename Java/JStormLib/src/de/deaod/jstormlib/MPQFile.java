package de.deaod.jstormlib;

import java.nio.ByteOrder;

import de.deaod.jstormlib.utility.ArrayDataReader;

public class MPQFile {
    
    private static final ByteOrder DATA_BYTE_ORDER = ByteOrder.BIG_ENDIAN;
    
    private long                   fileHandle      = 0;
    private MPQArchive             mpqArchive      = null;
    private String                 archivedName    = null;
    
    //
    
    public MPQFile() {
    }
    
    public MPQFile(MPQArchive mpq, String name, MPQFileOpenScope flags) {
        open(mpq, name, flags);
    }
    
    public MPQFile(MPQArchive mpq, String archivedName, long fileTime, int fileSize, MPQLocale locale,
            MPQFileFlags flags) {
        create(mpq, archivedName, fileTime, fileSize, locale, flags);
    }
    
    //
    
    long getFileHandle() {
        return this.fileHandle;
    }
    
    //
    
    public MPQArchive getContainingArchive() {
        return this.mpqArchive;
    }
    
    //
    
    private static native String getFileName(long file);
    
    private static native void renameFile(long mpq, String oldFileName, String newFileName);
    
    public void setArchivedName(String newName) {
        MPQFile.renameFile(this.mpqArchive.getMpqHandle(), this.archivedName, newName);
        this.archivedName = newName;
    }
    
    public String getArchivedName() {
        return MPQFile.getFileName(this.fileHandle);
    }
    
    //
    
    private static native void removeFile(long mpq, String fileName, int searchScope);
    
    public void removeFromArchive() {
        MPQFile.removeFile(this.mpqArchive.getMpqHandle(), this.archivedName, 0);
    }
    
    //
    
    private static native long getFileSize(long file);
    
    public long getSize() {
        return MPQFile.getFileSize(this.fileHandle);
    }
    
    //
    
    private static native long setFilePointer(long file, long newPosition, int moveMethod);
    
    public long setFilePointer(long newPosition, MPQFileMoveAnchor moveAnchor) {
        if (newPosition > Integer.MAX_VALUE * 2 + 1)
            throw new IllegalArgumentException("");
        return MPQFile.setFilePointer(this.fileHandle, newPosition, moveAnchor.getValue());
    }
    
    //
    
    private static native int readFile(long file, byte[] buffer, int offset, int bytesToRead);
    
    public int readFile(byte[] buffer, int offset, int length) {
        if (buffer == null)
            throw new IllegalArgumentException("Null Buffer");
        if (offset + length > buffer.length)
            throw new IllegalArgumentException("Offset + Length > Buffer Length (" + offset + " + " + length + " > "
                    + buffer.length + ")");
        if (length <= 0)
            throw new IllegalArgumentException("Length less than or equal to zero");
        if (offset < 0)
            throw new IllegalArgumentException("Negative Offset");
        
        return MPQFile.readFile(this.fileHandle, buffer, offset, length);
    }
    
    public int readFile(byte[] buffer) {
        return this.readFile(buffer, 0, buffer.length);
    }
    
    //
    
    private static native void writeFile(long file, byte[] data, int offset, int length, int compression);
    
    public void write(byte[] data, int offset, int length, MPQCompressionFlags compression) {
        MPQFile.writeFile(this.fileHandle, data, offset, length, compression.getFlags());
    }
    
    public void write(byte[] data, MPQCompressionFlags compression) {
        this.write(data, 0, data.length, compression);
    }
    
    //
    
    private static native boolean closeFile(long file);
    
    public void close() {
        MPQFile.closeFile(this.fileHandle);
        this.fileHandle = 0;
        this.mpqArchive = null;
        this.archivedName = null;
    }
    
    //
    
    private static native byte[] getFileInfo(long file, int infoType);
    
    @SuppressWarnings("resource")
    public int getHashIndex() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.HASH_INDEX.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public int getCodename1() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.CODENAME1.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public int getCodename2() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.CODENAME2.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public MPQLocale getLocale() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.LOCALEID.getValue()), MPQFile.DATA_BYTE_ORDER);
        return MPQLocale.fromInteger(dataReader.readInt());
    }
    
    @SuppressWarnings("resource")
    public int getBlockIndex() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.BLOCKINDEX.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public int getFileSize() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.FILE_SIZE.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public int getCompressedSize() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.COMPRESSED_SIZE.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public MPQFileFlags getFlags() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.FLAGS.getValue()), MPQFile.DATA_BYTE_ORDER);
        return MPQFileFlags.fromInteger(dataReader.readInt());
    }
    
    @SuppressWarnings("resource")
    public int getPosition() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.POSITION.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public int getKey() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.KEY.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public int getKeyUnfixed() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.KEY_UNFIXED.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    @SuppressWarnings("resource")
    public long getFileTime() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQFile.getFileInfo(
                this.fileHandle,
                MPQFileInfoFlags.FILETIME.getValue()), MPQFile.DATA_BYTE_ORDER);
        return dataReader.readLong();
    }
    
    //
    
    private static native void setFileLocale(long file, int newLocale);
    
    public void setLocale(MPQLocale locale) {
        MPQFile.setFileLocale(this.fileHandle, locale.getValue());
    }
    
    //
    
    private static native long createFile(long mpq, String archivedName, long fileTime, int fileSize, int locale,
            int flags);
    
    public void create(MPQArchive mpq, String archivedName, long fileTime, int fileSize, MPQLocale locale,
            MPQFileFlags flags) {
        close();
        this.mpqArchive = mpq;
        this.fileHandle = MPQFile.createFile(
                mpq.getMpqHandle(),
                archivedName,
                fileTime,
                fileSize,
                locale.getValue(),
                flags.getFlags());
        this.archivedName = getArchivedName();
    }
    
    //
    
    private static native long openFile(long mpq, String name, int scope);
    
    public void open(MPQArchive mpq, String name, MPQFileOpenScope flags) {
        close();
        this.mpqArchive = mpq;
        this.fileHandle = MPQFile.openFile(mpq.getMpqHandle(), name, flags.getValue());
        this.archivedName = getArchivedName();
    }
    
    public void open(MPQArchive mpq, String name) {
        this.open(mpq, name, MPQFileOpenScope.MPQ);
    }
    
    public void open(String name) {
        this.open(this.mpqArchive, name, MPQFileOpenScope.MPQ);
    }
    
}
