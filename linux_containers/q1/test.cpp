#include<iostream>
#include <chrono>
#include <sys/types.h>
#include <unistd.h>
#include <bits/stdc++.h>


using namespace std;
using namespace std::chrono;
int main(){
	//std::cout<<"start\n";
	//fork();
	auto start = high_resolution_clock::now();
	long i=0;
	pid_t pid = getpid();
	cout<<"pid:"<<pid<<"\n";
	//while(1);	
	char cmd[64];
	sprintf(cmd,"sudo echo %ld > /sys/fs/cgroup/cpu/cg1/tasks",(long)getpid());
	// strcat(cmd,string(pid));
	// strcat(cmd," > tasks");
	system(cmd);
	while(i<10000000000)i++;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << "Time taken by function: "
         << duration.count() << " seconds\n";
	return 0;
}
