/**
 * Program: System Monitoring Tool
 * Description: This C program will report different metrics of the utilization of a given system.
 * 
 * Author: David Qu
 * Date Created: Feburary 1, 2024
 * Last Modified: Feburary 4, 2024
 * 
 * StudentID: 1007653585
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <utmpx.h>

// Function prototypes
void parse_arguments(int argc, char *argv[], int *samples, int *tdelay, int *system_flag, int *user_flag, int *sequential_flag);
void gather_system_info();
void gather_memory_info(int samples,int tdelay)
void gather_user_info();
void gather_sequential_info(int samples,int tdelay);
void display_usage();

int main(int argc, char *argv[]) {
    int samples = 10, tdelay = 1; // Default values
    int system_flag = 0, user_flag = 0, sequential_flag = 0;

    // Parse command-line arguments
    parse_arguments(argc, argv, &samples, &tdelay, &system_flag, &user_flag, &sequential_flag);
	
    // Validate arguments and decide on the action
    if (system_flag) {
       
		gather_memory_info(samples,tdelay)
			if(user_flag == 1){
				gather_user_info();
				*user_flag = 0;
			}
		gather_system_info();
    }
    
    if (user_flag) {
        gather_user_info();
    }
	
	if(sequential_flag){
		gather_sequential_info(samples,tdelay);
	}


    return 0;
}

void parse_arguments(int argc, char *argv[], int *samples, int *tdelay, int *system_flag, int *user_flag, int *sequential_flag) {
    if (argc == 1){
		*user_flag = 1;
		*system_flag = 1;
	}
	else{
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "--system") == 0) {
				*system_flag = 1;
			} else if (strcmp(argv[i], "--user") == 0) {
				*user_flag = 1;
			} else if (strcmp(argv[i], "--sequential") == 0) {
				*sequential_flag = 1;
			} else if (strncmp(argv[i], "--samples=", 9) == 0) {
				*samples = atoi(argv[i] + 10);
			} else if (strncmp(argv[i], "--tdelay=", 8) == 0) {
				*tdelay = atoi(argv[i] + 9);
			} else {
				printf("Unknown argument: %s\n", argv[i]);
				display_usage();
				exit(EXIT_FAILURE);
			}
		}
	}	
}

void convert_seconds_to_hms(int seconds, char *buffer) {
    // Calculate hours, minutes, and seconds
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int seconds_remaining = seconds % 60;

    // Write the formatted time to the buffer
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds_remaining);
}

void convert_seconds_to_dhms(int seconds, char *buffer) {
    int days = seconds / (24 * 3600);
    seconds = seconds % (24 * 3600);
    int hours = seconds / 3600;
    seconds = seconds % 3600;
    int minutes = seconds / 60;
    seconds = seconds % 60;

    // Assuming buffer is large enough to hold the resulting string
    sprintf(buffer, "%d days %02d:%02d:%02d", days, hours, minutes, seconds);
}

// Function to get the number of CPU cores
int getCPUCoreCount() {
    FILE *fp = popen("nproc", "r");
    
    if (fp == NULL) {
        perror("Error opening pipe");
        exit(EXIT_FAILURE);
    }

    int coreCount;
    fscanf(fp, "%d", &coreCount);

    if (pclose(fp) == -1) {
        perror("Error closing pipe");
        exit(EXIT_FAILURE);
    }

    return coreCount;
}

// Function to get the total CPU usage
double getTotalCPUUsage() {
    FILE *fp = fopen("/proc/stat", "r");
    
    if (fp == NULL) {
        perror("Error opening /proc/stat");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), fp); // Read the first line

    // Parse the values from the line
    unsigned long long user, nice, system, idle;
    sscanf(buffer, "cpu %llu %llu %llu %llu", &user, &nice, &system, &idle);

    fclose(fp);

    // Calculate total CPU usage as a percentage
    unsigned long long total = user + nice + system + idle;
    unsigned long long usage = total - idle;
    double cpuUsage = (double)usage / total * 100.0;

    return cpuUsage;
}



void gather_system_info() {
    // Gather and display system information here
    long int time_in_seconds;
	int days;
	int core_num;
	double percentage;
	char *time_str[10];
	char *day_str[50];
	struct utsname uname_data;
    uname(&uname_data);
	struct sysinfo info;
    sysinfo(&info);
	
	// Get core_num and percentage.
	core_num = getCPUCoreCount();
	percentage = getTotalCPUUsage();
	
	printf("Number of cores: %d\n", core_num);
	printf("total cpu use = %.2f%%\n", percentage);
	printf("---------------------------------------\n");
	printf("### System Information ###")
    printf("System Name = %s\n", uname_data.sysname);
    printf("Machine Name = %s\n", uname_data.nodename);
    printf("Version = %s\n", uname_data.version);
    printf("Release = %s\n", uname_data.release);
    printf("Architecture = %s\n", uname_data.machine);
	
	time_in_seconds = info.uptime;
	convert_seconds_to_hms(time_in_seconds,time_str);
	convert_seconds_to_dhms(time_in_seconds,day_str);
	
    printf("System running since last reboot: %s (%s)\n",day_str,time_str);
    printf("---------------------------------------\n");
    
}

void gather_memory_info(int samples,int tdelay) {
    // Gather and display user information here
    // This could include parsing /var/run/utmp for user sessions
	struct sysinfo info;
	sysinfo(&info);
	printf("Nbr of samples: %d -- every %d secs\n",*samples,*tdelay);
	printf("Memory usage: %ld kilobytes\n", (info.totalram-info.freeram)/1024);
	printf("---------------------------------------\n");
	printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot) ");
	// Main loop for sampling 
    for (int i = 0; i < samples; i++) {
        // Gather and display stats here
		printf("%ld GB / %ld GB  -- %ld GB / %ld GB\n", (info.totalram-info.freeram)/(1024 * 1024 * 1024),info.totalram/(1024 * 1024 * 1024),
            (info.totalswap + info.ram - info.freeram -info.freeswap)/(1024 * 1024 * 1024),(info.totalswap + info.totalram)/(1024 * 1024 * 1024));
        // Wait for the next sample if not in the last iteration
        if (i < samples - 1) {
            sleep(tdelay);
        }
    }
	printf("---------------------------------------\n");
	
}

void gather_user_info() {
    struct utmpx *ut;

    // Open the utmpx file for reading
    setutxent();


	printf("### Sessions/users ###");
    // Read each entry in the utmpx file
    while ((ut = getutxent()) != NULL) {
        // Check if the entry represents a user process
        if (ut->ut_type == USER_PROCESS) {
            // Print information for the user
            printf("%-13s %s (%s)\n", ut->ut_user, ut->ut_line, ut->ut_host);
        }
    }
    printf("---------------------------------------\n");

    // Close the utmpx file
    endutxent();
}

void print_each_sequential(int iterationTime, int samples){
    int core_num;
	double percentage;
    struct sysinfo info;
	sysinfo(&info);
    
    printf(">>> iteration %d\n", iterationTime);
	printf("Memory usage: %ld kilobytes\n", (info.totalram-info.freeram)/1024);
	printf("---------------------------------------\n");
	printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot) ");
	
    // Main loop for sampling 
    for (int i = 0; i < samples; i++) {
       
        if (i == iterationTime){
            printf("%ld GB / %ld GB  -- %ld GB / %ld GB\n", (info.totalram-info.freeram)/(1024 * 1024 * 1024),info.totalram/(1024 * 1024 * 1024),
                (info.totalswap + info.ram - info.freeram -info.freeswap)/(1024 * 1024 * 1024),(info.totalswap + info.totalram)/(1024 * 1024 * 1024));
        }

        else if(i != iterationTime){
            printf("\n");
        }

    }
	printf("---------------------------------------\n");
    
    gather_user_info();
    
    // Get core_num and percentage.
	core_num = getCPUCoreCount();
	percentage = getTotalCPUUsage();
	
	printf("Number of cores: %d\n", core_num);
	printf("total cpu use = %.2f%%\n", percentage);

}

void gather_sequential_info(int samples,int tdelay);{
	// sample times' iteration   
	// ">" is all u need
    for (int i = 0; i < samples, i++)
    {
        print_each_sequential(i,samples);
        
        if (i < samples - 1) {
            sleep(tdelay);
        }
    }
}

void display_usage() {
    printf("Usage: ./program_name [--system] [--user] [--sequential] [--samples=N] [--tdelay=T]\n");
}


