package de.deaod.jstormlib;

public interface MPQCompactCallback {
    public void compactCallback(MPQWorkType workType, long bytesProcessed, long bytesTotal);
}
