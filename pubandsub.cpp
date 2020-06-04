#include "pubandsub.h"

Robots_msg PublishAndSubscribe::FindClosest(double x, double y){

    Robots_msg result;
    result.distance = -1;
            
    for (size_t i=0; i<landmarks_.size(); i++){
        const Landmark& landmark = landmarks_[i];
        double xd = landmark.x - x;
        double yd = landmark.y - y;
        double distance = sqrt(xd*xd + yd*yd);

        if (result.distance < 0 || distance < result.distance){
            result.name = landmark.name;
            result.distance = distance;
        }
    }
    return result;
}

void PublishAndSubscribe::InitLandmarks(){
    landmarks_.push_back(Landmark("Cubo", 0.31, -0.99));
    landmarks_.push_back(Landmark("Container", 0.11, -2.42));
    landmarks_.push_back(Landmark("Cilindro", -1.14, -2.88));
    landmarks_.push_back(Landmark("Barreira", -2.59, -0.83));
    landmarks_.push_back(Landmark("Estante", -0.09, 0.53));
}

