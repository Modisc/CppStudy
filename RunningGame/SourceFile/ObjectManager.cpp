#include "ObjectManager.h"
#include "Player.h"

ObjectManager* ObjectManager::obj_manager_instance_ = NULL;

ObjectManager::ObjectManager() : player_(NULL)
{
}

ObjectManager::~ObjectManager()
{
	SAFE_DELETE(player_);
}

bool ObjectManager::Init()
{
	player_ = new Player;
	player_->Init();
	return true;
}
