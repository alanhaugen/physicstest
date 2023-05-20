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
    ground->Add(new Cube(0,-2,0,2,2,2));
    ground->Uniform("colour", glm::vec4(0.607, 0.721, 0.929, 1.0)); // cute pale cerulean

    cube = new Actor();
    cube->Add(new Cube(0,2,0, 1,1,1));
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

    float gravity = 0.098f;
    cube->matrix.Translate(glm::vec3(0.0f, -gravity, 0.0f));
}

void Demo::UpdateAfterPhysics()
{
    if (physics->Collide(cube->collisionBox)) // Collision
    {
        float gravity = 0.098f;
        cube->matrix.Translate(glm::vec3(0.0f, gravity, 0.0f));
    }
}

int main(int argc, char **argv)
{
    Application application(argc, argv);

    application.AddScene(new Demo());

    return application.Exec();
}

