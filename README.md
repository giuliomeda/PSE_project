# SIMULAZIONE DI ROBOTICA DI GRUPPO
Nel 1987 Craig Reynolds pubblicò il modello Boid che simula il comportamento che si osserva
negli stormi di uccelli. Il nome boid deriva da “bird-oid object”, cioè un oggetto simile a un
uccello.
L’utilità del modello è l’uso che se ne può fare nell’animazione invece di mimare e creare
manualmente gli elementi dello stormo in movimento.
Ad esempio, un’implementazione
di questo modello è stata usata per l’animazione del branco di gnu e degli uccelli in cielo
durante l’iconica sequenza del calpestio nel film The Lion King della Disney.

## Istruzioni per la compilazione del programma
1. Clona il repository in locale con:
```bash
git clone https://github.com/giuliomeda/homework_PSE_23-24.git
```
2. Apri la directory del repository appena clonato e crea la tua cartella di build con:
```bash
mkdir build 
```

4. Compila con CMAKE:
```bash
 cd build/
 cmake ..
 make
```
5. Una volta terminata la compilazione puoi avviare l'applicazione tramite 
```bash
./app/eseguibile 
```

## Dipendenze per la compilazione 
### visualizer.py

Prima di utilizzare visualizer.py è necessario installare Python

Successivamente è necessario installare numpy e matplotlib (se non già installati) con:

`pip install numpy`

`pip install matplotlib`

Nel caso non funzioni (tipicamente su windows) una possibile soluzione è:

`py -m pip install numpy`

`py -m pip install matplotlib`

### GUI per python su WSL

Da PowerShell:

> wsl --version

Se versione 1:

> wsl --update

> wsl --shutdown

( <https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps> )

Se versione 2, passare a wsl, dal terminale linux:

`$ sudo apt install python3`

`$ sudo apt install python3-tk`

(The standard Python interface to the Tcl/Tk GUI toolkit)

`$ sudo apt install python3-pip`

(The package installer for Python)

