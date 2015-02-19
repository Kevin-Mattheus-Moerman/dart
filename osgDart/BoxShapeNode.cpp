/*
 * Copyright (c) 2011-2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Sehoon Ha <sehoon.ha@gmail.com>,
 *            Jeongseok Lee <jslee02@gmail.com>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#include "osgDart/BoxShapeNode.h"
#include "osgDart/utils.h"

#include "dart/dynamics/BoxShape.h"

namespace osgDart
{

BoxShapeNode::BoxShapeNode(dart::dynamics::BoxShape* shape, EntityNode* _parent)
  : ShapeNode(shape, _parent, this),
    mBoxShape(shape),
    mGeode(nullptr)
{
  initialize();
}

//==============================================================================
void BoxShapeNode::refresh()
{
  mUtilized = true;

  if(mShape->getDataVariance() == dart::dynamics::Shape::STATIC)
    return;

  initialize();
}

//==============================================================================
void BoxShapeNode::initialize()
{
  setMatrix(eigToOsg(mShape->getLocalTransform()));

  if(nullptr == mGeode)
  {
    mGeode = new BoxShapeGeode(mBoxShape, mParent);
    addChild(mGeode);
  }

  mGeode->refresh();
}

//==============================================================================
BoxShapeNode::~BoxShapeNode()
{
  // Do nothing
}

//==============================================================================
BoxShapeGeode::BoxShapeGeode(dart::dynamics::BoxShape* shape, EntityNode* _parent)
  : ShapeNode(shape, _parent, this),
    mBoxShape(shape),
    mDrawable(nullptr)
{

}

//==============================================================================
void BoxShapeGeode::refresh()
{
  if(nullptr == mDrawable)
  {
    mDrawable = new BoxShapeDrawable(mBoxShape);
    addDrawable(mDrawable);
  }

  mDrawable->refresh();
}

//==============================================================================
BoxShapeGeode::~BoxShapeGeode()
{
  // Do nothing
}

//==============================================================================
BoxShapeDrawable::BoxShapeDrawable(dart::dynamics::BoxShape* shape)
  : mBoxShape(shape)
{

}

//==============================================================================
void BoxShapeDrawable::refresh()
{
  const Eigen::Vector3d& d = mBoxShape->getSize();
  osg::ref_ptr<osg::Box> osg_shape = new osg::Box(osg::Vec3(0,0,0),
                                                  d[0], d[1], d[2]);

  setShape(osg_shape);
  const Eigen::Vector3d& c = mBoxShape->getColor();
  setColor(osg::Vec4(c[0], c[1], c[2], 1.0));
}

//==============================================================================
BoxShapeDrawable::~BoxShapeDrawable()
{
  // Do nothing
}

} // namespace osgDart