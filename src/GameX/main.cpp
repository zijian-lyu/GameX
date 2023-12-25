#include "GameX/application/application.h"

int main() {
  GameX::Base::ApplicationSettings settings;
  GameX::Base::Application app(settings);
  app.Run();
  return 0;
}
