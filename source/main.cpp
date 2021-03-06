#include <iostream>
#include<SFML/Graphics.hpp>

#include "controleur.h"

using namespace sf;

bool jeuEnCours=false;
bool jeuPause=false;
bool jeuFinPartie=false;
bool jeuDebut=false;
bool jeuRejouer=false;
bool jeuSauvegarde=false;
bool tetroLibre=false; //pour liberer le tetromino en stock touche C
bool descenteRap=false;
int sourisX=0,sourisY=0;
int nbLignesTemp=0,scoreTemp=0;


int main()
{
    srand(time(0));
    RenderWindow fenetre(VideoMode(900,700),"Tetris");
    Controleur controleurJ(fenetre);
    sf::Clock horl; 
    float timer=0;
    float delai=0.1f;

    while(fenetre.isOpen()) //Boucle jeu
    {
        float temps = horl.getElapsedTime().asSeconds(); //Mesurer le temps
		horl.restart();
        timer+=temps;

        Event evenement;
        while(fenetre.pollEvent(evenement))
        {
            // fermeture de la fenetre
            if(evenement.type==Event::Closed) {fenetre.close();}

            if(evenement.type==Event::MouseMoved) //Déplacement de la souris
            {
                sourisX=evenement.mouseMove.x;
                sourisY=evenement.mouseMove.y;
                if(!jeuEnCours) {controleurJ.gestionDplSouris();}
                else if(jeuEnCours && jeuPause) {controleurJ.gestionDplSouris();}
                else{}
            }


            switch(evenement.type)
            {
            case Event::MouseButtonPressed:
                if(jeuEnCours)
                
                    if(jeuPause)
                    {
                        Mouse::Button button = evenement.mouseButton.button
                        if (button == Mouse::Left) {controleurJ.gestionSelecSouris();}
                    }
                    else
                    {
                        Mouse::Button button = evenement.mouseButton.button;

                        if (button == Mouse::Left) {controleurJ.teleporTetro();
                        if (button == Mouse::Right) {controleurJ.stockerTetroActif();}
                    }
                }
                else
                {
                    Mouse::Button button = evenement.mouseButton.button;
                    if (button == Mouse::Left) 
                    {
                        controleurJ.gestionSelecSouris();
                        if(jeuDebut) {controleurJ.debutJeu();}
                    }
                }
                break;

            case Event::KeyPressed:
                if(jeuEnCours)
                {
                    //Assignation Touche/Action
                    if(!jeuPause)
                    {
                        if(sf::Keyboard::isKeyPressed(Keyboard::Left))
                        {
                            if(timer>delai)
                            {
                                controleurJ.mouvementTetro(mouv_g);
                                timer=0;
                            }
                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Right))
                        {
                            if(timer>delai)
                            {
                                controleurJ.mouvementTetro(mouv_d);
                                timer=0;
                            }
                        }
                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        {
                            controleurJ.rotationTertro(ROTATION_D);
                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Down))
                        {
                            controleurJ.descenteRapide();
                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Z))
                        {
                            controleurJ.rotationTertro(ROTATION_G);
                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::C))
                        {
                            controleurJ.stockerTetroActif();
                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            controleurJ.pauseJeu();
                        }
                        else if(sf::Keyboard::isKeyPressed(Keyboard::Space))
                        {
                            controleurJ.teleporTetro();
                        }
                        else{}
                    }
                    else
                    {
                        if(sf::Keyboard::isKeyPressed(Keyboard::Escape)) {controleurJ.pauseJeu();}
                    }
                }
                else{}
                break;

            case Event::TextEntered:
                if(jeuEnCours && jeuPause)
                {
                    if(evenement.text.unicode>96 && evenement.text.unicode<123) // de a ŕ z
                    {
                        char characTape;
                        characTape=static_cast<char>(evenement.text.unicode);
                        std::cout<<"ASCII character : "<<evenement.text.unicode<<std::endl;
                        controleurJ.saisieL(characTape);
                    }
                }
                break;
            default:;
            }
        }

        if(jeuEnCours)
        {
            if(!jeuPause) {controleurJ.gestMajDonnees();}
        }
        else
        {
            if(jeuSauvegarde)
            {
                controleurJ.sauvegardeScore();
                controleurJ.reinitTablScore();
            }
        }

        fenetre.clear(Color(82,82,82));
        controleurJ.afficheFondEc();

        if(jeuEnCours){controleurJ.afficheJeu();}
        else{controleurJ.afficheMenu();}
        fenetre.display();
    }

    return 0;
}
