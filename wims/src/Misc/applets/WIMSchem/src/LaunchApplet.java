/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2005 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
// This launches the application from the applet...
// so the added code is no good at all.
public class LaunchApplet extends JApplet implements ActionListener
{
    JButton openbutton;
    public Properties translation;

    public void init()
    {
        System.getProperty("java.version");
	String language = getParameter("language");
	if(language != null){language=language.toLowerCase();}else{language="en";}
	translation=loadProperties(language);
    	openbutton=new JButton(translation.getProperty("Open_WIMSchem"));
	add(openbutton);
    	openbutton.addActionListener(this);
    }
    
    public Properties loadProperties (String l){
	Properties P=new Properties();
	try{
	    InputStream in = getClass().getResourceAsStream("/lang/WIMSchemProperties_"+l+".properties");
	    P.load(in);in.close();
	    return P;
	} 
	catch (Exception e){ System.out.println("error reading /lang/WIMSchemProperties_"+l+".properties\n"+e);}         
        return null;                                                                                                               
    }  


    public void actionPerformed(ActionEvent e) 
    {
    	if (e.getSource()==openbutton)
	{
    	    MainWindow mw=new MainWindow(null,false,translation);
	    mw.setVisible(true);
	    System.out.println("foo");
	}
    }

    public String getAppletInfo() 
    {
    	return translation.getProperty("WIMSchem_Applet_Description");
    }
}



