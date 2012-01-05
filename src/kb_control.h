#pragma once
#include "userconfig.h"
#include <openrave/openrave.h>
#include <osgGA/GUIEventHandler>
#include "openravesupport.h"



typedef RaveRobotKinematicObject::Manipulator::Ptr ManipPtr;


struct IncTransform {
  static btTransform rotX(btTransform t,float s) {
    return t*btTransform(btQuaternion(s,0,0,1),btVector3(0,0,0));
  }
  static btTransform rotY(btTransform t,float s) {
    return t*btTransform(btQuaternion(0,s,0,1),btVector3(0,0,0));
  }
  static btTransform rotZ(btTransform t,float s) {
    return t*btTransform(btQuaternion(0,0,s,1),btVector3(0,0,0));
  }
  static btTransform moveX(btTransform t,float s) {
    return t*btTransform(btQuaternion(0,0,0,1),btVector3(s,0,0));
  }
  static btTransform moveY(btTransform t,float s) {
    return t*btTransform(btQuaternion(0,0,0,1),btVector3(0,s,0));
  }
  static btTransform moveZ(btTransform t,float s) {
    return t*btTransform(btQuaternion(0,0,0,1),btVector3(0,0,s));
  }

};

class GrippersMover : public osgGA::GUIEventHandler {
  ManipPtr m_leftManip;
  ManipPtr m_rightManip;
public:
  GrippersMover(ManipPtr leftManip, ManipPtr rightManip) : 
    m_leftManip(leftManip), m_rightManip(rightManip) {}
  bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
};
