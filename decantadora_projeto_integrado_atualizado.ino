#define tempo 7200000 /*Definindo tempo para decantação*/

/*Definindo Led's*/
#define led_verde_dec 2
#define led_amarelo_dec 3
#define led_vazio_res 6
#define led_verde_res 5 
#define led_cheio_res 4
#define led_alerta 7

/*Definindo sensores*/
#define sensor_dec A5 
#define sensor_cheio A4 
#define sensor_vazio A3 

/*Definindo conexões de energia para os sensores*/
#define energia_sensor_dec 13 
#define energia_sensor_cheio 12
#define energia_sensor_vazio 11 

/*Declarando variáveis para auxiliar no processo*/
int aux_dec = 0;
float val_sensor_dec = 0;
float val_sensor_cheio = 0;
float val_sensor_vazio = 0;

void setup() {
  /*Declarando as conexões de entrada e saída do controlador.*/
  pinMode(led_amarelo_dec, OUTPUT);
  pinMode(led_verde_dec, OUTPUT);
  pinMode(led_cheio_res, OUTPUT);
  pinMode(led_verde_res, OUTPUT);
  pinMode(led_vazio_res, OUTPUT);
  pinMode(led_alerta, OUTPUT);
  pinMode(sensor_dec, INPUT);
  pinMode(sensor_cheio, INPUT);
  pinMode(sensor_vazio, INPUT);
  pinMode(energia_sensor_dec, OUTPUT);
  pinMode(energia_sensor_cheio, OUTPUT);
  pinMode(energia_sensor_vazio, OUTPUT);

  /*Desligando as conexões de energia*/
  digitalWrite(energia_sensor_dec, LOW);
  digitalWrite(energia_sensor_cheio, LOW);
  digitalWrite(energia_sensor_vazio, LOW);
  Serial.begin(9600);
}

void loop() {
  /*Declarando e recebendo os valores de cada sensor*/
  int nivel_sensor_dec = readSensorDec(); /*Chamando a função do sensor de decantação*/
  int nivel_sensor_cheio = readSensorCheio(); /*Chamando a função do sensor do topo do reservatório*/
  int nivel_sensor_vazio = readSensorVazio(); /*Chamando a função do sensor da parte debaixo do reservatório*/

  Serial.print("sensor-cheio: ");
  Serial.println(nivel_sensor_cheio);
  Serial.print("sensor-vazio: ");
  Serial.println(nivel_sensor_vazio);
  Serial.print("\nsensor-dec: ");
  Serial.println(nivel_sensor_dec);
  
  
  delay(1000);  /*Atraso de 1s entre leituras*/
  
  if(nivel_sensor_dec > 300){ /*Verificar se o reservatório de decantação está com água*/
    switch(aux_dec){
      case 0:{/*Caso seja a primeira vez rodando, ele irá acender o LED de espera (amarelo) e aguardará o tempo até que a decantação seja concluída*/
        digitalWrite(led_amarelo_dec, HIGH);
        delay(tempo);
        aux_dec = 1;
        break;
      }
      case 1:{/*Ao concluir a decantação ele apaga o Led de espera e liga o Led que indica a conclusão do processo (verde), para que possam liberar a água*/
        digitalWrite(led_amarelo_dec, LOW);
        digitalWrite(led_verde_dec, HIGH);
        break;
      }
    }
  }else{ /*Quando para de detectar água, ele reinicia as variáveis auxiliares e desliga todos os Led's*/
    digitalWrite(led_amarelo_dec, LOW);
    digitalWrite(led_verde_dec, LOW);
    aux_dec = 0;
  }
  
  if(nivel_sensor_cheio > 300 and nivel_sensor_vazio < 300){/*É verificado se os 2 sensores do reservatório estão dando sinal, para identificar um defeito no produto*/
    digitalWrite(led_cheio_res, LOW);
    digitalWrite(led_vazio_res, LOW);
    digitalWrite(led_verde_res, LOW);
    digitalWrite(led_alerta, HIGH);
  }else{ /*Se não estão, ele funciona normalmente*/
    digitalWrite(led_alerta, LOW);
    if(nivel_sensor_cheio > 300){ /*Caso o reservatório esteja cheio ou perto de encher, é sinalizado ao cliente*/
      digitalWrite(led_cheio_res, HIGH);
    }else{
      digitalWrite(led_cheio_res, LOW);
    }
    if(!(nivel_sensor_vazio > 300)){ /*Caso o reservatório esteja vazio ou perto de esvaziar, é sinalizado ao cliente*/
      digitalWrite(led_vazio_res, HIGH);
    }else{
      digitalWrite(led_vazio_res, LOW);
    }
    if(nivel_sensor_cheio < 300 and nivel_sensor_vazio > 300){ /*Caso o nível de água no reservatório seja bom, é sinalizado ao cliente*/
      digitalWrite(led_verde_res, HIGH);
    }else{
      digitalWrite(led_verde_res, LOW);
    }
  }
}

int readSensorDec() {  
digitalWrite(energia_sensor_dec, HIGH);  /* alimenta o sensor */
delay(10);              /* espera 10ms */
val_sensor_dec = analogRead(sensor_dec);    /* Realiza a leitura analógica do sinal do sensor */
digitalWrite(energia_sensor_dec, LOW);   /* Desliga o sensor */
return val_sensor_dec;             /* envia leitura */
}

int readSensorCheio() {  
digitalWrite(energia_sensor_cheio, HIGH);  /* alimenta o sensor */
delay(10);              /* espera 10ms */
val_sensor_cheio = analogRead(sensor_cheio);    /* Realiza a leitura analógica do sinal do sensor */
digitalWrite(energia_sensor_cheio, LOW);   /* Desliga o sensor */
return val_sensor_cheio;             /* envia leitura */
}

int readSensorVazio() {  
digitalWrite(energia_sensor_vazio, HIGH);  /* alimenta o sensor */
delay(10);              /* espera 10ms */
val_sensor_vazio = analogRead(sensor_vazio);    /* Realiza a leitura analógica do sinal do sensor */
digitalWrite(energia_sensor_vazio, LOW);   /* Desliga o sensor */
return val_sensor_vazio;             /* envia leitura */
}
