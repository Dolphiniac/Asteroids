#include "Game/TheGame.hpp"
#include "Game/GameObject.hpp"
#include "Game/Asteroid.hpp"
#include "Game/Ship.hpp"
#include "Game/UFO.hpp"
#include "Game/Bullet.hpp"
#include "Game/Number.hpp"
#include "Game/Text.hpp"
#include "Engine/Core/Audio.hpp"
#include "Engine/Input/TheKeyboard.hpp"
#include "Engine/Input/XboxController.hpp"
#include "Engine/Renderer/GLRenderer.hpp"
#include "Engine/Core/Audio.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/EngineSystemManager.hpp"

#include <cstdlib>
#include <ctime>


//-----------------------------------------------------------------------------------------------
TheGame *g_theGame = nullptr;


//-----------------------------------------------------------------------------------------------
TheGame::TheGame()
: m_ship(nullptr)
, m_ufo(nullptr)
, m_points(0)
, m_timeBetweenUFOs(20.f)
, m_timeSinceLastUFO(0.f)
, m_levelAsteroids(4)
, m_laser(The.Audio->CreateOrGetSound("Data/Audio/laser.wav"))
, m_espload(The.Audio->CreateOrGetSound("Data/Audio/espload.wav"))
, m_shipEspload(The.Audio->CreateOrGetSound("Data/Audio/shipespload.wav"))
, m_shakeMagnitude(0.f)
, m_isQuitting(false)
{
	Ship* life;
	for (int i = 1; i <= 3; i++)
	{
		life = new Ship();
		float x = (DEFAULT_RENDER_RADIUS + 25.f) * (float)i - 15.f;
		float y = WINDOW_PHYSICAL_HEIGHT - (DEFAULT_RENDER_RADIUS + 25.f);
		life->SetPosition(Vector2(x, y));
		m_lives.push_back(life);
	}

	Number* digit;
	for (int i = 5; i >= 1; i--)
	{
		digit = new Number();
		float x = WINDOW_PHYSICAL_WIDTH - (digit->GetRenderRadius() + 25.f) * (float)i;
		float y = WINDOW_PHYSICAL_HEIGHT - (DEFAULT_RENDER_RADIUS + 25.f);
		digit->SetPosition(Vector2(x, y));
		m_score.push_back(digit);
	}

	srand(static_cast <unsigned int> (time(NULL)));

	SpawnShip();
	StartLevel();
}


//-----------------------------------------------------------------------------------------------
void TheGame::Update(float deltaSeconds)
{
	The.Renderer->PushView();
	ShakeScreen(deltaSeconds);

	UpdateUFOTimer(deltaSeconds);

	The.Renderer->Clear(BLACK);

	for (auto entityIter = m_entities.begin(); entityIter != m_entities.end();)
	{
		GameObject* go = *entityIter;
		go->Update(deltaSeconds);

		if (go->ShouldDelete())
		{
			m_points += go->GetPoints();
			entityIter++;
			if (go == m_ship)
			{
				delete m_ship;
				m_ship = nullptr;
				LoseLife();
			}
			else if (go == m_ufo)
			{
				delete m_ufo;	//Making sure to call UFO dtor
				m_ufo = nullptr;
			}
			else
			{
				delete go;
			}
			m_entities.erase(go);
			m_asteroids.erase((Asteroid*)go);
			m_playerBullets.erase((Bullet*)go);
			m_enemyBullets.erase((Bullet*)go);
		}
		else
		{
			entityIter++;
		}
	}

	AsteroidCollide();
	ShipBulletCollide();
	UFOBulletCollide();

	if (m_asteroids.empty())
	{
		++m_levelAsteroids;
		StartLevel();
	}

	HandleHotKeys();
}


//-----------------------------------------------------------------------------------------------
void TheGame::AsteroidCollide()
{
	for (Asteroid* asteroid : m_asteroids)
	{
		if (m_ship && m_ship->CollidesWith(asteroid))
		{
			The.Audio->PlaySound(m_shipEspload, .75f);
			SetShakeMagnitude(7.f);
			m_ship->m_isDead = true;
			asteroid->m_isDead = true;
		}

		for (Bullet* bullet : m_playerBullets)
		{
			if (bullet->CollidesWith(asteroid))
			{
				SetShakeMagnitude(2.f);

				The.Audio->PlaySound(m_espload);

				SpawnChildAsteroids(asteroid->GetPosition(), asteroid->GetSize());

				bullet->m_isDead = true;
				asteroid->m_isDead = true;
			}
		}
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::Render() const
{
	for (GameObject* go : m_entities)
	{
		go->Render();
	}
	The.Renderer->PopView();

	RenderGUI();
}


//-----------------------------------------------------------------------------------------------
void TheGame::HandleHotKeys()
{
	if (g_controllerOne->IsConnected())
	{
		XboxRespond();
	}
	KeyboardRespond();
}


//-----------------------------------------------------------------------------------------------
void TheGame::XboxRespond()
{
	if (The.Input->GetButton(VB_START))
	{
		SpawnShip();
	}
	if (The.Input->GetButtonDown(VB_DUP))
	{
		SpawnAsteroid();
	}
	if (The.Input->GetButtonDown(VB_DDOWN))
	{
		DeleteAsteroid();
	}
	if (The.Input->GetButtonDown(VB_DRIGHT))
	{
		SpawnUFO();
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::KeyboardRespond()
{
	if (The.Input->GetKey('P'))
	{
		SpawnShip();
	}
	if (The.Input->GetKeyDown('O'))
	{
		SpawnAsteroid();
	}
	if (The.Input->GetKeyDown('L'))
	{
		DeleteAsteroid();
	}
	if (The.Input->GetKeyDown('K'))
	{
		SpawnUFO();
	}
	if (The.Input->GetKeyDown(0x1b))
	{
		m_isQuitting = true;
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::SpawnShip()
{
	if (m_ship)
	{
		return;
	}

	m_ship = new Ship();
	m_entities.insert(m_ship);
}


//-----------------------------------------------------------------------------------------------
void TheGame::SpawnAsteroid()
{
	Asteroid* asteroid = new Asteroid();
	m_entities.insert(asteroid);
	m_asteroids.insert(asteroid);
}


//-----------------------------------------------------------------------------------------------
void TheGame::SpawnAsteroid(const Vector2& initialPos, AsteroidSize size)
{
	Asteroid* asteroid = new Asteroid(initialPos, size);
	m_entities.insert(asteroid);
	m_asteroids.insert(asteroid);
}


//-----------------------------------------------------------------------------------------------
void TheGame::SpawnChildAsteroids(const Vector2& initialPos, AsteroidSize size)
{
	if (size == SMALL)
	{
		return;
	}
	else
	{
		SpawnAsteroid(initialPos, (AsteroidSize)(size - 1));
		SpawnAsteroid(initialPos, (AsteroidSize)(size - 1));
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::DeleteAsteroid()
{
	if (m_asteroids.empty())
	{
		return;
	}

	Asteroid* asteroid = *(m_asteroids.begin());
	delete asteroid;
	m_entities.erase(asteroid);
	m_asteroids.erase(asteroid);
}


//-----------------------------------------------------------------------------------------------
void TheGame::FirePlayerBullet()
{
	if (!m_ship)
	{
		return;
	}

	Bullet* bullet = new Bullet(m_ship->GetPosition(), m_ship->GetRenderRadius(), m_ship->GetOrientation());
	m_playerBullets.insert(bullet);
	m_entities.insert(bullet);
	The.Audio->PlaySound(m_laser, .5f);
}


//-----------------------------------------------------------------------------------------------
void TheGame::FireEnemyBullet(const Vector2& position)
{
	if (!m_ship)
	{
		return;
	}
	Vector2 displacement = m_ship->GetPosition() - position;
	Bullet* bullet = new Bullet(position, 0.f, atan2f(displacement.y, displacement.x) * RAD2DEG, .75f);
	m_enemyBullets.insert(bullet);
	m_entities.insert(bullet);
	The.Audio->PlaySound(m_laser, .5f);
}


//-----------------------------------------------------------------------------------------------
void TheGame::ShakeScreen(float deltaSeconds)
{
	if (m_shakeMagnitude <= 0.f)
		return;

	float shakex = m_shakeMagnitude * ((float)(rand() % 200 - 100) / (100.f));
	float shakey = m_shakeMagnitude * ((float)(rand() % 200 - 100) / (100.f));

	The.Renderer->TranslateView(Vector2(shakex, shakey));

	m_shakeMagnitude -= 2.f * deltaSeconds;
}


//-----------------------------------------------------------------------------------------------
void TheGame::SetShakeMagnitude(float newMagnitude)
{
	if (newMagnitude > m_shakeMagnitude)
	{
		m_shakeMagnitude = newMagnitude;
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::StartLevel()
{
	for (int i = 0; i < m_levelAsteroids; i++)
	{
		SpawnAsteroid();
	}

	m_timeBetweenUFOs = 20.f - (float)(m_levelAsteroids - 4);
}


//-----------------------------------------------------------------------------------------------
void TheGame::ShipBulletCollide()
{
	if (!m_ship)
	{
		return;
	}

	for (Bullet* bullet : m_enemyBullets)
	{
		if (m_ship->CollidesWith(bullet))
		{
			m_ship->m_isDead = true;
			bullet->m_isDead = true;
			The.Audio->PlaySound(m_shipEspload);
			SetShakeMagnitude(7.f);
		}
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::UFOBulletCollide()
{
	if (!m_ufo)
	{
		return;
	}

	for (Bullet* bullet : m_playerBullets)
	{
		if (m_ufo->CollidesWith(bullet))
		{
			m_ufo->m_isDead = true;
			bullet->m_isDead = true;
			The.Audio->PlaySound(m_espload);
			SetShakeMagnitude(2.f);
		}
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::SpawnUFO()
{
	if (m_ufo)
	{
		return;
	}

	m_ufo = new UFO();
	m_entities.insert(m_ufo);

	m_timeSinceLastUFO = 0.f;
}


//-----------------------------------------------------------------------------------------------
Vector2 TheGame::GetPlayerPosition() const
{
	if (!m_ship)
	{
		return Vector2::Zero;
	}

	return m_ship->GetPosition();
}


//-----------------------------------------------------------------------------------------------
void TheGame::UpdateUFOTimer(float deltaSeconds)
{
	if (m_ufo)
	{
		return;
	}

	m_timeSinceLastUFO += deltaSeconds;
	if (m_timeSinceLastUFO >= m_timeBetweenUFOs)
	{
		SpawnUFO();
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::RenderGUI() const
{
	The.Renderer->SetOrtho(Vector2(0.f, 0.f), Vector2(1600.f, 900.f));
	for (Ship* life : m_lives)
	{
		life->Render();
	}

	UpdateScore();

	for (Number* digit : m_score)
	{
		digit->Render();
	}
}


//-----------------------------------------------------------------------------------------------
void TheGame::LoseLife()
{
	if (m_lives.empty())
	{
		m_isQuitting = true;
		return;
	}

	Ship* lifeToLose = *(m_lives.rbegin());
	delete lifeToLose;
	m_lives.pop_back();
}


//-----------------------------------------------------------------------------------------------
void TheGame::UpdateScore() const
{
	int points = m_points;
	int tenThousands = points / 10000;
	m_score[0]->SetNum(tenThousands);

	points %= 10000;
	int thousands = points / 1000;
	m_score[1]->SetNum(thousands);

	points %= 1000;
	int hundreds = points / 100;
	m_score[2]->SetNum(hundreds);

	points %= 100;
	int tens = points / 10;
	m_score[3]->SetNum(tens);

	points %= 10;
	int ones = points;
	m_score[4]->SetNum(ones);
}
