/*
$Id: LinearParserEventSource.java,v 1.3 2003/02/18 11:48:46 sander Exp $
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


package fr.ove.openmath.jome.ctrl.linear.events;

/**
* the interface to implement to become a LinearParserEvent event source.
*
* @author � 1999 DIRAT Laurent
* @version 1.0 06/10/1999
*/
public interface LinearParserEventSource {
    /**
    * Registers another listener of the instance.
    * @param linearParserListener the listener to add.
    */
    public void addLinearParserListener(LinearParserListener linearParserListener);

    /**
    * Removes a listener.
    * @param linearParserListener the listener to remove.
    */
    public void removeLinearParserListener(LinearParserListener linearParserListener);

    /**
    * Fires a LinearParserEvent event to registered listeners.
    * @param linearParserEvent event encapsulating relevant information.
    */
    public void fireLinearParserEvent(LinearParserEvent linearParserEvent);
}