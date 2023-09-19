#include "app.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "math/transform.h"
#include "ui/render_window.h"
#include "ui/widget.h"

#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"

App::App()
{
  using math::Vec;
  using math::Transform;

  m_window.create(sf::VideoMode(windowWidth, windowHeight),
                  "Gas simulation",
                  sf::Style::Close);
  setupUI();

  m_scene.createObject<sim::CircleMolecule>(Vec(),
                                            Transform(Vec(100, 200),
                                                      Vec(100, 100)));
  m_scene.createObject<sim::SquareMolecule>(2, Vec(),
                                            Transform(Vec(400, 300),
                                                      Vec(200, 200)));
}

void App::setupUI()
{
  using math::Vec;
  using math::Transform;

  /*
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(App::windowWidth/2,
                                 App::windowHeight/2));
  rectangle.setPosition(sf::Vector2f(App::windowWidth/4,
                                     App::windowHeight/4));
  rectangle.setFillColor(sf::Color(200, 0, 200));
  */

  ui::RenderWindow* canvas =
      new ui::RenderWindow(App::windowWidth, App::windowHeight);

  /*
  sim::Molecule* molecule1 = new sim::CircleMolecule(Vec(),
                                                     Transform(Vec(100, 200),
                                                               Vec(100, 100)));
  sim::Molecule* molecule2 = new sim::SquareMolecule(2, Vec(),
                                                     Transform(Vec(400, 300),
                                                               Vec(200, 200)));

  canvas->renderTexture().clear();
  canvas->renderTexture().draw(rectangle);
  molecule1->draw(*canvas);
  molecule2->draw(*canvas);

  delete molecule1;
  delete molecule2;
  */

  m_canvas     = canvas;
  m_widgetTree = canvas;
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


  while (m_window.isOpen())
  {
    while (m_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        m_window.close();
      }
    }
    if (!m_window.isOpen())
    {
      break;
    }

    m_window.clear();
    m_scene.updateObjects(0);
    m_scene.drawAll(*m_canvas);
    m_widgetTree->draw(m_window,
                       math::Transform(math::Vec(0, 0),
                                       math::Vec(windowWidth, windowHeight)));
    m_window.display();
  }
}
