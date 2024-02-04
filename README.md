##
# Assignment 1

## Solving Obstacles

1. The first problem I faced before developing anything on my program was the overwhelming C-libraries we probably wanted to include and
   use, trying to read through them is quite time-consuming, therefore I decided to focus on implementing its functionality, once I need
   some specific helper functions I will search on Google to find out which library I need to include and also find some examples which use
   those functions and examples are always good for learning.
2. After I developed some core functions: gather_system_info,gather_memory_info,gather_user_info(),gather_sequential_info...
   I find it really hard to track the user's command line arguments since the way I designed it accommodated users to input their
   arguments with no order. So I need a function to loop over all command line arguments and record the modification for flags, this is
   parse_arguments which helps a lot for controlling function calls in main().
3. Since I am trying to make my program run exactly like the demo video, where the Sessions/users and Memory are printed at the same time,
   and Memory is printed with Tdelay, but my program prints all Memory in order, and then the Sessions/users. I find these extremely
   confusing and barely found anything to address this issue on the internet, I tried a couple of hours and gave up on these, but since the functionality is
   already fulfilled I don't think it is hurting my program in any way.


##
## Overview of the Functions 

1.void parse_arguments(int argc, char *argv[], int *samples, int *tdelay, int *system_flag, int *user_flag, int *sequential_flag);<br />
  // Get and record the flags' state from user command line arguments<br />
2.void gather_system_info();<br />
  // Gather and display system information here<br />
3.void gather_memory_info(int samples,int tdelay);<br />
  // Gather and display memory information here<br />
4.void gather_user_info();<br />
  // Gather and display user information here<br />
5.void gather_sequential_info(int samples,int tdelay);<br />
  // gather and display memory information and user information once a time<br />
6.void display_usage();<br />
  // Warning for unacceptable arguments<br />
7.int main(int argc, char *argv[])<br />
  // All function calls happen in main() based on their flag check<br />
8.void convert_seconds_to_hms(int seconds, char *buffer) <br />
  // Convert seconds to hours:minutes:seconds<br />
9.void convert_seconds_to_dhms(int seconds, char *buffer)<br />
  // Convert seconds to days and hours:minutes:seconds<br />
10.int getCPUCoreCount()<br />
  // Function to get the number of CPU cores<br />
11.double getTotalCPUUsage()<br />
  // Function to get the total CPU usage<br />


##
## Guide to Run

=> Directly running the program will print all information we can provide with default sample=10 and tdelay =1.<br />
=> Running with command line arguments (order dose not matter):<br />
  -> --system : to indicate that only the system usage should be generated<br />
  -> --user :  to indicate that only the users usage should be generated<br />
  -> --graphic :  to include graphical output in the cases where a graphical outcome<br />
  -> --sequential : to indicate that the information will be output sequentially without needing to "refresh" the screen, do not<br /> 
                    combine with any other command line argument<br />
  -> --samples=N : if used the value N will indicate how many times the statistics are going to be collected and results will <br />
                   be average and reported based on the N number of repetitions<br />
  -> --tdelay=T : to indicate how frequently to sample in seconds<br />
                   
