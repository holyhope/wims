
Aquí están los fuentes separados por comas de las calificaciones introducidas 
manualmente, las puede modificar directamente (ver las 
explicaciones de abajo).
<p>
!form reply
!mexec catraw.sh
<p><input type="submit" name="reg" value="$wims_name_tosave">
</form> <p>
<b>Atención.</b>¡El servidor no comprueba los datos que envía para su grabación!
<p>
Por favor, no modifique la estructura de líneas del archivo, los
caracteres especiales de separación de los campos (`:' y `,'), ni los nombres de los
participantes. En caso contrario sus puntuaciones podrían llegar a 
ser inutilizables.
<p>
<b>Estructura del archivo.</b> Cada línea debe comenzar 
con el caracter `:', excepto las líneas segunda y tercera.
<p>
La primera línea es el porcentaje de la media de las puntuaciones introducidas 
manualmente en el cálculo del total.
<p>
La segunda línea es una lista de los títulos de la columna de puntuaciones.
<p>
La tercera línea es la lista de pesos de cada columna.
<p>
Las otras líneas son listas de campos separados por comas: 
el campo 1 es el nombre de acceso del participante, el campo 2 es el nombre 
real, y el resto son sus notas columna por columna.

<p>

