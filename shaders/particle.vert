#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVel;
layout (location = 2) in float aSpawnTime;

out vec4 particleColor;

uniform mat4 camMatrix;
uniform float time;

const float lifeSpan = 3.0;

void main() {
    float age = time - aSpawnTime;
    if (age > lifeSpan) {
        gl_Position = vec4(0.0, -9999.0, 0.0, 1.0);
        particleColor = vec4(0.0,0.0,1.0,0.0);
        return;
    }

    vec3 animatedPos = aPos + aVel * age;
    gl_Position = camMatrix * vec4(animatedPos, 1.0);

    float alpha = 1.0 - (age / lifeSpan);

    particleColor = vec4(0.25, 0.41, 0.88, alpha);
}