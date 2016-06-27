We use `Bower` to automatically download JS packages/plugins,
And then we use `Grunt` to perform special tasks (concat, minify, ...)

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


# Upgrade
---------
from `_packages` directory :

    npm update
    npm install -g bower
    npm install -g grunt-cli
    bower update -p


# Manage Bower Packages
-----------------------

## list all installed plugins :
    bower list

## update Javascripts plugins via Bower :
    bower update --save

## update Javascripts plugins for production (without devDepedencies) :
    bower update -p


# Download new Package(s)
-------------------------
    bower install <package> --save


# Migrate files from _packages/ to wims/
  #  After each update, Grunt is handy to automatically compress js + css, and move each files at is wims destination. simply call "grunt"
    grunt

#  Documentations
------------------------
* [Bower docs](http://bower.io/docs/creating-packages/)
* [Grunt HowTo (video fr)](http://www.grafikart.fr/tutoriels/grunt/grunt-introduction-470)
* [Grunt "getting started"](http://gruntjs.com/getting-started)
