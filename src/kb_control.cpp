#include "kb_control.h"
#include <iostream>
using namespace std;

#define KEY_CONTROL_LEFT(key, incfunc, delta)				\
  case key:								\
  m_leftManip->moveByIK(IncTransform::incfunc(m_leftManip->getTransform(),delta)); \
  cout << "hi" << endl;\
  break
#define KEY_CONTROL_RIGHT(key, incfunc, delta)				\
  case key:								\
  m_rightManip->moveByIK(IncTransform::incfunc(m_rightManip->getTransform(),delta)); \
  cout << "hi" << endl;\
  break

bool GrippersMover::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&) {
  switch (ea.getEventType()) {
  case osgGA::GUIEventAdapter::KEYDOWN:
    switch (ea.getKey()) {
      KEY_CONTROL_LEFT('q',rotX,.01);
      KEY_CONTROL_LEFT('Q',rotX,-.01);
      KEY_CONTROL_LEFT('w',rotY,.01);
      KEY_CONTROL_LEFT('W',rotY,-.01);
      KEY_CONTROL_LEFT('e',rotZ,.01);
      KEY_CONTROL_LEFT('E',rotZ,-.01);
      KEY_CONTROL_LEFT('a',moveX,.01);
      KEY_CONTROL_LEFT('A',moveX,-.01);
      KEY_CONTROL_LEFT('s',moveY,.01);
      KEY_CONTROL_LEFT('S',moveY,-.01);
      KEY_CONTROL_LEFT('d',moveZ,.01);
      KEY_CONTROL_LEFT('D',moveZ,-.01);

      KEY_CONTROL_RIGHT('p',rotX,.01);
      KEY_CONTROL_RIGHT('P',rotX,-.01);
      KEY_CONTROL_RIGHT('o',rotY,.01);
      KEY_CONTROL_RIGHT('O',rotY,-.01);
      KEY_CONTROL_RIGHT('i',rotZ,.01);
      KEY_CONTROL_RIGHT('I',rotZ,-.01);
      KEY_CONTROL_RIGHT('l',moveX,.01);
      KEY_CONTROL_RIGHT('L',moveX,-.01);
      KEY_CONTROL_RIGHT('k',moveY,.01);
      KEY_CONTROL_RIGHT('K',moveY,-.01);
      KEY_CONTROL_RIGHT('j',moveZ,.01);
      KEY_CONTROL_RIGHT('J',moveZ,-.01);

    }
  }  
  return false;

}
#undef KEY_CONTROL_LEFT
#undef KEY_CONTROL_RIGHT
