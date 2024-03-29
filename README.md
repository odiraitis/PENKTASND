# PENKTASND
## OOP-5 UZDUOTIS


### ASOCIOTYVIU KONTEINERIU NAUDOJIMAS.

1. Reikejo suskaičiuoti, kiek kartų kiekvienas skirtingas žodis pasikartoja mano tekst. Tuomet realizacijos output'e ("isvestis.txt") išvesti skirtingus žodžius (kableliai, taškai ir kiti skyrybos ženklai nėra žodžiu dalis!), kurie pasikartojo dažniau negu 1 kartą, o taip pat ir count'erį, nurodantį kiek kartų konkretus žodis pasikartojo.

2. Išvesti, kurioje teksto vietoje (kurioje(-iose) teksto eilutėse) kiekvienas iš daugiau negu vieną kartą pasikartojantis žodis buvo paminėtas.

3. URL adresų suradimas mano tekste. Tikslas - iš to teksto išrinkti visus URL'us ir grąžiai atspausdinti ekrane (ar išvesti į failą)!
Tam naudojau:

* std::set
* std::map

 ``` c++
 // pair and map type
using WordInfo = std::pair<int, std::set<int> >;
using WordMap = std::map<std::string, WordInfo>;
 ```
 
 Kiekvieną eilutę getlineinau ir transformavau į mažąsias raides (kad nebūtų kuriozų jog žodis "mama" nėra lygus "Mama" :
 
  ``` c++
   while(std::getline(in, eilute))
    {
        std::transform(eilute.begin(), eilute.end(), eilute.begin(), ::tolower); 
        std::stringstream read(eilute);
        std::string word;
        .......
     }
   ```
  Šiame cikle skaičiau po žodį (pas mane pavadinta word) ir erasinau skyrybos ženklus kurie yra prie to žodžio "prilipę".
  
  * Su std::regex tikrinau ar "word" yra URL, jeigu taip insertinau į mapą pavadinimu LINKAS.
  * Į std::map insertinau žodį (kaip first key), kiek kartų žodis pasikartoja (kaip second.first key) ir kuriose eilutėse (kaip second.second key);
  * Tuomet "pliusinau" žodžio skaičių (kiek jis pasikartoja);
  
  
  ``` c++
 
  using WordMap = std::map<std::string, WordInfo>;
  WordMap wm;
  
  std::map <std::string, int> linkas;
  
   while(std::getline(in, eilute))
    {
      .......
        while (read >> word)
        {
            
            if(std::regex_match(word, std::regex("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-   a-zA-Z0-9@:%_\\+.~#?&//=]*)") )){
                linkas.insert(std::pair<std::string,int>(word,line_number));
            }
            
             word.erase (std::remove_if(word.begin(), word.end(), ::ispunct), word.end()); // istrinu skyrybos zenklus
            // we call map::insert, not `[ ]` to insert into a map
            
            auto pr = wm.insert({word, {0,std::set<int>()}});
            
            // the return value of map::insert gives us a pair, where the first is
            // an iterator to the item in the map
            auto& mapIter = pr.first;
            // increment the word count
            ++(mapIter->second.first);
            
            // insert the line number into the set
            mapIter->second.second.insert(line_number);
            
        }
        ++line_number;
      }
  ``` 
  
  
  Taigi mano output failas "isvestis.txt" atrodo taip :
  
   ``` 
  Words that appear more than once in the text: 

The word  "5g" appears 3 times on the following lines:
61 62 77 
The word  "android" appears 9 times on the following lines:
3 15 16 18 37 38 40 43 46 
The word  "apie" appears 3 times on the following lines:
28 39 46 
The word  "atsisiųsti" appears 2 times on the following lines:
10 52 
The word  "atstovas" appears 3 times on the following lines:
10 12 30 
The word  "atviro" appears 4 times on the following lines:
7 38 47 50 
The word  "be" appears 3 times on the following lines:
28 63 80 
The word  "bei" appears 3 times on the following lines:
4 6 10 
The word  "bendrovė" appears 3 times on the following lines:
61 63 80 
The word  "bendrovės" appears 3 times on the following lines:
70 71 75 
The word  "bloomberg" appears 3 times on the following lines:
34 35 70 
The word  "broadcom" appears 4 times on the following lines:
32 35 69 70 
The word  "bus" appears 2 times on the following lines:
21 56 
The word  "būtinos" appears 2 times on the following lines:
32 60 
The word  "dalių" appears 5 times on the following lines:
66 72 75 78 79 
The word  "dar" appears 2 times on the following lines:
26 29 
The word  "darbuotojams" appears 2 times on the following lines:
32 70 
The word  "dolerių" appears 2 times on the following lines:
67 
The word  "duomenimis" appears 3 times on the following lines:
39 66 70 
The word  "ekspertai" appears 2 times on the following lines:
27 73 
The word  "esamų" appears 2 times on the following lines:
24 51 
The word  "gali" appears 4 times on the following lines:
14 55 58 77 
The word  "galės" appears 3 times on the following lines:
10 18 52 
The word  "gamintojai" appears 3 times on the following lines:
31 54 69 
The word  "gmail" appears 4 times on the following lines:
4 17 48 53 
The word  "google" appears 24 times on the following lines:
1 2 4 5 9 10 11 12 15 17 19 29 39 40 48 49 51 52 53 56 59 
The word  "huawei" appears 32 times on the following lines:
2 3 5 9 12 14 16 18 20 23 24 26 27 29 30 32 36 37 40 45 49 51 57 58 65 66 68 71 74 79 
The word  "iki" appears 2 times on the following lines:
33 71 
The word  "inc" appears 4 times on the following lines:
4 31 32 
The word  "intel" appears 4 times on the following lines:
31 34 69 70 
The word  "ir" appears 32 times on the following lines:
6 9 11 12 13 17 18 19 24 27 32 33 34 37 38 41 42 46 49 50 52 54 56 57 64 69 70 72 73 74 79 
The word  "iš" appears 7 times on the following lines:
24 25 31 35 43 49 68 
The word  "išmaniųjų" appears 7 times on the following lines:
9 14 16 59 63 64 80 
The word  "jau" appears 2 times on the following lines:
44 62 
The word  "jav" appears 13 times on the following lines:
8 22 26 28 35 46 64 67 68 69 72 74 
The word  "jeigu" appears 2 times on the following lines:
60 74 
The word  "jis" appears 2 times on the following lines:
13 48 
The word  "jog" appears 2 times on the following lines:
71 79 
The word  "jungtinių" appears 2 times on the following lines:
22 76 
The word  "juodąjį" appears 2 times on the following lines:
8 20 
The word  "jų" appears 2 times on the following lines:
12 57 
The word  "kad" appears 5 times on the following lines:
1 23 32 46 55 
The word  "kaip" appears 6 times on the following lines:
17 38 48 53 57 60 
The word  "karto" appears 3 times on the following lines:
24 31 35 
The word  "kas" appears 3 times on the following lines:
25 36 46 
The word  "kinijoje" appears 2 times on the following lines:
44 56 
The word  "kinijos" appears 6 times on the following lines:
1 7 14 55 61 71 
The word  "kodo" appears 4 times on the following lines:
7 38 48 50 
The word  "kompanijai" appears 3 times on the following lines:
8 21 47 
The word  "kompanijos" appears 2 times on the following lines:
27 58 
The word  "kurios" appears 3 times on the following lines:
6 43 67 
The word  "licenciją" appears 2 times on the following lines:
38 50 
The word  "lustų" appears 2 times on the following lines:
27 31 
The word  "maždaug" appears 2 times on the following lines:
67 
The word  "mlrd" appears 2 times on the following lines:
67 
The word  "naudotis" appears 3 times on the following lines:
3 10 43 
The word  "naujinius" appears 3 times on the following lines:
10 52 54 
The word  "ne" appears 3 times on the following lines:
24 31 35 
The word  "nebeturės" appears 2 times on the following lines:
17 18 
The word  "negalės" appears 2 times on the following lines:
3 74 
The word  "nes" appears 4 times on the following lines:
14 26 50 58 
The word  "neteks" appears 2 times on the following lines:
4 15 
The word  "nukentės" appears 2 times on the following lines:
25 74 
The word  "nuo" appears 3 times on the following lines:
40 65 74 
The word  "nėra" appears 2 times on the following lines:
25 50 
The word  "o" appears 2 times on the following lines:
56 77 
The word  "operacinės" appears 4 times on the following lines:
3 15 37 53 
The word  "pabrėžė" appears 3 times on the following lines:
10 48 61 
The word  "pagal" appears 2 times on the following lines:
37 58 
The word  "pagrindinių" appears 2 times on the following lines:
72 75 
The word  "pakomentuoti" appears 2 times on the following lines:
31 35 
The word  "pasaulio" appears 3 times on the following lines:
64 73 78 
The word  "pasaulyje" appears 2 times on the following lines:
8 39 
The word  "paslaugas" appears 2 times on the following lines:
28 59 
The word  "paslaugomis" appears 2 times on the following lines:
6 41 
The word  "paslaugų" appears 4 times on the following lines:
12 17 19 75 
The word  "pat" appears 5 times on the following lines:
16 29 36 58 68 
The word  "patvirtino" appears 3 times on the following lines:
13 19 23 
The word  "per" appears 3 times on the following lines:
42 49 53 
The word  "play" appears 7 times on the following lines:
4 12 17 49 52 53 
The word  "poveikį" appears 3 times on the following lines:
26 30 77 
The word  "praneša" appears 3 times on the following lines:
1 7 63 
The word  "pranešimo" appears 2 times on the following lines:
33 71 
The word  "pranešė" appears 6 times on the following lines:
11 30 32 42 44 71 
The word  "prašymus" appears 2 times on the following lines:
30 35 
The word  "prekybos" appears 3 times on the following lines:
20 22 35 
The word  "prie" appears 10 times on the following lines:
2 4 15 17 19 25 37 47 51 72 
The word  "prieigos" appears 5 times on the following lines:
4 15 17 18 72 
The word  "prieigą" appears 5 times on the following lines:
2 37 40 47 51 
The word  "priklausoma" appears 2 times on the following lines:
65 74 
The word  "programinės" appears 2 times on the following lines:
25 33 
The word  "programomis" appears 2 times on the following lines:
9 41 
The word  "programos" appears 3 times on the following lines:
48 53 59 
The word  "programų" appears 3 times on the following lines:
19 52 56 
The word  "puslaidininkių" appears 4 times on the following lines:
73 74 80 
The word  "qualcomm" appears 4 times on the following lines:
31 34 69 70 
The word  "reuters" appears 2 times on the following lines:
7 45 
The word  "santykius" appears 2 times on the following lines:
5 22 
The word  "savo" appears 6 times on the following lines:
32 41 43 47 68 70 
The word  "sekmadienį" appears 2 times on the following lines:
24 33 
The word  "sistemos" appears 4 times on the following lines:
3 15 37 53 
The word  "spaudai" appears 2 times on the following lines:
11 30 
The word  "store" appears 5 times on the following lines:
4 17 49 52 53 
The word  "su" appears 9 times on the following lines:
1 5 9 16 22 34 41 45 51 
The word  "sudedamųjų" appears 2 times on the following lines:
78 79 
The word  "sustabdymas" appears 2 times on the following lines:
14 29 
The word  "sustabdė" appears 2 times on the following lines:
1 5 
The word  "sąrašą" appears 2 times on the following lines:
9 20 
The word  "tai" appears 2 times on the following lines:
7 77 
The word  "taip" appears 6 times on the following lines:
16 29 36 56 58 68 
The word  "tam" appears 2 times on the following lines:
2 43 
The word  "tačiau" appears 4 times on the following lines:
40 51 53 65 
The word  "technologijų" appears 6 times on the following lines:
1 8 15 44 62 64 
The word  "teigia" appears 3 times on the following lines:
29 42 55 
The word  "teikiamus" appears 2 times on the following lines:
10 52 
The word  "telefonų" appears 9 times on the following lines:
9 14 16 49 54 59 63 64 80 
The word  "tiekimo" appears 2 times on the following lines:
27 80 
The word  "tiekėjams" appears 2 times on the following lines:
73 78 
The word  "tiekėjų" appears 2 times on the following lines:
65 68 
The word  "tinklo" appears 2 times on the following lines:
24 77 
The word  "to" appears 2 times on the following lines:
63 80 
The word  "tokios" appears 2 times on the following lines:
48 52 
The word  "toliau" appears 5 times on the following lines:
9 13 28 37 52 
The word  "turės" appears 2 times on the following lines:
37 72 
The word  "už" appears 2 times on the following lines:
14 66 
The word  "užsienio" appears 2 times on the following lines:
1 65 
The word  "valstijų" appears 2 times on the following lines:
22 76 
The word  "versijos" appears 2 times on the following lines:
16 37 
The word  "verslo" appears 3 times on the following lines:
5 21 66 
The word  "vietą" appears 2 times on the following lines:
62 65 
The word  "viešai" appears 2 times on the following lines:
6 18 
The word  "xilinx" appears 3 times on the following lines:
32 34 70 
The word  "youtube" appears 2 times on the following lines:
18 48 
The word  "yra" appears 7 times on the following lines:
6 38 39 53 56 60 74 
The word  "į" appears 7 times on the following lines:
8 11 20 30 35 50 62 
The word  "įrangos" appears 8 times on the following lines:
24 25 33 68 72 75 78 79 
The word  "įrenginių" appears 3 times on the following lines:
2 40 51 
The word  "įskaitant" appears 2 times on the following lines:
31 67 
The word  "įtakos" appears 2 times on the following lines:
55 72 
The word  "šaltinis" appears 2 times on the following lines:
19 29 
The word  "šių" appears 2 times on the following lines:
44 63 
The word  "žinoma" appears 2 times on the following lines:
25 38 

URL ADRESSES ARE : 
URL: https://stackoverflow.com/questions/20649480/is-there-any-way-to-extract-url-from-text-in-c. in line : 2
URL: https://www.facebook.com in line : 12
URL: www.vu.lt in line : 9

  
   ``` 
