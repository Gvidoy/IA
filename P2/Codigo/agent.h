#ifndef AGENT__
#define AGENT__

#include <string>
using namespace std;


//Constantes
    const int MAXFILA = 20;
    const int MAXCOL = 20;
    const int MAXOBST = 4;
    const int MURO = 1000;


// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent{

public:
	Agent(){
        trufa_size_=-1;
        bump_=false;
        orientacion_= 0;
        for (int i = 0; i < 4; i++){
            obstaculo_[i] = false;
        }
        ult_accion_=actIDLE;
        for (int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                mapa[i][j]=1;
            }
        }
        y = 10;
        x = 10;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
	    actSNIFF,
	    actEXTRACT,
	    actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();

private:
	int trufa_size_;
	bool bump_;
	int orientacion_;
	bool obstaculo_[MAXOBST];
	ActionType ult_accion_;
	int mapa[MAXFILA][MAXCOL];
	int x;
	int y;

    ActionType MejorElec();
    void RectiBump_();

};

string ActionStr(Agent::ActionType);

#endif
