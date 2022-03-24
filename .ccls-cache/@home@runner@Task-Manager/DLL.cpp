/* Shivam Chauhan and Estevan Bedolla */
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}
	DLL::DLL(string t, int p, int h, int m){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,p,h,m);
		first = n;
		last = n;
		numTasks=1;
		tothrs = h;
		totmin = m;
	}
	/***************************************************************************************************/
	/*Part 1																																		*/
	/***************************************************************************************************/
	void DLL::push(string n, int p, int h, int m) { // messed up 
    // does what you'd think, with a caveat that if the
	//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
	//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
	//task with a priority of 1, and insert the new task between the last task with a priority of
	//1 and the first task with a priority of 2
	//it also updates the total time of the list
    DNode *add = new DNode(n, p, h, m);
    if(numTasks == 0) { // creates new node to start 
      first = add;
      add->next = NULL;
      add->prev = NULL;
      last = add;
    }
    else if((add->task->priority == 3) || numTasks == 1){ // checks if priority is 3 and changes priority
      last->next = add;
      add->prev = last;
      add->next = NULL;
      last = add;
    }
    else { // compares priority to see if priorities intersect
      int prioritynum = 0;
      for(DNode *temp = last;;) {
        prioritynum = temp->task->priority;
        if(prioritynum == p) {
          add->next = temp->next;
          if(temp->next == NULL) { //checks if at end and makes add the last node
            last->next = add;
            add->prev = last;
            add->next = NULL;
            last = add;
          }
          else{  //makes add move up from temp 
            add->prev = temp->next->prev;
            temp->next->prev = add;
            temp->next = add;
          }
          break; // need this to break out of statements
        }
        else { // changes priority ! 
          temp = temp->prev;
          prioritynum = temp->task->priority;
          continue; //need this to get to next loop 
        }
      }
    }
    numTasks++; // increments through tasks
	}

	Task *DLL::pop() {  // DONE !!!
	//does what you'd think - make sure to update the total time of the list.
	//Note -this isn’t all that necessary for this particular project, but I 
	//kinda had to make you write pop because it’s //fundamental to so much of 
	//linked list data type uses (e.g., stack, undo).
    DNode *temp = last;
    last = last->prev;
    delete temp;
    last->next = NULL;
    numTasks--;
	}

	void DLL::printList() { //DONE!!!
		//prints out the entire list, along with the total time necessary to complete all tasks 
		//on the list
    DNode *temp = first;
    int timehr = 0, timemin = 0;
    while(temp!=NULL) {
      timehr+=temp->task->hr;
      timemin+=temp->task->min;
      temp->task->printTask();
      temp = temp->next;
    }
    timehr+=timemin/60;
    timemin = timemin%60;
    cout << "Total time necessary to complete all tasks is: " << timehr << ":" << timemin << endl;
	}

	void DLL::printList(int p) { // DONE!!!
		//print out only all the tasks with a priority of p, along with the total time necessary
		//to complete the tasks with a priority of p
    DNode *temp = first;
    int timehr = 0, timemin = 0; 
    while(temp!=NULL) {
      if(temp->task->priority==p) {
        temp->task->printTask();
        }
       temp = temp->next;
    }
    listDuration(&timehr, &timemin, p); 
    } 

	void DLL::moveUp(int t) { // does not change priortiy yet
		// moves task with number tn up one in the list.
	    //If it is at the beginning of the list,
        //it will be moved to the end of the list.
		// NOTE: if this moves a task up before a task with a higher priority (1 is
		// higher priority than 2 - I know the wording is a bit weird), then this
		// changes the priority of the task being moved to that higher priority
    DNode *temp = first;
    while(temp != NULL) {
		DNode *taskunder = temp->next;
    DNode *taskabove = temp->prev;
		if(temp->task->tasknum == t){
			if(temp->prev == NULL){ //checks if previous is empty (1st node)
				taskunder->prev = NULL;
				first = taskunder;
				last->next = temp;
				temp->prev = last;
				last = temp;
				temp->next = NULL;
			}
			else if(temp->next == NULL){ //checks if next is empty (last node)
				taskabove->prev->next = temp;
				temp->prev = taskabove->prev;
				temp->next = taskabove;
				taskabove->prev = temp;
				taskabove->next = NULL;
				last = taskabove;
			}
			else{ // for any other case
				taskabove->prev->next = temp;
				temp->prev = taskabove->prev;
				temp->next = taskabove;
				taskabove->prev = temp;
				taskabove->next = taskunder;
				taskunder->prev = taskabove;
        if(temp->task->priority > temp->next->task->priority) {
          temp->task->priority = temp->next->task->priority;
        }
			}
		}
      temp = temp->next;
      }
	}

	void DLL::listDuration(int *th, int *tm,int tp) { // DONE!!!
		// gets the list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)
		// I had you pass in the parameters as pointers for practice.
    DNode *temp = first;
    while(temp!=NULL) {
      if(temp->task->priority==tp) {
        *th += temp->task->hr;
        *tm += temp->task->min;
      }
      temp = temp->next;
    }
    *th+=*tm/60;
    *tm=*tm%60; 
	}
	
	
	void DLL::moveDown(int tn) { // need to update priority
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to
		//beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being
		//moved.
    DNode *temp = first;
    while(temp != NULL) { 
		DNode *taskabove = temp->prev;
		DNode *taskunder = temp->next;
      if(temp->task->tasknum == tn){
        if (temp->prev == NULL){ //checks if task before is empty (1st node)
          taskunder->next->prev = temp;
				  temp->next = taskunder->next;
				  temp->prev = taskunder;
				  taskunder->next = temp;
				  taskunder->prev = NULL;
				  first = taskunder;
			  }
			  else if (temp->next == NULL){ //checks if next is empty (last node)
				  taskabove->next = NULL;
				  last = taskabove;
				  first->prev = temp;
				  temp->next = first;
				  first = temp;
				  temp->prev = NULL;
			  }
			  else{ //for any other case
				  taskunder->next->prev = temp;
				  temp->next = taskunder->next;
				  temp->prev = taskunder;
				  taskunder->next = temp;
				  taskunder->prev = taskabove;
				  taskabove->next = taskunder;
          if(temp->task->priority > temp->prev->task->priority) {
          temp->task->priority = temp->next->task->priority;
        }
			  }
		  }
      temp = temp->next;
      }
    }

	int DLL::remove(int tn) { // DONE!!!
		//removes a task (based on its number) and updates the total time of the list
		//Make sure you link the next to the previous and the previous to the next.  The 
		//biggest catch with this method is making sure you test to make sure the node 
		//after and/or the node before the node you’re deleting aren’t NULL (i.e., you’re 
		//not deleting the first or last node in the list)
    DNode *temp = first;
    while(temp != NULL) {
      if(tn == temp->task->tasknum) {
        if(temp->prev == NULL) {
          first = temp->next;
        }
        else if(temp->next == NULL) {
          pop();
        }
        else{
          temp->prev->next = temp->next;
          temp->next->prev = temp->prev;
          }
      }
      temp = temp->next;
    }
    numTasks--;    
    return 0;
	}

	void DLL::changePriority(int tn, int newp) {
		//changes the priority of the task.  This method also moves the task to the end 
		//of the set of tasks with 
		//that priority.  In other words, if you have the following:
		/*task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task4, 2, 3:10
		task5, 2, 1:10
		task6, 3, 3:15
		task7, 3, 2:54

		And you change task6’s priority to 1, the resulting list should be:
		task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task6, 1, 3:15
		task4, 2, 3:10
		task5, 2, 1:10
		task7, 3, 2:54
		*/
    for(DNode *temp = first; temp !=NULL; temp = temp->next) {
      if(temp->task->tasknum == tn) {
          temp->task->priority = newp; 
        }
      }
	}

	DLL::~DLL(){
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp != NULL) {
			delete tmp;
			tmp = tmp2;
			if (tmp != NULL) {
				tmp2 = tmp2->next;
			}
		}
		first = NULL;
		last = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}

	/******************Optional Helper Methods********************************/
	void DLL::addTime(int h, int m) {
	}

	void DLL::removeTime(int h, int m) {
	}
	/********************End of Optional Helper Methods ********************/
