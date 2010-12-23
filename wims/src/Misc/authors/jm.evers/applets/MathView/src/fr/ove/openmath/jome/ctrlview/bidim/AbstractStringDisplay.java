/*
$Id: AbstractStringDisplay.java,v 1.3 2003/02/18 11:48:46 sander Exp $
*/


/*
Copyright (C) 2001-2002 Mainline Project (I3S - ESSI - CNRS -UNSA)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

For further information on the GNU Lesser General Public License,
see: http://www.gnu.org/copyleft/lesser.html
For further information on this library, contact: mainline@essi.fr
*/


package fr.ove.openmath.jome.ctrlview.bidim;

import java.awt.*;
import java.awt.event.*;
import java.text.*;
import fr.ove.utils.NumberUtils;
import fr.ove.openmath.jome.ctrlview.bidim.StringLayout;
import fr.ove.openmath.jome.ctrlview.bidim.Display;
import fr.ove.openmath.jome.ctrlview.bidim.GraphicContext;
import fr.ove.openmath.jome.model.*;
import fr.ove.openmath.jome.model.events.ModelEvent;

/**
* The display of a String.
*
* @author © 1999 DIRAT Laurent
* @version 2.0  04/08/1999
*/
public abstract class AbstractStringDisplay extends BidimDisplay {
    /**
    * The string that the display represents.
    */
    private String string;
        
    /**
    * The constructor.
    * @param graphicContext the graphic context of the display.
    * @param string the string to display
    */
    public AbstractStringDisplay(GraphicContext graphicContext, String string) {
        super(graphicContext);
        this.string = string;
    }
    
    /**
    * Sets a new string to the display.
    * @param string the string to set.
    */
    public void setString( String string ) {
        this.string = string;
    }
    
    /**
    * Returns the string to display.
    * @return the string.
    */
    public String getString() {
        return string;
    }
    
    /**
    * Scales the display.
    */
    public void scaleDisplay() {
        //System.out.println("string : " + string +"   Level = " + getLevel());
        setTheFont(getGraphicContext().scaleFont(getLevel()));
        // Il faut que le layout manager recalcule les attributs du display.
        setComputeAttributes(true);
        // Ceci est nécessaire pour que ce soit le layout manager qui retourne
        // la preferredSize du display, et donc qu'il y ait recalcul des attributs.
        // Sinon, le container considère qu'il a une taille valide, et donc retourne
        // comme preferredSize, la précédente, sans qu'il demande le recalcul au LM.
        invalidate();
    }    

    /**
    * Paints the display.
    * @param g where we paint the display.
    */
    public void paint(Graphics g) {
        super.paint(g);
        
        Color old = g.getColor();
        Font oldFont = g.getFont();
        Rectangle bounds = getBounds();
        
        if (isSelected())
            g.setColor(getSelectionColor());
        else
            g.setColor(getBackgroundColor());
            
        g.fillRect(0, 0, bounds.width /*- 1*/, bounds.height /*- 1*/);
        
        g.setColor(getForegroundColor());
        g.setFont(getFont());
        
        if (weDrawBounds())
            g.drawRect(0, 0, bounds.width - 1, bounds.height - 1);
        
        
        if ( string.equals("*") )
            g.drawString(string, 1, getHeight());
        else if ( string.equals("-") )
            g.drawString(string, 1, getAscent() - (int) Math.round(getDescent()*(40.0f/100.0f)));
        else
            g.drawString(string, 1, getAscent());
        
        /*
        // on trace la baseline
        g.setColor(Color.red);
        g.drawLine(0, getAscent(), bounds.width, getAscent());
        */
        
        g.setColor(old);
        g.setFont(oldFont);
    }
    
    /**
    * Returns the insertion position for the moving of displays.
    * @param mouseX the mouse position.
    */
    public int computeInsertionPosition(int mouseX) {
        int insertionPosition;
        // Si l'instance courante est un display d'opérateur, alors la position
        // d'insertion est la position de l'opérande dont le display suit l'instance
        // courante.
        if (isSymbolOperatorDisplay()) {
            Display display = (Display) getParent();
            display = (Display) display.getComponent(getRank() + 1);  // On est sûr de pouvoir prendre rank+1
            // puisque si on est sur une display d'opérateur, au pire on a un template.
            insertionPosition = ((FormulaTreeStructure) display.getListener()).getRank();
        }
        else {
            // On regarde la position de la souris.
            // Si elle est inférieure à la moitié de la largeur de l'instance, alors
            // la position d'insertion est la position de l'opérande dont l'instance est
            // le display. Sinon, la position d'insertion est la position de l'opérande 
            // dont l'instance l'instance est le display + 1.
            if (mouseX <= (getWidth() / 2))
                insertionPosition = ((FormulaTreeStructure) getListener()).getRank();
            else
                insertionPosition = ((FormulaTreeStructure) getListener()).getRank() + 1;
                // Pas de pb de test pour savoir si on n'est pas sur le dernier opérande
                // puisqu'on est obligé dans ce cas de retourner le nbre réel + 1 pour dire
                // effectivement que l'on insère à la dernière position.
        }
        // On retourne la position d'insertion calculée.
        return insertionPosition;
    }
    
    public void ToString() {
        super.ToString();
        System.out.println(" string = " + string);
    }

    public void whoAmI() {
        System.out.println("I am the StringDisplay : " + string);
        System.out.println("My level is " + getLevel());
    }
    
}