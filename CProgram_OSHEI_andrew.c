/*
*   Andrew O'Shei - 20001943
*	Projet de conception de robot rover
*	M1 Systemes embarques - Universite Paris 8
*/
#include <pic32mx.h>
#include <stdio.h>
#include <string.h>

// Déclarer l'adressage de tous les composants en tant que variables statiques
static unsigned int eeprom 	=	0x0000;
static unsigned int ram 	=	0x2000;
static unsigned int motor_1 =	0x4000;
static unsigned int motor_2 =	0x6000;
static unsigned int motor_3 =	0x8000;
static unsigned int motor_4 =	0xA000;
static unsigned int motor_5 =	0xC000;
static unsigned int motor_6 =	0xE000;
static unsigned int robo_arm_1=	0x10000;
static unsigned int robo_arm_2=	0x12000;
static unsigned int mast_cam =	0x14000;
static unsigned int mahli	=	0x16000;
static unsigned int apxs	=	0x18000;
static unsigned int chem_cam =	0x1A000;
static unsigned int che_min	=	0x1C000;
static unsigned int sam		=	0x1E000;
static unsigned int rad 	=	0x20000;
static unsigned int dan		=	0x22000;
static unsigned int rem		=	0x24000;

// Définir la taille du buffer d'entrée UART
static int BUFF_LIMIT = 128;

// Créer un buffer pour recevoir les messages de contrôle
char control_buffer[BUFF_LIMIT];
// Buffer pour stocker les données des composants
char data_buffer[BUFF_LIMIT];

// Déclarer nos prototypes de fonctions
void read_from_component( unsigned int *A, unsigned int *B, unsigned int target, char *data );
void write_to_component( unsigned int *A, unsigned int *B, unsigned int target, char *data );
void FlushRx();
unsigned int get_device_address(char *target, char *address);

void main() {
	// Initialiser les registres
	// Régler le registre A comme une sortie
	TRISA = 0x00000000;
	// Régler le registre B comme une entree
	TRISB = 0xFFFFFFFF;
	// les registres sont déclarés comme int afin d'accéder aux 32 bits complets du registre
	// Registre d'adressage
	PORTA = 0x00000000;
	// Registre d'entrée-sortie
	PORTB = 0x00000000;

	// Configurer le pointeur d'E/S pour les registres A et B
	unsigned int *register_B;
	register_A = &PORTA;
	register_B = &PORTB;

	// Configurer l'interface UART, 250000 baud
	// Pour cet exemple, nous allons prétendre que les messages de contrôle arrivent via UART
	UART1_Init(250000);

	// Boucle de programme
	while ( true ) {

		// // Si un message est disponibles sur l'interface UART
		if ( UART1_Data_Ready() ) {
			int rxCount = 0;
			while( UART1_Data_Ready() ) {
				// Charger les données dans le buffer
				control_buffer[rxCount] = UART1_Read();
				rxCount += 1;
				// Si nous atteignons la limite de taille du message
				if ( rxCount == BUFF_LIMIT ) {
					break;
				}
			}
			// Effacer le reste du registre UART RX, juste au cas où
			FlushRx();
		}

		// Obtenir le premier mot du message de contrôle
		char *target = strok( control_buffer, "/" );
		char *address = strok( NULL, "/" );
		char *command = strok( NULL, "/" );
		char *data = strok( NULL, "/" );

		// Une valeur pour déterminer le périphérique cible dans les fonctions
		unsigned int device = get_device_address( target, address );
		
		// Tester si l'appareil cible est un moteur ou un bras robotise
		if ( device > ram && device < mast_cam ) {
			write_to_component(register_A, register_B, device, data);
		} else {
			if (strcmp( command, "read" )) {
				read_from_component(register_A, register_B, device, data);
			}
			else if (strcmp( command, "write" )) {
				write_to_component(register_A, register_B, device, data);
			}
		}
	}
}

// Lire les données d'un composant sur le rover
void read_from_component( unsigned int *A, unsigned int *B, unsigned int target, char *data ) {
	// Définir le registre B pour qu'il fonctionne comme entree
	TRISB = 0xFFFFFFFF;
	char *tmp;
	// Mettre le registre A sur l'adresse du composant cible
	int read_length = atoi(data);
	// Sélectionner l'appareil cible
	*A = target;
	for (i = 0; i < read_length; i++ ) {
		// Si le buffer de données est plein, arrêtez la boucle
		if ( i == BUFF_LIMIT ) {
			break;
		}
		// Lire un octet du registre B
		data_buffer[i] = *B;
	}
}

// Écrire des données sur un composant du rover
void write_to_component( unsigned int *A, unsigned int *B, unsigned int target, char *data ) {
	// Définir le registre B pour qu'il fonctionne comme sortie
	TRISB = 0x00000000;
	char *tmp;
	int index = 0;
	// Mettre le registre A sur l'adresse du composant cible
	*A = target;
	// Pour chaque octet de données
	for ( tmp = data; data != '\0'; tmp++ ) {
		// Écrire des données dans le registre de données B
		*B = data[index];
		index += 1;
	}
	
}

// Vider le buffer RX de UART
void FlushRx() {
     while( UART1_Data_Ready() ) {
          UART1_Read();
     }
}

// Renvoie l'adresse de l'appareil cible
unsigned int get_device_address(char *target, char *address) {
	unsigned int device = 0x00;
	// Comparer le jeton avec des mots-clés afin de déterminer le cible
	if (strcmp( target, "eeprom" )) {
		// Obtenir l'adresse EEPROM
		unsigned long x = strtoul( address );
		device += x;
	}
	else if (strcmp( target, "ram" )) {
		device = ram;
		// Obtenir l'adresse RAM
		unsigned long x = strtoul( address );
		device += x;
	}
	else if (strcmp( target, "motor" )) {
		// Déterminer quel moteur nous contrôlons
		int x = atoi( address );
		switch( x ) {
			case 1:
				device = motor_1;
				break;
			case 2:
				device = motor_2;
				break;
			case 3:
				device = motor_3;
				break;
			case 4:
				device = motor_4;
				break;
			case 5:
				device = motor_5;
				break;
			case 6:
				device = motor_6;
				break;
		}
	}
	else if (strcmp( target, "robo_arm" )) {
		// Déterminer quel moteur nous contrôlons
		int x = atoi( address );
		if ( x ) {
			device = robo_arm_2;
		} else {
			device = robo_arm_1
		}
	}
	else if (strcmp( target, "mast_cam" )) {
		device = mast_cam;
	}
	else if (strcmp( target, "mahli" )) {
		device = mahli;
	}
	else if (strcmp( target, "apxs" )) {
		device = apxs;
	}
	else if (strcmp( target, "chem_cam" )) {
		device = chem_cam;
	}
	else if (strcmp( target, "che_min" )) {
		device = che_min;
	}
	else if (strcmp( target, "sam" )) {
		device = sam;
	}
	else if (strcmp( target, "rad" )) {
		device = rad;
	}
	else if (strcmp( target, "dan" )) {
		device = dan;
	}
	else if (strcmp( target, "rem" )) {
		device = rem;
	}
	return device;
}

