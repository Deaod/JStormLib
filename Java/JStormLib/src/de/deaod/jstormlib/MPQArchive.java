package de.deaod.jstormlib;

import java.io.File;
import java.net.URL;

import de.deaod.jstormlib.exceptions.MPQAlreadyExistsException;
import de.deaod.jstormlib.exceptions.MPQException;
import de.deaod.jstormlib.exceptions.MPQFormatException;
import de.deaod.jstormlib.exceptions.MPQIsAVIException;
import de.deaod.jstormlib.exceptions.MPQPermissionException;

public class MPQArchive {
    private static final int   MAX_FILE_COUNT_MIN     = 0x00000004;
    private static final int   MAX_FILE_COUNT_MAX     = 0x00080000;
    private static final int   DEFAULT_MAX_FILE_COUNT = MPQArchive.MAX_FILE_COUNT_MIN;
    
    private long               mpqHandle              = 0L;
    private MPQAddFileCallback addFileCallback        = null;
    private MPQCompactCallback compactCallback        = null;
    
    public MPQArchive(String file) {
        try {
            initializeOpen(file, new MPQOpenFlags());
        } catch (MPQException e) {
            initializeCreate(new File(file), new MPQCreateFlags(), MPQArchive.DEFAULT_MAX_FILE_COUNT);
        }
    }
    
    public MPQArchive(File file) {
        try {
            initializeOpen(file.getAbsolutePath(), new MPQOpenFlags());
        } catch (MPQException e) {
            initializeCreate(file, new MPQCreateFlags(), MPQArchive.DEFAULT_MAX_FILE_COUNT);
        }
    }
    
    public MPQArchive(URL url) throws MPQFormatException, MPQIsAVIException {
        MPQOpenFlags flags = new MPQOpenFlags();
        flags.setBaseProvider(MPQOpenFlags.BaseProvider.HTTP);
        initializeOpen(url.toString(), flags);
    }
    
    public MPQArchive(String file, MPQOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        initializeOpen(file, flags);
    }
    
    public MPQArchive(File file, MPQOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        initializeOpen(file.getAbsolutePath(), flags);
    }
    
    public MPQArchive(URL url, MPQOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
        flags.setBaseProvider(MPQOpenFlags.BaseProvider.HTTP);
        initializeOpen(url.toString(), flags);
    }
    
    public MPQArchive(String file, MPQCreateFlags flags) throws MPQAlreadyExistsException {
        initializeCreate(new File(file), flags, MPQArchive.DEFAULT_MAX_FILE_COUNT);
    }
    
    public MPQArchive(File file, MPQCreateFlags flags) throws MPQAlreadyExistsException {
        initializeCreate(file, flags, MPQArchive.DEFAULT_MAX_FILE_COUNT);
    }
    
    //
    
    private static native long createArchive(String name, int flags, int maxFileCount);
    
    private void initializeCreate(File file, MPQCreateFlags flags, int maxFileCount) {
        this.mpqHandle = MPQArchive.createArchive(file.getAbsolutePath(), flags.getFlags(), maxFileCount);
    }
    
    //
    
    private static native long openArchive(String name, int flags) throws MPQFormatException, MPQIsAVIException;
    
    private void initializeOpen(String file, MPQOpenFlags flags) throws MPQFormatException, MPQIsAVIException {
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
    
    private static native void setLocale(int locale);
    
    public static void setLocale(MPQLocale locale) {
        MPQArchive.setLocale(locale.getValue());
    }
    
    //
    
    private static native int getNativeLocale();
    
    public static MPQLocale getLocale() {
        return MPQLocale.getLocaleFromInteger(MPQArchive.getNativeLocale());
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
    
    public void addFile(String fileName, String archivedName, MPQAddFileFlags flags, MPQCompression compression) {
        addFile(fileName, archivedName, flags, compression, compression);
    }
    
    public void addFile(String fileName, String archivedName, MPQAddFileFlags flags, MPQCompression compression,
            MPQCompression compressionNext) {
        if (this.addFileCallback != null)
            MPQArchive.setAddFileCallback(this.mpqHandle, this.addFileCallback);
        
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
    
    //
    
    private static native void setAddFileCallback(long mpq, MPQAddFileCallback callbackObject);
    
    public void setAddFileCallback(MPQAddFileCallback addFileCallback) {
        this.addFileCallback = addFileCallback;
    }
    
    //
    
    private static native long createFile(long mpq, String archivedName, long fileTime, int fileSize, int locale,
            int flags);
    
    private static native boolean openFile(long mpq, String name, int scope, long[] file);
    
    private static native boolean hasFile(long mpq, String name);
    
    private static native boolean renameFile(long mpq, String oldFileName, String newFileName);
    
    private static native boolean removeFile(long mpq, String fileName, int searchScope);
    
    private static native boolean getArchiveInfo(long mpq, int infoType, byte[] data, int dataMaxSize, Integer dataSize);
    
    //
    
    private static native int verifyFile(long mpq, String fileName, int flags);
    
    public MPQVerifyFileResults verifyFile(String fileName, MPQVerifyFileFlags flags) {
        MPQVerifyFileResults results = new MPQVerifyFileResults();
        results.setFlagsFromInt(MPQArchive.verifyFile(this.mpqHandle, fileName, flags.getFlagsAsInt()));
        return results;
    }
    
    //
    
    private static native int verifyArchive(long mpq);
    
    public MPQVerifyArchiveResult verify() {
        return MPQVerifyArchiveResult.getFromInt(MPQArchive.verifyArchive(this.mpqHandle));
    }
    
    //
    
    private static native boolean extractFile(long mpq, String toExtract, String extracted, int searchScope);
    
    public void extractFile(String toExtract, File extracted) {
        this.extractFile(toExtract, extracted.getAbsolutePath());
    }
    
    public void extractFile(String toExtract, String extracted) {
        MPQArchive.extractFile(this.mpqHandle, toExtract, extracted, MPQSearchScope.MPQ.getValue());
    }
    
    //
    
    private static native long findFirstFile(long mpq, String mask, MPQFindData fileFindData, String listFile);
    
    private static native long listFindFirstFile(long mpq, String listFile, String mask, MPQFindData fileFindData);
    
    @Override
    protected void finalize() {
        if (this.mpqHandle != 0L) {
            close();
        }
    }
    
    static {
        System.loadLibrary("jStormLib.dll");
    }
}
