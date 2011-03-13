/*
 *  NodeAlbum.h
 *  Bloom
 *
 *  Created by Robert Hodgin on 1/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "Node.h"
#include "cinder/Vector.h"

class NodeAlbum : public Node
{
  public:
	NodeAlbum( Node *parent, int index, const ci::Font &font );
	
	void update( const ci::Matrix44f &mat );
	void drawStar();
	void drawStarGlow();
	void drawOrbitRing();
	void drawPlanet( const ci::Matrix44f &accelMatrix, const std::vector< ci::gl::Texture> &planets );
	void drawClouds( const ci::Matrix44f &accelMatrix, const std::vector< ci::gl::Texture> &clouds );
	void drawRings( const ci::gl::Texture &tex );
	void drawAtmosphere();
	void select();
	void setData( ci::ipod::PlaylistRef album );
	string getName();

	// TODO: should this be private?
	int mNumTracks;

  private:
	ci::ipod::PlaylistRef mAlbum;
	
};