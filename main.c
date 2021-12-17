// =========== Configurando pinos do MCU =========== //
sbit LCD_RS at RB5_bit;
sbit LCD_EN at RB4_bit;
sbit LCD_D4 at RB3_bit;
sbit LCD_D5 at RB2_bit;
sbit LCD_D6 at RB1_bit;
sbit LCD_D7 at RB0_bit;

sbit LCD_RS_Direction at TRISB5_bit;
sbit LCD_EN_Direction at TRISB4_bit;
sbit LCD_D4_Direction at TRISB3_bit;
sbit LCD_D5_Direction at TRISB2_bit;
sbit LCD_D6_Direction at TRISB1_bit;
sbit LCD_D7_Direction at TRISB0_bit;

void main() {
     unsigned int leituraADC;          // variavel auxiliar na conversao de word para string
     unsigned char texto0[10];         // variavel auxiliar para AN0
     unsigned char texto1[10];         // variavel auxiliar para AN1
     
     TRISA.RA0 = 1;                    // pino RA0 (AN0) como entrada
     TRISA.RA1 = 1;                    // pino RA1 (AN1) como entrada
     
     ADCON0 = 0b00000001;              // ativa modulo de conversao e declara AN0 como canal analogico
     ADCON1 = 0b00001101;              // configura AN0 e AN1 como input analogico para conversao A/D
     ADCON2 = 0b10101010;              /* justifica o resultado da conversao para a direita (---resultado)
                                          clock de conversao Fosc/32 */
     
     // =========== Configurando LCD =========== //
     Lcd_Init();                       // inicializa o LCD
     Lcd_Cmd(_LCD_CLEAR);              // limpa o LCD
     Lcd_Cmd(_LCD_CURSOR_OFF);         // remove o cursor
     Lcd_Out(1, 1, "AN0: ");           // inserir texto na linha 1, coluna 1
     Lcd_Out(2, 1, "AN1: ");           // // inserir texto na linha 2, coluna 1
     
     // =========== Funcao loop =========== //
     while(1) {
              // =========== AN0 =========== //
              ADCON0 = 0b00000001;                               // inicializa modulo de conversao no AN0
              ADCON0.GO_DONE = 1;                                // inicializa conversao
              while(ADCON0.GO_DONE == 1);                        // enquanto a conversao estiver em progresso...
              
              leituraADC = ((ADRESH << 8) | (int)ADRESL);        // armazena o resultado da conversao na variavel
              
              WordToStr(leituraADC, texto0);                     // converte o resultado de Word para Str
              Lcd_Out(1, 5, texto0);                             // mostra o resultado no LCD na linha 1, coluna 5
              Delay_ms(20);                                      // delay de 20ms para o processo se repetir
              
              // =========== AN1 =========== //
              ADCON0 = 0b00000101;                               // inicializa modulo de conversao no AN1
              ADCON0.GO_DONE = 1;
              while(ADCON0.GO_DONE == 1);

              leituraADC = ((ADRESH << 8) | (int)ADRESL);        // armazena o resultado da conversao na variavel

              WordToStr(leituraADC, texto1);                                       
              Lcd_Out(2, 5, texto1);                             // mostra o resultado no LCD na linha 2, coluna 5
              Delay_ms(20);
     }
}