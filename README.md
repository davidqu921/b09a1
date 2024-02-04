##
Assignment 1
##
<---------------------------------------------------------------------------------------------------------------------------------->
#Solving Obstacles
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
----------------------------------------------------------------------------------------------------------------------------------
#Overview of the Functions 
void parse_arguments(int argc, char *argv[], int *samples, int *tdelay, int *system_flag, int *user_flag, int *sequential_flag);
  // Get and record the flags' state from user command line arguments
void gather_system_info();
  // Gather and display system information here
void gather_memory_info(int samples,int tdelay);
  // Gather and display memory information here
void gather_user_info();
  // Gather and display user information here
void gather_sequential_info(int samples,int tdelay);
  // gather and display memory information and user information once a time
void display_usage();
  // Warning for unacceptable arguments
int main(int argc, char *argv[])
  // All function calls happen in main() based on their flag check
void convert_seconds_to_hms(int seconds, char *buffer) 
  // Convert seconds to hours:minutes:seconds
void convert_seconds_to_dhms(int seconds, char *buffer)
  // Convert seconds to days and hours:minutes:seconds
int getCPUCoreCount()
  // Function to get the number of CPU cores
double getTotalCPUUsage()
  // Function to get the total CPU usage
<---------------------------------------------------------------------------------------------------------------------------------->
#Guide to Run
=> Directly running the program will print all information we can provide with default sample=10 and tdelay =1.
=> Running with command line arguments (order dose not matter):
  -> --system : to indicate that only the system usage should be generated
  -> --user :  to indicate that only the users usage should be generated
  -> --graphic :  to include graphical output in the cases where a graphical outcome
  -> --sequential : to indicate that the information will be output sequentially without needing to "refresh" the screen, do not 
                    combine with any other command line argument
  -> --samples=N : if used the value N will indicate how many times the statistics are going to be collected and results will 
                   be average and reported based on the N number of repetitions
  -> --tdelay=T : to indicate how frequently to sample in seconds
                   
