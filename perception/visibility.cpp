#include "rope.h"
#include "utils_perception.h"
#include "clouds/utils_pcl.h"
#include "vector_io.h"
#include "bullet_typedefs.h"
using namespace Eigen;
using namespace pcl;


// todo: we should do a raycast
std::vector<float> calcVisibility(const Eigen::MatrixXf& pts, const Eigen::MatrixXf& depth, const cv::Mat& ropeMask) {
  VectorXf ptDists = pts.rowwise().norm();
  MatrixXi uvs = xyz2uv(pts);
  vector<float> vis(pts.rows(),true);

  for (int iPt=0; iPt<pts.rows(); iPt++) {
    int u = uvs(iPt,0);
    int v = uvs(iPt,1);
    if (u<depth.rows() && v<depth.cols() && u>0 && v>0) {
      vis[iPt] = ropeMask.at<uint8_t>(u,v) || isfinite(depth(u,v)) && (depth(u,v) + .04 > ptDists[iPt]);
    // see it if there's no non-rope pixel in front of it
    }
  }
  cout << vis << endl;
  return vis;
}


vector<btVector3> calcCandPositions(const btVector3& center, float stdev, int nSamples) {
  vector<btVector3> out(nSamples);
  if (nSamples==1)
    out[0] = center;
  else if (nSamples==4) { //todo: use a better basis
    out[0] = center + btVector3(stdev,0,0);
    out[1] = center + btVector3(-stdev,0,0);
    out[2] = center + btVector3(0,stdev,0);
    out[3] = center + btVector3(0,-stdev,0);
  }
  else if (nSamples==6) {
    out[0] = center + btVector3(stdev,0,0);
    out[1] = center + btVector3(-stdev,0,0);
    out[2] = center + btVector3(0,stdev,0);
    out[3] = center + btVector3(0,-stdev,0);
    out[4] = center + btVector3(0,0,stdev);
    out[5] = center + btVector3(0,0,-stdev);
  }
  return out;
}

float calcVisProbability(RigidBodyPtr body, const btVector3& cameraPos, btDynamicsWorld* world, float stdev, int nSamples) {
  vector<btVector3> candPositions = calcCandPositions(body->getCenterOfMassPosition(), stdev, nSamples);
  VectorXf vis(nSamples);
  for (int i=0; i < nSamples; i++) {
    btCollisionWorld::ClosestRayResultCallback rayCallback(cameraPos, candPositions[i]);
    world->rayTest(cameraPos, candPositions[i], rayCallback);
  //btRigidBody* hitBody = btRigidBody::upcast(rayCallback.m_collisionObject);
    btRigidBody* hitBody = dynamic_cast<btRigidBody*>(rayCallback.m_collisionObject);
    vis[i] =  (hitBody==NULL || hitBody == body.get());
  }
  return vis.sum()/nSamples;
}

std::vector<float> calcVisibility(const vector<RigidBodyPtr> bodies, btDynamicsWorld* world, const btVector3& cameraPos, float stdev, int nSamples) {
  int nPts = bodies.size();
  vector<float> vis(nPts);
  for (int i=0; i < nPts; i++)
    vis[i] = calcVisProbability(bodies[i], cameraPos, world, stdev, nSamples);
  return vis;
}


void colorByVisibility(CapsuleRope::Ptr rope, const vector<float>& pVis) {
  assert(rope->children.size() == pVis.size());
  for (int i=0; i<pVis.size(); i++) {
    float p = pVis[i];
    rope->children[i]->setColor(p,p,p,1);
  }
}