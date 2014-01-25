package de.deaod.jstormlib;

/**
 * Callback interface for use when you want to receive progress information about compacting an MPQ archive.
 * 
 * @author Deaod <deaod@deaod.de>
 * 
 */
public interface MPQCompactCallback {
    /**
     * Callback called while an MPQ archive is being compacted.<br>
     * Implementations should not block or repaint an interface within this function.
     * 
     * @param workType the type of work currently being done while compacting
     * @param bytesProcessed the amount of bytes that have already been processed for the current work
     * @param bytesTotal the total amount of bytes that need to be processed for the current work
     */
    public void compactCallback(MPQCompactWorkType workType, long bytesProcessed, long bytesTotal);
}
