
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
#include <string>
using std::string;
#include "stdlib.h"

#include "environment.h"
#include "random_num_gen.h"
#include"include/GL/glui.h"

Environment::Environment(ifstream &infile)
{
	string comment;
	getline(infile, comment);
	infile >> agentPosX_ >> agentPosY_ >> dirtyProb_ >> randomSeed_;
    agentOriented_=0; //Siempre mira hacia el norte

	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			char c;
			infile >> c;
			if (c == MAP_ROAD) {
   				maze_[row][col] = 0;
			}
			else if (c == MAP_OBSTACLE) {
   				maze_[row][col] = OBSTACLE;
			}
			else if (c == MAP_OBJETO) {
   				maze_[row][col] = OBJETO;
			}
			else {
				cout << c << " is an unknown symbol in agent.map!"; exit(1);
			}
		}// for - col
	}// for - row

	CNY70_ = false;
	BUMPER_= false;
	preAction_=Agent::actIDLE;
}
// -----------------------------------------------------------
void Environment::Show(int w,int h) const
{
	const static float dirty_level=50.0;
	float length=(float)(w>h?h:w)/(float)(MAZE_SIZE+4);
	for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			float x=(col-MAZE_SIZE/2)*length*2+length,y=(MAZE_SIZE/2-row)*length*2-length;
			if (maze_[row][col] == OBSTACLE){
				//cout << "XXXXXX";

				glBegin(GL_POLYGON);
					glColor3f(0.5,0.25,0.0);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
			}
			else if (maze_[row][col] == OBJETO){
				    glBegin(GL_POLYGON);
					  //glColor3f(0.0,0.0,0.0);
					  //glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					  //glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
					  glColor3f(0.1,0.1,0.1);
					  glVertex2f(x-length/2,y-length/2);	glVertex2f(x+length/2,y-length/2);
					  glVertex2f(x+length/2,y+length/2);	glVertex2f(x-length/2,y+length/2);
                    glEnd();
			     }
			else
			{
				char symbol = ' ';
   				if (row == agentPosX_ && col == agentPosY_){
					float size=0.8*length;
					symbol = '=';
					switch(preAction_){
						case Agent::actIDLE:
   						    switch (agentOriented_){
   						      case 0: // Orientacion Norte
							         glBegin(GL_POLYGON);
 							         if(CNY70_){
								       glColor3f(1.0,0.0,0.0);
							         }
							         else
								       glColor3f(0.0,0.0,1.0);
 								     glVertex2f(x,y+size);
								     glVertex2f(x+size,y-size);	glVertex2f(x-size,y-size);
							         glEnd();
							         break;
                              case 1: // Orientacion Este
							         glBegin(GL_POLYGON);
 							         if(CNY70_){
								       glColor3f(1.0,0.0,0.0);
							         }
							         else{
								       glColor3f(0.0,0.0,1.0);
                                     }
 								     glVertex2f(x+size,y);
								     glVertex2f(x-size,y-size);	glVertex2f(x-size,y+size);
								     glEnd();
								     break;
                              case 2: // Orientacion Sur
							         glBegin(GL_POLYGON);
 							         if(CNY70_){
								       glColor3f(1.0,0.0,0.0);
							         }
							         else
								       glColor3f(0.0,0.0,1.0);
 								     glVertex2f(x,y-size);
								     glVertex2f(x+size,y+size);	glVertex2f(x-size,y+size);
								     glEnd();
								     break;
                              case 3: // Orientacion Oeste
							         glBegin(GL_POLYGON);
 							         if(CNY70_){
								       glColor3f(1.0,0.0,0.0);
							         }
							         else
								       glColor3f(0.0,0.0,1.0);
 								     glVertex2f(x-size,y);
								     glVertex2f(x+size,y-size);	glVertex2f(x+size,y+size);
								     glEnd();
								     break;
   						    }
							break;
						case Agent::actFORWARD:
							if(CNY70_){
								glColor3f(1.0,0.0,0.0);
							}
							else{
								glColor3f(0.0,1.0,0.0);
							}
   						    switch (agentOriented_){
   						      case 0: // Orientacion Norte
							         glBegin(GL_POLYGON);
								     glVertex2f(x,y+size);
								     glVertex2f(x+size,y-size);	glVertex2f(x-size,y-size);
							         glEnd();
							         break;
                              case 1: // Orientacion Este
							         glBegin(GL_POLYGON);
								     glVertex2f(x+size,y);
								     glVertex2f(x-size,y-size);	glVertex2f(x-size,y+size);
								     glEnd();
								     break;
                              case 2: // Orientacion Sur
							         glBegin(GL_POLYGON);
								     glVertex2f(x,y-size);
								     glVertex2f(x+size,y+size);	glVertex2f(x-size,y+size);
								     glEnd();
								     break;
                              case 3: // Orientacion Oeste
							         glBegin(GL_POLYGON);
								     glVertex2f(x-size,y);
								     glVertex2f(x+size,y-size);	glVertex2f(x+size,y+size);
								     glEnd();
								     break;
   						    }
							break;
						case Agent::actTURN_R:
							if(CNY70_){
								glColor3f(1.0,0.0,0.0);
							}
							else{
								glColor3f(0.0,1.0,0.0);
							}
   						    switch (agentOriented_){
   						      case 0: // Orientacion Norte
							         glBegin(GL_POLYGON);
								     glVertex2f(x,y+size);
								     glVertex2f(x+size,y-size);	glVertex2f(x-size,y-size);
							         glEnd();
							         break;
                              case 1: // Orientacion Este
							         glBegin(GL_POLYGON);
								     glVertex2f(x+size,y);
								     glVertex2f(x-size,y-size);	glVertex2f(x-size,y+size);
								     glEnd();
								     break;
                              case 2: // Orientacion Sur
							         glBegin(GL_POLYGON);
								     glVertex2f(x,y-size);
								     glVertex2f(x+size,y+size);	glVertex2f(x-size,y+size);
								     glEnd();
								     break;
                              case 3: // Orientacion Oeste
							         glBegin(GL_POLYGON);
								     glVertex2f(x-size,y);
								     glVertex2f(x+size,y-size);	glVertex2f(x+size,y+size);
								     glEnd();
								     break;
   						    }
							break;
					}
				}
				glBegin(GL_POLYGON);
					glColor3f(((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level,((float)(dirty_level-maze_[row][col]))/dirty_level);
					glVertex2f(x-length,y-length);	glVertex2f(x+length,y-length);
					glVertex2f(x+length,y+length);	glVertex2f(x-length,y+length);
				glEnd();
				//cout << symbol;
				//cout << setw(4) << maze_[row][col];
				//cout << symbol;

			}
		}// for - col
		//cout << endl;
	}// for - row
}
// -----------------------------------------------------------
void Environment::Change(const RandomNumberGenerator &rng)
{
	/*for (int row=0; row<MAZE_SIZE; row+=1)
	{
		for (int col=0; col<MAZE_SIZE; col+=1)
		{
			if (maze_[row][col] != OBSTACLE &&
			    static_cast<double>(rng.RandomValue())/RAND_MAX < dirtyProb_) // probability: 0.01
			{
				maze_[row][col] += 1;
			}
		}// for - col
	}// for - row*/
}
// -----------------------------------------------------------
void Environment::AcceptAction(Agent::ActionType action)
{
    CNY70_=false;
    BUMPER_=false;

     switch(agentOriented_){
      case 0: // Orientacion Norte
             if (maze_[agentPosX_-1][agentPosY_] == OBSTACLE)
	         CNY70_ = true;
             if (maze_[agentPosX_-1][agentPosY_] == OBJETO)
             BUMPER_= true;
	         break;
	  case 1: // Orientacion Este
	         if (maze_[agentPosX_][agentPosY_+1] == OBSTACLE)
	         CNY70_ = true;
	         if (maze_[agentPosX_][agentPosY_+1] == OBJETO)
             BUMPER_= true;
	         break;
      case 2: // Orientacion Sur
	         if (maze_[agentPosX_+1][agentPosY_] == OBSTACLE)
	         CNY70_ = true;
	         if (maze_[agentPosX_+1][agentPosY_] == OBJETO)
             BUMPER_= true;
             break;
      case 3: // Orientacion Oeste
	         if (maze_[agentPosX_][agentPosY_-1] == OBSTACLE)
	         CNY70_ = true;
	         if (maze_[agentPosX_][agentPosY_-1] == OBJETO)
             BUMPER_= true;
             break;
    }

	switch (action)
	{
		case Agent::actFORWARD:
		    switch(agentOriented_){
                case 0: // Orientacion Norte
			            if (maze_[agentPosX_-1][agentPosY_] != OBSTACLE and maze_[agentPosX_-1][agentPosY_] != OBJETO)
			               agentPosX_-=1;
			            break;
			    case 1: // Orientacion Este
			            if (maze_[agentPosX_][agentPosY_+1] != OBSTACLE and maze_[agentPosX_][agentPosY_+1] != OBJETO)
			               agentPosY_+=1;
			            break;
                case 2: // Orientacion Sur
			            if (maze_[agentPosX_+1][agentPosY_] != OBSTACLE and maze_[agentPosX_+1][agentPosY_] != OBJETO)
			              agentPosX_+=1;
                        break;
                case 3: // Orientacion Oeste
			            if (maze_[agentPosX_][agentPosY_-1] != OBSTACLE and maze_[agentPosX_][agentPosY_-1] != OBJETO)
			              agentPosY_-=1;
                        break;

		    }
		    break;
		case Agent::actTURN_R:
		    agentOriented_ = (agentOriented_+1)%4;
			break;

	}

     CNY70_=false;
     BUMPER_=false;

     switch(agentOriented_){
      case 0: // Orientacion Norte
             if (maze_[agentPosX_-1][agentPosY_] == OBSTACLE)
	         CNY70_ = true;
             if (maze_[agentPosX_-1][agentPosY_] == OBJETO)
             BUMPER_= true;
	         break;
	  case 1: // Orientacion Este
	         if (maze_[agentPosX_][agentPosY_+1] == OBSTACLE)
	         CNY70_ = true;
	         if (maze_[agentPosX_][agentPosY_+1] == OBJETO)
             BUMPER_= true;
	         break;
      case 2: // Orientacion Sur
	         if (maze_[agentPosX_+1][agentPosY_] == OBSTACLE)
	         CNY70_ = true;
	         if (maze_[agentPosX_+1][agentPosY_] == OBJETO)
             BUMPER_= true;
             break;
      case 3: // Orientacion Oeste
	         if (maze_[agentPosX_][agentPosY_-1] == OBSTACLE)
	         CNY70_ = true;
	         if (maze_[agentPosX_][agentPosY_-1] == OBJETO)
             BUMPER_= true;
             break;
    }

	preAction_=action;
}
// -----------------------------------------------------------
