/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2008 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem.ds;

import WIMSchem.*;

import java.io.*;
import java.awt.*;
import java.util.*;
import java.awt.image.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.*;

/*
    Main window for datasheet viewing & editing.
*/

public class DataWindow extends JFrame implements ActionListener, WindowListener, KeyListener
{
    public static final boolean ALLOW=true; // temporary: disable DataSheet use while development is in-progress

    String filename=null;
    JSplitPane splitter=null;
    DataSheet ds=null;
    DataSheetCache cache=null;
    DataTableModel model=null;
    JTable sheet=null;
    MainPanel editor=null;
    int molEdRow=-1,molEdCol=-1;
    
    ImageIcon mainIcon=null,mainLogo=null;

    int unitRowHeight,curRowMag;
    
    public DataWindow(String LoadFN) 
    {
    	super("WIMSchem DataSheet");

	JFrame.setDefaultLookAndFeelDecorated(false); 
	setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

	mainIcon=new ImageIcon(getClass().getResource("/images/MainIcon.png"));
	mainLogo=new ImageIcon(getClass().getResource("/images/MainLogo.png"));

    	setIconImage(mainIcon.getImage());

    	filename=LoadFN;
	if (filename==null) 
	{
	    ds=new DataSheet();
	    cache=new DataSheetCache();
	    ds.AppendColumn("Molecule",DataSheet.COLTYPE_MOLECULE,"Molecular structure");
	} 
	else LoadDataSheet(filename);

	setLayout(new BorderLayout());

	JMenuBar menubar=CreateMenuBar();

    	model=new DataTableModel(ds,cache);
	sheet=new JTable(model);
    	sheet.setPreferredScrollableViewportSize(new Dimension(720,530));
	sheet.setDefaultRenderer(Molecule.class,model.NewMoleculeRenderer());
	sheet.setDefaultEditor(Molecule.class,model.NewMoleculeEditor(this));
	sheet.setRowSelectionAllowed(true);
	sheet.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
	sheet.addKeyListener(this);
		
	unitRowHeight=sheet.getRowHeight();
	UpdateRowHeight(2);
	
	editor=null;

    	splitter=new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,new JScrollPane(sheet),editor);
	splitter.setOneTouchExpandable(true);

    	add(menubar,BorderLayout.NORTH);
	add(splitter,BorderLayout.CENTER);
	
	pack();
	
	addWindowListener(this);
    }

    // ------------------ utility functions --------------------

    // loads a new datasheet and replaces the old one, without question
    private void LoadDataSheet(String FN)
    {
    	DataSheet newDS=null;
	FileInputStream istr=null;
    	try
	{
	    istr=new FileInputStream(FN);
	    if (DataSheetStream.ExamineIsXMLDS(istr))
	    {
	    	newDS=DataSheetStream.ReadXML(istr);
    	    	SetFilename(FN);
	    }
	    else if (DataSheetStream.ExamineIsMDLSDF(istr))
	    {
	    	newDS=DataSheetStream.ReadSDF(istr);
		SetFilename(null);
	    }
	    else
	    {
	    	String msg="["+FN+"]\n"+
		    	   "The file does not appear to be of the XML\n"+
			   "WIMSchem DataSheet format, an MDL SD file.";
	    	JOptionPane.showMessageDialog(null,msg,"Open Failed",JOptionPane.ERROR_MESSAGE);
	    }
	    cache=new DataSheetCache();
	}
	catch (IOException e) 
	{
	    e.printStackTrace();
	    JOptionPane.showMessageDialog(null,e.toString(),"Open Failed",JOptionPane.ERROR_MESSAGE);
	}
	finally 
	{
	    try {if (istr!=null) istr.close();} catch (IOException e) {}
	}

	if (newDS==null) 
	{
	    ds=new DataSheet(); // blank
	    return;
	}

	ds=newDS;
	
	if (model!=null)
	{
	    model.SetDataSheet(ds,cache);
	    model.fireTableStructureChanged();
	}
    }
    
    // assembles the menu items
    private JMenuBar CreateMenuBar()
    {
	JMenuBar menubar=new JMenuBar();
	
    	JMenu menufile=new JMenu("File");
	menufile.setMnemonic(KeyEvent.VK_F);
	menufile.add(MenuItem("New",KeyEvent.VK_N,null,KeyStroke.getKeyStroke('N',InputEvent.CTRL_MASK)));
	menufile.add(MenuItem("Open",KeyEvent.VK_O,null,KeyStroke.getKeyStroke('O',InputEvent.CTRL_MASK)));
	menufile.add(MenuItem("Save",KeyEvent.VK_S,null,KeyStroke.getKeyStroke('S',InputEvent.CTRL_MASK)));
	menufile.add(MenuItem("Save As",KeyEvent.VK_A));
	JMenu menuexport=new JMenu("Export");
	menuexport.setMnemonic(KeyEvent.VK_X);
	menuexport.add(MenuItem("as MDL SDF",KeyEvent.VK_S,null,KeyStroke.getKeyStroke('S',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menufile.add(menuexport);
	menufile.addSeparator();
	menufile.add(MenuItem("Quit",KeyEvent.VK_Q,null,KeyStroke.getKeyStroke('Q',InputEvent.CTRL_MASK)));

    	JMenu menumol=new JMenu("Molecule");
	menumol.setMnemonic(KeyEvent.VK_M);
	menumol.add(MenuItem("Edit Molecule",KeyEvent.VK_E,null,KeyStroke.getKeyStroke(KeyEvent.VK_SPACE,0)));
	menumol.add(MenuItem("Keep Edit",KeyEvent.VK_K,null,KeyStroke.getKeyStroke(KeyEvent.VK_ENTER,InputEvent.CTRL_MASK)));
	menumol.add(MenuItem("Abandon Edit",KeyEvent.VK_A));

    	JMenu menuedit=new JMenu("Edit");
	menuedit.setMnemonic(KeyEvent.VK_E);
	menuedit.add(MenuItem("Undo",KeyEvent.VK_U,null,KeyStroke.getKeyStroke('Z',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem("Redo",KeyEvent.VK_R,null,KeyStroke.getKeyStroke('Z',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuedit.addSeparator();
	menuedit.add(MenuItem("Add Row",KeyEvent.VK_A,null,KeyStroke.getKeyStroke(KeyEvent.VK_INSERT,0)));
	menuedit.add(MenuItem("Delete Rows",KeyEvent.VK_D));
	menuedit.addSeparator();
	menuedit.add(MenuItem("Copy Rows",KeyEvent.VK_C,null,KeyStroke.getKeyStroke('C',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuedit.add(MenuItem("Cut Rows",KeyEvent.VK_T,null,KeyStroke.getKeyStroke('X',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuedit.add(MenuItem("Paste Rows",KeyEvent.VK_P,null,KeyStroke.getKeyStroke('V',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuedit.addSeparator();
	menuedit.add(MenuItem("Edit Columns",KeyEvent.VK_C));
	
	JMenu menuview=new JMenu("View");
	menuview.setMnemonic(KeyEvent.VK_V);
	menuview.add(MenuItem("Single Line",KeyEvent.VK_L,null,KeyStroke.getKeyStroke('1',InputEvent.CTRL_MASK)));
	menuview.add(MenuItem("Small Height",KeyEvent.VK_S,null,KeyStroke.getKeyStroke('2',InputEvent.CTRL_MASK)));
	menuview.add(MenuItem("Medium Height",KeyEvent.VK_M,null,KeyStroke.getKeyStroke('3',InputEvent.CTRL_MASK)));
	menuview.add(MenuItem("Large Height",KeyEvent.VK_L,null,KeyStroke.getKeyStroke('4',InputEvent.CTRL_MASK)));

    	JMenu menuhelp=new JMenu("Help");
	menuhelp.setMnemonic(KeyEvent.VK_H);
	menuhelp.add(MenuItem("About",KeyEvent.VK_A));

	menubar.add(menufile);
	menubar.add(menumol);
	menubar.add(menuedit);
	menubar.add(menuview);
	menubar.add(Box.createHorizontalGlue());
	menubar.add(menuhelp);
	
	return menubar;
    }

    private JMenuItem MenuItem(String txt,int key) {return MenuItem(txt,key,null,null);}
    private JMenuItem MenuItem(String txt,int key,Icon icon) {return MenuItem(txt,key,icon,null);}
    private JMenuItem MenuItem(String txt,int key,Icon icon,KeyStroke accel)
    {
    	JMenuItem mi=new JMenuItem(txt,key);
	mi.addActionListener(this);
	if (icon!=null) mi.setIcon(icon);
	if (accel!=null) mi.setAccelerator(accel);
	return mi;
    }
    private JRadioButtonMenuItem RadioMenuItem(String txt,int key,boolean sel,ButtonGroup bg)
    {
    	JRadioButtonMenuItem mi=new JRadioButtonMenuItem(txt,sel);
	mi.addActionListener(this);
	mi.setMnemonic(key);
	bg.add(mi);
	return mi;
    }

    private void UpdateRowHeight(int Mag)
    {
    	curRowMag=Mag;
	sheet.setRowHeight(unitRowHeight*(curRowMag==2 ? 3 : curRowMag==3 ? 6 : curRowMag==4 ? 12 : 1));
    }
    
    private void SetFilename(String FN)
    {
    	filename=FN;
	String title="WIMSchem DataSheet";
	if (filename!=null) title+=" - "+new File(filename).getName();
	setTitle(title);
    }
    
    private void SaveCurrent()
    {
    	if (filename==null) return;
	try
	{
	    FileOutputStream ostr=new FileOutputStream(filename);
	    DataSheetStream.WriteXML(ostr,ds);
	    ostr.close();
	    ds.ClearDirty();
	}
	catch (IOException e)
	{
	    Utils.errmsg("Save Failed",e.toString());
	}
    }

    // returns true if two datasheets have the same columns
    boolean SameColumns(DataSheet DS1,DataSheet DS2)
    {
    	if (DS1.NumCols()!=DS2.NumCols()) return false;
	for (int n=0;n<DS1.NumCols();n++)
	{
	    if (DS1.ColName(n).compareTo(DS2.ColName(n))!=0) return false;
	    if (DS1.ColType(n)!=DS2.ColType(n)) return false;
	    if (DS1.ColDescr(n).compareTo(DS2.ColDescr(n))!=0) return false;
	}
	return true;
    }

    // ------------------ user responses --------------------

    private void FileQuit()
    {
    	if (ds.IsDirty())
	{
	    String opt[]={"Yes","No"};
	    if (JOptionPane.showOptionDialog(null,"Current datasheet has been modified. Exit without saving?","Quit",
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}
    	dispose();
    }
    
    private void FileNew()
    {
    	//if (ds.NumRows()==0 && !ds.IsDirty() && filename==null) return; // no point
	new DataWindow(null).setVisible(true);
    }
    
    private void FileOpen()
    {
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter("DataSheet Formats",".xml;.sdf"));
	// !! chooser.setAccessory(new FileMolPreview(chooser));
	if (chooser.showOpenDialog(this)!=JFileChooser.APPROVE_OPTION) return;
	String newfn=chooser.getSelectedFile().getPath();
	
	if (ds.NumRows()==0 && !ds.IsDirty())
	    LoadDataSheet(newfn); // replace blank with new thing
	else 
    	    new DataWindow(newfn).setVisible(true); // pop up a new window
    }
    
    private void FileSave()
    {
    	if (filename==null) {FileSaveAs(); return;}
	SaveCurrent();
    }
    
    private void FileSaveAs()
    {
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter("WIMSchem DataSheets",".xml"));
	if (chooser.showSaveDialog(this)!=JFileChooser.APPROVE_OPTION) return;
    
    	String fn=chooser.getSelectedFile().getPath();
	if (chooser.getSelectedFile().getName().indexOf('.')<0) fn=fn+".xml";
    
    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={"Yes","No"};
	    if (JOptionPane.showOptionDialog(null,"Overwrite existing file ["+newf.getName()+"]?","Save As",
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}    	
    
    	SetFilename(fn);
	SaveCurrent();
    }
    
    private void FileExportSDF()
    {
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter("MDL SD files",".sdf"));
	if (chooser.showSaveDialog(this)!=JFileChooser.APPROVE_OPTION) return;
    
    	String fn=chooser.getSelectedFile().getPath();
	if (chooser.getSelectedFile().getName().indexOf('.')<0) fn=fn+".sdf";
    
    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={"Yes","No"};
	    if (JOptionPane.showOptionDialog(null,"Overwrite existing file ["+newf.getName()+"]?","Save As",
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}
	
	// !! perhaps a warning if there are multiple molecule fields?
	
	try
	{
	    FileOutputStream ostr=new FileOutputStream(fn);
	    DataSheetStream.WriteSDF(ostr,ds);
	    ostr.close();
	}
	catch (IOException e)
	{
	    Utils.errmsg("Export Failed",e.toString());
	}
    }

    private void MoleculeEditMol()
    {
    	if (editor!=null) return;
	int row=sheet.getSelectedRow(),col=sheet.getSelectedColumn();
	
	if (row<0 || col<0 || col>=ds.NumCols()) return;
	
	if (ds.ColType(col)!=DataSheet.COLTYPE_MOLECULE) return;

    	// make sure this is the only way to trigger the molecule editor (otherwise is really annoying)
	model.SetTemporaryEdit(col);
	sheet.editCellAt(row,col);
	model.ClearTemporaryEdit();
    }
    
    private void MoleculeKeepEdit()
    {
    	if (editor==null) return;
	Molecule mol=editor.MolData();
	if (mol.NumAtoms()==0) mol=null;
    	cache.CacheUndo(ds);
	ds.SetMolecule(molEdRow,molEdCol,mol);
	ds.SetDirty();
	model.fireTableCellUpdated(molEdRow,molEdCol); 
	editor=null;
	splitter.setRightComponent(editor);
	sheet.requestFocusInWindow();
    }
    
    private void MoleculeAbandonEdit()
    {
    	if (editor==null) return;
	if (sheet.getCellEditor()!=null) sheet.getCellEditor().stopCellEditing();
	editor=null;
	splitter.setRightComponent(editor);
	sheet.requestFocusInWindow();
    }

    private void EditUndo()
    {
    	if (!cache.CanUndo()) return;

	DataSheet newds=cache.PerformUndo(ds);
	boolean colmod=!SameColumns(ds,newds);
	ds=newds;

	ds.SetDirty();
	model.SetDataSheet(ds,cache);
	if (colmod) model.fireTableStructureChanged(); else model.fireTableDataChanged();
    }
    
    private void EditRedo()
    {
    	if (!cache.CanRedo()) return;

	DataSheet newds=cache.PerformRedo(ds);
	boolean colmod=!SameColumns(ds,newds);
	ds=newds;
	
	ds.SetDirty();
	model.SetDataSheet(ds,cache);
	if (colmod) model.fireTableStructureChanged(); else model.fireTableDataChanged();
    }

    private void EditColumns()
    {
    	DialogEditColumns edcols=new DialogEditColumns(this,ds);
	if (!edcols.Execute()) return;
	
	ModifyColumns(edcols.ResultOldPos(),edcols.ResultNewPos(),edcols.ResultName(),edcols.ResultType(),edcols.ResultDescr());
	ds.SetDirty();
	
	model.fireTableStructureChanged();
    }
    
    private void AddRow()
    {
    	cache.CacheUndo(ds);
    	ds.AppendRow();
	model.fireTableChanged(new TableModelEvent(model));
	sheet.setRowSelectionInterval(ds.NumRows()-1,ds.NumRows()-1);
    }
    
    private void DeleteRows()
    {
    	if (sheet.getSelectedRowCount()==0) return;
    	cache.CacheUndo(ds);
	int[] todel=sheet.getSelectedRows();
	for (int i=0;i<todel.length;i++)
	{
	    ds.DeleteRow(i);
	    for (int j=i+1;j<todel.length;j++) if (todel[j]>todel[i]) todel[j]--;
	}
	model.fireTableChanged(new TableModelEvent(model));
    }

    private void CopyRows()
    {
    	if (sheet.getSelectedRowCount()==0) return;
    	int[] rn=sheet.getSelectedRows();
    
    	DataSheet copy=new DataSheet();
	for (int n=0;n<ds.NumCols();n++) 
	{
	    copy.AppendColumn(ds.ColName(n),ds.ColType(n),ds.ColDescr(n));
	}
	for (int i=0;i<rn.length;i++)
	{
	    copy.AppendRow();
	    for (int j=0;j<ds.NumCols();j++) copy.SetObject(i,j,ds.GetObject(rn[i],j));
	}
	
	StringWriter sw=new StringWriter();
	try
	{
	    DataSheetStream.WriteXML(new BufferedWriter(sw),copy);
	    //System.out.println(sw.toString());
            Clipboard clip=Toolkit.getDefaultToolkit().getSystemClipboard();
    	    clip.setContents(new StringSelection(sw.toString()),null);
	}
	catch (IOException e)
	{
	    e.printStackTrace();
	    JOptionPane.showMessageDialog(null,e.toString(),"Copy Failed",JOptionPane.ERROR_MESSAGE);
	}
    }
    
    private void CutRows()
    {
    	CopyRows();
	DeleteRows();
    }
    
    private void PasteRows()
    {
    	String cliptext="";
    
    	try
	{
    	    Clipboard clip=Toolkit.getDefaultToolkit().getSystemClipboard();
	    Transferable contents=clip.getContents(null);
	    if (contents!=null && contents.isDataFlavorSupported(DataFlavor.stringFlavor))
		cliptext=(String)contents.getTransferData(DataFlavor.stringFlavor);
	}
	catch (UnsupportedFlavorException e) 
	{
    	    JOptionPane.showMessageDialog(null,e.toString(),"Clipboard Read Failed",JOptionPane.ERROR_MESSAGE);
	}
	catch (IOException e) 
	{
    	    JOptionPane.showMessageDialog(null,e.toString(),"Paste Failed",JOptionPane.ERROR_MESSAGE);
	}

    	DataSheet paste=null;
	try
	{
	    if (DataSheetStream.ExamineIsXMLDS(new BufferedReader(new StringReader(cliptext))))
		paste=DataSheetStream.ReadXML(new BufferedReader(new StringReader(cliptext)));
	    else if (DataSheetStream.ExamineIsMDLSDF(new BufferedReader(new StringReader(cliptext))))
		paste=DataSheetStream.ReadSDF(new BufferedReader(new StringReader(cliptext)));
	}
	catch (IOException e) {e.printStackTrace(); return;}

    	if (paste==null) 
	{
	    JOptionPane.showMessageDialog(null,
	    	"Unknown format: must be DataSheet XML or MDL SDF","Paste Failed",JOptionPane.ERROR_MESSAGE);
	    return;
	}
	
    	cache.CacheUndo(ds);
	
	//System.out.println("R="+paste.NumRows()+",C="+paste.NumCols());
	
	// handle columns first: find mapping index for each, based on name
	int[] newcolpos=new int[paste.NumCols()];
	for (int i=0;i<paste.NumCols();i++)
	{
	    newcolpos[i]=-1;
	    for (int j=0;j<ds.NumCols();j++) if (ds.ColName(j).compareTo(paste.ColName(i))==0) {newcolpos[i]=j; break;}
	    if (newcolpos[i]<0) newcolpos[i]=ds.AppendColumn(paste.ColName(i),paste.ColType(i),paste.ColDescr(i));
	}
	
	// now paste the new rows
	for (int i=0;i<paste.NumRows();i++)
	{
	    int rn=ds.AppendRow();
	    for (int j=0;j<paste.NumCols();j++)
	    {
	    	int cn=newcolpos[j];
		int ptype=paste.ColType(j),dtype=ds.ColType(j);
		String strval="";
		
		if (ptype==DataSheet.COLTYPE_MOLECULE && dtype==DataSheet.COLTYPE_MOLECULE)
		{
		    ds.SetMolecule(rn,cn,paste.GetMolecule(i,j));
		}
		else if (ptype==DataSheet.COLTYPE_MOLECULE || dtype==DataSheet.COLTYPE_MOLECULE) {} // not possible
		else 
	    	{
		    String val="";
		    if (ptype==DataSheet.COLTYPE_STRING) val=paste.GetString(i,j);
		    else if (ptype==DataSheet.COLTYPE_INTEGER) val=String.valueOf(paste.GetInteger(i,j));
		    else if (ptype==DataSheet.COLTYPE_REAL) val=String.valueOf(paste.GetReal(i,j));
		    else if (ptype==DataSheet.COLTYPE_BOOLEAN) val=paste.GetBoolean(i,j) ? "true" : "false";
		    
		    try
		    {
	    		if (dtype==DataSheet.COLTYPE_STRING) ds.SetString(rn,cn,val);
			else if (dtype==DataSheet.COLTYPE_INTEGER) ds.SetInteger(rn,cn,new Integer(val).intValue());
			else if (dtype==DataSheet.COLTYPE_REAL) ds.SetReal(rn,cn,new Double(val).doubleValue());
			else if (dtype==DataSheet.COLTYPE_BOOLEAN) 
			    ds.SetBoolean(rn,cn,val.toLowerCase().compareTo("true")==0 ? true : false);
		    }
		    catch (NumberFormatException e) {} // stays null
		}
	    }
	}

	model.fireTableChanged(new TableModelEvent(model));
    }

    private void HelpAbout()
    {
    	String msg="WIMSchem v"+MainPanel.VERSION+"\n"+
	    	   "Molecule drawing tool\n"+
		   "© 2005-2008 Dr. Alex M. Clark\n"+
		   "Released under the Gnu Public\n"+
		   "License (GPL), see www.gnu.org\n"+
		   "Home page and documentation:\n"+
		   "http://sketchel.sf.net\n";
    	JOptionPane.showMessageDialog(null,msg,"About WIMSchem",JOptionPane.INFORMATION_MESSAGE,mainLogo);
    }
 
    private void EditMolecule(int RN,int CN)
    {
    	if (editor!=null)
	{
	    /*editor=null;
	    splitter.setRightComponent(editor);*/
	    // !! offer to save, or something?
	}
	
	editor=new MainPanel(null,false,true,null,null,null,null,null,null,true,true);
    	molEdRow=RN;
	molEdCol=CN;
	Molecule mol=ds.GetMolecule(RN,CN);
	if (mol!=null) editor.SetMolecule(mol.Clone());
	
	splitter.setRightComponent(editor);
	int pos=splitter.getWidth()-560;
	splitter.setDividerLocation(pos<0 ? 50 : pos);
	editor.requestFocusInWindow();
    }

    private void ModifyColumns(int[] OldPos,int[] NewPos,String[] Name,int[] Type,String[] Descr)
    {
    	int sz=OldPos.length;
	
	// delete those which need to be chopped out
    	for (int n=0;n<sz;n++) if (NewPos[n]<0)
	{
	    ds.DeleteColumn(OldPos[n]);
	    for (int i=0;i<sz;i++) if (OldPos[i]>OldPos[n]) OldPos[i]--;
	    for (int i=n;i<sz-1;i++) 
	    {
	    	OldPos[i]=OldPos[i+1];
		NewPos[i]=NewPos[i+1];
		Name[i]=Name[i+1];
		Type[i]=Type[i+1];
		Descr[i]=Descr[i+1];
	    }
	    n--;
	    sz--;
	}
	
	// add the new ones
	for (int n=0;n<sz;n++) if (OldPos[n]<0)
	{
	    OldPos[n]=ds.AppendColumn(Name[n],Type[n],Descr[n]);
	}
	
	// modify any existing content
	for (int n=0;n<sz;n++)
	{
	    ds.ChangeColumnName(OldPos[n],Name[n],Descr[n]);
	    ds.ChangeColumnType(OldPos[n],Type[n],true);
	}
	
	// now redefine the column order
	int[] reord=new int[sz];
	for (int n=0;n<sz;n++) reord[NewPos[n]]=OldPos[n];
    	cache.CacheUndo(ds);
	ds.ReorderColumns(reord);
    }

    // ------------------ event functions --------------------
    
    public void actionPerformed(ActionEvent e)
    {
    	String cmd=e.getActionCommand();

    	//System.out.println("CMD:["+cmd+"]");

    	if (e.getSource()==sheet)
	{
	    String[] rc=cmd.split(",");
	    EditMolecule(Integer.parseInt(rc[0]),Integer.parseInt(rc[1]));
	}
	else if (cmd=="Quit") FileQuit();
	else if (cmd=="New") FileNew();
    	else if (cmd=="Open") FileOpen();
	else if (cmd=="Save") FileSave();
	else if (cmd=="Save As") FileSaveAs();
	else if (cmd=="as MDL SDF") FileExportSDF();
	else if (cmd=="Edit Molecule") MoleculeEditMol();
	else if (cmd=="Keep Edit") MoleculeKeepEdit();
	else if (cmd=="Abandon Edit") MoleculeAbandonEdit();
	else if (cmd=="Undo") EditUndo();
	else if (cmd=="Redo") EditRedo();
    	else if (cmd=="Add Row") AddRow();
    	else if (cmd=="Delete Rows") DeleteRows();
    	else if (cmd=="Copy Rows") CopyRows();
    	else if (cmd=="Cut Rows") CutRows();
    	else if (cmd=="Paste Rows") PasteRows();
    	else if (cmd=="Edit Columns") EditColumns();
	else if (cmd=="Single Line") UpdateRowHeight(1);
	else if (cmd=="Small Height") UpdateRowHeight(2);
	else if (cmd=="Medium Height") UpdateRowHeight(3);
	else if (cmd=="Large Height") UpdateRowHeight(4);
	else if (cmd=="About") HelpAbout();
    }
    
    public void windowActivated(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowClosing(WindowEvent e) 
    {
    	FileQuit();
    }
    public void windowDeactivated(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowOpened(WindowEvent e) {}

    public void keyPressed(KeyEvent e) {}
    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) 
    {
    	if (e.getSource()==sheet)
	{
	    if (sheet.isEditing()) return;
	
    	    //System.out.println("key caught: ["+(int)e.getKeyChar()+"]");

	    // decide which keys are permitted to activate editing of a cell (other than molecules, which are handled
	    // by the menu item)
	    boolean shouldEdit=false;
	    if (e.getKeyChar()>=32 && e.getKeyChar()<=126) shouldEdit=true;
	    if (e.getKeyChar()=='\b') shouldEdit=true;
	    if (e.getModifiers()!=0) shouldEdit=false; 
	    int row=sheet.getSelectedRow(),col=sheet.getSelectedColumn();
	    if (row<0 || col<0) shouldEdit=false;
	    else if (ds.ColType(col)==DataSheet.COLTYPE_MOLECULE) shouldEdit=false; // mols have their own way
	    
    	    if (shouldEdit)
	    {
		model.SetTemporaryEdit(col);
		sheet.editCellAt(row,col);
		model.ClearTemporaryEdit();
	    }
	}
    }
}
