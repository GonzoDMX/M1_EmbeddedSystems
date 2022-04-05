# M1 Systèmes Embarqués - Projet Robot Rover - OSHEI Andrew

Ce projet démontre une solution de contrôle pour un Robot Rover. Cela inclut des sélections de composants ainsi qu'une implémentation hypothétique d'un décodeur FPGA qui permettrait à un microcontrôleur limité d'effectuer des opérations sur de nombreux composants. Pour tester notre implémentation de code VHDL, des simulations ont été exécutées à l'aide de ModelSim.

## Fichiers inclus :

1. **CompSelect_OSHEI_andrew.pdf** - Comprend une description des composantes choisies pour ce projet et pourquoi elles ont été choisies (Microcontrôleur, EEPROM et RAM).
2. **TableAdressage_OSHEI_andrew.pdf** - Une représentation visuelle de la table d'adresses utilisée pour commander chacun des composants connectés au microcontrôleur.
3. **VHDLProgram_OSHEI_andrew.vhd** - Un programme écrit en VHDL pour le FPGA hypothétique qui sera utilisé pour décoder le signal de sélection de puce pour chacun des composants.
4. **Simulation_OSHEI_andrew.png** - Une représentation "Wave" du programme VHDL simulé via ModelSim.
5. **DataflowSim_OSHEI_andrew.png** - Une représentation "Dataflow" du programme VHDL simulé via ModelSim.
6. **SchemaSignaux_OSHEI_andrew.pdf** - Un schéma des connexions entre chacun des composants utilisés dans le projet.
7. **CProgram_OSHEI_andrew.c** - Le programme C montrant comment le microcontrôleur lit et écrit sur les composants à l'aide du décodeur FPGA pour l'adressage des composants.

<p align="center">Schéma du flux de signaux</p>
<p align="center">
  <img style="width: 80%; height: 80%;" src="https://github.com/GonzoDMX/M1_EmbeddedSystems/blob/main/assets/SchemaSignaux_OSHEI_andrew.png">
</p>
</br>
<p align="center">Table d'adressage</p>
<p align="center">
  <img style="width: 80%; height: 80%;" src="https://github.com/GonzoDMX/M1_EmbeddedSystems/blob/main/assets/TableAdressage_OSHEI_andrew.png">
</p>
</br>
<p align="center">Simulation ModelSim - Wave</p>
<p align="center">
  <img style="width: 80%; height: 80%;" src="https://github.com/GonzoDMX/M1_EmbeddedSystems/blob/main/Simulation_OSHEI_andrew.png">
</p>
</br>
<p align="center">Simulation ModelSim - Dataflow</p>
<p align="center">
  <img style="width: 80%; height: 80%;" src="https://github.com/GonzoDMX/M1_EmbeddedSystems/blob/main/DataflowSim_OSHEI_andrew.png">
</p>



