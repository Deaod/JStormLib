package de.deaod.jstormlib.exceptions;

public class MPQNoMoreFilesException extends MPQException {
    
    /**
     * 
     */
    private static final long serialVersionUID = 7582646162204055032L;
    
    public MPQNoMoreFilesException() {
        super();
    }
    
    public MPQNoMoreFilesException(String msg) {
        super(msg);
    }
}
