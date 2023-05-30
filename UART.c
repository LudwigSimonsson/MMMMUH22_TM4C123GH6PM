#include <stdint.h>
#include "tm4c123gh6pm.h"
//Inkluderar de dependencies vi kräver för att peka till utvecklingskortets olika komponenter

//Initiera och deklarera programmets delfunktioner
void UART0Tx(char c);
void delayMs(int n);

//Initiera och deklarera huvudfunktionen
int main(void)
  {
  SYSCTL->RCGCUART |= 1; //Enablea klockan till UART-enheten
  SYSCTL->RCGCGPIO |= 1; //Enablea klockan till PortA
  
//Initiera UART-protokollet
  UART0->CTL = 0; //Disablear UART0
  UART0->IBRD = 104; //Definerar vi en Baud Rate om 9600bps
  UART0->FBRD = 11; //Definerar fraktionen till ekvationen
  UART0->CC = 0; //Konfigurerar systemklockan
  UART0->LCRH = 0x60; //Sätter dataöverföringen till 8-bitars intervaller utan parity, utan break och utan FIFO med en stopp-bit
  UART0->CTL = 0x301; //Aktiverar UART0, Tx och Rx 

 //UART:s TX0 och RX0 skall defineras till att använda PA0 och PA1
  GPIOA->DEN = 0x03; //Sätter pins 0 och 1 till digitalt läge
  GPIOA->AFSEL = 0x03; //Sätter pinsen i alternativt funktionsläge
  GPIOA->PCTL = 0x11; //Konfigurerar PA0 och PA1 till UART
  
  //Konfigurera delay
  delayMS(1); //Tillåter vår output och konfig att stabilsera sig

  //Loop som printar HELLO in till terminalen med vår UART-konfig
  for(;;)
    {
    UARTT0Tx(H);
    UARTT0Tx(E);
    UARTT0Tx(L);
    UARTT0Tx(L);
    UARTT0Tx(O);
    }
  }

  //UART0 Överföring
  void UART0Tx(char c)
    {
      while((UART0->FR & 0x20) !=0); //Vänta tills Tx buffern flaggar som ej full
      UART0->DR = c;                 //Ge nästa byte
    }
