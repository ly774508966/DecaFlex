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
		mRightHand.Pinky_Proximal->setOrientation(1, -(float)DFDevice.LeftGlove().Pinky_Proximal/128.0f,0,0);
		// Pinky_Middle
		mRightHand.Pinky_Middle->setOrientation(1, -(float)DFDevice.LeftGlove().Pinky_Middle/128.0f,0,0);
		// Pinky_Distal
		mRightHand.Pinky_Distal->setOrientation(1, -(float)DFDevice.LeftGlove().Pinky_Distal/128.0f,0,0);

		// Ring_Meta

		// Ring_Proximal
		mRightHand.Ring_Proximal->setOrientation(1, -(float)DFDevice.LeftGlove().Ring_Proximal/128.0f,0,0);
		// Ring_Middle
		mRightHand.Ring_Middle->setOrientation(1, -(float)DFDevice.LeftGlove().Ring_Middle/128.0f,0,0);
		// Ring_Distal
		mRightHand.Ring_Distal->setOrientation(1, -(float)DFDevice.LeftGlove().Ring_Distal/128.0f,0,0);

		// Middle_Meta
		// Middle_Proximal
		mRightHand.Middle_Proximal->setOrientation(1, -(float)DFDevice.LeftGlove().Middle_Proximal/128.0f,0,0);
		// Middle_Middle
		mRightHand.Middle_Middle->setOrientation(1, -(float)DFDevice.LeftGlove().Middle_Middle/128.0f,0,0);
		// Middle_Distal
		mRightHand.Middle_Distal->setOrientation(1, -(float)DFDevice.LeftGlove().Middle_Distal/128.0f, 0,0);

		// Index_Meta
		
		// Index_Proximal	
		mRightHand.Index_Proximal->setOrientation(1,-(float)DFDevice.LeftGlove().Index_Proximal/128.0f,0,0);	// Index_Proximal
		// Index_Middle
		mRightHand.Index_Middle->setOrientation(1, -(float)DFDevice.LeftGlove().Index_Middle/128.0f,0,0);
		// Index_Distal
		mRightHand.Index_Distal->setOrientation(1, -(float)DFDevice.LeftGlove().Index_Distal/128.0f,0,0);

		// Thumb_Meta
		// mRightHand.Thumb_Meta->setOrientation(1, 0,0, -(float)DFDevice.LeftGlove().Thumb_Proximal/128.0f);
		// Thumb_Proximal
		mRightHand.Thumb_Proximal->setOrientation(1, -(float)DFDevice.LeftGlove().Thumb_Proximal/128.0f,0,0);
		// Thumb_Distal
		mRightHand.Thumb_Distal->setOrientation(1, -(float)DFDevice.LeftGlove().Thumb_Distal/128.0f,0,0);

		
		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{

			// Sequence
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(DFDevice.LeftGlove().Thumb_Meta));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(DFDevice.LeftGlove().Thumb_Proximal));
			
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(DFDevice.LeftGlove().Thumb_Distal));

			mDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(DFDevice.LeftGlove().Index_Proximal));
			mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(DFDevice.LeftGlove().Index_Middle));
			mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(DFDevice.LeftGlove().Index_Distal));

			mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(DFDevice.LeftGlove().Middle_Proximal));
			mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(DFDevice.LeftGlove().Middle_Middle));
			mDetailsPanel->setParamValue(8, Ogre::StringConverter::toString(DFDevice.LeftGlove().Middle_Distal));

			mDetailsPanel->setParamValue(9, Ogre::StringConverter::toString(DFDevice.LeftGlove().Ring_Proximal));
			mDetailsPanel->setParamValue(10, Ogre::StringConverter::toString(DFDevice.LeftGlove().Ring_Middle));
			mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(DFDevice.LeftGlove().Ring_Distal));

			mDetailsPanel->setParamValue(12, Ogre::StringConverter::toString(DFDevice.LeftGlove().Pinky_Proximal));
			mDetailsPanel->setParamValue(13, Ogre::StringConverter::toString(DFDevice.LeftGlove().Pinky_Middle));
			mDetailsPanel->setParamValue(14, Ogre::StringConverter::toString(DFDevice.LeftGlove().Pinky_Distal));
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
