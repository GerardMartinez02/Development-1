#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class SceneIntro;
class Map;
class ModuleFadeToBlack;
class ModulePhysics;
class ModulePlayer;
class SceneIntro;
class GameOver;
class DragonEnemy;
class ModuleEnemies;
class ModuleParticles;
class Particles;
class ModuleCollisions;
class Path;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadFile();
	bool SaveFile() const;

public:

	// Modules
	Window* win = nullptr;
	Input* input = nullptr;
	Render* render = nullptr;
	Textures* tex = nullptr;
	Audio* audio = nullptr;
	Scene* scene = nullptr;
	SceneIntro* intro = nullptr;
	/*GameOver* gameOver;*/
	Map* map = nullptr;
	ModuleFadeToBlack* fadeToBlack = nullptr;
	ModulePhysics* physics = nullptr;
	ModulePlayer* player = nullptr;
	ModuleEnemies* enemies = nullptr;
	SceneIntro* sceneIntro = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollisions* collisions = nullptr;
	Path* path = nullptr;
		

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	pugi::xml_document configFile;
	pugi::xml_document gameStateFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;
	float dt;

	mutable bool saveGameRequested;
	bool loadGameRequested;
};

extern App* app;

#endif	// __APP_H__