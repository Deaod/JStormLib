package de.deaod.jstormlib;

import java.util.Iterator;

import de.deaod.jstormlib.data.MPQFindData;
import de.deaod.jstormlib.exceptions.MPQFileNotFoundException;

public class MPQSearch implements AutoCloseable, Iterator<MPQFindData> {
    long        searchHandle;
    MPQFindData next;
    
    enum SearchType {
        NORMAL,
        LISTFILE;
    }
    
    SearchType type = SearchType.NORMAL;
    
    MPQSearch() {
    }
    
    private static native boolean findNextFile(long search, MPQFindData findFileData) throws MPQFileNotFoundException;
    
    private static native boolean findClose(long search);
    
    private static native boolean listFindNextFile(long search, MPQFindData findFileData)
            throws MPQFileNotFoundException;
    
    private static native boolean listFindClose(long search);
    
    @Override
    public boolean hasNext() {
        return this.next != null;
    }
    
    @Override
    public MPQFindData next() {
        if (this.next == null)
            return null;
        MPQFindData next = this.next;
        this.next = new MPQFindData();
        try {
            switch (this.type) {
                case NORMAL:
                    MPQSearch.findNextFile(this.searchHandle, this.next);
                    break;
                case LISTFILE:
                    MPQSearch.listFindNextFile(this.searchHandle, this.next);
                    break;
            }
        } catch (MPQFileNotFoundException fnfe) {
            this.next = null;
        }
        return next;
    }
    
    /**
     * Not supported by MPQSearch. Always throws UnsupportedOperationException.
     * 
     * @see UnsupportedOperationException
     */
    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
    
    @Override
    public void close() {
        if (this.searchHandle > 0) {
            switch (this.type) {
                case NORMAL:
                    MPQSearch.findClose(this.searchHandle);
                    break;
                case LISTFILE:
                    MPQSearch.listFindClose(this.searchHandle);
                    break;
            }
            this.searchHandle = 0;
        }
    }
    
    @Override
    protected void finalize() throws Throwable {
        close();
        super.finalize();
    }
}
