
!form reply
 <input type="hidden" name="job" value="grestrict">
 Hier kunt aangeven welke computer netwerkadressen
 mogen deelnemen aan Uw virtuele klas.<br> 
 Deze instellingen blijven van kracht, en hebben een hogere prioriteit dan
 mogelijk andere de instellingen uit de individuele werkbladen

 <p>
 <table border="0">
 <tr><td align="right">Toegestane adressen&nbsp;:
 <td><input size="35" name="allow" value="$allow">
 <tr><td align="right">Uitgezonderd&nbsp;:
 <td><input size="35" name="except" value="$except">
 </table> <p>
 <input type="submit" name="save" value="$wims_name_tosave">&nbsp;&nbsp;&nbsp;
 <input type="submit" name="abandon" value="$wims_name_giveup">
</form>

<p>
U kunt een of meerdere adressen invullen in het invulveld.
De server zal elk ingevuld adres controleren op hostname en ipadres.
Zelfs al is het ingevulde adres een "sub-string" van de hostname of ip-adres
<p>
<div class="wims_smallremark">
    <b>Tip.</b>
     In het <span class="wims_label">Toegestane Adressen</span> veld, kunnen ook <em>openings tijden</em> worden aangebracht door de woorden: 
    <tt class="wims_code_words">
&gt;yyyymmdd.hh:mm</tt>
    (begin tijd) en/of
    <tt class="wims_code_words">
&lt;yyyymmdd.hh:mm</tt> (eind tijd). <br>
    De genoemde tijden moeten natuurlijk wel worden genoteerd in de <em>locale tijd van de Server</em><br>
    en moeten worden gescheiden van de andere "woorden" door spaties.
 </div>


