# enigma_attacks
implementataion of some enigma variants and major attacks (hill climbing, bombe)

## Enigma Models
* Enigma I
* Enigma M3
* Enigma M4
* Railway Enigma (Reichsbahn)/Rocket I
* Swiss-K (Schweizer/Switzerland)
* Enigma D/K
* Norway Enigma (Norenigma)
* Sonder Enigma
* Enigma T (Tripitz, Japanese Enigma)

NOTE: Not implemented UKW-D, Uhr features. Enigma G models seems to have some different stepping mechanism (cogwheel).

## Attack
major attacks for finding the plugboard(sticker) setting against specified model, rotor/reflector order, rotor/reflector setting

* Bombe
  
  known partial plaintext (crib) attack

  Pros:
  * not required plaintext/ciphertext statistics

  Cons:
  * crib should be known
  * it might give wrong plugboard for short crib

* Hill climbing
  
  ciphertext only attack

  Pros:
  * no crib required (ciphertext only)

  Cons:
  * plaintext statistics should be known (assuming wrong human language leads wrong plugboard)
  * it takes longer time compared to bombe
  * cannot attack to too short message

if some settings except plugboard are unknown, use bruteforce. 
When you known plaintext statistics, you may filter some settings. (no plugboard decryption keeps plaintext statistics somehow for correct plugboard decryption.) 
And you can consider reducing bruteforcing range for ring settings. (many rotor order and ring setting pairs produces same ciphertext. especially, first ring setting is no means, and second ring setting is rarely important.)

## Test
For generating .so files and test binaries, run `make` command.
For testing encryption/decryption for enigma models, run `enigma/testenigma`.
For testing attacks, run `attack/testenigmaattack`.

Before testing hill climbing attack, put plaintext statistics files to "freqdb" directory with specified filename. (monogram, bigram, trigram, quadgram)
Simple shell scripts are provided.
* freqdb/getfreqlst_general.sh

  download statistics files from http://practicalcryptography.com/cryptanalysis/letter-frequencies-various-languages/
  
  normal English, German text statistics (German ons includes German specified characters(such as Ü), which is not included in standard Enigma text.)
* freqdb/getfreqlst_special.sh

  download statistics files from http://www.bytereef.org/dict/

  some German statistics calculated on special texts which is similar to texts on German WWII. (Enigma text characters only)

Note: On testing, I noticed some encryption/decryption results are different on some different Enigma simulators. (And some website shows different rotor/reflector wiring settings.) Finally, I decided to use the following resorces cause they have no contradiction with different context.
* http://wiki.franklinheath.co.uk/index.php/Enigma/Sample_Messages

  Collection of real Enigma ciphertexts
* https://dencode.com/en/cipher/enigma

  An Enigma simulator for various models

## Reference
including just memo (necessarily not checked in detail), but helpful all.

* enigma simulators (many models are implemented)
  * http://people.physik.hu-berlin.de/~palloks/js/enigma/index_en.html
  * https://cryptii.com/pipes/enigma-machine
  * https://dencode.com/en/cipher/enigma
  * https://enigma.w6k.ca/enigma.html

* enigma implementation (many models are implemented)
  * https://github.com/the-lambda-way/bruteforce-enigma
  * https://github.com/aurbano/enigma_py

* https://www.cryptomuseum.com/crypto/enigma/

* https://de.wikipedia.org/wiki/Enigma-Walzen

* https://cryptocellar.org/bgac/
    * https://cryptocellar.org/pubs/bgac.pdf
    * https://cryptocellar.org/bgac/hillclimb-enigma.pdf
    * https://cryptocellar.org/pubs/enigma-modern-breaking.pdf

* https://www.bytereef.org/m4_project.html

* http://practicalcryptography.com/cryptanalysis/breaking-machine-ciphers/cryptanalysis-enigma/

* http://www.ellsbury.com/enigmabombe.htm

* https://github.com/shreyas-sriram/enigma-cryptanalysis

* https://github.com/CrypToolProject/CrypTool-2/tree/main/LibSource/EnigmaAnalyzerLib/EnigmaAnalyzer

* https://github.com/gchq/CyberChef/blob/master/src/core/lib/Bombe.mjs
