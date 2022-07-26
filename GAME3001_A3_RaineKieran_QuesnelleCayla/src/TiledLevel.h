#pragma once
#ifndef __TILED_LEVEL__
#define __TILED_LEVEL__

#include <map>
#include <vector>
#include <string>
#include "DisplayObject.h"
#include "Tile.h"

class TiledLevel final : public DisplayObject
{
public:
	TiledLevel(const std::string& levelMap, const std::string& tileData, const std::string& texturePath,
		const std::string& textureKey,	const SDL_Point tileSrcSize, const SDL_FPoint tileDstSize,
		const unsigned short rows = 15, const unsigned short cols = 20,
		const bool hasNavigation = false, const bool isRendered = true);
	~TiledLevel() override;

	// DisplayObject Life-Cycle Functions
	void Draw() override;
	void Update() override;
	void Clean() override;

	// Other
	void SetLabelsEnabled(bool state);
	[[nodiscard]] Tile* GetTile(unsigned col, unsigned row) const;
	[[nodiscard]] Tile* GetTile(glm::vec2 pos) const;
	[[nodiscard]] std::vector<Tile*>& GetLevel();
	[[nodiscard]] std::vector<Tile*>& GetImpassables();
	[[nodiscard]] std::vector<Tile*>& GetHazards();
	[[nodiscard]] bool HasNavigation() const;

private:
	bool m_hasNavigation, m_renderTiles;
	std::string m_textureKey;
	int m_rows, m_cols;
	std::map<char, Tile*> m_tiles; // Map of prototype Tile objects.
	std::vector<Tile*> m_level; // 1D vector.
	std::vector<Tile*> m_impassables;
	std::vector<Tile*> m_hazards;

	void LinkTiles();
};

#endif /* defined (__TILED_LEVEL__) */