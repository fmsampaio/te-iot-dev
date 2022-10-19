/* 
  Exemplo: 02-Components/DisplayLCD
*/
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// A função setup é executada uma vez quando forem pressionados os botões de reset ou de power on na placa
void setup()
{
  //Define o número de colunas (16) e linhas (2) do LCD
  lcd.begin(16, 2);
}

// A função loop é executada de forma repetida sem parada
void loop()
{
  //Display LCD: Limpa a tela
  lcd.clear();
  
  lcd.setCursor(3, 0);        //Display LCD: Posiciona o cursor na coluna 3, linha 0
  lcd.print("INF - IFRS");    //Display LCD: Escreve no display a string "INF - IFRS"
  lcd.setCursor(3, 1);        //Display LCD: Posiciona o cursor na coluna 3, linha 1
  lcd.print("DisplayLCD");    //Display LCD: Escreve no display a string "DisplayLCD"
  delay(5000);

  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }

  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}