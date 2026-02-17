#pragma once

#include "Menu.h"
#include "../Managers/BackupManager.h"

class BackupMenu: public Menu{
  public:
    BackupMenu();

  protected:
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
  private:
    BackupManager _backupManager;
};

