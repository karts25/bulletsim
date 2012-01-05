#include "simplescene.h"
#include "userconfig.h"
#include "kb_control.h"
#include "util.h"
#include <openrave/openrave.h>

struct CustomScene : public Scene {
  void run() {
    //setSyncTime(true);
    viewer.addEventHandler(new GrippersMover(pr2Left, pr2Right));
    startViewer();
    startFixedTimestepLoop(CFG.bullet.dt);
  }
};

int main(int argc, char *argv[]) {
  Config::read(argc, argv);
  CFG.scene.scale = 1.;
  CFG.viewer.cameraHomePosition = btVector3(100, 0, 100);
  CFG.bullet.dt = 0.01;
  CFG.bullet.internalTimeStep = 0.01;
  CFG.bullet.maxSubSteps = 0;
  CFG.scene.enableRobotCollision = false;

  CustomScene().run();
  return 0;
}
