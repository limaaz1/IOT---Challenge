// Projeto: Módulo Diagnóstico de Manutenção - Mottu
// Função: Ler sensores simulados por potenciômetros (tensão e temperatura)


void setup() {
  Serial.begin(9600);  
}

void loop() {

  int leituraTensao = analogRead(A0);
  int leituraTemp = analogRead(A1);

  
  float tensao = leituraTensao * (5.0 / 1023.0);

 
  float temperatura = leituraTemp * (5.0 / 1023.0) * 100;

 
  Serial.print("Tensao da bateria: ");
  Serial.print(tensao);
  Serial.print(" V\t");

  Serial.print("Temperatura do motor: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  delay(2000);  
}
