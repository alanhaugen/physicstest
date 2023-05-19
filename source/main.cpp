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
    ground = new Actor();
    ground->Add(new Cube(0,-10,0,50,50,50));
    ground->Uniform("colour", glm::vec4(0.1, 0.9, 0.9, 1.0));

    cube = new Actor();
    cube->Add(new Cube(0,0,0, 10,10,10));
    cube->Uniform("colour", glm::vec4(0.9, 0.9, 0.0, 1.0));

    camera = new Camera(0,0,100);

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
}

void Demo::UpdateAfterPhysics()
{
}

int main(int argc, char **argv)
{
    Application application(argc, argv);

    application.AddScene(new Demo());

    return application.Exec();
}

