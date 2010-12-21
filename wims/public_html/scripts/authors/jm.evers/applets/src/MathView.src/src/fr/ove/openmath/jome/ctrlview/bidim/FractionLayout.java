/*
$Id: FractionLayout.java,v 1.3 2003/02/18 11:48:46 sander Exp $
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
import fr.ove.openmath.jome.ctrlview.bidim.DisplayLayout;
import fr.ove.openmath.jome.ctrlview.bidim.Display;
import fr.ove.openmath.jome.ctrlview.bidim.Bar;
import fr.ove.openmath.jome.ctrlview.bidim.selection.events.SelectionEvent;
import fr.ove.openmath.jome.model.*;
import fr.ove.utils.FontInfo;

/**
* A layout manager that lays components to be displayed as a fraction.
*
* @author � 1999 DIRAT Laurent
* @version 2.0 15/12/1999
*/
public class FractionLayout extends BetweenOperatorLayout {
    /**
    * Computes the size of the display according to its children size (if any),
    * and its different attributes.
    * @return the size of the display.
    */
    public Dimension computeAttributes() {
        SymbolDisplay displayBar = null;
        Bar fractionBar = null;
        
        updateLevel(displayToLay.getLevel());
        
        // On est dans le cas particulier d'un symbol qui ne connait pas sa taille � l'avance.
        // Pour que cela puisse fonctionner correctement avec les autres displays, il faut qu'on
        // lui precise sa preferred size.
        // On met sa longueur � 0 pour �viter les �largissements infinis lors des diff�rents retaillages
        // dus aux d�siconifications. (On rajoute 8 pixels � sa largeur un peu plus bas)
        displayBar = (SymbolDisplay) displayToLay.getComponent(0);
        displayBar.setWidth(0);
        fractionBar = (Bar) displayBar.getSymbol();
        fractionBar.setWidth(0);
        
        fractionBar.setHeight(FontInfo.getLineThickness(displayToLay, displayToLay.getFont())); // la hauteur fixe aussi ascent et descent
        
        displayBar.setComputeAttributes(true);
    
        // On calcule les attributs des display enfants comme si 
        // on avait affaire � un VerticalCenteredLayout
        Dimension dim = super.computeAttributes(); 
        
        // La diff�rence r�side en le calcul suppl�mentaire de la taille de la 
        // de fraction que l'on ne peut fixer apr�s avoir calcul� la largeur
        // du num�rateur et du d�nominateur
        fractionBar.setWidth(dim.width + 8);
        displayBar.setSize(fractionBar.getSize());
        
        dim.width = displayBar.getWidth();
        displayToLay.setSize(dim);
        
        return dim;
    }
    
    /**
    * Returns the display of the operator
    */
    public Display createOperatorDisplay() {
        SymbolDisplay fractionBar = new SymbolDisplay(displayToLay.getGraphicContext(), new Bar());
        // Le display de la barre de fraction est le display d'un op�rateur (on peut le consid�rer comme tel)
        fractionBar.setIsSymbolOperatorDisplay(true);
        
        return fractionBar;
    }    
}
