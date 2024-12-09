#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Game.h"
#include "EndState.h"
class PlayState : public GameState
{
public:
    PlayState(Game* g, int l);
    virtual ~PlayState() = default;

    void render(SDL_Renderer* renderer) override;
    void update() override;

    void loadLevel(int l); // Carga el nivel

    void loadObjectMap(const string& mapFile); // Carga los objs del nivel

    // add object to stateList
    void addObject(SceneObject* o);

    void resetLevel();

    /// ===== Juego =====
    
    Collision checkCollision(const SDL_Rect& rect, Collision::Target target);

    void spawnMushroom(int x, int y);
    void spawnCoin(int x, int y);
    void goEndState(int aux);
    void playerHit();
    bool getMarioImmunity();

    /// ===== Getters y setters =====

    int getMapOffset() const { return mapOffset; }
    void setMapOffset(int m) { mapOffset = m; }

    void setGameWon(bool w) { gameWon = w; }

    // devuelve el numero total de niveles (o el numero del nivel final)
    int getLastLevel() const { return lastLevel; }

    int getLevel() { return level; }
    void setLevel(int n) { level = n; }

private:
    // coordenada x del extremo izquierdo de la vista
    int mapOffset;
    // indice para indicar el siguiente objeto a instanciar
    int nextObject;

    // vamos extrayendo objetos de la cola segun vaya avanzando el nivel
    std::vector<SceneObject*> objectQueue;

    bool gameWon;

    // nivel actual del juego
    int level;

    // ultimo nivel
    int lastLevel;

    // colores del fondo del nivel
    int r, g, b;

    /// --- SceneObjects ---

    Player* player = nullptr;
    SceneObject* tilemap = nullptr;

    // Objetos del juego
    GameList<SceneObject> sceneObjects;


};

#endif