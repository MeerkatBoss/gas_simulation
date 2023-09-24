/**
 * @file app.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __APP_H
#define __APP_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "simulation/molecule_controller.h"
#include "simulation/scene.h"
#include "ui/scene_view.h"
#include "ui/canvas.h"
#include "ui/widget.h"

class App
{
public:
  static constexpr size_t windowWidth  = 1024;
  static constexpr size_t windowHeight = 720;

  App();
  ~App();

  void run(void);
private:
  sf::Texture m_buttonTexture;
  sf::Texture m_sliderBack;
  sf::Texture m_sliderHandle;

  sf::RenderWindow        m_window;
  ui::Widget*             m_widgetTree;
  sim::Scene              m_scene;
  sim::MoleculeController m_moleculeController;

  void setupUI();
  void setupScene();

  void runMainLoop(void);
};

#endif /* app.h */
