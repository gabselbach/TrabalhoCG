#ifndef GAME_H
#define GAME_H
#include <string.h>
class Game 
{
public:
	float delta =0.6f;
	int x=0;
	Game(int valor){
		x=valor;
	}
	char * setaTexto(int valor,std::string strin){
	std::stringstream final;
    //std::string vd = "pontos=";
    final << strin << valor;
    std::string nov(final.str());
    char *pal = new char[nov.size()+1];
    strcpy(pal, nov.c_str());
    return pal;
	}
	float retornaDelta(){
		return delta;
	}
private:
};
#endif