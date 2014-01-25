package de.deaod.jstormlib;

import java.io.File;
import java.net.URL;
import java.nio.ByteOrder;

import de.deaod.jstormlib.MPQSearch.SearchType;
import de.deaod.jstormlib.data.MPQBetHeader;
import de.deaod.jstormlib.data.MPQBetTable;
import de.deaod.jstormlib.data.MPQFindData;
import de.deaod.jstormlib.data.MPQHash;
import de.deaod.jstormlib.data.MPQHeader;
import de.deaod.jstormlib.data.MPQHetHeader;
import de.deaod.jstormlib.data.MPQHetTable;
import de.deaod.jstormlib.data.MPQUserDataHeader;
import de.deaod.jstormlib.exceptions.MPQAlreadyExistsException;
import de.deaod.jstormlib.exceptions.MPQException;
import de.deaod.jstormlib.exceptions.MPQFileNotFoundException;
import de.deaod.jstormlib.exceptions.MPQFormatException;
import de.deaod.jstormlib.exceptions.MPQIsAVIException;
import de.deaod.jstormlib.exceptions.MPQPermissionException;

/**
 * This class represents an entire MPQ archive.<br>
 * <br>
 * An MPQ archive is a file containing other, possibly compressed files. These files are stored in one or more blocks
 * which in turn are referenced by a hash table which contains an entry for every file in the archive. The hash table
 * does not contain file names in full, but only hashes of those names. Each hash table entry consists of two 32 bit
 * hashes and the hashing functions ignore case and treat / and \ as the same character.<br>
 * By convention archives may contain a file named "(listfile)", which is a text file with the name of one file
 * contained within the archive on each line. The listfile is not guaranteed to only contain files acutally within the
 * archive, nor is it guaranteed to contain every file within the archive.
 * 
 * @author Deaod <deaod@deaod.de>
 * @version 1.0
 * 
 * @see <a href="http://zezula.net/en/mpq/mpqformat.html">MPQ Format</a>
 */
public class MPQArchive implements AutoCloseable {
    private static final int       MAX_FILE_COUNT_MIN     = 0x00000004;
    private static final int       MAX_FILE_COUNT_MAX     = 0x00080000;
    private static final int       DEFAULT_MAX_FILE_COUNT = MPQArchive.MAX_FILE_COUNT_MIN;
    private static final ByteOrder DATA_BYTE_ORDER        = ByteOrder.nativeOrder();
    
    private long                   mpqHandle              = 0L;
    private MPQAddFileCallback     addFileCallback        = null;
    private MPQCompactCallback     compactCallback        = null;
    
    /**
     * Tries to open the specified file as an MPQ or create a new MPQ, if the file cant be opened as an MPQ. If this
     * file already exists, try to open it as an MPQ, or create a new MPQ containing the file if its not an MPQ. If the
     * file doesnt exist, this creates a new MPQ with no content.
     * 
     * @param file the file to open as an MPQ.
     * @throws MPQFileNotFoundException in case the file cant be converted into an MPQ, eg. when the file is actually a
     *             directory.
     */
    public MPQArchive(String file) throws MPQFileNotFoundException {
        try {
            initializeOpen(file, new MPQArchiveOpenFlags());
        } catch (MPQException e) {
            initializeCreate(file, new MPQArchiveCreateFlags(), MPQArchive.DEFAULT_MAX_FILE_COUNT);
        }
    }
    
    /**
     * Tries to open the specified file as an MPQ or create a new MPQ, if the file cant be opened as an MPQ. If this
     * file already exists, try to open it as an MPQ, or create a new MPQ containing the file if its not an MPQ. If the
     * file doesnt exist, this creates a new MPQ with no content.
     * 
     * @param file the file to open as an MPQ.
     * @throws MPQFileNotFoundException in case the file cant be converted into an MPQ, eg. when the file is actually a
     *             directory.
     */
    public MPQArchive(File file) throws MPQFileNotFoundException {
        try {
            initializeOpen(file.getAbsolutePath(), new MPQArchiveOpenFlags());
        } catch (MPQException e) {
            initializeCreate(file.getAbsolutePath(), new MPQArchiveCreateFlags(), MPQArchive.DEFAULT_MAX_FILE_COUNT);
        }
    }
    
    /**
     * Tries to open the specified URL as an MPQ archive. <br>
     * This currently only works under Windows.
     * 
     * @param url the URL to open
     * @throws MPQFormatException in case the URL doesnt point to an MPQ archive
     * @throws MPQIsAVIException in case the URL points to an AVI file
     * @throws MPQFileNotFoundException in case the URL doesnt point to a file
     */
    public MPQArchive(URL url) throws MPQFormatException, MPQIsAVIException, MPQFileNotFoundException {
        MPQArchiveOpenFlags flags = new MPQArchiveOpenFlags();
        flags.setBaseProvider(MPQArchiveOpenFlags.BaseProvider.HTTP);
        initializeOpen(url.toString(), flags);
    }
    
    /**
     * Tries to open the specified file as an MPQ archive.
     * 
     * @param file the MPQ to open
     * @param flags the flags to open the MPQ with
     * @throws MPQFormatException in case the file is not a valid MPQ archive
     * @throws MPQIsAVIException in case the file is an AVI file
     * @throws MPQFileNotFoundException in case the file doesnt exist
     */
    public MPQArchive(String file, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException,
            MPQFileNotFoundException {
        initializeOpen(file, flags);
    }
    
    /**
     * Tries to open the specified file as an MPQ archive.
     * 
     * @param file the MPQ to open
     * @param flags the flags to open the MPQ with
     * @throws MPQFormatException in case the file is not a valid MPQ archive
     * @throws MPQIsAVIException in case the file is an AVI file
     * @throws MPQFileNotFoundException in case the file doesnt exist
     */
    public MPQArchive(File file, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException,
            MPQFileNotFoundException {
        initializeOpen(file.getAbsolutePath(), flags);
    }
    
    /**
     * Tries to open the specified URL as an MPQ archive.
     * 
     * @param url the MPQ to open
     * @param flags the flags to open the URL with
     * @throws MPQFormatException in case the URL doesnt point to a valid MPQ archive
     * @throws MPQIsAVIException in case the URL points to an AVI file
     * @throws MPQFileNotFoundException in case the URL doesnt point to a valid resource
     */
    public MPQArchive(URL url, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException,
            MPQFileNotFoundException {
        flags.setBaseProvider(MPQArchiveOpenFlags.BaseProvider.HTTP);
        initializeOpen(url.toString(), flags);
    }
    
    /**
     * Tries to create an MPQ archive either from scratch or by wrapping the specified file into an MPQ archive.
     * 
     * @param file the new MPQ archive
     * @param flags the flags to create the new MPQ with
     * @throws MPQAlreadyExistsException in case the specified file is already an MPQ archive
     * @throws MPQFileNotFoundException in case creating the MPQ archive failed
     */
    public MPQArchive(String file, MPQArchiveCreateFlags flags) throws MPQAlreadyExistsException,
            MPQFileNotFoundException {
        initializeCreate(file, flags, MPQArchive.DEFAULT_MAX_FILE_COUNT);
    }
    
    /**
     * Tries to create an MPQ archive either from scratch or by wrapping the specified file into an MPQ archive.
     * 
     * @param file the new MPQ archive
     * @param flags the flags to create the new MPQ with
     * @throws MPQAlreadyExistsException in case the specified file is already an MPQ archive
     * @throws MPQFileNotFoundException in case creating the MPQ archive failed
     */
    public MPQArchive(File file, MPQArchiveCreateFlags flags) throws MPQAlreadyExistsException,
            MPQFileNotFoundException {
        initializeCreate(file.getAbsolutePath(), flags, MPQArchive.DEFAULT_MAX_FILE_COUNT);
    }
    
    //
    
    private static native long createArchive(String name, int flags, int maxFileCount) throws MPQFileNotFoundException;
    
    private void initializeCreate(String file, MPQArchiveCreateFlags flags, int maxFileCount)
            throws MPQFileNotFoundException {
        this.mpqHandle = MPQArchive.createArchive(file, flags.getFlags(), maxFileCount);
    }
    
    //
    
    private static native long openArchive(String name, int flags) throws MPQFormatException, MPQIsAVIException,
            MPQFileNotFoundException;
    
    private void initializeOpen(String file, MPQArchiveOpenFlags flags) throws MPQFormatException, MPQIsAVIException,
            MPQFileNotFoundException {
        this.mpqHandle = MPQArchive.openArchive(file, flags.getFlags());
    }
    
    //
    
    private static native void addListFile(long mpq, String name);
    
    /**
     * Uses the specified file as an auxiliary listfile to detect names of files within the archive. This does not
     * modify the archive.
     * 
     * @param file the auxiliary listfile
     */
    public void addListFile(String file) {
        MPQArchive.addListFile(this.mpqHandle, file);
    }
    
    /**
     * Uses the specified file as an auxiliary listfile to detect names of files within the archive. This does not
     * modify the archive.
     * 
     * @param file the auxiliary listfile
     */
    public void addListFile(File file) {
        MPQArchive.addListFile(this.mpqHandle, file.getAbsolutePath());
    }
    
    //
    
    long getMpqHandle() {
        return this.mpqHandle;
    }
    
    //
    
    private static native void setLocale(int locale);
    
    /**
     * Changes the locale for adding files to archives and opening files within archives.
     * 
     * @param locale the new locale
     */
    public static void setLocale(MPQLocale locale) {
        MPQArchive.setLocale(locale.getValue());
    }
    
    //
    
    private static native int getNativeLocale();
    
    /**
     * Returns the locale for adding files to archives and opening files within archives.
     * 
     * @return the locale for MPQ operations
     */
    public static MPQLocale getLocale() {
        return MPQLocale.fromInteger(MPQArchive.getNativeLocale());
    }
    
    //
    
    private static native void flushArchive(long mpq);
    
    /**
     * Writes all changes to the archive to disk.
     */
    public void flush() {
        MPQArchive.flushArchive(this.mpqHandle);
    }
    
    //
    
    private static native void closeArchive(long mpq);
    
    /**
     * Closes the archive. All further operations on the archive will fail with an exception.
     */
    public void close() {
        MPQArchive.closeArchive(this.mpqHandle);
        this.mpqHandle = 0L;
    }
    
    //
    
    private static native void setMaxFileCount(long mpq, int maxFileCount);
    
    /**
     * Changes the maximum amount of files that can be stored within the archive.
     * 
     * @param maxFileCount the new limit of files that can be stored within the archive.
     */
    public void setMaxFileCount(int maxFileCount) {
        MPQArchive.setMaxFileCount(
                this.mpqHandle,
                Math.max(MPQArchive.MAX_FILE_COUNT_MIN, Math.min(maxFileCount, MPQArchive.MAX_FILE_COUNT_MAX)));
    }
    
    //
    
    private static native void compactArchive(long mpq, String listFile, boolean reserved)
            throws MPQPermissionException;
    
    /**
     * Starts a complete rebuild of the archive, essentially defragmenting the archive. This operation blocks until it
     * has finished and may block for long amounts of time if the archive is big.
     * 
     * @throws MPQPermissionException in case the archive was opened in read-only mode.
     * @see #setCompactCallback(MPQCompactCallback)
     */
    public void compactArchive() throws MPQPermissionException {
        this.compactArchive((String) null);
    }
    
    /**
     * Starts a complete rebuild of the archive, essentially defragmenting the archive. This operation blocks until it
     * has finished and may block for long amounts of time if the archive is big.
     * 
     * @param listFile additional, external listfile
     * @throws MPQPermissionException in case the archive was opened in read-only mode.
     * @see #setCompactCallback(MPQCompactCallback)
     */
    public void compactArchive(File listFile) throws MPQPermissionException {
        this.compactArchive(listFile.getAbsolutePath());
    }
    
    /**
     * Starts a complete rebuild of the archive, essentially defragmenting the archive. This operation blocks until it
     * has finished and may block for long amounts of time if the archive is big.
     * 
     * @param listFile additional, external listfile
     * @throws MPQPermissionException in case the archive was opened in read-only mode.
     * @see #setCompactCallback(MPQCompactCallback)
     */
    public void compactArchive(String listFile) throws MPQPermissionException {
        if (this.compactCallback != null)
            MPQArchive.setCompactCallback(this.mpqHandle, this.compactCallback);
        
        MPQArchive.compactArchive(this.mpqHandle, listFile, false);
    }
    
    private static void compactArchiveCallback(MPQCompactCallback callback, int workType, long bytesProcessed,
            long bytesTotal) {
        callback.compactCallback(MPQCompactWorkType.fromInteger(workType), bytesProcessed, bytesTotal);
    }
    
    //
    
    private static native void setCompactCallback(long mpq, MPQCompactCallback compactCallback);
    
    /**
     * The compact callback is called when compacting the archive. You should not execute blocking functions within this
     * callback.
     * 
     * @param compactCallback the new compact callback, or <code>null</code>.
     */
    public void setCompactCallback(MPQCompactCallback compactCallback) {
        this.compactCallback = compactCallback;
    }
    
    //
    
    private static native void openPatchArchive(long mpq, String name, String patchPathPrefix, int flags)
            throws MPQPermissionException, MPQFormatException, MPQIsAVIException;
    
    /**
     * Opens a file as a patch to the archive. The archive must have been opened in read-only mode. The patch archive
     * itself cannot be accessed directly.
     * 
     * @param file the MPQ to load as a patch
     * @param patchPathPrefix the prefix to remove from filenames of files within the patched archive
     * @throws MPQPermissionException in case the archive wasnt opened with read-only permissions
     * @throws MPQFormatException in case the patch arcive is not a valid MPQ archive
     * @throws MPQIsAVIException in case the patch archive is an AVI file
     */
    public void openPatchArchive(File file, String patchPathPrefix) throws MPQPermissionException, MPQFormatException,
            MPQIsAVIException {
        this.openPatchArchive(file.getAbsolutePath(), patchPathPrefix);
    }
    
    /**
     * Opens a file as a patch to the archive. The archive must have been opened in read-only mode. The patch archive
     * itself cannot be accessed directly.
     * 
     * @param file the MPQ to load as a patch
     * @param patchPathPrefix the prefix to remove from filenames of files within the patched archive
     * @throws MPQPermissionException in case the archive wasnt opened with read-only permissions
     * @throws MPQFormatException in case the patch arcive is not a valid MPQ archive
     * @throws MPQIsAVIException in case the patch archive is an AVI file
     */
    public void openPatchArchive(String file, String patchPathPrefix) throws MPQPermissionException,
            MPQFormatException, MPQIsAVIException {
        MPQArchive.openPatchArchive(this.mpqHandle, file, patchPathPrefix, 0);
    }
    
    //
    
    private static native boolean isPatchedArchive(long mpq);
    
    /**
     * Returns whether or not the current archive has patch archives attached to it.
     * 
     * @return <code>true</code> if the current archive has patches attached to it, <code>false</code> otherwise.
     */
    public boolean isPatchedArchive() {
        return MPQArchive.isPatchedArchive(this.mpqHandle);
    }
    
    //
    
    /**
     * Adds the specified file to the archive under the specified name.
     * 
     * @param fileName the file to add to the archive
     * @param archivedName the name of the file inside the archive
     * @throws MPQAlreadyExistsException in case the archive already contains a file with the specified name
     */
    public void addFile(String fileName, String archivedName) throws MPQAlreadyExistsException {
        addFile(fileName, archivedName, new MPQFileFlags(), new MPQCompressionFlags());
    }
    
    /**
     * Adds the specified file to the archive under the specified name.
     * 
     * @param fileName the file to add to the archive
     * @param archivedName the name of the file inside the archive
     * @param flags the flags to add the file with
     * @param compression in case the flags contain {@link MPQFileFlags.Compression#COMPRESS}, this specifies the
     *            compression to use.
     * @throws MPQAlreadyExistsException in case the archive already contains a file with the specified name
     */
    public void addFile(String fileName, String archivedName, MPQFileFlags flags, MPQCompressionFlags compression)
            throws MPQAlreadyExistsException {
        addFile(fileName, archivedName, flags, compression, compression);
    }
    
    /**
     * Adds the specified file to the archive under the specified name.
     * 
     * @param fileName the file to add to the archive
     * @param archivedName the name of the file inside the archive
     * @param flags the flags to add the file with
     * @param compression in case the flags contain {@link MPQFileFlags.Compression#COMPRESS}, this specifies the
     *            compression to use for the first block of data
     * @param compressionNext in case the flags contain {@link MPQFileFlags.Compression#COMPRESS}, this specifies the
     *            compression to use for all blocks of data except the first one
     * @throws MPQAlreadyExistsException in case the archive already contains a file with the specified name
     */
    public void addFile(String fileName, String archivedName, MPQFileFlags flags, MPQCompressionFlags compression,
            MPQCompressionFlags compressionNext) throws MPQAlreadyExistsException {
        
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
            int compressionNext) throws MPQAlreadyExistsException;
    
    private static void addFileCallback(MPQAddFileCallback callback, int bytesWritten, int bytesTotal, boolean finalCall) {
        callback.addFileCallback(bytesWritten, bytesTotal, finalCall);
    }
    
    //
    
    /**
     * Returns an {@link MPQFile} representing the file with the specified archived name contained in this MPQ archive.
     * 
     * @param archivedName the name of the file to open
     * @return an {@link MPQFile} representing the specified file
     */
    public MPQFile openFile(String archivedName) {
        return new MPQFile(this, archivedName, MPQFileOpenScope.MPQ);
    }
    
    //
    
    public MPQFile createFile(String name, long fileTime, int fileSize, MPQLocale locale, MPQFileFlags flags) {
        return new MPQFile(this, name, fileTime, fileSize, locale, flags);
    }
    
    public MPQFile createFile(String name, int fileSize, MPQFileFlags flags) {
        return createFile(name, 0L, fileSize, MPQLocale.DEFAULT, flags);
    }
    
    public MPQFile createFile(String name, int fileSize) {
        return createFile(name, 0L, fileSize, MPQLocale.DEFAULT, new MPQFileFlags());
    }
    
    //
    
    private static native void setAddFileCallback(long mpq, MPQAddFileCallback callbackObject);
    
    /**
     * Changes the callback that is called when adding files. You should not execute blocking functions within this
     * callback.
     * 
     * @param addFileCallback the new add file callback, or <code>null</code>
     */
    public void setAddFileCallback(MPQAddFileCallback addFileCallback) {
        this.addFileCallback = addFileCallback;
    }
    
    //
    
    private static native boolean hasFile(long mpq, String name);
    
    /**
     * Returns whether or not the archive contains a file with the specified name.
     * 
     * @param name the file to look for
     * @return <code>true</code> if the archive contains a file with that name, <code>false</code> otherwise
     */
    public boolean hasFile(String name) {
        return MPQArchive.hasFile(this.mpqHandle, name);
    }
    
    /**
     * Returns whether or not the archive contains the MPQ file.
     * 
     * @param name the file to look for
     * @return <code>true</code> if the archive contains the file, <code>false</code> otherwise
     */
    public boolean hasFile(MPQFile file) {
        if (this.mpqHandle == file.getContainingArchive().mpqHandle) {
            return this.hasFile(file.getArchivedName());
        }
        return false;
    }
    
    //
    
    private static native String getArchiveNameN(long mpq);
    
    private static native long getUserDataOffsetN(long mpq);
    
    private static native MPQUserDataHeader getUserDataHeaderN(long mpq);
    
    private static native byte[] getUserDataN(long mpq);
    
    private static native long getHeaderOffsetN(long mpq);
    
    private static native int getHeaderSizeN(long mpq);
    
    private static native MPQHeader getHeaderN(long mpq);
    
    private static native long getHetTableOffsetN(long mpq);
    
    private static native long getHetTableSizeN(long mpq);
    
    private static native MPQHetHeader getHetHeaderN(long mpq);
    
    private static native MPQHetTable getHetTableN(long mpq);
    
    private static native long getBetTableOffsetN(long mpq);
    
    private static native long getBetTableSizeN(long mpq);
    
    private static native MPQBetHeader getBetHeaderN(long mpq);
    
    private static native MPQBetTable getBetTableN(long mpq);
    
    private static native int getArchiveSizeN(long mpq);
    
    private static native int getHashTableSizeN(long mpq);
    
    private static native int getBlockTableSizeN(long mpq);
    
    private static native MPQHash[] getMPQDataN(long mpq);
    
    private static native int getSectorSizeN(long mpq);
    
    private static native int getFilesCountN(long mpq);
    
    private static native boolean isReadOnlyN(long mpq);
    
    /**
     * Returns the archives name
     * 
     * @return the name of the archive
     */
    public String getArchiveName() {
        return getArchiveNameN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private long getUserDataOffset() {
        return getUserDataOffsetN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private MPQUserDataHeader getUserDataHeader() {
        return getUserDataHeaderN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private byte[] getUserData() {
        return getUserDataN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private long getHeaderOffset() {
        return getHeaderOffsetN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private int getHeaderSize() {
        return getHeaderSizeN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private MPQHeader getHeader() {
        return getHeaderN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private long getHetTableOffset() {
        return getHetTableOffsetN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private long getHetTableSize() {
        return getHetTableSizeN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private MPQHetHeader getHetHeader() {
        return getHetHeaderN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private MPQHetTable getHetTable() {
        return getHetTableN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private long getBetTableOffset() {
        return getBetTableOffsetN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private long getBetTableSize() {
        return getBetTableSizeN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private MPQBetHeader getBetHeader() {
        return getBetHeaderN(this.mpqHandle);
    }
    
    /**
     * 
     * @return
     */
    private MPQBetTable getBetTable() {
        return getBetTableN(this.mpqHandle);
    }
    
    /**
     * Returns the size of the archive, as given in the archives header.
     * 
     * @return the size of the archive
     */
    public int getArchiveSize() {
        return getArchiveSizeN(this.mpqHandle);
    }
    
    /**
     * Returns the number of entries in the archives hash table.
     * 
     * @return the number of entries in the archives hash table
     */
    public int getHashTableSize() {
        return getHashTableSizeN(this.mpqHandle);
    }
    
    /**
     * Returns the number of entries in the archives block table.
     * 
     * @return the number of entries in the archives block table
     */
    public int getBlockTableSize() {
        return getBlockTableSizeN(this.mpqHandle);
    }
    
    /**
     * Returns the size of one file sector within the archive in bytes.
     * 
     * @return the size of one file sector within the archive in bytes
     */
    public int getSectorSize() {
        return getSectorSizeN(this.mpqHandle);
    }
    
    /**
     * Returns the number of files in the archive.
     * 
     * @return the number of files in the archive
     */
    public int getFilesCount() {
        return getFilesCountN(this.mpqHandle);
    }
    
    /**
     * Returns a copy of the archives hash table. Every hash contains a non-null reference to a block.
     * 
     * @return a copy of the archives hash table
     */
    public MPQHash[] getMPQData() {
        return getMPQDataN(this.mpqHandle);
    }
    
    //
    
    private static native int verifyFile(long mpq, String fileName, int flags);
    
    /**
     * Verifies the readability and various signatures of the specified file.
     * 
     * @param fileName the file to verify
     * @param flags which signatures to verify
     * @return result of each individual check.
     */
    public MPQVerifyFileResults verifyFile(String fileName, MPQVerifyFileFlags flags) {
        MPQVerifyFileResults results = new MPQVerifyFileResults();
        results.fromInteger(MPQArchive.verifyFile(this.mpqHandle, fileName, flags.getFlagsAsInt()));
        return results;
    }
    
    //
    
    private static native int verifyArchive(long mpq);
    
    /**
     * Verifies the digital signature of the archive.<br>
     * <br>
     * MPQs created by JStormLib are never signed.
     * 
     * @return the strength of the signature (if any) and whether the signature was successfully verified.
     */
    public MPQVerifyArchiveResult verify() {
        return MPQVerifyArchiveResult.fromInteger(MPQArchive.verifyArchive(this.mpqHandle));
    }
    
    //
    
    private static native void extractFile(long mpq, String toExtract, String extracted, int searchScope)
            throws MPQFileNotFoundException;
    
    /**
     * Extract a single file from within the archive to the specified destination.
     * 
     * @param toExtract the name of the file you want to extract from the archive
     * @param extracted the file you want to extract the data to. Overwrites existing files.
     * @throws MPQFileNotFoundException in case either of the parameters are not valid files.
     */
    public void extractFile(String toExtract, File extracted) throws MPQFileNotFoundException {
        this.extractFile(toExtract, extracted.getAbsolutePath());
    }
    
    /**
     * Extract a single file from within the archive to the specified destination.
     * 
     * @param toExtract the name of the file you want to extract from the archive.
     * @param extracted the file you want to extract the data to. Overwrites existing files.
     * @throws MPQFileNotFoundException in case either of the parameters are not valid files.
     */
    public void extractFile(String toExtract, String extracted) throws MPQFileNotFoundException {
        MPQArchive.extractFile(this.mpqHandle, toExtract, extracted, MPQSearchScope.MPQ.getValue());
    }
    
    //
    
    /**
     * Searches through the file names of all known files within this MPQ archive for the specified mask
     * 
     * @param mask the mask to look for
     * @return an iterator over all files found
     */
    public MPQSearch find(String mask) {
        return find(mask, null);
    }
    
    /**
     * Adds the specified listfile to the archive, then searches through the file names of all known files within this
     * MPQ archive for the specified mask.
     * 
     * @param mask the mask to look for
     * @param listFile the listfile to add to the archive before starting the search
     * @return an iterator over all files found
     */
    public MPQSearch find(String mask, String listFile) {
        MPQSearch search = new MPQSearch();
        MPQFindData data = new MPQFindData();
        search.type = SearchType.NORMAL;
        try {
            search.searchHandle = MPQArchive.findFirstFile(this.mpqHandle, mask, data, listFile);
            search.next = data;
        } catch (MPQFileNotFoundException fnfe) {
            search.searchHandle = 0L;
            search.next = null;
        }
        return search;
    }
    
    private static native long findFirstFile(long mpq, String mask, MPQFindData fileFindData, String listFile)
            throws MPQFileNotFoundException;
    
    /**
     * Searches for the sepcified mask within the listfile of this MPQ archive.
     * 
     * @param mask the mask to look for
     * @return an iterator over all files found
     */
    public MPQSearch listFind(String mask) {
        MPQSearch search = new MPQSearch();
        MPQFindData data = new MPQFindData();
        search.type = SearchType.LISTFILE;
        try {
            search.searchHandle = MPQArchive.listFindFirstFile(this.mpqHandle, null, mask, data);
            search.next = data;
        } catch (MPQFileNotFoundException fnfe) {
            search.searchHandle = 0L;
            search.next = null;
        }
        return search;
    }
    
    /**
     * Searches for the specified mask within the specified listfile.
     * 
     * @param mask the mask to look for
     * @param listFile the listfile to search through
     * @return an iterator over all files found
     */
    public static MPQSearch listFind(String mask, String listFile) {
        MPQSearch search = new MPQSearch();
        MPQFindData data = new MPQFindData();
        search.type = SearchType.LISTFILE;
        try {
            search.searchHandle = MPQArchive.listFindFirstFile(0L, listFile, mask, data);
            search.next = data;
        } catch (MPQFileNotFoundException fnfe) {
            search.searchHandle = 0L;
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
            System.loadLibrary("JStormLib64");
        } else {
            // running 32 bit JVM, probably
            System.loadLibrary("JStormLib32");
        }
    }
}
