#include <irrlicht.h>
#include "EventHandler.hh"
#include "Player.hh"
#include "Map.hh"

using namespace irr;

int main(void) {
	irr::IrrlichtDevice* device =
			createDevice(video::EDT_OPENGL,
							  core::dimension2d<u32>(640,480),
							  32);
	video::IVideoDriver*  driver = device->getVideoDriver();
	scene::ISceneManager* sceneManager = device->getSceneManager();

	Map map("./assets/maps/Basic.map");

	/* MODELE */

	Player player(sceneManager, driver);

	/* MAP */

	scene::IMetaTriangleSelector* meta = sceneManager->createMetaTriangleSelector();
	if (!meta) {
		return 1;
	}
	for (auto & wall : map.getWalls()) {
		scene::ITriangleSelector*     selector = NULL;
		scene::IAnimatedMesh*         wallMesh = sceneManager->getMesh(("./assets/box/" + wall.getMesh() + ".obj").c_str());
		scene::ISceneNode*            wallNode = NULL;
		if (wallMesh) {
			wallMesh->setMaterialFlag(video::EMF_LIGHTING, false);
			wallNode = sceneManager->addOctreeSceneNode(wallMesh->getMesh(0));
			if (wallNode) {
                wallNode->setPosition(irr::core::vector3df(50, 50, -50) * wall.getPosition());
                wallNode->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
			}
			sceneManager->setAmbientLight(video::SColorf(1.0,1.0,1.0,0.0));
			selector = sceneManager->createOctreeTriangleSelector(wallMesh->getMesh(0), wallNode, 128);
			if (selector) {
				meta->addTriangleSelector(selector);
			}
		}
	}

	scene::ISceneNodeAnimator* anim = sceneManager->createCollisionResponseAnimator(
			meta, player.getMesh(), core::vector3df(10, 25, 10),
			core::vector3df(0,-10,0), core::vector3df(0,0,0));
	player.addAnimator(anim);
	anim->drop();

	scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode(
			0,
			core::vector3df(100, 100, 0),
			core::vector3df(100, 0, 100));

	EventHandler receiver;
	device->setEventReceiver(&receiver);

	/* RENDU */

	while (device->run()) {
		driver->beginScene(true, true, video::SColor(0,255,255,255));
		player.move(receiver);
		camera->setPosition(player.getPosition() + core::vector3df(0, 150, -100));
		camera->setTarget(player.getPosition());
		sceneManager->drawAll();
		driver->endScene();
	}

	device->drop();
	return 0;
}
