package de.deaod.jstormlib;

import java.io.IOException;
import java.nio.ByteOrder;

import de.deaod.jstormlib.utility.ArrayDataReader;

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
    MPQFile(MPQArchive mpq, String name, MPQFileOpenScope flags) {
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
    MPQFile(MPQArchive mpq, String archivedName, long fileTime, int fileSize, MPQLocale locale, MPQFileFlags flags) {
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
    public void setArchivedName(String newName) {
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
    public long setFilePointer(long newPosition, MPQFileMoveAnchor moveAnchor) {
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
    public int readFile(byte[] buffer, int offset, int length) {
        return MPQFile.readFile(this.fileHandle, buffer, offset, length);
    }
    
    /**
     * Reads data starting from the current position of the file. Fills the buffer passed to this function.
     * 
     * @param buffer the buffer to read data into
     * @return the amount of bytes that have been read.
     */
    public int readFile(byte[] buffer) {
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
    public void write(byte[] data, int offset, int length, MPQCompressionFlags compression) {
        MPQFile.writeFile(this.fileHandle, data, offset, length, compression.getFlags());
    }
    
    /**
     * Writes all data contained in the spcified buffer to the current position of the file.
     * 
     * @param data buffer containing data to write
     * @param compression compression to use for the data written, ignored if the file does not specify the COMPRESSED
     *            flag.
     */
    public void write(byte[] data, MPQCompressionFlags compression) {
        this.write(data, 0, data.length, compression);
    }
    
    //
    
    private static native boolean closeFile(long file);
    
    public void close() {
        if (this.fileHandle != 0) {
            MPQFile.closeFile(this.fileHandle);
        }
        this.fileHandle = 0;
        this.mpqArchive = null;
        this.archivedName = null;
    }
    
    //
    
    private static native byte[] getFileInfo(long file, int infoType);
    
    /**
     * 
     * @return
     */
    public int getHashIndex() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.HASH_INDEX.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public int getCodename1() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.CODENAME1.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public int getCodename2() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.CODENAME2.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public MPQLocale getLocale() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.LOCALEID.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return MPQLocale.fromInteger(dataReader.readInt());
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return MPQLocale.DEFAULT;
        }
    }
    
    public int getBlockIndex() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.BLOCKINDEX.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public int getFileSize() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.FILE_SIZE.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public int getCompressedSize() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.COMPRESSED_SIZE.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public MPQFileFlags getFlags() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.FLAGS.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return MPQFileFlags.fromInteger(dataReader.readInt());
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return MPQFileFlags.fromInteger(0);
        }
    }
    
    public int getPosition() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.POSITION.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public int getKey() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.KEY.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public int getKeyUnfixed() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.KEY_UNFIXED.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readInt();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    public long getFileTime() {
        byte[] data = MPQFile.getFileInfo(this.fileHandle, MPQFileInfoFlags.FILETIME.getValue());
        try (ArrayDataReader dataReader = new ArrayDataReader(data, MPQFile.DATA_BYTE_ORDER)) {
            return dataReader.readLong();
        } catch (IOException e) {
            // should never come here, but what the hell ...
            return 0;
        }
    }
    
    //
    
    private static native void setFileLocale(long file, int newLocale);
    
    /**
     * Changes the locale of the file.
     * 
     * @param locale the new locale
     */
    public void setLocale(MPQLocale locale) {
        MPQFile.setFileLocale(this.fileHandle, locale.getValue());
    }
    
    //
    
    private static native long createFile(long mpq, String archivedName, long fileTime, int fileSize, int locale,
            int flags);
    
    void create(MPQArchive mpq, String archivedName, long fileTime, int fileSize, MPQLocale locale, MPQFileFlags flags) {
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
    
    void open(MPQArchive mpq, String name, MPQFileOpenScope flags) {
        close();
        this.mpqArchive = mpq;
        this.fileHandle = MPQFile.openFile(mpq.getMpqHandle(), name, flags.getValue());
        this.archivedName = getArchivedName();
    }
    
    void open(MPQArchive mpq, String name) {
        this.open(mpq, name, MPQFileOpenScope.MPQ);
    }
    
    void open(String name) {
        this.open(this.mpqArchive, name, MPQFileOpenScope.MPQ);
    }
    
}
