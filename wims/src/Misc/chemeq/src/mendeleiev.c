// -*- coding: utf-8 -*-
//file mendeleiev.c

#include "chemeq.h"
// not i18nalized ?
#define N_(a) a

// data taken from Kyle Burton's gperiodic free program

struct table_entry table [] = {
  {N_("Hydrogen"), "H", "1", "1.00794", "14.01", "20.28", "2.20"},
  {N_("Helium"), "He", "2", "4.002602", "0.95", "4.216", "0.0"},

  {N_("Lithium"), "Li", "3", "6.941", "553.69", "1118.15", "0.98"},
  {N_("Beryllium"), "Be", "4", "9.01218", "1551", "3243", "1.57"},
  {N_("Boron"), "B", "5", "10.811", "2573", "3931", "2.04"},
  {N_("Carbon"), "C", "6", "12.011", "3820", "5100", "2.55"},
  {N_("Nitrogen"), "N", "7", "14.00674", "63.29", "77.4", "3.04"},
  {N_("Oxygen"), "O", "8", "15.9994", "54.8", "90.19", "3.44"},
  {N_("Fluorine"), "F", "9", "18.998403", "53.53", "85.01", "3.98"},
  {N_("Neon"), "Ne", "10", "20.1797", "48", "27.1", "0.0"},

  {N_("Sodium"), "Na", "11", "22.989768", "370.96", "1156.1", "0.93"},
  {N_("Magnesium"), "Mg", "12", "24.305", "922", "1363", "1.31"},
  {N_("Aluminum"), "Al", "13", "26.981539", "933.5", "2740", "1.61"},
  {N_("Silicon"), "Si", "14", "28.0855", "1683", "2628", "1.90"},
  {N_("Phosphorus"), "P", "15", "30.973762", "317.3", "553", "2.19"},
  {N_("Sulfur"), "S", "16", "32.066", "386", "717.824", "2.58"},
  {N_("Chlorine"), "Cl", "17", "35.4527", "172.2", "238.6", "3.16"},
  {N_("Argon"), "Ar", "18", "39.948", "83.8", "87.3", "0.0"},

  {N_("Potassium"), "K", "19", "39.0983", "336.8", "1047", "0.82"},
  {N_("Calcium"), "Ca", "20", "40.078", "1112", "1757", "1.00"},
  {N_("Scandium"), "Sc", "21", "44.95591", "1814", "3104", "1.36"},
  {N_("Titanium"), "Ti", "22", "47.88", "1933", "3560", "1.54"},
  {N_("Vanadium"), "V", "23", "50.9415", "2160", "3650", "1.63"},
  {N_("Chromium"), "Cr", "24", "51.9961", "2130", "2945", "1.66"},
  {N_("Manganese"), "Mn", "25", "54.93805", "1517", "2235", "1.55"},
  {N_("Iron"), "Fe", "26", "55.847", "1808", "3023", "1.83"},
  {N_("Cobalt"), "Co", "27", "58.9332", "1768", "3143", "1.88"},
  {N_("Nickel"), "Ni", "28", "58.6934", "1726", "3005", "1.91"},
  {N_("Copper"), "Cu", "29", "63.546", "1356.6", "2840", "1.90"},
  {N_("Zinc"), "Zn", "30", "65.39", "692.73", "1180", "1.65"},
  {N_("Gallium"), "Ga", "31", "69.723", "302.93", "2676", "1.81"},
  {N_("Germanium"), "Ge", "32", "72.61", "1210.6", "3103", "2.01"},
  {N_("Arsenic"), "As", "33", "74.92159", "1090", "876", "2.18"},
  {N_("Selenium"), "Se", "34", "78.96", "490", "958.1", "2.55"},
  {N_("Bromine"), "Br", "35", "79.904", "265.9", "331.9", "2.96"},
  {N_("Krypton"), "Kr", "36", "83.8", "116.6", "120.85", "0.0"},

  {N_("Rubidium"), "Rb", "37", "85.4678", "312.2", "961", "0.82"},
  {N_("Strontium"), "Sr", "38", "87.62", "1042", "1657", "0.95"},
  {N_("Yttrium"), "Y", "39", "88.90585", "1795", "3611", "1.22"},
  {N_("Zirconium"), "Zr", "40", "91.224", "2125", "4650", "1.33"},
  {N_("Niobium"), "Nb", "41", "92.90638", "2741", "5015", "1.6"},
  {N_("Molybdenum"), "Mo", "42", "95.94", "2890", "4885", "2.16"},
  {N_("Technetium"), "Tc", "43", "97.9072", "2445", "5150", "1.9"},
  {N_("Ruthenium"), "Ru", "44", "101.07", "2583", "4173", "2.2"},
  {N_("Rhodium"), "Rh", "45", "102.9055", "2239", "4000", "2.28"},
  {N_("Palladium"), "Pd", "46", "106.42", "1825", "3413", "2.20"},
  {N_("Silver"), "Ag", "47", "107.8682", "1235.1", "2485", "1.93"},
  {N_("Cadmium"), "Cd", "48", "112.411", "594.1", "1038", "1.69"},
  {N_("Indium"), "In", "49", "114.818", "429.32", "2353", "1.78"},
  {N_("Tin"), "Sn", "50", "118.71", "505.1", "2543", "1.96"},
  {N_("Antimony"), "Sb", "51", "121.760", "903.9", "1908", "2.05"},
  {N_("Tellurium"), "Te", "52", "127.6", "722.7", "1263", "2.1"},
  {N_("Iodine"), "I", "53", "126.90447", "386.7", "457.5", "2.66"},
  {N_("Xenon"), "Xe", "54", "131.29", "161.3", "166.1", "0.0"},

  {N_("Cesium"), "Cs", "55", "132.90543", "301.6", "951.6", "0.79"},
  {N_("Barium"), "Ba", "56", "137.327", "1002", "1910", "0.89"},

  {N_("Lanthanum"), "La", "57", "138.9055", "1194", "3730", "1.10"},
  {N_("Cerium"), "Ce", "58", "140.115", "1072", "3699", "1.12"},
  {N_("Praseodymium"), "Pr", "59", "140.90765", "1204", "3785", "1.13"},
  {N_("Neodymium"), "Nd", "60", "144.24", "1294", "3341", "1.14"},
  {N_("Promethium"), "Pm", "61", "144.9127", "1441", "3000", "0.0"},
  {N_("Samarium"), "Sm", "62", "150.36", "1350", "2064", "1.17"},
  {N_("Europium"), "Eu", "63", "151.965", "1095", "1870", "0.0"},
  {N_("Gadolinium"), "Gd", "64", "157.25", "1586", "3539", "1.20"},
  {N_("Terbium"), "Tb", "65", "158.92534", "1629", "3296", "0.0"},
  {N_("Dysprosium"), "Dy", "66", "162.50", "1685", "2835", "1.22"},
  {N_("Holmium"), "Ho", "67", "164.93032", "1747", "2968", "1.23"},
  {N_("Erbium"), "Er", "68", "167.26", "1802", "3136", "1.24"},
  {N_("Thulium"), "Tm", "69", "168.93421", "1818", "2220", "1.25"},
  {N_("Ytterbium"), "Yb", "70", "173.04", "1097", "1466", "0.0"},

  {N_("Lutetium"), "Lu", "71", "174.967", "1936", "3668", "1.27"},
  {N_("Hafnium"), "Hf", "72", "178.49", "2503", "5470", "1.3"},
  {N_("Tantalum"), "Ta", "73", "180.9479", "3269", "5698", "1.5"},
  {N_("Tungsten"), "W", "74", "183.84", "3680", "5930", "2.36"},
  {N_("Rhenium"), "Re", "75", "186.207", "3453", "5900", "1.9"},
  {N_("Osmium"), "Os", "76", "190.23", "3327", "5300", "2.2"},
  {N_("Iridium"), "Ir", "77", "192.22", "2683", "4403", "2.20"},
  {N_("Platinum"), "Pt", "78", "195.08", "2045", "4100", "2.28"},
  {N_("Gold"), "Au", "79", "196.96654", "1337.58", "3080", "2.54"},
  {N_("Mercury"), "Hg", "80", "200.59", "234.28", "629.73", "2.00"},
  {N_("Thallium"), "Tl", "81", "204.3833", "576.6", "1730", "1.62"},
  {N_("Lead"), "Pb", "82", "207.2", "600.65", "2013", "1.8"},
  {N_("Bismuth"), "Bi", "83", "208.98037", "544.5", "1883", "2.02"},
  {N_("Polonium"), "Po", "84", "208.9824", "527", "1235", "2.0"},
  {N_("Astatine"), "At", "85", "209.9871", "575", "610", "2.2"},
  {N_("Radon"), "Rn", "86", "222.0176", "202", "211.4", "0.0"},

  {N_("Francium"), "Fr", "87", "223.0197", "300", "950", "0.7"},
  {N_("Radium"), "Ra", "88", "226.0254", "973", "1413", "0.9"},

  {N_("Actinium"), "Ac", "89", "227.0278", "1320", "3470", "1.1"},
  {N_("Thorium"), "Th", "90", "232.0381", "2028", "5060", "1.3"},
  {N_("Protactinium"), "Pa", "91", "231.03588", "2113", "4300", "1.5"},
  {N_("Uranium"), "U", "92", "238.0289", "1405.5", "4018", "1.38"},
  {N_("Neptunium"), "Np", "93", "237.048", "913", "4175", "1.36"},
  {N_("Plutonium"), "Pu", "94", "244.0642", "914", "3505", "1.28"},
  {N_("Americium"), "Am", "95", "243.0614", "1267", "2880", "1.3"},
  {N_("Curium"), "Cm", "96", "247.0703", "1620", "n/a", "1.3"},
  {N_("Berkelium"), "Bk", "97", "247.0703", "n/a", "n/a", "1.3"},
  {N_("Californium"), "Cf", "98", "251.0796", "1170", "n/a", "1.3"},
  {N_("Einsteinium"), "Es", "99", "252.083", "1130", "n/a", "1.3"},
  {N_("Fermium"), "Fm", "100", "257.0951", "1800", "n/a", "1.3"},
  {N_("Mendelevium"), "Md", "101", "258.1", "1100", "n/a", "1.3"},
  {N_("Nobelium"), "No", "102", "259.1009", "1100", "n/a", "1.3"},

  {N_("Lawrencium"), "Lr", "103", "262.11", "n/a", "n/a", "n/a"},
  {N_("Rutherfordium"), "Rf", "104", "[261]", "n/a", "n/a", "n/a"},
  {N_("Dubnium"), "Db", "105", "[262]", "n/a", "n/a", "n/a"},
  {N_("Seaborgium"), "Sg", "106", "[266]", "n/a", "n/a", "n/a"},
  {N_("Bohrium"), "Bh", "107", "[264]", "n/a", "n/a", "n/a"},
  {N_("Hassium"), "Hs", "108", "[269]", "n/a", "n/a", "n/a"},
  {N_("Meitnerium"), "Mt", "109", "[268]", "n/a", "n/a", "n/a"},
  {N_("Ununnilium"), "Uun", "110", "[269]", "n/a", "n/a", "n/a"},
  {N_("Unununium"), "Uuu", "111", "[272]", "n/a", "n/a", "n/a"},
  {N_("Ununbium"), "Uub", "112", "[277]", "n/a", "n/a", "n/a"},
  {N_("Ununtrium"), "Uut", "113", "n/a", "n/a", "n/a", "n/a"},
  {N_("Ununquadium"), "Uuq", "114", "[289]", "n/a", "n/a", "n/a"},
  {N_("Ununpentium"), "Uup", "115", "n/a", "n/a", "n/a", "n/a"},
  {N_("Ununhexium"), "Uuh", "116", "n/a", "n/a", "n/a", "n/a"},
  {N_("Ununseptium"), "Uus", "117", "n/a", "n/a", "n/a", "n/a"},
  {N_("Ununoctium"), "Uuo", "118", "n/a", "n/a", "n/a", "n/a"},
  {(char *)NULL}
};
