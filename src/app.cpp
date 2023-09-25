#include "app.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include "math/transform.h"
#include "simulation/molecule_controller.h"
#include "simulation/scene_object.h"
#include "simulation/wall.h"
#include "ui/canvas.h"
#include "ui/widget.h"
#include "ui/button.h"
#include "ui/slider.h"
#include "ui/widget_group.h"

#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"

class DebugController : public ui::ButtonController, public ui::SliderController
{
public:
  void onClick(size_t) override
  {
    puts("DEBUG: Clicked!");
  }

  void onHold(size_t) override
  {
    puts("DEBUG: Holding...");
  }

  void onRelease(size_t) override
  {
    puts("DEBUG: Released!");
  }

  void onSetVal(double val) override
  {
    printf("DEBUG: Set value %lg\n", m_value);
    m_value = val;
  }

  double getMaxVal() override { return 10; }
  double getMinVal() override { return 2; }
  double getCurVal() override { return m_value; }


private:
  double m_value = 2;
};

static DebugController g_debugController = DebugController();

App::App() :
  m_moleculeController(m_scene, m_circleTexture, m_squareTexture)
{
  using math::Vec;
  using math::Transform;

  m_window.create(sf::VideoMode(windowWidth, windowHeight),
                  "Gas simulation",
                  sf::Style::Close);
  m_buttonTexture.loadFromFile("assets/button.png");
  m_circleButtonTexture.loadFromFile("assets/button_circle.png");
  m_squareButtonTexture.loadFromFile("assets/button_square.png");
  m_sliderBack.loadFromFile("assets/slider_back.png");
  m_sliderHandle.loadFromFile("assets/slider_handle.png");
  m_circleTexture.loadFromFile("assets/circle.png");
  m_squareTexture.loadFromFile("assets/square.png");

  setupScene();
  setupUI();
}

void App::setupScene()
{
  // m_scene.createObject<sim::Wall>(math::Point(3, 13), 20);
  m_scene.createObject<sim::Wall>(math::Point(3, 13), 20);
  m_scene.createObject<sim::Wall>(math::Point(3, -1), 20);
  m_scene.createObject<sim::Wall>(math::Point(8, 6), 20, 90);
  m_scene.createObject<sim::Wall>(math::Point(-2, 6), 20, 90);

  m_moleculeController.setSpawnScale(1);
  m_moleculeController.setSpawnPoint(math::Vec(3, 1));
  m_moleculeController.setSpawnVelocity(math::Vec(0, 4));
  m_moleculeController.setSpread(20);
  m_moleculeController.setSpawnRate(2.3);
}

void App::setupUI()
{
  using math::Vec;
  using math::Point;
  using math::Transform;

  ui::WidgetGroup* root = new ui::WidgetGroup();

  ui::Canvas* canvas =
      new ui::Canvas(App::windowWidth / 2, App::windowHeight,
          Transform(Point(0, 0), Vec(.5, 1)));
  ui::SceneView* scene_view =
      new ui::SceneView(m_scene, canvas, 50, Point(2, 1));

  root->captureWidget(scene_view);

  ui::WidgetGroup* ui_root
    = new ui::WidgetGroup(Transform(
                          Point(.5, 0), Vec(.5, 1)));
  ui::Widget* button1 = new ui::Button(m_moleculeController,
                                       m_circleButtonTexture,
                                       0.5, Point(0, 0));
  m_moleculeController.setCircleButton(button1->getId());

  ui::Widget* button2 = new ui::Button(m_moleculeController,
                                       m_squareButtonTexture,
                                       0.5, Point(0.5, 0));
  m_moleculeController.setSquareButton(button2->getId());

  ui::Widget* slider = new ui::Slider(g_debugController,
                                 m_sliderBack, m_sliderHandle,
                                 1, Point(0, .5));
  ui_root->captureWidget(button1);
  ui_root->captureWidget(button2);
  ui_root->captureWidget(slider);

  root->captureWidget(ui_root);
  m_widgetTree = root;
}

App::~App()
{
  if (m_window.isOpen())
  {
    m_window.close();
  }
  delete m_widgetTree;
}

void App::run()
{
  runMainLoop();
}

void App::runMainLoop()
{
  sf::Event event;
  sf::Clock clock;

  math::Transform root = math::Transform(math::Vec(0, 0),
                                       math::Vec(windowWidth, windowHeight));
  while (m_window.isOpen())
  {
    while (m_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        m_window.close();
      }
      m_widgetTree->handleMouseEvent(
                      ui::MouseEvent::getMouseEvent(m_window, event), root);
    }
    if (!m_window.isOpen())
    {
      break;
    }
    double delta_time = clock.restart().asSeconds();

    /*
    seconds += delta_time;
    while (seconds > 1)
    {
      --seconds;
      m_moleculeController.spawnSquare();
    }
    */

    m_window.clear();
    m_moleculeController.runReactions();
    m_scene.updateObjects(delta_time);

    m_widgetTree->draw(m_window, root);
    m_window.display();
  }
}
