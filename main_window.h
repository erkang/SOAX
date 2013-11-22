#ifndef SOAX_MAINWINDOW_H_
#define SOAX_MAINWINDOW_H_

#include <QMainWindow>
#include "global.h"

class QProgressBar;


namespace soax {

class Multisnake;
class Viewer;

/*
 * SOAX GUI main window.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();

  // Disable right click on the toolbar
  virtual QMenu *createPopupMenu() {return NULL;}

 private slots:
  void OpenImage();
  void SaveAsIsotropicImage();
  void LoadParameters();
  void SaveParameters();
  void LoadSnakes();
  void SaveSnakes();
  void CompareSnakes();
  void CompareAnotherSnakes();
  void LoadJFilamentSnakes();
  void SaveJFilamentSnakes();
  void CloseSession();
  void AboutSOAX();

  void InitializeSnakes();
  void DeformSnakes();
  void DeformSnakesInAction();
  void DeformOneSnake();
  void CutSnakes();
  void GroupSnakes();


 private:
  void CreateActions();
  void CreateFileMenuActions();
  void CreateViewMenuActions();
  void CreateProcessMenuActions();
  void CreateHelpMenuActions();

  void CreateMenus();
  void CreateToolBar();
  void CreateStatusBar();

  void ResetActions();
  QString GetLastDirectory(const std::string &filename);


  QWidget *central_widget_;

  // Actions in File menu
  QAction *open_image_;
  QAction *save_as_isotropic_image_;
  QAction *load_parameters_;
  QAction *save_parameters_;
  QAction *load_snakes_;
  QAction *save_snakes_;
  QAction *load_jfilament_snakes_;
  QAction *save_jfilament_snakes_;
  QAction *compare_snakes_;
  QAction *compare_another_snakes_;
  QAction *close_session_;
  QAction *exit_;

  // Actions in View menu
  QAction *toggle_planes_;
  QAction *toggle_mip_;
  QAction *toggle_orientation_marker_;
  QAction *toggle_corner_text_;
  QAction *toggle_bounding_box_;
  QAction *toggle_cube_axes_;
  QAction *toggle_snakes_;
  QAction *toggle_junctions_;

  // Actions in Process menu
  QAction *initialize_snakes_;
  QAction *deform_snakes_;
  QAction *deform_snakes_in_action_;
  QAction *deform_one_snake_;
  QAction *cut_snakes_;
  QAction *group_snakes_;

  // Actions in Help menu
  QAction *about_soax_;
  QAction *about_qt_;

  // Menus
  QMenu *file_;
  QMenu *view_;
  QMenu *process_;
  QMenu *help_;

  QToolBar *toolbar_;
  QProgressBar *progress_bar_;
  int message_timeout_; // in milliseconds

  // Complete image file path and name
  std::string image_filename_;
  std::string parameter_filename_;
  std::string snake_filename_;
  Multisnake *multisnake_;
  Viewer *viewer_;

  DISALLOW_COPY_AND_ASSIGN(MainWindow);
};

} // namespace soax

#endif // SOAX_MAINWINDOW_H_
