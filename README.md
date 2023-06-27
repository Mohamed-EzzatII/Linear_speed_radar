# Linear_speed_radar
A project to measure the linear speed
- This is a linear speed sensor that is used to measure the linear speed using two IR sensors 

- The main idea is to measure the time needed by the car to cover a specific distance between two sensors which in my case was 15cm, we measure that time using timer1 module.

- I used two TCRT5000L sensors because they are good enough, affordable and cheap.

The main idea : 
 we measure the time needed by the car to cover the 15 cm using the timer1, calculate the speed, and display the speed on the tera terminal 
using the UART module and also on the LCD

If the speed exceeds 15cm/sec, that means that the car exceeds the speed limit, so a buzzer and red will alert for 1 sec
else a green led will illuminate for 1 sec 

- The project is a layered model based where I used the following drivers : 
MCAL Layer: GPIO - Interrupt - Timer1 - UART 
HAL LAyer  : GRN_LED - RED_LED - LCD - Buzzer 


Note : 
I didn't find the TCRT5000L in protous, so I replaced it with a logic toggle.
