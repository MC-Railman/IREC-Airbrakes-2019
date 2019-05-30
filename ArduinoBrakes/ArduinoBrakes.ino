void setup() {
  // put your setup code here, to run once:
  /* import library to read from altimeter here 
   * write altimeter setup here
   * import library for component that activates airbrakes
   * write airbrakes component setup here
   */

  Serial.begin(9600);
}

void loop() {
  
  // Establishing Known Values
  float g = 32.17;
  float hi = 0;
  float vi = 0;
  float A = 0.25;
  float Cdo = 1;
  float Cdc = 0.75;
  float t = 0.1;
  float h = 0;
  float hf = 0;
  float v = 0;
  float p = 0.0;

  // Establishing Input Values
  /* This line is done to read input from the user. 
   * If the values for the mass and desired apogee can be coded beforehand,
   * it would make this program a lot more simple.
   */ 
   
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
  
  // until the final height of the rocket is above the desired apogee,
  // this loop will continue to run
  while (hf < ho) {
    
    hi = h;
    Serial.print("Input current height of the rocket");
    while (Serial.available() == 0) {}
    h = Serial.read();
    vi = v;
    d = ho - h;
    
    if (h < 5000)
      p = 23.77 * 0.0001;
      
    if (h < 10000)
      p = 20.48 * 0.0001;
      
    if (h >= 10000)
      p = 17.56 * 0.0001;

    float visq = vi * vi;
    hf = (0.5 * visq - d * Cdc * p * visq * A / 2) / (m * g);
    v = (h - hi) / t;
    
  }

  Serial.print("Activate second loop");

  while (hf <= ho) {
    hi = h;
    Serial.print("Input current height of the rocket");
    while (Serial.available() == 0) {}
    h = Serial.read();
    vi = v;
    d = ho - h;

    if (h < 5000)
      p = 23.77 * 0.0001;
      
    if (h < 10000)
      p = 20.48 * 0.0001;
      
    if (h >= 10000)
      p = 17.56 * 0.0001;

    float visq = vi * vi;
    hf = (0.5 * m * visq - d * Cdo * p * visq * A / 2) / (m * g);
    v = (h - hi) / t;
  }

  Serial.print("ACTIVATE AIRBRAKES");

  // function call or another loop to activate airbrakes
  
}
