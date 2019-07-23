#include "SharedVariables.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson\document.h"

#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>

TTF_Font *g_font;
int g_CurrentFPS;

using namespace rapidjson;

SharedVariables::SharedVariables()
{
	m_texturePath = new std::string(TEXTURES_PATH);

	TTF_Init();
	m_font = TTF_OpenFont(FONT_PATH, 100);
	g_font = m_font;
}

SharedVariables::~SharedVariables()
{
	delete m_texturePath;
	TTF_CloseFont(m_font);
	if (m_enemyInfos) {
		for (auto e : *m_enemyInfos) {
			delete e;
		}
		delete(m_enemyInfos);
	}
	if (m_stageInfos) {
		for (auto s : *m_stageInfos) {
			delete s;
		}
		delete(m_stageInfos);
	}

	if (m_enemyGroups) {
		for (auto eg : *m_enemyGroups) {
			delete eg;
		}
		delete(m_enemyGroups);
	}

	if (m_playerLevelInfos) {
		for (auto lv : *m_playerLevelInfos) {
			delete lv;
		}
		delete(m_playerLevelInfos);
	}
}

SharedVariables * SharedVariables::ms_Instance = 0;
SharedVariables * SharedVariables::getInstance()
{
	if (!ms_Instance) {
		ms_Instance = new SharedVariables();
	}
	return ms_Instance;
}

void SharedVariables::DestroyInstance() {
	if (ms_Instance) {
		delete ms_Instance;
		ms_Instance = 0;
	}
}

const std::string * SharedVariables::getTexturePath()
{
	return m_texturePath;
}

TTF_Font * SharedVariables::getFont()
{
	return m_font;
}

void SharedVariables::load()
{
	loadEnemyInfos();
	loadEnemyGroups();
	loadStageInfos(); 
	loadPlayerLevelInfo();
}

EnemyInfo * SharedVariables::getEnemyInfoAtLevel(int lvl)
{
	if (lvl < 1) {
		lvl = 1;
	}
	if (lvl > m_enemyInfos->size()) {
		lvl = m_enemyInfos->size();
	}
	EnemyInfo * result = m_enemyInfos->at(lvl - 1);
	if (result->getLevel() != lvl) {
		SDL_Log("wrong enemy lvl %d", result->getLevel());
		for (auto eInfo : *m_enemyInfos) {
			if (eInfo->getLevel() == lvl) {
				result = eInfo;
				break;
			}
		}
	}
	return result;
}

StageInfo * SharedVariables::getStageInfoAt(int stage)
{
	if (stage < 1) {
		stage = 1;
	}
	if (stage > m_stageInfos->size()) {
		stage = m_stageInfos->size();
	}
	StageInfo *result = m_stageInfos->at(stage - 1);
	if (result->getStageNumber() != stage) {
		SDL_Log("wrong stage %d", result->getStageNumber());
		for (auto sInfo : *m_stageInfos) {
			if (sInfo->getStageNumber() == stage) {
				result = sInfo;
				break;
			}
		}
	}
	return result;
}

EnemyGroupInfo * SharedVariables::getRandomGroup()
{
	int randomIndex = rand() % m_enemyGroups->size();
	return m_enemyGroups->at(randomIndex);
}

void SharedVariables::calcFPS(float dt)
{
	g_CurrentFPS = 1.f / dt;
	if (g_CurrentFPS == 0) {
		g_CurrentFPS = 1;
	}
}

void SharedVariables::loadGame(int & stage, int & playerLv, int & score)
{
	FILE* fp;
 	fopen_s(&fp, "saveGame.json", "rb");
	if (fp) {
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));


		rapidjson::Document document;
		document.ParseStream(is);
		assert(document.IsObject());
		auto obj = document.GetObject();

		if (obj.HasMember("stage")) {
			stage = obj["stage"].GetInt();
		}
		else {
			stage = 1;
		}

		if (obj.HasMember("pLevel")) {
			playerLv = obj["pLevel"].GetInt();
		}
		else {
			playerLv = 1;
		}

		if (obj.HasMember("score")) {
			score = obj["score"].GetInt();
		}
		else {
			score = 0;
		}

		fclose(fp);
	}
	else {
		stage = 1;
		saveGame(stage, playerLv, score);
	}
}

void SharedVariables::saveGame(int stage, int playerLv, int score)
{
	Document d;
	d.SetObject();
	d.AddMember("stage", stage, d.GetAllocator());
	d.AddMember("pLevel", playerLv, d.GetAllocator());
	d.AddMember("score", score, d.GetAllocator());

	FILE* fp;
	fopen_s(&fp, "saveGame.json", "wb");
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	d.Accept(writer);
	fclose(fp);
}

void SharedVariables::loadEnemyInfos()
{
	if (!m_enemyInfos) {
		FILE* fp;
		fopen_s(&fp, "Resources/Data/Enemy.json", "rb");

		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));


		rapidjson::Document document;
		document.ParseStream(is);
		assert(document.IsArray());
		auto arr = document.GetArray();

		m_enemyInfos = new std::vector<EnemyInfo*>;

		for (auto itr = arr.Begin(); itr != arr.End(); ++itr) {
			assert(itr->IsObject());
			auto obj = itr->GetObject();
			assert(obj.HasMember("level"));
			int level = obj["level"].GetInt();
			assert(obj.HasMember("hp"));
			int hp = obj["hp"].GetInt();
			assert(obj.HasMember("ms"));
			int ms = obj["ms"].GetInt();
			assert(obj.HasMember("as"));
			int as = obj["as"].GetInt();

			assert(obj.HasMember("res"));
			auto res = obj["res"].GetArray();
			std::vector<std::string *> *resNames = new std::vector<std::string *>;
			for (auto resItr = res.Begin(); resItr != res.End(); ++resItr) {
				assert(resItr->IsString());
				std::string *resStr = new std::string(resItr->GetString());
				resNames->push_back(resStr);
			}

			EnemyInfo * eInfo = new EnemyInfo(level, hp, as, ms, resNames);
			m_enemyInfos->push_back(eInfo);
		}
		fclose(fp);
	}
}

void SharedVariables::loadStageInfos()
{
	if (!m_stageInfos) {
		FILE* fp;
		fopen_s(&fp, "Resources/Data/stages.json", "rb");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		rapidjson::Document document;
		document.ParseStream(is);
		assert(document.IsArray());
		auto arr = document.GetArray();

		m_stageInfos = new std::vector<StageInfo*>;

		for (auto itr = arr.Begin(); itr != arr.End(); ++itr) {
			assert(itr->IsObject());
			auto obj = itr->GetObject();
			assert(obj.HasMember("stage"));
			int stageIdx = obj["stage"].GetInt();
			assert(obj.HasMember("enemy count"));
			int ec = obj["enemy count"].GetInt();
			assert(obj.HasMember("enemy spawn time"));
			float est = obj["enemy spawn time"].GetFloat();
			assert(obj.HasMember("enemy min level"));
			int eminl = obj["enemy min level"].GetInt();
			assert(obj.HasMember("enemy max level"));
			int emaxl = obj["enemy max level"].GetInt();
			assert(obj.HasMember("boss"));
			bool isBoss = obj["boss"].GetBool();

 			StageInfo * sInfo = new StageInfo(stageIdx, ec, est, eminl, emaxl, isBoss);
			m_stageInfos->push_back(sInfo);
		}
		fclose(fp);
	}
}

void SharedVariables::loadEnemyGroups()
{
	if (!m_enemyGroups) {
		FILE* fp;
		fopen_s(&fp, "Resources/Data/enemyGroup.json", "rb");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		rapidjson::Document document;
		document.ParseStream(is);
		assert(document.IsArray());
		auto arr = document.GetArray();

		m_enemyGroups = new std::vector<EnemyGroupInfo*>;

		for (auto itr = arr.Begin(); itr != arr.End(); ++itr) {
			assert(itr->IsObject());
			auto obj = itr->GetObject();

			assert(obj.HasMember("group"));
			int group = obj["group"].GetInt();
			assert(obj.HasMember("count"));
			int count = obj["count"].GetInt();
			assert(obj.HasMember("rows"));
			int rows = obj["rows"].GetInt();
			assert(obj.HasMember("cols"));
			int cols = obj["cols"].GetInt();
			assert(obj.HasMember("space"));
			int space = obj["space"].GetInt();

			assert(obj.HasMember("layout"));
			auto layoutArr = obj["layout"].GetArray();
			int *layout = new int[rows * cols];
			int layoutIndex = 0;
			for (auto litr = layoutArr.Begin(); litr != layoutArr.End(); ++litr) {
				assert(litr->IsInt());
				layout[layoutIndex] = litr->GetInt();
				layoutIndex++;
			}

			EnemyGroupInfo * egInfo = new EnemyGroupInfo(group, count, rows, cols, space, layout);
			m_enemyGroups->push_back(egInfo);
		}
		fclose(fp);
	}
}

void SharedVariables::loadPlayerLevelInfo()
{
	if (!m_playerLevelInfos) {
		FILE* fp;
		fopen_s(&fp, "Resources/Data/playerLevel.json", "rb");
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

		rapidjson::Document document;
		document.ParseStream(is);
		assert(document.IsArray());
		auto arr = document.GetArray();

		m_playerLevelInfos = new std::vector<PlayerLevelInfo*>;

		for (auto itr = arr.Begin(); itr != arr.End(); ++itr) {
			assert(itr->IsObject());
			auto obj = itr->GetObject();

			assert(obj.HasMember("level"));
			int level = obj["level"].GetInt();

			assert(obj.HasMember("beam type"));
			int bt = obj["beam type"].GetInt();

			assert(obj.HasMember("beam damage"));
			int bd = obj["beam damage"].GetInt();

			assert(obj.HasMember("score to next"));
			int sc = obj["score to next"].GetInt();
			
			auto levelInfo = new PlayerLevelInfo(level, bt, bd, sc);
			m_playerLevelInfos->push_back(levelInfo);
		}
		fclose(fp);
	}
}


PlayerLevelInfo * SharedVariables::getLevelInfo(int lv)
{
	if (lv < 1) {
		lv = 1;
	}
	if (lv > m_playerLevelInfos->size()) {
		lv = m_playerLevelInfos->size();
	}
	auto result = m_playerLevelInfos->at(lv - 1);
	if (result->getLevel() != lv) {
		SDL_Log("wrong lvl %d", result->getLevel());
			for (auto lvInfo : *m_playerLevelInfos) {
				if (lvInfo->getLevel() == lv) {
					result = lvInfo;
					break;
				}
			}
	}

	return result;
}

int SharedVariables::getPlayerMaxLevel()
{
	return m_playerLevelInfos->size();
}
