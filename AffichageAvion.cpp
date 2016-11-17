/* INCLUDES */

#include <osgViewer/Viewer>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/Light>
#include <osg/LightSource>

using namespace std;

int main()
{
	/* OBJECTS CREATION */

	/* VIEWER CREATION */ 

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer; 
	
	/* ROOT CREATION */

	osg::ref_ptr<osg::Group> root (new osg::Group);

	/* AIRCRAFT PATS CREATION */

	osg::ref_ptr<osg::PositionAttitudeTransform>  patAvionAmi1 = new osg::PositionAttitudeTransform();
	osg::ref_ptr<osg::PositionAttitudeTransform>  patAvionAmi2 = new osg::PositionAttitudeTransform();
	osg::ref_ptr<osg::PositionAttitudeTransform>  patAlignement = new osg::PositionAttitudeTransform();
	osg::ref_ptr<osg::PositionAttitudeTransform>  patAvionEnnemi1 = new osg::PositionAttitudeTransform();
	osg::ref_ptr<osg::PositionAttitudeTransform>  patAvionEnnemi2 = new osg::PositionAttitudeTransform();

	/* MATERIAL CREATION & INITIALISATION */
	
	osg::ref_ptr<osg::Material> mat (new osg::Material);
	osg::ref_ptr<osg::Material> mat2 (new osg::Material);
	mat->setDiffuse(mat->FRONT_AND_BACK,osg::Vec4f(0.1,0.1,0.1,1));
	mat2->setDiffuse(mat2->FRONT_AND_BACK,osg::Vec4f(0.1,0.1,0.1,1));

	/* AIRCRAFTS IMPORTATION */
	
	osg::ref_ptr<osg::Node> avionAmi(osgDB::readNodeFile("Avion.3ds"));
	osg::ref_ptr<osg::Node> avionEnnemi(osgDB::readNodeFile("TIE-fighter.3ds"));

	/* STATE SETS CREATION & INITIALISATION */

	osg::ref_ptr<osg::StateSet> StateSetAmi1(patAvionAmi1->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> StateSetAmi2(patAvionAmi2->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> StateSetEnnemi1(patAvionEnnemi1->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> StateSetEnnemi2(patAvionEnnemi2->getOrCreateStateSet());

	StateSetAmi1->setAttribute(mat);
	StateSetAmi2->setAttribute(mat);
	StateSetEnnemi1->setAttribute(mat2);
	StateSetEnnemi2->setAttribute(mat2);

	/* PAT INITIALISATION */
	
	patAvionAmi1->setPosition(osg::Vec3f(500,0,0));
	patAvionAmi2->setPosition(osg::Vec3f(0,500,0));

	patAvionEnnemi1->setScale(osg::Vec3f(3,3,3));
	patAvionEnnemi2->setScale(osg::Vec3f(3,3,3));

	patAvionEnnemi1->setPosition(osg::Vec3f(0,0,500));
	patAvionEnnemi2->setPosition(osg::Vec3f(0,0,0));

	/* SCENE GRAPH */
	
	root->addChild(patAvionAmi1.get());
	root->addChild(patAvionAmi2.get());
	root->addChild(patAvionEnnemi1.get());
	root->addChild(patAvionEnnemi2.get());

	patAvionAmi1->addChild(avionAmi.get());
	patAvionAmi2->addChild(avionAmi.get());
	patAvionEnnemi1->addChild(avionEnnemi.get());
	patAvionEnnemi2->addChild(avionEnnemi.get());

	/* START VIEWER */

	viewer->setUpViewInWindow(100, 100, 800, 800);
	viewer->setSceneData(root.get());
	viewer->getCamera()->setClearColor(osg::Vec4(0,0,0,1.0)); //Background color

	return (viewer->run());
}

