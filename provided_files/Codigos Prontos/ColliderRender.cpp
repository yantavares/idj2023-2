
// Adicione o trecho abaixo no começo do seu Collider.cpp,
// logo após os seus includes e antes de qualquer função.

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
