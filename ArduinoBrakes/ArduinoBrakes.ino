void setup() {
  // put your setup code here, to run once:
  /* import library to read from altimeter here 
   * write altimeter setup here
   * import library for component that activates airbrakes
   * write airbrakes component setup here
   */

  // if you still want to read values from user input, you need a serial port setup.
  // the number will be different depending on where you connect the screen to the arduino
  Serial.begin(9600);
}

void loop() {
  
  // Establishing Known Values
  float g = 32.17;        // ft/s^2
  float hi = 0;           // ft
  float vi = 0;           // ft/s
  float A = 0.25;         // ft^2
  float Cdo = 1;          // No unit
  float Cdc = 0.75;       // No unit
  float t = 0.1;          // Seconds. This is based on how quickly the loop will input new data
  float h = 0;            // ft. Current height
  float hf = 0;           // ft. Final projected rocket height
  float v = 0;            // ft/s. Current velocity of the rocket
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
  /* As the rocket launches, these values will need to be updated. Using an
   * altimeter, the height will be adjusted, but for the sake of having this
   * code work, I will do a simplified vector that will replace the information
   * from the altimeter.
   */

  float vo = (d * 2) / (t - vi);
  
  // each time the loop runs, the final velocity from the previous run will become 
  // the initial velocity.
  vi = vo;

  //  Establishing Overshoot Loop
  /* This loop will run until the projected apogee of the rocket exceeds the
   * desired height of the rocket. With this in mind, if the rocket is never
   * projected to reach desired apogee, the brakes will never deploy and
   * further hinder the height. However, if the rocket is projected to exceed
   * desired height, a secondary loop will activate in order to find the best
   * time to activate the brakes. This loop will constantly calculate the
   * projected height of the rocket using the work balance equation and
   * utilize the changing environment.
   */

  // until the final height of the rocket is above the desired apogee,
  // this loop will continue to run
  while (hf < ho) {
    
    hi = h;
    Serial.print("Input current height of the rocket");
    while (Serial.available() == 0) {}
    
    // This manual input will act for the altimeter.
    h = Serial.read();    
    vi = v;

    // this is the distance left to reach, supplying d for how much drag will be instigated
    d = ho - h;
    
    if (h < 5000)
      p = 23.77 * 0.0001;
      
    if (h < 10000)
      p = 20.48 * 0.0001;
      
    if (h >= 10000)
      p = 17.56 * 0.0001;

    float visq = vi * vi;

    // %Energy Balance equation, assuming final velocity is zero and initial height is zero
    hf = (0.5 * visq - d * Cdc * p * visq * A / 2) / (m * g);

    // current velocity using the change of height divided by the time interval ft/s
    v = (h - hi) / t;
  }

  // Signal for secondary loop (mainly to check if it will activate
  Serial.print("Activate second loop");

  // Activation Loop
  /* This loop will run its course with an updated Coefficient of
   * Drag based on the rocket with the air brake fins activated. By running the
   * while loop until the project height is close to the desired apogee, this
   * loop will optimize the instant of activation.
   * 
   */
   
  while (hf <= ho) {

    /* The earlier the brakes activate, the lower the rocket will go, so 
     * this loop will only end when the rocket will reach or slightly exceed 
     * the desired height.
     * NOTE: IF WANTING A TIGHTER TOLERANCE, IT IS ADVISED TO INPUT A SLIGHTLY
     * LOWER ho ex. hf<=(ho-20)
     */
     
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

    /* This loop will keep running until the projected height reaches the
     * desired apogee, otherwise, the brakes will not open and the rocket
     * will go as high as possible without the brakes. This is intended as a
     * safety deligation.
     */
  }

  // Activating Brakes
  
  Serial.print("ACTIVATE AIRBRAKES");

  // function call or another loop to activate airbrakes
  
}
