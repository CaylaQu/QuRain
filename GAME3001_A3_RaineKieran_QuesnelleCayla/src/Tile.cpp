#include "Tile.h"
#include "TextureManager.h"
#include "Util.h"
#include "PathNode.h"
#include <sstream>
#include <iomanip>

Tile::Tile(SDL_FRect dst, TileType type) : m_src({0,0,0,0}), m_dst(dst), 
	m_type(type), m_status(TileStatus::NONE), m_health(0), m_cost(0),
	m_costLabel(nullptr), m_statusLabel(nullptr), m_labelsEnabled(false),
	m_node(nullptr)
{
	SetWidth(static_cast<int>(m_dst.w));
	SetHeight(static_cast<int>(m_dst.h));
}

Tile::~Tile()
{
	delete m_costLabel;
	m_costLabel = nullptr;
	delete m_statusLabel;
	m_statusLabel = nullptr;
	delete m_node;
	m_node = nullptr;
}

void Tile::Draw()
{
	TextureManager::Instance().Draw(m_textureKey, m_src, m_dst);
}

void Tile::DrawNavigation()
{
	if (m_node != nullptr) // Don't draw connections on a null PathNode.
	{
		for (const auto connection : m_node->GetConnections())
		{
			auto offset = glm::vec2(GetWidth() / 2, GetHeight() / 2);
			Util::DrawLine(connection->GetFromNode()->GetTile()->GetTransform()->position + offset,
				connection->GetToNode()->GetTile()->GetTransform()->position + offset,
				glm::vec4(0,0,0,1));
		}
	}

	m_costLabel->Draw();
	m_statusLabel->Draw();

	switch (m_type)
	{
	case TileType::IMPASSABLE:
		Util::DrawRect(GetTransform()->position, GetWidth(), GetHeight(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	case TileType::HAZARD:
		Util::DrawRect(GetTransform()->position, GetWidth(), GetHeight(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		Util::DrawRect(GetTransform()->position, GetWidth(), GetHeight());
		break;
	}
	
}

void Tile::Update()
{

}

void Tile::Clean()
{
	// Empty for now. Uses destructor.
}

TileType Tile::GetTileType() const
{
	return m_type;
}

void Tile::SetTileType(TileType type)
{
	m_type = type;
}

TileStatus Tile::GetTileStatus() const
{
	return m_status;
}

void Tile::SetTileStatus(TileStatus status)
{
	m_status = status;
	switch (m_status)
	{
	case TileStatus::UNVISITED:
		m_statusLabel->SetText("=");
		break;
	case TileStatus::OPEN:
		m_statusLabel->SetText("O");
		break;
	case TileStatus::CLOSED:
		m_statusLabel->SetText("C");
		break;
	case TileStatus::GOAL:
		m_statusLabel->SetText("G");
		break;
	case TileStatus::START:
		m_statusLabel->SetText("S");
		break;
	default:
		m_statusLabel->SetText(" ");
		break;
	}
}

unsigned short Tile::GetTileHealth() const
{
	return m_health;
}

void Tile::SetTileHealth(int health)
{
	m_health = health;
}

float Tile::GetTileCost() const
{
	return m_cost;
}

void Tile::SetTileCost(float cost)
{
	m_cost = cost;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << m_cost;
	const std::string cost_string = stream.str();
	m_costLabel->SetText(cost_string);
}

void Tile::SetDrawData(SDL_Rect src, const std::string& textureKey)
{
	m_src = src;
	m_textureKey = textureKey;
}

SDL_Rect Tile::GetSrc() const
{
	return m_src;
}

const std::string& Tile::GetTextureKey() const
{
	return m_textureKey;
}

PathNode* Tile::GetNode() const
{
	return m_node;
}

void Tile::AddNode()
{
	m_node = new PathNode(this);
}

void Tile::AddLabels()
{
	// Cost label.
	auto offset = glm::vec2(m_dst.w * 0.5f, m_dst.h * 0.5f);
	m_costLabel = new Label(" ", "Consolas", 12);
	m_costLabel->GetTransform()->position = GetTransform()->position + offset + glm::vec2(0.0f, -6.0f);
	m_costLabel->SetEnabled(false);

	// Status label.
	offset = glm::vec2(m_dst.w * 0.25f, m_dst.h * 0.6f);
	m_statusLabel = new Label(" ", "Consolas", 12, {255,255,255,255});
	m_statusLabel->GetTransform()->position = GetTransform()->position + offset + glm::vec2(0.0f, 6.0f);
	m_statusLabel->SetEnabled(false);
}

bool Tile::GetLabelsEnabled() const
{
	return m_labelsEnabled;
}

void Tile::SetLabelsEnabled(bool state)
{
	m_labelsEnabled = state;
	m_costLabel->SetEnabled(m_labelsEnabled);
	m_statusLabel->SetEnabled(m_labelsEnabled);
}

Tile* Tile::Clone() const
{
	return new Tile(m_dst, m_type);
}

void Tile::SetPos(float col, float row, float sizeX, float sizeY)
{
	this->GetTransform()->position = glm::vec2(col * sizeX, row * sizeY);
	m_dst.x = col * sizeX;
	m_dst.y = row * sizeY;
}