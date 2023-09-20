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
#include "simulation/molecule_controller.h"
#include "simulation/scene.h"
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
  sf::RenderWindow        m_window;
  ui::Widget*             m_widgetTree;
  ui::Canvas*             m_canvas;
  sim::Scene              m_scene;
  sim::MoleculeController m_moleculeController;

  void setupUI();

  void runMainLoop(void);
};

#endif /* app.h */
