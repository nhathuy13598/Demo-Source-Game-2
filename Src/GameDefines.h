#pragma once

#define radian2degree(a) (a * 57.295779513082)
#define degree2radian(a) (a * 0.017453292519)


#define RESOURCES_PATH	"Resources/"
#define TEXTURES_PATH	"Resources/Textures/"
#define DATA_PATH		"Resources/Data/"
#define FONT_PATH		"Resources/Fonts/font.ttf"

#define LOGO_GAME_1 "LogoGame_1.png"
#define LOGO_GAME_2 "LogoGame_2.png"
#define LOGO_GAME_3 "LogoGame_3.png"

#define GAME_PLAY_SUGGESTION	"Press/Hold spacebar to fire"
#define GAME_OVER_TITLE	"GAME OVER"
#define HELP_TITLE		"HELP"
#define ABOUT_TITLE		"ABOUT"
#define PLAY_TITLE		"PLAY"
#define PREPARE_TITLE	"READY"
#define SKIP_DESC		"Press any key to continue"
#define DEVELOPER_NAME  "Nguyen Anh Phuong"
#define ABOUT_DESC		"Training C++"
#define REPLAY_TEXT		"Replay"
#define CONTINUE_TEXT	"Continue"
#define QUIT_TEXT		"Quit"
#define FPS_TITLE		"FPS: "
#define SCORE_TITLE		"Score: "
#define PLAYER_LEVEL_TITLE	"Player level: "
#define STAGE_TITLE		"Stage-"
#define PLAYER_HP_TITLE "HP: "

#define ENEMY_COUNT_TITLE "Enemy Count: "
#define NEXT_STAGE_TITLE "Next Stage: "
// texture resource
#define MAIN_MENU_BG	"SpaceBackground-7.jpg"
#define ABOUT_BG		"SpaceBackground-2.jpg"
#define HELP_BG			"SpaceBackground-3.jpg"
#define BEAM_TEXTURE	"beams.png"
#define HEART_TEXTURE	"heart.png"
#define COIN_TEXTURE	"coin.png"

#define EXLORATION_TEXTURE "ExplosionSprite.png"
#define EXLORATION_TEXTURE_COL 4
#define EXLORATION_TEXTURE_ROW 4

#define PLAYER_TEXTURE	"mc.png"

typedef enum GameplayState {
	PREPARE_STAGE_STATE,
	PLAYING_STAGE_STATE,
	ENDING_STAGE_STATE,
	INGAME_MENU_STATE,
	GAME_OVER_STATE
}GameplayState;