package de.deaod.jstormlib;

import java.util.Iterator;

import de.deaod.jstormlib.data.MPQFindData;
import de.deaod.jstormlib.exceptions.MPQFileNotFoundException;

public class MPQSearch implements Iterator<MPQFindData> {
    long        search;
    MPQFindData next;
    
    enum SearchType {
        NORMAL,
        LISTFILE;
    }
    
    SearchType type = SearchType.NORMAL;
    
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
                    MPQSearch.findNextFile(this.search, this.next);
                    break;
                case LISTFILE:
                    MPQSearch.listFindNextFile(this.search, this.next);
                    break;
            }
        } catch (MPQFileNotFoundException fnfe) {
            this.next = null;
        }
        return next;
    }
    
    /**
     * Not supported by MPQSearch; always throws UnsupportedOperationException.
     * 
     * @see UnsupportedOperationException
     */
    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
    
    @Override
    protected void finalize() throws Throwable {
        switch (this.type) {
            case NORMAL:
                MPQSearch.findClose(this.search);
                break;
            case LISTFILE:
                MPQSearch.listFindClose(this.search);
                break;
        }
        super.finalize();
    }
}
