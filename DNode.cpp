/*
 * DNode.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: 13027
 */
/* Shivam Chauhan and Estevan Bedolla */

#include <stdlib.h>
#include <iostream>
#include "DNode.hpp"
using namespace std;


DNode::DNode(string t, int p, int h, int m){
/*You need to write this!!!! */
  task = new Task(t, p, h, m);
  next = NULL;
  prev = NULL;
}


DNode::DNode(){
	task = NULL;
	next = NULL;
	prev = NULL;
}




