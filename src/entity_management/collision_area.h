#ifndef COLLISION_AREA_H
#define COLLISION_AREA_H

class CollisionArea {
    float x_min, x_max;
    float y_min, y_max;

    bool isMovingTowards(glm::vec2 test_point, glm::vec2 object_position, glm::vec2 object_velocity) {
        glm::vec2 to_point = test_point - object_position; //a vector going from your obect to the point
        return glm::dot(to_point, object_velocity) > 0;
    }

public:
    CollisionArea() {

    }

    CollisionArea(float x_min_rel, float x_max_rel, float y_min_rel, float y_max_rel, glm::vec2 position) {
        this->x_min = x_min_rel + position.x;
        this->x_max = x_max_rel + position.x;
        this->y_min = y_min_rel + position.y;
        this->y_max = y_max_rel + position.y;
    }

    void offsetBy(glm::vec2 offset) {
        this->x_min += offset.x;
        this->x_max += offset.x;
        this->y_min += offset.y;
        this->y_max += offset.y;
    }
    
    // return (xmax1 >= xmin2) && (xmax2 >= xmin1);
    bool intersects(CollisionArea& testing_area) {
        return (
            this->x_min < testing_area.x_max
            && this->x_max > testing_area.x_min
            && this->y_min < testing_area.y_max
            && this->y_max > testing_area.y_min
            );
    }

    glm::vec2 resolveGoingInto(CollisionArea colliding_area, glm::vec2 desired_velocity) {
        glm::vec2 this_center = { (this->x_min + this->x_max)/2, (this->y_min + this->y_max)/2 };
        glm::vec2 colliding_center = { (colliding_area.x_min + colliding_area.x_max)/2, (colliding_area.y_min + colliding_area.y_max)/2 };

        if (isMovingTowards(colliding_center, this_center, desired_velocity)) {
            glm::vec2 pos_difference = colliding_center - this_center;

            if (abs(pos_difference.x) > abs(pos_difference.y)) {
                return { 0.0f, desired_velocity.y };
            } else {
                return { desired_velocity.x, 0.0f };
            }
        } else {
            return desired_velocity;
        }
    }

    void print() {
        std::cout << "x_min " << x_min << " x_max " << x_max << " y_min " << y_min << " y_max " << y_max << "\n";
    }
};

#endif