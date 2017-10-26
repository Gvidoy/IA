#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <time.h>

using namespace std;



// -----------------------------------------------------------
Agent::ActionType Agent::MejorElec(){

    int mov[4];
    int result;
    int dire;
    int calculo;
    ActionType movimiento;
    int aux = orientacion_;

    //Almaceno Lo que tengo alrededor
    mov[0]= mapa[x-1][y]; //Arriba
    mov[1]= mapa[x][y+1]; //Derecha
    mov[2]= mapa[x+1][y]; //Abajo
    mov[3]= mapa[x][y-1]; //Izquierda

    //Si todas las posibilidad
    if((mov[0]==mov[1]) && (mov[0]==mov[2])&& (mov[0]==mov[3])) {
        dire = 0;
    }
    else{
    //Si no busco la mejor opción de el vector mov[]

        result = mov[0];
        dire = 0;
    //Me quedo con la casilla mas pequeña
        for (int i = 1; i < 4; i++){
            if (result > mov[i]){
                result = mov[i];
                dire = i;
            }
        }
    }
    //Calculo la acción segun la orientación actual
    if(dire == aux){
        movimiento = actFORWARD;
    }
    else if((dire+1) == aux){
            movimiento = actTURN_L;
    }
    else{
            movimiento = actTURN_R;
    }
    return movimiento;
}

void Agent::RectiBump_(){
    if(orientacion_ == 0){
        x++;
    }
    else if(orientacion_ == 1){
        y--;
    }
    else if (orientacion_== 2){
        x--;
    }
    else if (orientacion_ == 3){
        y++;
    }
}


// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
    switch(ult_accion_){
        case actFORWARD:
            if (bump_){
                mapa[x][y]=MURO;
                //Rectifico la posición si choca
                RectiBump_();
                obstaculo_[orientacion_] = true;
            }
            else{
                for (int i = 0; i < 4; i++){
                    obstaculo_[i] = false;
                }
            }
            break;
        case actTURN_R:
            orientacion_++;
            if(orientacion_>3){
                orientacion_=0;
            }
            break;
        case actTURN_L:
            orientacion_--;
            if (orientacion_ < 0){
                orientacion_=3;
            }
            break;
    }

    ActionType accion;

    //Extraigo tufas si detecta mas de 5 trufas
    if(trufa_size_ > 5){
        accion = actEXTRACT;
    }
    //huele si trufas_size -1
    else if(trufa_size_ == -1){
        accion=actSNIFF;
    }
    else if(!obstaculo_[orientacion_]){
            if(orientaCcion_ == 0){
                if ((mapa[x-1][y]) == MURO){
                    accion = actTURN_R;
                }else{
                    mapa[x][y]++;
                    accion = MejorElec();
                        if(accion == actFORWARD){
                            x--;
                        }
                }
            }
            else if(orientacion_ == 1){
                if ((mapa[x][y+1]) == MURO){
                    accion = actTURN_R;
                }else{
                    mapa[x][y]++;
                    accion = MejorElec();
                    if(accion == actFORWARD){
                            y++;
                    }
                }
            }
            else if (orientacion_ == 2){
                if ((mapa[x+1][y]) == MURO){
                    accion = actTURN_R;
                }else{
                    mapa[x][y]++;
                    accion = MejorElec();
                    if(accion == actFORWARD){
                            x++;
                    }
                }
            }
            else if (orientacion_ == 3){
                if ((mapa[x][y-1]) == MURO){
                    accion = actTURN_R;
                }else{
                    mapa[x][y]++;
                    accion = MejorElec();
                    if(accion == actFORWARD){
                            y--;
                    }
                }
            }
    }
    else if (!obstaculo_[(orientacion_+1)%4]){
        accion = actTURN_R;
    }else{
        accion = actTURN_L;
    }
    ult_accion_ = accion;

	return accion;

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	trufa_size_ = env.TrufaAmount();
	bump_ = env.isJustBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actSNIFF: return "SNIFF";
	case Agent::actEXTRACT: return "EXTRACT";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
