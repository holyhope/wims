We use `Bower` to automatically download JS packages/plugins,
And then we use `Grunt` to perform special tasks (concat, minify, verify ...)

# Installation
--------------

## Install Dependencies :
*  You need to install node, npm and git.
*  See here : [install Bower](http://bower.io#install-bower)

## Install Bower :
    npm install -g bower

## Install Grunt :
    npm update
    npm install -g grunt-cli


# Upgrade package manager
-------------------------
from `_packages` directory :

    npm update
    npm install -g bower
    npm install -g grunt-cli
    bower update -p


# Manage Bower Packages
-----------------------

## List all installed plugins :
    bower list

## Update Javascripts plugins via Bower :
    bower update --save
*nb : After each jquery-ui update, look at these URL :*

* Tabs : [searchform](http://localhost/wims/wims.cgi?cmd=new&module=home&search_keywords=oef&search_category=A&search_lang=fr#searchform)
* Menu : [H6/algebra/docnatural.fr](http://localhost/wims/wims.cgi?module=H6/algebra/docnatural.fr)

## Update Javascripts plugins for production (without devDepedencies) :
    bower update -p


# Download new Package(s)
-------------------------
    bower install <package> --save


# Migrate files from _packages/ to wims/
  #  After each update, Grunt is handy to automatically compress js + css, and move each files at is wims destination. simply call "grunt"

    grunt

#  Documentations
-----------------
* [Bower docs](http://bower.io/docs/creating-packages/)
* [Grunt HowTo (video fr)](http://www.grafikart.fr/tutoriels/grunt/grunt-introduction-470)
* [Grunt "getting started"](http://gruntjs.com/getting-started)
