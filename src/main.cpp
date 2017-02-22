#include <irrlicht.h>
#include "EventHandler.hh"
#include "Player.hh"

int main(void) {

	irr::IrrlichtDevice* device =
	        irr::createDevice(irr::video::EDT_OPENGL,
	                          irr::core::dimension2d<irr::u32>(640,480),
	                          32);
	irr::video::IVideoDriver*  driver = device->getVideoDriver();
	irr::scene::ISceneManager* sceneManager = device->getSceneManager();
	// device->getCursorControl()->setVisible(false);

	/* MODELE */

  Player player(sceneManager, driver);

	/* MAP */

	irr::scene::ITriangleSelector* selector = NULL;
	irr::scene::IAnimatedMesh*     mapMesh = sceneManager->getMesh("./media/awp_india.obj");
	irr::scene::ISceneNode*        mapNode = NULL;
	if (mapMesh) {
		mapMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		mapNode = sceneManager->addOctreeSceneNode(mapMesh->getMesh(0));
		if (mapNode) {
			mapNode->setPosition(irr::core::vector3df(0,-140,0));
		}
		sceneManager->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
		selector = sceneManager->createOctreeTriangleSelector(mapMesh->getMesh(0), mapNode, 128);
		if (selector) {
			irr::scene::ISceneNodeAnimator* anim = sceneManager->createCollisionResponseAnimator(
			        selector, player.getMesh(), irr::core::vector3df(10, 25, 10),
			        irr::core::vector3df(0,-10,0), irr::core::vector3df(0,0,0));
			selector->drop();
			player.addAnimator(anim);
			anim->drop();
		}
	}

	//      // Maintenant, nous créons trois personnages animés que nous pourrons choisir, ainsi qu'une lumière dynamique pour les éclairer,
	//      // et un panneau pour dessiner où nous trouvons une intersection.
	//
	//      // Tout d'abord, débarrassons-nous du curseur de la souris. Nous utiliserons un panneau pour montrer ce à quoi nous regardons.
	//      device->getCursorControl()->setVisible(false);
	//
	//      // On ajoute le panneau.
	//      scene::IBillboardSceneNode * bill = sceneManager->addBillboardSceneNode();
	//      bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//      bill->setMaterialTexture(0, driver->getTexture("../../media/particle.bmp"));
	//      bill->setMaterialFlag(video::EMF_LIGHTING, false);
	//      bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	//      bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	//      bill->setID(ID_IsNotPickable); // Ceci s'assure que nous n'effectuons pas le choix avec le rayon accidentellement.
	//      map->setTriangleSelector(selector);
	// }
	//

	/* CAMERA */

	// irr::SKeyMap keyMap[5];                             // re-assigne les commandes
	// keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
	// keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
	// keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
	// keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
	// keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
	// keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
	// keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
	// keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
	// keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
	// keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace
	//
	// irr::scene::ICameraSceneNode* camera =
	// sceneManager->addCameraSceneNodeFPS(       // ajout de la camera FPS
	//      0,                                     // pas de noeud parent
	//      100.0f,                                // vitesse de rotation
	//      0.1f,                                  // vitesse de deplacement
	//      -1,                                    // pas de numero d'ID
	//      keyMap,                                // on change la keymap
	//      5);                                    // avec une taille de 5
	//
	// camera->setPosition(irr::core::vector3df(100, 100, 0));
	// camera->setTarget(irr::core::vector3df(100, 0, 100));

	irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode(
	        0,
	        irr::core::vector3df(100, 100, 0),
	        irr::core::vector3df(100, 0, 100));

	EventHandler receiver;
	device->setEventReceiver(&receiver);

	/* RENDU */

	while (device->run()) {
		driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
		player.move(receiver);
		camera->setPosition(player.getPosition() + irr::core::vector3df(0, 150, -100));
		camera->setTarget(player.getPosition());
		sceneManager->drawAll ();
		driver->endScene ();
	}

	device->drop();
	return 0;
}
