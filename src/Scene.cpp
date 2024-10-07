#include <Scene.hpp>
void Scene::addObject( Object* object) {
    objects.push_back(object);
}

// Add lights to the scene
void Scene::addLight( Light* light) {
    lights.push_back(light);
}

// Getters for objects and lights
const std::vector<Object*>& Scene::getObjects() const {
    return objects;
}

const std::vector<Light*>& Scene::getLights() const {
    return lights;
}
