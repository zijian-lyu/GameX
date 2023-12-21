#include "GameX/application/application.h"

int main() {
  GameX::ApplicationSettings settings;
  GameX::Application app(settings);
  app.Run();
  return 0;
}
