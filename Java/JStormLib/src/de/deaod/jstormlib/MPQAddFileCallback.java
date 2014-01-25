package de.deaod.jstormlib;

/**
 * Callback interface for use when you want to receive information about the progress of adding a file to an MPQ
 * archive. For example, when you have a GUI and want to display progress to the user.
 * 
 * @author Deaod <deaod@deaod.de>
 * 
 */
public interface MPQAddFileCallback {
    /**
     * Callback called while a file is being added to an MPQ archive. <br>
     * Implementations should not block or repaint an interface within this function.
     * 
     * @param bytesWritten the amount of bytes that have already been written to the archive
     * @param bytesTotal the amount of bytes that have to be written in total to the archive
     * @param finalCall is <code>true</code> when the current callback is the last while adding a file to the archive.
     */
    public void addFileCallback(int bytesWritten, int bytesTotal, boolean finalCall);
}
