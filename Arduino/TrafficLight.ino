//Start lcd
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

int tempoRestante=0;
int bt_press=0;



void setup() {
  lcd.begin(16, 2);
  pinMode(1, INPUT);  
  pinMode(0, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  
  //lcd
  lcd.print("RXMichel");
  lcd.setCursor(0,2);
  lcd.print("SrGMS");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("        ");
  lcd.setCursor(0,2);
  lcd.print("        ");
}



void loop() {
  
  //traffic light 1
  
  unsigned long  start1 = millis();
  
  pedestre1_ligaVermelho();
  pedestre2_ligaVerde();
  
  //lcd
  lcd.setCursor(0,1);
  lcd.print("__");

//traffic light 1 -> 20 seconds
  while((millis()-start1)<20000){
    
    tempoRestante=(23-((int)(millis()-start1)/1000));
    
    //lcd
    lcd.setCursor(0,0);
    lcd.print("Sem_1");
    lcd.setCursor(0,1);
    
    if (tempoRestante < 10){
        lcd.print("0");
        lcd.print(tempoRestante);
    } else {
        lcd.print(tempoRestante);
    }
    
    //button 1
      if(digitalRead(1)==HIGH){
        //if button 1 is pressed and the timeout is great that 15 second//
          if((millis()-start1)<15000){
            //timeout is set to 8 ( 5 green light and 3 yellow light)
               start1=millis()-15000;
               //lcd
               lcd.setCursor(7,1);
               lcd.print("bt1_A");
               //button 1 is triggered
               bt_press=1;
          } else if(bt_press==0){
               lcd.setCursor(7,1);
               lcd.print("bt1_R");
          }
      }
      
        semaforo1_ligaVerde();
        semaforo2_ligaVermelho();
    
  }
  
    
  start1=millis();
  
  // if the timeout is less that 3 seconds
  while((millis()-start1)<3000){
    tempoRestante=(3-((int)(millis()-start1)/1000));
    
    lcd.setCursor(0,1);
    lcd.print("0");
    lcd.print(tempoRestante);

    semaforo1_ligaAmarelo();
    if((millis()%1000)>500){
        pedestre2_pisca(HIGH);
        lcd.setCursor(7,0);
        lcd.print("pisca");
    } else {
        pedestre2_pisca(LOW);
        lcd.setCursor(7,0);
        lcd.print("     ");

    }
 }

  
  pedestre1_ligaVerde();
  semaforo1_ligaVermelho();
  lcd.setCursor(7,0);
  lcd.print("     ");
  lcd.setCursor(7,1);
  lcd.print("     ");
  bt_press=0;
  
  //traffic light 2
  unsigned long  start2=millis();
  
  pedestre2_ligaVermelho();
  
  lcd.setCursor(0,1);
  lcd.print("__");
  
  while((millis()-start2)<20000){
    
    tempoRestante=(23-((int)(millis()-start2)/1000));
    
    lcd.setCursor(0,0);
    lcd.print("Sem_2");
    lcd.setCursor(0,1);
    
    if (tempoRestante<10){
        lcd.print("0");
        lcd.print(tempoRestante);
    }
    else{
        lcd.print(tempoRestante);
    }


    //button 2
      if(digitalRead(8)==HIGH){
        if ((millis()-start2)<15000){
           start2=millis()-15000;
           lcd.setCursor(7,1);
           lcd.print("bt2_A");
           bt_press=1;
        } else if(bt_press==0){
               lcd.setCursor(7,1);
               lcd.print("bt2_R");
          }
      }
       
      semaforo2_ligaVerde();
      semaforo1_ligaVermelho();

    }
    
    start2=millis();
    
    while((millis()-start2)<3000){
      
              semaforo2_ligaAmarelo();
              
              tempoRestante=(3-((int)(millis()-start2)/1000));
              lcd.setCursor(0,1);
              lcd.print("0");
              lcd.print(tempoRestante);
              
              if((millis()%1000)>500){
                  pedestre1_pisca(HIGH);
                  lcd.setCursor(7,0);
                  lcd.print("pisca");
              }
              else{
                  pedestre1_pisca(LOW);
                  lcd.setCursor(7,0);
                  lcd.print("     ");
              }
           
        }
  lcd.setCursor(7,0);
  lcd.print("     ");
  lcd.setCursor(7,1);
  lcd.print("     ");
  bt_press=0;
}



//functions
void semaforo1_ligaVerde(){
    digitalWrite(A2,HIGH);
    digitalWrite(A0,LOW);
}
void semaforo1_ligaAmarelo(){
    digitalWrite(A2,LOW);
    digitalWrite(A1,HIGH);
    digitalWrite(A0,LOW);
}
void semaforo1_ligaVermelho(){
    digitalWrite(A2,LOW);
    digitalWrite(A1,LOW);
    digitalWrite(A0,HIGH);
}

void semaforo2_ligaVerde(){
    digitalWrite(11,HIGH);
    digitalWrite(13,LOW);
}
void semaforo2_ligaAmarelo(){
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
}
void semaforo2_ligaVermelho(){
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
}

void pedestre1_ligaVermelho(){
  digitalWrite(A4,LOW);
  digitalWrite(A3,HIGH);
}

void pedestre1_ligaVerde(){
  digitalWrite(A4,HIGH);
  digitalWrite(A3,LOW);
}

void pedestre1_pisca(boolean pisc){
  digitalWrite(A4,pisc);
}


void pedestre2_ligaVermelho(){
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
}

void pedestre2_ligaVerde(){
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
}

void pedestre2_pisca(boolean pisc){
  digitalWrite(9,pisc);
}
