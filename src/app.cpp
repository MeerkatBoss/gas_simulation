#include "app.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include "math/transform.h"
#include "simulation/molecule_controller.h"
#include "simulation/reactions/circle_absorb_reaction.h"
#include "simulation/reactions/square_split_reaction.h"
#include "simulation/scene_object.h"
#include "simulation/wall.h"
#include "simulation/reactions/circle_fuse_reaction.h"
#include "ui/canvas.h"
#include "ui/plot_view.h"
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
  m_scene.createObject<sim::Wall>(math::Point(3, 13), 20);
  m_scene.createObject<sim::Wall>(math::Point(3, -1), 20);
  m_scene.createObject<sim::Wall>(math::Point(8, 6), 20, 90);
  m_scene.createObject<sim::Wall>(math::Point(-2, 6), 20, 90);

  m_moleculeController.setSpawnScale(1);
  m_moleculeController.setSpawnPoint(math::Vec(3, 0.5));
  m_moleculeController.setSpawnVelocity(math::Vec(0, 4));
  m_moleculeController.setSpread(20);
  m_moleculeController.setSpawnRate(2.3);

  m_moleculeController.addReactionTemplate(
      new sim::CircleFuseReactionTemplate(m_moleculeController));
  m_moleculeController.addReactionTemplate(
      new sim::CircleAbsorbReactionTemplate(m_moleculeController));
  m_moleculeController.addReactionTemplate(
      new sim::SquareSplitReactionTemplate(m_moleculeController));

  sim::Wall* piston = m_scene.createObject<sim::Wall>(math::Point(3, 6), 20);
  m_pistonController.setPiston(piston);
  m_pistonController.setPistonRange(math::Point(3, 2), math::Point(3, 10));
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

  ui::WidgetGroup* spawn_controls =
      new ui::WidgetGroup(Transform(Point(.6, .5), Vec(.4, .5)));
  ui::Widget* button1 = new ui::Button(m_moleculeController,
                                       m_circleButtonTexture,
                                       .35, Point(.1, 0));
  m_moleculeController.setCircleButton(button1->getId());

  ui::Widget* button2 = new ui::Button(m_moleculeController,
                                       m_squareButtonTexture,
                                       .35, Point(.55, 0));
  m_moleculeController.setSquareButton(button2->getId());

  ui::Widget* slider = new ui::Slider(m_moleculeController,
                                 m_sliderBack, m_sliderHandle,
                                 .8, Point(.1, .5));

  spawn_controls->captureWidget(button1);
  spawn_controls->captureWidget(button2);
  spawn_controls->captureWidget(slider);

  ui::Widget* piston = new ui::Slider(m_pistonController,
                                 m_sliderBack, m_sliderHandle,
                                 0.8, Point(.6, .9), 180);

  ui::Canvas* plot_canvas =
    new ui::Canvas(size_t(App::windowWidth*0.8) , App::windowHeight,
          Transform(Point(.6, 0), Vec(.4, .5)));
  ui::PlotView* plot = new ui::PlotView(plot_canvas, .2, .5);
  m_plotView = plot;

  root->captureWidget(spawn_controls);
  root->captureWidget(piston);
  root->captureWidget(plot);
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

    m_plotView->addPoint(delta_time, double(rand()) / RAND_MAX);
    m_window.clear(sf::Color(128, 128, 128));
    m_moleculeController.runReactions();
    m_scene.updateObjects(delta_time);

    m_widgetTree->draw(m_window, root);
    m_window.display();
  }
}
