/*
    WIMSchem Elements: Chemistry molecular diagram drawing tool.
    
    (c) 2005 Dr. Alex M. Clark
    
    Released as GNUware, under the Gnu Public License (GPL)
    
    See www.gnu.org for details.
*/

package WIMSchem;

import java.util.*;
import java.text.*;
import java.lang.*;
import javax.swing.*;

// A very generic class containing static utility functions, which are painfully absent from the Java libraries.

public class Utils
{
    // pure convenience
    public static void write(String S) {System.out.print(S);}
    public static void writeln(String S) {System.out.println(S);}

    public static void errmsg(String Title,String Text)
    {
    	JOptionPane.showMessageDialog(null,Text,Title,JOptionPane.ERROR_MESSAGE);
    }

    // parse number-from-string functions which return a default value if it's badly formatted, instead of throwing an exception
    public static int safeInt(String S,int Def) 
    {
    	if (S==null) return Def;
	try {return new Integer(S).intValue();} 
	catch (NumberFormatException e) {return Def;}
    }
    public static int safeInt(String S) {return safeInt(S,0);}
    public static double safeDouble(String S,double Def) 
    {
    	if (S==null) return Def;
    	try {return new Double(S).doubleValue();} 
	catch (NumberFormatException e) {return Def;}
    }
    public static double safeDouble(String S) {return safeDouble(S,0);}
}
