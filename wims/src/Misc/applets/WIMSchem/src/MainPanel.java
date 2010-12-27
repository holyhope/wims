/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2007 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import WIMSchem.ds.*;

import java.io.*;
import java.awt.*;
import java.util.*;
import java.awt.image.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import javax.swing.*;

/*
    Encapsulates the editing panel, provides menus and toolbars, and responds to various types
    of events.
    
    General description of WIMSchem: molecular sketching program, for preparing cheminformatic representations of molecules, and a
    few other miscellaneous useful tasks. Is generally intended for using in conjunction with various computational or presentation
    packages which do not themselves necessarily have a good editor for molecular connection graphs.
*/

public class MainPanel extends JPanel implements ActionListener, MouseListener, WindowListener, KeyListener, ClipboardOwner, 
    	    	    	    	    	    	  TemplSelectListener, MolSelectListener
{
    public String LICENSE= // (encoded in a string so that it appears in the final .jar file)
	"This program is free software; you can redistribute it and/or modify\n"+
	"it under the terms of the GNU General Public License as published by\n"+
	"the Free Software Foundation; either version 2 of the License, or\n"+
	"(at your option) any later version.\n\n"+
	"This program is distributed in the hope that it will be useful,\n"+
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"+
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"+
	"GNU General Public License for more details.\n\n"+
	"You should have received a copy of the GNU General Public License\n"+
	"along with this program; if not, write to the Free Software\n"+
	"Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA\n\n"+
	"or see http://www.gnu.org for details.";

    public static String VERSION="0.1";

    public Properties loadProperties(String lang){//jm.evers                                                                               
        Properties P=new Properties();                                                                                                     
        try{                                                                                                                               
            InputStream in = getClass().getResourceAsStream("/lang/WIMSchemProperties_"+lang+".properties");                               
            P.load(in);in.close();                                                                                                         
            return P;                                                                                                                      
    }                                                                                                                                      
        catch (Exception e){ System.out.println("error reading /lang/WIMSchemProperties_"+lang+".properties\n"+e);}                        
        return null;                                                                                                                       
    } 


    MainWindow frameParent;

    ImageIcon mainIcon=null,mainLogo=null;
    public static boolean viewH;
    public static boolean viewC;
    static final int TOOL_CURSOR=0;
    static final int TOOL_ROTATOR=1;
    static final int TOOL_ERASOR=2;
    static final int TOOL_DIALOG=3;
    static final int TOOL_EDIT=4;
    static final int TOOL_SETATOM=5;
    static final int TOOL_SINGLE=6;
    static final int TOOL_DOUBLE=7;
    static final int TOOL_TRIPLE=8;
    static final int TOOL_ZERO=9;
    static final int TOOL_INCLINED=10;
    static final int TOOL_DECLINED=11;
    static final int TOOL_UNKNOWN=12;
    static final int TOOL_CHARGE=13;
    static final int TOOL_UNDO=14;
    static final int TOOL_REDO=15;
    static final int TOOL_TEMPLATE=16;
    static final int TOOL_CUT=17;
    static final int TOOL_COPY=18;
    static final int TOOL_PASTE=19;
    static final int TOOL_UNSELECT=20;
    static final int TOOL_SELECT=21;
    static final int TOOL_COUNT=22;
    public String[] TOOL_TIPS;
    public String[] IMAGE_TOOL={
    	"Cursor","Rotator","Erasor","EDialog","AEdit","ASelect","BSingle","BDouble","BTriple","BZero","BInclined","BDeclined","BUnknown",
	"ACharge","Undo","Redo","Template","ECut","ECopy","EPaste","UnSelect","Select"
    };
    
    // jm.evers
    public boolean[] selected_tools={true,true,true,true,true,true,true,true,true,true,
    	    	    	    	    	true,true,true,true,true,true,true,true,true,true,true,true};
    // jm.evers
    public boolean[] selected_menus={true,true,true,true,true,true,true,true};
    
    public String[] my_atoms;

    // jm.evers
    public  String getToolTips( int p ){
	if(p>TOOL_COUNT){return "error";}
	TOOL_TIPS[0]=translation.getProperty("CURSOR_TIP");
	TOOL_TIPS[1]=translation.getProperty("ROTATOR_TIP");
	TOOL_TIPS[2]=translation.getProperty("ERASOR_TIP");
	TOOL_TIPS[3]=translation.getProperty("EDIT_DIALOG_TIP");
	TOOL_TIPS[4]=translation.getProperty("EDIT_ELEMENT_TIP");
	TOOL_TIPS[5]=translation.getProperty("PLACE_ELEMENT_TIP");
	TOOL_TIPS[6]=translation.getProperty("SINGLE_BOND_TIP");
	TOOL_TIPS[7]=translation.getProperty("DOUBLE_BOND_TIP");
	TOOL_TIPS[8]=translation.getProperty("TRIPLE_BOND_TIP");
	TOOL_TIPS[9]=translation.getProperty("ZERO_BOND_TIP");
	TOOL_TIPS[10]=translation.getProperty("INCLINED_BOND_TIP");
	TOOL_TIPS[11]=translation.getProperty("DECLINE_BOND_TIP");
	TOOL_TIPS[12]=translation.getProperty("SQUIGGLY_BOND_TIP");
	TOOL_TIPS[13]=translation.getProperty("CHARGE_TIP");
	TOOL_TIPS[14]=translation.getProperty("UNDO_TIP");
	TOOL_TIPS[15]=translation.getProperty("REDO_TIP");
	TOOL_TIPS[16]=translation.getProperty("TEMPLATE_TIP");
	TOOL_TIPS[17]=translation.getProperty("CUT_TIP");
	TOOL_TIPS[18]=translation.getProperty("COPY_TIP");
	TOOL_TIPS[19]=translation.getProperty("PASTE");
	TOOL_TIPS[20]=translation.getProperty("UNSELECT");
	TOOL_TIPS[21]=translation.getProperty("SELECT");
	return TOOL_TIPS[p];
    }
    
    AbstractButton[] toolButtons;
    ButtonGroup toolGroup;
    ImageIcon[] toolIcons;
    EditorPane editor;
    // hmmm
    DrawMolecule redraw;
    Templates templ;
    JCheckBoxMenuItem chkShowHydr,chkShowSter;
    
    boolean firstResize=true;
    String filename=null;
    String lastElement=null,typedElement="";
    Molecule lastTemplate=null;
    int templateIdx=-1;
    boolean streamMode=false;
    public static boolean appletMode=false;
    String language="";
    Properties translation;
    boolean useLocalClipboard=false;
    String appletClipboard="";
    

    public MainPanel(String LoadFN,boolean StreamMode,boolean AppletMode,MainWindow FrameParent,String Language,Properties Translation, boolean[] Selected_Tools, boolean[] Selected_Menus , String[] My_Atoms , boolean ViewH, boolean ViewC){
	streamMode=StreamMode;
	appletMode=AppletMode;
	// jm.evers
	if(appletMode){
	    viewH=ViewH;
	    viewC=ViewC;
    	    selected_tools=Selected_Tools;
	    selected_menus=Selected_Menus;
	    my_atoms=My_Atoms;
	    mainIcon=new ImageIcon(getClass().getResource("/images/wims_icon.gif"));
	    mainLogo=new ImageIcon(getClass().getResource("/images/wims_logo.gif"));
	    language=Language;
	    translation=Translation;
	    System.out.println("Hi, I\'m the applet version....language is :"+language);
	}
	else
	{// no language button yet...
	    language="en";
	    my_atoms=null;
	    viewH=true;
	    viewC=true;    
	    mainIcon=new ImageIcon(getClass().getResource("/images/MainIcon.png"));
	    mainLogo=new ImageIcon(getClass().getResource("/images/MainLogo.png"));
	    translation=loadProperties("en");
	    System.out.println("Hi, I\'m the standalone version....language is :"+language);
	}
	frameParent=FrameParent;
	useLocalClipboard=appletMode; 
	// applet mode always uses "local clipboard"; if the applet is signed, this will need to switch
	// to false if permission has been granted to use the system clipboard
	templ=new Templates(getClass());
	
	// toolbar
	TOOL_TIPS=new String[TOOL_COUNT];
	JToolBar tools=new JToolBar(JToolBar.VERTICAL);
	tools.setFloatable(!AppletMode);
	toolButtons=new AbstractButton[TOOL_COUNT];
	toolIcons=new ImageIcon[TOOL_COUNT];
	toolGroup=new ButtonGroup();

	// jm.evers
	for (int n=0;n<TOOL_COUNT;n++) 
	{
	    if (selected_tools[n]) 
	    {
	    //System.out.println("loading tool "+n+" images= "+IMAGE_TOOL[n]+".png");
		toolIcons[n]=new ImageIcon(getClass().getResource("/images/"+IMAGE_TOOL[n]+".png"));
	    	toolButtons[n]=new ToolButton(toolIcons[n]); 
		toolGroup.add(toolButtons[n]);
		tools.add(toolButtons[n]);
	    	toolButtons[n].addActionListener(this);
		toolButtons[n].setToolTipText(getToolTips(n));
	    }
	    /*else {toolButtons[n]=new JButton(toolIcons[n]);
	    tools.add(toolButtons[n]);
	    toolButtons[n].addActionListener(this);}*/
	}
	if(selected_tools[0]){toolGroup.setSelected(toolButtons[TOOL_CURSOR].getModel(),true);}
	if(selected_tools[5]){
	    toolButtons[TOOL_SETATOM].addMouseListener(this);// tool 5
	    toolButtons[TOOL_SETATOM].addKeyListener(this);
	    SelectElement("C");
	}
	if(selected_tools[16]){toolButtons[TOOL_TEMPLATE].addMouseListener(this);}	
 
	// menu
	
	JMenuBar menubar=AppletMode ? MenuBarApplet() : MenuBarApplication();

	// molecule
	
    	editor=new EditorPane();
	editor.SetMolSelectListener(this);
	JScrollPane scroll=new JScrollPane(editor);

    	// overall layout

    	if (!AppletMode)
	{
	    setLayout(new BorderLayout());
	    add(scroll,BorderLayout.CENTER);
    	    add(menubar,BorderLayout.NORTH);
    	    add(tools,BorderLayout.WEST);
	}
	else
	{
    	    // (!! add a little icon somewhere which does the About box...)

	    JPanel p=new JPanel();
	    p.setLayout(new BorderLayout());
	    p.add(menubar,BorderLayout.NORTH);
	    p.add(scroll,BorderLayout.CENTER);
	    
	    setLayout(new BorderLayout());
	    add(tools,BorderLayout.WEST);
	    add(p,BorderLayout.CENTER);
	}
	
	editor.grabFocus();
	
	editor.SetToolCursor();
	
	if (LoadFN!=null)
	{
	    try
	    {
		FileInputStream istr=new FileInputStream(LoadFN);
		Molecule frag=MoleculeStream.ReadUnknown(istr);
		editor.AddArbitraryFragment(frag);
		istr.close();
	    }
	    catch (IOException e) 
	    {
		JOptionPane.showMessageDialog(null,e.toString(),"Open Failed",JOptionPane.ERROR_MESSAGE);
		return;
	    }

	    SetFilename(LoadFN);
	    editor.NotifySaved();
	}
	if (streamMode) ReadStream();
	
	addKeyListener(this);
	editor.addKeyListener(this);
	// jm.evers test
	//editor.NormaliseBondLengths();

	if (frameParent!=null) frameParent.addWindowListener(this);
    }
    
    // builds and returns a menu bar suitable for the application-style invocation
    public JMenuBar MenuBarApplication()
    {
	JMenuBar menubar=new JMenuBar();
    	JMenu menufile=new JMenu(translation.getProperty("File"));
	menufile.setMnemonic(KeyEvent.VK_F);
	menufile.add(MenuItem(translation.getProperty("New"),KeyEvent.VK_N,null,KeyStroke.getKeyStroke('N',InputEvent.CTRL_MASK)));
	menufile.add(MenuItem(translation.getProperty("New_Window"),KeyEvent.VK_W,null,KeyStroke.getKeyStroke('N',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	if (DataWindow.ALLOW) // (temporary)
	    menufile.add(MenuItem(translation.getProperty("New_DataSheet"),KeyEvent.VK_D,null));
	menufile.add(MenuItem(translation.getProperty("Open"),KeyEvent.VK_O,null,KeyStroke.getKeyStroke('O',InputEvent.CTRL_MASK)));
	if (!streamMode) menufile.add(MenuItem(translation.getProperty("Save"),KeyEvent.VK_S,null,KeyStroke.getKeyStroke('S',InputEvent.CTRL_MASK)));
	menufile.add(MenuItem(translation.getProperty("Save_As"),KeyEvent.VK_A));
	JMenu menuexport=new JMenu(translation.getProperty("Export"));
	menuexport.setMnemonic(KeyEvent.VK_X);
	menuexport.add(MenuItem("Native2Javascript (wims)",KeyEvent.VK_M,null,KeyStroke.getKeyStroke('W',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuexport.add(MenuItem("MDLMol2Javascript (wims)",KeyEvent.VK_M,null,KeyStroke.getKeyStroke('V',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuexport.add(MenuItem(translation.getProperty("as_MDL_MOL"),KeyEvent.VK_M,null,KeyStroke.getKeyStroke('M',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuexport.add(MenuItem(translation.getProperty("as_CML_XML"),KeyEvent.VK_X,null,KeyStroke.getKeyStroke('X',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menufile.add(menuexport);

	menufile.addSeparator();
	if (!streamMode) menufile.add(MenuItem(translation.getProperty("Quit"),KeyEvent.VK_Q,null,KeyStroke.getKeyStroke('Q',InputEvent.CTRL_MASK)));
	else menufile.add(MenuItem(translation.getProperty("Save_and_Quit"),KeyEvent.VK_Q,null,KeyStroke.getKeyStroke('Q',InputEvent.CTRL_MASK)));
	
	JMenu menuedit=new JMenu(translation.getProperty("Edit"));
	menuedit.setMnemonic(KeyEvent.VK_E);
	menuedit.add(MenuItem(translation.getProperty("Editttt"),KeyEvent.VK_E,toolIcons[TOOL_DIALOG],KeyStroke.getKeyStroke(' ',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Undo"),KeyEvent.VK_U,toolIcons[TOOL_UNDO],KeyStroke.getKeyStroke('Z',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Redo"),KeyEvent.VK_R,toolIcons[TOOL_REDO],KeyStroke.getKeyStroke('Z',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
    	menuedit.add(MenuItem(translation.getProperty("Cut"),KeyEvent.VK_X,toolIcons[TOOL_CUT],KeyStroke.getKeyStroke('X',InputEvent.CTRL_MASK)));
    	menuedit.add(MenuItem(translation.getProperty("Copy"),KeyEvent.VK_C,toolIcons[TOOL_COPY],KeyStroke.getKeyStroke('C',InputEvent.CTRL_MASK)));
    	menuedit.add(MenuItem(translation.getProperty("Paste"),KeyEvent.VK_V,toolIcons[TOOL_PASTE],KeyStroke.getKeyStroke('V',InputEvent.CTRL_MASK)));
	menuedit.addSeparator();
	//menuedit.add(MenuItem(translation.getProperty("DeSelect_All"),KeyEvent.VK_Q,null,KeyStroke.getKeyStroke('Q',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Select_All"),KeyEvent.VK_S,null,KeyStroke.getKeyStroke('A',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Next_Atom"),KeyEvent.VK_N,null,KeyStroke.getKeyStroke('E',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Previous_Atom"),KeyEvent.VK_P,null,KeyStroke.getKeyStroke('E',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Next_Group"),KeyEvent.VK_G,null,KeyStroke.getKeyStroke('G',InputEvent.CTRL_MASK)));
	menuedit.add(MenuItem(translation.getProperty("Previous_Group"),KeyEvent.VK_R,null,KeyStroke.getKeyStroke('G',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	menuedit.addSeparator();
	menuedit.add(MenuItem(translation.getProperty("Flip_Horizontal"),KeyEvent.VK_H,null,null));
	menuedit.add(MenuItem(translation.getProperty("Flip_Vertical"),KeyEvent.VK_V,null,null));
	menuedit.add(MenuItem(translation.getProperty("Rotate_P45"),KeyEvent.VK_4,null,null));
	menuedit.add(MenuItem(translation.getProperty("Rotate_M45"),KeyEvent.VK_5,null,null));
	menuedit.add(MenuItem(translation.getProperty("Rotate_P90"),KeyEvent.VK_9,null,null));
	menuedit.add(MenuItem(translation.getProperty("Rotate_M90"),KeyEvent.VK_0,null,null));
	menuedit.addSeparator();
    	menuedit.add(MenuItem(translation.getProperty("Add_Temporary_Template"),KeyEvent.VK_T,null,null));
	menuedit.add(MenuItem(translation.getProperty("Normalise_Bond_Lengths"),KeyEvent.VK_N,null,null));
    	
	JMenu menuview=new JMenu(translation.getProperty("View"));
	menuview.setMnemonic(KeyEvent.VK_V);
	menuview.add(MenuItem(translation.getProperty("Zoom_Full"),KeyEvent.VK_F,null,KeyStroke.getKeyStroke('0',InputEvent.CTRL_MASK)));
	menuview.add(MenuItem(translation.getProperty("Zoom_In"),KeyEvent.VK_I,null,KeyStroke.getKeyStroke('=',InputEvent.CTRL_MASK)));
	menuview.add(MenuItem(translation.getProperty("Zoom_Out"),KeyEvent.VK_O,null,KeyStroke.getKeyStroke('-',InputEvent.CTRL_MASK)));
	menuview.addSeparator();
	ButtonGroup showBG=new ButtonGroup();
	menuview.add(RadioMenuItem(translation.getProperty("Show_Elements"),KeyEvent.VK_E,true,showBG));
	menuview.add(RadioMenuItem(translation.getProperty("Show_All_Elements"),KeyEvent.VK_A,false,showBG));
	menuview.add(RadioMenuItem(translation.getProperty("Show_Indices"),KeyEvent.VK_I,false,showBG));
	menuview.add(RadioMenuItem(translation.getProperty("Show_Ring_ID"),KeyEvent.VK_R,false,showBG));
    	menuview.add(RadioMenuItem(translation.getProperty("Show_CIP_Priority"),KeyEvent.VK_C,false,showBG));
	menuview.add(RadioMenuItem(translation.getProperty("Show_Mapping_Number"),KeyEvent.VK_M,false,showBG));
	
	JMenu menutool=new JMenu(translation.getProperty("Tool"));
	menutool.setMnemonic(KeyEvent.VK_T);
	menutool.add(MenuItem(translation.getProperty("Cursor"),KeyEvent.VK_C,toolIcons[TOOL_CURSOR],KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE,0)));
	menutool.add(MenuItem(translation.getProperty("Rotator"),KeyEvent.VK_R,toolIcons[TOOL_ROTATOR],KeyStroke.getKeyStroke('R',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Erasor"),KeyEvent.VK_E,toolIcons[TOOL_ERASOR],KeyStroke.getKeyStroke('D',InputEvent.CTRL_MASK)));
    	menutool.add(MenuItem(translation.getProperty("Edit_Atom"),KeyEvent.VK_A,toolIcons[TOOL_EDIT],KeyStroke.getKeyStroke(',',InputEvent.CTRL_MASK)));
    	menutool.add(MenuItem(translation.getProperty("Set_Atom"),KeyEvent.VK_S,new ImageIcon(getClass().getResource("/images/ASelMenu.png")),KeyStroke.getKeyStroke('.',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Single_Bond"),KeyEvent.VK_1,toolIcons[TOOL_SINGLE],KeyStroke.getKeyStroke('1',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Double_Bond"),KeyEvent.VK_2,toolIcons[TOOL_DOUBLE],KeyStroke.getKeyStroke('2',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Triple_Bond"),KeyEvent.VK_3,toolIcons[TOOL_TRIPLE],KeyStroke.getKeyStroke('3',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Zero_Bond"),KeyEvent.VK_0,toolIcons[TOOL_ZERO],KeyStroke.getKeyStroke('0',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Inclined_Bond"),KeyEvent.VK_I,toolIcons[TOOL_INCLINED]));
	menutool.add(MenuItem(translation.getProperty("Declined_Bond"),KeyEvent.VK_D,toolIcons[TOOL_DECLINED]));
	menutool.add(MenuItem(translation.getProperty("Unknown_Bond"),KeyEvent.VK_U,toolIcons[TOOL_UNKNOWN]));
	menutool.add(MenuItem(translation.getProperty("Charge"),KeyEvent.VK_H,toolIcons[TOOL_CHARGE],KeyStroke.getKeyStroke('H',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Template_Tool"),KeyEvent.VK_T,toolIcons[TOOL_TEMPLATE],KeyStroke.getKeyStroke('T',InputEvent.CTRL_MASK)));
	menutool.add(MenuItem(translation.getProperty("Select_Template"),KeyEvent.VK_T,toolIcons[TOOL_TEMPLATE],KeyStroke.getKeyStroke('T',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	JMenu menuhydr=new JMenu(translation.getProperty("Hydrogen"));
	menuhydr.setMnemonic(KeyEvent.VK_Y);
	chkShowHydr=new JCheckBoxMenuItem(translation.getProperty("Show_Hydrogen"));
	chkShowHydr.setMnemonic(KeyEvent.VK_Y);
	chkShowHydr.setSelected(true);
	chkShowHydr.addActionListener(this);
	menuhydr.add(chkShowHydr);
	menuhydr.add(MenuItem(translation.getProperty("Set_Explicit"),KeyEvent.VK_E));
	menuhydr.add(MenuItem(translation.getProperty("Clear_Explicit"),KeyEvent.VK_X));
	menuhydr.add(MenuItem(translation.getProperty("Zero_Explicit"),KeyEvent.VK_Z));
	menuhydr.add(MenuItem(translation.getProperty("Create_Actual"),KeyEvent.VK_C));
	menuhydr.add(MenuItem(translation.getProperty("Delete_Actual"),KeyEvent.VK_D));

	JMenu menuster=new JMenu(translation.getProperty("Stereochemistry"));
	menuster.setMnemonic(KeyEvent.VK_S);
	chkShowSter=new JCheckBoxMenuItem(translation.getProperty("Show_Stereolabels"));
	chkShowSter.setMnemonic(KeyEvent.VK_L);
	chkShowSter.setSelected(false);
	chkShowSter.addActionListener(this);
	menuster.add(chkShowSter);
	menuster.add(MenuItem(translation.getProperty("Invert_Stereochemistry"),KeyEvent.VK_I));
	menuster.add(MenuItem(translation.getProperty("Set_RZ"),KeyEvent.VK_R));
	menuster.add(MenuItem(translation.getProperty("Set_SE"),KeyEvent.VK_S));
	menuster.add(MenuItem(translation.getProperty("Cycle_Wedges"),KeyEvent.VK_C));
	menuster.add(MenuItem(translation.getProperty("Remove_Wedges"),KeyEvent.VK_W));

    	JMenu menuhelp=new JMenu(translation.getProperty("Help"));
	menuhelp.setMnemonic(KeyEvent.VK_H);
	menuhelp.add(MenuItem(translation.getProperty("About"),KeyEvent.VK_A));

	menubar.add(menufile);
	menubar.add(menuedit);
	menubar.add(menuview);
	menubar.add(menutool);
	menubar.add(menuhydr);
	menubar.add(menuster);
	menubar.add(Box.createHorizontalGlue());
	menubar.add(menuhelp);
	
	return menubar;
    }    

/// ------------
    // builds and returns a menu bar suitable for the applet-style invocation
    
   // menus={"MENU_BLOCK","MENU_SELECT","MENU_TRANSFORM","MENU_ZOOM","MENU_SHOW","MENU_HYDROGEN","MENU_STEREO","MENU_HELP"};
    public JMenuBar MenuBarApplet(){
	JMenuBar menubar=new JMenuBar();
	if(selected_menus[0]){
	    AppletMenu menublock=new AppletMenu(translation.getProperty("Block"));
	    menublock.setMnemonic(KeyEvent.VK_B);
	    menublock.add(MenuItem(translation.getProperty("New"),KeyEvent.VK_N,null,KeyStroke.getKeyStroke('N',InputEvent.CTRL_MASK)));
	    menublock.add(MenuItem(translation.getProperty("Editttt"),KeyEvent.VK_E,null,KeyStroke.getKeyStroke(' ',InputEvent.CTRL_MASK)));
	    menublock.add(MenuItem(translation.getProperty("Undo"),KeyEvent.VK_U,null,KeyStroke.getKeyStroke('Z',InputEvent.CTRL_MASK)));
	    menublock.add(MenuItem(translation.getProperty("Redo"),KeyEvent.VK_R,null,KeyStroke.getKeyStroke('Z',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
    	    menublock.add(MenuItem(translation.getProperty("Cut"),KeyEvent.VK_X,null,KeyStroke.getKeyStroke('X',InputEvent.CTRL_MASK)));
    	    menublock.add(MenuItem(translation.getProperty("Copy"),KeyEvent.VK_C,null,KeyStroke.getKeyStroke('C',InputEvent.CTRL_MASK)));
    	    menublock.add(MenuItem(translation.getProperty("Paste"),KeyEvent.VK_V,null,KeyStroke.getKeyStroke('V',InputEvent.CTRL_MASK)));
	    
	    menubar.add(menublock);
	}
	if(selected_menus[1]){
	    AppletMenu menuselect=new AppletMenu(translation.getProperty("Select"));
	    menuselect.setMnemonic(KeyEvent.VK_S);
	    menuselect.add(MenuItem(translation.getProperty("DeSelect_All"),KeyEvent.VK_Q,null,KeyStroke.getKeyStroke('Q',InputEvent.CTRL_MASK)));
	    menuselect.add(MenuItem(translation.getProperty("Select_All"),KeyEvent.VK_S,null,KeyStroke.getKeyStroke('A',InputEvent.CTRL_MASK)));
	    menuselect.add(MenuItem(translation.getProperty("Next_Atom"),KeyEvent.VK_N,null,KeyStroke.getKeyStroke('E',InputEvent.CTRL_MASK)));
	    menuselect.add(MenuItem(translation.getProperty("Previous_Atom"),KeyEvent.VK_P,null,KeyStroke.getKeyStroke('E',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
	    menuselect.add(MenuItem(translation.getProperty("Next_Group"),KeyEvent.VK_G,null,KeyStroke.getKeyStroke('G',InputEvent.CTRL_MASK)));
	    menuselect.add(MenuItem(translation.getProperty("Previous_Group"),KeyEvent.VK_R,null,KeyStroke.getKeyStroke('G',InputEvent.CTRL_MASK+InputEvent.SHIFT_MASK)));
    
    	    menubar.add(menuselect);
	}
	
	
	if(selected_menus[2]){
	    AppletMenu menutransform=new AppletMenu(translation.getProperty("Transform"));
	    menutransform.setMnemonic(KeyEvent.VK_T);
	    menutransform.add(MenuItem(translation.getProperty("Flip_Horizontal"),KeyEvent.VK_H,null,null));
	    menutransform.add(MenuItem(translation.getProperty("Flip_Vertical"),KeyEvent.VK_V,null,null));
	    menutransform.add(MenuItem(translation.getProperty("Rotate_P45"),KeyEvent.VK_4,null,null));
	    menutransform.add(MenuItem(translation.getProperty("Rotate_M45"),KeyEvent.VK_5,null,null));
    	    menutransform.add(MenuItem(translation.getProperty("Rotate_P90"),KeyEvent.VK_9,null,null));
	    menutransform.add(MenuItem(translation.getProperty("Rotate_M90"),KeyEvent.VK_0,null,null));
	    menutransform.addSeparator();
    	    menutransform.add(MenuItem(translation.getProperty("Add_Temporary_Template"),KeyEvent.VK_T,null,null));
	    menutransform.add(MenuItem(translation.getProperty("Normalise_Bond_Lengths"),KeyEvent.VK_N,null,null));
	menubar.add(menutransform);
	}

	if(selected_menus[3]){
	    AppletMenu menuzoom=new AppletMenu(translation.getProperty("Zoom"));
	    menuzoom.setMnemonic(KeyEvent.VK_Z);
	    menuzoom.add(MenuItem(translation.getProperty("Zoom_Full"),KeyEvent.VK_F,null,KeyStroke.getKeyStroke('0',InputEvent.CTRL_MASK)));
	    menuzoom.add(MenuItem(translation.getProperty("Zoom_In"),KeyEvent.VK_I,null,KeyStroke.getKeyStroke('=',InputEvent.CTRL_MASK)));
	    menuzoom.add(MenuItem(translation.getProperty("Zoom_Out"),KeyEvent.VK_O,null,KeyStroke.getKeyStroke('-',InputEvent.CTRL_MASK)));
	    menubar.add(menuzoom);
	}

	if(selected_menus[4]){	
	    AppletMenu menushow=new AppletMenu(translation.getProperty("Show"));
	    menushow.setMnemonic(KeyEvent.VK_O);
	    ButtonGroup showBG=new ButtonGroup();
//	    if(viewC){
		menushow.add(RadioMenuItem(translation.getProperty("Show_Elements"),KeyEvent.VK_E,true,showBG));
		menushow.add(RadioMenuItem(translation.getProperty("Show_All_Elements"),KeyEvent.VK_A,false,showBG));
//	    }
	    menushow.add(RadioMenuItem(translation.getProperty("Show_Indices"),KeyEvent.VK_I,false,showBG));
	    menushow.add(RadioMenuItem(translation.getProperty("Show_Ring_ID"),KeyEvent.VK_R,false,showBG));
    	    menushow.add(RadioMenuItem(translation.getProperty("Show_CIP_Priority"),KeyEvent.VK_C,false,showBG));
	    menushow.add(RadioMenuItem(translation.getProperty("Show_Mapping_Number"),KeyEvent.VK_M,false,showBG));
	    menubar.add(menushow);
	}

	if(selected_menus[5]){	
	    AppletMenu menuhydrogen=new AppletMenu(translation.getProperty("Hydrogen"));
	    menuhydrogen.setMnemonic(KeyEvent.VK_H);
	    // jm.evers : do not show checkbox in appletparam "viewH" is "no
	    if(viewH){
		chkShowHydr=new JCheckBoxMenuItem(translation.getProperty("Show_Hydrogen"));
	        chkShowHydr.setMnemonic(KeyEvent.VK_Y);
		chkShowHydr.setSelected(true);
	        chkShowHydr.addActionListener(this);
		menuhydrogen.add(chkShowHydr);
	    }
	    menuhydrogen.add(MenuItem(translation.getProperty("Set_Explicit"),KeyEvent.VK_E));
	    menuhydrogen.add(MenuItem(translation.getProperty("Clear_Explicit"),KeyEvent.VK_X));
	    menuhydrogen.add(MenuItem(translation.getProperty("Zero_Explicit"),KeyEvent.VK_Z));
	    menuhydrogen.add(MenuItem(translation.getProperty("Create_Actual"),KeyEvent.VK_C));
	    menuhydrogen.add(MenuItem(translation.getProperty("Delete_Actual"),KeyEvent.VK_D));
	
	    menubar.add(menuhydrogen);
	}
	
	if(selected_menus[6]){
	    AppletMenu menustereo=new AppletMenu(translation.getProperty("Stereo"));
	    menustereo.setMnemonic(KeyEvent.VK_E);
	    chkShowSter=new JCheckBoxMenuItem(translation.getProperty("Show_Stereolabels"));
	    chkShowSter.setMnemonic(KeyEvent.VK_L);
	    chkShowSter.setSelected(false);
	    chkShowSter.addActionListener(this);
	    menustereo.add(chkShowSter);
	    menustereo.add(MenuItem(translation.getProperty("Invert_Stereochemistry"),KeyEvent.VK_I));
	    menustereo.add(MenuItem(translation.getProperty("Set_RZ"),KeyEvent.VK_R));
	    menustereo.add(MenuItem(translation.getProperty("Set_SE"),KeyEvent.VK_S));
	    menustereo.add(MenuItem(translation.getProperty("Cycle_Wedges"),KeyEvent.VK_C));
	    menustereo.add(MenuItem(translation.getProperty("Remove_Wedges"),KeyEvent.VK_W));
	
	    menubar.add(menustereo);
	}

	if(selected_menus[7]){
    	    AppletMenu menuhelp=new AppletMenu(translation.getProperty("Help"));
	    menuhelp.setMnemonic(KeyEvent.VK_P);
	    menuhelp.add(MenuItem(translation.getProperty("About"),KeyEvent.VK_A));
	
	    menubar.add(menuhelp);
	}
	
	return menubar;
    }
    
    
    public Molecule MolData() {return editor.MolData();} // shallow copy, use with care
    
    public void SetMolecule(Molecule Mol){
    	editor.Replace(Mol);
	editor.RotateMolecule();
    	editor.ScaleToFit();
	// jm.evers test 1/2010
	editor.NormaliseBondLengths();
	editor.NotifySaved();
    }
    public void AddMolecule(Molecule Mol){
    	editor.AddArbitraryFragment(Mol);
//	if(MainApplet.user_selection){// jm.evers 1/2010
//	    editor.bondselection = new boolean[Mol.NumBonds()+256]; //hmmm
//	    editor.atomselection = new boolean[Mol.NumAtoms()+256]; //hmmm
//	}
	// jm.evers test
	editor.RotateMolecule();
	editor.NormaliseBondLengths();
    	editor.ScaleToFit();
	editor.NotifySaved();
    }
    
    public void ScaleToFit() {editor.ScaleToFit();}
    
    JMenuItem MenuItem(String txt,int key) {return MenuItem(txt,key,null,null);}
    JMenuItem MenuItem(String txt,int key,Icon icon) {return MenuItem(txt,key,icon,null);}
    JMenuItem MenuItem(String txt,int key,Icon icon,KeyStroke accel)
    {
    	JMenuItem mi=new JMenuItem(txt,key);
	mi.addActionListener(this);
	if (icon!=null) mi.setIcon(icon);
	if (accel!=null) mi.setAccelerator(accel);
	return mi;
    }
    JRadioButtonMenuItem RadioMenuItem(String txt,int key,boolean sel,ButtonGroup bg)
    {
    	JRadioButtonMenuItem mi=new JRadioButtonMenuItem(txt,sel);
	mi.addActionListener(this);
	mi.setMnemonic(key);
	bg.add(mi);
	return mi;
    }
    
    void FileQuit()
    {
    	if (!streamMode)
	{
    	    if (editor.IsDirty())
	    {
		String opt[]={"Yes","No"};
		if (JOptionPane.showOptionDialog(null,translation.getProperty("Current_structure_has_been_modified"),translation.getProperty("Quit"),
    	    		JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	    }
	}
	else
	{
	    WriteStream();
	}

	if (frameParent!=null) frameParent.dispose(); 

	return;
    }
    void FileNew()
    {
    	if (editor.MolData().NumAtoms()>0)
	{
	    String opt[]={translation.getProperty("Yes"),translation.getProperty("No")};
	    if (JOptionPane.showOptionDialog(null,translation.getProperty("Clear_current_structure_and_start_anew"),translation.getProperty("New"),
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}
    	editor.Clear();
	filename=null;
	if (frameParent!=null) frameParent.setTitle("WIMSchem");
	editor.NotifySaved();
    }
    void FileNewWindow()
    {
    	MainWindow mw=new MainWindow(null,false,translation);
	mw.setVisible(true);
    }
    void FileNewDataSheet()
    {
    	DataWindow dw=new DataWindow(null);
	dw.setVisible(true);
    }
    void FileOpen()
    {
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter(translation.getProperty("Molecular_Structures"),".el;.mol;.sdf;*.xml"));
	chooser.setAccessory(new FileMolPreview(chooser));
	if (chooser.showOpenDialog(frameParent)!=JFileChooser.APPROVE_OPTION) return;
	
	boolean fresh=editor.IsEmpty();
	String newfn=chooser.getSelectedFile().getPath();
	boolean anything=editor.MolData().NumAtoms()>0;
	try
	{
	    FileInputStream istr=new FileInputStream(newfn);
	    if (!DataWindow.ALLOW && MoleculeStream.ExamineIsDatabase(istr)) 
	    {	// !! this section is to be deprecated when DataSheet is fully functional
    	    	istr.close();
	    	CatalogWindow cw=new CatalogWindow(newfn);
		cw.setVisible(true);
	    }
	    else if (DataSheetStream.ExamineIsXMLDS(istr) || DataSheetStream.ExamineIsMDLSDF(istr))
	    {
	    	istr.close();
		DataWindow dw=new DataWindow(newfn);
		dw.setVisible(true);
	    }
	    else
	    {
	    	Molecule frag=MoleculeStream.ReadUnknown(istr);
	    	editor.AddArbitraryFragment(frag);
		// jm.evers test
		editor.NormaliseBondLengths();

    	    	istr.close();
	    	if (fresh) SetFilename(newfn);
    	    	if (!anything) editor.NotifySaved();
	    }
	}
	catch (IOException e) 
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Open_Failed"),JOptionPane.ERROR_MESSAGE);
	    //e.printStackTrace();
	    return;
	}
    }
    
    void FileSave()
    {
    	if (filename==null) {FileSaveAs(); return;}
	SaveCurrent();
    }
    
    void FileSaveAs()
    {
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter(translation.getProperty("WIMSchem_Files"),".el"));
	chooser.setAccessory(new FileMolPreview(chooser));
	if (chooser.showSaveDialog(frameParent)!=JFileChooser.APPROVE_OPTION) return;
    
    	String fn=chooser.getSelectedFile().getPath();
	if (chooser.getSelectedFile().getName().indexOf('.')<0) fn=fn+".el";
    
    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={translation.getProperty("Yes"),translation.getProperty("No")};
	    if (JOptionPane.showOptionDialog(null,translation.getProperty("Overwrite_existing_file")+" ["+newf.getName()+"]?",translation.getProperty("Save_As"),
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}    	
    
    	SetFilename(fn);
	SaveCurrent();
    }
    
    void FileExportNative2JavaScript(){
	// jm.evers :test with export to more convinient wims usage...? make a Native Javascript string
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	if (chooser.showSaveDialog(frameParent)!=JFileChooser.APPROVE_OPTION) return;

    	String fn=chooser.getSelectedFile().getPath();

    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={translation.getProperty("Yes"),translation.getProperty("No")};
	    if (JOptionPane.showOptionDialog(null,translation.getProperty("Overwrite_existing_file")+" ["+newf.getName()+"]?",translation.getProperty("Export_MDL_MOL"),
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}    	

	try
	{
	    FileOutputStream ostr=new FileOutputStream(fn);
	    MoleculeStream.WriteNative2JavaScript(ostr,editor.MolData());
	    ostr.close();
	}
	catch (IOException e)
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Export_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }
    
    void FileExportMDLMol2JavaScript(){
	// jm.evers :test with export to more convinient wims usage...? make a MDLMol Javascript string
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	if (chooser.showSaveDialog(frameParent)!=JFileChooser.APPROVE_OPTION) return;

    	String fn=chooser.getSelectedFile().getPath();

    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={translation.getProperty("Yes"),translation.getProperty("No")};
	    if (JOptionPane.showOptionDialog(null,translation.getProperty("Overwrite_existing_file")+" ["+newf.getName()+"]?",translation.getProperty("Export_MDL_MOL"),
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}    	

	try
	{
	    FileOutputStream ostr=new FileOutputStream(fn);
	    MoleculeStream.WriteMDLMol2JavaScript(ostr,editor.MolData());
	    ostr.close();
	}
	catch (IOException e)
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Export_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }
    


    void FileExportMDLMOL(){
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter(translation.getProperty("MDL_MOL_Files"),".mol"));
	chooser.setAccessory(new FileMolPreview(chooser));
	if (chooser.showSaveDialog(frameParent)!=JFileChooser.APPROVE_OPTION) return;

    	String fn=chooser.getSelectedFile().getPath();
	if (chooser.getSelectedFile().getName().indexOf('.')<0) fn=fn+".mol";

    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={translation.getProperty("Yes"),translation.getProperty("No")};
	    if (JOptionPane.showOptionDialog(null,translation.getProperty("Overwrite_existing_file")+" ["+newf.getName()+"]?",translation.getProperty("Export_MDL_MOL"),
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}    	

	try
	{
	    FileOutputStream ostr=new FileOutputStream(fn);
	    MoleculeStream.WriteMDLMOL(ostr,editor.MolData());
	    ostr.close();
	}
	catch (IOException e)
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Export_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }

    void FileExportCMLXML(){
	JFileChooser chooser=new JFileChooser(System.getenv().get("PWD"));
	chooser.setDragEnabled(false);
	chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
	chooser.setFileFilter(new FileExtFilter(translation.getProperty("XML_Files"),".xml"));
	chooser.setAccessory(new FileMolPreview(chooser));
	if (chooser.showSaveDialog(frameParent)!=JFileChooser.APPROVE_OPTION) return;

    	String fn=chooser.getSelectedFile().getPath();
	if (chooser.getSelectedFile().getName().indexOf('.')<0) fn=fn+".xml";

    	File newf=new File(fn);
    	if (newf.exists())
	{
	    String opt[]={translation.getProperty("Yes"),translation.getProperty("No")};
	    if (JOptionPane.showOptionDialog(null,translation.getProperty("Overwrite_existing_file")+" ["+newf.getName()+"]?",translation.getProperty("Export_CML_XML"),
    	    	    JOptionPane.YES_NO_OPTION,JOptionPane.YES_NO_OPTION,null,opt,opt[0])!=JOptionPane.YES_OPTION) return;
	}    	

	try
	{
	    FileOutputStream ostr=new FileOutputStream(fn);
	    MoleculeStream.WriteCMLXML(ostr,editor.MolData());
	    ostr.close();
	}
	catch (IOException e)
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Export_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }


    void SetFilename(String fn){
    	if (fn.length()==0) {filename=null; return;}
    	filename=fn;
	
	if (!streamMode)
	{
	   String chopfn=fn;
	   int i=chopfn.lastIndexOf("/");
	   if (i>=0) chopfn=chopfn.substring(i+1);
           if (frameParent!=null) frameParent.setTitle(chopfn+" - WIMSchem");
	} 
	else {if (frameParent!=null) frameParent.setTitle("WIMSchem");}
    }
    
    void SaveCurrent(){
	try
	{
	    FileOutputStream ostr=new FileOutputStream(filename);
	    MoleculeStream.WriteNative(ostr,editor.MolData());
	    ostr.close();
	    editor.NotifySaved();
	}
	catch (IOException e)
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Save_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }
    
    void ReadStream(){
	try
	{
	    Molecule frag=MoleculeStream.ReadUnknown(System.in);
	    editor.AddArbitraryFragment(frag);
	    // jm.evers test
	    editor.NormaliseBondLengths();
	}
	catch (IOException e) 
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("stdin_Read_Failed"),JOptionPane.ERROR_MESSAGE);
	    return;
	}
    }
    void WriteStream(){
    	Molecule mol=editor.MolData();
	try
	{
	    MoleculeStream.WriteMDLMOL(System.out,mol);
	    MoleculeStream.WriteNative(System.out,mol);
	}
	catch (IOException e) 
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("stdout_Write_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }
    
    void TestMol(){
    	Molecule mol=new Molecule();
	
	mol.AddAtom("N",0,0);
	mol.AddAtom("C",1.2,0);
	mol.AddAtom("O",2,0.8);
	mol.AddAtom("H",3,-0.8);
	mol.AddAtom("H",4,0);
	mol.AddBond(1,2,1);
	mol.AddBond(2,3,2);
	mol.AddBond(3,4,1);
	mol.AddBond(4,5,0);
	
	editor.Replace(mol);
    } 
    
    void EditCut(){
    	Molecule frag=editor.SelectedSubgraph();
	try
	{
	    StringWriter sw=new StringWriter();
	    BufferedWriter bw=new BufferedWriter(sw);
	    MoleculeStream.WriteMDLMOL(bw,frag);
	    MoleculeStream.WriteNative(bw,frag);
	    if (useLocalClipboard)
	    {
	    	appletClipboard=sw.toString();
	    }
	    else
	    {
    		Clipboard clip=Toolkit.getDefaultToolkit().getSystemClipboard();
    		clip.setContents(new StringSelection(sw.toString()),this);
	    }
	    editor.DeleteSelected(); // (keep this within the exception trap)
	}
	catch (IOException e) 
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Cut_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }
    
    void EditCopy(){
    	Molecule frag=editor.SelectedSubgraph();
	try
	{
	    StringWriter sw=new StringWriter();
	    BufferedWriter bw=new BufferedWriter(sw);
	    MoleculeStream.WriteMDLMOL(bw,frag);
	    MoleculeStream.WriteNative(bw,frag);
	    if (useLocalClipboard)
	    {
	    	appletClipboard=sw.toString();
	    }
	    else
	    {
    	    	Clipboard clip=Toolkit.getDefaultToolkit().getSystemClipboard();
    	    	clip.setContents(new StringSelection(sw.toString()),this);
	    }
	}
	catch (IOException e) 
	{
	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Copy_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }
    
    void EditPaste(){
    	try 
	{
	    String cliptext=null;
	    if (useLocalClipboard) cliptext=appletClipboard;
	    else
	    {
    		Clipboard clip=Toolkit.getDefaultToolkit().getSystemClipboard();
		Transferable contents=clip.getContents(null);
		if (contents!=null && contents.isDataFlavorSupported(DataFlavor.stringFlavor))
		{
		    cliptext=(String)contents.getTransferData(DataFlavor.stringFlavor);
		}
	    }
	    
	    if (cliptext!=null)
	    {
	    	Molecule frag=MoleculeStream.ReadUnknown(new BufferedReader(new StringReader(cliptext)));
		if (frag!=null) editor.AddArbitraryFragment(frag);
	    }
	}
	catch (UnsupportedFlavorException e) 
	{
    	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Clipboard_Read_Failed"),JOptionPane.ERROR_MESSAGE);
	}
	catch (IOException e) 
	{
    	    JOptionPane.showMessageDialog(null,e.toString(),translation.getProperty("Paste_Failed"),JOptionPane.ERROR_MESSAGE);
	}
    }

    void SelectElement(String El){
    	if (lastElement!=null) 
	{
	    if (lastElement.compareTo(El)==0) return;
	    toolIcons[TOOL_SETATOM]=new ImageIcon(getClass().getResource("/images/"+IMAGE_TOOL[TOOL_SETATOM]+".png"));
	}

	int w=toolIcons[TOOL_SETATOM].getImage().getWidth(null),h=toolIcons[TOOL_SETATOM].getImage().getHeight(null);
	BufferedImage img=new BufferedImage(w,h,BufferedImage.TYPE_INT_ARGB);
	Graphics2D g=(Graphics2D)img.getGraphics();
	g.setColor(new Color(0x00000000,true));
	g.fillRect(0,0,w,h);
	g.drawImage(toolIcons[TOOL_SETATOM].getImage(),0,0,null);
	
    	Font font=new Font("SansSerif",Font.PLAIN,El.length()==1 ? 20 : 14);
	g.setFont(font);
	g.setColor(new Color(0,192,0));
	FontMetrics metrics=g.getFontMetrics();
	g.drawString(El,(w-metrics.stringWidth(El))/2-3,(h+metrics.getAscent())/2-2);
	
	toolButtons[TOOL_SETATOM].setIcon(new ImageIcon(img));
	
    	lastElement=El;
    }
    
    void TemplateTool(){
    	if (lastTemplate==null) {TemplateSelect(); return;}
    	editor.SetToolTemplate(lastTemplate,templateIdx);
    }
    
    void TemplateSelect(){
    	int heightFudge=appletMode ? 30 : 0; // !! unpleasant hack which stands in for being a non-signed applet; correct at some point
    	TemplateSelector sel=new TemplateSelector(templ,this,heightFudge);
	Point pos=toolButtons[TOOL_TEMPLATE].getLocationOnScreen();

	Dimension ssz=Toolkit.getDefaultToolkit().getScreenSize();
    	GraphicsEnvironment ge=GraphicsEnvironment.getLocalGraphicsEnvironment();
	GraphicsConfiguration gc=ge.getScreenDevices()[0].getConfigurations()[0];
	ssz.width-=Toolkit.getDefaultToolkit().getScreenInsets(gc).right;
	ssz.height-=Toolkit.getDefaultToolkit().getScreenInsets(gc).bottom;
	      	
	if (pos.x+sel.getWidth()>ssz.width) pos.x=ssz.width-sel.getWidth();
	if (pos.y+sel.getHeight()>ssz.height) pos.y=ssz.height-sel.getHeight();
	sel.setLocation(pos);
	sel.setVisible(true);
    }
    
    void TemplateAddTo(){
    	templ.AddTemplate(editor.SelectedSubgraph());
    }
    
    void EditDialog(){
    	Molecule newMol=(new DialogEdit(frameParent,editor.MolData(),editor.SelectedIndices())).exec();
	if (newMol!=null) 
	{
	    editor.CacheUndo();
	    editor.Replace(newMol,false);
	}
    }
    
    void HelpAbout()
    {
    	String msg="        WIMSchem v"+VERSION+"           \n"+
		   "                                        \n"+
	    	   "   Molecule drawing tool for WIMS       \n"+
		   "   [ the Interactive Education Server ] \n"+
		   "   http://wims.unice.fr/wims/wims.cgi?  \n"+
		   "   A slightly modified version of:      \n"+
		   "                                        \n"+
		   "      SketchEl  version1.19             \n"+
		   "   © 2005-2008 Dr. Alex M. Clark        \n"+
		   "   Released under the Gnu Public        \n"+
		   "   License (GPL), see www.gnu.org       \n"+
		   "   Home page and documentation:         \n"+
		   "   http://sketchel.sf.net               \n";
    	JOptionPane.showMessageDialog(null,msg,translation.getProperty("About_WIMSchem"),JOptionPane.INFORMATION_MESSAGE,mainLogo);
    }
    
    // ------------------ event functions --------------------

    public void actionPerformed(ActionEvent e) 
    {
    	String cmd=e.getActionCommand();
	
	int setsel=-1;
	
	if (cmd.equals(translation.getProperty("Quit")) || cmd.equals(translation.getProperty("Save_and_Quit"))) FileQuit();
	else if (cmd.equals(translation.getProperty("New"))) FileNew();
	else if (cmd.equals(translation.getProperty("New_Window"))) FileNewWindow();
	else if (cmd.equals(translation.getProperty("New_DataSheet"))) FileNewDataSheet();
	else if (cmd.equals(translation.getProperty("Open"))) FileOpen();
	else if (cmd.equals(translation.getProperty("Save"))) FileSave();
	else if (cmd.equals(translation.getProperty("Save_As"))) FileSaveAs();
    	else if (cmd.equals(translation.getProperty("as_MDL_MOL"))) FileExportMDLMOL();
    	else if (cmd.equals(translation.getProperty("as_CML_XML"))) FileExportCMLXML();
    	else if (cmd.equals("Native2Javascript (wims)")) FileExportNative2JavaScript();
    	else if (cmd.equals("MDLMol2Javascript (wims)")) FileExportMDLMol2JavaScript();
	else if (cmd.equals(translation.getProperty("Cursor")) || e.getSource()==toolButtons[TOOL_CURSOR]) {editor.SetToolCursor(); setsel=TOOL_CURSOR;}
	else if (cmd.equals(translation.getProperty("Rotator")) || e.getSource()==toolButtons[TOOL_ROTATOR]) {editor.SetToolRotator(); setsel=TOOL_ROTATOR;}
	else if (cmd.equals(translation.getProperty("Erasor")) || e.getSource()==toolButtons[TOOL_ERASOR]) {editor.SetToolErasor(); setsel=TOOL_ERASOR;}
	else if (cmd.equals(translation.getProperty("Editttt")) || e.getSource()==toolButtons[TOOL_DIALOG]) EditDialog();
    	else if (cmd.equals(translation.getProperty("DeSelect_All")) || e.getSource()==toolButtons[TOOL_UNSELECT]) editor.DeSelectAll();
    	else if (cmd.equals(translation.getProperty("Select")) || e.getSource()==toolButtons[TOOL_SELECT]) editor.Select();
    	else if (cmd.equals(translation.getProperty("Select_All"))) editor.SelectAll();
	else if (cmd.equals(translation.getProperty("Next_Atom"))) editor.CycleSelection(true,false);
	else if (cmd.equals(translation.getProperty("Previous_Atom"))) editor.CycleSelection(false,false);
	else if (cmd.equals(translation.getProperty("Next_Group"))) editor.CycleSelection(true,true);
	else if (cmd.equals(translation.getProperty("Previous_Group"))) editor.CycleSelection(false,true);
	else if (cmd.equals(translation.getProperty("Edit_Atom")) || e.getSource()==toolButtons[TOOL_EDIT]) {editor.SetToolAtom(null); setsel=TOOL_EDIT;}
	else if (cmd.equals(translation.getProperty("Set_Atom")) || e.getSource()==toolButtons[TOOL_SETATOM]) {editor.SetToolAtom(lastElement); setsel=TOOL_SETATOM;}
	else if (cmd.equals(translation.getProperty("Single_Bond")) || e.getSource()==toolButtons[TOOL_SINGLE]) {editor.SetToolBond(1); setsel=TOOL_SINGLE;}
	else if (cmd.equals(translation.getProperty("Double_Bond")) || e.getSource()==toolButtons[TOOL_DOUBLE]) {editor.SetToolBond(2); setsel=TOOL_DOUBLE;}
	else if (cmd.equals(translation.getProperty("Triple_Bond")) || e.getSource()==toolButtons[TOOL_TRIPLE]) {editor.SetToolBond(3); setsel=TOOL_TRIPLE;}
	else if (cmd.equals(translation.getProperty("Zero_Bond")) || e.getSource()==toolButtons[TOOL_ZERO]) {editor.SetToolBond(0); setsel=TOOL_ZERO;}
	else if (cmd.equals(translation.getProperty("Inclined_Bond")) || e.getSource()==toolButtons[TOOL_INCLINED]) {editor.SetToolBond(-1); setsel=TOOL_INCLINED;}
	else if (cmd.equals(translation.getProperty("Declined_Bond")) || e.getSource()==toolButtons[TOOL_DECLINED]) {editor.SetToolBond(-2); setsel=TOOL_DECLINED;}
	else if (cmd.equals(translation.getProperty("Unknown_Bond")) || e.getSource()==toolButtons[TOOL_UNKNOWN]) {editor.SetToolBond(-3); setsel=TOOL_UNKNOWN;}
	else if (cmd.equals(translation.getProperty("Charge")) || e.getSource()==toolButtons[TOOL_CHARGE]) {editor.SetToolCharge(1); setsel=TOOL_CHARGE;}
	else if (cmd.equals(translation.getProperty("Undo")) || e.getSource()==toolButtons[TOOL_UNDO]) editor.Undo();
	else if (cmd.equals(translation.getProperty("Redo")) || e.getSource()==toolButtons[TOOL_REDO]) editor.Redo();
	else if (cmd.equals(translation.getProperty("Cut"))) EditCut();
	else if (cmd.equals(translation.getProperty("Copy"))) EditCopy();
	else if (cmd.equals(translation.getProperty("Paste"))) EditPaste();
	else if (cmd.equals(translation.getProperty("Flip_Horizontal"))) editor.FlipSelectedAtoms(false);
	else if (cmd.equals(translation.getProperty("Flip_Vertical"))) editor.FlipSelectedAtoms(true);
	else if (cmd.equals(translation.getProperty("Rotate_P45"))) editor.RotateSelectedAtoms(45);
	else if (cmd.equals(translation.getProperty("Rotate_M45"))) editor.RotateSelectedAtoms(-45);
	else if (cmd.equals(translation.getProperty("Rotate_P90"))) editor.RotateSelectedAtoms(90);
	else if (cmd.equals(translation.getProperty("Rotate_M90"))) editor.RotateSelectedAtoms(-90);
    	else if (cmd.equals(translation.getProperty("Add_Temporary_Template"))) TemplateAddTo();
    	else if (cmd.equals(translation.getProperty("Normalise_Bond_Lengths"))) editor.NormaliseBondLengths();
	else if (cmd.equals(translation.getProperty("Template_Tool")) || e.getSource()==toolButtons[TOOL_TEMPLATE]) {TemplateTool(); setsel=TOOL_TEMPLATE;}
	else if (cmd.equals(translation.getProperty("Select_Template"))) {TemplateSelect(); setsel=TOOL_TEMPLATE;}
	else if (cmd.equals(translation.getProperty("Zoom_Full"))) editor.ZoomFull();
	else if (cmd.equals(translation.getProperty("Zoom_In"))) editor.ZoomIn(1.5);
	else if (cmd.equals(translation.getProperty("Zoom_Out"))) editor.ZoomOut(1.5);
	else if (cmd.equals(translation.getProperty("Show_Elements"))) editor.SetShowMode(DrawMolecule.SHOW_ELEMENTS);
	else if (cmd.equals(translation.getProperty("Show_All_Elements"))) editor.SetShowMode(DrawMolecule.SHOW_ALL_ELEMENTS);
	else if (cmd.equals(translation.getProperty("Show_Indices"))) editor.SetShowMode(DrawMolecule.SHOW_INDEXES);
	else if (cmd.equals(translation.getProperty("Show_Ring_ID"))) editor.SetShowMode(DrawMolecule.SHOW_RINGID);
	else if (cmd.equals(translation.getProperty("Show_CIP_Priority"))) editor.SetShowMode(DrawMolecule.SHOW_PRIORITY);
	else if (cmd.equals(translation.getProperty("Show_Mapping_Number"))) editor.SetShowMode(DrawMolecule.SHOW_MAPNUM);
	else if (cmd.equals(translation.getProperty("Show_Hydrogen"))) editor.SetShowHydrogens(chkShowHydr.isSelected());
	else if (cmd.equals(translation.getProperty("Set_Explicit")))  editor.HydrogenSetExplicit(true);
	else if (cmd.equals(translation.getProperty("Clear_Explicit"))) editor.HydrogenSetExplicit(false);
    	else if (cmd.equals(translation.getProperty("Zero_Explicit"))) editor.HydrogenSetExplicit(false,0);
	else if (cmd.equals(translation.getProperty("Create_Actual"))) editor.HydrogenCreateActual();
	else if (cmd.equals(translation.getProperty("Delete_Actual"))) editor.HydrogenDeleteActual();
	else if (cmd.equals(translation.getProperty("Show_Stereolabels"))) editor.SetShowStereolabels(chkShowSter.isSelected());
	else if (cmd.equals(translation.getProperty("Invert_Stereochemistry"))) editor.SetStereo(Molecule.STEREO_UNKNOWN);
	else if (cmd.equals(translation.getProperty("Set_RZ"))) editor.SetStereo(Molecule.STEREO_POS);
	else if (cmd.equals(translation.getProperty("Set_SE"))) editor.SetStereo(Molecule.STEREO_NEG);
	else if (cmd.equals(translation.getProperty("Cycle_Wedges"))) editor.CycleChiralWedges();
	else if (cmd.equals(translation.getProperty("Remove_Wedges"))) editor.RemoveChiralWedges();
	else if (cmd.equals(translation.getProperty("About"))) HelpAbout();
	else if (cmd.length()<=2) {SelectElement(cmd); editor.SetToolAtom(lastElement);}
    	if (setsel!=-1) toolGroup.setSelected(toolButtons[setsel].getModel(),true);
    } 
    
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mousePressed(MouseEvent e){
	// jm.evers : setting atoms menulist according applet-params...or not
    	if (e.getSource()==toolButtons[TOOL_SETATOM] && e.getButton()==MouseEvent.BUTTON3)
	{
	    toolButtons[TOOL_SETATOM].setSelected(true);
	    JPopupMenu popup=new JPopupMenu();
	    if(my_atoms==null){
		popup.add(MenuItem("C",0));
	        popup.add(MenuItem("H",0));
		popup.add(MenuItem("O",0));
	        popup.add(MenuItem("N",0));
	        popup.add(MenuItem("S",0));
	        popup.add(MenuItem("P",0));
	        popup.add(MenuItem("Li",0));
	        popup.add(MenuItem("Na",0));
	        popup.add(MenuItem("K",0));
	        popup.add(MenuItem("Mg",0));
	        popup.add(MenuItem("Ca",0));
		popup.add(MenuItem("Ti",0));
	        popup.add(MenuItem("Zr",0));
	        popup.add(MenuItem("Cr",0));
	        popup.add(MenuItem("Mo",0));
	        popup.add(MenuItem("Mn",0));
	        popup.add(MenuItem("Fe",0));
	        popup.add(MenuItem("Cu",0));
	        popup.add(MenuItem("Zn",0));
	        popup.add(MenuItem("Ag",0));
	        popup.add(MenuItem("Hg",0));
	        popup.add(MenuItem("Al",0));
	        popup.add(MenuItem("Si",0));
	        popup.add(MenuItem("F",0));
	        popup.add(MenuItem("Cl",0));
	        popup.add(MenuItem("Br",0));
	        popup.add(MenuItem("I",0));
	    }
	    else
	    {
		for(int p=0; p<my_atoms.length;p++){
	    	    popup.add(MenuItem(my_atoms[p],0));
		}
	    }
	    popup.show(toolButtons[TOOL_SETATOM],0,0);
	}
	if (e.getSource()==toolButtons[TOOL_TEMPLATE] && e.getButton()==MouseEvent.BUTTON3) 
	{
	    toolGroup.setSelected(toolButtons[TOOL_TEMPLATE].getModel(),true);
	    TemplateSelect();
	}
    }
    public void mouseReleased(MouseEvent e) {}   
    public void keyPressed(KeyEvent e) 
    {
    	// keyboard arrow-nudges
    	if (!e.isAltDown() && !e.isShiftDown() && !e.isControlDown() && !e.isMetaDown())
	{
	    if (e.getKeyCode()==KeyEvent.VK_UP) {editor.NudgeSelectedAtoms(0,0.05); return;}
	    if (e.getKeyCode()==KeyEvent.VK_DOWN) {editor.NudgeSelectedAtoms(0,-0.05); return;}
	    if (e.getKeyCode()==KeyEvent.VK_LEFT) {editor.NudgeSelectedAtoms(-0.05,0); return;}
	    if (e.getKeyCode()==KeyEvent.VK_RIGHT) {editor.NudgeSelectedAtoms(0.05,0); return;}
	}
    }
    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e)
    {    
    	// user typing in an element...
    	char ch=e.getKeyChar();
	if (ch>='A' && ch<='Z') typedElement=""+ch;
	else if (typedElement.length()==1 && ch>='a' && ch<='z') typedElement=typedElement+ch;
	else if (typedElement.compareTo("R")==0 && ch>='0' && ch<='9') typedElement=typedElement+ch;
	else {typedElement=""; return;}

	String elset=null;
	if (typedElement.length()>=2 && typedElement.charAt(0)=='R' && typedElement.charAt(1)>='0' && typedElement.charAt(1)<='9') 
	{
	    elset=typedElement;
	}
	else
	{
	    for (int n=1;n<Molecule.ELEMENTS.length;n++) if (typedElement.compareTo(Molecule.ELEMENTS[n])==0) {elset=typedElement;}
	}
	if (elset!=null)
	{
	    SelectElement(elset); 
	    toolGroup.setSelected(toolButtons[TOOL_SETATOM].getModel(),true);
	    editor.SetToolAtom(elset);
	}
    }
    
    public void TemplSelected(Molecule mol,int idx)
    {
    	lastTemplate=mol;
	templateIdx=idx;
	editor.SetToolTemplate(mol,idx);
    }
    public void MolSelected(EditorPane source,int idx,boolean dblclick)
    {
    	if (dblclick && idx!=0)
	{
	    ArrayList<Integer> selidx=new ArrayList<Integer>();
	    if (idx>0) selidx.add(idx);
	    else {selidx.add(editor.MolData().BondFrom(-idx)); selidx.add(editor.MolData().BondTo(-idx));}
	    Molecule newMol=(new DialogEdit(frameParent,editor.MolData(),selidx)).exec();
	    if (newMol!=null) editor.Replace(newMol);
	}
    }
    public void DirtyChanged(boolean isdirty)
    {
    	String str=frameParent==null ? "WIMSchem" : frameParent.getTitle();
	if (str.charAt(0)=='*') str=str.substring(1);
	if (isdirty) str="*"+str;
	if (frameParent!=null) frameParent.setTitle(str);
    }
    
    public void lostOwnership(Clipboard clipboard,Transferable contents) {} // don't care
    
    public void windowActivated(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowClosing(WindowEvent e) 
    {
    	FileQuit();
    }
    public void windowDeactivated(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowOpened(WindowEvent e) 
    {
    	if (firstResize)
	{
	    editor.ScaleToFit();
	    editor.repaint();
	    firstResize=false;
	}
	editor.requestFocusInWindow();
    }
}
