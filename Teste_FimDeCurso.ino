// Código desenvolvido colvido com o objetivo de testar e calibrar
// a parada do elevador de acordo com o posicionamento das chaves
// fim de curso. 
// O teste é feito em um andar por vez.

int porta_rele1 = 13;
int porta_rele2 = 12;
int porta_rele3 = 11;
int porta_rele4 = 10;

int porta_botao1 = 2;
int porta_botao2 = 3;


int porta_FimCurso = 7;
int emerg2 = 19;

int leitura1 = 0;


void setup()
{
  //Define pinos para o rele como saida
  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_rele2, OUTPUT);
  pinMode(porta_rele3, OUTPUT); 
  pinMode(porta_rele4, OUTPUT);
  //Define pinos dos botoes como entrada
  pinMode(porta_botao1, INPUT_PULLUP); 
  pinMode(porta_botao2, INPUT_PULLUP);
  pinMode(emerg2, INPUT_PULLUP);
  pinMode(porta_FimCurso, INPUT_PULLUP);
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele1, HIGH);
  digitalWrite(porta_rele2, HIGH);
  digitalWrite(porta_rele3, HIGH);
  digitalWrite(porta_rele4, HIGH);
}

void loop() {



  if (digitalRead(porta_FimCurso) == 0 ) {
         leitura1 = digitalRead(porta_botao1);
      
         if (digitalRead(porta_botao1) == 0 ) {
              while ((digitalRead(porta_botao1) == 0 && digitalRead(porta_FimCurso) == 0) || (digitalRead(porta_botao1) == 0 && digitalRead(emerg2) == 0)) {
              digitalWrite(porta_rele1, 1); 
              digitalWrite(porta_rele2, 1);
              delay(100);
              digitalWrite(porta_rele3, 0); 
              digitalWrite(porta_rele4, 0);
              
            } 
              digitalWrite(porta_rele1, 1);
              digitalWrite(porta_rele2, 1); 
              digitalWrite(porta_rele3, 1);
              digitalWrite(porta_rele4, 1);      
            }  
      
         if (digitalRead(porta_botao2) == 0 ) {
              while ((digitalRead(porta_botao2) == 0 && digitalRead(porta_FimCurso) == 0) || (digitalRead(porta_botao1) == 0 && digitalRead(emerg2) == 0)) {
                digitalWrite(porta_rele3, 1); 
                digitalWrite(porta_rele4, 1);
                delay(100);
                digitalWrite(porta_rele1, 0); 
                digitalWrite(porta_rele2, 0);
                      
            } 
              digitalWrite(porta_rele1, 1);
              digitalWrite(porta_rele2, 1); 
              digitalWrite(porta_rele3, 1);
              digitalWrite(porta_rele4, 1);      
            }
        
      }
       
  }

  
  

    
