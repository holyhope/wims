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
    DataSheet is a container class for storing a row/column format collection of molecular data. 
    This implementation stores the entirety of
    the collection in memory, and is not intended to be used for large datasets. 
    Its file format is expected to be an XML format, or 
    imported/exported from various others, such as SD files.
*/

public class DataSheet
{
    public static final int COLTYPE_MOLECULE=1;
    public static final int COLTYPE_STRING=2;
    public static final int COLTYPE_INTEGER=3;
    public static final int COLTYPE_REAL=4;
    public static final int COLTYPE_BOOLEAN=5;
    
    class Column
    {
    	String Name;
	int Type;
	String Descr;
    }
    private ArrayList<Column> cols=new ArrayList<Column>();
    private ArrayList<Object[]> rows=new ArrayList<Object[]>();

    private boolean isDirty=false;

    public DataSheet()
    {
    }
    
    public int NumCols() {return cols.size();}
    public int NumRows() {return rows.size();}
    
    public static String TypeName(int Type) 
    {
	return Type==DataSheet.COLTYPE_MOLECULE ? "molecule" :
	       Type==DataSheet.COLTYPE_STRING ? "string" :
	       Type==DataSheet.COLTYPE_REAL ? "real" :
	       Type==DataSheet.COLTYPE_INTEGER ? "integer" :
	       Type==DataSheet.COLTYPE_BOOLEAN ? "boolean" : "?";
    }
    
    public boolean IsDirty() {return isDirty;}
    public void SetDirty() {isDirty=true;}
    public void ClearDirty() {isDirty=false;}
    
    // reading column info
    public String ColName(int N) {return cols.get(N).Name;}
    public int ColType(int N) {return cols.get(N).Type;}
    public String ColDescr(int N) {return cols.get(N).Descr;}
    
    // returns whether a cell is null; should always be checked for primitive types
    public boolean IsNull(int RN,int CN) {return (rows.get(RN))[CN]==null;}

    // fetching row data; note that the correct type must be use, else exception
    public Molecule GetMolecule(int RN,int CN) {return (Molecule)(rows.get(RN))[CN];}
    public String GetString(int RN,int CN) {return (String)(rows.get(RN))[CN];}
    public int GetInteger(int RN,int CN) {return ((Integer)(rows.get(RN))[CN]).intValue();}
    public double GetReal(int RN,int CN) {return ((Double)(rows.get(RN))[CN]).doubleValue();}
    public boolean GetBoolean(int RN,int CN) {return ((Boolean)(rows.get(RN))[CN]).booleanValue();}

    // gets the untyped object for a cell; use with care
    public Object GetObject(int RN,int CN) {return (rows.get(RN))[CN];}

    // sets a cell to null, which is valid for all types
    public void SetToNull(int RN,int CN) {(rows.get(RN))[CN]=null;}

    // setting row data; fails silently if the type is wrong
    public void SetMolecule(int RN,int CN,Molecule V) {if (ColType(CN)==COLTYPE_MOLECULE) (rows.get(RN))[CN]=V==null ? V : V.Clone();}
    public void SetString(int RN,int CN,String V) {if (ColType(CN)==COLTYPE_STRING) (rows.get(RN))[CN]=V;}
    public void SetInteger(int RN,int CN,int V) {if (ColType(CN)==COLTYPE_INTEGER) (rows.get(RN))[CN]=new Integer(V);}
    public void SetReal(int RN,int CN,double V) {if (ColType(CN)==COLTYPE_REAL) (rows.get(RN))[CN]=new Double(V);}
    public void SetBoolean(int RN,int CN,boolean V) {if (ColType(CN)==COLTYPE_BOOLEAN) (rows.get(RN))[CN]=new Boolean(V);}

    // sets the object for a cell, without any type checking; use with care
    public void SetObject(int RN,int CN,Object V) {(rows.get(RN))[CN]=V;}
    
    // appends a new column to the end of the list, and updates the underlying data accordingly
    public int AppendColumn(String Name,int Type,String Descr)
    {
    	Column c=new Column();
	c.Name=Name;
	c.Type=Type;
	c.Descr=Descr;
	cols.add(c);
	for (int n=0;n<rows.size();n++)
	{
	    Object[] d1=rows.get(n);
	    Object[] d2=new Object[d1.length+1];
	    for (int i=0;i<d1.length;i++) d2[i]=d1[i];
	    d2[d1.length]=null;
	    rows.set(n,d2);
	}
	return cols.size()-1;
    }
    
    // appends a row containing all-nulls to the end of the list, and returns the new index position
    public int AppendRow()
    {
    	rows.add(new Object[cols.size()]);
	return rows.size()-1;
    }
    
    public void DeleteRow(int RN) {rows.remove(RN);}
    
    // removes a column, and adjusts all the data accordingly
    public void DeleteColumn(int CN) 
    {
    	cols.remove(CN);
	for (int n=0;n<rows.size();n++)
	{
	    Object[] prev=rows.get(n),cur=new Object[cols.size()-1];
	    for (int i=0,j=0;i<prev.length;i++) if (i!=CN) cur[j++]=prev[i];
	    rows.set(n,cur);
	}
    }
    
    // modifies name and/or description (null=do nothing)
    public void ChangeColumnName(int CN,String Name,String Descr)
    {
    	Column c=cols.get(CN);
    	if (Name!=null) c.Name=Name;
	if (Descr!=null) c.Descr=Descr;
    }
    
    // dynamically modifies the column type, correcting the existing data and reformulating; returns true if the conversion was
    // successful (for example, can't switch between molecule & other); if Force is set, then incompatible conversions will result
    // in null, otherwise the operation will fail
    public boolean ChangeColumnType(int CN,int NewType,boolean Force)
    {
    	if (CN<0 || CN>=NumCols()) return false;
    	if (ColType(CN)==NewType) return true;
	
	boolean incompatible=ColType(CN)==COLTYPE_MOLECULE || NewType==COLTYPE_MOLECULE;
	if (incompatible && !Force) return false;
	
	Column col=cols.get(CN);
	int prevType=col.Type;
	col.Type=NewType;
	
	for (int n=0,nrows=rows.size();n<nrows;n++)
	{
	    Object[] row=rows.get(n);
	    
	    if (row[CN]==null) continue;
	    if (incompatible) {row[CN]=null; continue;}
	    
	    String val="";
	    if (prevType==COLTYPE_STRING) val=(String)row[CN];
	    else if (prevType==COLTYPE_INTEGER) val=String.valueOf(((Integer)row[CN]).intValue());
	    else if (prevType==COLTYPE_REAL) val=String.valueOf(((Double)row[CN]).intValue());
	    else if (prevType==COLTYPE_BOOLEAN) val=((Boolean)row[CN]).booleanValue() ? "true" : "false";
	    
    	    row[CN]=null;
	    
	    try
	    {
	    	if (NewType==COLTYPE_STRING) row[CN]=val;
		else if (NewType==COLTYPE_INTEGER) row[CN]=new Integer(val);
		else if (NewType==COLTYPE_REAL) row[CN]=new Double(val);
		else if (NewType==COLTYPE_BOOLEAN) row[CN]=val.toLowerCase().compareTo("true")==0 ? Boolean.TRUE : Boolean.FALSE;
	    }
	    catch (NumberFormatException e) {} // stays null
	}
	
	return true;
    }
    
    // reorders the columns; each value of Order[n] defines the index into the original list which this should now be
    public void ReorderColumns(int[] Order)
    {
    	boolean identity=true;
    	for (int n=0;n<Order.length-1;n++) if (Order[n]!=Order[n+1]+1) {identity=false; break;}
	if (identity) return; // nothing to do
	
    	ArrayList<Column> newcols=new ArrayList<Column>();
	for (int n=0;n<cols.size();n++) newcols.add(cols.get(Order[n]));
	cols=newcols;
	
	for (int n=0;n<rows.size();n++)
	{
	    Object[] row=rows.get(n),newrow=new Object[row.length];
	    for (int i=0;i<row.length;i++) newrow[i]=row[Order[i]];
	    rows.set(n,newrow);
	}
    }
}


