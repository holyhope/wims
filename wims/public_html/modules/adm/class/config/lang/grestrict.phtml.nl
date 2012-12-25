
!form reply
 <input type="hidden" name="job" value="grestrict" />
 <p>Hier kunt aangeven welke computer netwerkadressen
 mogen deelnemen aan Uw virtuele klas.<br /> 
 Deze instellingen blijven van kracht, en hebben een hogere prioriteit dan
 mogelijk andere de instellingen uit de individuele werkbladen
 </p>
 <div class="wimscenter">
 <table class="wimsnoborder wimscenter wimsform">
 <tr><td align="right">Toegestane adressen&nbsp;:</td>
 <td><input size="35" name="allow" value="$allow" /></td>
 </tr><tr>
 <td align="right">Uitgezonderd&nbsp;:</td>
 <td><input size="35" name="except" value="$except" /></td>
 </tr>
 </table>
 </div>
 <div class="wimscenter wimsform">
 <input type="submit" name="save" value="$wims_name_tosave" />&nbsp;&nbsp;&nbsp;
 <input type="submit" name="abandon" value="$wims_name_giveup" />
 </div>

!formend

<p>
U kunt een of meerdere adressen invullen in het invulveld.
De server zal elk ingevuld adres controleren op hostname en ipadres.
Zelfs al is het ingevulde adres een "sub-string" van de hostname of ip-adres
</p>
<div class="wims_smallremark">
    <b>Tip.</b>
     In het <span class="wims_label">Toegestane Adressen</span> veld, kunnen ook <em>openings tijden</em> worden aangebracht door de woorden: 
    <span class="tt wims_code_words">
&gt;yyyymmdd.hh:mm</span>
    (begin tijd) en/of
    <span class="tt wims_code_words">
&lt;yyyymmdd.hh:mm</span> (eind tijd). <br />
    De genoemde tijden moeten natuurlijk wel worden genoteerd in de <em>locale tijd van de Server</em><br />
    en moeten worden gescheiden van de andere "woorden" door spaties.
 </div>


