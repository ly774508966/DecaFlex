/*

	DecaFlex™ Test application.

*/

#include "DFTest.h"



//-------------------------------------------------------------------------------------
DFTest::DFTest(void):somenumber(0) ,pSkeletonDebug(NULL)
{
}
//-------------------------------------------------------------------------------------
DFTest::~DFTest(void)
{
	disconnect();
}

void DFTest::setupHand( HandBones & handStruct, Ogre::SkeletonInstance* pSkeleton )
{
	handStruct.Pinky_Meta = pSkeleton->getBone("Pinky_Meta");	// Pinky_Meta
	handStruct.Pinky_Meta->setManuallyControlled(true);

	handStruct.Pinky_Proximal = pSkeleton->getBone("Pinky_Proximal");	// Pinky_Proximal
	handStruct.Pinky_Proximal->setManuallyControlled(true);

	handStruct.Pinky_Middle = pSkeleton->getBone("Pinky_Middle");	// Pinky_Middle
	handStruct.Pinky_Middle->setManuallyControlled(true);

	handStruct.Pinky_Distal = pSkeleton->getBone("Pinky_Distal");	// Pinky_Distal
	handStruct.Pinky_Distal->setManuallyControlled(true);

	handStruct.Ring_Meta = pSkeleton->getBone("Ring_Meta");	// Ring_Meta
	handStruct.Ring_Meta->setManuallyControlled(true);

	handStruct.Ring_Proximal = pSkeleton->getBone("Ring_Proximal");	// Ring_Proximal
	handStruct.Ring_Proximal->setManuallyControlled(true);

	handStruct.Ring_Middle = pSkeleton->getBone("Ring_Middle");	// Ring_Middle
	handStruct.Ring_Middle->setManuallyControlled(true);

	handStruct.Ring_Distal = pSkeleton->getBone("Ring_Distal");	// Ring_Distal
	handStruct.Ring_Distal->setManuallyControlled(true);

	handStruct.Middle_Meta = pSkeleton->getBone("Middle_Meta");	// Middle_Meta
	handStruct.Middle_Meta->setManuallyControlled(true);

	handStruct.Middle_Proximal = pSkeleton->getBone("Middle_Proximal");	// Middle_Proximal
	handStruct.Middle_Proximal->setManuallyControlled(true);

	handStruct.Middle_Middle = pSkeleton->getBone("Middle_Middle");	// Middle_Middle
	handStruct.Middle_Middle->setManuallyControlled(true);

	handStruct.Middle_Distal = pSkeleton->getBone("Middle_Distal");	// Middle_Distal
	handStruct.Middle_Distal->setManuallyControlled(true);

	handStruct.Index_Meta = pSkeleton->getBone("Index_Meta");	// Index_Meta
	handStruct.Index_Meta->setManuallyControlled(true);

	handStruct.Index_Proximal = pSkeleton->getBone("Index_Proximal");
	handStruct.Index_Proximal->setManuallyControlled(true);

	handStruct.Index_Middle = pSkeleton->getBone("Index_Middle");		// Index_Middle
	handStruct.Index_Middle->setManuallyControlled(true);

	handStruct.Index_Distal = pSkeleton->getBone("Index_Distal");		// Index_Distal
	handStruct.Index_Distal->setManuallyControlled(true);


	handStruct.Thumb_Meta = pSkeleton->getBone("Thumb_Meta");	// Thumb_Meta
	handStruct.Thumb_Meta->setManuallyControlled(true);

	handStruct.Thumb_Proximal = pSkeleton->getBone("Thumb_Proximal");	// Thumb_Proximal
	handStruct.Thumb_Proximal->setManuallyControlled(true);

	handStruct.Thumb_Distal = pSkeleton->getBone("Thumb_Distal");	// Thumb_Distal
	handStruct.Thumb_Distal->setManuallyControlled(true);

}


//-------------------------------------------------------------------------------------
void DFTest::createScene(void)
{

    rightHand = mSceneMgr->createEntity("Hand", "RainerHand.mesh");

    Ogre::SceneNode* handNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    handNode->attachObject(rightHand);
	handNode->scale(5, 5, 5);	
	pSkeletonDebug = new SkeletonDebug(rightHand, mSceneMgr, mCamera, 2.0F);
	pSkeletonDebug->setAxesScale(1);
	pSkeletonDebug->showAxes(false);
	

//	handNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(180));
//	rightHand->setDisplaySkeleton(true);
	
	// Setup bones
	setupHand(mRightHand, rightHand->getSkeleton());
	
//	rightHand->setDebugDisplayEnabled(true);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);

}

void DFTest::connect()
{
	
	// Locate the device.
//	pTextBox = mTrayMgr->createTextBox(OgreBites::TrayLocation::TL_TOPLEFT, "RAWUpdate","RAWData", 0.5, 0.5);
//	pTextBox->setText("Test");

	// Enter RAW Mode
	DFDevice.SetRAWMode();


}

void DFTest::disconnect()
{
	

}

void DFTest::update()
{
	
	if(DFDevice.Update())
	{

		// Update bone positions

		// Pinky_Meta
		// Pinky_Proximal
		// Pinky_Middle
		// Pinky_Distal

		// Ring_Meta
		// Ring_Proximal
		// Ring_Middle
		// Ring_Distal

		// Middle_Meta
		// Middle_Proximal
		// Middle_Middle
		// Middle_Distal

		// Index_Meta
		mRightHand.Index_Proximal->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(20));	// Index_Proximal	
		// Index_Middle
		// Index_Distal

		// Thumb_Meta
		// Thumb_Proximal
		// Index_Middle
		// Index_Distal

		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{

			// Sequence
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(DFDevice.LeftGlove().SequenceID));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(DFDevice.LeftGlove().BatteryStatus));
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(DFDevice.LeftGlove().Accel_X));
			mDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(DFDevice.LeftGlove().Accel_Y));
			mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(DFDevice.LeftGlove().Accel_Z));
			mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(DFDevice.LeftGlove().Gyro_X));
			mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(DFDevice.LeftGlove().Gyro_Y));
			mDetailsPanel->setParamValue(8, Ogre::StringConverter::toString(DFDevice.LeftGlove().Gyro_Z));
			mDetailsPanel->setParamValue(10, Ogre::StringConverter::toString(DFDevice.LeftGlove().Thumb_Proximal));
			mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(DFDevice.LeftGlove().Thumb_Middle));
			mDetailsPanel->setParamValue(12, Ogre::StringConverter::toString(DFDevice.LeftGlove().Thumb_Distal));

			mDetailsPanel->setParamValue(13, Ogre::StringConverter::toString(mRightHand.Index_Proximal->getOrientation()));
			mDetailsPanel->setParamValue(14, Ogre::StringConverter::toString(mRightHand.Index_Middle->getOrientation()));
			mDetailsPanel->setParamValue(15, Ogre::StringConverter::toString(mRightHand.Index_Distal->getOrientation()));

			mDetailsPanel->setParamValue(16, Ogre::StringConverter::toString(DFDevice.LeftGlove().Middle_Proximal));
			mDetailsPanel->setParamValue(17, Ogre::StringConverter::toString(DFDevice.LeftGlove().Middle_Middle));
			mDetailsPanel->setParamValue(18, Ogre::StringConverter::toString(DFDevice.LeftGlove().Middle_Distal));

			mDetailsPanel->setParamValue(19, Ogre::StringConverter::toString(DFDevice.LeftGlove().Ring_Proximal));
			mDetailsPanel->setParamValue(20, Ogre::StringConverter::toString(DFDevice.LeftGlove().Ring_Middle));
			mDetailsPanel->setParamValue(21, Ogre::StringConverter::toString(DFDevice.LeftGlove().Ring_Distal));

			mDetailsPanel->setParamValue(22, Ogre::StringConverter::toString(DFDevice.LeftGlove().Pinky_Proximal));
			mDetailsPanel->setParamValue(23, Ogre::StringConverter::toString(DFDevice.LeftGlove().Pinky_Middle));
			mDetailsPanel->setParamValue(24, Ogre::StringConverter::toString(somenumber++));
		}
	}


}

bool DFTest::frameRenderingQueued( const Ogre::FrameEvent& evt )
{
	
	if (pSkeletonDebug)
	{
		pSkeletonDebug->update();
	}

	
	// Finished
	return BaseApplication::frameRenderingQueued(evt);

}






#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        DFTest app;

        try {
			app.connect();
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
