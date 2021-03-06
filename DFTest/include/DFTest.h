/*
-----------------------------------------------------------------------------
Filename:    DFTest.h
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.8.x Application Wizard for VC10 (May 2012)
      https://bitbucket.org/jacmoe/ogreappwizards
-----------------------------------------------------------------------------
*/
#ifndef __DFTest_h_
#define __DFTest_h_

#include "BaseApplication.h"
#include "SkeletonDebug.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

#include "DecaFlex.h"

#include <memory>



struct HandBones
{
	Ogre::Bone* Pinky_Meta;		// Pinky_Meta
	Ogre::Bone* Pinky_Proximal;	// Pinky_Proximal
	Ogre::Bone* Pinky_Middle;	// Pinky_Middle
	Ogre::Bone* Pinky_Distal;	// Pinky_Distal

	Ogre::Bone* Ring_Meta;		// Ring_Meta
	Ogre::Bone* Ring_Proximal;	// Ring_Proximal
	Ogre::Bone* Ring_Middle;	// Ring_Middle
	Ogre::Bone* Ring_Distal;	// Ring_Distal

	Ogre::Bone* Middle_Meta;		// Middle_Meta
	Ogre::Bone* Middle_Proximal;	// Middle_Proximal
	Ogre::Bone* Middle_Middle;		// Middle_Middle
	Ogre::Bone* Middle_Distal;		// Middle_Distal

	Ogre::Bone*	Index_Meta;		// Index_Meta
	Ogre::Bone* Index_Proximal;	// Index_Proximal
	Ogre::Bone* Index_Middle;	// Index_Middle
	Ogre::Bone* Index_Distal;	// Index_Distal

	Ogre::Bone* Thumb_Meta;		// Thumb_Meta
	Ogre::Bone* Thumb_Proximal;	// Thumb_Proximal
	Ogre::Bone* Thumb_Distal;	// Thumb_Distal

	Ogre::Node* Wrist;
};



class DFTest : public BaseApplication
{
public:
    DFTest(void);
    virtual ~DFTest(void);

	void connect();	/// Connect to device

	void disconnect();			/// Disconnect from device
	virtual void update();		/// Get latest device RAW frame.

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
    
	virtual void createScene(void);
	void setupHand(HandBones & handStruct, Ogre::SkeletonInstance* pSkeleton);

private:
	
	DecaFlex DFDevice;
	OgreBites::TextBox* pTextBox;
	SkeletonDebug* pSkeletonDebug;
	Ogre::Entity* rightHand;
	HandBones mRightHand;

	unsigned int somenumber;
};

#endif // #ifndef __DFTest_h_

