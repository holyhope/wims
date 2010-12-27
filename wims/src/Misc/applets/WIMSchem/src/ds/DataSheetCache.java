/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2008 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem.ds;

import WIMSchem.*;

import java.io.*;
import java.util.*;

/*
    Caching system for DataSheet instances, which is intended for undo/redo purposes.
    
    NOTE: current implementation is very inefficient, as it stores a copy of the datasheet for every undo/redo instance.
    At some point this should be rewritten to store differences.
*/

public class DataSheetCache
{
    private final int MAX_UNDO=10;
    private Stack<String> undo=new Stack<String>(),redo=new Stack<String>();
    
    public DataSheetCache()
    {
    }
        
    public boolean CanUndo() {return !undo.empty();}
    public boolean CanRedo() {return !redo.empty();}
    
    /* !! figure something out...
    public void NotifySaved() {saveidx=curidx;}
    public boolean IsSaved() {return curidx==saveidx;}*/
    
    public void CacheUndo(DataSheet DS)
    {
    	String str=ToString(DS);
	undo.push(str);
    	while (undo.size()>MAX_UNDO) undo.remove(0);
	redo.clear();
    }
    
    public DataSheet PerformUndo(DataSheet Cur)
    {
    	if (undo.empty()) return null;
	redo.push(ToString(Cur));
	return FromString(undo.pop());
    }
    
    public DataSheet PerformRedo(DataSheet Cur)
    {
    	if (redo.empty()) return null;
	undo.push(ToString(Cur));
	return FromString(redo.pop());
    }
    
    private String ToString(DataSheet DS)
    {
	StringWriter sw=new StringWriter();
	try {DataSheetStream.WriteXML(new BufferedWriter(sw),DS);}
	catch (IOException e) {return null;}
	return sw.toString();
    }
    
    private DataSheet FromString(String StrDS)
    {
    	DataSheet ds=null;
	try
	{
	    if (DataSheetStream.ExamineIsXMLDS(new BufferedReader(new StringReader(StrDS))))
		ds=DataSheetStream.ReadXML(new BufferedReader(new StringReader(StrDS)));
	}
	catch (IOException e) {e.printStackTrace();}
	return ds;
    }
}
