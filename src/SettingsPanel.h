//
//  SettingsPanel.h
//  Kepler
//
//  Created by Tom Carden on 8/25/11.
//  Copyright 2011 Bloom Studio, Inc. All rights reserved.
//

#pragma once

#include <sstream>

#include "cinder/app/AppCocoaTouch.h"
#include "cinder/gl/Texture.h"
#include "cinder/Font.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"

#include "BloomNode.h"
#include "Buttons.h"
#include "Slider.h"
#include "TextLabel.h"
#include "CinderIPodPlayer.h"

class SettingsPanel : public BloomNode {
public:
    
	enum ButtonId { NO_BUTTON, 
                    SHUFFLE, REPEAT, 
                    HELP, AUTO_MOVE, DRAW_RINGS, DRAW_TEXT, USE_GYRO, DEBUG_FEATURE,
                    PARAMSLIDER1, PARAMSLIDER2 };
    
    SettingsPanel() {};
    ~SettingsPanel() {};
    
    void setup( const ci::Vec2f &interfaceSize, 
                ci::ipod::Player *player,
                const ci::Font &font, 
                const ci::gl::Texture &smallButtonsTex );
    
    void update();
    
    // State stuff, passed onto UI classes directly...    
    void setHelpOn(bool on) { mHelpButton->setOn(on); };
	void setDebugOn(bool on) { mDebugButton->setOn(on); };
	void setGyroOn(bool on) { mGyroButton->setOn(on); };
    void setOrbitsOn(bool on) { mOrbitsButton->setOn(on); };
    void setLabelsOn(bool on) { mLabelsButton->setOn(on); };	
	void setShuffleOn(bool on) { mShuffleButton->setOn(on); };
	void setScreensaverOn(bool on){ mScreensaverButton->setOn(on); };
	void setRepeatMode(ci::ipod::Player::RepeatMode state)
    { 
        int stateInt = state == ci::ipod::Player::RepeatModeNone ? 0 :
        state == ci::ipod::Player::RepeatModeAll ? 1 :
        state == ci::ipod::Player::RepeatModeOne ? 2 : 0; // 0 for RepeatModeDefault
        mRepeatButton->setState(stateInt); 
    };	
	float getParamSlider1Value(){ return mParamSlider1->getValue(); }
	float getParamSlider2Value(){ return mParamSlider2->getValue(); }
    
	// !!! EVENT STUFF (slightly nicer interface for adding listeners)
	template<typename T>
    ci::CallbackId registerButtonPressed( T *obj, bool (T::*callback)(ButtonId) )
	{
		return mCallbacksButtonPressed.registerCb(std::bind1st(std::mem_fun(callback), obj));
	}
	
    bool addedToScene(); // from BloomNode
    void deepDraw();
        
private:
    
    // instantiate and set fonts/areas/textures (called once)
    void createChildren( const ci::Font &font, const ci::gl::Texture &uiSmallButtonsTex );
    
    // add everything (called once)
    void addChildren();
    
    // set positions (can be called repeatedly whenever interfaceSize changes)
    void setInterfaceSize( const ci::Vec2f &interfaceSize );
    
    // for detecting orientation change, updating layout    
    ci::Vec2f mInterfaceSize;
    
	// !!! EVENT STUFF (keep track of listeners)
	ci::CallbackMgr<bool(ButtonId)> mCallbacksButtonPressed;
    
    ///////////// UI Classes:
    
    // Remember:
    //
    //   -- SimpleButton is just a trigger (down when touched, up when not)
    //   -- ToggleButton is for things that are sticky, on or off
    //   -- TwoStateButton is really just for Play/Pause, but who knows
    //   -- ThreeStateButton is really just for RepeatMode, but who knows
    //
    // And furthermore thusly:
    //
    //   -- TextLabel is for simple static labels
    //   -- ScrollingLabel will flutter back and forth if you tell it the lastSomethingOrOtherTime
    //   -- TimeLabel will format a number of seconds as mm:ss
    //
    
    ToggleButton *mHelpButton;
    ToggleButton *mScreensaverButton;
    ToggleButton *mOrbitsButton;
    ToggleButton *mLabelsButton;
    ToggleButton *mDebugButton;
    ToggleButton *mGyroButton;
    ToggleButton *mShuffleButton;
    ThreeStateButton *mRepeatButton;
    
	TextLabel *mParamSlider1Label;
    Slider *mParamSlider1;
	TextLabel *mParamSlider2Label;
    Slider *mParamSlider2;        
};