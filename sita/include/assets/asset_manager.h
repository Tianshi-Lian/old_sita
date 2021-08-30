#pragma once

#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;

namespace sita::assets {

	class Asset_Manager {
	public:
		Asset_Manager(SDL_Renderer* renderer);
		~Asset_Manager();

		void loadTexture(const std::string& assetId, const std::string& filepath);
		SDL_Texture* getTexture(const std::string& assetId) const;
		void unloadTexture(const std::string& assetId);

		void clear();

	private:
		SDL_Renderer* m_renderer;

		std::unordered_map<std::string, SDL_Texture*> m_textures;
	};

}
