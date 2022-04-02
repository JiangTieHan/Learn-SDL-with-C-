#include "textureManager.h"
#include "../Core/engine.h"
#include "../Camera/camera.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load surface SDL: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (!texture)
    {
        SDL_Log("Failed to load texture SDL: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    for (auto& m : m_TextureMap)
    {
        SDL_DestroyTexture(m.second);
    }

    m_TextureMap.clear();
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { 0, 0, width, height };
    Vector2D cam = Camera::GetInstance(SCREEN_WIDTH, SCREEN_HIGHT)->GetPosition() * 0.5;

    SDL_Rect dstRect = { x - cam.X, y - cam.Y, width, height };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { width * frame, height * row, width, height };
    Vector2D cam = Camera::GetInstance(SCREEN_WIDTH, SCREEN_HIGHT)->GetPosition();

    SDL_Rect dstRect = { x - cam.X, y - cam.Y, width, height };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tileSetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {  tileSize * frame, tileSize * row, tileSize, tileSize };
    Vector2D cam = Camera::GetInstance(SCREEN_WIDTH, SCREEN_HIGHT)->GetPosition();

    SDL_Rect dstRect = { x - cam.X, y - cam.Y, tileSize, tileSize };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tileSetID], &srcRect, &dstRect, 0, nullptr, flip);
}
