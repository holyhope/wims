
# How to update GeogebraWeb Library :

## Download new version

Download the latest GGBWeb at http://dev.geogebra.org/download/web/

Upgrade Geogebraweb :

	./compile --geogebra

## Modify "deployggb.js"
Download the latest "deployggb.js" here : [www.geogebra.org/scripts/deployggb.js](https://www.geogebra.org/scripts/deployggb.js)

## Adapt GGB code for WIMS

### Hack WIMS 1 :
GGB use it's own hosted library. To use WIMS included GGB version, replace the original *getTubeURL()* geogebra function in *deployggb.js* by this :

    var getTubeURL = function() {
        return "scripts/js/geogebra/geogebraweb/";
     };

### Hack WIMS 2 :
Then, modify in "deployggb.js" `codebase = "https://cdn.geogebra.org/apps/" + latestVersion + "/"`
 by `codebase = getTubeURL();`

### Hack WIMS 3 :
Since WIMS 4.13 use ISO-xxx charsets (not UTF-8), you must add this to each 3 geogebra "####.cache.js" files (web/, web3d/, webSimple/) :

	d.charset='utf-8';

just next to this :

	()+'js/properties_keys_'+c+'.js');`

## Publish new GGBWeb version into WIMS
* duplicate your geogebraweb folder
* rename it, so it contains the new version number
* zip it
* send it to wims.unice.fr/download server (ask his administrator bado@unice.fr)
* Update the variable vGeogebra in the ./compile file at WIMS root, so it contains the new Geogebra number version
* remove the duplicated folder and the zip archive

## See More...
Nb : if you're curious to see non-obfuscated geogebra code, you have to follow these explanations :
[dev.geogebra.org/trac/wiki/SetUp](https://dev.geogebra.org/trac/wiki/SetUp)