/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2008 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem.ds;

import WIMSchem.*;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.table.*;
import javax.swing.border.*;

/*
    Data model to reconcile a DataSheet instance with the editing performed by a JTable component.
*/

public class DataTableModel extends AbstractTableModel 
{
    // Class implemented specially to draw molecules on a table.

    class MoleculeRenderer extends EditorPane implements TableCellRenderer
    {
	Border focusBorder=null;

	public MoleculeRenderer() 
	{
            setOpaque(true);

	    SetEditable(false);
	    SetAutoScale(true);
	}

	public Component getTableCellRendererComponent(JTable table,Object mol,boolean isSelected,boolean hasFocus,int row,int col)
	{
    	    if (mol!=null) this.Replace((Molecule)mol); else this.Clear();

    	    setBackground(isSelected ? table.getSelectionBackground() : table.getBackground());

    	    //SetBorder(hasFocus);
	    if (hasFocus) 
	    {
    		if (focusBorder==null) 
		    focusBorder=BorderFactory.createMatteBorder(1,1,1,1,table.getSelectionBackground().darker());
        	setBorder(focusBorder);
	    }
	    else setBorder(null);

	    return this;
	}
    }
    public MoleculeRenderer NewMoleculeRenderer() {return new MoleculeRenderer();}
    
    // Class implemented for editing of molecules: just sends an event notice to the parent, rather than actually doing the work.
    
    class MoleculeEditor extends AbstractCellEditor implements TableCellEditor
    {
    	ActionListener actlist;
    
    	public MoleculeEditor(ActionListener ActList)
	{
	    actlist=ActList;
	}
	
	public Component getTableCellEditorComponent(JTable table,Object value,boolean isSelected,int row,int col) 
	{
	    actlist.actionPerformed(new ActionEvent(table,0,row+","+col));
    	    fireEditingStopped();
	    return null;
	}
	public Object getCellEditorValue() {return null;}
    }
    //JOptionPane.showMessageDialog(null,e.toString(),"Clipboard Read Failed",JOptionPane.ERROR_MESSAGE);
    public MoleculeEditor NewMoleculeEditor(ActionListener ActList) {return new MoleculeEditor(ActList);}

    // main implementation

    DataSheet ds=null;
    DataSheetCache cache=null;
    int temporaryEdit=-1;

    public DataTableModel(DataSheet DS,DataSheetCache Cache) {ds=DS; cache=Cache;}
    public void SetDataSheet(DataSheet DS,DataSheetCache Cache) {ds=DS; cache=Cache;}
    
    public void SetTemporaryEdit(int Col) {temporaryEdit=Col;}
    public void ClearTemporaryEdit() {temporaryEdit=-1;}
    
    public int getColumnCount() {return ds.NumCols();}
    public int getRowCount() {return ds.NumRows();}
    public String getColumnName(int col) {return ds.ColName(col);}
    public Object getValueAt(int row,int col) 
    {
    	int t=ds.ColType(col);
	if (ds.IsNull(row,col))
	{
	    if (t==DataSheet.COLTYPE_MOLECULE) return null;
	    if (t==DataSheet.COLTYPE_BOOLEAN) return new Boolean(false); // (no UI concept of null)
	    return ""; // null
	}
	else
	{
	    if (t==DataSheet.COLTYPE_MOLECULE) return ds.GetMolecule(row,col);
	    if (t==DataSheet.COLTYPE_STRING) return ds.GetString(row,col);
	    if (t==DataSheet.COLTYPE_INTEGER) return new Integer(ds.GetInteger(row,col));
	    if (t==DataSheet.COLTYPE_REAL) return new Double(ds.GetReal(row,col));
	    if (t==DataSheet.COLTYPE_BOOLEAN) return new Boolean(ds.GetBoolean(row,col));
	}
	return "";
    }
    public Class getColumnClass(int col) 
    {
    	int t=ds.ColType(col);
	if (t==DataSheet.COLTYPE_MOLECULE) return new Molecule().getClass();
	if (t==DataSheet.COLTYPE_STRING) return new String("").getClass();
	if (t==DataSheet.COLTYPE_INTEGER) return new String("").getClass();
	if (t==DataSheet.COLTYPE_REAL) return new String("").getClass();
	if (t==DataSheet.COLTYPE_BOOLEAN) return new Boolean(false).getClass();
	return new String("").getClass();
    }
    public boolean isCellEditable(int row,int col) 
    {
    	// (molecule only) return temporaryEdit==col || ds.ColType(col)!=DataSheet.COLTYPE_MOLECULE;
	return temporaryEdit==col;
    }
    public void setValueAt(Object val,int row,int col) 
    {
    	int t=ds.ColType(col);
	try
	{
	    cache.CacheUndo(ds);
	
	    if (t==DataSheet.COLTYPE_MOLECULE) ds.SetMolecule(row,col,(Molecule)val);
	    else if (t==DataSheet.COLTYPE_STRING) ds.SetString(row,col,(String)val);
	    else if (t==DataSheet.COLTYPE_INTEGER) 
	    {
	    	String str=(String)val;
		if (str.length()==0) ds.SetToNull(row,col);
	    	else ds.SetInteger(row,col,Integer.parseInt(str));
	    }
	    else if (t==DataSheet.COLTYPE_REAL) 
	    {
	    	String str=(String)val;
		if (str.length()==0) ds.SetToNull(row,col);
		else ds.SetReal(row,col,Double.parseDouble(str));
	    }
	    else if (t==DataSheet.COLTYPE_BOOLEAN) ds.SetBoolean(row,col,((Boolean)val).booleanValue());
	    
	    ds.SetDirty();
	}
	catch (NumberFormatException ex) {} // (do nothing --> change gets rejected)
    }
    
    // normally implemented in JTable, but passed along to this class; returns default editing/rendering properties for unit datatypes,
    // and a special one for molecules...
    public TableCellRenderer getCellRenderer(int row,int col,TableCellRenderer def) 
    {
    	if (ds.ColType(col)==DataSheet.COLTYPE_MOLECULE)
	{
	    // !! if column height is set to one-line, use a 'molecular formula' renderer...
	    return new MoleculeRenderer();
	}
	
    	return def;
    }
}



