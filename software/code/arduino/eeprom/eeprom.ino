#define DATAOUT 11//MOSI
#define DATAIN  12//MISO 
#define SPICLOCK  13//sck
#define SLAVESELECT 10//ss

//opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

byte eeprom_output_data;
byte eeprom_input_data=0;
byte clr;
int address=0;
//data buffer
char buffer [128];

void fill_buffer()
{
  for (int I=0;I<128;I++)
  {
    buffer[I]=I;
  }
}

char spi_transfer(volatile char data)
{
  SPDR = data;                    // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
  {
  };
  return SPDR;                    // return the received byte
}

void setup()
{
  Serial.begin(9600);

  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  digitalWrite(SLAVESELECT,HIGH); //disable device
  // SPCR = 01010000
  //interrupt disabled,spi enabled,msb 1st,master,clk low when idle,
  //sample on leading edge of clk,system clock/4 rate (fastest)
  SPCR = (1<<SPE)|(1<<MSTR);
  clr=SPSR;
  clr=SPDR;
  delay(10);
  //fill buffer with data
  fill_buffer();
  //fill eeprom w/ buffer
  digitalWrite(SLAVESELECT,LOW);
  spi_transfer(WREN); //write enable
  digitalWrite(SLAVESELECT,HIGH);
  delay(10);
  digitalWrite(SLAVESELECT,LOW);
  spi_transfer(WRITE); //write instruction
  address=0;
  spi_transfer((char)(address>>8));   //send MSByte address first
  spi_transfer((char)(address));      //send LSByte address
  //write 128 bytes
  for (int I=0;I<128;I++)
  {
    spi_transfer(buffer[I]); //write data byte
  }
  digitalWrite(SLAVESELECT,HIGH); //release chip
  //wait for eeprom to finish writing
  delay(3000);
  Serial.println("Hi");//debug
  delay(1000);
}

byte read_eeprom(int EEPROM_address)
{
  //READ EEPROM
  int data;
  digitalWrite(SLAVESELECT,LOW);
  spi_transfer(READ); //transmit read opcode
  spi_transfer((char)(EEPROM_address>>8));   //send MSByte address first
  spi_transfer((char)(EEPROM_address));      //send LSByte address
  data = spi_transfer(0xFF); //get data byte
  digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer
  return data;
}

void loop()
{
  eeprom_output_data = read_eeprom(address);
  Serial.println(eeprom_output_data,DEC);
  address++;
  if (address == 128)
    address = 0;
  delay(500); //pause for readability
}
