# oop_projekt
# Endless Runner

## Opis projekta
**Endless Runner** je 2D igra u kojoj igrač upravlja likom koji se neprekidno kreće prema naprijed.  
Cilj igre je preživjeti što dulje, izbjegavati prepreke i skupljati predmete za povećanje rezultata.
Igra se s vremenom postupno ubrzava, čime se povećava razina težine.

---

## Kontrole
- **LEFT / RIGHT** – pomicanje igrača između traka
- **ENTER** – ponovno pokretanje igre (Game Over)
- **ESC** – povratak u glavni izbornik

---

## Pokretanje projekta

### Windows
1. Pokrenuti `Runner.exe`
2. Osigurati da su SFML `.dll` datoteke u istom direktoriju kao `.exe`

### Linux
1. 
### Instalacija ovisnosti
```bash
sudo apt update
sudo apt install -y g++ make libsfml-dev
```bash
2. Pokrenuti izvršnu datoteku iz terminala
```bash
make
./endless_runner
