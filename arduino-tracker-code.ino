//Written in Arduino IDE 1.8.9

/*
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/

#define MAX_RPMS             100.0  //maximum speed, change as desired and allowable
#define SIDEREAL_RPMS       0.6949  //with hinge-to-rod length 32cm 
#define STEP_PIN                 9
#define DIRECTION_PIN            8
#define REVERSE_PIN             10
#define SIDEREAL_PIN            11
#define R_PIN                   12
#define F_PIN                   13
#define STEPS_PER_REV          200  //steps per revolution depends on the stepper motor used
#define MICROSTEPS_PER_STEP      8  //according to the driver/motor and user

//nothing needs to be changed below this line

#define MICROSECONDS_PER_MICROSTEPMAX  (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(MAX_RPMS / 60))
#define MICROSECONDS_PER_MICROSTEP (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(SIDEREAL_RPMS/60))

uint32_t LastStepTime = 0;
uint32_t CurrentTime = 0;

void setup() {                
  pinMode(STEP_PIN, OUTPUT);     
  pinMode(DIRECTION_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  pinMode(R_PIN,INPUT);
  pinMode(F_PIN,INPUT);
}

void loop() {
  if (digitalRead(REVERSE_PIN) == LOW)
  {
    digitalWrite(DIRECTION_PIN, HIGH);
  }
  else if (digitalRead(SIDEREAL_PIN) == LOW)
  {
    digitalWrite(DIRECTION_PIN, LOW);
  }
  
  if (digitalRead(R_PIN) == LOW){
    CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEPMAX)
    {
      LastStepTime = CurrentTime;
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds((MICROSECONDS_PER_MICROSTEPMAX * 0.9)/2);
      digitalWrite(STEP_PIN, LOW); 
      delayMicroseconds((MICROSECONDS_PER_MICROSTEPMAX * 0.9)/2);
    }
  }
  else if(digitalRead(F_PIN == LOW))
  {
     CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
      LastStepTime = CurrentTime;
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
      digitalWrite(STEP_PIN, LOW); 
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
    }
  }
}
