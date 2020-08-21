#include "Rocket.h"

Rocket::Rocket(float fuel, float fuelWeight, float fuelUsageRate, glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 color)
    : Sphere(position, velocity, mass, radius, color){

    m_fuelUsageRate = fuelUsageRate;
    m_fuel = fuel;
    m_fuelMass = fuelWeight;
    m_baseMass = mass;
}

void Rocket::fixedUpdate(glm::vec2 gravity, float timeStep){
    propulse();
    m_mass = m_baseMass + (m_fuel * m_fuelMass);
    Sphere::fixedUpdate(gravity, timeStep);
}

void Rocket::propulse(){
    
    applyForce(glm::vec2(0, 150));
    m_fuel -= m_fuelUsageRate;
}
