
Hier is de lijst van handmatig ingevoerde cijfers,
 deze kunen rechtstreeks worden aangepast. (zie uitleg beneden)

!form reply
!mexec catraw.sh
<p><input type="submit" name="reg" value="$wims_name_tosave" />

!formend

<b>Waarschuwing.</b> 
De WIMS server controleert niet de juistheid van de opgestuurde gegevens.
<p>
De regelstructuur, de speciale scheidingstekens (";" en ",") en
de gebruikersnamen, mogen niet worden veranderd, 
omdat anders het bestand onbruikbaar wordt.
</p><p>
<b>Structuur van dit bestand.</b> Elke regel moet met een 
":" karakter beginnen, behalve de tweede en derde regel.
</p><p>
De eerste regel is het gemiddelde percentage van het handmatig ingevoerde cijfer ten 
opzichte van het totaal. 
</p><p>
De tweede regel is de lijst van titels van de cijfer kolommen.
</p><p>
De derde regel is het gewicht van elke kolom.
</p><p>
De andere regels zijn "komma gescheiden" velden; 
veld 1 is de login naam , veld 2 is de echte naam van de leerling.
en de rest zijn kolom per kolom de cijfers. 
</p><p>

