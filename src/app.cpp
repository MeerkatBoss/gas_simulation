#include "app.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "ui/render_window.h"
#include "ui/widget.h"

static ui::Widget* setupUI();

App::App()
{
  m_window.create(sf::VideoMode(windowWidth, windowHeight),
                  "Gas simulation",
                  sf::Style::Close);
  m_widgetTree = setupUI();
}

static ui::Widget* setupUI()
{
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(500, 300));
  rectangle.setPosition(sf::Vector2f(200, 200));
  rectangle.setFillColor(sf::Color(200, 0, 200));

  ui::RenderWindow* renderWindow = new ui::RenderWindow(
                                          App::windowWidth,
                                          App::windowHeight);
  renderWindow->renderTexture().clear();
  renderWindow->renderTexture().draw(rectangle);

  return renderWindow;
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
    m_widgetTree->draw(m_window);
    m_window.display();
  }
}
