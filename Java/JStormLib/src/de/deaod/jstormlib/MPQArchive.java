package de.deaod.jstormlib;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.nio.ByteOrder;

import de.deaod.jstormlib.MPQSearch.SearchType;
import de.deaod.jstormlib.data.MPQBlock;
import de.deaod.jstormlib.data.MPQFindData;
import de.deaod.jstormlib.data.MPQHash;
import de.deaod.jstormlib.exceptions.MPQAlreadyExistsException;
import de.deaod.jstormlib.exceptions.MPQException;
import de.deaod.jstormlib.exceptions.MPQFileNotFoundException;
import de.deaod.jstormlib.exceptions.MPQFormatException;
import de.deaod.jstormlib.exceptions.MPQIsAVIException;
import de.deaod.jstormlib.exceptions.MPQPermissionException;
import de.deaod.jstormlib.utility.ArrayDataReader;

/**
 * This class represents an entire MPQ archive.
 * 
 * @author Deaod <deaod@deaod.de>
 * @version 1.0
 * 
 * @see <a href="http://zezula.net/en/mpq/mpqformat.html">MPQ Format</a>
 */
public class MPQArchive {
    private static final int       MAX_FILE_COUNT_MIN     = 0x00000004;
    private static final int       MAX_FILE_COUNT_MAX     = 0x00080000;
    private static final int       DEFAULT_MAX_FILE_COUNT = MPQArchive.MAX_FILE_COUNT_MIN;
    private static final ByteOrder DATA_BYTE_ORDER        = ByteOrder.nativeOrder();
    
    private long                   mpqHandle              = 0L;
    private MPQAddFileCallback     addFileCallback        = null;
    private MPQCompactCallback     compactCallback        = null;
    
    /**
     * 
     * @param file - path to the MPQ file to be opened.
     */
    public MPQArchive(String file) {
        if (file == null)
            throw new IllegalArgumentException("file MUST NOT be null");
        try {
            initializeOpen(file, new MPQArchiveOpenFlags());
        } catch (MPQException e) {
            initializeCreate(new File(file), new MPQArchiveCreateFlags(), MPQArchive.DEFAULT_MAX_FILE_COUNT);
        }
    }
    
    /**
     * 
     * @param file - the MPQ file to be opened.
     */
    public MPQArchive(File file) {
        if (file == null)
            throw new IllegalArgumentException("file MUST NOT be null");
        try {
            initializeOpen(file.getAbsolutePath(), new MPQArchiveOpenFlags());
        } catch (MPQException e) {
            initializeCreate(file, new MPQArchiveCreateFlags(), MPQArchive.DEFAULT_MAX_FILE_COUNT);
        }
    }
    
    public MPQArchive(URL url) throws MPQFormatException, MPQIsAVIException {
        if (url == null)
            throw new IllegalArgumentException("url MUST NOT be null");
        MPQArchiveOpenFlags flags = new MPQArchiveOpenFlags();
        flags.setBaseProvider(MPQArchiveOpenFlags.BaseProvider.HTTP);
        initializeOpen(url.toString(), flags);
    }
    
    public MPQArchive(String file, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        initializeOpen(file, flags);
    }
    
    public MPQArchive(File file, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        initializeOpen(file.getAbsolutePath(), flags);
    }
    
    public MPQArchive(URL url, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        flags.setBaseProvider(MPQArchiveOpenFlags.BaseProvider.HTTP);
        initializeOpen(url.toString(), flags);
    }
    
    public MPQArchive(String file, MPQArchiveCreateFlags flags) throws MPQAlreadyExistsException {
        initializeCreate(new File(file), flags, MPQArchive.DEFAULT_MAX_FILE_COUNT);
    }
    
    public MPQArchive(File file, MPQArchiveCreateFlags flags) throws MPQAlreadyExistsException {
        initializeCreate(file, flags, MPQArchive.DEFAULT_MAX_FILE_COUNT);
    }
    
    //
    
    private static native long createArchive(String name, int flags, int maxFileCount);
    
    private void initializeCreate(File file, MPQArchiveCreateFlags flags, int maxFileCount) {
        this.mpqHandle = MPQArchive.createArchive(file.getAbsolutePath(), flags.getFlags(), maxFileCount);
    }
    
    //
    
    private static native long openArchive(String name, int flags) throws MPQFormatException, MPQIsAVIException;
    
    private void initializeOpen(String file, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        this.mpqHandle = MPQArchive.openArchive(file, flags.getFlags());
    }
    
    //
    
    private static native void addListFile(long mpq, String name);
    
    public void addListFile(String file) {
        MPQArchive.addListFile(this.mpqHandle, file);
    }
    
    public void addListFile(File file) {
        MPQArchive.addListFile(this.mpqHandle, file.getAbsolutePath());
    }
    
    //
    
    long getMpqHandle() {
        return this.mpqHandle;
    }
    
    //
    
    private static native void setLocale(int locale);
    
    public static void setLocale(MPQLocale locale) {
        MPQArchive.setLocale(locale.getValue());
    }
    
    //
    
    private static native int getNativeLocale();
    
    public static MPQLocale getLocale() {
        return MPQLocale.fromInteger(MPQArchive.getNativeLocale());
    }
    
    //
    
    private static native void flushArchive(long mpq);
    
    public void flush() {
        MPQArchive.flushArchive(this.mpqHandle);
    }
    
    //
    
    private static native void closeArchive(long mpq);
    
    public void close() {
        MPQArchive.closeArchive(this.mpqHandle);
        this.mpqHandle = 0L;
    }
    
    //
    
    private static native void setMaxFileCount(long mpq, int maxFileCount);
    
    public void setMaxFileCount(int maxFileCount) {
        MPQArchive.setMaxFileCount(
                this.mpqHandle,
                Math.max(MPQArchive.MAX_FILE_COUNT_MIN, Math.min(maxFileCount, MPQArchive.MAX_FILE_COUNT_MAX)));
    }
    
    //
    
    private static native void compactArchive(long mpq, String listFile, boolean reserved)
            throws MPQPermissionException;
    
    public void compactArchive(File listFile) throws MPQPermissionException {
        this.compactArchive(listFile.getAbsolutePath());
    }
    
    public void compactArchive(String listFile) throws MPQPermissionException {
        if (this.compactCallback != null)
            MPQArchive.setCompactCallback(this.mpqHandle, this.compactCallback);
        
        MPQArchive.compactArchive(this.mpqHandle, listFile, false);
    }
    
    private static void compactArchiveCallback(MPQCompactCallback callback, int workType, long bytesProcessed,
            long bytesTotal) {
        callback.compactCallback(MPQCompressionWorkType.fromInteger(workType), bytesProcessed, bytesTotal);
    }
    
    //
    
    private static native void setCompactCallback(long mpq, MPQCompactCallback compactCallback);
    
    public void setCompactCallback(MPQCompactCallback compactCallback) {
        this.compactCallback = compactCallback;
    }
    
    //
    
    private static native void openPatchArchive(long mpq, String name, String patchPathPrefix, int flags)
            throws MPQPermissionException, MPQFormatException, MPQIsAVIException;
    
    public void openPatchArchive(File file, String patchPathPrefix) throws MPQPermissionException, MPQFormatException,
            MPQIsAVIException {
        this.openPatchArchive(file.getAbsolutePath(), patchPathPrefix);
    }
    
    public void openPatchArchive(String file, String patchPathPrefix) throws MPQPermissionException,
            MPQFormatException, MPQIsAVIException {
        MPQArchive.openPatchArchive(this.mpqHandle, file, patchPathPrefix, 0);
    }
    
    //
    
    private static native boolean isPatchedArchive(long mpq);
    
    public boolean isPatchedArchive() {
        return MPQArchive.isPatchedArchive(this.mpqHandle);
    }
    
    //
    
    public void addFile(String fileName, String archivedName, MPQFileFlags flags, MPQCompressionFlags compression) {
        addFile(fileName, archivedName, flags, compression, compression);
    }
    
    public void addFile(String fileName, String archivedName, MPQFileFlags flags, MPQCompressionFlags compression,
            MPQCompressionFlags compressionNext) {
        
        if (this.addFileCallback != null) {
            MPQArchive.setAddFileCallback(this.mpqHandle, this.addFileCallback);
        }
        
        MPQArchive.addFileEx(
                this.mpqHandle,
                fileName,
                archivedName,
                flags.getFlags(),
                compression.getFlags(),
                compressionNext.getFlags());
    }
    
    private static native boolean addFileEx(long mpq, String fileName, String archivedName, int flags, int compression,
            int compressionNext);
    
    private static void addFileCallback(MPQAddFileCallback callback, int bytesWritten, int bytesTotal, boolean finalCall) {
        callback.addFileCallback(bytesWritten, bytesTotal, finalCall);
    }
    
    //
    
    private static native void setAddFileCallback(long mpq, MPQAddFileCallback callbackObject);
    
    public void setAddFileCallback(MPQAddFileCallback addFileCallback) {
        this.addFileCallback = addFileCallback;
    }
    
    //
    
    private static native boolean hasFile(long mpq, String name);
    
    public boolean hasFile(String name) {
        return MPQArchive.hasFile(this.mpqHandle, name);
    }
    
    public boolean hasFile(MPQFile file) {
        if (this.mpqHandle == file.getContainingArchive().mpqHandle) {
            return this.hasFile(file.getArchivedName());
        }
        return false;
    }
    
    //
    
    private static native byte[] getArchiveInfo(long mpq, int infoType);
    
    public String getArchiveName() {
        try {
            byte[] data = MPQArchive.getArchiveInfo(this.mpqHandle, MPQArchiveInfoFlags.ARCHIVE_NAME.getValue());
            return new String(data, "US-ASCII");
        } catch (UnsupportedEncodingException e) {
            // ASCII isnt supported.
            // good luck.
            throw new Error("ASCII charset not supported. Try praying.");
        }
    }
    
    // ArrayDataReader doesnt need to be closed
    @SuppressWarnings("resource")
    public int getArchiveSize() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.ARCHIVE_SIZE.getValue()), MPQArchive.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    // ArrayDataReader doesnt need to be closed
    @SuppressWarnings("resource")
    public int getHashTableSize() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.HASH_TABLE_SIZE.getValue()), MPQArchive.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    // ArrayDataReader doesnt need to be closed
    @SuppressWarnings("resource")
    public int getBlockTableSize() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.BLOCK_TABLE_SIZE.getValue()), MPQArchive.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    // ArrayDataReader doesnt need to be closed
    @SuppressWarnings("resource")
    public int getSectorSize() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.SECTOR_SIZE.getValue()), MPQArchive.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    // ArrayDataReader doesnt need to be closed
    @SuppressWarnings("resource")
    public int getFilesCount() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.NUM_FILES.getValue()), MPQArchive.DATA_BYTE_ORDER);
        return dataReader.readInt();
    }
    
    // ArrayDataReader doesnt need to be closed
    @SuppressWarnings("resource")
    public MPQHash[] getMPQData() {
        ArrayDataReader dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.BLOCK_TABLE.getValue()), MPQArchive.DATA_BYTE_ORDER);
        MPQBlock[] blocks = new MPQBlock[getBlockTableSize()];
        for (int i = 0; i < blocks.length; i++) {
            MPQBlock block = new MPQBlock();
            block.setFilePosition(dataReader.readInt());
            block.setCompressedSize(dataReader.readInt());
            block.setFileSize(dataReader.readInt());
            block.setFlags(MPQFileFlags.fromInteger(dataReader.readInt()));
            
            blocks[i] = block;
        }
        
        dataReader = new ArrayDataReader(MPQArchive.getArchiveInfo(
                this.mpqHandle,
                MPQArchiveInfoFlags.HASH_TABLE.getValue()), MPQArchive.DATA_BYTE_ORDER);
        MPQHash[] hashes = new MPQHash[getHashTableSize()];
        
        for (int i = 0; i < hashes.length; i++) {
            MPQHash hash = new MPQHash();
            hash.setFilePathHashA(dataReader.readInt());
            hash.setFilePathHashB(dataReader.readInt());
            hash.setLocale(MPQLocale.fromInteger(dataReader.readShort()));
            dataReader.skip(2); // wPlatform // unused
            int blockIndex = dataReader.readInt();
            if (blockIndex == MPQHash.EMPTY_BLOCK_INDEX) {
                hash.setBlock(MPQBlock.EMPTY);
            } else if (blockIndex == MPQHash.DELETED_BLOCK_INDEX) {
                hash.setBlock(MPQBlock.DELETED);
            } else {
                hash.setBlock(blocks[blockIndex]);
            }
            
            hashes[i] = hash;
        }
        return hashes;
    }
    
    //
    
    private static native int verifyFile(long mpq, String fileName, int flags);
    
    public MPQVerifyFileResults verifyFile(String fileName, MPQVerifyFileFlags flags) {
        MPQVerifyFileResults results = new MPQVerifyFileResults();
        results.fromInteger(MPQArchive.verifyFile(this.mpqHandle, fileName, flags.getFlagsAsInt()));
        return results;
    }
    
    //
    
    private static native int verifyArchive(long mpq);
    
    public MPQVerifyArchiveResult verify() {
        return MPQVerifyArchiveResult.fromInteger(MPQArchive.verifyArchive(this.mpqHandle));
    }
    
    //
    
    private static native void extractFile(long mpq, String toExtract, String extracted, int searchScope);
    
    public void extractFile(String toExtract, File extracted) {
        this.extractFile(toExtract, extracted.getAbsolutePath());
    }
    
    public void extractFile(String toExtract, String extracted) {
        MPQArchive.extractFile(this.mpqHandle, toExtract, extracted, MPQSearchScope.MPQ.getValue());
    }
    
    //
    
    public MPQSearch find(String mask) {
        return find(mask, null);
    }
    
    public MPQSearch find(String mask, String listFile) {
        MPQSearch search = new MPQSearch();
        MPQFindData data = new MPQFindData();
        search.type = SearchType.NORMAL;
        try {
            search.search = MPQArchive.findFirstFile(this.mpqHandle, mask, data, listFile);
            search.next = data;
        } catch (MPQFileNotFoundException fnfe) {
            search.search = 0L;
            search.next = null;
        }
        return search;
    }
    
    private static native long findFirstFile(long mpq, String mask, MPQFindData fileFindData, String listFile)
            throws MPQFileNotFoundException;
    
    public MPQSearch listFind(String mask) {
        MPQSearch search = new MPQSearch();
        MPQFindData data = new MPQFindData();
        search.type = SearchType.LISTFILE;
        try {
            search.search = MPQArchive.listFindFirstFile(this.mpqHandle, null, mask, data);
            search.next = data;
        } catch (MPQFileNotFoundException fnfe) {
            search.search = 0L;
            search.next = null;
        }
        return search;
    }
    
    public static MPQSearch listFind(String mask, String listFile) {
        MPQSearch search = new MPQSearch();
        MPQFindData data = new MPQFindData();
        search.type = SearchType.LISTFILE;
        try {
            search.search = MPQArchive.listFindFirstFile(0L, listFile, mask, data);
            search.next = data;
        } catch (MPQFileNotFoundException fnfe) {
            search.search = 0L;
            search.next = null;
        }
        return search;
    }
    
    private static native long listFindFirstFile(long mpq, String listFile, String mask, MPQFindData fileFindData)
            throws MPQFileNotFoundException;
    
    //
    
    @Override
    protected void finalize() {
        if (this.mpqHandle != 0L) {
            close();
        }
    }
    
    static {
        String arch = System.getProperty("sun.arch.data.model");
        if (arch.equals("64")) { // might cause problems with JVMs other than the Sun one.
            // running 64 bit JVM
            System.loadLibrary("JStormLib64.dll");
        } else {
            // running 32 bit JVM, probably
            System.loadLibrary("JStormLib32.dll");
        }
    }
}
