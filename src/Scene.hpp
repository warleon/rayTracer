#pragma once
#include <vector>

#include <object/Object.hpp>
#include <light/Light.hpp>

class OBJLoader;


class Scene {
private:
    std::vector<Object*> objects;  // List of objects in the scene
    std::vector<Light*> lights;    // List of lights in the scene

public:
    // Constructor
    Scene() = default;

    // Add objects to the scene
    void addObject( Object* object) ;

    // Add lights to the scene
    void addLight( Light* light) ;

    // Getters for objects and lights
    const std::vector<Object*>& getObjects() const ;

    const std::vector<Light*>& getLights() const ;

    // Friend class declaration
    friend class OBJLoader;
};
