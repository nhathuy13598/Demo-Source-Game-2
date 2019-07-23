#include "GameConfigInfo.h"

#include "rapidjson/filereadstream.h"
#include "rapidjson\document.h"

#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>

using namespace rapidjson;

GameConfigInfo::GameConfigInfo()
{
	// default value
	m_screenWidth = 800;
	m_screenHeight = 600;
	m_fps = 60;
	m_playerMoveSpeed = 300;
	m_beamSpeed = 500;
	m_enemyStopChasingY = 150;
	m_startStagePlayerHP = 10;
	m_playerSize = 70;
	m_enemySize = 60;
	m_bossSize = 5;
	m_bossHP = 20;
	m_bossAtkSpd = 4;
}

GameConfigInfo::~GameConfigInfo()
{
}

GameConfigInfo * GameConfigInfo::ms_Instance = 0;
GameConfigInfo * GameConfigInfo::getInstance()
{
	if (!ms_Instance) {
		ms_Instance = new GameConfigInfo();
	}
	return ms_Instance;
}

void GameConfigInfo::DestroyInstance()
{
	if (ms_Instance) {
		delete ms_Instance;
		ms_Instance = 0;
	}
}

int GameConfigInfo::getScreenWidth()
{
	return m_screenWidth;
}

int GameConfigInfo::getScreenHeight()
{
	return m_screenHeight;
}

int GameConfigInfo::getFPS()
{
	return m_fps;
}

int GameConfigInfo::getPlayerMoveSpeed()
{
	return m_playerMoveSpeed;
}

int GameConfigInfo::getBeamSpeed()
{
	return m_beamSpeed;
}

int GameConfigInfo::getEnemyStopChasingY()
{
	return m_enemyStopChasingY;
}

int GameConfigInfo::getStartStagePlayerHP()
{
	return m_startStagePlayerHP;
}

int GameConfigInfo::getPlayerSize()
{
	return m_playerSize;
}

int GameConfigInfo::getEnemySize()
{
	return m_enemySize;
}

int GameConfigInfo::getBossSize()
{
	return m_bossSize;
}

int GameConfigInfo::getBossHP()
{
	return m_bossHP;
}

int GameConfigInfo::getBossAttackSpeed()
{
	return m_bossAtkSpd;
}

void GameConfigInfo::loadConfig()
{
	FILE* fp;
	fopen_s(&fp, "Resources/Data/config.json", "rb");
	if (fp) {
		char readBuffer[65536];
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		Document document;
		document.ParseStream(is);
		assert(document.IsObject());
		auto obj = document.GetObject();

		if (obj.HasMember("screenWidth")) {
			m_screenWidth = obj["screenWidth"].GetInt();
		}
		if (obj.HasMember("screenHeight")) {
			m_screenHeight = obj["screenHeight"].GetInt();
		}
		if (obj.HasMember("FPS")) {
			m_fps = obj["FPS"].GetInt();
		}
		if (obj.HasMember("playerMoveSpeed")) {
			m_playerMoveSpeed = obj["playerMoveSpeed"].GetInt();
		}
		if (obj.HasMember("beamSpeed")) {
			m_beamSpeed = obj["beamSpeed"].GetInt();
		}
		if (obj.HasMember("enemyStopChasingY")) {
			m_enemyStopChasingY = obj["enemyStopChasingY"].GetInt();
		}
		if (obj.HasMember("startStagePlayerHP")) {
			m_startStagePlayerHP = obj["startStagePlayerHP"].GetInt();
		}
		if (obj.HasMember("playerSize")) {
			m_playerSize = obj["playerSize"].GetInt();
		}
		if (obj.HasMember("enemySize")) {
			m_enemySize = obj["enemySize"].GetInt();
		}
		if (obj.HasMember("bossSize")) {
			m_bossSize = obj["bossSize"].GetInt();
		}
		if (obj.HasMember("bossHP")) {
			m_bossHP = obj["bossHP"].GetInt();
		}
		if (obj.HasMember("bossAtkSpd")) {
			m_bossAtkSpd = obj["bossAtkSpd"].GetInt();
		}

		fclose(fp);
	}
	else {
		Document d;
		d.SetObject();

		d.AddMember("screenWidth", m_screenWidth, d.GetAllocator());
		d.AddMember("screenHeight", m_screenHeight, d.GetAllocator());
		d.AddMember("FPS", m_fps, d.GetAllocator());
		d.AddMember("playerMoveSpeed", m_playerMoveSpeed, d.GetAllocator());
		d.AddMember("beamSpeed", m_beamSpeed, d.GetAllocator());
		d.AddMember("enemyStopChasingY", m_enemyStopChasingY, d.GetAllocator());
		d.AddMember("startStagePlayerHP", m_startStagePlayerHP, d.GetAllocator());
		d.AddMember("playerSize", m_playerSize, d.GetAllocator());
		d.AddMember("enemySize", m_enemySize, d.GetAllocator());
		d.AddMember("bossSize", m_bossSize, d.GetAllocator());
		d.AddMember("bossHP", m_bossHP, d.GetAllocator());
		d.AddMember("bossAtkSpd", m_bossAtkSpd, d.GetAllocator());

		FILE* fp;
		fopen_s(&fp, "Resources/Data/config.json", "wb");
		char writeBuffer[65536];
		FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
		Writer<FileWriteStream> writer(os);
		d.Accept(writer);
		fclose(fp);
	}
}
