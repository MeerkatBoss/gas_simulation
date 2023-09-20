#include "app.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "math/transform.h"
#include "simulation/molecule_controller.h"
#include "simulation/scene_object.h"
#include "ui/canvas.h"
#include "ui/widget.h"

#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"

App::App() :
  m_moleculeController(m_scene, 2, math::Point(3, 1), math::Vec(2, 1))
{
  using math::Vec;
  using math::Transform;

  m_window.create(sf::VideoMode(windowWidth, windowHeight),
                  "Gas simulation",
                  sf::Style::Close);
  setupUI();

  /*
  m_scene.createObject<sim::CircleMolecule>(Vec(10, 10),
                                            Transform(Vec(100, 200),
                                                      Vec(100, 100)));
  m_scene.createObject<sim::SquareMolecule>(2, Vec(5, 2),
                                            Transform(Vec(400, 300),
                                                      Vec(200, 200)));
  */
}

void App::setupUI()
{
  using math::Vec;
  using math::Point;
  using math::Transform;

  ui::Canvas* canvas =
      new ui::Canvas(App::windowWidth, App::windowHeight);

  ui::SceneView* scene_view =
      new ui::SceneView(m_scene, canvas, 50, Point(2, 1));

  m_widgetTree = scene_view;
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

  double seconds = 0;

  m_scene.createObject<sim::SquareMolecule>(10, math::Vec(),
                                            math::Transform(
                                              math::Point(6, 3),
                                              math::Vec(3, 3)));
  m_moleculeController.spawnSquare();

  while (m_window.isOpen())
  {
    while (m_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        m_window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed)
      {
        sim::SceneObject* object = m_scene.findObject(1);
        if (object != nullptr)
        {
          object->kill();
        }
      }
    }
    if (!m_window.isOpen())
    {
      break;
    }
    double delta_time = clock.restart().asSeconds();
    seconds += delta_time;

    while (seconds > 1)
    {
      --seconds;
      // m_moleculeController.spawnSquare();
    }

    m_window.clear();
    m_moleculeController.runReactions();
    m_scene.updateObjects(delta_time);

    m_widgetTree->draw(m_window,
                       math::Transform(math::Vec(0, 0),
                                       math::Vec(windowWidth, windowHeight)));
    m_window.display();
  }
}
