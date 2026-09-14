

#define COKELED 13

#define RETURNLED 12

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);   // fixed LCD address 0x20

int changeReturned = 0; //Stores the amount of change returned to the user

int Change_In = 0; //The amount of change inserted by user into the coke machine 

int Price = 100; // Price of Coke can = 100


int isDispensed = 0; //Flag variable that is set to 0  if Coke can is initially not dispensed , set to 1 if coke can is dispensed 

int isChangeReturned = 0; // Flag variable that  is set to 0 if no change is returned, set to 1 if change is dispensed


const uint8_t FIVECENT_BUTTON = 2;
const uint8_t TWENTYCENT_BUTTON = 4;
const uint8_t FIFTYCENT_BUTTON = 6;
const uint8_t RETURNCHANGE_BUTTON = 8;

enum CokeMachineState {

  IDLE,  //0
  FIVE_CENTS,  //1
  TWENTY_CENTS,  //2
  FIFTY_CENTS,  //3
  Coke_Product,  //4
  Return_Change, //5
  Exit, //6
  _Quit_ //7


};

// Variable to track CokeMachine State 
// Initialise it as being Idle as default
CokeMachineState currentState = IDLE;





void setup() {
  // put your setup code here, to run once:

  pinMode(FIVECENT_BUTTON, INPUT_PULLUP);
  pinMode(TWENTYCENT_BUTTON, INPUT_PULLUP);
  pinMode(FIFTYCENT_BUTTON, INPUT_PULLUP);
   pinMode(RETURNCHANGE_BUTTON, INPUT_PULLUP);

  pinMode(COKELED, OUTPUT);
  pinMode(RETURNLED, OUTPUT);


  Serial.begin(9600);
  
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  

   


}

void loop() {
  // put your main code here, to run repeatedly:



 

  //Lcd print formatting for row 1
  lcd.setCursor(0,0);
  lcd.print("CREDIT:");
  lcd.setCursor(7,0);
  lcd.print(Change_In);
  lcd.setCursor(10,0);
  lcd.print("COKE:");
  lcd.setCursor(15,0);
  lcd.print(isDispensed);

  //Lcd print formatting for row 2
  lcd.setCursor(0,1);
  lcd.print("RETURN:");
  lcd.setCursor(7,1);
  lcd.print(changeReturned);
  lcd.setCursor(10,1);
  lcd.print("CHNG:");
  lcd.setCursor(15,1);
  lcd.print(isChangeReturned);
 

   //if current state is Quit State 
  if(currentState == _Quit_){

     //Quit program by exiting void loop()
    exit(0);
  }

  Serial.println("...IDLE..."); //DEBUGGING MESSAGE

  Serial.println("Change In: "); Serial.println(Change_In); //DEBUGGING MESSAGE

  
  //while currentState is still equal to Idle 

     //If-else statement to check if a button has been pressed

      //If a certain button pressed, change state accordingly

        //If B1(5 cents) is pressed, Change currentState to 5_CENTS

          //THEN BREAK OUT OF LOOP

  while(currentState == IDLE){

      //If the five cent button is pressed (LOW)
      if(digitalRead(FIVECENT_BUTTON) == LOW ){

        //set currentState to FIVE_CENTS
        currentState = FIVE_CENTS;
        //Break out of loop
        break;
      }

     //If the twenty cent button is pressed (LOW)
      if(digitalRead(TWENTYCENT_BUTTON) == LOW ){

        //set currentState to TWENTY_CENTS state
        currentState = TWENTY_CENTS;
        //Break out of loop
        break;
      }

    //If the 50 cent button is pressed (LOW)
      if(digitalRead(FIFTYCENT_BUTTON) == LOW ){

        //set currentState to FIFTY_CENTS state
        currentState = FIFTY_CENTS;
        //Break out of loop
        break;
      }


      //If the Return Change Button is pressed (LOW)


      if(digitalRead(RETURNCHANGE_BUTTON) == LOW){

        //Set currentState to Return change state 
        currentState = Return_Change;
        break;
      }

  }




  //Switch statement for CokeMachineState for Cases when coin is inserted and if Return_Change state is set

  switch(currentState){

    //For 5_CENTS Case:
    case FIVE_CENTS:
      //Print 5 Cents Inserted to the serial
      Serial.println("5 CENTS HAS BEEN INSERTED"); //DEBUGGING MESSAGE
      //Increment Change_In by 5 cents 
      Change_In = Change_In + 5;
      //delay for 2 secs
      delay(1000*2);

      //Check if Change_In < Price
      if(Change_In < Price){
        //Set currentState back to IDLE
        currentState = IDLE;
        //break out of switch statement
        break;
       //Else if Change_In is greater than or equal to Price of Coke Can
      } else if(Change_In >= Price){
         //Set currentState to  Coke_Product state 
         currentState = Coke_Product;
      }

     
    //For 20 CENTS Case:
    case TWENTY_CENTS:
      //Print 20 Cents Inserted to the serial 
      Serial.println("20 CENTS HAS BEEN INSERTED"); //DEBUGGING MESSAGE

       //Increase Change_In by + 20 cents 
      Change_In = Change_In + 20;
      //delay for 2 secs
       delay(1000*2);

      //Check if Change_In < Price
      if(Change_In < Price){
        //Set currentState back to IDLE
          currentState = IDLE;
          //break out of switch statement
           break;
        //Else if Change_In is greater than or equal to Price of Coke Can
        } else if(Change_In >= Price){
          //Set currentState to  Coke_Product state 
          currentState = Coke_Product;
          }

    

      //For the 50_CENTS Case:
      case FIFTY_CENTS:
        //Print 50 Cents Inserted to the serial
        Serial.println("50 CENTS HAS BEEN INSERTED"); //DEBUGGING MESSAGE
        //Increase Change_In by + 50 cents 
        Change_In = Change_In + 50;
        //delay for 2 secs
        delay(1000*2);

        //Check if Change_In  is less than Price of Coke can
        if(Change_In < Price){
          //Set currentState back to IDLE
          currentState = IDLE;
          //break out of switch statement
            break;
        //Else if Change_In is greater than or equal to Price of Coke Can
          } else if(Change_In >= Price){
         //Set currentState to  Coke_Product state 
         currentState = Coke_Product;
            }

          

          //For Coke_Product Case:
          case Coke_Product:
            //Print Success message
            Serial.println("Coke Can Dispensed"); //DEBUGGING MESSAGE
            
           //Set Coke LED to HIGH (ON)
            digitalWrite(COKELED, HIGH);

          //Set isDisensed to state of Coke Led so 1 or 0 
          isDispensed = digitalRead(COKELED);

            //IF Change_In is equal to Price of Coke can
            if(Change_In == Price){
            //Set state to EXIT
            currentState = Exit;
  
            // ELSE IF Change_In is greater than Price of coke can
            } else if (Change_In > Price){
  
            //SET State to Return_change state 
              currentState = Return_Change;
              }
   
          
      

        //For RETURN Change Case:
      case Return_Change:

          

        //If User decides they don't want to the can of coke and just want their change back
        if(Change_In < Price){

            changeReturned = Change_In;

            Serial.print("CHANGE RETURNED:"); Serial.println(Change_In); //DEBUGGING MESSAGE

            //Set CHANGE LED HIGH (ON) when change is returned 
            digitalWrite(RETURNLED, HIGH);

        }

        //If user has inserted a total that is greater than the price of the coke can and wants the coke can
        if(Change_In > Price){

          changeReturned = Change_In - Price;

        //Print CHANGE RETURNED: (Change_In - Price) to the screen 
        Serial.print("CHANGE RETURNED:"); Serial.println(Change_In - Price); //DEBUGGING MESSAGE

        //Set CHANGE LED HIGH (ON) when change is returned 
        digitalWrite(RETURNLED, HIGH);

        }
        
        
        
        //Set isChangeRetured to state of RETURN LED so 1 or 0
        isChangeReturned = digitalRead(RETURNLED);

        //Set currentState to EXIT state
        currentState = Exit;
     

        //For EXIT Case:
      case Exit:
        //Set currentState to Quit State
        currentState = _Quit_;
        //break out of switch statement 
      break;



  }
  //End of switch statement

   


 
 

}
