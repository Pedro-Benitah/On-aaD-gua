const int tempo = 3000;

int led_verde_dec = 6;
int led_amarelo_dec = 7;
int led_vazio_res = 3;
int led_verde_res = 4;
int led_cheio_res = 5;
int led_alerta = 1;
int sensor_dec = 13;
int sensor_cheio = 12;
int sensor_vazio = 11;
int aux_dec = 0;

void setup() {
  pinMode(led_amarelo_dec, OUTPUT);
  pinMode(led_verde_dec, OUTPUT);
  pinMode(led_cheio_res, OUTPUT);
  pinMode(led_verde_res, OUTPUT);
  pinMode(led_vazio_res, OUTPUT);
  pinMode(led_alerta, OUTPUT);
  pinMode(sensor_dec, INPUT);
  pinMode(sensor_cheio, INPUT);
  pinMode(sensor_vazio, INPUT);
}

void loop() {
  if(digitalRead(sensor_dec)){
    switch(aux_dec){
      case 0:{
        digitalWrite(led_amarelo_dec, HIGH);
        delay(tempo);
        aux_dec = 1;
        break;
      }
      case 1:{
        digitalWrite(led_amarelo_dec, LOW);
        digitalWrite(led_verde_dec, HIGH);
        break;
      }
    }
  }else{
    digitalWrite(led_verde_dec, LOW);
    aux_dec = 0;
  }
  
  if(digitalRead(sensor_cheio) and digitalRead(sensor_vazio)){
    digitalWrite(led_cheio_res, LOW);
    digitalWrite(led_vazio_res, LOW);
    digitalWrite(led_verde_res, LOW);
    digitalWrite(led_alerta, HIGH);
  }else{
    digitalWrite(led_alerta, LOW);
    if(digitalRead(sensor_cheio)){
      digitalWrite(led_cheio_res, HIGH);
    }else{
      digitalWrite(led_cheio_res, LOW);
    }
    if(digitalRead(sensor_vazio)){
      digitalWrite(led_vazio_res, HIGH);
    }else{
      digitalWrite(led_vazio_res, LOW);
    }
    if(!(digitalRead(sensor_cheio)) and !(digitalRead(sensor_vazio))){
      digitalWrite(led_verde_res, HIGH);
    }else{
      digitalWrite(led_verde_res, LOW);
    }
  }
}
