//
// Created by Brandon Boudreaux on 3/25/23.
//

#include "Object.h"

namespace PhyG{
    void Object::SetPos(glm::vec3 pos){
        position = pos;
    }

    glm::vec3 Object::GetPos(){
        return position;
    }

    void Object::SetRot(glm::vec3 rot){
        rotation = rot;
    }

    glm::vec3 Object::GetRot(){
        return rotation;
    }

    void Object::SetName(const char * n){
        name = n;
    }

    const char* Object::GetName(){
        return name;
    }
}