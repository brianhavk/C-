#include <Keypad.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <Adafruit_GFX.h> // Hardware-specific library
#include <Adafruit_TFTLCD.h>
//////////////////
#define LCD_CS A3 // Chip Select - Pin analogico 3
#define LCD_CD A2 // Command/Data - Pin Analogico 2
#define LCD_WR A1 // LCD Write - Pin Analogico 1
#define LCD_RD A0 // LCD Read - Pin Analogico 0
#define LCD_RESET A4 // LCD Reset - Pin Analogico 4
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
////////////////////////////////// MIS VARIABLES de conversion
char npc[100],base[100],Csp[100],CSedg[100],baseSS[100], Cnum[100];
int i=0,j=0,baseN,k,m,p,a=0,sp=0,b=1,q,R,o=0,baseS,EMnp[100];
float n,sn=0.0,Sedg,Mnp;
boolean bandera0=true,bandera1=false,bandera2=false, Ac=false,bandera3=false,ki=false,bandera4=false,C=false,bandera5=false;
////////////////////
byte const ROWS  = 4; // cuatro filas
byte const COLS = 4; // cuatro columnas
// definir los cymbols en los botones de los teclados
char hexaKeys [ROWS] [COLS] = {
{ '1','2','3','A'},
{ '4','5','6','B'},
{ '7','8','9','C'},
{ '.','0',' ','D'},
};
byte rowPins[ROWS] = {30,32,34,36}; // conectarse a las patillas de salida de fila del teclado
byte colPins[COLS] = {40,42,44,46}; // conectarse a las patillas de las columnas del teclado
// inicializar una instancia de clase NewKeypad
Keypad customKeypad = Keypad (makeKeymap (hexaKeys), rowPins, colPins,ROWS, COLS);
/////////////////////////// Variables tft
uint8_t aspect;
////////////////////////////////////////////////////
void setup () {
    Serial.begin(9600);
    tft.reset();
    uint16_t identifier = tft.readID();
    tft.begin(identifier);
    tft.setRotation(3);// rotar pantalla
    tft.fillScreen(0x0000);
    tft.setCursor(30,100);
    tft.setTextSize(2); //tamaño de texto
    tft.setTextColor(0x001F);
    tft.println("Bienvenido Roberth");
    tft.setCursor(45,120);
    tft.setTextSize(2); //tamaño de texto
    tft.setTextColor(0x001F);
    tft.println("Al conversor de bases");
    delay(2000);
    tft.fillScreen(0x0000);
    Serial.println("hola");
}

void loop () {
char customKey=customKeypad.getKey();
tft.setRotation(3);
tft.setTextSize(2);
tft.setTextColor(0xF800);
if(bandera0)
   {
    tft.setCursor(0,0);
    tft.println("Ingrese el numero a convertir: ");
    bandera2=false;
    if(customKey&&bandera0) 
      {
       npc[i]=customKey;
       Serial.println(npc);
       tft.println(npc);
       R=i;
       i++;
       if(customKey==' ')
         {
          bandera0=false;
          bandera1=true;
          customKey='\0';
          delay(1000);
          tft.fillScreen(0x0000);
         }
      }
   }
if(bandera1)
   {
    tft.setCursor(0,0);
    tft.println("Ingrese la base del numero:");
    if(bandera1&&customKey)
      {
       base[j]=customKey;
       j++;
       tft.println(base); 
       if(customKey==' ')
         {
          bandera1=false;
          bandera2=true;
          baseN=atoi(base);
          customKey='\0';
          delay(1000);
          tft.fillScreen(0x0000); 
         }   
      }
   }
if(bandera2)
  {
   if(baseN!=2&&baseN!=8&&baseN!=10&&baseN!=16)
     {
      tft.println("Ingresaste mal la base. Tendras que repetir la digitacion");
      for(k=0;k<=j;k++) base[k]='\0';
      j=0;
      bandera1=true;
      bandera2=false;
     }
  }
if(bandera2)
  {
   bandera2=false;
   bandera3=true;
   if(baseN==2)
     {
      for(m=0;npc[m]!=' ';m++)
         {
          if(npc[m]!='0'&&npc[m]!='1'&&npc[m]!='.')
             {
              tft.setCursor(0,50);
              tft.print("Error. Tendras que digitar el numero y la base nuevamente.");
              bandera0=true;
              Ac=true;
              bandera2=true;
              bandera3=false;
             }
          if(npc[m]=='.') 
             {
              q=m;
              ki=true;
             }
         }
      if(Ac)
        {
         delay(1000);
         tft.fillScreen(0x0000);
         Ac=false;
         for(k=0;k<=i;k++) npc[k]='\0';
         i=0;
         for(k=0;k<=j;k++) base[k]='\0';
         j=0;
        }
      if(ki) 
        {
         for(k=q-1;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='0') npc[k]=0; 
                p=npc[k]*pow(2,a);
                a++;
                sp=sp+p;
             }
        for(k=q+1;npc[k]!=' ';k++)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='0') npc[k]=0;
                n=npc[k]*pow(2,-(b));
                b++;
                sn=sn+n;
             } 
        }
     if(ki==false)
       {
         k=R-1;
         for(k;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='0') npc[k]=0;  
                p=npc[k]*pow(2,a);
                a++;
                sp=sp+p;
             }
       } 
     }
   if(baseN==8)
     {
      for(m=0;npc[m]!=' ';m++)
         {
          if(npc[m]!='0'&&npc[m]!='1'&&npc[m]!='2'&&npc[m]!='3'&&npc[m]!='4'&&npc[m]!='5'&&npc[m]!='6'&&npc[m]!='7'&&npc[m]!='.')
             {
              tft.setCursor(0,50);
              tft.print("Error. Tendras que digitar el numero y la base nuevamente.");
              bandera0=true;
              Ac=true;
              bandera2=true;
              bandera3=false;
             }
          if(npc[m]=='.') 
            {
              ki=true;
              q=m;
            }
         }
      if(Ac)
        {
         delay(1000);
         tft.fillScreen(0x0000);
         Ac=false;
         for(k=0;k<=i;k++) npc[k]='\0';
         i=0;
         for(k=0;k<=j;k++) base[k]='\0';
         j=0;
        }
      if(ki) 
        {
         for(k=q-1;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='0') npc[k]=0; 
                p=npc[k]*pow(8,a);
                a++;
                sp=sp+p;
             }
        for(k=q+1;npc[k]!=' ';k++)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='0') npc[k]=0;
                n=npc[k]*pow(8,-(b));
                b++;
                sn=sn+n;
             } 
        }
     if(ki==false)
       {
         k=R-1;
         for(k;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='0') npc[k]=0;
                p=npc[k]*pow(8,a);
                a++;
                sp=sp+p;
             }
       } 
     }
   if(baseN==10)
     {
      for(m=0;npc[m]!=' ';m++)
         {
          if(npc[m]!='0'&&npc[m]!='1'&&npc[m]!='2'&&npc[m]!='3'&&npc[m]!='4'&&npc[m]!='5'&&npc[m]!='6'&&npc[m]!='7'&&npc[m]!='8'&&npc[m]!='9'&&npc[m]!='.')
             {
              tft.setCursor(0,50);
              tft.print("Error. Tendras que digitar el numero y la base nuevamente.");
              bandera0=true;
              Ac=true;
              bandera2=true;
              bandera3=false;
             }
          if(npc[m]=='.') 
             {
              q=m;
              ki=true;
             }
         }
      if(Ac)
        {
         delay(1000);
         tft.fillScreen(0x0000);
         Ac=false;
         for(k=0;k<=i;k++) npc[k]='\0';
         i=0;
         for(k=0;k<=j;k++) base[k]='\0';
         j=0;
        }
       if(ki) 
        {
         for(k=q-1;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='8') npc[k]=8;
                if(npc[k]=='9') npc[k]=9; if(npc[k]=='0') npc[k]=0;  
                p=npc[k]*pow(10,a);
                a++;
                sp=sp+p;
             }
        for(k=q+1;npc[k]!=' ';k++)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='8') npc[k]=8;
                if(npc[k]=='9') npc[k]=9; if(npc[k]=='0') npc[k]=0;  
                n=npc[k]*pow(10,-(b));
                b++;
                sn=sn+n;
             } 
        }
     if(ki==false)
       {
         m=R-1;
         for(m;m>=0;m--)
             {
                if(npc[m]=='1') npc[m]=1; if(npc[m]=='2') npc[m]=2; if(npc[m]=='3') npc[m]=3; if(npc[m]=='4') npc[m]=4;
                if(npc[m]=='5') npc[m]=5; if(npc[m]=='6') npc[m]=6; if(npc[m]=='7') npc[m]=7; if(npc[m]=='8') npc[m]=8;
                if(npc[m]=='9') npc[m]=9; if(npc[m]=='0') npc[m]=0;  
                p=npc[m]*pow(10,a);
                a++;
                sp=sp+p;
             }
       } 
     }
   if(baseN==16)
     {
      for(m=0;npc[m]!=' ';m++)
         {
          if(npc[m]!='0'&&npc[m]!='1'&&npc[m]!='2'&&npc[m]!='3'&&npc[m]!='4'&&npc[m]!='5'&&npc[m]!='6'&&npc[m]!='7'&&npc[m]!='8'&&npc[m]!='9'&&npc[m]!='A'&&npc[m]!='B'&&npc[m]!='C'&&npc[m]!='D'&&npc[m]!='.')
             {
              tft.setCursor(0,50);
              tft.print("Error. Tendras que digitar el numero y la base nuevamente.");
              bandera0=true;
              Ac=true;
              bandera2=true;
              bandera3=false;
             }
          if(npc[m]=='.') 
            {
             q=m;
             ki=true;
            }
         }
      if(Ac)
        {
         delay(1000);
         tft.fillScreen(0x0000);
         Ac=false;
         for(k=0;k<=i;k++) npc[k]='\0';
         i=0;
         for(k=0;k<=j;k++) base[k]='\0';
         j=0;
        }
      if(ki) 
        {
         for(k=q-1;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='8') npc[k]=8;
                if(npc[k]=='9') npc[k]=9; if(npc[k]=='0') npc[k]=0; if(npc[k]=='A') npc[k]=10; if(npc[k]=='B') npc[k]=11;
                if(npc[k]=='C') npc[k]=12; if(npc[k]=='D') npc[k]=13; 
                p=npc[k]*pow(16,a);
                a++;
                sp=sp+p;
             }
        for(k=q+1;npc[k]!=' ';k++)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='8') npc[k]=8;
                if(npc[k]=='9') npc[k]=9; if(npc[k]=='0') npc[k]=0; if(npc[k]=='A') npc[k]=10; if(npc[k]=='B') npc[k]=11;
                if(npc[k]=='C') npc[k]=12; if(npc[k]=='D') npc[k]=13; 
                n=npc[k]*pow(16,-(b));
                b++;
                sn=sn+n;
             } 
        }
     if(ki==false)
       {
         k=R-1;
         for(k;k>=0;k--)
             {
                if(npc[k]=='1') npc[k]=1; if(npc[k]=='2') npc[k]=2; if(npc[k]=='3') npc[k]=3; if(npc[k]=='4') npc[k]=4;
                if(npc[k]=='5') npc[k]=5; if(npc[k]=='6') npc[k]=6; if(npc[k]=='7') npc[k]=7; if(npc[k]=='8') npc[k]=8;
                if(npc[k]=='9') npc[k]=9; if(npc[k]=='0') npc[k]=0; if(npc[k]=='A') npc[k]=10; if(npc[k]=='B') npc[k]=11;
                if(npc[k]=='C') npc[k]=12; if(npc[k]=='D') npc[k]=13; 
                p=npc[k]*pow(16,a);
                a++;
                sp=sp+p;
             }
       }
     }
  }
 if(bandera3)
   {
    Sedg=sp+sn;
    if(ki==false) 
      {
        tft.print("La conversion a EDG es: ");
        tft.println(sp);
      }
    if(ki) 
      {
        tft.print("La conversion a EDG es: ");
        tft.println(Sedg, 4);
      }
    bandera3=false;
    bandera4=true;
    delay(4000);
    tft.fillScreen(0x0000);
   }
 if(bandera4)
    {
     bandera5=true;
     tft.setCursor(0,0);
     tft.println("En cual base quiere convertir el numero:");
     tft.println("1. Base 2");
     tft.println("2. Base 8");
     tft.println("3. Base 10");
     tft.println("4. Base 16");
     tft.print("Digitela:");
     if(bandera4&&customKey)
       {
        baseSS[o]=customKey;
        o++;
        tft.println(baseSS);
        if(customKey==' ')
          {
            bandera4=false;
            C=true;
            baseS=atoi(baseSS);
            delay(1000);
            tft.fillScreen(0x0000);
          }
       }
      if(C)
        {
          if(baseS!=1&&baseS!=2&&baseS!=3&&baseS!=4)
            {
              tft.println("Error de seleccion de menu, tendra que hacerlo otra vez");
              bandera4=true;
              C=false;
              for(k=0;k<=o;k++) baseSS[k]='\0';
              o=0;
              delay(1000);
              tft.fillScreen(0x0000);
            }
        }
    }
   if(bandera5)
     {
      switch(baseS)
 {
    case 1: tft.print("El valor del numero en base binaria es: ");
             tft.print(sp, BIN); 
          if(ki) 
            { 
             tft.print(".");
             Mnp=sn*2;
             EMnp[0]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*2;
             EMnp[1]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*2;
             EMnp[2]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*2;
             EMnp[3]=Mnp; 
             printf(".");
             for(j=0;j<=3;j++) tft.print(EMnp[j]);
            }
      break;
    
          break;
    case 2:  tft.print("El valor del numero en base octal es: ");
             tft.print(sp, OCT); 
          if(ki) 
            { 
             tft.print(".");
             Mnp=sn*8;
             EMnp[0]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*8;
             EMnp[1]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*8;
             EMnp[2]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*8;
             EMnp[3]=Mnp; 
             printf(".");
             for(j=0;j<=3;j++) tft.print(EMnp[j]);
            }
      break;
    case 3: if(ki==false)
              {
               tft.print("El valor del numero en base decimal es: ");
               tft.print(sp); 
              }
            if(ki) 
              { 
               tft.print("El valor del numero en base decimal es: ");
               tft.print(Sedg);
              }
      break;
      
  case 4:    tft.print("El valor del numero en base hexadecimal es: ");
             tft.print(sp, HEX); 
          if(ki) 
            { 
             tft.print(".");
             Mnp=sn*16;
             EMnp[0]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*16;
             EMnp[1]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*16;
             EMnp[2]=Mnp;
             while(Mnp>1) Mnp--;
             Mnp=Mnp*16;
             EMnp[3]=Mnp; 
             printf(".");
             for(j=0;j<=3;j++) 
                {
                 if(EMnp[j]==1) tft.print("1"); if(EMnp[j]==2) tft.print("2"); if(EMnp[j]==3) tft.print("3"); if(EMnp[j]==4) tft.print("4"); if(EMnp[j]==5) tft.print("5"); 
                 if(EMnp[j]==6) tft.print("6"); if(EMnp[j]==7) tft.print("7"); if(EMnp[j]==8) tft.print("8"); if(EMnp[j]==9) tft.print("9"); if(EMnp[j]==10) tft.print("A");
                 if(EMnp[j]==11) tft.print("B"); if(EMnp[j]==12) tft.print("C"); if(EMnp[j]==13) tft.print("D"); 
                 }
            }
      break;
 }
 bandera5=false;
     }
 }
