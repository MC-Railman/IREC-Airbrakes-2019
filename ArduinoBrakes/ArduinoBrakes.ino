void setup() {
  // put your setup code here, to run once:

  // Establishing Known Values
  float g = 32.17;
  int hi = 0;
  float vi = 0;
  float A = 0.25;
  int Cdo = 1;
  float Cdc = 0.75;
  float t = 0.1;
  int h = 0;
  int hf = 0;
  int v = 0;

  // Establishing Input Values
  /* This line is done to read input from the user. 
   * If the values for the mass and desired apogee can be coded beforehand,
   * it would make this program a lot more simple.
   */ 

  Serial.begin(9600);

  Serial.print("Input mass of rocket in slugs");
  while (Serial.available() == 0) {}
  float m = Serial.read();

  Serial.print("Input the desired apogee in feet");
  while (Serial.available() == 0) {}
  float ho = Serial.read();
  
  float d = ho - hi;
  
  // Finding the Values
  float vo = (d * 2) / (t - vi);
  vi = vo;
}

void loop() {
  // put your main code here, to run repeatedly:

}
