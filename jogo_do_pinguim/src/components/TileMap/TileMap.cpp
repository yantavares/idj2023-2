#include "TileMap.hpp"
#include "../../game/Camera/Camera.hpp"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated)
{
    Load(file);
    this->tileSet = tileSet;

    associated.box = Rect(0, 0, tileSet->GetColumns() * tileSet->GetTileWidth(), tileSet->GetRows() * tileSet->GetTileHeight());
}

TileMap::~TileMap()
{
}

void TileMap::Load(string file)
{
    ifstream fin;
    int tmp;
    char discard;
    fin.open(file);
    fin >> mapWidth >> discard >> mapHeight >> discard >> mapDepth;
    for (int i = 0; i < mapDepth; i++)
    {
        fin >> discard;
        for (int j = 0; j < mapHeight; j++)
        {
            for (int k = 0; k < mapWidth; k++)
            {
                fin >> tmp >> discard;
                tmp--;
                tileMatrix.push_back(tmp);
            }
        }
    }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z)
{
    int tmp;
    tmp = z * mapWidth * mapHeight + y * mapWidth + x;
    return tileMatrix[tmp];
}

void TileMap::Render()
{
    for (int layer = 0; layer < mapDepth; layer++)
    {
        RenderLayer(layer, Camera::pos.x, Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            tileSet->RenderTile(At(j, i, layer), (j * tileSet->GetTileWidth() - cameraX * (layer + 1)), (i * tileSet->GetTileHeight() - cameraY * (layer + 1)));
        }
    }
}

void TileMap::Update(float dt) {}

bool TileMap::Is(string type)
{
    return type == "TileMap" ? true : false;
}