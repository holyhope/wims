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
    Readers and writers of the DataSheet format.
    
    The native format is XML (or at least, the subset of XML used by the TrivialDOM class), and is structured as follows:
    
    	<?xml version="1.0" encoding="UTF-8"?>
    	<DataSheet>
	    <Header ncols=~ nrows=~>
	    	<Column id="1" name=~ type=~>{description}</Column>
	    	<Column id="2" name=~ type=~>{description}</Column>
		...
	    	<Column id="{ncols}" name=~ type=~>{description}</Column>
	    </Header>
	    <Content>
	    	<Row id="1">
		    <Cell id="1">{data}</Cell>
		    <Cell id="2">{data}</Cell>
		    ...
		    <Cell id="{ncols}">{data}</Cell>
		</Row>
		...
		<Row id="{nrows}">
		    ...
		</Row>
	    </Content>
	</DataSheet>
	    
    All indices are 1-based.
	    	
*/

public class DataSheetStream
{
    // read-ahead code to try to figure out a filetype

    // returns true if stream is the native datasheet format; preserves file position
    public static boolean ExamineIsXMLDS(FileInputStream istr)
    {
    	boolean ret=false;
    	try
	{
    	    long lastpos=istr.getChannel().position();
    	    BufferedReader rdr=new BufferedReader(new InputStreamReader(istr));
	    ret=ExamineIsXMLDS(rdr);
    	    istr.getChannel().position(lastpos);
	}
	catch (IOException e) {}
    	return ret;
    }
    
    // as above, except this version loses the stream position
    public static boolean ExamineIsXMLDS(BufferedReader rdr)
    {
    	try
	{
	    for (int n=0;n<2;n++)
	    {
		String str=rdr.readLine();
		if (str==null) break;
		if (str.startsWith("<DataSheet>")) return true;
	    }
	}
	catch (IOException e) {}
	return false;
    }
    
    // returns true if stream appears to be an MDL SDfile; preserves file position
    public static boolean ExamineIsMDLSDF(FileInputStream istr)
    {
    	boolean ret=false;
    	try
	{
    	    long lastpos=istr.getChannel().position();
    	    BufferedReader rdr=new BufferedReader(new InputStreamReader(istr));
	    ret=ExamineIsMDLSDF(rdr);
    	    istr.getChannel().position(lastpos);
	}
	catch (IOException e) {}
    	return ret;
    }

    // as above, except this version loses the stream position
    public static boolean ExamineIsMDLSDF(BufferedReader rdr)
    {
    	try
	{
	    for (int n=0;n<3000;n++)
	    {
		String str=rdr.readLine();
		if (str==null) break;
		if (str.compareTo("$$$$")==0 || str.compareTo("M  END")==0) return true;
	    }
	}
	catch (IOException e) {}
	return false;
     }

   // reading of datasheets from the WIMSchem XML format

    public static DataSheet ReadXML(InputStream istr) throws IOException 
    {
    	return ReadXML(new BufferedReader(new InputStreamReader(istr)));
    }
    public static DataSheet ReadXML(BufferedReader in) throws IOException
    {
	TrivialDOM xml=TrivialDOM.ReadXML(in);

	if (xml.Document().NodeName().compareTo("DataSheet")!=0) 
	    throw new IOException("Input stream is XML, but the root node is not <DataSheet>.");
	
    	DataSheet ds=new DataSheet();
	
	// do a precursory check
	TrivialDOM.Node doc=xml.Document(),header=null,content=null;
	for (int n=0;n<doc.NumChildren();n++) if (doc.ChildType(n)==TrivialDOM.TYPE_NODE)
	{
	    TrivialDOM.Node node=doc.GetChildNode(n);
	    if (node.NodeName().compareTo("Header")==0) header=node;
	    if (node.NodeName().compareTo("Content")==0) content=node;
	}
	if (header==null) throw new IOException("XML document lacks a <Header> element.");
	if (content==null) throw new IOException("XML document lacks a <Content> element.");
	
	int ncols=Utils.safeInt(header.Attribute("ncols"),-1),nrows=Utils.safeInt(header.Attribute("nrows"),-1);
	if (ncols<0 || ncols>5000) throw new IOException("Header@ncols attribute absent or improperly specified.");
	if (nrows<0) throw new IOException("Header@nrows attribute absent or improperly specified.");
	
	// put the columns into an array, then create in datasheet
	String[] colName=new String[ncols],colDescr=new String[ncols];
	int[] colType=new int[ncols];
	for (int n=0;n<ncols;n++) colName[n]=null; // means unspecified in source
	for (int n=0;n<header.NumChildren();n++) if (header.ChildType(n)==TrivialDOM.TYPE_NODE)
	{
	    TrivialDOM.Node node=header.GetChildNode(n);
	    if (node.NodeName().compareTo("Column")!=0) continue;
	    int id=Utils.safeInt(node.Attribute("id"),0);
	    if (id<1 || id>ncols) throw new IOException("Column@id out of range.");
	    String strName=node.Attribute("name"),strType=node.Attribute("type");
	    if (strName==null) throw new IOException("Column name not specified.");
	    if (strType==null) throw new IOException("Column type not specified.");
	    int type=0;
	    if (strType.compareTo("molecule")==0) type=DataSheet.COLTYPE_MOLECULE;
	    else if (strType.compareTo("string")==0) type=DataSheet.COLTYPE_STRING;
	    else if (strType.compareTo("integer")==0) type=DataSheet.COLTYPE_INTEGER;
	    else if (strType.compareTo("real")==0) type=DataSheet.COLTYPE_REAL;
	    else if (strType.compareTo("boolean")==0) type=DataSheet.COLTYPE_BOOLEAN;
	    else throw new IOException("Coltype type ["+strType+"] not recognised.");
	    
	    colName[id-1]=strName;
	    colType[id-1]=type;
	    colDescr[id-1]=node.GetText();
	}
	for (int n=0;n<ncols;n++) if (colName[n]==null) throw new IOException("Column id#"+(n+1)+" is not defined.");
	for (int n=0;n<ncols;n++) ds.AppendColumn(colName[n],colType[n],colDescr[n]);
	
	// append a row for each claimed case, then fill in the data as it is encountered
	for (int n=0;n<nrows;n++) ds.AppendRow();
	for (int i=0;i<content.NumChildren();i++) if (content.ChildType(i)==TrivialDOM.TYPE_NODE)
	{
	    TrivialDOM.Node row=content.GetChildNode(i);
	    if (row.NodeName().compareTo("Row")!=0) continue;
	    int rid=Utils.safeInt(row.Attribute("id"),0);
	    if (rid<1 || rid>nrows) throw new IOException("Row@id out of range.");
	    
	    for (int j=0;j<row.NumChildren();j++) if (row.ChildType(j)==TrivialDOM.TYPE_NODE)
	    {
	    	TrivialDOM.Node cell=row.GetChildNode(j);
    	    	if (cell.NodeName().compareTo("Cell")!=0) continue;
		int cid=Utils.safeInt(cell.Attribute("id"),0);
		if (cid<1 || cid>ncols) throw new IOException("Cell@id out of range.");
		
		String data=cell.GetText();
    	    	int type=colType[cid-1];
		
		if (type==DataSheet.COLTYPE_MOLECULE)
		{
		    Molecule mol=null;
		    try {mol=MoleculeStream.ReadUnknown(new BufferedReader(new StringReader(data)));}
		    catch (IOException e) {} // leave it null
		    ds.SetMolecule(rid-1,cid-1,mol);
		}
		else if (type==DataSheet.COLTYPE_STRING)
		{
		    ds.SetString(rid-1,cid-1,data);
		}
		else if (type==DataSheet.COLTYPE_INTEGER)
		{
		    try
		    {
		    	int v=new Integer(data).intValue();
			ds.SetInteger(rid-1,cid-1,v);
		    }
	    	    catch (NumberFormatException e) {ds.SetToNull(rid-1,cid-1);}
		}
		else if (type==DataSheet.COLTYPE_REAL)
		{
		    try
		    {
		    	double v=new Double(data).doubleValue();
			ds.SetReal(rid-1,cid-1,v);
		    }
	    	    catch (NumberFormatException e) {ds.SetToNull(rid-1,cid-1);}
		}
		else if (type==DataSheet.COLTYPE_BOOLEAN)
		{
		    ds.SetBoolean(rid-1,cid-1,data.toLowerCase().compareTo("true")==0) ;
		}
	    }
	}
	
	return ds;
    }

    // reading of datasheets from the MDL SD file format

    public static DataSheet ReadSDF(InputStream istr) throws IOException 
    {
    	return ReadSDF(new BufferedReader(new InputStreamReader(istr)));
    }
    public static DataSheet ReadSDF(BufferedReader in) throws IOException
    {
    	DataSheet ds=new DataSheet();
	
	ds.AppendColumn("mol",DataSheet.COLTYPE_MOLECULE,"Molecule");

	ArrayList<String> entry=new ArrayList<String>();

    	while (true)
	{
	    String line=in.readLine();
	    if (line==null) break;
	    if (!line.startsWith("$$$$")) {entry.add(line); continue;}
	    
	    int rn=ds.AppendRow();
	    
	    StringBuffer sb=new StringBuffer();
	    int pos=0;
	    while (pos<entry.size())
	    {
	    	line=entry.get(pos);
		if (line.startsWith("> ")) break;
		sb.append(line+"\n"); 
		pos++; 
	    	if (line.startsWith("M  END")) {break;}
	    }

	    Molecule mol=null;
	    try {mol=MoleculeStream.ReadMDLMOL(new BufferedReader(new StringReader(sb.toString())));}
	    catch (IOException e) {} // leave it null
	    if (mol!=null) ds.SetMolecule(rn,0,mol);
	    
	    for (;pos+2<entry.size();pos+=3)
	    {
	    	String key=entry.get(pos),val=entry.get(pos+1);
		if (!key.startsWith(">")) continue;
		int z=key.indexOf("<"); if (z<0) continue;
		key=key.substring(z+1);
		z=key.indexOf(">"); if (z<0) continue;
		key=key.substring(0,z);
		if (key.length()==0) continue;
		
		int type=val.length() > 0 ? DataSheet.COLTYPE_STRING : DataSheet.COLTYPE_INTEGER;
		double dval=0;
		int ival=0;
		try
		{
		    dval=Double.parseDouble(val);
		    ival=(int)Math.round(dval);
		    type=dval==ival ? DataSheet.COLTYPE_INTEGER : DataSheet.COLTYPE_REAL;
		}
	    	catch (NumberFormatException e) {} // stays string

		int cn=-1;
		for (int n=0;n<ds.NumCols();n++) if (ds.ColName(n).compareTo(key)==0) {cn=n; break;}
		if (cn<0) cn=ds.AppendColumn(key,type,"");
		
		int curType=ds.ColType(cn);
		if (val.length()==0) ds.SetToNull(rn,cn);
		else if (curType==DataSheet.COLTYPE_STRING) ds.SetString(rn,cn,val);
		else if (curType==DataSheet.COLTYPE_REAL)
		{
		    if (type==DataSheet.COLTYPE_STRING)
		    {
		    	if (ds.ChangeColumnType(cn,DataSheet.COLTYPE_STRING,false)) ds.SetString(rn,cn,val);
		    }
		    else ds.SetReal(rn,cn,dval);
		}
		else if (curType==DataSheet.COLTYPE_INTEGER)
		{
		    if (type==DataSheet.COLTYPE_STRING)
		    {
		    	if (ds.ChangeColumnType(cn,DataSheet.COLTYPE_STRING,false)) ds.SetString(rn,cn,val);
		    }
		    else if (type==DataSheet.COLTYPE_REAL)
		    {
		    	if (ds.ChangeColumnType(cn,DataSheet.COLTYPE_REAL,false)) ds.SetReal(rn,cn,dval);
		    }
		    else ds.SetInteger(rn,cn,ival);
		}
	    }
	 
	    entry.clear();
	}
	
	return ds;
    }

    // writing of datasheets to the WIMSchem XML format
    
    public static void WriteXML(OutputStream ostr,DataSheet ds) throws IOException
    {
	WriteXML(new BufferedWriter(new OutputStreamWriter(ostr)),ds);
    }
    public static void WriteXML(BufferedWriter out,DataSheet ds) throws IOException
    {
    	TrivialDOM xml=new TrivialDOM("DataSheet");

    	int ncols=ds.NumCols(),nrows=ds.NumRows();

    	TrivialDOM.Node header=xml.Document().AppendNode("Header");
	header.SetAttribute("ncols",ds.NumCols()+"");
	header.SetAttribute("nrows",ds.NumRows()+"");
	for (int n=0;n<ncols;n++)
	{
	    TrivialDOM.Node col=header.AppendNode("Column");
	    col.SetAttribute("id",String.valueOf(n+1));
	    col.SetAttribute("name",ds.ColName(n));
	    int type=ds.ColType(n);
	    if (type==DataSheet.COLTYPE_MOLECULE) col.SetAttribute("type","molecule");
	    else if (type==DataSheet.COLTYPE_STRING) col.SetAttribute("type","string");
	    else if (type==DataSheet.COLTYPE_INTEGER) col.SetAttribute("type","integer");
	    else if (type==DataSheet.COLTYPE_REAL) col.SetAttribute("type","real");
	    else if (type==DataSheet.COLTYPE_BOOLEAN) col.SetAttribute("type","boolean");

	    col.SetText(ds.ColDescr(n),false);
	}

    	TrivialDOM.Node content=xml.Document().AppendNode("Content");
	for (int i=0;i<nrows;i++)
	{
	    TrivialDOM.Node row=content.AppendNode("Row");
	    row.SetAttribute("id",String.valueOf(i+1));
	    for (int j=0;j<ncols;j++)
	    {
	    	TrivialDOM.Node col=row.AppendNode("Cell");
		col.SetAttribute("id",String.valueOf(j+1));
		int type=ds.ColType(j);
		if (ds.IsNull(i,j)) {} // do nothing (stays blank)
		else if (type==DataSheet.COLTYPE_MOLECULE)
		{
		    try
		    {
			StringWriter sw=new StringWriter();
			BufferedWriter bw=new BufferedWriter(sw);
			MoleculeStream.WriteNative(bw,ds.GetMolecule(i,j));
			col.SetText(sw.toString(),true);
		    }
		    catch (IOException e) {} // entry stays blank
		}
		else if (type==DataSheet.COLTYPE_STRING) col.SetText(ds.GetString(i,j),true);
		else if (type==DataSheet.COLTYPE_INTEGER) col.SetText(String.valueOf(ds.GetInteger(i,j)),false);
		else if (type==DataSheet.COLTYPE_REAL) col.SetText(String.valueOf(ds.GetReal(i,j)),false);
		else if (type==DataSheet.COLTYPE_BOOLEAN) col.SetText(ds.GetBoolean(i,j) ? "true" : "false",false);
	    }
	}

	TrivialDOM.WriteXML(out,xml);
    }
    
    // writing of datasheets to the MDL SD file format
    
    public static void WriteSDF(OutputStream ostr,DataSheet ds) throws IOException
    {
	WriteSDF(new BufferedWriter(new OutputStreamWriter(ostr)),ds);
    }
    public static void WriteSDF(BufferedWriter out,DataSheet ds) throws IOException
    {
    	int molfld=-1;
	for (int n=0;n<ds.NumCols();n++) if (ds.ColType(n)==DataSheet.COLTYPE_MOLECULE) {molfld=n; break;}
	
	for (int i=0;i<ds.NumRows();i++)
	{
	    if (molfld>=0) if (!ds.IsNull(i,molfld))
	    {
	    	MoleculeStream.WriteMDLMOL(out,ds.GetMolecule(i,molfld));
	    }
	    for (int j=0;j<ds.NumCols();j++) if (ds.ColType(j)!=DataSheet.COLTYPE_MOLECULE && !ds.IsNull(i,j))
	    {
	    	String line="";
		
		if (ds.ColType(j)==DataSheet.COLTYPE_STRING) line=ds.GetString(i,j);
		else if (ds.ColType(j)==DataSheet.COLTYPE_INTEGER) line=String.valueOf(ds.GetInteger(i,j));
		else if (ds.ColType(j)==DataSheet.COLTYPE_REAL) line=String.valueOf(ds.GetReal(i,j));
		else if (ds.ColType(j)==DataSheet.COLTYPE_BOOLEAN) line=ds.GetBoolean(i,j) ? "true" : "false";

    	    	if (line.length()==0) continue;
		String[] bits=line.split("\n");
		boolean anything=false;
		for (int n=0;n<bits.length;n++) if (bits[n].length()>0) anything=true;
		if (!anything) continue;
		
		out.write("> <"+ds.ColName(j)+">\n");
		for (int n=0;n<bits.length;n++) if (bits[n].length()>0) 
		{
		    if (bits[n].length()>78) bits[n]=bits[n].substring(0,78); // tuff
		    out.write(bits[n]+"\n");
		}
		out.write("\n");
	    }
	    
	    out.write("$$$$\n");
	}
	
	out.flush();
    }
}
