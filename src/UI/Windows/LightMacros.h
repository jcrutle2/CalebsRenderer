//
// Created by Caleb Rutledge on 2/24/24.
//

#ifndef CALEBSRENDERER_LIGHT_MACROS_H
#define CALEBSRENDERER_LIGHT_MACROS_H

#endif //CALEBSRENDERER_LIGHT_MACROS_H

#define DIRECTION_LIGHT_WINDOW(li) {                                                    \
    glm::vec3 direction = li.getDirection();                                            \
    glm::vec3 ambient = li.getAmbient();                                                \
    glm::vec3 specular = li.getSpecular();                                              \
    glm::vec3 diffuse = li.getDiffuse();                                                \
                                                                                        \
    if (ImGui::InputFloat3("Direction", &direction.x)) li.setDirection(direction);      \
    if (ImGui::InputFloat3("Ambient", &ambient.x)) li.setAmbient(ambient);              \
    if (ImGui::InputFloat3("Specular", &specular.x)) li.setSpecular(specular);           \
    if (ImGui::InputFloat3("Diffuse", &diffuse.x)) li.setDiffuse(diffuse);              \
}

#define POINT_LIGHT_WINDOW(li) {                                                            \
    glm::vec3 position = li.getPosition();                                                  \
    glm::vec3 ambient = li.getAmbient();                                                    \
    glm::vec3 specular = li.getSpecular();                                                  \
    glm::vec3 diffuse = li.getDiffuse();                                                    \
    float constant = li.getConstant();                                                      \
    float linear = li.getLinear();                                                          \
    float quadratic = li.getQuadratic();                                                    \
                                                                                            \
    if (ImGui::InputFloat3("Position", &position.x)) li.setPosition(position);              \
    if (ImGui::InputFloat3("Ambient", &ambient.x)) li.setAmbient(ambient);                  \
    if (ImGui::InputFloat3("Specular", &specular.x)) li.setSpecular(specular);              \
    if (ImGui::InputFloat3("Diffuse", &diffuse.x)) li.setDiffuse(diffuse);                  \
    if (ImGui::InputFloat("Constant Falloff", &constant)) li.setConstant(constant);         \
    if (ImGui::InputFloat("Linear Falloff", &linear)) li.setLinear(linear);                 \
    if (ImGui::InputFloat("Quadratic Falloff", &quadratic)) li.setQuadratic(quadratic);     \
}

