-- M1 Systemes Embarques - Robot Rover - Andrew O'SHEI
library ieee;
use ieee.std_logic_1164.all;

-- Créer le décodeur et ses entrées et sorties
ENTITY decoder IS

PORT(
-- Horloge de synchronisation des changements d'état
clk : IN bit;
-- Configurer un tableau de 5 bits correspondant à A13 - A17 sur le bus d'adresse
A : IN std_logic_vector(4 DOWNTO 0);
-- Créer une sortie pour chaque composant
eeprom : OUT bit;
ram : OUT bit;
motor1 : OUT bit;
motor2 : OUT bit;
motor3 : OUT bit;
motor4 : OUT bit;
motor5 : OUT bit;
motor6 : OUT bit;
arm1 : OUT bit;
arm2 : OUT bit;
mastcam : OUT bit;
mahli : OUT bit;
apxs : OUT bit;
chemcam : OUT bit;
chemin : OUT bit;
sam : OUT bit;
rad : OUT bit;
dan : OUT bit;
remrem : OUT bit
);
END decoder;

ARCHITECTURE chipselect OF decoder IS
-- Le programme commence ici
BEGIN
-- Lorsque le signal d'adresse correspond à un composant, réglez-le sur '1', sinon '0'
eeprom <= '1' WHEN A = "00000" ELSE '0';
ram <= '1' WHEN A = "00001" ELSE '0';
motor1 <= '1' WHEN A = "00010" ELSE '0';
motor2 <= '1' WHEN A = "00011" ELSE '0';
motor3 <= '1' WHEN A = "00100" ELSE '0';
motor4 <= '1' WHEN A = "00101" ELSE '0';
motor5 <= '1' WHEN A = "00110" ELSE '0';
motor6 <= '1' WHEN A = "00111" ELSE '0';
arm1 <= '1' WHEN A = "01000" ELSE '0';
arm2 <= '1' WHEN A = "01001" ELSE '0';
mastcam <= '1' WHEN A = "01010" ELSE '0';
mahli <= '1' WHEN A = "01011" ELSE '0';
apxs <= '1' WHEN A = "01100" ELSE '0';
chemcam <= '1' WHEN A = "01101" ELSE '0';
chemin <= '1' WHEN A = "01110" ELSE '0';
sam <= '1' WHEN A = "01111" ELSE '0';
rad <= '1' WHEN A = "10000" ELSE '0';
dan <= '1' WHEN A = "10001" ELSE '0';
remrem <= '1' WHEN A = "10010" ELSE '0';

END chipselect;
