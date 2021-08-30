#include "assets/asset_manager.h"

#include <SDL2/SDL.h>
#include <SDL2_gpu/SDL_gpu.h>

#include "debug/logger.h"

using namespace sita::assets;

Asset_Manager::Asset_Manager(SDL_Renderer* renderer)
	: m_renderer(renderer) {
}

Asset_Manager::~Asset_Manager() {
	clear();
}

void Asset_Manager::loadTexture(const std::string& assetId, const std::string& filepath) {
	SDL_Surface* surface = GPU_LoadSurface(filepath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	m_textures.emplace(assetId, texture);

	Log::info("Asset_Manager::loadTexture - Loaded: {} {}x{}", assetId, surface->w, surface->h);
	SDL_FreeSurface(surface);
}

SDL_Texture* Asset_Manager::getTexture(const std::string& assetId) const {
	return m_textures.at(assetId);
}

void Asset_Manager::unloadTexture(const std::string& assetId) {
	SDL_DestroyTexture(m_textures[assetId]);
	m_textures.erase(assetId);

	Log::info("Asset_Manager::loadTexture - Unloaded: {}", assetId);
}

void Asset_Manager::clear() {
	for (const auto& texture : m_textures) {
		SDL_DestroyTexture(texture.second);
	}
	m_textures.clear();
}
