#include <core/application.h>
#include <core/components/cube.h>
#include <core/components/fpscamera.h>
#include <core/components/fpscounter.h>
#include <core/x-platform/scene.h>

class Demo : public IScene
{
private:
    Actor  *ground;
    Actor  *cube;
    Camera *camera;

    FPSCamera *fpsCamera;
    FPSCounter *fpsCounter;

    int dir;
    float speed;

public:
    Demo();
    ~Demo();

    void Init();
    void Update();
    void UpdateAfterPhysics();
};

Demo::Demo()
{
}

Demo::~Demo()
{
}

void Demo::Init()
{
    // https://www.schemecolor.com/soft-and-cute.php
    ground = new Actor();
    ground->Add(new Cube(0,0,0, 2,2,2));
    ground->matrix.Translate(glm::vec3(0,-2,0));
    ground->collisionBox->dimensions *= 2.0f; //Translate(glm::vec3(0,2,0));
    ground->Uniform("colour", glm::vec4(0.607, 0.721, 0.929, 1.0)); // cute pale cerulean

    cube = new Actor();
    cube->Add(new Cube(0,0,0, 1,1,1));
    cube->matrix.Translate(glm::vec3(0,2,0));
    cube->Uniform("colour", glm::vec4(0.996, 0.776, 0.875, 1.0)); // cute classic rose

    camera = new Camera(0,0,10);

    fpsCamera = new FPSCamera(camera);
    fpsCounter = new FPSCounter();

    components.Add(ground);
    components.Add(cube);
    components.Add(camera);
    components.Add(fpsCamera);
    components.Add(fpsCounter);
}

void Demo::Update()
{
    glm::vec3 lightPos(50, 100,50);
    ground->Uniform("u_lightPosition", static_cast<glm::vec3>(lightPos));
    ground->Uniform("u_cameraPosition", static_cast<glm::vec3>(camera->position));
    cube->Uniform("u_lightPosition", static_cast<glm::vec3>(lightPos));
    cube->Uniform("u_cameraPosition", static_cast<glm::vec3>(camera->position));

    speed = 0.3f;
    if (input.Held(input.Key.A))
    {
        cube->matrix.Translate(glm::vec3(-speed, 0.0f, 0.0f));
        dir = 0;
    }
    else if (input.Held(input.Key.D))
    {
        cube->matrix.Translate(glm::vec3(+speed, 0.0f, 0.0f));
        dir = 1;
    }
    else if (input.Held(input.Key.W))
    {
        cube->matrix.Translate(glm::vec3(0.0f, +speed, 0.0f));
        dir = 2;
    }
    else if (input.Held(input.Key.S))
    {
        cube->matrix.Translate(glm::vec3(0.0f, -speed, 0.0f));
        dir = 3;
    }
    else if (input.Held(input.Key.F))
    {
        cube->matrix.Translate(glm::vec3(0.0f, 0.0f, +speed));
        dir = 4;
    }
    else if (input.Held(input.Key.R))
    {
        cube->matrix.Translate(glm::vec3(0.0f, 0.0f, -speed));
        dir = 5;
    }
}

void Demo::UpdateAfterPhysics()
{
    if (physics->Collide(cube->collisionBox)) // Collision
    {
        if (dir == 0)
        {
            cube->matrix.Translate(glm::vec3(+speed, 0.0f, 0.0f));
        }
        else if (dir == 1)
        {
            cube->matrix.Translate(glm::vec3(-speed, 0.0f, 0.0f));
        }
        else if (dir == 2)
        {
            cube->matrix.Translate(glm::vec3(0.0f, -speed, 0.0f));
        }
        else if (dir == 3)
        {
            cube->matrix.Translate(glm::vec3(0.0f, +speed, 0.0f));
        }
        else if (dir == 4)
        {
            cube->matrix.Translate(glm::vec3(0.0f, 0.0f, -speed));
        }
        else if (dir == 5)
        {
            cube->matrix.Translate(glm::vec3(0.0f, 0.0f, +speed));
        }
    }
}

int main(int argc, char **argv)
{
    Application application(argc, argv);

    application.AddScene(new Demo());

    return application.Exec();
}

