/*
 * MainDLL.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */
/* Shivam Chauhan and Estevan Bedolla */

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	TaskManager *list = new TaskManager("ListofTasks.txt");
}

