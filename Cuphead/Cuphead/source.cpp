#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"

using namespace sf;
using namespace std;

RenderWindow window(VideoMode::getDesktopMode(), "Cuphead", Style::Fullscreen);

/*
  -------------------------------------------------
  | Page Number          |      cuurent Texture  |
  -------------------------------------------------
  | 50                   |     title screen     |
  | 1000                 |     main menu        |
  | 0                    |         map          |
  | 1                    |         Options      |
  | -1                   |          Exit        |
  | 10                   |        Shop			|
  | 5                    |        Level 1       |
  | 6                    |        Level 2       |
  | 7                    |        Level 3       |
  -------------------------------------------------
*/

// Common Textures And Sounds
// Winning Screen
Texture knockOutTex_Level2, backgroundWinTex, cupheadWinTex, cupheadTitleWinTex, theResultsWinTex, boardWinTex, lineWinTex, greyStarWinTex, yellowStarWinTex,
gradeCircleTex;
Font winFont;
SoundBuffer knockOutBuffer, bossDefeatBuffer, startClockBuffer, endClockBuffer, tickBuffer, starBuffer, winningScreenMusicBuffer;
// Common Textures
Texture hpBarTex, ghostTex, youDiedTextTex, ready_WallopTex_Level2, deathMenuTex;
// Common Sounds
SoundBuffer readyWallopBuffer;
Font deathMenuFont;

/* Common Player Level 1 & 2  */
Texture playerStandingTex, playerRunTex, playerJumpTex, playerDigonalDownTex, playerRunShootStraightTex,
playerRunDiagonalUpTex, playerShootUpTex, playerShootStraightTex, straightBulletTex, upBulletTex, diagonalUpBulletTex,
spawnTex, playerHitTex, playerCrawlTex, bulletDeathTex;
SoundBuffer playerJumpBuffer, playerHitBuffer, playerShootBuffer;

// Menu
/* Menu Textures, Fonts, Audios& Global Variables */
Texture MenuBackground, optionsBackground, TitleScreenBackground, CupheadnMugman, IntroTex, Story01Tex, Story02Tex, Story03Tex, Story04Tex, Story05Tex,
Story06Tex, Story07Tex, Story08Tex, Story09Tex, Story10Tex, Story11Tex, Story12Tex, Story13Tex, Story14Tex, Story15Tex, Story16Tex, OutroTex;
Font font;
SoundBuffer MenuBackgroungMusic, StoryBackgroungMusic;

// Map
// player
Texture mapTex_map, standingTex_map, runStraightTex_map, runDiagonalUpTex_map, runDiagonalDownTex_map, runUpTex_map, runDownTex_map;
Texture boardLevelTex_map, levelNameTex_map, entryLevelBackgroundTex_map, coinOverworld_map, LockTex_map;
Texture buttonXTex_map;
// Font
Font mapFont_map, guideFont_map;
// guide
Texture GuideMapTex_map, GuideTalkingTex_map, speechTex_map;
// Sound
SoundBuffer mapMusicBuffer_map, playerWalkBuffer_map, selectLevelBuffer_map, afterWinningBuffer_map;

// Shop
// Textures
Texture Background_Shop, LeftDrawer_Shop, RightDrawer_Shop, PorkrindWelcome_Shop, PorkrindIdle_Shop, PorkrindNods_Shop, PorkrindCheckClock_Shop, PorkrindGoodbye_Shop,
HealthItem_Shop, DamageItem_Shop, ItemSold_Shop, Infoboard_Shop, B_ButtonTex,
A_ButtonTex, CoinTex_Shop;
// Fonts
Font storeFont;
// Audios
SoundBuffer BackgroundMusic_Shop, PorkrindWelcomeBuf_Shop, PorkrindGoodByeBuf_Shop, ItemSoldBuf_Shop, DrawerOpenBuf_Shop, DrawerCloseBuf_Shop,
SelectSmthBuf_Shop;

// Level 1 
// Textures
Texture blueSkt_Level1Tex, clouds_Level1Tex[7], bushes_Level1Tex[5], tree_Level1Tex[2], tires_Level1Tex, ground_Level1Tex[6], mainGround_Level1Tex, fence_Level1Tex[2];
Texture background_Level1Tex, earthBreak_Level1Tex, potatoSpawn_Level1Tex, potatoAttack_Level1Tex, potatoBullet_Level1Tex, potatoDeath_Level1Tex;
Texture carrotSpawn_Level1Tex, carrotAttack_Level1Tex, carrotAttack2_level1Tex, carrotBullet_level1Tex, carrotRings_Level1Tex, carrotDeath_Level1Tex;
// Buffers
SoundBuffer musicBuffer_Level1, potatoGroundBuffer_Level1, potatoSpitBuffer_Level1, carrotGroundBuffer_Level1, carrotRingsBuffer_Level1, smallCarrotDeathBuffer_Level1;

/* Level 2 Textures & Sounds & Fonts */
// Background
Texture lightBackgroundTex_Level2, lightTowerTex_Level2, midCloudIdleTex_Level2, midCloudStandingTex_Level2,
cloudForegroundLightTex_Level2, cloudbackgroundLightTex_Level2;
// Phase 1
Texture dragonIdleTex_Level2, dragonIntroTex_Level2, dragonPeashotTex_Level2, dragonMeteorShootTex_Level2, fireBallTex_Level2,
ringTex_Level2, eyesAttackTex_Level2;
// Phase 2
Texture  dragonIntroPhase2Tex_Level2, dragonDashTex_Level2, drgonTongueTex_Level2, firstEnemyTex_Level2, enemyRunTex_Level2, enemyReadyTex_Level2,
enemyAttackTex_Level2, firePhase2Tex_Level2, smokePhase2Tex_Level2, dragonDeathPhase2Tex_Level2;
// Sound
// Phase 1
SoundBuffer levelTwoBuffer_Level2, meteorStartBuffer_Level2, meteorAttackBuffer_Level2, dragonIdleBuffer_Level2,
peashotAttackBuffer_Level2, peashotStartBuffer_Level2, peashotEndBuffer_Level2;
// Phase 2
SoundBuffer dashBuffer_Level2, dragonIntroBuffer_Level2, fireBuffer_Level2, smokeBuffer_Level2, firemarcherJumpBuffer_Level2,
firemarcherReadyBuffer_Level2;

/* Level 3 Textures, Fonts, Audios & Global Variables */
// Background
Texture backgroundTex_Level3, background2Tex_Level3;
// Player
Texture transUpTex_Level3, transDownTex_Level3, straightTex_Level3, straightBulletTex_Level3, spawnTex_Level3, PlayerParryTex_Level3, CupheadIntro, hitDustTex_Level3;
// Enemies
Texture enemyIntroTex_Level3, enemyIntro2Tex_Level3, enemyStaticTex_Level3, enemyBarfTex_Level3, EggTex_Level3, EggDeathTex_Level3,
handGunTex_Level3, handBulletTex_Level3, handBulletDeathTex_Level3, enemySteamTex_Level3, enemyFlapIntroTex_Level3, enemyFlapLoopTex_Level3,
FeatherTex_Level3, enemyFlapOutroTex_Level3, enemyPantTex_Level3, enemyDeathTex_Level3, yellowBirdTex_Level3, birdDeathTex_Level3,
knockoutTextTex_Level3;
// Audios
SoundBuffer ReadyWallopBuf_Level3, EnemyClockIntroBuf_Level3, EnemySecondIntroBuf_Level3, EnemyBarfBuf_Level3, EggDeathBuf_Level3, EnemyHandGunBuf_Level3,
EnemySteamBuf_Level3, EnemyPantBuf_Level3, FeatherAttackBuf_Level3, EnemyDeathBuf_Level3, birdDeathBuf_Level3, EnemyFlapBuf_Level3,
backgroundBuf_Level3, PlayerDeathBuf_Level3, youDiedTextBuf, PlayerParryBuf_Level3, PlayerBulletBuf_Level3, knockoutTextBuf_Level3;

// Common Global variables
float const windowSizeX = window.getSize().x;
float const windowSizeY = window.getSize().y;
float const rightWall = windowSizeX;
float const leftWall = 0;

// Level 1 Global variables
float const ground_Level1 = window.getSize().y - 350;
// Level 2 Global variables
float const ground_Level2 = windowSizeY;
// Level 3 Global variables
Clock LevelTime;
float PlayTimer = LevelTime.getElapsedTime().asSeconds();
long double const PI = 3.141592653589793238462643383279502884197;

// Menu Global Variables
int PageNumber = 50; // Title screen
bool isLastPageNumberMap;
// Shop Global Variables
int additionlLives = 0, coins = 0, DamageBought = 0;
int lastCoinsGained[3];
bool levelisDone[3];
Sound music;

Vector2f lastPositionOnMap = { 500 , 425 };

// Common Functions (Needed In Structures)
int randomNumber(int from, int to);
bool fadeToBlack(RectangleShape& rectangleFade, Clock& clock);
void shadowBackgroundSetup(Sprite& shadowBackgroundSprite, Texture& currentTexture);
void setTexturesAndFonts();

// Common Structures
struct readyWallopSt
{
	Sprite readyWallopSprite;
	float currentFrame;
	IntRect subRect;
	Clock increasingFrame;
	Sound readyWallopSound;
	bool soundPlayed;

	// In This SubRect , The Photo Is Vertical
	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = 0;
		subRect.top = size.y / photosNumber * int(currentFrame);
		subRect.width = size.x;
		subRect.height = size.y / photosNumber;
	}
	void setup()
	{
		readyWallopSprite.setTexture(ready_WallopTex_Level2);
		updateSubRectNoDirection(subRect, ready_WallopTex_Level2, 50, currentFrame);
		readyWallopSprite.setTextureRect(subRect);
		// Size for Every Photo ->  512, 288
		readyWallopSprite.setScale(windowSizeX / readyWallopSprite.getLocalBounds().width,
			windowSizeY / readyWallopSprite.getLocalBounds().height);
		currentFrame = 0;

		readyWallopSound.setBuffer(readyWallopBuffer);
		soundPlayed = false;
	}
	void update(int startingTime)
	{
		updateSubRectNoDirection(subRect, ready_WallopTex_Level2, 50, currentFrame);
		readyWallopSprite.setTextureRect(subRect);
		// 2500 -> startingTime, 50 -> photosNumber 
		// Every 2500 / 50.0 sec , the currentFrame Will Increase
		if (increasingFrame.getElapsedTime().asMilliseconds() > startingTime / 50.0)
		{
			currentFrame += 1;
			increasingFrame.restart();
		}
		// Sound
		if (!soundPlayed)
		{
			readyWallopSound.play();
			readyWallopSound.setVolume(60);
			soundPlayed = true;
		}
	}

	void draw()
	{
		window.draw(readyWallopSprite);
	}
};
struct knockOutSt
{
	Sprite knockOutSprite;
	float knockOutFrame;
	IntRect subRect;
	Sound knockOutSound;
	bool soundPlayed;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	void setup()
	{
		updateSubRectNoDirection(subRect, knockOutTex_Level2, 27, knockOutFrame);
		knockOutSprite.setTexture(knockOutTex_Level2);
		knockOutFrame = 0;
		knockOutSprite.setTextureRect(subRect);
		knockOutSprite.setScale(windowSizeX / knockOutSprite.getLocalBounds().width,
			windowSizeY / knockOutSprite.getLocalBounds().height);

		knockOutSound.setBuffer(knockOutBuffer);
		soundPlayed = false;
	}
	void update()
	{
		updateSubRectNoDirection(subRect, knockOutTex_Level2, 27, knockOutFrame);
		knockOutSprite.setTextureRect(subRect);
		knockOutFrame += 0.15;

		if (!soundPlayed)
		{
			soundPlayed = true;
			knockOutSound.play();
		}
	}
	void draw()
	{
		window.draw(knockOutSprite);
	}
};
struct winningScreenSt
{
	Sprite backgroundSprite, cupHeadSprite, cupHeadTitleSprite, theResultsSprite, boardSprite, lineSprite, starSprite;
	Text timeText, hpText, skillLevelText;
	Sprite stars[3];

	float cupHeadFrame;
	bool increaseCupheadFrame;
	IntRect cupHeadSubRect;

	// Every Level Set This Lives, for Hp
	int livesBefore, livesAfter;
	int livesCounter = 0; // From 0 To livesBefore
	Text hpResultText;

	// Every Level Set The Finishing Time, By Getting The Time Elapsed ,  (asSeconds)
	Text clockText;
	int finishingTime = 1000;
	int minutes = 0, seconds = 0;
	Clock increase;
	Clock startEveryAnimation;
	bool setFinishingTime = false;

	// Sound
	Sound startClockSound, endClockSound, tickSound, starSound;
	bool startClockSoundPlayed = false, musicPlayed = false;

	int nStars = 0, currentStar = 0; // How Many Stars He Got
	// Every Level Set The Time For Every Stars, (asSeconds)
	int threeStarsTime = 80, twoStarsTime = 120;

	Text gradeText;
	Sprite circleSprite;
	IntRect circleSubRect;
	int currentChar = 0;
	float circleFrame = 0;

	bool isLevelDone = false;
	bool clockTextFinished = false, hpTextFinished = false, starsFinished = false, gradeTextFinished = false;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		// background
		backgroundSprite.setTexture(backgroundWinTex);
		backgroundSprite.setScale(windowSizeX / backgroundSprite.getLocalBounds().width,
			windowSizeY / backgroundSprite.getLocalBounds().height);
		// moving Cuphead
		cupHeadFrame = 0;
		increaseCupheadFrame = true;
		updateSubRectNoDirection(cupHeadSubRect, cupheadWinTex, 7, cupHeadFrame);
		cupHeadSprite.setTexture(cupheadWinTex);
		cupHeadSprite.setTextureRect(cupHeadSubRect);
		cupHeadSprite.setScale(1.4, 1.4);
		cupHeadSprite.setOrigin(cupHeadSprite.getLocalBounds().width / 2, cupHeadSprite.getLocalBounds().height / 2);
		cupHeadSprite.setPosition(windowSizeX / 2 - 340, windowSizeY / 2 + 30);

		// the Results Word
		theResultsSprite.setTexture(theResultsWinTex);
		theResultsSprite.setScale(1.4, 1.4);
		theResultsSprite.setOrigin(theResultsSprite.getLocalBounds().width / 2, theResultsSprite.getLocalBounds().height / 2);
		theResultsSprite.setPosition(windowSizeX / 2, 150);

		// Cuphead Title
		cupHeadTitleSprite.setTexture(cupheadTitleWinTex);
		cupHeadTitleSprite.setOrigin(cupHeadTitleSprite.getLocalBounds().width / 2, cupHeadTitleSprite.getLocalBounds().height / 2);
		cupHeadTitleSprite.setPosition(cupHeadSprite.getPosition().x, windowSizeY / 2 + 380);
		cupHeadTitleSprite.setScale(cupHeadSprite.getLocalBounds().width / cupHeadTitleSprite.getLocalBounds().width, 1.4);

		// Board
		boardSprite.setTexture(boardWinTex);
		boardSprite.setOrigin(boardSprite.getLocalBounds().width / 2, boardSprite.getLocalBounds().height / 2);
		boardSprite.setPosition(windowSizeX / 2 + 220, windowSizeY / 2 + 75);
		boardSprite.setScale(1.2, 1.2);

		// Texts On Board
		// Texts On Left
		double textPosX = boardSprite.getPosition().x - boardSprite.getLocalBounds().width / 2 + 35;
		double textPosY = boardSprite.getPosition().y - boardSprite.getLocalBounds().height / 2 + 40;
		timeText.setFont(winFont);
		timeText.setString("Time.........");
		timeText.setCharacterSize(45);
		timeText.setPosition(textPosX, textPosY);

		hpText.setFont(winFont);
		hpText.setString("Hp...........");
		hpText.setCharacterSize(45);
		hpText.setPosition(textPosX, textPosY + 90);

		skillLevelText.setFont(winFont);
		skillLevelText.setString("Skill Level..");
		skillLevelText.setCharacterSize(45);
		skillLevelText.setPosition(textPosX, textPosY + 180);

		lineSprite.setTexture(lineWinTex);
		lineSprite.setScale(1.3, 1.1);
		lineSprite.setPosition(skillLevelText.getPosition().x, skillLevelText.getPosition().y + 75);

		// Results On Right
		double resultsPosX = skillLevelText.getPosition().x + 360;
		double resultsPosY = skillLevelText.getPosition().y + 13;

		clockText.setFont(winFont);
		clockText.setCharacterSize(40);
		clockText.setString("00:00");
		clockText.setPosition(resultsPosX + 5, resultsPosY - 180);

		hpResultText.setFont(winFont);
		hpResultText.setCharacterSize(45);
		hpResultText.setString(to_string(livesCounter) + "/" + to_string(livesBefore));
		hpResultText.setPosition(resultsPosX + 15, resultsPosY - 98);

		for (int i = 0; i < 3; i++)
		{
			stars[i].setTexture(greyStarWinTex);
			stars[i].setScale(1.25, 1.25);
			stars[i].setPosition(resultsPosX + (i * 45), resultsPosY);
		}
		// gradText 
		gradeText.setFont(winFont);
		gradeText.setCharacterSize(56);
		gradeText.setFillColor(Color::Yellow);
		gradeText.setString("Grade....?");
		gradeText.setPosition(lineSprite.getPosition().x + 55, lineSprite.getPosition().y + 30);

		updateSubRectNoDirection(circleSubRect, gradeCircleTex, 12, circleFrame);
		circleSprite.setTexture(gradeCircleTex);
		circleSprite.setTextureRect(circleSubRect);
		circleSprite.setScale(1.4, 1.4);
		circleSprite.setPosition(gradeText.getPosition().x + 290, gradeText.getPosition().y);

		// Sounds
		startClockSound.setBuffer(startClockBuffer);
		endClockSound.setBuffer(endClockBuffer);
		tickSound.setBuffer(tickBuffer);
		starSound.setBuffer(starBuffer);
	}
	void cupHeadUpdate()
	{
		if (cupHeadFrame >= 6)
			increaseCupheadFrame = false;
		if (cupHeadFrame <= 0)
			increaseCupheadFrame = true;

		if (increaseCupheadFrame)
			cupHeadFrame += 0.15;
		else
			cupHeadFrame -= 0.15;

		updateSubRectNoDirection(cupHeadSubRect, cupheadWinTex, 7, cupHeadFrame);
		cupHeadSprite.setTextureRect(cupHeadSubRect);
	}
	void updateClockText()
	{
		if (!startClockSoundPlayed)
		{
			startClockSound.play();
			startClockSound.setLoop(true);
			startClockSoundPlayed = true;
		}
		if (increase.getElapsedTime().asMilliseconds() >= 20)
		{
			seconds++;
			increase.restart();
		}
		if (seconds >= 60)
		{
			seconds = 0;
			minutes++;
		}
		clockText.setString('0' + to_string(minutes) + ':' + (seconds < 10 ? to_string(seconds) + '0' : to_string(seconds)));

		if (seconds + (minutes * 60) == finishingTime)
		{
			clockTextFinished = true;
			clockText.setFillColor(Color::Yellow);
			startEveryAnimation.restart();
			startClockSound.stop();
			endClockSound.play();
		}
	}
	void updateHpText()
	{
		if (increase.getElapsedTime().asMilliseconds() >= 300)
		{
			livesCounter++;
			tickSound.play();
			increase.restart();
		}
		hpResultText.setString(to_string(livesCounter) + '/' + to_string(livesBefore));
		if (livesCounter == livesAfter)
		{
			hpTextFinished = true;
			hpResultText.setFillColor(Color::Yellow);
			startEveryAnimation.restart();
		}
	}
	void updateStars()
	{
		if (increase.getElapsedTime().asMilliseconds() >= 600)
		{
			increase.restart();
			stars[currentStar].setTexture(yellowStarWinTex);
			starSound.play();
			currentStar++;
		}

		if (currentStar == nStars)
		{
			starsFinished = true;
			startEveryAnimation.restart();
		}
	}
	void circleAnimation()
	{
		updateSubRectNoDirection(circleSubRect, gradeCircleTex, 12, circleFrame);
		circleSprite.setTextureRect(circleSubRect);

		circleFrame += 0.2;
	}
	void updateGradeText()
	{
		if (increase.getElapsedTime().asMilliseconds() >= 350)
		{
			increase.restart();
			if (currentChar == 0)
				gradeText.setString("Grade....C");
			else if (currentChar == 1)
				gradeText.setString("Grade....B");
			else
				gradeText.setString("Grade....A");
			currentChar++;
			tickSound.play();
		}

		if (currentChar == nStars)
		{
			gradeTextFinished = true;
			startEveryAnimation.restart();
		}
	}

	void update()
	{
		if (!musicPlayed)
		{
			// Stars The Player Got
			if (finishingTime <= threeStarsTime)
				nStars = 3;
			else if (finishingTime <= twoStarsTime)
				nStars = 2;
			else
				nStars = 1;

			if (nStars > lastCoinsGained[PageNumber - 5])
			{
				coins += nStars - lastCoinsGained[PageNumber - 5];
				lastCoinsGained[PageNumber - 5] = nStars;
			}
			levelisDone[PageNumber - 5] = true;

			musicPlayed = true;
			music.play();
		}
		cupHeadUpdate();
		if (startEveryAnimation.getElapsedTime().asMilliseconds() >= 1000)
		{
			if (!clockTextFinished)
				updateClockText();
			else if (!hpTextFinished)
				updateHpText();
			else if (!starsFinished)
				updateStars();
			else if (!gradeTextFinished)
				updateGradeText();
		}
		else
			increase.restart();
		if (gradeTextFinished && circleFrame < 12)
			circleAnimation();
		if (circleFrame >= 12)
			isLevelDone = true;
	}
	void draw()
	{
		window.draw(backgroundSprite);
		window.draw(cupHeadSprite);
		window.draw(theResultsSprite);
		window.draw(cupHeadTitleSprite);
		window.draw(boardSprite);
		window.draw(timeText);
		window.draw(hpText);
		window.draw(skillLevelText);
		window.draw(lineSprite);
		for (int i = 0; i < 3; i++)
			window.draw(stars[i]);
		window.draw(hpResultText);
		window.draw(clockText);
		window.draw(gradeText);

		if (gradeTextFinished)
			window.draw(circleSprite);
	}
};
struct HpBarSt
{
	Sprite hpSprite;
	int lives;
	IntRect hpRect;
	bool isHit, oneLive;
	Clock hpClock;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void hpSetup()
	{
		lives = 5 + additionlLives;
		isHit = false;
		hpSprite.setTexture(hpBarTex);
		hpSprite.setScale(1.3, 1.3);
		hpSprite.setPosition(25, 25);
		updateSubRectNoDirection(hpRect, hpBarTex, 10, lives + 1);
		hpSprite.setTextureRect(hpRect);
		oneLive = false;
	}
	void oneLiveAnimation()
	{
		if (hpClock.getElapsedTime().asMilliseconds() >= 600)
		{
			hpClock.restart();
			if (oneLive)
				updateSubRectNoDirection(hpRect, hpBarTex, 10, lives + 1);
			else
				updateSubRectNoDirection(hpRect, hpBarTex, 10, lives);

			oneLive = !oneLive;
			hpSprite.setTextureRect(hpRect);
		}
	}
	void getHit()
	{
		if (lives == 1)
			lives -= 2;
		else
			lives--;
		updateSubRectNoDirection(hpRect, hpBarTex, 10, lives + 1);
		hpSprite.setTextureRect(hpRect);
		isHit = false;
	}
};
struct GhostSt
{
	Sprite youDiedSprite;
	IntRect deathRect;
	float deathFrame;
	bool isDead;
	Clock deathClock;
	Sprite shadowBackground;

	Sound ghostSound, youDiedSound;
	bool died;

	void updateSubRectDirection(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame, int lastKeyPressed)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		if (lastKeyPressed == 2)
		{
			subRect.left += size.x / photosNumber;
			photosNumber *= -1;
		}
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void ghostSetup()
	{
		youDiedSprite.setTexture(youDiedTextTex);
		youDiedSprite.setPosition(window.getSize().x / 2 - youDiedTextTex.getSize().x / 2, window.getSize().y / 2 - youDiedTextTex.getSize().y / 2);
		deathFrame = 0;
		isDead = false, died = true;
	}
	// Last Key Key Pressed Here , If We dont Wanna Direction Then let it With Default Value 
	void death(Texture& currentTexture, Sprite& player, float& moveY, int lastKeyPressed = 1)
	{
		if (died) {
			ghostSound.setBuffer(PlayerDeathBuf_Level3);
			ghostSound.play();
			youDiedSound.setBuffer(youDiedTextBuf);
			youDiedSound.play();

			died = false;
		}

		currentTexture = ghostTex;
		deathFrame += 0.2;
		if (deathFrame >= 24)
			deathFrame -= 24;
		updateSubRectDirection(deathRect, currentTexture, 24.0, deathFrame, lastKeyPressed);
		player.setTextureRect(deathRect);
		moveY = -2;
		player.move(0, moveY);
	}
};
struct deathMenuSt
{
	Sprite deathMenuSprite;
	Text options[2];
	int currentOption = 0;
	bool deathMenuDone;

	void setup()
	{
		deathMenuDone = false;

		deathMenuSprite.setTexture(deathMenuTex);
		deathMenuSprite.setScale(1.3, 1.3);
		deathMenuSprite.setPosition(windowSizeX / 2 - deathMenuSprite.getLocalBounds().width / 2 - 70,
			windowSizeY / 2 - deathMenuSprite.getLocalBounds().height / 2 - 70);

		for (int i = 0; i < 2; i++)
		{
			options[i].setFont(deathMenuFont);
			options[i].setFillColor(Color::Black);
			options[i].setCharacterSize(80);
			options[i].setStyle(Text::Bold);
		}
		options[0].setPosition(deathMenuSprite.getPosition().x + 240, deathMenuSprite.getPosition().y + 530);
		options[0].setString("RETRY");
		options[1].setPosition(deathMenuSprite.getPosition().x + 157, deathMenuSprite.getPosition().y + 600);
		options[1].setString("EXIT TO MAP");
	}
	void update(Event& event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up)
			{
				if (currentOption == 1)
					currentOption -= 1;
			}
			else if (event.key.code == Keyboard::Down)
			{
				if (currentOption == 0)
					currentOption += 1;
			}
			else if (event.key.code == Keyboard::Enter)
			{
				if (currentOption == 1)
					PageNumber = 0;
				deathMenuDone = true;
			}
		}
		for (int i = 0; i < 2; i++)
			options[i].setFillColor(Color::Black);
		options[currentOption].setFillColor(Color::Red);
	}
	void draw()
	{
		window.draw(deathMenuSprite);
		for (int i = 0; i < 2; i++)
			window.draw(options[i]);
	}
};

// Common Level 1 & 2
struct BulletSt
{
	// Bullet
	Sprite bulletSprite;
	float moveX = 0, moveY = 0;

	// Spawn
	Sprite spawnSprite;
	IntRect spawnSubRect;
	bool isSpawning;
	float spawnFrame;

	// Bullet Death
	bool bulletHitBoss = false, decreaseBossHealth = true;
	float bulletDeathFrame = 0;
	IntRect bulletDeathSubRect;

	void spawnSetup()
	{
		spawnSprite.setTexture(spawnTex);
		spawnSprite.setScale(0.6, 0.6);
		spawnFrame = 0;
		isSpawning = true;
	}
};

/* Structures & Functions */
// Menu
struct TitleScreenSt {
	Sprite TitleScreenBg, Cuphead;
	IntRect subRect;
	float TexFrame;
	Text pressAny;

	void updateSubRect(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame) {
		auto size = currentTexture.getSize();

		subRect.left = 0;
		subRect.top = size.y / photosNumber * int(currentFrame);
		subRect.width = size.x;
		subRect.height = size.y / photosNumber;
	}

	void setup() {
		music.setBuffer(MenuBackgroungMusic);
		music.play();
		music.setLoop(true);


		TitleScreenBg.setTexture(TitleScreenBackground);
		TitleScreenBg.setScale(1.5, 1.5);

		pressAny.setFont(font);
		pressAny.setFillColor(Color::Yellow);
		pressAny.setOutlineColor(Color::Black);
		pressAny.setOutlineThickness(5.0);
		pressAny.setString("Press Any Button");
		pressAny.setCharacterSize(70);
		pressAny.setPosition((window.getSize().x / 2) - 300, (window.getSize().y * 0.90));

		Cuphead.setTexture(CupheadnMugman);
		Cuphead.setTextureRect(subRect);
		Cuphead.setPosition(280, 300);
		Cuphead.setScale(1.7, 1.7);
		TexFrame = 0;
		updateSubRect(subRect, CupheadnMugman, 34.0, TexFrame);

	}
	void update() {
		TexFrame += 0.2;
		if (TexFrame >= 34)
		{
			TexFrame -= 34;
		}

		Cuphead.setTexture(CupheadnMugman);
		Cuphead.setTextureRect(subRect);
		updateSubRect(subRect, CupheadnMugman, 34.0, TexFrame);
	}

	void draw() {
		window.draw(TitleScreenBg);
		window.draw(Cuphead);
		window.draw(pressAny);

	}

};
struct StorySt
{
	Sprite StorySp;
	Texture CurrentTexture;
	IntRect subRect;
	float currentFrame, frameSpeed;
	Clock clock;
	bool Intro, Story01, Story02, Story03, Story04, Story05,
		Story06, Story07, Story08, Story09, Story10, Story11, Story12, Story13, Story14, Story15, Story16, Outro, isPressed;


	void updateSubRectCompact(IntRect& subRect, Texture currentTexture, int numRows, int numCols, int currentFrame) {
		auto size = currentTexture.getSize();

		int row = currentFrame / numCols;
		int col = currentFrame % numCols;

		subRect.width = size.x / numCols;
		subRect.height = size.y / numRows;
		subRect.left = col * subRect.width;
		subRect.top = row * subRect.height;
	}
	// Variables Intializtion
	void setup()
	{
		music.setBuffer(StoryBackgroungMusic);
		music.play();
		CurrentTexture = IntroTex;
		StorySp.setTexture(CurrentTexture);
		updateSubRectCompact(subRect, CurrentTexture, 10.0, 10.0, currentFrame);
		StorySp.setTextureRect(subRect);

		StorySp.setScale(window.getSize().x / StorySp.getLocalBounds().width,
			window.getSize().y / StorySp.getLocalBounds().height);

		currentFrame = 0;
		frameSpeed = 15.0;
		Intro = true, Story01 = false, Story02 = false, Story03 = false, Story04 = false, Story05 = false,
			Story06 = false, Story07 = false, Story08 = false, Story09 = false, Story10 = false, Story11 = false, Story12 = false, Story13 = false,
			Story14 = false, Story15 = false, Story16 = false, Outro = false, isPressed = true;
	}
	void update()
	{
		float deltaTime = clock.restart().asSeconds();

		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Space) || isPressed)
		{
			if (Intro)
			{
				currentFrame += frameSpeed * deltaTime; // Increment the current frame for Story01
				if (currentFrame >= 101.0)
				{
					currentFrame = 100.0; // Clamp current frame to the last frame of Story01
					Intro = false;
					Story01 = true;
					CurrentTexture = Story01Tex;
					currentFrame = 0; // Reset frame for Story02
				}
				updateSubRectCompact(subRect, CurrentTexture, 10.0, 10.0, currentFrame);
				StorySp.setTextureRect(subRect);
			}
			else if (Story01)
			{
				currentFrame += frameSpeed * deltaTime; // Increment the current frame for Story02
				if (currentFrame >= 24.0)
				{
					currentFrame = 23.0;
					Story01 = false;
					Story02 = true;
					CurrentTexture = Story02Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);
			}
			else if (Story02)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story02 = false;
					Story03 = true;
					CurrentTexture = Story03Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story03)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story03 = false;
					Story04 = true;
					CurrentTexture = Story04Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story04)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story04 = false;
					Story05 = true;
					CurrentTexture = Story05Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story05)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story05 = false;
					Story06 = true;
					CurrentTexture = Story06Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story06)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 21)
				{
					currentFrame = 21;
					Story06 = false;
					Story07 = true;
					CurrentTexture = Story07Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 7.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story07)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story07 = false;
					Story08 = true;
					CurrentTexture = Story08Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story08)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story08 = false;
					Story09 = true;
					CurrentTexture = Story09Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story09)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story09 = false;
					Story10 = true;
					CurrentTexture = Story10Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story10)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story10 = false;
					Story11 = true;
					CurrentTexture = Story11Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story11)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story11 = false;
					Story12 = true;
					CurrentTexture = Story12Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story12)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story12 = false;
					Story13 = true;
					CurrentTexture = Story13Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}

			else if (Story13)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story13 = false;
					Story14 = true;
					CurrentTexture = Story14Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story14)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story14 = false;
					Story15 = true;
					CurrentTexture = Story15Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}

			else if (Story15)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story15 = false;
					Story16 = true;
					CurrentTexture = Story16Tex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 8.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Story16)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 24)
				{
					currentFrame = 23;
					Story16 = false;
					Outro = true;
					CurrentTexture = OutroTex;
					currentFrame = 0;
				}
				updateSubRectCompact(subRect, CurrentTexture, 3.0, 9.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}
			else if (Outro)
			{
				currentFrame += frameSpeed * deltaTime;
				if (currentFrame >= 100)
				{
					currentFrame -= 100;
					Outro = false;

				}
				updateSubRectCompact(subRect, CurrentTexture, 10.0, 10.0, currentFrame);
				StorySp.setTextureRect(subRect);

			}

		}
	}

	void draw()
	{
		window.draw(StorySp);
	}
};

// Map Structres
struct PlayerMap_map
{
	Sprite mapSprite;
	View view;

	Sprite playerSpriteM;
	Texture currentTexture;
	IntRect subRect;
	int lastKeyPressed;
	int lastMove;
	float standFrame, runStraightFrame, runDiagonalUpFrame, runDiagonalDownFrame, runUpFrame, runDownFrame, moveX, moveY, Frame;
	float speed = 1.2, diagonalSpeed = 0.8;

	void updateSubRectDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		if (lastKeyPressed == 2)
		{
			subRect.left += size.x / photosNumber;
			photosNumber *= -1;
		}
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		currentTexture = standingTex_map;
		playerSpriteM.setTexture(currentTexture);
		playerSpriteM.setPosition(lastPositionOnMap);
		playerSpriteM.setScale(0.45, 0.45);
		lastKeyPressed = 1;
		moveX = 0, moveY = 0;
		standFrame = 0, runStraightFrame = 3, runDiagonalUpFrame = 4, runDiagonalDownFrame = 3, runUpFrame = 4, runDownFrame = 0;
		Frame = 0.2;

		mapSprite.setTexture(mapTex_map);
		mapSprite.setScale(window.getSize().x / mapSprite.getGlobalBounds().width, window.getSize().y / mapSprite.getGlobalBounds().height);
	}

	void moveRight()
	{
		lastKeyPressed = 1; // ( 1 : right , 2 : left )
		currentTexture = runStraightTex_map;
		updateSubRectDirection(subRect, currentTexture, 14.0, runStraightFrame);
		moveX = speed;
		runStraightFrame += Frame;
		if (runStraightFrame >= 14)
			runStraightFrame -= 11;

	}
	void moveLeft()
	{
		lastKeyPressed = 2;

		currentTexture = runStraightTex_map;
		updateSubRectDirection(subRect, currentTexture, 14.0, runStraightFrame);
		moveX = -1 * speed;
		runStraightFrame += Frame;
		if (runStraightFrame >= 14)
			runStraightFrame -= 11;
	}
	void moveUp()
	{
		currentTexture = runUpTex_map;
		updateSubRectNoDirection(subRect, currentTexture, 16.0, runUpFrame);
		moveY = -1 * speed;
		runUpFrame += Frame;
		if (runUpFrame >= 16)
			runUpFrame -= 12;
	}
	void moveDown()
	{
		currentTexture = runDownTex_map;
		updateSubRectNoDirection(subRect, currentTexture, 13.0, runDownFrame);
		moveY = speed;
		runDownFrame += Frame;
		if (runDownFrame >= 13)
			runDownFrame -= 13;
	}
	void moveDoignalUpRight()
	{
		lastKeyPressed = 1;
		currentTexture = runDiagonalUpTex_map;
		updateSubRectDirection(subRect, currentTexture, 15.0, runDiagonalUpFrame);
		moveX = diagonalSpeed, moveY = -1 * diagonalSpeed;
		runDiagonalUpFrame += Frame;
		if (runDiagonalUpFrame >= 15)
			runDiagonalUpFrame -= 11;
	}
	void moveDoignalUpLeft()
	{
		lastKeyPressed = 2;
		currentTexture = runDiagonalUpTex_map;
		updateSubRectDirection(subRect, currentTexture, 15.0, runDiagonalUpFrame);
		moveX = -1 * diagonalSpeed, moveY = -1 * diagonalSpeed;
		runDiagonalUpFrame += Frame;
		if (runDiagonalUpFrame >= 15)
			runDiagonalUpFrame -= 11;
	}
	void moveDoignalDownRight()
	{
		lastKeyPressed = 1;
		currentTexture = runDiagonalDownTex_map;
		updateSubRectDirection(subRect, currentTexture, 16.0, runDiagonalDownFrame);
		moveX = diagonalSpeed, moveY = diagonalSpeed;
		runDiagonalDownFrame += Frame;
		if (runDiagonalDownFrame >= 16)
			runDiagonalDownFrame -= 13;
	}
	void moveDoignalDownLeft()
	{
		lastKeyPressed = 2;
		currentTexture = runDiagonalDownTex_map;
		updateSubRectDirection(subRect, currentTexture, 16.0, runDiagonalDownFrame);
		moveX = -1 * diagonalSpeed, moveY = diagonalSpeed;
		runDiagonalDownFrame += Frame;
		if (runDiagonalDownFrame >= 16)
			runDiagonalDownFrame -= 13;
	}

	void update()
	{
		playerSpriteM.setTexture(currentTexture);
		playerSpriteM.setTextureRect(subRect);

		if (moveX == 0 && moveY == 0)
		{
			currentTexture = standingTex_map;
			updateSubRectNoDirection(subRect, currentTexture, 9.0, standFrame);
			standFrame += Frame / 4;
			if (standFrame >= 4)
				standFrame -= 4;
		}

		playerSpriteM.move(moveX, moveY);
		moveX = 0, moveY = 0;
		view.setCenter(playerSpriteM.getPosition().x + playerSpriteM.getLocalBounds().width / 2, playerSpriteM.getPosition().y + playerSpriteM.getLocalBounds().height / 2);
		lastPositionOnMap = playerSpriteM.getPosition();
		view.setSize(Vector2f(600, 450));
	}
	void draw()
	{
		window.setView(view);
		window.draw(mapSprite);

		window.draw(playerSpriteM);
	}
};
struct CoinMap_map
{
	Sprite coinSprite;
	IntRect coinRect;
	float frameX, frameY;
	string coinStr;
	Text coinText;

	void updateSubRect2D(IntRect& subRect, Texture& currentTexture, float numberX, float numberY, float frameX, float frameY)
	{
		// x Rows , y Columns -> (numberX -> y , numberY -> x)
		auto size = currentTexture.getSize();

		subRect.left = size.x / numberX * int(frameX);
		subRect.top = size.y / numberY * int(frameY);
		subRect.width = size.x / numberX;
		subRect.height = size.y / numberY;
	}

	void setup()
	{
		frameX = 0;
		frameY = 0;
		coinStr = to_string(coins);
		coinText.setFont(mapFont_map);
		coinText.setString("x" + coinStr);
	}
	void update(PlayerMap_map& player)
	{
		coinStr = to_string(coins);
		coinText.setString("x" + coinStr);
		updateSubRect2D(coinRect, coinOverworld_map, 4, 4, frameX, frameY);
		coinSprite.setTexture(coinOverworld_map);
		coinSprite.setTextureRect(coinRect);
		if (PageNumber == 0) {
			coinSprite.setScale(0.16, 0.16);
			coinSprite.setPosition(player.view.getCenter() - player.view.getSize() / 2.0f);
			coinText.setPosition(coinSprite.getPosition().x + 34, coinSprite.getPosition().y + 5);
		}
		else {
			coinSprite.setScale(0.3, 0.3);
			coinText.setCharacterSize(50);
			coinText.setPosition(85, 35);
			coinText.setFillColor(Color::Red);
			coinSprite.setPosition(10, 10);
		}


		frameX += 0.1;

		if (frameX >= 4 && frameY >= 3)
		{
			frameX = 0;
			frameY = 0;
		}
		else if (frameX >= 4)
		{
			frameX = 0;
			frameY++;
		}
	}

	void draw()
	{
		window.draw(coinSprite);
		window.draw(coinText);
	}
};
struct buttonXSt_map
{
	Sprite buttonXSprite;
	RectangleShape rec;
	void setup()
	{
		buttonXSprite.setTexture(buttonXTex_map);
		buttonXSprite.setScale(0.6, 0.6);
		rec.setFillColor(Color::Black);
		rec.setSize(Vector2f(20, 20));
	}
	void update(PlayerMap_map& playerMap)
	{
		buttonXSprite.setPosition(playerMap.playerSpriteM.getPosition().x + 15, playerMap.playerSpriteM.getPosition().y - 13);
		rec.setPosition(buttonXSprite.getPosition().x - 2, buttonXSprite.getPosition().y - 2.5);
	}
	void draw()
	{
		window.draw(rec);
		window.draw(buttonXSprite);
	}
};
struct entryLevelScreen_map
{
	Sprite boardSprite, levelNameSprite, entryLevelBackgroundSprite, levelLocked;
	IntRect subRect;
	Vector2f centerPos;
	Text shopText;
	bool isClicked = false;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup(PlayerMap_map& playerMap)
	{
		entryLevelBackgroundSprite.setTexture(entryLevelBackgroundTex_map);
		entryLevelBackgroundSprite.setOrigin(entryLevelBackgroundSprite.getLocalBounds().width / 2, entryLevelBackgroundSprite.getLocalBounds().height / 2);

		boardSprite.setTexture(boardLevelTex_map);
		boardSprite.setScale(0.6, 0.6);
		boardSprite.setOrigin(boardSprite.getLocalBounds().width / 2, boardSprite.getLocalBounds().height / 2);

		entryLevelBackgroundSprite.setScale(playerMap.view.getSize().x / entryLevelBackgroundSprite.getTexture()->getSize().x,
			playerMap.view.getSize().y / entryLevelBackgroundSprite.getTexture()->getSize().y);

		updateSubRectNoDirection(subRect, levelNameTex_map, 4, 0);
		levelNameSprite.setTextureRect(subRect);

		levelNameSprite.setTexture(levelNameTex_map);
		levelNameSprite.setScale(0.45, 0.45);
		levelNameSprite.setOrigin(levelNameSprite.getLocalBounds().width / 2, levelNameSprite.getLocalBounds().height / 2);

		levelLocked.setTexture(LockTex_map);
		levelLocked.setScale(0.57, 0.57);
	}
	void update(PlayerMap_map& playerMap, int currentState)
	{
		centerPos.x = playerMap.playerSpriteM.getPosition().x + playerMap.playerSpriteM.getLocalBounds().width / 2;
		centerPos.y = playerMap.playerSpriteM.getPosition().y + playerMap.playerSpriteM.getLocalBounds().height / 2;

		entryLevelBackgroundSprite.setPosition(centerPos.x, centerPos.y);
		boardSprite.setPosition(centerPos.x, centerPos.y);
		updateSubRectNoDirection(subRect, levelNameTex_map, 4, currentState);
		levelNameSprite.setTextureRect(subRect);
		levelNameSprite.setPosition(centerPos.x, centerPos.y);
		levelLocked.setPosition(centerPos.x - 122, centerPos.y - 170);
	}

	void draw(int currentState)
	{
		window.draw(entryLevelBackgroundSprite);
		window.draw(boardSprite);
		window.draw(levelNameSprite);
		if (currentState > 0 && currentState < 3) {
			if (!levelisDone[currentState - 1])
				window.draw(levelLocked);
		}
	}
};
struct guideSt_map {
	Sprite guide;
	Texture currentTexture;
	IntRect subRect;
	float IdleFrame, talkingFrame;
	Clock clock;
	bool isFrameIncreasing;

	void updateSubRect(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();
		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup() {
		currentTexture = GuideMapTex_map;
		guide.setTexture(currentTexture);
		guide.setTextureRect(subRect);
		guide.setPosition(835, 480);
		guide.setScale(0.2, 0.2);

		IdleFrame = 0, talkingFrame = 0;
		updateSubRect(subRect, currentTexture, 7.0, IdleFrame);
		isFrameIncreasing = true;
	}

	void idle() {
		currentTexture = GuideMapTex_map;
		guide.setTexture(currentTexture);
		guide.setTextureRect(subRect);
		if (IdleFrame >= 6.0)
			isFrameIncreasing = false;
		if (IdleFrame <= 0)
			isFrameIncreasing = true;

		if (isFrameIncreasing)
			IdleFrame += 0.08;
		else
			IdleFrame -= 0.08;
		updateSubRect(subRect, currentTexture, 7.0, IdleFrame);
	}
	void talking() {
		currentTexture = GuideTalkingTex_map;
		guide.setTexture(currentTexture);
		guide.setTextureRect(subRect);

		talkingFrame += 0.1;
		if (talkingFrame >= 5.0)
			talkingFrame -= 5.0;
		updateSubRect(subRect, currentTexture, 5.0, talkingFrame);
	}
	void update(bool isClicked) {
		if (isClicked) {
			talking();
		}
		else {
			idle();
		}
	}

	void draw() {
		window.draw(guide);
	}
};
struct speechSt_map {
	Sprite speech;
	Text Paragraphs[8];
	int currentParagraph;
	bool isClicked;
	Clock res;

	void setup() {
		isClicked = false;
		// Initialize currentParagraph to 0
		currentParagraph = 0;

		// Set up the Speech sprite
		// Assuming you have speechTex and guideFont defined somewhere
		speech.setTexture(speechTex_map);
		speech.setPosition(775, 360);
		speech.setScale(0.3, 0.3);

		// Set up each paragraph
		for (int i = 0; i < 8; i++) {
			Paragraphs[i].setFont(guideFont_map);
			Paragraphs[i].setFillColor(Color::Black);
			Paragraphs[i].setCharacterSize(7.5);
		}

		Paragraphs[0].setString("Ah, 'ello there, young adventurer!\nWell, before ya set off, there's\n   somethin' ya oughta know.");
		Paragraphs[0].setPosition(790, 395);

		Paragraphs[1].setString("Listen 'ere now,This world we're in \nis full o' surprises, it is, and it's\n up to brave souls like yerself \n\t\t  to discover 'em!");
		Paragraphs[1].setPosition(788, 391);

		Paragraphs[2].setString("\tFirst off,there's a patch o'\nvegetables just a stone's throw\nsouth from 'ere. Don't let yer \n\t\tguard down,me friend! ");
		Paragraphs[2].setPosition(790, 391);

		Paragraphs[3].setString("There's a challenge awaitin' amidst\n\t them carrots and potatos,\n\t\t\t mark me words!");
		Paragraphs[3].setPosition(786, 391);

		Paragraphs[4].setString("  Then,up north,there's a spring\nthat'll send you skyward you'll be\n\t flyin' high in the clouds.");
		Paragraphs[4].setPosition(788, 391);

		Paragraphs[5].setString("rubbin' elbows with mighty dragons.\n   But be warned,danger lurks \nup there,so keep yer wits about ye!");
		Paragraphs[5].setPosition(788, 392);

		Paragraphs[6].setString("And last but not least,there's\nthe airport up northeast, where\nthe skies stretchas far as the\neye can see.You'll soar with the\nbirds and feel the wind in yer 'air!");
		Paragraphs[6].setPosition(788, 385);

		Paragraphs[7].setString("So, me hearty adventurer,are you\n\t\tready to take on these\nchallenges? It won't be easy,but\n\t I've got a feelin' you're up \n\t\t\tto the task!");
		Paragraphs[7].setPosition(788, 388);
	}

	void draw(guideSt_map& guide)
	{
		window.draw(speech);
		window.draw(Paragraphs[currentParagraph]);
	}
	void handleKeyPress(guideSt_map& guide, Event& event) {
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Right) {
				currentParagraph++;
				if (currentParagraph == 8) {
					isClicked = false;
					currentParagraph = 0;
				}
			}
		}
	}
};

// Shop Structures
struct porkrindSt_Shop {
	Sprite Porkrind;
	Texture currentTexture;
	IntRect subRect;
	float WelcomeFrame, IdleFrame, NodFrame, CheckClockFrame, GoodbyeFrame;
	Clock clock, play;
	bool selectSmth, End, BisPressed;


	// Sound 
	Sound PorkrindSound;
	SoundBuffer CurrentSound;
	bool welcomeSound, GoodbyeSound;

	// Update Player's Animation
	void updateSubRect(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();
		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRectCompact(IntRect& subRect, Texture currentTexture, int numRows, int numCols, int currentFrame) {
		auto size = currentTexture.getSize();

		int row = currentFrame / numCols;
		int col = currentFrame % numCols;

		subRect.width = size.x / numCols;
		subRect.height = size.y / numRows;
		subRect.left = col * subRect.width;
		subRect.top = row * subRect.height;
	}

	// Variables Intializtion
	void setup() {
		CurrentSound = PorkrindWelcomeBuf_Shop;
		PorkrindSound.setBuffer(CurrentSound);
		PorkrindSound.play();
		currentTexture = PorkrindWelcome_Shop;
		Porkrind.setTexture(currentTexture);
		Porkrind.setTextureRect(subRect);
		Porkrind.setPosition(600, -20);
		Porkrind.setScale(1.5, 1.5);

		selectSmth = false, End = false, BisPressed = false;

		welcomeSound = true, GoodbyeSound = true;

		WelcomeFrame = 0, IdleFrame = 0, NodFrame = 0, CheckClockFrame = 0, GoodbyeFrame = 0;
		updateSubRect(subRect, currentTexture, 27.0, WelcomeFrame);
	}
	// Porkrind's Animation
	void welcome(float deltaTime) {
		if (welcomeSound) {
			CurrentSound = PorkrindWelcomeBuf_Shop;
			PorkrindSound.setBuffer(CurrentSound);
			PorkrindSound.play();
			welcomeSound = false;
		}
		currentTexture = PorkrindWelcome_Shop;
		Porkrind.setTexture(currentTexture);
		Porkrind.setTextureRect(subRect);

		WelcomeFrame += 0.15;
		if (WelcomeFrame >= 27.0)
			WelcomeFrame -= 27.0;
		updateSubRect(subRect, currentTexture, 27.0, WelcomeFrame);

	}
	void Idle(float deltaTime) {
		currentTexture = PorkrindIdle_Shop;
		Porkrind.setTexture(currentTexture);
		Porkrind.setTextureRect(subRect);

		IdleFrame += 7 * deltaTime;
		if (IdleFrame >= 6.0)
			IdleFrame -= 6.0;
		updateSubRect(subRect, currentTexture, 6.0, IdleFrame);

	}
	void Nod(float deltaTime) {
		currentTexture = PorkrindNods_Shop;
		Porkrind.setTexture(currentTexture);
		Porkrind.setTextureRect(subRect);

		NodFrame += 15 * deltaTime;
		if (NodFrame >= 14.0)
		{
			NodFrame -= 14.0;
			selectSmth = false;
		}
		updateSubRect(subRect, currentTexture, 14.0, NodFrame);

	}
	void CheckClock(float deltaTime) {
		currentTexture = PorkrindCheckClock_Shop;
		Porkrind.setTexture(currentTexture);
		Porkrind.setTextureRect(subRect);

		CheckClockFrame += 20 * deltaTime;
		if (CheckClockFrame >= 23.0)
			CheckClockFrame -= 23.0;
		updateSubRect(subRect, currentTexture, 23.0, CheckClockFrame);

	}
	void Goodbye(float deltaTime) {
		if (GoodbyeSound) {
			CurrentSound = PorkrindGoodByeBuf_Shop;
			PorkrindSound.setBuffer(CurrentSound);
			PorkrindSound.play();
			GoodbyeSound = false;
		}

		currentTexture = PorkrindGoodbye_Shop;
		Porkrind.setTexture(currentTexture);
		Porkrind.setTextureRect(subRect);

		GoodbyeFrame += 35 * deltaTime;
		if (GoodbyeFrame >= 34.0)
		{
			GoodbyeFrame -= 34.0;
			End = true;
		}
		updateSubRectCompact(subRect, currentTexture, 2.0, 17.0, GoodbyeFrame);

	}
	// Update
	void update() {
		float deltaTime = clock.restart().asSeconds();
		float playTime = play.getElapsedTime().asSeconds();


		if (playTime < 1.4) {
			welcome(deltaTime);
		}
		else if (selectSmth) {
			Nod(deltaTime);
		}
		else if (!selectSmth && fmod(playTime, 15.0) < 1.2) {
			CheckClock(deltaTime);
		}
		else if (Keyboard::isKeyPressed(Keyboard::B) || BisPressed) {
			BisPressed = true;
			PageNumber = 0;
			Goodbye(deltaTime);
		}
		else {
			Idle(deltaTime);
		}
	}
	// Draw
	void draw() {
		window.draw(Porkrind);
	}

};
struct itemSt_Shop {
	Sprite item;
	IntRect subRect;
	float CurrentFrame, SoldFrame;
	bool isSelected, isBought, Done;
	bool coinsSubtracted;

	Vector2f originalPosition;

	// Sound 
	Sound itemSound;
	bool isBoughtSound, ShowInfoSound;

	// Update Player's Animation
	void updateSubRect(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();
		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	// Variables Intializtion
	void setup(Texture& currentTexture, float photosNumber, float PositionX, float PositionY) {
		item.setTexture(currentTexture);
		item.setTextureRect(subRect);
		item.setPosition(PositionX, PositionY);

		originalPosition = item.getPosition();
		CurrentFrame = 0, SoldFrame = 0;
		updateSubRect(subRect, currentTexture, photosNumber, CurrentFrame);

		isSelected = false, isBought = false, Done = false;
		coinsSubtracted = false;

		isBoughtSound = true, ShowInfoSound = true;
	}

	bool ShowInfo(Vector2f worldPos) {

		// Get the bounding rectangle of the sprite
		FloatRect spriteBounds = item.getGlobalBounds();

		// Check if the mouse position intersects with the sprite
		bool isIntersecting = spriteBounds.contains(worldPos);
		return isIntersecting;
	}

	void ChosenItem(Texture& currentTexture, float photosNumber) {
		item.setTexture(currentTexture);
		item.setTextureRect(subRect);

		CurrentFrame += 0.1;
		if (CurrentFrame >= photosNumber)
			CurrentFrame -= photosNumber;

		updateSubRect(subRect, currentTexture, photosNumber, CurrentFrame);

	}

	// Update
	void update(Texture& currentTexture, float photosNumber, Vector2f worldPos) {
		item.setTexture(currentTexture);
		item.setTextureRect(subRect);

		isSelected = ShowInfo(worldPos);

		if (isBought && !Done) {
			if (isBoughtSound) {
				itemSound.setBuffer(ItemSoldBuf_Shop);
				itemSound.play();
				isBoughtSound = false;
			}
			item.setTexture(ItemSold_Shop);
			item.setTextureRect(subRect);
			SoldFrame += 0.2;
			if (SoldFrame >= 10.0)
			{
				SoldFrame -= 10.0;
				Done = true;
			}

			updateSubRect(subRect, ItemSold_Shop, 10.0, SoldFrame);
			return;
		}
		else if (Done) {
			item.setPosition(originalPosition);

			CurrentFrame = 0;
			updateSubRect(subRect, currentTexture, photosNumber, CurrentFrame);
			return;
		}

		if (ShowInfo(worldPos)) {
			if (ShowInfoSound) {
				itemSound.setBuffer(SelectSmthBuf_Shop);
				itemSound.play();
				ShowInfoSound = false;
			}
			// If mouse is over the item, set its position slightly adjusted
			item.setPosition(item.getPosition().x, originalPosition.y - 10);

			// Set the sub-rectangle to show the second photo
			subRect.left = currentTexture.getSize().x / photosNumber; // Assuming the second photo is at index 1
			subRect.width = currentTexture.getSize().x / photosNumber;

			ChosenItem(currentTexture, photosNumber);
		}
		else {
			ShowInfoSound = true;
			// Otherwise, set the position to its original position
			item.setPosition(originalPosition);

			// Set the sub-rectangle to show the first photo
			subRect.left = 0;
			subRect.width = currentTexture.getSize().x / photosNumber;

			CurrentFrame = 0;
			updateSubRect(subRect, currentTexture, photosNumber, CurrentFrame);
		}
	}

	// Draw
	void draw() {
		window.draw(item);
	}
};
struct HealthDescriptionSt_Shop {

	Sprite CoinSp_Shop;
	Text Title, subHeading, Description, Price;

	void setup() {
		CoinSp_Shop.setTexture(CoinTex_Shop);
		CoinSp_Shop.setPosition(875, 710);
		CoinSp_Shop.setScale(0.4, 0.4);

		Price.setString("2");
		Price.setFont(storeFont);
		Price.setCharacterSize(55);
		Price.setFillColor(Color::White);
		Price.setPosition(860, 712);

		Title.setString("HEART");
		Title.setFont(storeFont);
		Title.setCharacterSize(40);
		Title.setFillColor(Color::White);
		Title.setPosition(480, 740);
		Title.setStyle(Text::Bold);

		subHeading.setString("Extra Lives for Health");
		subHeading.setFont(storeFont);
		subHeading.setCharacterSize(32);
		subHeading.setFillColor(Color::White);
		subHeading.setPosition(380, 790);
		subHeading.setStyle(Text::Bold);

		Description.setString("Adds additional lives to your health bar; your\n\t\t health bar has 8 lives instead of 5.");
		Description.setFont(storeFont);
		Description.setCharacterSize(30);
		Description.setFillColor(Color::White);
		Description.setPosition(210, 850);
	}

	void draw() {
		window.draw(CoinSp_Shop);
		window.draw(Title);
		window.draw(subHeading);
		window.draw(Description);
		window.draw(Price);
	}

};
struct DamageDescriptionSt_Shop {

	Sprite CoinSp_Shop;
	Text Title, subHeading, Description, Price;

	void setup() {

		CoinSp_Shop.setTexture(CoinTex_Shop);
		CoinSp_Shop.setPosition(875, 710);
		CoinSp_Shop.setScale(0.4, 0.4);

		Price.setString("2");
		Price.setFont(storeFont);
		Price.setCharacterSize(55);
		Price.setFillColor(Color::White);
		Price.setPosition(860, 712);

		Title.setString("D.SUGAR");
		Title.setFont(storeFont);
		Title.setCharacterSize(40);
		Title.setFillColor(Color::White);
		Title.setPosition(455, 740);
		Title.setStyle(Text::Bold);

		subHeading.setString("Increase Boss Damage");
		subHeading.setFont(storeFont);
		subHeading.setCharacterSize(32);
		subHeading.setFillColor(Color::White);
		subHeading.setPosition(380, 790);
		subHeading.setStyle(Text::Bold);

		Description.setString("Decreasing Boss health by two units upon use.");
		Description.setFont(storeFont);
		Description.setCharacterSize(30);
		Description.setFillColor(Color::White);
		Description.setPosition(220, 850);
	}

	void draw() {
		window.draw(CoinSp_Shop);
		window.draw(Title);
		window.draw(subHeading);
		window.draw(Description);
		window.draw(Price);
	}

};
struct PurchasedSt_Shop {

	Sprite CoinSp_Shop;
	Text Title, subHeading;

	void setup() {

		CoinSp_Shop.setTexture(CoinTex_Shop);
		CoinSp_Shop.setPosition(875, 710);
		CoinSp_Shop.setScale(0.4, 0.4);

		Title.setString("PURCHASED");
		Title.setFont(storeFont);
		Title.setCharacterSize(40);
		Title.setFillColor(Color::White);
		Title.setPosition(430, 740);
		Title.setStyle(Text::Bold);

		subHeading.setString("Item no longer available!");
		subHeading.setFont(storeFont);
		subHeading.setCharacterSize(32);
		subHeading.setFillColor(Color::White);
		subHeading.setPosition(350, 790);
		subHeading.setStyle(Text::Bold);
	}

	void draw(Text Price) {
		window.draw(CoinSp_Shop);
		window.draw(Title);
		window.draw(subHeading);
		window.draw(Price);
	}

};
struct BackgroundSt_Shop {
	Sprite Background, leftDrawerSp, rightDrawerSp, InfoBoard, B_Button, A_Button;
	Text confirm, Back;
	Sound BackgroundMusic, DrawerSound;
	bool DrawerOpenSound, DrawerCloseSound;

	void setup() {
		BackgroundMusic.setBuffer(BackgroundMusic_Shop);
		BackgroundMusic.play();
		DrawerOpenSound = true, DrawerCloseSound = true;

		Background.setTexture(Background_Shop);

		InfoBoard.setTexture(Infoboard_Shop);
		InfoBoard.setPosition(-110, 690);
		InfoBoard.setScale(1.6, 1.6);

		leftDrawerSp.setTexture(LeftDrawer_Shop);
		leftDrawerSp.setPosition(95, 710);

		rightDrawerSp.setTexture(RightDrawer_Shop);
		rightDrawerSp.setPosition(1050, 710);

		B_Button.setTexture(B_ButtonTex);
		B_Button.setPosition(1880, 1030);

		A_Button.setTexture(A_ButtonTex);
		A_Button.setPosition(1750, 1030);

		confirm.setString("Confirm");
		confirm.setFont(storeFont);
		confirm.setFillColor(Color::White);
		confirm.setPosition(1618, 1022);
		confirm.setStyle(Text::Bold);

		Back.setString("Back");
		Back.setFont(storeFont);
		Back.setFillColor(Color::White);
		Back.setPosition(1800, 1022);
		Back.setStyle(Text::Bold);

	}

	void draw_back() {
		window.draw(InfoBoard);
	}
	void draw_middle() {
		window.draw(leftDrawerSp);
		window.draw(rightDrawerSp);
		window.draw(Background);

	}
	void draw_front() {
		window.draw(B_Button);
		window.draw(A_Button);
		window.draw(confirm);
		window.draw(Back);

	}
};

// Level 1 Structres
struct PlayerSt_Level1
{
	// Player
	Sprite playerSprite;
	float moveX, moveY, runFrame, jumpFrame, shootUpFrame, standFrame;
	int lastKeyPressed; // to show the last Positon if it is right or left, ( 1 : right , 2 : left )
	float positionX, positionY;
	Texture currentTexture; // set the current move
	IntRect subRect; // to Set All Textures We Want
	bool onGround, standIncreasingFrame;

	// Player Hp
	HpBarSt hp;

	// Player Death
	GhostSt ghost;

	// Shoot 
	vector<BulletSt> bullets;
	float const shootSpeed = 11;
	float shootCooldown;

	// Player Hit
	bool hitAnimation;
	float hitFrame;

	// Sounds
	Sound jumpSound, hitSound, shootSound;

	void updateSubRectDirection(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		if (lastKeyPressed == 2)
		{
			subRect.left += size.x / photosNumber;
			photosNumber *= -1;
		}
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRectNoDirection(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	// inital Values of every thing
	void setup()
	{
		// player
		currentTexture = playerStandingTex;
		positionX = playerSprite.getPosition().x, positionY = playerSprite.getPosition().y;
		playerSprite.setTexture(currentTexture);
		playerSprite.setPosition(window.getSize().x * 0.25, ground_Level1 - playerSprite.getLocalBounds().height - 10);
		playerSprite.setScale(0.8, 0.8);
		lastKeyPressed = 1;
		moveX = 0, moveY = 0;
		runFrame = 0, jumpFrame = 0, shootUpFrame = 0, standFrame = 0;
		onGround = false;

		// Hp
		hp.hpSetup();

		// Death
		ghost.ghostSetup();

		// Shooting
		bullets.clear();
		shootCooldown = 170;

		// Player Hit
		hitAnimation = false;
		hitFrame = 0;

		// Sound
		jumpSound.setBuffer(playerJumpBuffer);
		jumpSound.setVolume(60);
		hitSound.setBuffer(playerHitBuffer);
		hitSound.setVolume(80);
		shootSound.setBuffer(playerShootBuffer);
		shootSound.setVolume(30);
	}

	// PLayer Move
	void moveRight()
	{
		lastKeyPressed = 1; // ( 1 : right , 2 : left )

		currentTexture = playerRunTex;
		moveX = 5;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);
	}
	void moveLeft()
	{
		lastKeyPressed = 2; // ( 1 : right , 2 : left )

		currentTexture = playerRunTex;
		moveX = -5;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);
	}
	void jumb()
	{
		if (!onGround)
			return;
		jumpSound.play();
		moveY = -14;
		onGround = false;
	}

	// Player Hit
	void playerHit()
	{
		currentTexture = playerHitTex;
		updateSubRectDirection(subRect, playerHitTex, 6, hitFrame);
		hitFrame += 0.1;
		if (hitFrame >= 6)
		{
			hitFrame = 0;
			hitAnimation = false;
		}
	}

	// Player Shoot Moving && Bullets
	void shootStraight(Clock& shootClock)
	{
		// Player
		currentTexture = playerShootStraightTex;
		updateSubRectDirection(subRect, currentTexture, 6.0, shootUpFrame);

		shootUpFrame += 0.25;
		if (shootUpFrame >= 6)
			shootUpFrame -= 6;

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;
		shootClock.restart();
		// Sound
		shootSound.play();
		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(straightBulletTex);
		currentBullet.moveX = shootSpeed;

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 140, positionY - 65);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 125, positionY + 65);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 305, positionY - 65);
			currentBullet.moveX *= -1;

			auto size = straightBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX - 15, positionY + 65);
		}
		bullets.push_back(currentBullet);
	}
	void shootRunStraight(Clock& shootClock) {

		currentTexture = playerRunShootStraightTex;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;
		shootClock.restart();
		// Sound
		shootSound.play();
		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(straightBulletTex);

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 135, positionY - 50);
			currentBullet.moveX = (shootSpeed + 3);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 150, positionY + 80);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 310, positionY - 50);
			currentBullet.moveX = (shootSpeed + 3) * -1;

			auto size = straightBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX - 45, positionY + 80);
		}

		bullets.push_back(currentBullet);
	}
	void shootRunDiagonalUp(Clock& shootClock) {
		// Player
		currentTexture = playerRunDiagonalUpTex;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;
		shootClock.restart();
		// Sound
		shootSound.play();
		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(diagonalUpBulletTex);
		currentBullet.moveX = shootSpeed;
		currentBullet.moveY = -1 * shootSpeed;

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 20, positionY - 350);
			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 150, positionY);
		}
		else if (lastKeyPressed == 2)
		{
			currentBullet.bulletSprite.setPosition(positionX - 200, positionY - 350);
			currentBullet.moveX *= -1;

			auto size = diagonalUpBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX - 50, positionY);
		}
		currentBullet.bulletSprite.setScale(1.2, 1.2);

		bullets.push_back(currentBullet);
	}
	void shootUp(Clock& shootClock)
	{
		// Player
		currentTexture = playerShootUpTex;
		updateSubRectDirection(subRect, currentTexture, 6.0, shootUpFrame);
		shootUpFrame += 0.25;
		if (shootUpFrame >= 6)
			shootUpFrame -= 6;

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;
		shootClock.restart();
		// Sound
		shootSound.play();
		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(upBulletTex);
		currentBullet.moveY = -1 * shootSpeed;

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 35, positionY - 325);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 85, positionY - 37);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 105, positionY - 325);

			auto size = upBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 15, positionY - 37);
		}

		bullets.push_back(currentBullet);
	}

	void update(int& currentPhase)
	{
		// re scale the player
		playerSprite.setScale(0.8, 0.8);

		// Death 
		if (hp.lives <= 0)
		{
			ghost.death(currentTexture, playerSprite, moveY, lastKeyPressed);
			ghost.isDead = true;

			// Clear Bullets
			if (bullets.size())
				bullets.clear();
			return;
		}
		// Timer Starts From Death Time
		ghost.deathClock.restart();

		// Standing Position
		if (moveX == 0 && onGround && !(Mouse::isButtonPressed(Mouse::Left)))
		{
			currentTexture = playerStandingTex;
			updateSubRectDirection(subRect, currentTexture, 5, standFrame);

			if (standFrame <= 0.08)
				standIncreasingFrame = true;
			if (standFrame >= 4.92)
				standIncreasingFrame = false;

			if (standIncreasingFrame)
				standFrame += 0.08;
			else
				standFrame -= 0.08;
		}
		// Jumping
		else if (!onGround)
		{
			currentTexture = playerJumpTex;
			updateSubRectDirection(subRect, currentTexture, 8, jumpFrame);

			moveY += 0.4;
			playerSprite.setScale(0.6, 0.6);

			jumpFrame += 0.25;
			if (jumpFrame >= 8)
				jumpFrame -= 8;
		}

		if (hitAnimation)
			playerHit();

		if (playerSprite.getPosition().x <= leftWall && moveX < 0)
			moveX = 0;
		if (currentPhase == 1)
		{
			if (playerSprite.getPosition().x >= rightWall - 850 && moveX > 0)
				moveX = 0;
		}
		if (currentPhase == 2)
		{
			if (playerSprite.getPosition().x >= rightWall - 180 && moveX > 0)
				moveX = 0;
		}

		playerSprite.setTexture(currentTexture);
		playerSprite.setTextureRect(subRect);

		// Bullets Moving
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].bulletSprite.move(bullets[i].moveX, bullets[i].moveY);
			// spawn
			if (bullets[i].spawnFrame >= 4)
			{
				bullets[i].isSpawning = false;
			}
			if (bullets[i].isSpawning)
			{
				bullets[i].spawnFrame += 0.4;
				updateSubRectDirection(bullets[i].spawnSubRect, spawnTex, 4.0, bullets[i].spawnFrame);
				bullets[i].spawnSprite.setTextureRect(bullets[i].spawnSubRect);
			}

			if (bullets[i].bulletHitBoss)
			{
				bullets[i].bulletSprite.setTexture(bulletDeathTex);
				updateSubRectNoDirection(bullets[i].bulletDeathSubRect, bulletDeathTex, 6, bullets[i].bulletDeathFrame);
				bullets[i].bulletSprite.setTextureRect(bullets[i].bulletDeathSubRect);
				bullets[i].bulletSprite.setScale(1.7, 1.7);
				bullets[i].bulletDeathFrame += 0.2;

				bullets[i].moveX = 0;
				bullets[i].moveY = 0;
			}

			if (bullets[i].bulletSprite.getPosition().x >= rightWall || bullets[i].bulletSprite.getPosition().x <= leftWall - 300
				|| bullets[i].bulletSprite.getPosition().y <= -400 || bullets[i].bulletDeathFrame >= 6)
			{
				bullets.erase(bullets.begin() + i);
				i--;
			}
		}

		// Player Move 
		playerSprite.move(moveX, moveY);
		runFrame += 0.25;
		if (runFrame >= 16)
			runFrame -= 16;

		// Hp
		if (hp.isHit)
		{
			hp.getHit();
			hitSound.play();
			hitAnimation = true;
			hitFrame = 0;
		}

		if (hp.lives == 1)
		{
			hp.oneLiveAnimation();
		}

		// Player on The Ground
		onGround = false;
		if (playerSprite.getPosition().y >= ground_Level1)
		{
			moveY = 0;
			onGround = true;
		}

		hp.isHit = false;
		moveX = 0;
		positionX = playerSprite.getPosition().x;
		positionY = playerSprite.getPosition().y;
	}
	void draw()
	{
		window.draw(playerSprite);
		window.draw(hp.hpSprite);
		if (ghost.isDead && ghost.deathClock.getElapsedTime().asMilliseconds() <= 3000 && ghost.deathClock.getElapsedTime().asMilliseconds() >= 500)
		{
			window.draw(ghost.youDiedSprite);
		}
	}
};
struct backgroundSt_Level1
{
	Sprite blueSky, clouds[7], bushes[5];
	Sprite tree[2], tires;
	IntRect tiresRect;
	float tiresFrameX, tiresFrameY;
	bool tiresReverse;

	Sprite ground[6];
	Sprite mainGround, fence[2];

	void updateSubRect2D(IntRect& subRect, Texture& currentTexture, float numberX, float numberY, float frameX, float frameY)
	{
		// x Rows , y Columns -> (numberX -> y , numberY -> x)
		auto size = currentTexture.getSize();

		subRect.left = size.x / numberX * int(frameX);
		subRect.top = size.y / numberY * int(frameY);
		subRect.width = size.x / numberX;
		subRect.height = size.y / numberY;
	}

	void setup()
	{
		mainGround.setTexture(mainGround_Level1Tex);

		blueSky.setTexture(blueSkt_Level1Tex);
		blueSky.setScale(windowSizeX / blueSky.getLocalBounds().width, windowSizeY / blueSky.getGlobalBounds().height);
		blueSky.setPosition(0, 0);

		for (int i = 0; i < 7; i++)
		{
			clouds[i].setTexture(clouds_Level1Tex[i]);
			clouds[i].setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);
		}

		clouds[0].setPosition(0, -10);
		clouds[1].setPosition(500, 250);
		clouds[2].setPosition(windowSizeX - 10, -10);
		clouds[3].setPosition(900, 320);
		clouds[4].setPosition(windowSizeX, 340);
		clouds[5].setPosition(200, -30);
		clouds[6].setPosition(1000, 0);

		for (int i = 0; i < 5; i++)
		{
			bushes[i].setTexture(bushes_Level1Tex[i]);
			bushes[i].setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);
		}

		bushes[0].setPosition(-50, 350);
		bushes[3].setPosition(640, 350);

		for (int i = 0; i < 2; i++)
			tree[i].setTexture(tree_Level1Tex[i]);

		tree[0].setPosition(-50, -50);
		tree[0].setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);
		tree[1].setPosition(windowSizeX - 730, 280);
		tree[1].setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);

		tiresFrameX = 0;
		tiresFrameY = 0;
		tiresReverse = false;

		updateSubRect2D(tiresRect, tires_Level1Tex, 4, 4, tiresFrameX, tiresFrameY);
		tires.setTexture(tires_Level1Tex);
		tires.setPosition(435, 220);
		tires.setTextureRect(tiresRect);
		tires.setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);


		for (int i = 0; i < 6; i++)
		{
			ground[i].setTexture(ground_Level1Tex[i]);
			ground[i].setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);
		}
		ground[0].setPosition(-40, ground_Level1 - 225);
		ground[1].setPosition(-40, ground_Level1 - 270);
		ground[2].setPosition(-40, ground_Level1 - 290);
		ground[3].setPosition(-10, ground_Level1 - 360);
		ground[4].setPosition(-3, ground_Level1 - 340);
		ground[5].setPosition(-40, ground_Level1 - 260);

		mainGround.setScale(windowSizeX / mainGround.getLocalBounds().width + 0.05, windowSizeX / mainGround.getLocalBounds().width + 0.05);
		mainGround.setPosition(-10, windowSizeY - mainGround.getLocalBounds().height - 250);

		for (int i = 0; i < 2; i++)
			fence[i].setTexture(fence_Level1Tex[i]);

		fence[0].setPosition(-15, windowSizeY - fence[0].getLocalBounds().height - 90);
		fence[0].setScale(1.8, 1.8);

		fence[1].setPosition(windowSizeX - fence[1].getLocalBounds().width - 350, window.getSize().y - fence[1].getLocalBounds().height - 90);
		fence[1].setScale(1.8, 1.8);

	}

	void update()
	{
		if (!tiresReverse)
		{
			tiresFrameX += 0.05;
			if (tiresFrameX >= 1 && tiresFrameY >= 3)
			{
				tiresReverse = true;
				tiresFrameX = 0;
			}
			if (tiresFrameX >= 4)
			{
				tiresFrameX = 0;
				tiresFrameY++;
			}
		}
		else
		{
			tiresFrameX -= 0.05;
			if (tiresFrameX <= 0 && tiresFrameY <= 0)
			{
				tiresReverse = false;
				tiresFrameX = 0;
			}
			else if (tiresFrameX <= 0)
			{
				tiresFrameX = 3;
				tiresFrameY--;
			}
		}

		updateSubRect2D(tiresRect, tires_Level1Tex, 4, 4, tiresFrameX, tiresFrameY);
		tires.setTextureRect(tiresRect);

		for (int i = 0; i < 7; i++)
		{
			clouds[i].move(-(i * 0.1 + 0.25), 0);
			if (clouds[i].getPosition().x < -400 - clouds[i].getLocalBounds().width)
				clouds[i].setPosition(window.getSize().x, clouds[i].getPosition().y);
		}
	}

	void draw1()
	{
		window.draw(blueSky);
		for (int i = 0; i < 7; i++)
			window.draw(clouds[i]);
		window.draw(bushes[0]);
		window.draw(bushes[3]);
		for (int i = 0; i < 2; i++)
			window.draw(tree[i]);
		window.draw(tires);
		for (int i = 5; i >= 1; i--)
			window.draw(ground[i]);
	}
	void draw2()
	{
		window.draw(ground[0]);
		window.draw(mainGround);
	}
	void draw3()
	{
		for (int i = 0; i < 2; i++)
			window.draw(fence[i]);
	}
};
struct potatoBullet_Level1
{
	Sprite bullet;
	IntRect subRect;
	float bulletMoveX = -9;
	float bulletFrameX = 0;
};
struct carrotRings
{
	Sprite ring;
	IntRect ringRect;
	float moveX, moveY;
	float ringFrameX = 0;
};
struct level1
{
	int currentPhase = 1;

	Sprite earth;
	Texture earthCurrentTexture;
	IntRect earthRect;
	float earthFrameX, earthFrameY;
	bool earthBreak;

	Sprite boss;
	Texture bossCurrentTexture;
	IntRect bossRect;
	int health;
	float bossFrameX, bossFrameY;
	bool bossSpawnStart, bossSpawn, dead;

	bool startShooting;
	vector<potatoBullet_Level1> bossBullets;

	int carrotAttack;
	int const ringSpeed = 7.5;
	float lengthRing, moveXRing, moveYRing;
	bool startShootingRing[4];
	Vector2f directionRing, bossEyeRing;
	vector<carrotRings> rings;

	float const bulletSpeed = 5;
	bool startShootingBullet[4];
	vector<Sprite> carrotBullets;
	bool carrotBulletSkip;

	bool deathFrame;

	Color EnemyColor = boss.getColor();
	Clock fadetimer;
	float elapsedTime;

	RectangleShape carrotShapeCollision;

	bool isCarrotDead = false;
	// Sounds
	Sound potatoGroundSound, potatoSpitSound, carrotGroundSound, carrotRingsSound, smallCarrotDeathSound;
	bool potatoGroundSoundPlayed = false, carrotRingSoundPlayed = false;

	void updateSubRect2D(IntRect& subRect, Texture& currentTexture, float numberX, float numberY, float frameX, float frameY)
	{
		// x Rows , y Columns -> (numberX -> y , numberY -> x)
		auto size = currentTexture.getSize();

		subRect.left = size.x / numberX * int(frameX);
		subRect.top = size.y / numberY * int(frameY);
		subRect.width = size.x / numberX;
		subRect.height = size.y / numberY;
	}
	void updateSubRect(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	void setup()
	{
		earthFrameX = 0;
		earthFrameY = 0;
		earthBreak = false;

		bossFrameX = 0;
		bossFrameY = 0;
		if (currentPhase == 1)
			health = 800;
		else
			health = 1400;

		bossSpawnStart = false;
		bossSpawn = false;
		dead = false;

		startShooting = true;

		carrotAttack = 0;
		startShootingRing[0] = true;
		startShootingRing[1] = true;
		startShootingRing[2] = true;
		startShootingRing[3] = true;
		carrotBulletSkip = false;

		deathFrame = false;

		EnemyColor = boss.getColor();
		elapsedTime = 0;

		carrotShapeCollision.setPosition(820, 0);
		carrotShapeCollision.setSize(Vector2f(200, 200));

		// Sounds
		potatoGroundSound.setBuffer(potatoGroundBuffer_Level1);
		potatoSpitSound.setBuffer(potatoSpitBuffer_Level1);
		carrotGroundSound.setBuffer(carrotGroundBuffer_Level1);
		carrotRingsSound.setBuffer(carrotRingsBuffer_Level1);
		smallCarrotDeathSound.setBuffer(smallCarrotDeathBuffer_Level1);
	}

	void bulletHitBoss(vector<BulletSt>& currentBullets, PlayerSt_Level1& player)
	{
		if (player.ghost.isDead)
			return;
		for (auto& bullet : currentBullets)
		{
			auto bulletPos = bullet.bulletSprite.getPosition();
			float bossPos;

			if (currentPhase == 1)
			{
				if (player.playerSprite.getPosition().x < boss.getPosition().x)
					bossPos = boss.getPosition().x;
				else
					bossPos = boss.getPosition().x + boss.getLocalBounds().width;

				if (bullet.bulletSprite.getGlobalBounds().intersects(boss.getGlobalBounds()) && bulletPos.x >= bossPos)
				{
					bullet.bulletHitBoss = true;
					if (bullet.decreaseBossHealth)
						health -= 10 + DamageBought;
					bullet.decreaseBossHealth = false;

					EnemyColor.a = 255 - 50; // Decrease alpha
					boss.setColor(EnemyColor);
				}
			}
			else
			{
				if (bullet.bulletSprite.getGlobalBounds().intersects(carrotShapeCollision.getGlobalBounds()))
				{
					bullet.bulletHitBoss = true;
					if (bullet.decreaseBossHealth)
						health -= 10 + DamageBought;
					bullet.decreaseBossHealth = false;

					EnemyColor.a = 255 - 50; // Decrease alpha
					boss.setColor(EnemyColor);
				}
			}
		}
	}
	void potatoBulletHitPlayer(PlayerSt_Level1& player, bool& winning)
	{
		if (winning)
			return;
		for (int i = 0; i < bossBullets.size();)
		{
			if (bossBullets[i].bullet.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds())
				&& player.playerSprite.getPosition().x + player.playerSprite.getLocalBounds().width > bossBullets[i].bullet.getPosition().x + 30
				&& player.playerSprite.getPosition().y + player.playerSprite.getLocalBounds().height > bossBullets[i].bullet.getPosition().y + bossBullets[i].bullet.getLocalBounds().height + 40
				&& player.playerSprite.getPosition().x < bossBullets[i].bullet.getPosition().x + bossBullets[i].bullet.getLocalBounds().width - 17)
			{
				player.hp.isHit = true;
				bossBullets.erase(bossBullets.begin() + i);
			}
			else
				i++;
		}
	}
	void carrotBulletsHitPlayer(PlayerSt_Level1& player, bool& winning)
	{
		if (winning)
			return;
		for (int i = 0; i < carrotBullets.size(); i++)
		{
			bool isCurrnetCarrotBulletHitted = false;
			for (int j = 0; j < player.bullets.size(); j++)
			{
				if (player.bullets[j].bulletSprite.getGlobalBounds().intersects(carrotBullets[i].getGlobalBounds()))
				{
					player.bullets[j].bulletHitBoss = true;
					smallCarrotDeathSound.play();
					carrotBullets.erase(carrotBullets.begin() + i);
					isCurrnetCarrotBulletHitted = true;
					i--;
					break;
				}
			}

			if (!isCurrnetCarrotBulletHitted && carrotBullets[i].getGlobalBounds().intersects(player.playerSprite.getGlobalBounds()))
			{
				player.hp.isHit = true;
				smallCarrotDeathSound.play();
				carrotBullets.erase(carrotBullets.begin() + i);
			}
		}
	}
	void carrotRingsHitPlayer(PlayerSt_Level1& player, bool& winning)
	{
		if (winning)
			return;
		for (int i = 0; i < rings.size();)
		{
			if (rings[i].ring.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds())
				&& player.playerSprite.getPosition().y + player.playerSprite.getLocalBounds().height > rings[i].ring.getPosition().y + rings[i].ring.getLocalBounds().height - 15
				&& player.playerSprite.getPosition().x < rings[i].ring.getPosition().x + rings[i].ring.getLocalBounds().width - 75)
			{
				player.hp.isHit = true;
				rings.erase(rings.begin() + i);
			}
			else
				i++;
		}
	}
	void potatoBulletUpdate()
	{
		for (int i = 0; i < bossBullets.size();)
		{
			bossBullets[i].bulletFrameX += 0.1;

			if (bossBullets[i].bulletFrameX >= 8)
				bossBullets[i].bulletFrameX = 0;


			bossBullets[i].bullet.move(bossBullets[i].bulletMoveX, 0);

			updateSubRect(bossBullets[i].subRect, potatoBullet_Level1Tex, 8, bossBullets[i].bulletFrameX);
			bossBullets[i].bullet.setTextureRect(bossBullets[i].subRect);

			if (bossBullets[i].bullet.getPosition().x < -200)
				bossBullets.erase(bossBullets.begin() + i);
			else
				i++;
		}
	}
	void carrotRingsUpdate()
	{
		for (int i = 0; i < rings.size();)
		{
			rings[i].ringFrameX += 0.1;

			if (rings[i].ringFrameX >= 9)
				rings[i].ringFrameX = 3;

			rings[i].ring.move(rings[i].moveX, rings[i].moveY);

			updateSubRect(rings[i].ringRect, carrotRings_Level1Tex, 9, rings[i].ringFrameX);
			rings[i].ring.setTextureRect(rings[i].ringRect);

			if (rings[i].ring.getPosition().y >= ground_Level1 + 100)
				rings.erase(rings.begin() + i);
			else
				i++;
		}
	}
	void carrotBulletsUpdate(Vector2f playerPosition)
	{
		for (int i = 0; i < carrotBullets.size();)
		{
			carrotBullets[i].move(0, bulletSpeed);
			if (carrotBullets[i].getPosition().y >= ground_Level1 + 150)
			{
				carrotBullets.erase(carrotBullets.begin() + i);
				smallCarrotDeathSound.play();
			}
			else
				i++;
		}
	}

	void update(vector<BulletSt>& currentBullets, PlayerSt_Level1& player, Clock startLevelClock, int startTime, bool& winning)
	{
		// Phase 1
		if (currentPhase == 1 && startLevelClock.getElapsedTime().asMilliseconds() >= startTime - startTime / 4)
		{
			bulletHitBoss(currentBullets, player);
			elapsedTime = fadetimer.getElapsedTime().asMilliseconds();
			if (elapsedTime > 50)
			{
				EnemyColor.a = 255; // Reset the alpha component to 255
				boss.setColor(EnemyColor);
				fadetimer.restart();
			}

			potatoBulletUpdate();
			potatoBulletHitPlayer(player, winning);

			if (!earthBreak)
			{
				if (!potatoGroundSoundPlayed)
				{
					potatoGroundSoundPlayed = true;
					potatoGroundSound.play();
				}

				earthCurrentTexture = earthBreak_Level1Tex;
				updateSubRect2D(earthRect, earthCurrentTexture, 5, 4, earthFrameX, earthFrameY);
				earth.setTexture(earthCurrentTexture);
				earth.setTextureRect(earthRect);
				earth.setScale(1.4, 1.4);
				earth.setPosition(window.getSize().x - earth.getLocalBounds().width - 325, ground_Level1 - earth.getLocalBounds().height + 100);

				earthFrameX += 0.1;

				if (earthFrameX >= 3 && earthFrameY >= 1)
					bossSpawnStart = true;

				if (earthFrameX >= 5 && earthFrameY >= 3)
					earthBreak = true;

				if (earthFrameX >= 5)
				{
					earthFrameX = 0;
					earthFrameY++;
				}
			}

			if (bossSpawnStart && !bossSpawn)
			{
				bossCurrentTexture = potatoSpawn_Level1Tex;
				updateSubRect2D(bossRect, bossCurrentTexture, 6, 4, bossFrameX, bossFrameY);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.8, 1.8);
				boss.setPosition(earth.getPosition().x, ground_Level1 - boss.getLocalBounds().height - 100);

				bossFrameX += 0.1;


				if (bossFrameX >= 2 && bossFrameY >= 3)
				{
					bossSpawn = true;
					bossFrameX = 0;
					bossFrameY = 0;
				}
				if (bossFrameX >= 6)
				{
					bossFrameX = 0;
					bossFrameY++;
				}
			}
			if (bossSpawn && !dead)
			{
				bossCurrentTexture = potatoAttack_Level1Tex;
				updateSubRect2D(bossRect, bossCurrentTexture, 6, 3, bossFrameX, bossFrameY);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.8, 1.8);
				boss.setPosition(earth.getPosition().x, ground_Level1 - boss.getLocalBounds().height - 100);

				bossFrameX += 0.13;


				if (bossFrameX >= 4 && bossFrameY == 1 && startShooting)
				{
					potatoBullet_Level1 bossBullet;
					updateSubRect(bossBullet.subRect, potatoBullet_Level1Tex, 8, 0);

					bossBullet.bullet.setTexture(potatoBullet_Level1Tex);
					bossBullet.bullet.setTextureRect(bossBullet.subRect);
					bossBullet.bullet.setScale(1.4, 1.4);
					bossBullet.bullet.setPosition(boss.getPosition().x - 50, boss.getPosition().y + 580);
					bossBullets.push_back(bossBullet);
					potatoSpitSound.play();
					startShooting = false;
				}

				if (bossFrameX >= 6)
				{
					bossFrameX = 0;
					bossFrameY++;
				}
				if (bossFrameX >= 5 && bossFrameY >= 2)
				{
					bossFrameX = 0;
					bossFrameY = 0;
					startShooting = true;
				}
			}
			if (health <= 0)
			{
				bossCurrentTexture = potatoDeath_Level1Tex;
				updateSubRect(bossRect, bossCurrentTexture, 9, bossFrameX);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.8, 1.8);

				bossFrameX += 0.1;
				if (bossFrameX >= 9)
					bossFrameX = 0;
				boss.move(3, 0);

				dead = true;

				if (boss.getPosition().x >= window.getSize().x + 500)
				{
					setup();
					carrotGroundSound.play();
					currentPhase = 2;
				}
			}
		}

		// Phase 2
		else if (currentPhase == 2)
		{
			bulletHitBoss(currentBullets, player);
			elapsedTime = fadetimer.getElapsedTime().asMilliseconds();
			if (elapsedTime > 50)
			{
				EnemyColor.a = 255; // Reset the alpha component to 255
				boss.setColor(EnemyColor);
				fadetimer.restart();
			}

			carrotRingsUpdate();
			carrotRingsHitPlayer(player, winning);

			carrotBulletsUpdate(player.playerSprite.getPosition());
			carrotBulletsHitPlayer(player, winning);

			if (!earthBreak)
			{
				earthCurrentTexture = earthBreak_Level1Tex;
				updateSubRect2D(earthRect, earthCurrentTexture, 5, 4, earthFrameX, earthFrameY);
				earth.setTexture(earthCurrentTexture);
				earth.setTextureRect(earthRect);
				earth.setScale(1.2, 1.2);
				earth.setPosition(window.getSize().x * 0.4 - earth.getLocalBounds().width * 0.3, ground_Level1 - earth.getLocalBounds().height + 20);

				earthFrameX += 0.1;

				if (earthFrameX >= 3 && earthFrameY >= 1)
					bossSpawnStart = true;

				if (earthFrameX >= 5 && earthFrameY >= 3)
					earthBreak = true;

				if (earthFrameX >= 5)
				{
					earthFrameX = 0;
					earthFrameY++;
				}
			}

			if (bossSpawnStart && !bossSpawn)
			{
				bossCurrentTexture = carrotSpawn_Level1Tex;
				updateSubRect2D(bossRect, bossCurrentTexture, 8, 4, bossFrameX, bossFrameY);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.5, 1.5);
				boss.setPosition(earth.getPosition().x - boss.getLocalBounds().width * 0.22, ground_Level1 - boss.getLocalBounds().height - 210);
				bossFrameX += 0.1;


				if (bossFrameX >= 1 && bossFrameY >= 3)
				{
					bossSpawn = true;
					bossFrameX = 0;
					bossFrameY = 0;
				}
				if (bossFrameX >= 8)
				{
					bossFrameX = 0;
					bossFrameY++;
				}
			}
			if (bossSpawn && carrotAttack < 4 && !dead)
			{
				bossCurrentTexture = carrotAttack_Level1Tex;
				updateSubRect2D(bossRect, bossCurrentTexture, 10, 3, bossFrameX, bossFrameY);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.5, 1.5);
				boss.setPosition(earth.getPosition().x - boss.getLocalBounds().width * 0.22 + 50, ground_Level1 - boss.getLocalBounds().height - 150);
				bossFrameX += 0.1;

				if (bossFrameX >= 10)
				{
					bossFrameX = 0;
					bossFrameY++;

					Sprite bullet(carrotBullet_level1Tex);
					bullet.setScale(1.5, 1.5);

					bullet.setPosition(rand() % window.getSize().x, -bullet.getLocalBounds().height);
					carrotBullets.push_back(bullet);
					bullet.setPosition(rand() % window.getSize().x, -bullet.getLocalBounds().height);
					carrotBullets.push_back(bullet);
				}
				if (bossFrameX >= 2 && bossFrameY >= 2)
				{
					bossFrameX = 0;
					bossFrameY = 0;
					carrotAttack++;
				}
				carrotRingSoundPlayed = false;
			}
			if (bossSpawn && carrotAttack >= 4 && !dead)
			{
				if (!carrotRingSoundPlayed)
				{
					carrotRingsSound.play();
					carrotRingsSound.setLoop(true);
					carrotRingSoundPlayed = true;
				}
				bossCurrentTexture = carrotAttack2_level1Tex;
				updateSubRect2D(bossRect, bossCurrentTexture, 10, 2, bossFrameX, bossFrameY);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.5, 1.5);
				boss.setPosition(earth.getPosition().x - boss.getLocalBounds().width * 0.22 + 50, ground_Level1 - boss.getLocalBounds().height - 210);
				bossFrameX += 0.1;

				if (bossFrameX >= 7 && bossFrameY == 0 && startShootingRing[0])
				{
					carrotRings ring;
					updateSubRect(ring.ringRect, carrotRings_Level1Tex, 9, 0);
					ring.ring.setTexture(carrotRings_Level1Tex);
					ring.ring.setTextureRect(ring.ringRect);
					ring.ring.setScale(1.4, 1.4);
					ring.ring.setPosition(boss.getPosition().x + boss.getLocalBounds().width / 2 - ring.ring.getLocalBounds().width / 2 + 130, boss.getPosition().y + 170);

					bossEyeRing.x = ring.ring.getPosition().x;
					bossEyeRing.y = ring.ring.getPosition().y;
					if (player.playerSprite.getPosition().x < boss.getPosition().x)
						directionRing = Vector2f(player.playerSprite.getPosition().x - bossEyeRing.x, player.playerSprite.getPosition().y - bossEyeRing.y);
					else
						directionRing = Vector2f(player.playerSprite.getPosition().x + player.playerSprite.getLocalBounds().width - bossEyeRing.x, player.playerSprite.getPosition().y - bossEyeRing.y);

					lengthRing = sqrt(directionRing.x * directionRing.x + directionRing.y * directionRing.y);

					moveXRing = (directionRing.x / lengthRing) * ringSpeed;
					moveYRing = (directionRing.y / lengthRing) * ringSpeed;

					ring.moveX = moveXRing;
					ring.moveY = moveYRing;

					rings.push_back(ring);

					startShootingRing[0] = false;
				}
				if (bossFrameX >= 0 && bossFrameY == 1 && startShootingRing[1])
				{
					carrotRings ring;
					ring.moveX = moveXRing;
					ring.moveY = moveYRing;

					updateSubRect(ring.ringRect, carrotRings_Level1Tex, 9, 0);

					ring.ring.setTexture(carrotRings_Level1Tex);
					ring.ring.setTextureRect(ring.ringRect);
					ring.ring.setScale(1.4, 1.4);
					ring.ring.setPosition(boss.getPosition().x + boss.getLocalBounds().width / 2 - ring.ring.getLocalBounds().width / 2 + 130, boss.getPosition().y + 170);
					rings.push_back(ring);

					startShootingRing[1] = false;
				}
				if (bossFrameX >= 3 && bossFrameY == 1 && startShootingRing[2])
				{
					carrotRings ring;
					ring.moveX = moveXRing;
					ring.moveY = moveYRing;

					updateSubRect(ring.ringRect, carrotRings_Level1Tex, 9, 0);

					ring.ring.setTexture(carrotRings_Level1Tex);
					ring.ring.setTextureRect(ring.ringRect);
					ring.ring.setScale(1.4, 1.4);
					ring.ring.setPosition(boss.getPosition().x + boss.getLocalBounds().width / 2 - ring.ring.getLocalBounds().width / 2 + 130, boss.getPosition().y + 170);
					rings.push_back(ring);

					startShootingRing[2] = false;
				}
				if (bossFrameX >= 6 && bossFrameY == 1 && startShootingRing[3])
				{
					carrotRings ring;
					ring.moveX = moveXRing;
					ring.moveY = moveYRing;

					updateSubRect(ring.ringRect, carrotRings_Level1Tex, 9, 0);

					ring.ring.setTexture(carrotRings_Level1Tex);
					ring.ring.setTextureRect(ring.ringRect);
					ring.ring.setScale(1.4, 1.4);
					ring.ring.setPosition(boss.getPosition().x + boss.getLocalBounds().width / 2 - ring.ring.getLocalBounds().width / 2 + 130, boss.getPosition().y + 170);
					rings.push_back(ring);

					startShootingRing[3] = false;
				}


				if (bossFrameX >= 10)
				{
					bossFrameX = 0;
					bossFrameY++;
				}
				if (bossFrameX >= 8 && bossFrameY >= 1)
				{
					bossFrameX = 0;
					bossFrameY = 0;
					carrotAttack++;
					startShootingRing[0] = true;
					startShootingRing[1] = true;
					startShootingRing[2] = true;
					startShootingRing[3] = true;
				}
			}
			if (carrotAttack >= 10)
				carrotAttack = 0;
			if (health <= 0)
			{
				carrotRingsSound.stop();
				bossCurrentTexture = carrotDeath_Level1Tex;
				updateSubRect(bossRect, bossCurrentTexture, 13, bossFrameX);
				boss.setTexture(bossCurrentTexture);
				boss.setTextureRect(bossRect);
				boss.setScale(1.8, 1.8);

				if (!deathFrame)
					bossFrameX += 0.1;
				else
					bossFrameX -= 0.1;

				if (bossFrameX >= 13)
					deathFrame = true;
				else if (bossFrameX <= 0)
					deathFrame = false;

				dead = true;
			}
		}
	}
	void draw()
	{
		window.draw(boss);
		window.draw(earth);

		for (int i = 0; i < bossBullets.size(); i++)
			window.draw(bossBullets[i].bullet);
	}
};

/* Level 2 Structres */
// Player
struct PlayerSt_Level2
{
	// Player
	Sprite playerSprite;
	float moveX, moveY, runFrame, jumpFrame, shootUpFrame, standFrame;
	int lastKeyPressed; // to show the last Position if it is right or left, ( 1 : right , 2 : left )
	float positionX, positionY;
	Texture currentTexture; // set the current move
	IntRect subRect; // to Set All Textures We Want
	bool onGround, standIncreasingFrame;

	// Level 2
	float standingSpeed;
	bool isFalling;
	bool isCrawling;
	float crawlFrame;

	// Player Hp
	HpBarSt hp;
	// Player Death
	GhostSt ghost;

	// Shoot 
	vector<BulletSt> bullets;
	float const shootSpeed = 11;
	float shootCooldown;
	// Hit Animation
	bool hitAnimation;
	float hitFrame;

	// Sounds
	Sound jumpSound, hitSound, shootSound;

	void updateSubRectDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		if (lastKeyPressed == 2)
		{
			subRect.left += size.x / photosNumber;
			photosNumber *= -1;
		}
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	// inital Values of every thing
	void setup()
	{
		// player
		currentTexture = playerStandingTex;
		positionX = playerSprite.getPosition().x, positionY = playerSprite.getPosition().y;
		playerSprite.setTexture(currentTexture);
		playerSprite.setPosition(0, ground_Level2);
		playerSprite.setScale(0.9, 0.9);
		lastKeyPressed = 1;
		moveX = 0, moveY = 0;
		runFrame = 0, jumpFrame = 0, shootUpFrame = 0, standFrame = 0;
		onGround = true;

		// Hp
		hp.hpSetup();
		// Death
		ghost.ghostSetup();
		// Shooting
		bullets.clear();
		shootCooldown = 170;
		// Level 2
		standingSpeed = -2.3;
		isFalling = false, isCrawling = false;
		crawlFrame = 0;
		// Hit
		hitFrame = 0;
		hitAnimation = false;

		// Sound
		jumpSound.setBuffer(playerJumpBuffer);
		jumpSound.setVolume(60);
		hitSound.setBuffer(playerHitBuffer);
		hitSound.setVolume(80);
		shootSound.setBuffer(playerShootBuffer);
		shootSound.setVolume(30);
	}
	// PLayer Move
	void moveRight()
	{
		lastKeyPressed = 1; // ( 1 : right , 2 : left )

		currentTexture = playerRunTex;
		moveX = 6.2;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);
	}
	void moveLeft()
	{
		lastKeyPressed = 2; // ( 1 : right , 2 : left )

		currentTexture = playerRunTex;
		moveX = -6.5;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);
	}
	void jumb()
	{
		if (!onGround)
			return;
		jumpSound.play();
		moveY = -14.5;
		onGround = false;
	}
	void playerHit()
	{
		currentTexture = playerHitTex;
		updateSubRectDirection(subRect, playerHitTex, 6, hitFrame);
		hitFrame += 0.1;
		if (hitFrame >= 6)
		{
			hitFrame = 0;
			hitAnimation = false;
		}
	}

	// Player Shoot Moving && Bullets
	void shootStraight(Clock& shootClock)
	{
		// Player
		currentTexture = playerShootStraightTex;
		updateSubRectDirection(subRect, currentTexture, 6.0, shootUpFrame);

		shootUpFrame += 0.25;
		if (shootUpFrame >= 6)
			shootUpFrame -= 6;

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;
		// Sound
		shootSound.play();

		shootClock.restart();

		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(straightBulletTex);
		currentBullet.moveX = shootSpeed;

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 140, positionY - 60);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 140, positionY + 70);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 305, positionY - 60);
			currentBullet.moveX *= -1;

			auto size = straightBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX - 15, positionY + 70);
		}
		bullets.push_back(currentBullet);
	}
	void shootRunStraight(Clock& shootClock) {

		currentTexture = playerRunShootStraightTex;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;

		// Sound
		shootSound.play();
		shootClock.restart();

		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(straightBulletTex);

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 120, positionY - 45);
			currentBullet.moveX = (shootSpeed + 3);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 165, positionY + 85);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 320, positionY - 45);
			currentBullet.moveX = (shootSpeed + 3) * -1;

			auto size = straightBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX - 50, positionY + 85);
		}

		bullets.push_back(currentBullet);
	}
	void shootRunDiagonalUp(Clock& shootClock) {
		// Player
		currentTexture = playerRunDiagonalUpTex;
		updateSubRectDirection(subRect, currentTexture, 16.0, runFrame);

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;

		// Sound
		shootSound.play();
		shootClock.restart();

		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(diagonalUpBulletTex);
		currentBullet.moveX = shootSpeed;
		currentBullet.moveY = -1 * shootSpeed;

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 10, positionY - 350);
			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 160, positionY);
		}
		else if (lastKeyPressed == 2)
		{
			currentBullet.bulletSprite.setPosition(positionX - 200, positionY - 350);
			currentBullet.moveX *= -1;

			auto size = diagonalUpBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX - 50, positionY);
		}
		currentBullet.bulletSprite.setScale(1.2, 1.2);

		bullets.push_back(currentBullet);
	}
	void shootUp(Clock& shootClock)
	{
		// Player
		currentTexture = playerShootUpTex;
		updateSubRectDirection(subRect, currentTexture, 6.0, shootUpFrame);
		shootUpFrame += 0.25;
		if (shootUpFrame >= 6)
			shootUpFrame -= 6;

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;

		// Sound
		shootSound.play();
		shootClock.restart();

		// Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(upBulletTex);
		currentBullet.moveY = -1 * shootSpeed;

		currentBullet.spawnSetup();


		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 20, positionY - 325);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 100, positionY - 37);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 100, positionY - 325);

			auto size = upBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 20, positionY - 37);
		}

		bullets.push_back(currentBullet);
	}
	void shootCrawling(Clock& shootClock)
	{
		isCrawling = true;
		if (isFalling)
			return;
		//player
		currentTexture = playerCrawlTex;
		updateSubRectDirection(subRect, currentTexture, 6.0, crawlFrame);

		crawlFrame += 0.25;
		if (crawlFrame >= 6)
			crawlFrame -= 6;

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;

		// Sound
		shootSound.play();
		shootClock.restart();

		//Shooting
		BulletSt currentBullet;

		currentBullet.bulletSprite.setTexture(straightBulletTex);
		currentBullet.moveX = shootSpeed;

		currentBullet.spawnSetup();

		if (lastKeyPressed == 1)
		{
			currentBullet.bulletSprite.setPosition(positionX - 140, positionY + 5);

			// spawn
			currentBullet.spawnSprite.setPosition(positionX + 135, positionY + 135);
		}
		else
		{
			currentBullet.bulletSprite.setPosition(positionX - 335, positionY + 10);
			currentBullet.moveX *= -1;

			auto size = straightBulletTex.getSize();
			currentBullet.bulletSprite.setTextureRect(IntRect(size.x, 0, -1 * size.x, size.y));

			// spawn
			// 95
			currentBullet.spawnSprite.setPosition(positionX - 45, positionY + 135);
		}
		bullets.push_back(currentBullet);
	}

	void update(int currentPhase, bool winning)
	{
		// re scale the player
		playerSprite.setScale(0.9, 0.9);

		// Death 
		if (hp.lives <= 0)
		{
			ghost.death(currentTexture, playerSprite, moveY, lastKeyPressed);
			ghost.isDead = true;

			// Clear Bullets
			if (bullets.size())
				bullets.clear();
			return;
		}
		// Timer Starts From Death Time
		ghost.deathClock.restart();
		// Standing Position
		// moveX -> 0 or -2.3 ,  0 -> for standing ,  -2.3 -> if he is on the cloud
		if (isCrawling)
		{
			moveX = standingSpeed;
			moveY = 0;
		}
		else if ((moveX == standingSpeed || moveX == 0) && onGround && !(Mouse::isButtonPressed(Mouse::Left)))
		{
			currentTexture = playerStandingTex;
			updateSubRectDirection(subRect, currentTexture, 5, standFrame);

			if (standFrame <= 0.08)
				standIncreasingFrame = true;
			if (standFrame >= 4.92)
				standIncreasingFrame = false;

			if (standIncreasingFrame)
				standFrame += 0.08;
			else
				standFrame -= 0.08;
		}
		// Jumping
		else if (!onGround)
		{
			currentTexture = playerJumpTex;
			updateSubRectDirection(subRect, currentTexture, 8, jumpFrame);

			if (isFalling)
				moveY += 0.15;
			else
				moveY += 0.4;
			playerSprite.setScale(0.65, 0.65);

			jumpFrame += 0.25;
			if (jumpFrame >= 8)
				jumpFrame -= 8;
		}
		// Player Falling
		if (positionY >= ground_Level2)
		{
			// if he Fall And Die , The Animation Of The Ghost Happen From Down , to See It

			if (hp.lives > 1)
				playerSprite.setPosition(positionX, 0);
			moveY = 0; // 1
			// Decrement The Lives
			hp.isHit = true;
			isFalling = true;
		}
		if (hitAnimation)
		{
			playerHit();
		}

		playerSprite.setTexture(currentTexture);
		playerSprite.setTextureRect(subRect);

		if (currentPhase == 1)
		{
			if (positionX <= leftWall && moveX < 0)
				moveX = 0;
			if (positionX >= windowSizeX - 500 && moveX > 0)
				moveX = 0;
		}
		else
		{
			if (positionX <= leftWall + 300 && moveX < 0)
				moveX = 0;
			if (positionX >= windowSizeX - 170 && moveX > 0)
				moveX = 0;
		}

		playerSprite.move(moveX, moveY);
		runFrame += 0.25;
		if (runFrame >= 16)
			runFrame -= 16;

		// Bullets Moving
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].bulletSprite.move(bullets[i].moveX, bullets[i].moveY);
			// spawn
			if (bullets[i].spawnFrame >= 4)
			{
				bullets[i].isSpawning = false;
			}
			if (bullets[i].isSpawning)
			{
				bullets[i].spawnFrame += 0.4;
				updateSubRectDirection(bullets[i].spawnSubRect, spawnTex, 4.0, bullets[i].spawnFrame);
				bullets[i].spawnSprite.setTextureRect(bullets[i].spawnSubRect);
			}

			if (bullets[i].bulletHitBoss)
			{
				bullets[i].bulletSprite.setTexture(bulletDeathTex);
				updateSubRectNoDirection(bullets[i].bulletDeathSubRect, bulletDeathTex, 6, bullets[i].bulletDeathFrame);
				bullets[i].bulletSprite.setTextureRect(bullets[i].bulletDeathSubRect);
				bullets[i].bulletSprite.setScale(1.7, 1.7);
				bullets[i].bulletDeathFrame += 0.2;

				bullets[i].moveX = 0;
				bullets[i].moveY = 0;
			}

			if (bullets[i].bulletSprite.getPosition().x >= rightWall || bullets[i].bulletSprite.getPosition().x <= leftWall - 300
				|| bullets[i].bulletSprite.getPosition().y <= -400 || bullets[i].bulletDeathFrame >= 6)
			{
				bullets.erase(bullets.begin() + i);
			}
		}

		// Hp
		if (hp.isHit && !winning)
		{
			hp.getHit();
			hitSound.play();
			hitFrame = 0;
			hitAnimation = true;
		}
		if (hp.lives == 1)
		{
			hp.oneLiveAnimation();
		}

		moveX = 0;
		hp.isHit = false;
		isCrawling = false;
		positionX = playerSprite.getPosition().x;
		positionY = playerSprite.getPosition().y;
	}
	void draw()
	{
		window.draw(playerSprite);
		window.draw(hp.hpSprite);
		if (ghost.isDead)
		{
			if (ghost.deathClock.getElapsedTime().asMilliseconds() <= 3000 && ghost.deathClock.getElapsedTime().asMilliseconds() >= 500)
				window.draw(ghost.youDiedSprite);
		}
	}
};
// BackGround
struct BackgroundSt_Level2
{
	Sprite backgroundSprite[3];
	Texture currentTexture;
	IntRect subRect;
	bool isLightning = false;
	int darkBackgroundFrame = 0;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		currentTexture = lightBackgroundTex_Level2;
		updateSubRectNoDirection(subRect, currentTexture, 1, 0);
		backgroundSprite[0].setPosition(0, 0);
		backgroundSprite[1].setPosition(1 * windowSizeX - 2, 0);
		backgroundSprite[2].setPosition(2 * windowSizeX - 4, 0);
	}

	void update()
	{
		updateSubRectNoDirection(subRect, currentTexture, 1, 0);
		for (int i = 0; i < 3; i++)
		{
			backgroundSprite[i].setTexture(currentTexture);
			backgroundSprite[i].setTextureRect(subRect);
			backgroundSprite[i].setScale(windowSizeX / backgroundSprite[i].getLocalBounds().width,
				windowSizeY / backgroundSprite[i].getLocalBounds().height);
			if (backgroundSprite[i].getPosition().x >= 1 * windowSizeX)
			{
				int lastBackground = (i + 2) % 3; // to get The last Background
				float lastBackgroundPositionX = backgroundSprite[lastBackground].getPosition().x;
				backgroundSprite[i].setPosition(lastBackgroundPositionX - windowSizeX - 2, 0);
			}
			backgroundSprite[i].move(1.2, 0);
		}
	}

	void draw()
	{
		for (int i = 0; i < 3; i++)
			window.draw(backgroundSprite[i]);
	}
};
struct TowerSt_Level2
{
	Sprite towerSprite;
	IntRect subRect;
	float towerFrameX, towerFrameY;
	bool isDark;
	void updateSubRect2D(IntRect& subRect, Texture& currentTexture, float numberX, float numberY, float frameX, float frameY)
	{
		// 13 Rows , 14 Columns -> (numberX -> 14 , numberY -> 13)
		auto size = currentTexture.getSize();

		subRect.left = size.x / numberX * int(frameX);
		subRect.top = size.y / numberY * int(frameY);
		subRect.width = size.x / numberX;
		subRect.height = size.y / numberY;
	}

	void setup()
	{
		towerFrameX = 0, towerFrameY = 0;
		towerSprite.setTexture(lightTowerTex_Level2);
		towerSprite.setScale(1.2, 1.2);
		towerSprite.setPosition(windowSizeX / 2.0 - lightTowerTex_Level2.getSize().x / 14.0 / 2.0 - 30, -30);
		isDark = false;
	}
	void update()
	{
		updateSubRect2D(subRect, lightTowerTex_Level2, 14, 13, towerFrameX, towerFrameY);
		towerSprite.setTextureRect(subRect);
		towerFrameX += 0.1;
		if (towerFrameX >= 14)
		{
			towerFrameX = 0;
			towerFrameY++;
		}
		if (towerFrameX >= 11 && towerFrameY >= 12)
		{
			towerFrameX = 0, towerFrameY = 0;
		}
	}
	void draw()
	{
		window.draw(towerSprite);
	}
};
struct OneMidCloudSt_Level2
{
	Sprite cloudSprite;
	float cloudIdleFrame, cloudeStandingFrame;
	Texture currentTexture;
	IntRect subRect;
	float moveX;
	bool isStanding;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		currentTexture = midCloudIdleTex_Level2;
		cloudSprite.setTexture(currentTexture);
		cloudSprite.setScale(1.5, 1.5);
		moveX = -2.3;
		cloudIdleFrame = 0, cloudeStandingFrame = 0;
		isStanding = false;
	}
	void update()
	{
		if (isStanding)
		{
			cloudIdleFrame = 0;
			currentTexture = midCloudStandingTex_Level2;
			updateSubRectNoDirection(subRect, currentTexture, 7, cloudeStandingFrame);

			if (cloudeStandingFrame <= 6)
				cloudeStandingFrame += 0.3;
		}
		else
		{
			// First Return to The normal Position
			if (cloudeStandingFrame > 0)
				cloudeStandingFrame -= 0.3;
			if (cloudeStandingFrame <= 0)
			{
				cloudeStandingFrame = 0;
				currentTexture = midCloudIdleTex_Level2;
				updateSubRectNoDirection(subRect, currentTexture, 3, cloudIdleFrame);

				cloudIdleFrame += 0.05;
				if (cloudIdleFrame >= 3)
					cloudIdleFrame -= 3;
			}
			else
			{
				updateSubRectNoDirection(subRect, currentTexture, 7, cloudeStandingFrame);
			}
		}
		cloudSprite.setTexture(currentTexture);
		cloudSprite.setTextureRect(subRect);
		cloudSprite.move(moveX, 0);
	}

	void draw()
	{
		window.draw(cloudSprite);
	}
};
struct MidCloudsSt_Level2
{
	vector<OneMidCloudSt_Level2> clouds;
	Clock topCloudsClock, midCloudsClock, bottomCloudsClock;
	// top -> every 2.5 sec , mid -> every 3.5 sec , bottom -> every 2 sec 
	void cloudCollision(PlayerSt_Level2& player)
	{
		bool isPlayerOnCloud = false;
		for (auto& currentCloud : clouds)
		{
			int cloudPosX = currentCloud.cloudSprite.getPosition().x;
			int cloudPosY = currentCloud.cloudSprite.getPosition().y;

			if (player.playerSprite.getGlobalBounds().intersects(currentCloud.cloudSprite.getGlobalBounds()) && player.moveY >= 0
				&& player.positionY + 100 <= currentCloud.cloudSprite.getPosition().y &&
				player.positionX + 75 >= cloudPosX && player.positionX <= cloudPosX + 265)
			{
				currentCloud.isStanding = true;
				isPlayerOnCloud = true;
				player.moveY = 0;
				player.moveX = currentCloud.moveX;
				player.isFalling = false;
			}
			else
			{
				currentCloud.isStanding = false;
			}
		}
		player.onGround = isPlayerOnCloud;
	}
	void setFirstElements()
	{
		int x = 10;
		for (int i = 0; i < 3; i++)
		{
			OneMidCloudSt_Level2 cloud;
			cloud.setup();

			cloud.cloudSprite.setPosition(x + randomNumber(100, 200), randomNumber(200, 350));
			clouds.push_back(cloud);
			cloud.cloudSprite.setPosition(x + randomNumber(100, 200), randomNumber(450, 500));
			clouds.push_back(cloud);
			cloud.cloudSprite.setPosition(x + randomNumber(100, 200), randomNumber(700, 800));
			clouds.push_back(cloud);
			x += 500;
		}

	}

	void update(PlayerSt_Level2& player, Clock& startLevelClock, int startingTime)
	{
		if (topCloudsClock.getElapsedTime().asMilliseconds() >= 2100)
		{
			topCloudsClock.restart();
			OneMidCloudSt_Level2 cloud;
			cloud.setup();
			cloud.cloudSprite.setPosition(windowSizeX, randomNumber(250, 350));
			clouds.push_back(cloud);
		}
		if (midCloudsClock.getElapsedTime().asMilliseconds() >= 5000)
		{
			midCloudsClock.restart();
			OneMidCloudSt_Level2 cloud;
			cloud.setup();
			cloud.cloudSprite.setPosition(windowSizeX, randomNumber(450, 550));
			clouds.push_back(cloud);
		}
		if (bottomCloudsClock.getElapsedTime().asMilliseconds() >= 2000)
		{
			bottomCloudsClock.restart();
			OneMidCloudSt_Level2 cloud;
			cloud.setup();
			cloud.cloudSprite.setPosition(windowSizeX, randomNumber(650, 850));
			clouds.push_back(cloud);
		}

		cloudCollision(player);
		for (int i = 0; i < clouds.size(); i++)
		{
			if (startLevelClock.getElapsedTime().asMilliseconds() <= startingTime)
			{
				clouds[i].moveX = 0;
			}
			else
				clouds[i].moveX = -2.3;

			clouds[i].update();
			if (clouds[i].cloudSprite.getPosition().x <= 0 - midCloudIdleTex_Level2.getSize().x / 3.0 - 100)
				clouds.erase(clouds.begin() + i);
		}
	}

	void draw()
	{
		for (auto& cloud : clouds)
			cloud.draw();
	}
};
struct cloud_foreground_Level2 {
	Sprite cloud_sprite;
	IntRect subRect;
	Texture currentTexture;
	float moveX = 0;
	Clock cloudClock;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		currentTexture = cloudForegroundLightTex_Level2;
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		cloud_sprite.setTexture(cloudForegroundLightTex_Level2);
		moveX = -2;
		updateSubRectNoDirection(subRect, currentTexture, 3, randomNumber(0, 2)); // random from any of the three clouds
		cloud_sprite.setTextureRect(subRect);
		cloud_sprite.setPosition(windowSizeX, windowSizeY - 170);
	}
};
struct cloud_st_foreground_Level2
{
	vector< cloud_foreground_Level2>clouds;
	cloud_foreground_Level2 cloud;
	void update()
	{
		if (clouds.size() <= 3 && clouds.size() <= cloud.cloudClock.getElapsedTime().asSeconds())
		{
			cloud.setup();
			clouds.push_back(cloud);
			cloud.cloudClock.restart();
		}
		for (int i = 0; i < clouds.size(); i++)
		{
			clouds[i].cloud_sprite.move(cloud.moveX, 0);
			if (clouds[i].cloud_sprite.getPosition().x <= 0 - cloudForegroundLightTex_Level2.getSize().x / 3.0 - 100)
				clouds.erase(clouds.begin() + i);
		}
	}
	void draw()
	{
		for (int i = 0; i < clouds.size(); i++)
			window.draw(clouds[i].cloud_sprite);
	}
};
struct cloud_background_Level2 {
	Sprite cloud_sprite;
	IntRect subRect;
	Texture currentTexture;
	float moveX = -1;
	Clock cloudClock;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		currentTexture = cloudbackgroundLightTex_Level2;
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		cloud_sprite.setTexture(cloudbackgroundLightTex_Level2);

		moveX = 0;
		updateSubRectNoDirection(subRect, currentTexture, 5, randomNumber(0, 2));
		cloud_sprite.setTextureRect(subRect);
		cloud_sprite.setScale(0.8, 0.8);
		cloud_sprite.setPosition(-1 * windowSizeX, randomNumber(0, 800));
	}
};
struct cloud_st_background_Level2
{
	vector<cloud_background_Level2>clouds;
	cloud_background_Level2 cloud;
	void update()
	{
		if (clouds.size() <= 10 && clouds.size() <= cloud.cloudClock.getElapsedTime().asSeconds() + 3)
		{
			cloud.setup();
			clouds.push_back(cloud);
			cloud.cloudClock.restart();
		}
		for (int i = 0; i < clouds.size(); i++)
		{
			clouds[i].cloud_sprite.move(randomNumber(10, 14) * 0.1, 0);
			if (clouds[i].cloud_sprite.getPosition().x >= cloudbackgroundLightTex_Level2.getSize().x / 5.0 + 100)
				clouds.erase(clouds.begin() + i);
		}
	}
	void draw()
	{
		for (int i = 0; i < clouds.size(); i++)
			window.draw(clouds[i].cloud_sprite);
	}
};
// Phase 1
struct fireBallSt_Level2
{
	Sprite fireBallSprite;
	IntRect subRect;
	float ballFrame, moveX, moveY;
	bool goTop;
	bool hitCuphead;
	float positionX, positionY;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	void setup()
	{
		fireBallSprite.setTexture(fireBallTex_Level2);
		ballFrame = 0;
		moveX = -4.3, moveY = 0;
		updateSubRectNoDirection(subRect, fireBallTex_Level2, 8, ballFrame);
		fireBallSprite.setTextureRect(subRect);
		fireBallSprite.setScale(1.3, 1.3);
		hitCuphead = false;
		positionX = fireBallSprite.getPosition().x;
		positionY = fireBallSprite.getPosition().y;
	}
	void update()
	{
		positionX = fireBallSprite.getPosition().x;
		positionY = fireBallSprite.getPosition().y;
		updateSubRectNoDirection(subRect, fireBallTex_Level2, 8, ballFrame);
		fireBallSprite.setTextureRect(subRect);

		ballFrame += 0.1;
		if (ballFrame >= 8)
			ballFrame -= 8;

		if (fireBallSprite.getPosition().y <= 0)
		{
			goTop = false;
			moveY = 1.5;
		}
		if (fireBallSprite.getPosition().y >= 800)
		{
			goTop = true;
			moveY = -1.5;
		}

		if (goTop)
			moveY -= 0.1;
		else
			moveY += 0.1;

		fireBallSprite.move(moveX, moveY);
	}

	void draw()
	{
		window.draw(fireBallSprite);
	}
};
struct oneRingSt_Level2
{
	Sprite ringSprite;
	IntRect subRect;
	float ringFrame;
	float moveX, moveY;
	float positionX, positionY;
	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	void setup()
	{
		ringFrame = 0;
		ringSprite.setTexture(ringTex_Level2);
		updateSubRectNoDirection(subRect, ringTex_Level2, 8, ringFrame);
		ringSprite.setTextureRect(subRect);
		ringSprite.setScale(1.3, 1.3);
		positionX = ringSprite.getPosition().x;
		positionY = ringSprite.getPosition().y;
	}
	void update()
	{
		positionX = ringSprite.getPosition().x;
		positionY = ringSprite.getPosition().y;
		updateSubRectNoDirection(subRect, ringTex_Level2, 8, ringFrame);
		ringSprite.setTextureRect(subRect);

		ringFrame += 0.2;
		if (ringFrame >= 8)
			ringFrame = 0;

		ringSprite.move(moveX, moveY);
	}

	void draw()
	{
		window.draw(ringSprite);
	}
};
struct eyesAttackSt_Level2
{
	Sprite eyesAttackSprite;
	float eyesFrame;
	IntRect subRect;
	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	void setup()
	{
		eyesAttackSprite.setTexture(eyesAttackTex_Level2);
		eyesFrame = 0;
		eyesAttackSprite.setScale(1.4, 1.4);
	}
	void update(float dragonPosX)
	{
		updateSubRectNoDirection(subRect, eyesAttackTex_Level2, 11, eyesFrame);
		eyesAttackSprite.setTextureRect(subRect);
		eyesAttackSprite.setPosition(dragonPosX + 390, 170);
		eyesFrame += 0.05;
		if (eyesFrame >= 11)
			eyesFrame -= 11;
	}
	void draw()
	{
		window.draw(eyesAttackSprite);
	}
};
struct DragonPhaseOne_Level2
{
	Sprite dragonSprite;
	Texture currentTexture;
	IntRect subRect;
	int health = 1400;
	float introFrameX = 0, introFrameY = 0, idleFrame = 0;
	// When He Back From The Shooting Just Set It Once , BC if The Health Is ZERO He Will Movw
	bool setIdlePositionOnce = true;

	bool isPeashoot = true;

	// Meteor Shoot
	float meteorShootFrameX = 0;
	float meteorShootFrameY = 0;

	// FireBalls
	int currentBallIndex = 0; // if fireBallEnds = (3 -> nShoots) Then He Swap to rings Animation and fireBallEnds return To 0
	bool fireBallGo = true;
	fireBallSt_Level2 fireBall[4];

	// Rings
	int ringsEnds = 0; // if RingEnds = (2 -> nShoots) Then He Swap to Fire Ball Animation and ringEnds return To 0
	bool ringsBeforeStart = true;
	Clock ringClock;
	int lastRing = -1;
	oneRingSt_Level2 rings[3];
	float ringTime = 180;
	Vector2f direction;
	float ringShootFrameX = 0, ringShootFrameY = 0;
	bool ringAnimationEnds = false;
	bool inRingsAttackMode = false;
	bool isRingHitCupead = false;

	int idleTime = 2700;
	Clock idleClock;

	eyesAttackSt_Level2 eyesAttack;

	// Fade
	Color dragonColor = dragonSprite.getColor();
	Clock fadeTimer;

	// Sound
	bool isSetup = false;
	Sound dragonIdleSound, peashotStartSound, peashotEndSound;
	bool dragonIdleSoundPlayed = false, peashotStartSoundPlayed = false, peashotEndSoundPlayed = false;
	Sound peashotAttackSound[3];
	bool peashotAttackSoundPlayed[3]{}; // For 3 Rings

	Sound meteorStartSound[4], meteorAttackSound[4];

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRect2D(IntRect& subRect, Texture& currentTexture, float numberX, float numberY, float frameX, float frameY)
	{
		// 4 Rows , 10 Columns -> (numberX -> 10 , numberY -> 4)
		auto size = currentTexture.getSize();

		subRect.left = size.x / numberX * int(frameX);
		subRect.top = size.y / numberY * int(frameY);
		subRect.width = size.x / numberX;
		subRect.height = size.y / numberY;
	}

	void bulletHitBoss(vector<BulletSt>& currentBullets, int playerLives)
	{
		if (playerLives <= 0)
			return;
		for (auto& bullet : currentBullets)
		{
			auto bulletPos = bullet.bulletSprite.getPosition();
			auto dragonPos = dragonSprite.getPosition();
			if (bullet.bulletSprite.getGlobalBounds().intersects(dragonSprite.getGlobalBounds()) && bulletPos.x >= dragonPos.x + 100)
			{
				bullet.bulletHitBoss = true;
				if (bullet.decreaseBossHealth)
				{
					health -= 10 + DamageBought;
					dragonColor.a = 255 - 85;
					fadeTimer.restart();
				}
				bullet.decreaseBossHealth = false;
			}
		}
	}
	void ringHitCuphead(PlayerSt_Level2& player)
	{
		for (int i = 0; i < 3; i++)
		{
			if (player.playerSprite.getGlobalBounds().intersects(rings[i].ringSprite.getGlobalBounds())
				&& player.positionX >= rings[i].positionX - 105 && player.positionX <= rings[i].positionX + 55
				&& player.positionY >= rings[i].positionY - 180 && !isRingHitCupead)
			{
				if (player.isCrawling)
				{
					if (player.positionY <= rings[i].positionY + 40)
					{
						isRingHitCupead = true;
						player.hp.isHit = true;
					}
				}
				else
				{
					if (player.positionY <= rings[i].positionY + 160)
					{
						isRingHitCupead = true;
						player.hp.isHit = true;
					}
				}
			}
		}
	}
	void meteorHitCuphead(PlayerSt_Level2& player)
	{
		for (int i = 0; i < 4; i++)
		{
			if (player.playerSprite.getGlobalBounds().intersects(fireBall[i].fireBallSprite.getGlobalBounds())
				&& player.positionX >= fireBall[i].positionX - 110 && player.positionX <= fireBall[i].positionX + 180
				&& player.positionY >= fireBall[i].positionY - 165 && fireBall[i].hitCuphead == false)
			{
				if (player.isCrawling)
				{
					if (player.positionY <= fireBall[i].positionY + 100)
					{
						player.hp.isHit = true;
						fireBall[i].hitCuphead = true;
					}
				}
				else
				{
					if (player.positionY <= fireBall[i].positionY + 210)
					{
						player.hp.isHit = true;
						fireBall[i].hitCuphead = true;
					}
				}
			}
		}
	}

	void dragonIntro()
	{
		updateSubRect2D(subRect, dragonIntroTex_Level2, 10, 4.0, introFrameX, introFrameY);
		dragonSprite.setTexture(dragonIntroTex_Level2);

		introFrameX += 0.17;
		if (introFrameX >= 10)
		{
			introFrameX = 0;
			introFrameY++;
		}
		dragonSprite.setPosition((windowSizeX - 1100) - 150, -50);
	}
	void dragonIdle()
	{
		updateSubRectNoDirection(subRect, dragonIdleTex_Level2, 16.0, idleFrame);
		dragonSprite.setTexture(dragonIdleTex_Level2);

		idleFrame += 0.15;
		if (idleFrame >= 16)
			idleFrame -= 16;
		if (setIdlePositionOnce)
			dragonSprite.setPosition((windowSizeX - 1100) + 330, 50);
	}
	void dragonMeteorShoot()
	{
		updateSubRect2D(subRect, dragonMeteorShootTex_Level2, 8, 4, meteorShootFrameX, meteorShootFrameY);
		dragonSprite.setTexture(dragonMeteorShootTex_Level2);

		meteorShootFrameX += 0.13;
		if (meteorShootFrameX >= 8)
		{
			meteorShootFrameX = 0;
			meteorShootFrameY++;
		}
		if (meteorShootFrameY >= 4)
		{
			meteorShootFrameX = 0;
			meteorShootFrameY = 0;
		}
		dragonSprite.setPosition((windowSizeX - 1100) + 330, 50);
	}
	void dragonRingShoot()
	{
		updateSubRect2D(subRect, dragonPeashotTex_Level2, 6, 6, ringShootFrameX, ringShootFrameY);
		dragonSprite.setTexture(dragonPeashotTex_Level2);
		ringShootFrameX += 0.2;

		if (ringShootFrameX >= 6)
		{
			ringShootFrameX = 0;
			ringShootFrameY++;
			if (ringShootFrameY == 4 && ringAnimationEnds == false)
			{
				ringShootFrameX = 2;
				ringShootFrameY = 1;
			}

		}
		if ((ringShootFrameX >= 2 && ringShootFrameY == 1) || (ringShootFrameY >= 2 && ringShootFrameY <= 3))
			inRingsAttackMode = true;
		else
			inRingsAttackMode = false;

		dragonSprite.setPosition((windowSizeX - 1100) + 240, -100);
	}

	void update(Clock& startLevelClock, PlayerSt_Level2& player, int& currentPhase)
	{
		if (!isSetup)
		{
			isSetup = true;
			// Peashot
			peashotStartSound.setBuffer(peashotStartBuffer_Level2);
			peashotStartSound.setVolume(70);
			peashotEndSound.setBuffer(peashotEndBuffer_Level2);
			peashotEndSound.setVolume(70);
			for (int i = 0; i < 3; i++)
			{
				peashotAttackSound[i].setBuffer(peashotAttackBuffer_Level2);
				peashotAttackSound[i].setVolume(50);
			}

			dragonIdleSound.setBuffer(dragonIdleBuffer_Level2);
			dragonIdleSound.setVolume(40);

			// Meteor Shoot
			for (int i = 0; i < 4; i++)
			{
				meteorStartSound[i].setBuffer(meteorStartBuffer_Level2);
				meteorStartSound[i].setVolume(60);
				meteorAttackSound[i].setBuffer(meteorAttackBuffer_Level2);
				meteorAttackSound[i].setVolume(60);
			}
		}
		if (introFrameY <= 3)
		{
			dragonIntro();
			ringClock.restart();
			idleClock.restart();
		}
		else
		{
			if (!dragonIdleSoundPlayed)
			{
				dragonIdleSoundPlayed = true;
				dragonIdleSound.play();
				dragonIdleSound.setLoop(true);
			}
			if (idleClock.getElapsedTime().asMilliseconds() >= idleTime)
			{
				setIdlePositionOnce = true;
				// PeaShoot 
				if (isPeashoot)
				{
					if (!peashotStartSoundPlayed)
					{
						peashotStartSoundPlayed = true;
						peashotStartSound.play();
					}

					if (ringAnimationEnds && ringShootFrameX >= 1 && ringShootFrameY >= 5)
						dragonIdle();
					else
						dragonRingShoot();
					// Update Eyes IF He is Attacking
					if (inRingsAttackMode)
						eyesAttack.update(dragonSprite.getPosition().x);

					if (ringsBeforeStart)
					{
						Vector2f ringPosition(dragonSprite.getPosition().x + 335, 170);
						Vector2f direction = player.playerSprite.getPosition() - ringPosition;
						float length = sqrt(direction.x * direction.x + direction.y * direction.y);
						direction /= length;

						for (int i = 0; i < 3; i++)
						{
							rings[i].setup();
							rings[i].moveX = direction.x * 8.0;
							rings[i].moveY = direction.y * 8.0;
							rings[i].ringSprite.setPosition(ringPosition);
						}
						isRingHitCupead = false;
					}
					ringsBeforeStart = false;


					float clockTime = ringClock.getElapsedTime().asMilliseconds();
					if (clockTime >= ringTime * 2)
						lastRing = 1;
					if (clockTime >= ringTime * 3)
						lastRing = 2;
					// To Wait Until His Eyes Change
					if (ringShootFrameY == 0 || (ringShootFrameY == 1 && ringShootFrameX <= 1))
						ringClock.restart();
					else if (lastRing == -1 && clockTime >= ringTime)
					{
						lastRing = 0;
						// Sound
						if (!peashotStartSoundPlayed)
						{
							peashotStartSoundPlayed = true;
							peashotStartSound.play();
						}
					}

					for (int i = 0; i <= lastRing; i++)
					{
						if (!peashotAttackSoundPlayed[i])
						{
							peashotAttackSoundPlayed[i] = true;
							peashotAttackSound[i].play();
						}
					}

					// Sound to turn From Peashot To Idle Mode
					if (lastRing == 2 && !inRingsAttackMode && !peashotEndSoundPlayed)
					{
						peashotEndSoundPlayed = true;
						peashotEndSound.play();
					}

					if (ringsEnds == 1 && ringClock.getElapsedTime().asMilliseconds() >= 1000)
						ringAnimationEnds = true;

					for (int i = 0; i <= lastRing; i++)
						rings[i].update();

					if (rings[2].ringSprite.getPosition().x <= -600)
					{
						ringsBeforeStart = true;
						lastRing = -1;
						ringClock.restart();
						ringsEnds++;

						// Reset Sound Of Rings
						for (int i = 0; i < 3; i++)
							peashotAttackSoundPlayed[i] = false;
					}
					// End This And Go To Meator Shoot
					if (ringsEnds == 2)
					{
						ringsEnds = 0;
						isPeashoot = false;
						idleClock.restart();

						// To Reset The CurrentBallIndex Before The meteor Shoot
						currentBallIndex = 0;
					}
				}
				// Meateor Shoot
				else
				{
					// Start Sound
					if (meteorShootFrameX == 0 && meteorShootFrameY == 0)
					{
						meteorStartSound[currentBallIndex].play();
					}

					dragonMeteorShoot();
					if ((int)meteorShootFrameX == 6 && (int)meteorShootFrameY == 2 && fireBallGo)
					{
						fireBall[currentBallIndex].setup();
						fireBall[currentBallIndex].fireBallSprite.setPosition(dragonSprite.getPosition().x + 30, 450);
						fireBall[currentBallIndex].goTop = randomNumber(0, 1);
						fireBallGo = false;
						meteorAttackSound[currentBallIndex].play();
						currentBallIndex++;
					}
					if ((int)meteorShootFrameX == 7 && (int)meteorShootFrameY == 3)
					{
						fireBallGo = true;
						// End This And Go To Peashoot Attack
						if (currentBallIndex == 4)
						{
							isPeashoot = true;
							meteorShootFrameX = 0;
							meteorShootFrameY = 0;
							idleClock.restart();
						}
					}
				}
			}
			// Go To Idle
			else
			{
				dragonIdle();
				if (health <= 0)
				{
					idleClock.restart();
					dragonIdleSound.stop();
					dragonSprite.move(4, 0);
				}
				if (dragonSprite.getPosition().x >= windowSizeX + dragonSprite.getLocalBounds().width + 100)
					currentPhase++;
				ringClock.restart();
				ringAnimationEnds = false;
				ringShootFrameX = 0, ringShootFrameY = 0;
				eyesAttack.eyesFrame = 0;
				setIdlePositionOnce = false;

				// Reset For Sounds
				peashotStartSoundPlayed = false;
				peashotEndSoundPlayed = false;
			}

			for (int i = 0; i < currentBallIndex; i++)
				fireBall[i].update();
		}

		bulletHitBoss(player.bullets, player.hp.lives);
		ringHitCuphead(player);
		meteorHitCuphead(player);

		// Dragon Fade
		if (fadeTimer.getElapsedTime().asMilliseconds() >= 50)
			dragonColor.a = 255;
		dragonSprite.setColor(dragonColor);

		dragonSprite.setTextureRect(subRect);
		dragonSprite.setScale(1.7, 1.7);
	}
	void draw()
	{
		window.draw(dragonSprite);

		if (isPeashoot)
		{
			for (int i = 0; i <= lastRing; i++)
				rings[i].draw();
			if (inRingsAttackMode)
				eyesAttack.draw();
		}
		for (int i = 0; i < currentBallIndex; i++)
			fireBall[i].draw();
	}
};
// Phase 2
struct firstFiremarcher_Level2
{
	Sprite enemySprite;
	IntRect subRect;
	float moveX = 0, enemyFrame = 0;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		enemySprite.setTexture(firstEnemyTex_Level2);
		enemySprite.setTextureRect(subRect);
		enemySprite.setScale(1.3, 1.3);
		enemySprite.setPosition(430, 762);
	}

	void update()
	{
		if (moveX == 0)
			setup();
		updateSubRectNoDirection(subRect, firstEnemyTex_Level2, 16.0, enemyFrame);
		moveX = 3;
		enemyFrame += 0.15;
		if (enemyFrame >= 16)
			enemyFrame -= 16;

		enemySprite.setTexture(firstEnemyTex_Level2);
		enemySprite.setTextureRect(subRect);
		enemySprite.move(moveX, 0);
	}
	void draw()
	{
		window.draw(enemySprite);
	}
};
struct oneFiremarcher_Level2
{
	Sprite enemySprite;
	Texture currentTexture;
	IntRect subRect;
	float runFrame, readyFrame, attackFrame, moveX, moveY, gravity = 0.08167;
	bool isAttack = false;
	Clock attackClock;
	bool hitCupHead = false;
	float positionX, positionY;
	long double angle;
	int currentState = 1;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void setup()
	{
		enemySprite.setTexture(currentTexture);
		moveX = 3, moveY = 0;
		enemySprite.setTextureRect(subRect);
		enemySprite.setPosition(400, 832);
		enemySprite.setScale(1.3, 1.3);
		runFrame = 0, readyFrame = 0, attackFrame = 0;
	}
	void runEnemy()
	{
		currentTexture = enemyRunTex_Level2;
		updateSubRectNoDirection(subRect, currentTexture, 15.0, runFrame);
		runFrame += 0.25;
		if (runFrame >= 15)
			runFrame -= 15;

	}
	void readyEnemy(Vector2f playerPosition)
	{
		currentTexture = enemyReadyTex_Level2;
		updateSubRectNoDirection(subRect, currentTexture, 14.0, readyFrame);
		moveX = 0, moveY = 0;
		readyFrame += 0.1;
		if (readyFrame >= 14)
		{
			currentState = 3;
			jumpAttack(playerPosition);
		}
	}
	void jumpAttack(Vector2f playerPosition)
	{
		angle = atan2(enemySprite.getPosition().y - playerPosition.y, enemySprite.getPosition().x - playerPosition.x) * 180 / PI;
		moveY = -1 * sqrt(2 * gravity * (window.getSize().y - enemySprite.getPosition().y));
		moveX = moveY / tan(angle * PI / 180);
	}
	void attackEnemy()
	{
		currentTexture = enemyAttackTex_Level2;
		updateSubRectNoDirection(subRect, currentTexture, 8.0, attackFrame);
		attackFrame += 0.25;
		if (attackFrame >= 8)
			attackFrame -= 8;
		moveY -= gravity * 5;
	}
	void update()
	{
		enemySprite.setTexture(currentTexture);
		enemySprite.setTextureRect(subRect);
		enemySprite.move(moveX, moveY);

		positionX = enemySprite.getPosition().x;
		positionY = enemySprite.getPosition().y;
	}

	void draw()
	{
		window.draw(enemySprite);
	}
};
struct firemarcherdSt_Level2
{
	vector<oneFiremarcher_Level2>firemarchers;
	Clock firemarcherClock, attackClock, jumpClock;

	void fireMarchHitCuphead(PlayerSt_Level2& player)
	{
		for (auto& march : firemarchers)
		{
			if (player.playerSprite.getGlobalBounds().intersects(march.enemySprite.getGlobalBounds())
				&& player.positionX >= march.positionX - 100 && player.positionX <= march.positionX + 50
				&& player.positionY >= march.positionY - 190 && march.hitCupHead == false)
			{
				if (player.isCrawling)
				{
					if (player.positionY <= march.positionY)
					{
						march.hitCupHead = true;
						player.hp.isHit = true;
					}
				}
				else
				{
					if (player.positionY <= march.positionY + 100)
					{
						march.hitCupHead = true;
						player.hp.isHit = true;
					}
				}
			}
		}
	}
	void update(PlayerSt_Level2& player, bool& isDead, bool& isTongue)
	{
		if (jumpClock.getElapsedTime().asMilliseconds() >= 4000 && firemarchers.size() >= 5)
		{
			firemarchers[3].currentState = 2;
			jumpClock.restart();
		}
		if (firemarcherClock.getElapsedTime().asMilliseconds() >= 800 && !isDead)
		{
			firemarcherClock.restart();
			oneFiremarcher_Level2 firemarcher;
			firemarcher.setup();
			firemarchers.push_back(firemarcher);
		}
		fireMarchHitCuphead(player);

		for (int i = 0; i < firemarchers.size(); i++)
		{
			if (firemarchers[i].currentState == 1)
				firemarchers[i].runEnemy();
			else if (firemarchers[i].currentState == 2)
				firemarchers[i].readyEnemy(player.playerSprite.getPosition());
			else if (firemarchers[i].currentState == 3)
				firemarchers[i].attackEnemy();

			firemarchers[i].update();
			if (firemarchers[i].enemySprite.getPosition().x >= windowSizeX + 200 || firemarchers[i].enemySprite.getPosition().x <= -200
				|| firemarchers[i].enemySprite.getPosition().y <= -200)
			{
				firemarchers.erase(firemarchers.begin() + i);
				i--;
			}
		}
	}
	void draw()
	{
		for (auto& firemarcher : firemarchers)
			firemarcher.draw();
	}
};
struct tongue_Level2
{
	Sprite tongueSprite;
	IntRect subRect;
	float tongueFrame = 0;
	void updateSubRectNoDirectionVertical(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = 0;
		subRect.top = size.y / photosNumber * int(currentFrame);
		subRect.width = size.x;
		subRect.height = size.y / photosNumber;
	}

	void update(bool& isTongue)
	{
		updateSubRectNoDirectionVertical(subRect, drgonTongueTex_Level2, 14.0, tongueFrame);
		if (!isTongue)
		{
			if (tongueFrame >= 0)
				tongueFrame -= 0.2;
		}
		else
		{
			if (tongueFrame < 11)
				tongueFrame += 0.2;
			else if (tongueFrame >= 11 && tongueFrame <= 14)
			{
				tongueFrame += 0.05;
			}
			if (tongueFrame > 14)
			{
				tongueFrame = 11;
			}
		}
		tongueSprite.setPosition(390, 782);
		tongueSprite.setTexture(drgonTongueTex_Level2);
		tongueSprite.setTextureRect(subRect);
		if (tongueFrame < 0)
			tongueSprite.setScale(0, 0);
		else
			tongueSprite.setScale(1.5, 1.5);
	}
	void draw()
	{
		window.draw(tongueSprite);
	}
};
struct fire_smoke
{
	Sprite sprite;
	Texture currentTexture;
	IntRect subRect;
	Clock fireClock;
	bool isFire = true;
	float fireFrame = 0, smokeFrame = 0;
	bool soundPlayed = false;
	bool hitCupHead = false;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void fire()
	{
		currentTexture = firePhase2Tex_Level2;
		updateSubRectNoDirection(subRect, currentTexture, 19.0, fireFrame);
		fireFrame += 0.08;

		sprite.setPosition(320, 50);

	}
	void smoke()
	{
		currentTexture = smokePhase2Tex_Level2;
		updateSubRectNoDirection(subRect, currentTexture, 21.0, smokeFrame);
		smokeFrame += 0.08;

		sprite.setPosition(175, 225);

	}

	bool fireHitCupHead(PlayerSt_Level2& player)
	{
		if (player.playerSprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) &&
			player.playerSprite.getPosition().x <= sprite.getPosition().x + 50)
			return true;

		return false;
	}

	void update(Sound& fireSound, Sound& smokeSound, int& dragonHealth, PlayerSt_Level2& player)
	{
		if (fireClock.getElapsedTime().asMilliseconds() >= 800 && dragonHealth > 0)
		{
			if (isFire)
			{
				if (fireHitCupHead(player) && !hitCupHead)
				{
					player.hp.isHit = true;
					hitCupHead = true;
				}
				if (!soundPlayed)
				{
					soundPlayed = true;
					fireSound.play();
				}
				fire();
				if (fireFrame >= 19)
				{
					isFire = false;
					soundPlayed = false;
					fireFrame -= 19;
					fireClock.restart();
				}

			}
			else
			{
				hitCupHead = false;
				if (!soundPlayed)
				{
					soundPlayed = true;
					smokeSound.play();
				}
				smoke();
				if (smokeFrame >= 21)
				{
					isFire = true;
					smokeFrame -= 21;
					fireClock.restart();
				}
			}
		}

		sprite.setTexture(currentTexture);
		sprite.setTextureRect(subRect);
		sprite.setScale(1.2, 1.2);

	}
	void draw()
	{
		window.draw(sprite);
	}
};
struct DragonPhaseTwo_Level2
{
	Sprite dragonSprite;
	Texture currentTexture;
	IntRect subRect;
	int health = 1200, moveX = 0, moveY = 0;
	float introFrameX = 0, introFrameY = 0, idleFrame = 0, dashFrame = 0, deathFrame = 0;
	bool isDead = false, isTongue = true;
	int dragonPosX = dragonSprite.getPosition().x;
	int dragonPosY = dragonSprite.getPosition().y;
	Clock starting;

	fire_smoke fireSmoke;

	tongue_Level2 tongue;
	firstFiremarcher_Level2 firstEnemy;
	firemarcherdSt_Level2 firemarcher;

	bool dashDone = false, idleDone = false, deathDone = false; // To Set The Textures Just Once
	// Fade 
	Color dragonColor = dragonSprite.getColor();
	Clock fadeTimer;

	bool isSetup = false;
	Sound dashSound, fireSound, smokeSound, dragonIntroSound, firemarcherReadySound, firemarcherJumpSound;
	bool dashSoundPlayed = false, dragonIntroSoundPlayed = false;

	void updateSubRectNoDirection(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRect2D(IntRect& subRect, Texture& currentTexture, float numberX, float numberY, float frameX, float frameY)
	{
		// 4 Rows , 10 Columns -> (numberX -> 10 , numberY -> 4)
		auto size = currentTexture.getSize();

		subRect.left = size.x / numberX * int(frameX);
		subRect.top = size.y / numberY * int(frameY);
		subRect.width = size.x / numberX;
		subRect.height = size.y / numberY;
	}
	void updateSubRectNoDirectionVertical(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();

		subRect.left = 0;
		subRect.top = size.y / photosNumber * int(currentFrame);
		subRect.width = size.x;
		subRect.height = size.y / photosNumber;
	}

	void bulletHitBoss(vector<BulletSt>& currentBullets)
	{
		for (auto& bullet : currentBullets)
		{
			auto bulletPos = bullet.bulletSprite.getPosition();
			auto dragonPos = dragonSprite.getPosition();
			if (bullet.bulletSprite.getGlobalBounds().intersects(dragonSprite.getGlobalBounds()) &&
				bulletPos.x <= dragonPos.x + 500 && bulletPos.y >= dragonPos.y)
			{
				bullet.bulletHitBoss = true;
				if (bullet.decreaseBossHealth)
				{
					health -= 10 + DamageBought;
					dragonColor.a = 255 - 85;
					fadeTimer.restart();
				}
				bullet.decreaseBossHealth = false;
			}
		}
	}

	void dragonDash()
	{
		if (moveX == 0)
			dragonSprite.setPosition(windowSizeX + 100, 400);
		updateSubRectNoDirection(subRect, dragonDashTex_Level2, 8.0, dashFrame);
		moveX = -15;
		dashFrame += 0.02;
	}
	void dragonIntro_Idle()
	{
		updateSubRect2D(subRect, dragonIntroPhase2Tex_Level2, 7.0, 5.0, introFrameX, introFrameY);
		if (introFrameX == 0 && introFrameY == 0)
			dragonSprite.setPosition(-900, -50);

		moveX = 0, moveY = 0;
		introFrameX += 0.15;
		if (introFrameX >= 7)
		{
			introFrameX -= 7;
			introFrameY++;
			if (introFrameY >= 5)
			{
				introFrameY -= 2;
				introFrameX++;
			}
		}

		if (introFrameY < 2 && introFrameX < 4)
			moveX = 7;
		else
		{
			if (introFrameY < 3)
				moveY = 2;
		}
	}
	void dragonDeath()
	{
		updateSubRectNoDirection(subRect, dragonDeathPhase2Tex_Level2, 8.0, deathFrame);
		deathFrame += 0.05;
		if (deathFrame >= 8)
			deathFrame -= 8;
		dragonSprite.setPosition(-395, 225);
	}

	void update(vector<BulletSt>& currentBullets, PlayerSt_Level2& player, bool& winning)
	{
		// For Sounds
		if (!isSetup)
		{
			isSetup = true;
			// For Sound
			dashSound.setBuffer(dashBuffer_Level2);
			dashSound.setVolume(80);
			fireSound.setBuffer(fireBuffer_Level2);
			fireSound.setVolume(60);
			smokeSound.setBuffer(smokeBuffer_Level2);
			smokeSound.setVolume(60);
			dragonIntroSound.setBuffer(dragonIntroBuffer_Level2);
			dragonIntroSound.setVolume(80);
			firemarcherReadySound.setBuffer(firemarcherReadyBuffer_Level2);
			firemarcherJumpSound.setBuffer(firemarcherJumpBuffer_Level2);

		}
		if (dashFrame <= 8)
		{
			if (!dashSoundPlayed)
			{
				dashSoundPlayed = true;
				dashSound.play();
			}
			if (!dashDone)
			{
				dashDone = true;
				dragonSprite.setTexture(dragonDashTex_Level2);
			}
			dragonDash();
		}
		else
		{
			if (!idleDone)
			{
				idleDone = true;
				dragonSprite.setTexture(dragonIntroPhase2Tex_Level2);
			}
			dragonIntro_Idle();
			if (introFrameY >= 3)
			{
				if (starting.getElapsedTime().asMilliseconds() >= 700)
					firemarcher.update(player, isDead, isTongue);
				firstEnemy.update();
				fireSmoke.update(fireSound, smokeSound, health, player);
				tongue.update(isTongue);
				if (health <= 0)
				{
					if (!deathDone)
					{
						deathDone = true;
						winning = true;
						dragonSprite.setTexture(dragonDeathPhase2Tex_Level2);
					}
					dragonDeath();
				}
			}
			else
			{
				if (!dragonIntroSoundPlayed)
				{
					dragonIntroSoundPlayed = true;
					dragonIntroSound.play();
				}
				starting.restart();
			}
		}
		dragonSprite.setTextureRect(subRect);

		if (health <= 0)
		{
			isDead = true;
			isTongue = true;
		}
		dragonSprite.move(moveX, moveY);
		dragonSprite.setScale(1.5, 1.5);
		bulletHitBoss(currentBullets);

		// Dragon Fade
		if (fadeTimer.getElapsedTime().asMilliseconds() >= 50)
			dragonColor.a = 255;
		dragonSprite.setColor(dragonColor);
	}
	void draw()
	{
		window.draw(dragonSprite);
		tongue.draw();
		firstEnemy.draw();
		firemarcher.draw();
		if (fireSmoke.fireClock.getElapsedTime().asMilliseconds() >= 800 && !isDead)
		{
			fireSmoke.draw();
		}
	}
};
// Dragon
struct DragonSt_Level2
{
	DragonPhaseOne_Level2 dragonPhaseOne;
	DragonPhaseTwo_Level2 dragonPhaseTwo;

	void update(int& currentPhase, Clock& startLevelClock, PlayerSt_Level2& player, bool& winning)
	{
		if (currentPhase == 1)
		{
			dragonPhaseOne.update(startLevelClock, player, currentPhase);
		}
		else if (currentPhase == 2)
		{
			dragonPhaseTwo.update(player.bullets, player, winning);
		}
	}
	void draw(int currentPhase)
	{
		if (currentPhase == 1)
		{
			dragonPhaseOne.draw();
		}
		else
		{
			dragonPhaseTwo.draw();
		}
	}
};

// Level 3 Structures
struct BulletSt_Level3
{
	// Bullet
	Sprite bulletSprite, spawnSprite;
	IntRect subRect;
	bool  isSpawning;
	float spawnFrame, moveX = 0, moveY = 0;

	// Bullet Death
	float deathTime = 5, currentTimer = 0;
	float bulletDeathFrame = 0;
	bool  deleteMe = false;

	// Check Collision Boss & Player's Bullet
	bool bossDamage = false, healthDecreased = true;

	// Check Collision Birds & Player's Bullet
	bool birdDamage = false, birdHealthDec = true;

	void timerTillDeath(float deltaTime) {
		currentTimer += deltaTime;
		if (currentTimer >= deathTime)
			deleteMe = true;
	}

	// Initialize spawn and bullet scale
	void spawnSetup()
	{
		spawnSprite.setTexture(spawnTex_Level3);
		spawnSprite.setScale(1, 1);
		bulletSprite.setScale(0.1, 0.1);
		spawnFrame = 0;
		isSpawning = true;
	}
};
struct PlayerSt_Level3
{

	// Player Intro
	float radius, angle, angularSpeed; // Radius of the circular path, Current angle in radians, Angular speed in radians per frame
	bool isMoving = true;

	// player
	Sprite playerSprite;
	Texture currentTexture;
	IntRect subRect;
	float moveY, moveX, positionX, positionY,
		transDownFrame, transUpFrame, flyFrame, IntroFrame;
	bool isStarted;
	Clock clock, playerTexIntro;

	//Sound
	Sound bulletSound;

	// Shoot 
	vector<BulletSt_Level3> bullets;
	float const shootSpeed = 11;
	float shootCooldown;

	// Player Health
	HpBarSt hp;

	// Player Death
	GhostSt ghost;

	// Update Player's Animation
	void updateSubRect(IntRect& subRect, Texture currentTexture, float photosNumber, float currentFrame)
	{
		auto size = currentTexture.getSize();
		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	// Variables Intializtion
	void setup() {
		currentTexture = straightTex_Level3;
		positionX = playerSprite.getPosition().x, positionY = playerSprite.getPosition().y;
		playerSprite.setTexture(currentTexture);
		playerSprite.setPosition(10, 300);
		playerSprite.setScale(0.7, 0.7);
		moveY = 0, moveX = 0;
		radius = 150.0, angle = 0.75 * PI, angularSpeed = 0.040;
		transDownFrame = 0, transUpFrame = 0, flyFrame = 0, IntroFrame = 0;
		updateSubRect(subRect, currentTexture, 4.0, flyFrame);


		// Shooting
		bullets.clear();
		shootCooldown = 170;

		// Hp
		hp.hpSetup();

		// Death
		ghost.ghostSetup();
		//deathMenu.setup();
	}

	// Functions of Player Movement
	void Stationary() {

		currentTexture = straightTex_Level3;
		playerSprite.setScale(0.7, 0.7);
		moveY = 0, moveX = 0;
		updateSubRect(subRect, currentTexture, 4.0, flyFrame);
	}
	void moveRight() {

		currentTexture = straightTex_Level3;
		playerSprite.setScale(0.7, 0.7);
		if (positionX < rightWall)
			moveX = 4;
		updateSubRect(subRect, currentTexture, 4.0, flyFrame);
	}
	void moveLeft() {

		currentTexture = straightTex_Level3;
		playerSprite.setScale(0.7, 0.7);
		if (positionX > leftWall)
			moveX = -4;
		updateSubRect(subRect, currentTexture, 4.0, flyFrame);
	}
	void transitionUp() {
		currentTexture = transUpTex_Level3;
		playerSprite.setScale(0.7, 0.7);
		if (positionY > 0)
			moveY = -4;
		updateSubRect(subRect, transUpTex_Level3, 4.0, transUpFrame);
		transUpFrame += 0.15;
		if (transUpFrame >= 4)
			transUpFrame -= 4;
	}
	void transitionDown() {
		currentTexture = transDownTex_Level3;
		playerSprite.setScale(0.7, 0.7);
		if (positionY < window.getSize().y - 200)
			moveY = 4;
		updateSubRect(subRect, transDownTex_Level3, 4.0, transDownFrame);
		transDownFrame += 0.15;
		if (transDownFrame >= 4)
			transDownFrame -= 4;
	}

	// Shooting Function
	void shoot(Clock& shootClock) {

		if (shootClock.getElapsedTime().asMilliseconds() < shootCooldown)
			return;
		shootClock.restart();

		BulletSt_Level3 currentBullet;

		currentBullet.bulletSprite.setTexture(straightBulletTex_Level3);
		currentBullet.moveX = shootSpeed;

		currentBullet.spawnSetup();
		currentBullet.bulletSprite.setPosition(positionX, positionY + 75);
		currentBullet.spawnSprite.setPosition(positionX + 130, positionY + 45);

		bulletSound.setBuffer(PlayerBulletBuf_Level3);
		bulletSound.play();

		bullets.push_back(currentBullet);
	}

	// Update
	void update(menu& menu, Event& event, int& PageNumber) {
		float IntroTime = playerTexIntro.getElapsedTime().asSeconds();
		if (IntroTime <= 1.55) {

			currentTexture = CupheadIntro;
			playerSprite.setTexture(currentTexture);
			playerSprite.setTextureRect(subRect);
			updateSubRect(subRect, currentTexture, 35.0, IntroFrame);
			if (isMoving)
			{
				// Calculate new position in the circular path
				float x = 0 + radius * cos(angle);
				float y = 125 + radius * sin(angle);
				playerSprite.setPosition(x, y);

				// Update angle
				angle -= angularSpeed;

				// Stop moving after one complete circle (2 * pi radians)
				if (angle <= (-2 * PI))
					isMoving = false;

			}

			IntroFrame += 0.17;
			if (IntroFrame >= 35.0)
				IntroFrame -= 35;

		}

		// Set player
		else if (IntroTime > 1.55)
		{
			playerSprite.setTexture(currentTexture);
			playerSprite.setTextureRect(subRect);
			updateSubRect(subRect, currentTexture, 4.0, flyFrame);

		}
		// Update player's animation
		playerSprite.setTexture(currentTexture);
		playerSprite.setTextureRect(subRect);
		playerSprite.move(moveX, moveY);

		flyFrame += 0.25;
		if (flyFrame >= 4)
			flyFrame -= 4;

		if (hp.lives <= 0)
		{
			ghost.death(currentTexture, playerSprite, moveY);
			ghost.isDead = true;

			// Clear Bullets
			if (bullets.size())
				bullets.clear();
			return;
		}
		ghost.deathClock.restart();


		// Bullets Moving
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].deleteMe)
				bullets.erase(bullets.begin() + i);
			else {
				bullets[i].bulletSprite.move(bullets[i].moveX, bullets[i].moveY);
				// spawn
				if (bullets[i].spawnFrame >= 2) {
					bullets[i].isSpawning = false;
				}

				if (bullets[i].isSpawning) {
					bullets[i].spawnFrame += 0.4;
					updateSubRect(bullets[i].subRect, spawnTex_Level3, 2.0, bullets[i].spawnFrame);
					bullets[i].spawnSprite.setTextureRect(bullets[i].subRect);
				}
				if (bullets[i].bossDamage)
				{
					bullets[i].bulletSprite.setTexture(hitDustTex_Level3);
					updateSubRect(bullets[i].subRect, hitDustTex_Level3, 12.0, bullets[i].bulletDeathFrame);
					bullets[i].bulletSprite.setTextureRect(bullets[i].subRect);
					bullets[i].bulletSprite.setScale(0.4, 0.4);
					bullets[i].bulletDeathFrame += 0.2;

					bullets[i].moveX = 0;
					bullets[i].moveY = 0;
				}

				if (bullets[i].bulletSprite.getPosition().x >= rightWall || bullets[i].bulletSprite.getPosition().x <= leftWall - 300
					|| bullets[i].bulletSprite.getPosition().y <= -400) {
					bullets[i].deleteMe = true;
				}
			}
		}

		// Hp
		if (hp.isHit) {
			hp.getHit();
		}
		if (hp.lives == 1)
		{
			hp.oneLiveAnimation();
		}

		moveX = 0, moveY = 0;
		positionX = playerSprite.getPosition().x;
		positionY = playerSprite.getPosition().y;
	}

	// Draw
	void draw(menu& menu, RenderWindow& window, int& PageNumber) {
		window.draw(playerSprite);		// player's Sprite
		window.draw(hp.hpSprite);		// player's health

		if (ghost.isDead && ghost.deathClock.getElapsedTime().asMilliseconds() <= 3000 && ghost.deathClock.getElapsedTime().asMilliseconds() >= 500)
		{
			window.draw(ghost.youDiedSprite);
		}
	}
};

struct EggSt_Level3
{
	// Egg
	Sprite EggSprite;
	IntRect subRect;
	int EggFrame;
	bool isShooting, broken;

	// Egg Death
	bool isHit;
	float deathFrame;
	IntRect deathRect;

	// Check Collision Player & Egg
	bool playerDamage, PlayerDecreased;

	// Variables Intializtion
	void setup() {
		EggSprite.setTexture(EggTex_Level3);
		EggSprite.setScale(0.8, 0.8);
		EggFrame = 0, deathFrame = 0;
		isShooting = true, playerDamage = false, PlayerDecreased = true, broken = true;
	}
	// Death Function
	void death() {
		broken = false;
		EggSprite.setTexture(EggDeathTex_Level3);
		EggSprite.setTextureRect(deathRect);
		EggSprite.setScale(1.3, 1.3);

	}

};
struct HandBullet_Level3 {

	// Boss's Bullet
	Sprite bulletSprite;
	IntRect subRect;
	int bulletFrame;
	float speedX, speedY;

	// Check Collision Player & Boss's Bullet
	bool playerDamage, playerDecreased;

	// Bullet Death
	bool isHit;
	float deathFrame;
	IntRect deathRect;

	// Variables Intializtion
	void setup() {
		bulletSprite.setTexture(handBulletTex_Level3);
		bulletSprite.setScale(0.9, 0.9);
		speedX = 0, speedY = 0, bulletFrame = 0, deathFrame = 0;
		playerDamage = false, playerDecreased = true;

	}
	// Death Function
	void death() {
		bulletSprite.setTexture(handBulletDeathTex_Level3);
		bulletSprite.setTextureRect(deathRect);
		bulletSprite.setScale(0.45, 0.45);

	}

};
struct OneFeather_Level3 {

	// Feather
	Sprite featherSprite;
	IntRect subRect;
	int damage;
	float featherFrame, DeathTime, currentTimer;
	bool deleteMe, playerDamage, playerDecreased;
	Clock featherClock;
	Vector2f velocity;

	// Update Feather Animation
	void updateSubRect(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame) {
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	// Variables Intializtion
	void setup() {
		featherSprite.setTexture(FeatherTex_Level3);
		featherSprite.setTextureRect(subRect);
		featherFrame = 0;

		DeathTime = 5; //kill yourself after 5 seconds >:)
		currentTimer = 0; //the actual timer

		//Player collision with feathers
		playerDamage = false, playerDecreased = true;

		//Deleting feathers
		deleteMe = false;

		updateSubRect(subRect, FeatherTex_Level3, 8.0, featherFrame);
	}

	// Update
	void update(float deltaTime) {

		featherFrame += 0.25;
		if (featherFrame >= 8)
			featherFrame -= 8;

		featherSprite.setTexture(FeatherTex_Level3);
		featherSprite.setTextureRect(subRect);

		featherSprite.move(velocity * deltaTime);

		if (featherSprite.getPosition().x <= -50 || featherSprite.getPosition().x > 1950 || featherSprite.getPosition().y <= -50 ||
			featherSprite.getPosition().y > 1200)
		{
			deleteMe = true;
		}

		updateSubRect(subRect, FeatherTex_Level3, 8.0, featherFrame);

	}

	// Draw
	void draw() {
		window.draw(featherSprite);
	}

};
struct EnemySt_Level3 {

	// Boss
	Sprite EnemySprite;
	float moveSpeed, IntroFrame, Intro2Frame, StaticFrame, BarfFrame, PositionX, PositionY, handGunFrame,
		SteamFrameX, SteamFrameY, FlapIntroFrame, FlapLoopFrame, FlapOutroFrame, PantFrame, SteamFrame;
	Texture currentTexture;
	IntRect subRect;
	bool moveUp, isBarfing, Static;
	Clock timer, enemyTexTime, BarfClock, handGunClock, SteamClock;

	// Sound
	Sound EnemySound, EggSound, GunSound;
	SoundBuffer currentSound, EggCurrentSound, GunCurrentSound;
	bool second, handgun, steam, pant, flap, died, house;

	// Boss Death
	float DeathFrame, DeathFrameX, DeathFrameY;
	IntRect deathRect;
	bool isDead, fadeOut;
	Clock deathClock;
	int bossHealth = 1800;

	// Boss Damage
	Color EnemyColor = EnemySprite.getColor();
	Clock fadetimer;
	float elapsedTime;

	// Barf Shoot 
	vector<EggSt_Level3> Eggs;

	// Hand Shoot
	vector<HandBullet_Level3> bullets;

	// Feather Attack
	Clock featherClock;
	vector< OneFeather_Level3> feathers;
	int feathersToFire = 15; //number of feathers per wave
	int wavesCtr = 0;
	int numberOfBulletSegments = 15; //divide the circle to 15 pieces
	float radiusOfFeatherRing = 0.1; //the radius of the feather ring duh
	float featherSpeed = -500; //the speed of the feather
	int featherDamage = 10; //damage of the feather

	// Player Damage
	bool playerDamage, playerDecreased;

	// Update Boss's Animation
	void updateSubRect(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame) {
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}
	void updateSubRectCompact(IntRect& subRect, Texture& currentTexture, int numRows, int numCols, int currentFrame) {
		auto size = currentTexture.getSize();

		int row = currentFrame / numCols;
		int col = currentFrame % numCols;

		subRect.width = size.x / numCols;
		subRect.height = size.y / numRows;
		subRect.left = col * subRect.width;
		subRect.top = row * subRect.height;
	}

	// Variables Intializtion
	void setup() {
		currentTexture = enemyIntroTex_Level3;
		PositionX = EnemySprite.getPosition().x, PositionY = EnemySprite.getPosition().y;
		EnemySprite.setTexture(currentTexture);
		EnemySprite.setPosition(1100, 300);
		EnemySprite.setScale(1.5, 1.5);
		moveSpeed = 3;
		IntroFrame = 0, Intro2Frame = 0, StaticFrame = 0, BarfFrame = 0, handGunFrame = 0, SteamFrameX = 0, SteamFrameY = 0, SteamFrame = 0,
			FlapIntroFrame = 0, FlapLoopFrame = 0, FlapOutroFrame = 0, PantFrame = 0, DeathFrame = 0, DeathFrameX = 0, DeathFrameY = 0;
		moveUp = true, isBarfing = false, isDead = false, fadeOut = true;

		updateSubRect(subRect, currentTexture, 10.0, IntroFrame);

		currentSound = EnemyClockIntroBuf_Level3;
		EnemySound.setBuffer(currentSound);
		EnemySound.play();
		second = true, handgun = true, steam = true, pant = true, flap = true, died = true, house = true;


		// Boss Damage
		EnemyColor = EnemySprite.getColor();
		elapsedTime = 0;

		// Player damage
		playerDamage = false, playerDecreased = true;

		// Shooting
		Eggs.clear();
		bullets.clear();
		feathers.clear();

	}

	//Shooting Functions
	void Barfshoot(Clock& shootClock) {
		if (shootClock.getElapsedTime().asSeconds() < 7)
			return;
		shootClock.restart();

		EggSt_Level3 currentEgg;

		currentEgg.setup();
		currentEgg.EggSprite.setPosition(PositionX + 15, PositionY + 190);
		EggCurrentSound = EnemyBarfBuf_Level3;
		EggSound.setBuffer(EggCurrentSound);
		EggSound.play();

		Eggs.push_back(currentEgg);
	}
	void handShoot(Clock& shootClock) {
		if (shootClock.getElapsedTime().asSeconds() < 2.38)
			return; // Ensure shooting starts only after the head has transformed into a hand
		shootClock.restart();


		for (int i = 0; i < 3; ++i) {
			HandBullet_Level3 currentBullet;
			currentBullet.bulletSprite.setTexture(handBulletTex_Level3);

			currentBullet.setup();
			currentBullet.bulletSprite.setPosition(PositionX + 150, PositionY + 200);

			GunCurrentSound = EnemyHandGunBuf_Level3;
			GunSound.setBuffer(GunCurrentSound);
			GunSound.play();

			bullets.push_back(currentBullet);
		}
	}
	void featherAttack(float deltaTime, Clock& shootClock) {
		if (shootClock.getElapsedTime().asSeconds() < 0.6)
			return; // Ensure shooting starts only after feather loop
		shootClock.restart();

		for (int i = 0; i < feathersToFire; i++)
		{
			OneFeather_Level3 newFeather;
			newFeather.setup();

			//determine the angle at which the current feather should spawn!
			float angle = ((i + (wavesCtr * 4 * 3.14)) / static_cast<float>(numberOfBulletSegments)) * 2 * 3.14;
			//set the position of the feather around the big evil bird depending on the angle
			float x = (PositionX)+radiusOfFeatherRing * cos(angle);
			float y = (PositionY)+radiusOfFeatherRing * sin(angle);
			newFeather.featherSprite.setPosition(x + 400, y + 400);
			//get the dir at which the feather should move in, that's the current velocity!, we multiply the norm(direction) by the
			//speed of which we want the feather to be in(magnitude) to create our velocity vector!
			Vector2f dir = Vector2f(x, y) - EnemySprite.getPosition();
			Vector2f norm = dir / sqrt(dir.x * dir.x + dir.y * dir.y);
			newFeather.featherSprite.setRotation(atan2(norm.y, norm.x) * 180 / 3.14);
			newFeather.velocity = featherSpeed * norm;
			newFeather.damage = featherDamage;
			//we then push back our brand new feather to our vector
			currentSound = FeatherAttackBuf_Level3;
			EnemySound.setBuffer(currentSound);
			EnemySound.play();

			feathers.push_back(newFeather);
		}
		wavesCtr++;
	}

	// Animation 
	void IntroAnimation(float deltaTime) {
		EnemySprite.setTexture(enemyIntroTex_Level3);
		EnemySprite.setTextureRect(subRect);
		updateSubRect(subRect, enemyIntroTex_Level3, 10.0, IntroFrame);
		IntroFrame += 14 * deltaTime;
		if (IntroFrame >= 10.0) {
			IntroFrame -= 10.0;
		}
	}
	void secondIntroAnimation(float deltaTime) {
		if (second) {
			currentSound = EnemySecondIntroBuf_Level3;
			EnemySound.setBuffer(currentSound);
			EnemySound.play();
			second = false;
		}
		EnemySprite.setTexture(enemyIntro2Tex_Level3);
		EnemySprite.setTextureRect(subRect);

		updateSubRect(subRect, enemyIntro2Tex_Level3, 19.0, Intro2Frame);
		Intro2Frame += 13 * deltaTime;
		if (Intro2Frame >= 19.0) {
			Intro2Frame -= 19.0;
		}
	}
	void staticEnemy(float deltaTime) {
		EnemySprite.setTexture(enemyStaticTex_Level3);
		EnemySprite.setTextureRect(subRect);

		if (moveUp) {
			EnemySprite.move(0, -moveSpeed);
			if (EnemySprite.getPosition().y <= 0)
				moveUp = false;
		}
		else {
			EnemySprite.move(0, moveSpeed);
			if (EnemySprite.getPosition().y + enemyStaticTex_Level3.getSize().y + 100 >= window.getSize().y)
				moveUp = true;
		}
		updateSubRect(subRect, enemyStaticTex_Level3, 17.0, StaticFrame);
		StaticFrame += 18 * deltaTime;
		if (StaticFrame >= 17.0) {
			StaticFrame -= 17.0;
		}
	}
	void BarfingEnemy(float deltaTime) {
		EnemySprite.setTexture(enemyBarfTex_Level3);
		EnemySprite.setTextureRect(subRect);

		updateSubRect(subRect, enemyBarfTex_Level3, 16.0, BarfFrame);
		Barfshoot(BarfClock);
		BarfFrame += 17 * deltaTime;
		if (BarfFrame >= 16.0) {
			BarfFrame -= 16.0;
			isBarfing = false;
			BarfClock.restart();
		}
	}
	void handGunEnemy(float deltaTime, float& IntroTime) {
		EnemySprite.setTexture(handGunTex_Level3);
		EnemySprite.setTextureRect(subRect);
		updateSubRect(subRect, handGunTex_Level3, 26.0, handGunFrame);
		if (IntroTime >= 54 && IntroTime < 55.3)
			handShoot(handGunClock);
		handGunFrame += 12 * deltaTime;
		if (handGunFrame >= 26) {
			handGunFrame -= 26;
			handGunClock.restart();
		}
	}
	void steamEnemy(float deltaTime) {
		if (steam) {
			currentSound = EnemySteamBuf_Level3;
			EnemySound.setBuffer(currentSound);
			EnemySound.play();
		}

		EnemySprite.setTexture(enemySteamTex_Level3);
		EnemySprite.setTextureRect(subRect);
		EnemySprite.setPosition(515, -500);

		updateSubRectCompact(subRect, enemySteamTex_Level3, 4.0, 10.0, SteamFrame);
		SteamFrame += 24 * deltaTime;
		if (SteamFrame >= 40.0) {
			SteamFrame -= 40.0;
		}
		Static = true;
	}
	void flapIntro(float deltaTime) {
		if (flap) {
			currentSound = EnemyFlapBuf_Level3;
			EnemySound.setBuffer(currentSound);
			EnemySound.play();
			flap = false;
		}

		EnemySprite.setTexture(enemyFlapIntroTex_Level3);
		EnemySprite.setTextureRect(subRect);
		EnemySprite.setPosition(1250, 200);
		updateSubRect(subRect, enemyFlapIntroTex_Level3, 9.0, FlapIntroFrame);
		FlapIntroFrame += 10 * deltaTime;
		if (FlapIntroFrame >= 9.0) {
			FlapIntroFrame -= 9.0;
		}

	}
	void flapLoop(float deltaTime) {
		EnemySprite.setTexture(enemyFlapLoopTex_Level3);
		EnemySprite.setTextureRect(subRect);
		EnemySprite.setScale(1.8, 1.8);

		updateSubRect(subRect, enemyFlapLoopTex_Level3, 9.0, FlapLoopFrame);
		featherAttack(deltaTime, featherClock);
		FlapLoopFrame += 10 * deltaTime;
		if (FlapLoopFrame >= 9.0) {
			FlapLoopFrame -= 9.0;
		}
	}
	void flapOutro(float deltaTime) {
		EnemySprite.setTexture(enemyFlapOutroTex_Level3);
		EnemySprite.setTextureRect(subRect);
		updateSubRect(subRect, enemyFlapOutroTex_Level3, 3.0, FlapOutroFrame);
		FlapOutroFrame += 4 * deltaTime;
		if (FlapOutroFrame >= 3.0) {
			FlapOutroFrame -= 3.0;
		}
	}
	void pantAnimation(float deltaTime) {
		if (pant) {
			currentSound = EnemyPantBuf_Level3;
			EnemySound.setBuffer(currentSound);
			EnemySound.play();
			pant = false;
		}

		EnemySprite.setTexture(enemyPantTex_Level3);
		EnemySprite.setTextureRect(subRect);

		if (moveUp) {
			EnemySprite.move(0, -2);
			if (EnemySprite.getPosition().y <= 0)
				moveUp = false;
		}
		else {
			EnemySprite.move(0, 2);
			if (EnemySprite.getPosition().y + enemyPantTex_Level3.getSize().y + 100 >= window.getSize().y)
				moveUp = true;
		}
		updateSubRect(subRect, enemyPantTex_Level3, 12.0, PantFrame);
		PantFrame += 13 * deltaTime;
		if (PantFrame >= 12.0) {
			PantFrame -= 12.0;
		}
	}

	// Boss Death
	void BossDeath() {
		if (died) {
			currentSound = EnemyDeathBuf_Level3;
			EnemySound.setBuffer(currentSound);
			EnemySound.play();
			died = false;
		}
		if (!isDead) {
			EnemySprite.setTexture(enemyDeathTex_Level3);
			EnemySprite.setTextureRect(subRect);
			EnemySprite.setScale(1.7, 1.7);
			EnemySprite.setPosition(850, PositionY);

			updateSubRectCompact(subRect, enemyDeathTex_Level3, 2.0, 15.0, DeathFrame);
			DeathFrame += 0.2;
			if (DeathFrame >= 30.0) {
				DeathFrame -= 30.0;
				isDead = true;
			}


		}


	}

	//Boss Damage
	void damage(vector<BulletSt_Level3>& currentBullets) {
		for (auto& bullet : currentBullets) {
			auto bulletPos = bullet.bulletSprite.getPosition();
			auto EnemyPos = EnemySprite.getPosition();
			if (bullet.bulletSprite.getGlobalBounds().intersects(EnemySprite.getGlobalBounds()) && bulletPos.x >= EnemyPos.x) {
				bullet.deleteMe = true;
				bullet.bossDamage = true;
				if (bullet.healthDecreased)
				{
					bossHealth--;
					if (bossHealth > 3) {
						EnemyColor.a -= 85; // Decrease the alpha component by 50
						EnemySprite.setColor(EnemyColor);
					}
				}
				bullet.healthDecreased = false;
			}
		}
	}

	// Update
	void update(PlayerSt_Level3 player, vector<BulletSt_Level3>& currentBullets) {
		float deltaTime = timer.restart().asSeconds();
		float IntroTime = enemyTexTime.getElapsedTime().asSeconds();
		float BarfTime = BarfClock.getElapsedTime().asSeconds();
		PlayTimer = LevelTime.getElapsedTime().asSeconds();


		/*Shooting Logic*/
		// Eggs
		for (int i = 0; i < Eggs.size();)
		{
			//Egg movement
			float speedX = 3;
			Eggs[i].EggSprite.move(-speedX, 0);

			// Egg Animation
			Eggs[i].EggFrame += 1;
			if (Eggs[i].EggFrame >= 33)
				Eggs[i].EggFrame -= 32;

			updateSubRect(Eggs[i].subRect, EggTex_Level3, 32.0, Eggs[i].EggFrame);
			Eggs[i].EggSprite.setTextureRect(Eggs[i].subRect);

			// Egg Death (Collision): Egg & Player && Egg & Left Wall
			if (Eggs[i].EggSprite.getPosition().x <= leftWall || (player.playerSprite.getGlobalBounds().intersects(Eggs[i].EggSprite.getGlobalBounds()) && !player.ghost.isDead)) {

				//Play sound
				if (Eggs[i].broken) {
					EggCurrentSound = EggDeathBuf_Level3;
					EggSound.setBuffer(EggCurrentSound);
					EggSound.play();
				}

				Eggs[i].death();

				Eggs[i].deathFrame += 0.25;
				if (Eggs[i].deathFrame >= 9) {
					Eggs[i].deathFrame -= 9;

					Eggs.erase(Eggs.begin() + i);
					continue;
				}

				updateSubRect(Eggs[i].deathRect, EggDeathTex_Level3, 9.0, Eggs[i].deathFrame);
			}
			++i;
		}

		//Bullets
		for (int i = 0; i < bullets.size();) {

			// Define the angles for each bullet
			float angles[] = { 25.0, 0.0, -25.0 };

			//movement for each bullet based on its angle
			float speedX = 3, speedY = 3;
			float dx = -speedX * cos(angles[i] * PI / 180.0);  /*convert degrees to radians*/
			float dy = -speedY * sin(angles[i] * PI / 180.0);


			//bullet movement
			bullets[i].bulletSprite.move(dx, dy);

			bullets[i].bulletFrame += 1;
			if (bullets[i].bulletFrame >= 6)
				bullets[i].bulletFrame -= 6;

			updateSubRect(bullets[i].subRect, handBulletTex_Level3, 6.0, bullets[i].bulletFrame);
			bullets[i].bulletSprite.setTextureRect(bullets[i].subRect);

			if (player.playerSprite.getGlobalBounds().intersects(bullets[i].bulletSprite.getGlobalBounds())) {
				bullets[i].death();

				bullets[i].deathFrame += 0.25;
				if (bullets[i].deathFrame >= 7) {
					bullets[i].deathFrame -= 7;
					bullets.erase(bullets.begin() + i);
					continue;
				}

				updateSubRect(bullets[i].deathRect, handBulletDeathTex_Level3, 7.0, bullets[i].deathFrame);
			}
			++i;

		}
		// Feathers
		for (int i = 0; i < feathers.size(); i++)
		{
			if (feathers[i].deleteMe)
				feathers.erase(feathers.begin() + i);
			else
				feathers[i].update(deltaTime);

		}

		/* Boss Health */

		// Boss Death
		if (bossHealth <= 0) {
			BossDeath();
			if (isDead) EnemySprite.move(0, 11);
			return;
		}
		deathClock.restart();

		// Boss Damage
		damage(currentBullets);
		elapsedTime = fadetimer.getElapsedTime().asSeconds();
		if (elapsedTime > 0.1f) {
			EnemyColor.a = 255; // Reset the alpha component to 255
			EnemySprite.setColor(EnemyColor);
			fadetimer.restart();
		}

		/* Animation */

		// Intro Animation
		if (BarfTime - 3.75 >= 3) {
			isBarfing = true;
		}
		if (IntroTime < 3) {
			IntroAnimation(deltaTime);
		}
		else if (IntroTime >= 3 && IntroTime < 4.5) {
			secondIntroAnimation(deltaTime);
		}
		else if (IntroTime >= 4.5 && !isBarfing) {
			staticEnemy(deltaTime);
		}
		// Barfing
		else if (isBarfing && IntroTime < 50 && IntroTime >= 3.75)
		{
			BarfingEnemy(deltaTime);
		}
		// HandGun
		else if (IntroTime > 50 && IntroTime < 55.1) {
			handGunEnemy(deltaTime, IntroTime);
		}
		// Back to Static
		else if (IntroTime >= 55.1 && IntroTime < 58.7) {
			staticEnemy(deltaTime);
		}
		// Steam
		else if (IntroTime >= 58.7 && IntroTime < 60.4) {
			steamEnemy(deltaTime);
			steam = false;
		}
		// Back to Static
		else if (IntroTime >= 60.4 && IntroTime < 65.1) {
			if (Static) {
				EnemySprite.setPosition(1100, 50);
				Static = false;
			}
			staticEnemy(deltaTime);
		}
		// Flap Intro 1
		else if (IntroTime >= 65.1 && IntroTime < 65.9) {
			flapIntro(deltaTime);
		}
		// Flap Loop  1
		else if (IntroTime >= 65.9 && IntroTime < 72.9) {
			flapLoop(deltaTime);
		}
		// Flap Outro 1
		else if (IntroTime >= 72.9 && IntroTime < 73.3) {
			flapOutro(deltaTime);
		}
		// Pant 1
		else if (IntroTime >= 73.3 && IntroTime < 77.3) {
			if (!Static) {
				EnemySprite.setPosition(1150, 260);
				EnemySprite.setScale(1.5, 1.5);
				Static = true;
			}
			pantAnimation(deltaTime);
		}
		// Flap Intro 2 (0.8secc)
		else if (IntroTime >= 77.3 && IntroTime < 78.1) {
			pant = true, flap = true;
			EnemySprite.setPosition(1250, 200);
			flapIntro(deltaTime);
		}
		// Flap Loop  2 (7secs)
		else if (IntroTime >= 78.1 && IntroTime < 85) {
			EnemySprite.setScale(1.8, 1.8);
			flapLoop(deltaTime);
		}
		// Flap Outro 2 (0.5secs)
		else if (IntroTime >= 85 && IntroTime < 85.5) {
			flapOutro(deltaTime);
		}
		// Pant 2 5.2secs
		else if (IntroTime >= 85.5 && IntroTime < 90.7) {
			if (Static) {
				EnemySprite.setPosition(1150, 260);
				EnemySprite.setScale(1.5, 1.5);
				Static = false;
			}
			pantAnimation(deltaTime);
		}
		// Flap Intro 3
		else if (IntroTime >= 90.7 && IntroTime < 91.5) {
			pant = true, flap = true;
			EnemySprite.setPosition(1250, -50);
			flapIntro(deltaTime);
		}
		// Flap Loop  3
		else if (IntroTime >= 91.5 && IntroTime < 98.5) {
			EnemySprite.setScale(1.8, 1.8);
			flapLoop(deltaTime);
		}
		// Flap Outro 3
		else if (IntroTime >= 98.5 && IntroTime < 99) {
			flapOutro(deltaTime);
		}
		// Pant 3
		else if (IntroTime >= 99 && IntroTime < 104.2) {
			if (!Static) {
				EnemySprite.setPosition(1150, 260);
				EnemySprite.setScale(1.5, 1.5);
				Static = true;
			}
			pantAnimation(deltaTime);
		}
		// Flap Intro 4
		else if (IntroTime >= 104.2 && IntroTime < 105) {
			pant = true, flap = true;
			EnemySprite.setPosition(1250, -50);
			flapIntro(deltaTime);
		}
		// Flap Loop  4
		else if (IntroTime >= 105 && IntroTime < 112) {
			EnemySprite.setScale(1.8, 1.8);
			flapLoop(deltaTime);
		}
		// Flap Outro 4
		else if (IntroTime >= 112 && IntroTime < 112.5) {
			flapOutro(deltaTime);
		}
		// Pant 4
		else if (IntroTime >= 112.5) {
			if (Static) {
				EnemySprite.setPosition(1150, 260);
				EnemySprite.setScale(1.5, 1.5);
				Static = false;
			}
			pantAnimation(deltaTime);
			if (EnemySound.getStatus() == Sound::Stopped) pant = true;
		}

		PositionX = EnemySprite.getPosition().x;
		PositionY = EnemySprite.getPosition().y;
	}

	// Draw
	void draw() {
		for (int i = 0; i < Eggs.size(); i++)  // Egg (Barf Shoot)
		{
			if (Eggs[i].isShooting)
				window.draw(Eggs[i].EggSprite);

		}

		for (int i = 0; i < feathers.size(); i++)   // Feathers (Feather Attack)
		{
			window.draw(feathers[i].featherSprite);
		}

		window.draw(EnemySprite);  // Boss

		for (int i = 0; i < bullets.size(); i++) {    // Boss's Bullets
			window.draw(bullets[i].bulletSprite);
		}

	}
};
struct OneYellowBird_Level3 {
	// Yellow Bird
	Sprite birdSprite;
	Texture currentTexture;
	IntRect subRect;
	float speedX, birdFrame, targetY, PositionX, PositionY;
	bool moveDown = true;
	Clock switchClock;

	// Sound
	Sound birdSound;
	SoundBuffer currentSound;
	bool died;

	// Bird Death
	bool isDead, isHit, disappear, hitbyWall;
	float deathFrame;
	int lives;
	IntRect deathRect;
	Clock deathClock, respawnClock;


	// Check Collision Player & Yellow Bird
	bool playerDamage, playerDecreased;

	// Update Bird's Animation
	void updateSubRect(IntRect& subRect, Texture& currentTexture, float photosNumber, float currentFrame) {
		auto size = currentTexture.getSize();

		subRect.left = size.x / photosNumber * int(currentFrame);
		subRect.top = 0;
		subRect.width = size.x / photosNumber;
		subRect.height = size.y;
	}

	// Variables Intializtion
	void setup() {
		currentTexture = yellowBirdTex_Level3;
		birdSprite.setTexture(currentTexture);
		birdSprite.setTextureRect(subRect);
		lives = 1, speedX = 2, birdFrame = 0;

		birdSprite.setScale(1, 1);

		//death
		isDead = false, isHit = false, disappear = false;
		deathFrame = 0;

		// Player Damage
		playerDamage = false, playerDecreased = true;

		//sound
		died = true, hitbyWall = false;

		updateSubRect(subRect, currentTexture, 15.0, birdFrame);
	}

	// Bird Damage
	void damage(PlayerSt_Level3 player, vector<BulletSt_Level3>& currentBullets) {
		for (int j = 0; j < currentBullets.size(); j++) {
			auto bulletPos = currentBullets[j].bulletSprite.getPosition();
			auto birdPos = birdSprite.getPosition();
			if (currentBullets[j].bulletSprite.getGlobalBounds().intersects(birdSprite.getGlobalBounds()) && bulletPos.x >= birdPos.x) {
				currentBullets[j].deleteMe = true;
				currentBullets[j].birdDamage = true;
				if (currentBullets[j].healthDecreased)
				{
					lives--;
				}
				currentBullets[j].healthDecreased = false;
				currentBullets.erase(currentBullets.begin() + j);
			}
		}
		if (player.playerSprite.getGlobalBounds().intersects(birdSprite.getGlobalBounds()) && !player.ghost.isDead) {
			lives--;
		}
	}

	// Bird Death
	void death() {
		if (died && !hitbyWall) {
			birdSound.setBuffer(birdDeathBuf_Level3);
			birdSound.play();
		}
		currentTexture = birdDeathTex_Level3;
		deathFrame += 0.25;
		if (deathFrame >= 11) {
			deathFrame = 0;
			birdSprite.setScale(0, 0);
			disappear = true;
			respawnClock.restart();
		}
		updateSubRect(deathRect, currentTexture, 11.0, deathFrame);
		birdSprite.setTextureRect(deathRect);
	}

	// Bird Respawn
	void respawn(float positionX, float positionY) {
		if (disappear && respawnClock.getElapsedTime().asSeconds() >= 1.5) {
			setup();
			birdSprite.setPosition(positionX, positionY);
		}
	}

	// Update
	void update(PlayerSt_Level3 player, vector<BulletSt_Level3>& currentBullets, float positionX, float positionY) {

		respawn(positionX, positionY);

		if (lives <= 0) {
			death();
			died = false;
			isDead = true;
			return;
		}

		deathClock.restart();

		birdFrame += 0.25;
		if (birdFrame >= 15)
			birdFrame -= 15;

		birdSprite.move(-speedX, 0);

		if (birdSprite.getPosition().x <= -200) {
			lives--;
			hitbyWall = true;
		}

		if (isHit) {
			lives--;
			isHit = false;
		}

		damage(player, currentBullets);

		birdSprite.setTexture(currentTexture);
		birdSprite.setTextureRect(subRect);

		updateSubRect(subRect, currentTexture, 15.0, birdFrame);
		PositionX = birdSprite.getPosition().x;
		PositionY = birdSprite.getPosition().y;


	}

	// Draw
	void draw() {
		window.draw(birdSprite);
	}


};
struct YellowBirdsSt_Level3 {

	OneYellowBird_Level3 birds[4];
	Clock batchClock;
	bool started = true;

	// Update Birds Positions based on their index
	void update(PlayerSt_Level3 player, vector<BulletSt_Level3>& currentBullets) {

		if (started) {
			for (int i = 0; i < 4; i++) {
				if (birds[i].moveDown) {
					birds[i].setup();
					birds[i].birdSprite.setPosition(1920 + (i * 200), 750);
				}
				else {
					birds[i].setup();

					birds[i].birdSprite.setPosition(1920 + (i * 200), 150);
				}
			}

		}

		started = false;
		for (int i = 0; i < 4; i++) {
			if (birds[i].moveDown)
				birds[i].update(player, currentBullets, (1920.0 + (i * 200.0)), 750);
			else
				birds[i].update(player, currentBullets, (1920.0 + (i * 200.0)), 150);
		}

		if (batchClock.getElapsedTime().asSeconds() > 15) {
			started = true;
			for (int i = 0; i < 4; i++) {
				birds[i].moveDown = !birds[i].moveDown;
			}
			batchClock.restart();
		}

	}

	// Draw
	void draw() {
		for (int i = 0; i < 4; i++) {
			birds[i].draw();
		}
	}
};
struct backgroundTrees_Level3 {
	Sprite trees[2];

	// Intializtion
	void setup() {
		for (int i = 0; i < 2; i++) {
			trees[i].setTexture(background2Tex_Level3);
			trees[i].setPosition(Vector2f(i * 1920, 0));
		}
	}

	// Update Position
	void update() {
		for (int i = 0; i < 2; i++) {
			trees[i].move(Vector2f(-5, 0));
		}
		if (trees[0].getPosition().x <= -1920) {
			trees[0].setPosition(Vector2f(1920, 0));
		}
		else if (trees[1].getPosition().x <= -1920) {
			trees[1].setPosition(Vector2f(1920, 0));
		}

	}

	// Draw
	void draw() {
		for (int i = 0; i < 2; i++) {					// Background's layers
			window.draw(trees[i]);
		}
	}
};
struct background_Level3 {
	// Background
	Sprite background[2];
	// Sound
	Texture currentTexture;

	// Intializtion
	void setup() {
		music.setBuffer(backgroundBuf_Level3);
		music.play();
		music.setLoop(true);
		currentTexture = backgroundTex_Level3;

		for (int i = 0; i < 2; i++) {
			background[i].setTexture(currentTexture);
			background[i].setPosition(Vector2f(i * 1920, 0));
		}
	}

	// Update
	void update(PlayerSt_Level3& player) {
		for (int i = 0; i < 2; i++) {
			background[i].move(Vector2f(-5, 0));
		}
		if (background[0].getPosition().x <= -1920) {
			background[0].setPosition(Vector2f(1920, 0));
		}
		else if (background[1].getPosition().x <= -1920) {
			background[1].setPosition(Vector2f(1920, 0));
		}

		if (player.ghost.isDead)
			music.stop();

	}

	// Draw
	void draw() {
		for (int i = 0; i < 2; i++) {
			window.draw(background[i]);
		}
	}

};

// Menu Functions
void TitleScreen(Event& event);
void MainMenu(menu menu, Event& event);
void Options(menu& menu, RenderWindow& window, Sound& SFXMusic, Event& event);
void Story(RenderWindow& window, Event& event);

// Map Functions
void mapPage();
bool checkCollision_map(PlayerMap_map& playerMap, RectangleShape route[], int rectNumbers);
bool checkCollision_map(PlayerMap_map& playerMap, RectangleShape& currentRect);

// Shop Functions
bool buy(itemSt_Shop item, Vector2f worldPos);
void DrawerOpenAnimationAndSound(itemSt_Shop& item, Sprite& leftDrawerSp, Sound& DrawerSound, float drawerSpeed, bool& DrawerOpenSound, bool& DrawerCloseSound, Vector2f& worldPos,
	float minLeftDrawerPosX, float maxLeftDrawerPosX);
void DrawerCloseAnimationAndSound(Sprite& leftDrawerSp, Sound& DrawerSound, float drawerSpeed, bool& DrawerOpenSound, bool& DrawerCloseSound, Vector2f& worldPos,
	float minLeftDrawerPosX, float maxLeftDrawerPosX);
void Shop_Page();

// Level 1 Functions
void Level1_Page();

// Level 2 Functions
void Level2_Page();

// Level 3 Functions
void Level3_Page(menu& menu, Event& event);
void checkcollision(EnemySt_Level3& enemy, PlayerSt_Level3& player, YellowBirdsSt_Level3& flappyBirds);   // Check Collision between Player & Boss and Player & Yellow Birds

void CUPHEAD()
{
	menu menu(windowSizeX, windowSizeY);
	Sound SFX;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		// To Reset The View From The Map
		if (PageNumber != 0)
		{
			View view(FloatRect(0, 0, windowSizeX, windowSizeY));
			window.setView(view);
		}

		if (PageNumber == 50) {
			TitleScreen(event);
		}
		else if (PageNumber == 1000) {
			MainMenu(menu, event);
		}
		else if (PageNumber == 0) {
			mapPage();
			isLastPageNumberMap = true;
		}
		else if (PageNumber == 1) {
			Options(menu, window, SFX, event);
		}
		else if (PageNumber == -1) {
			window.close();
		}
		else if (PageNumber == 10) {
			Shop_Page();
		}
		else if (PageNumber == 5)
			Level1_Page();
		else if (PageNumber == 6)
			Level2_Page();
		else if (PageNumber == 7)
			Level3_Page(menu, event);
	}
}
// Main
int main()
{
	window.setFramerateLimit(120);
	srand(time(0));
	setTexturesAndFonts();

	CUPHEAD();
	return 0;
}

// Common Functiona
void setTexturesAndFonts()
{
	/* Common Textures between 3 levels */
	ready_WallopTex_Level2.loadFromFile("images/level3/others/ReadyWallop.png");
	youDiedTextTex.loadFromFile("images/level3/others/youDiedText.png");
	hpBarTex.loadFromFile("images/level3/others/hpBar.png");
	ghostTex.loadFromFile("images/level3/player/PlayerGhost.png");
	deathMenuTex.loadFromFile("images/MainMenu/MenuAfterDeath.png");
	deathMenuFont.loadFromFile("fonts/MainMenu/deathMenu.ttf");

	// Winning Screen
	knockOutTex_Level2.loadFromFile("images/Winning/knockOut.png");
	backgroundWinTex.loadFromFile("images/Winning/backgroundWin.png");
	cupheadWinTex.loadFromFile("images/Winning/cupheadWin.png");
	cupheadTitleWinTex.loadFromFile("images/Winning/cupheadTitleWin.png");
	theResultsWinTex.loadFromFile("images/Winning/theResults.png");
	boardWinTex.loadFromFile("images/Winning/boardWin.png");
	lineWinTex.loadFromFile("images/Winning/lineWin.png");
	greyStarWinTex.loadFromFile("images/Winning/greyStar.png");
	yellowStarWinTex.loadFromFile("images/Winning/yellowStar.png");
	gradeCircleTex.loadFromFile("images/Winning/circle.png");
	// Font & Sounds
	winFont.loadFromFile("fonts/Winning/winningFont.ttf");
	knockOutBuffer.loadFromFile("Audios/Winning/knockoutSound.mp3");
	bossDefeatBuffer.loadFromFile("Audios/Winning/bossDefeat.wav");
	startClockBuffer.loadFromFile("Audios/Winning/beginClock.wav");
	endClockBuffer.loadFromFile("Audios/Winning/endClock.wav");
	tickBuffer.loadFromFile("Audios/Winning/tick.wav");
	starBuffer.loadFromFile("Audios/Winning/star.wav");
	winningScreenMusicBuffer.loadFromFile("Audios/Winning/winningScreenMusic.mp3");

	// Common Player Level 1 & 2
	// Player Tex
	playerStandingTex.loadFromFile("images/cuphead/standing.png");
	playerRunTex.loadFromFile("images/cuphead/run.png");
	playerJumpTex.loadFromFile("images/cuphead/jumb.png");
	playerRunShootStraightTex.loadFromFile("images/cuphead/shootRunStraight.png");
	playerRunDiagonalUpTex.loadFromFile("images/cuphead/shootDigonalUp.png");
	playerShootUpTex.loadFromFile("images/cuphead/shootUp.png");
	playerShootStraightTex.loadFromFile("images/cuphead/shootStraight.png");
	straightBulletTex.loadFromFile("images/cuphead/straightBullet.png");
	upBulletTex.loadFromFile("images/cuphead/upBullet.png");
	diagonalUpBulletTex.loadFromFile("images/cuphead/diagonalUpBullet.png");
	spawnTex.loadFromFile("images/cuphead/spawn.png");
	hpBarTex.loadFromFile("images/cuphead/hpBar.png");
	ghostTex.loadFromFile("images/cuphead/ghost.png");
	youDiedTextTex.loadFromFile("images/cuphead/youDiedText.png");
	bulletDeathTex.loadFromFile("images/cuphead/bulletDeath.png");
	playerCrawlTex.loadFromFile("images/cuphead/shootCrawling.png");
	playerHitTex.loadFromFile("images/cuphead/cupheadHit.png");
	// Player Buff
	playerJumpBuffer.loadFromFile("Audios/cuphead/jump.wav");
	playerHitBuffer.loadFromFile("Audios/cuphead/playerHit.wav");
	playerShootBuffer.loadFromFile("Audios/cuphead/shoot.wav");

	/* Main Menu */
	TitleScreenBackground.loadFromFile("images/MainMenu/TitleScreen.png");
	MenuBackground.loadFromFile("images/MainMenu/MenuBackground.png");
	CupheadnMugman.loadFromFile("images/MainMenu/CupheadnMugman2.png");
	font.loadFromFile("fonts/MainMenu/Cat_Comic.otf");
	//IntroTex.loadFromFile("images/story/intro.png");
	//Story01Tex.loadFromFile("images/story/page1-2.png");
	//Story02Tex.loadFromFile("images/story/page2-3.png");
	//Story03Tex.loadFromFile("images/story/page3-4.png");
	//Story04Tex.loadFromFile("images/story/page4-5.png");
	//Story05Tex.loadFromFile("images/story/page5-6.png");
	//Story06Tex.loadFromFile("images/story/page6-7.png");
	//Story07Tex.loadFromFile("images/story/page7-8.png");
	//Story08Tex.loadFromFile("images/story/page8-9.png");
	//Story09Tex.loadFromFile("images/story/page9-10.png");
	//Story10Tex.loadFromFile("images/story/page10-11.png");
	//Story11Tex.loadFromFile("images/story/page12-13.png");
	//Story12Tex.loadFromFile("images/story/page13-14.png");
	//Story13Tex.loadFromFile("images/story/page14-15.png");
	//Story14Tex.loadFromFile("images/story/page15-16.png");
	//Story15Tex.loadFromFile("images/story/page16-17.png");
	//Story16Tex.loadFromFile("images/story/page17-18.png");
	//OutroTex.loadFromFile("images/story/outro.png");
	optionsBackground.loadFromFile("images/MainMenu/optionsMenu.png");
	MenuBackgroungMusic.loadFromFile("Audios/MainMenu/MenuBackgroundMusic.mp3");
	StoryBackgroungMusic.loadFromFile("Audios/MainMenu/StoryBackgroundMusic.mp3");

	// Map
	mapTex_map.loadFromFile("map/map.png");
	standingTex_map.loadFromFile("map/standing.png");
	runStraightTex_map.loadFromFile("map/runStraight.png");
	runDiagonalUpTex_map.loadFromFile("map/runDiagonalUp.png");
	runDiagonalDownTex_map.loadFromFile("map/runDiagonalDown.png");
	runUpTex_map.loadFromFile("map/runUp.png");
	runDownTex_map.loadFromFile("map/runDown.png");
	boardLevelTex_map.loadFromFile("map/levelBoard.png");
	levelNameTex_map.loadFromFile("map/levelNames.png");
	entryLevelBackgroundTex_map.loadFromFile("map/entryLevelBackground.png");
	coinOverworld_map.loadFromFile("map/coinOverworld.png");
	buttonXTex_map.loadFromFile("map/x.png");
	GuideMapTex_map.loadFromFile("map/idle.png");
	GuideTalkingTex_map.loadFromFile("map/talking.png");
	speechTex_map.loadFromFile("map/speech.png");
	LockTex_map.loadFromFile("map/LevelLocked.png");
	// Map Font
	mapFont_map.loadFromFile("map/mapFont.otf");
	guideFont_map.loadFromFile("map/guide.otf");
	// Map Sound
	mapMusicBuffer_map.loadFromFile("map/sounds/mapMusic.mp3");
	playerWalkBuffer_map.loadFromFile("map/sounds/playerWalk.wav");
	selectLevelBuffer_map.loadFromFile("map/sounds/selectLevel.wav");
	afterWinningBuffer_map.loadFromFile("map/sounds/afterWinning.wav");

	/* Shop */
	// Textures
	Background_Shop.loadFromFile("images/store/Background_Shop.png");
	LeftDrawer_Shop.loadFromFile("images/store/LeftDrawer_Shop.png");
	RightDrawer_Shop.loadFromFile("images/store/RightDrawer_Shop.png");
	PorkrindWelcome_Shop.loadFromFile("images/store/PorkrindWelcome_Shop.png");
	PorkrindIdle_Shop.loadFromFile("images/store/PorkrindIdle_Shop.png");
	PorkrindNods_Shop.loadFromFile("images/store/PorkrindNods_Shop.png");
	PorkrindCheckClock_Shop.loadFromFile("images/store/PorkrindCheckClock_Shop.png");
	PorkrindGoodbye_Shop.loadFromFile("images/store/PorkrindGoodbye_Shop.png");
	HealthItem_Shop.loadFromFile("images/store/healthItem_Shop.png");
	DamageItem_Shop.loadFromFile("images/store/DamageItem_Shop.png");
	ItemSold_Shop.loadFromFile("images/store/ItemSold_Shop.png");
	Infoboard_Shop.loadFromFile("images/store/board_Shop.png");
	B_ButtonTex.loadFromFile("images/store/B_Button.png");
	A_ButtonTex.loadFromFile("images/store/A_Button.png");
	CoinTex_Shop.loadFromFile("images/store/Coin_Shop.png");
	// Fonts
	storeFont.loadFromFile("fonts/store/CupheadMemphis-Medium.otf");
	// Audios
	BackgroundMusic_Shop.loadFromFile("Audios/store/PorkrindShop_MusicBg.mp3");
	PorkrindWelcomeBuf_Shop.loadFromFile("Audios/store/PorkrindWelcome.wav");
	PorkrindGoodByeBuf_Shop.loadFromFile("Audios/store/PorkrindGoodbye.wav");
	ItemSoldBuf_Shop.loadFromFile("Audios/store/ItemSold.wav");
	DrawerOpenBuf_Shop.loadFromFile("Audios/store/DrawerOpen.wav");
	DrawerCloseBuf_Shop.loadFromFile("Audios/store/DrawerClose.wav");
	SelectSmthBuf_Shop.loadFromFile("Audios/store/SelectSmth.wav");

	/* Level 1 */
	// Textures
	blueSkt_Level1Tex.loadFromFile("images/Level1/blueSky.png");
	for (int i = 0; i < 7; i++)
		clouds_Level1Tex[i].loadFromFile("images/Level1/clouds/" + to_string(i + 1) + ".png");
	for (int i = 0; i < 5; i++)
		bushes_Level1Tex[i].loadFromFile("images/Level1/bushes/" + to_string(i + 1) + ".png");
	for (int i = 0; i < 2; i++)
		tree_Level1Tex[i].loadFromFile("images/Level1/tree/" + to_string(i + 1) + ".png");
	tires_Level1Tex.loadFromFile("images/Level1/tires.png");
	for (int i = 0; i < 6; i++)
		ground_Level1Tex[i].loadFromFile("images/Level1/ground/" + to_string(i + 1) + ".png");
	mainGround_Level1Tex.loadFromFile("images/Level1/mainGround.png");
	for (int i = 0; i < 2; i++)
		fence_Level1Tex[i].loadFromFile("images/Level1/fence/" + to_string(i + 1) + ".png");

	background_Level1Tex.loadFromFile("images/Level1/background.jpg");
	earthBreak_Level1Tex.loadFromFile("images/Level1/phase1/earthBreak.png");
	potatoSpawn_Level1Tex.loadFromFile("images/Level1/phase1/potatoSpawn.png");
	potatoAttack_Level1Tex.loadFromFile("images/Level1/phase1/potatoAttack.png");
	potatoBullet_Level1Tex.loadFromFile("images/Level1/phase1/potatoBullet.png");
	potatoDeath_Level1Tex.loadFromFile("images/Level1/phase1/potatoDeath.png");
	carrotSpawn_Level1Tex.loadFromFile("images/Level1/phase2/carrotSpawn.png");
	carrotAttack_Level1Tex.loadFromFile("images/Level1/phase2/carrotAttack.png");
	carrotAttack2_level1Tex.loadFromFile("images/Level1/phase2/carrotAttack2.png");
	carrotBullet_level1Tex.loadFromFile("images/Level1/phase2/carrotBullet.png");
	carrotRings_Level1Tex.loadFromFile("images/Level1/phase2/carrotRings.png");
	carrotDeath_Level1Tex.loadFromFile("images/Level1/phase2/carrotDeath.png");
	// Sounds
	musicBuffer_Level1.loadFromFile("Audios/Level1/level1Sound.mp3");
	potatoGroundBuffer_Level1.loadFromFile("Audios/Level1/potatoGround.wav");
	potatoSpitBuffer_Level1.loadFromFile("Audios/Level1/potatoSpit.wav");
	carrotGroundBuffer_Level1.loadFromFile("Audios/Level1/carrotGround.wav");
	carrotRingsBuffer_Level1.loadFromFile("Audios/Level1/carrotRings.wav");
	smallCarrotDeathBuffer_Level1.loadFromFile("Audios/Level1/smallCarrotDeath.wav");

	/* Level 2 */
	// Textures
	// Background
	lightBackgroundTex_Level2.loadFromFile("images/Level2/Background_Light.png");
	lightTowerTex_Level2.loadFromFile("images/Level2/Tower_Light.png");
	midCloudIdleTex_Level2.loadFromFile("images/Level2/cloud_idle.png");
	midCloudStandingTex_Level2.loadFromFile("images/Level2/cloud_animation.png");
	cloudForegroundLightTex_Level2.loadFromFile("images/Level2/cloud_light_foreground.png");
	cloudbackgroundLightTex_Level2.loadFromFile("images/Level2/cloud_light_background.png");
	// Dragon
	// Phase 1
	dragonIdleTex_Level2.loadFromFile("images/Level2/idle.png");
	dragonIntroTex_Level2.loadFromFile("images/Level2/intro.png");
	dragonMeteorShootTex_Level2.loadFromFile("images/Level2/meteorShoot.png");
	dragonPeashotTex_Level2.loadFromFile("images/Level2/peashootAttack.png");
	fireBallTex_Level2.loadFromFile("images/Level2/meteor.png");
	ringTex_Level2.loadFromFile("images/Level2/greenRing.png");
	eyesAttackTex_Level2.loadFromFile("images/Level2/peashotattackeyes.png");
	// Phase 2
	dragonIntroPhase2Tex_Level2.loadFromFile("images/Level2/intro&idlePhase2.png");
	drgonTongueTex_Level2.loadFromFile("images/Level2/tongue.png");
	dragonDashTex_Level2.loadFromFile("images/Level2/dashphase2.png");
	firstEnemyTex_Level2.loadFromFile("images/Level2/firstEnemy.png");
	enemyRunTex_Level2.loadFromFile("images/Level2/runEnemy.png");
	enemyReadyTex_Level2.loadFromFile("images/Level2/readyEnemy.png");
	enemyAttackTex_Level2.loadFromFile("images/Level2/attackEnemy.png");
	firePhase2Tex_Level2.loadFromFile("images/Level2/fire.png");
	smokePhase2Tex_Level2.loadFromFile("images/Level2/smoke.png");
	dragonDeathPhase2Tex_Level2.loadFromFile("images/Level2/deathPhase2.png");
	// Sounds
	// Phase 1
	levelTwoBuffer_Level2.loadFromFile("Audios/Level2/level2Sound.mp3");
	meteorStartBuffer_Level2.loadFromFile("Audios/Level2/meteorStart.wav");
	meteorAttackBuffer_Level2.loadFromFile("Audios/Level2/meteorAttack.wav");
	dragonIdleBuffer_Level2.loadFromFile("Audios/Level2/dragonIdle.wav");
	peashotAttackBuffer_Level2.loadFromFile("Audios/Level2/peashotAttaack.wav");
	peashotStartBuffer_Level2.loadFromFile("Audios/Level2/peashotStart.wav");
	peashotEndBuffer_Level2.loadFromFile("Audios/Level2/peashotEnd.wav");
	// Phase 2
	dashBuffer_Level2.loadFromFile("Audios/Level2/Dash.wav");
	dragonIntroBuffer_Level2.loadFromFile("Audios/Level2/dragonIntroPahse2.wav");
	fireBuffer_Level2.loadFromFile("Audios/Level2/fire.mp3");
	smokeBuffer_Level2.loadFromFile("Audios/Level2/smoke.mp3");
	firemarcherJumpBuffer_Level2.loadFromFile("Audios/Level2/firemarcherJump.wav");
	firemarcherReadyBuffer_Level2.loadFromFile("Audios/Level2/firemarcherReady.wav");

	/* Level 3 */
	// player
	CupheadIntro.loadFromFile("images/level3/player/PlayerIntro_Level3.png");
	transDownTex_Level3.loadFromFile("images/level3/player/PlayerTransDown_Level3.png");
	transUpTex_Level3.loadFromFile("images/level3/player/PlayerTransUp_Level3.png");
	straightTex_Level3.loadFromFile("images/level3/player/PlayerStraight_Level3.png");
	straightBulletTex_Level3.loadFromFile("images/level3/player/PlayerBullet_Level3.png");
	spawnTex_Level3.loadFromFile("images/level3/player/PlayerBulletSpawn_Level3.png");
	hitDustTex_Level3.loadFromFile("images/level3/player/HitDust_Level3.png");
	// Wally Warples (Boss)
	enemyIntroTex_Level3.loadFromFile("images/level3/Boss/BossIntro_Level3.png");
	enemyIntro2Tex_Level3.loadFromFile("images/level3/Boss/BossSecondIntro_Level3.png");
	enemyStaticTex_Level3.loadFromFile("images/level3/Boss/BossIdle_Level3.png");
	enemyBarfTex_Level3.loadFromFile("images/level3/Boss/BossBarf_Level3.png");
	enemySteamTex_Level3.loadFromFile("images/level3/Boss/BossSteam_Level3.png");
	enemyFlapIntroTex_Level3.loadFromFile("images/level3/Boss/BossFlapIntro_Level3.png");
	enemyFlapLoopTex_Level3.loadFromFile("images/level3/Boss/BossFlapLoop_Level3.png");
	enemyFlapOutroTex_Level3.loadFromFile("images/level3/Boss/BossFlapOutro_Level3.png");
	enemyPantTex_Level3.loadFromFile("images/level3/Boss/BossPant_Level3.png");
	FeatherTex_Level3.loadFromFile("images/level3/Boss/Feather_Level3.png");
	enemyDeathTex_Level3.loadFromFile("images/level3/Boss/BossDeath_Level3.png");
	EggDeathTex_Level3.loadFromFile("images/level3/Boss/BossEggDeath_Level3.png");
	EggTex_Level3.loadFromFile("images/level3/Boss/BossEgg_Level3.png");
	handGunTex_Level3.loadFromFile("images/level3/Boss/BossHandGun_Level3.png");
	handBulletTex_Level3.loadFromFile("images/level3/Boss/BossBullet_Level3.png");
	handBulletDeathTex_Level3.loadFromFile("images/level3/Boss/BossBulletDeath_Level3.png");
	// Yellow Birds
	yellowBirdTex_Level3.loadFromFile("images/level3/yellowBird/yellowBird.png");
	birdDeathTex_Level3.loadFromFile("images/level3/yellowBird/birdDeath.png");
	// Background
	backgroundTex_Level3.loadFromFile("images/level3/others/background.png");
	background2Tex_Level3.loadFromFile("images/level3/others/backgroundTrees.png");
	knockoutTextTex_Level3.loadFromFile("images/level3/others/knockout.png");
	// Audios
	EnemyClockIntroBuf_Level3.loadFromFile("Audios/level3/Boss_Intro_full.wav");
	EnemySecondIntroBuf_Level3.loadFromFile("Audios/level3/Boss_Intro_b.wav");
	EnemyBarfBuf_Level3.loadFromFile("Audios/level3/EnemyBarfBuffer.wav");
	EggDeathBuf_Level3.loadFromFile("Audios/level3/EnemyEggDeath.wav");
	EnemyHandGunBuf_Level3.loadFromFile("Audios/level3/EnemyHandGun.wav");
	EnemyFlapBuf_Level3.loadFromFile("Audios/level3/EnemyFlap.wav");
	EnemySteamBuf_Level3.loadFromFile("Audios/level3/EnemySteam.wav");
	EnemyPantBuf_Level3.loadFromFile("Audios/level3/EnemyPant.wav");
	FeatherAttackBuf_Level3.loadFromFile("Audios/level3/EnemyFeatherAttack.wav");
	EnemyDeathBuf_Level3.loadFromFile("Audios/level3/EnemyDeath.wav");
	birdDeathBuf_Level3.loadFromFile("Audios/level3/YellowBirdDeath.wav");
	backgroundBuf_Level3.loadFromFile("Audios/level3/backgroundMusic.mp3");
	PlayerDeathBuf_Level3.loadFromFile("Audios/level3/PlayerDeath.wav");
	youDiedTextBuf.loadFromFile("Audios/level3/PlayerGameOver.wav");
	ReadyWallopBuf_Level3.loadFromFile("Audios/level3/ReadyWallop.mp3");
	PlayerBulletBuf_Level3.loadFromFile("Audios/level3/PlayerBullet.wav");
	knockoutTextBuf_Level3.loadFromFile("Audios/level3/Knockout.wav");
}
// Common Functiona
int randomNumber(int from, int to)
{
	if (from > to)
		swap(from, to);
	return (rand() % (to - from + 1)) + from;
}
bool fadeToBlack(RectangleShape& rectangleFade, Clock& clock) {
	// Calculate the alpha value based on elapsed time
	float alpha = clock.getElapsedTime().asSeconds() * 255 / 3; // 3 seconds to fade to black

	// Ensure alpha doesn't exceed 255 (maximum transparency)
	if (alpha > 255) {
		alpha = 255;
	}
	rectangleFade.setFillColor(sf::Color(0, 0, 0, static_cast<Uint8>(alpha)));

	return (alpha >= 255);
}
void shadowBackgroundSetup(Sprite& shadowBackgroundSprite, Texture& currentTexture)
{
	shadowBackgroundSprite.setTexture(currentTexture);
	shadowBackgroundSprite.setScale(windowSizeX / shadowBackgroundSprite.getLocalBounds().width,
		windowSizeY / shadowBackgroundSprite.getLocalBounds().height);
	shadowBackgroundSprite.setColor(Color(0, 0, 0, 140));
}

// Menu Functions
void TitleScreen(Event& event) {
	TitleScreenSt Title;
	Title.setup();

	while (window.isOpen() && PageNumber == 50) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				PageNumber = 1000; //go to the main menu
			}
		}

		Title.update();

		window.clear();
		Title.draw();
		window.display();
	}
}
void MainMenu(menu menu, Event& event)
{
	Sprite background;
	background.setTexture(MenuBackground);
	background.setScale(1.1, 1.1);
	if (isLastPageNumberMap)
	{
		music.setBuffer(MenuBackgroungMusic);
		music.play();
		music.setLoop(true);
		isLastPageNumberMap = false;
	}


	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					menu.MoveUp();
				}
				if (event.key.code == Keyboard::Down) {
					menu.MoveDown();
				}
				if (event.key.code == Keyboard::Return) {
					if (menu.pressed() == 0) {
						PageNumber = 0;
					}
					if (menu.pressed() == 1) {
						PageNumber = 1;
					}
					if (menu.pressed() == 2) {
						PageNumber = -1;
					}
				}
			}
		}
		window.clear();

		if (PageNumber != 1000) break;

		window.draw(background);
		menu.draw(window);
		window.display();
	}
}
void Options(menu& menu, RenderWindow& window, Sound& SFXMusic, Event& event)
{
	Sprite background, outerBackground;
	Text Title;
	background.setTexture(optionsBackground);
	outerBackground.setTexture(MenuBackground);
	outerBackground.setScale(1.1, 1.1);
	background.setScale(1, 1);
	background.setPosition(window.getSize().x / 2 - optionsBackground.getSize().x / 2, window.getSize().y / 2 - optionsBackground.getSize().y / 2 + 10);

	Title.setFont(font);
	Title.setString("Options");
	Title.setCharacterSize(70);
	Title.setPosition(850, 200);
	Title.setFillColor(Color{ 128,128,128 });
	Title.setOutlineColor(Color::Black);
	Title.setOutlineThickness(2);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				PageNumber = 1000;
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					menu.MoveUpOp();
				}
				if (event.key.code == Keyboard::Down) {
					menu.MoveDownOp();
				}
				if (event.key.code == Keyboard::Right) {
					menu.volumeLevel[menu.isPressed()]++; // Increase volume
					if (menu.volumeLevel[menu.isPressed()] > 10) {
						menu.volumeLevel[menu.isPressed()] = 10; //not exceeding max
					}
					if (menu.isPressed() == 1) {
						int currentVolume = SFXMusic.getVolume() + 10;
						if (currentVolume < 100) SFXMusic.setVolume(currentVolume);
						else {
							currentVolume = 100;
							SFXMusic.setVolume(currentVolume);
						}
					}
					else if (menu.isPressed() == 2) {
						int currentVolume = music.getVolume() + 10;
						if (currentVolume < 100) music.setVolume(currentVolume);
						else {
							currentVolume = 100;
							music.setVolume(currentVolume);
						}
					}
					else {
						int currentSFXVolume = SFXMusic.getVolume() + 10;
						int currentMusicVolume = music.getVolume() + 10;
						if (currentSFXVolume < 100) SFXMusic.setVolume(currentSFXVolume);
						else {
							currentSFXVolume = 100;
							SFXMusic.setVolume(currentSFXVolume);
						}
						if (currentMusicVolume < 100) music.setVolume(currentMusicVolume);
						else {
							currentMusicVolume = 100;
							music.setVolume(currentMusicVolume);
						}

					}


				}
				if (event.key.code == Keyboard::Left) {
					menu.volumeLevel[menu.isPressed()]--; // Decrease volume 
					if (menu.volumeLevel[menu.isPressed()] < 0) {
						menu.volumeLevel[menu.isPressed()] = 0; //not exceeding min
					}
					if (menu.isPressed() == 1) {
						int currentVolume = SFXMusic.getVolume() - 10;
						if (currentVolume > 0) SFXMusic.setVolume(currentVolume);
						else {
							currentVolume = 0;
							SFXMusic.setVolume(currentVolume);
						}
					}
					else if (menu.isPressed() == 2) {
						int currentVolume = music.getVolume() - 10;
						if (currentVolume > 0) music.setVolume(currentVolume);
						else {
							currentVolume = 0;
							music.setVolume(currentVolume);
						}
					}
					else {
						int currentSFXVolume = SFXMusic.getVolume() - 10;
						int currentMusicVolume = music.getVolume() - 10;
						if (currentSFXVolume > 0) SFXMusic.setVolume(currentSFXVolume);
						else {
							currentSFXVolume = 0;
							SFXMusic.setVolume(currentSFXVolume);
						}
						if (currentMusicVolume > 0) music.setVolume(currentMusicVolume);
						else {
							currentMusicVolume = 0;
							music.setVolume(currentMusicVolume);
						}

					}

				}
			}
		}
		window.clear();

		if (PageNumber != 1) break;

		// Draw background
		window.draw(outerBackground);
		window.draw(background);
		window.draw(Title);

		// Draw options
		menu.drawOptions(window);

		// Update and draw volume options
		for (int i = 0; i < 3; ++i) {
			//current volume level
			string volumeText;
			switch (i) {
			case 0:
				volumeText = "MASTER VOLUME: ";
				break;
			case 1:
				volumeText = "SFX VOLUME: ";
				break;
			case 2:
				volumeText = "MUSIC VOLUME: ";
				break;
			}
			// update hyphens based on current volume
			for (int j = 0; j < menu.volumeLevel[i]; ++j) {
				volumeText += "-";
			}
			//update text
			menu.options[i].setString(volumeText);

			//draw
			window.draw(menu.options[i]);
		}

		window.display();
	}
}
void Story(RenderWindow& window, Event& event) {
	StorySt story;
	story.setup();

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			PageNumber = 1000;

		story.update();

		window.clear();

		if (PageNumber != 0) break;

		story.draw();

		window.display();
	}

}

// Map Functions
void mapPage()
{
	// player
	PlayerMap_map playerMap;
	CoinMap_map coinMap;

	coinMap.setup();
	playerMap.setup();

	int const rectNumbers = 6;
	RectangleShape route[rectNumbers];

	route[0].setPosition(510, 445);
	route[0].setSize(Vector2f(50, 50));
	route[1].setPosition(720, 500);
	route[1].setSize(Vector2f(4, 160));
	route[1].setRotation(70);
	route[2].setPosition(740, 525);
	route[2].setSize(Vector2f(120, 0.2));
	route[3].setPosition(900, 330);
	route[3].setSize(Vector2f(95, 380));
	route[4].setPosition(980, 620);
	route[4].setSize(Vector2f(110, 150));
	route[5].setPosition(980, 280);
	route[5].setSize(Vector2f(465, 15));

	Vector2f lastPos;

	RectangleShape Level1_Rect, Level2_Rect, Level3_Rect, Shop_Rect, Guide_Rect;
	Level1_Rect.setPosition(870, 690);
	Level1_Rect.setSize(Vector2f(7, 7));
	Level2_Rect.setPosition(972, 485);
	Level2_Rect.setSize(Vector2f(7, 7));
	Level3_Rect.setPosition(1396, 284);
	Level3_Rect.setSize(Vector2f(7, 7));
	Shop_Rect.setPosition(1002, 586);
	Shop_Rect.setSize(Vector2f(7, 7));
	Guide_Rect.setPosition(842, 517);
	Guide_Rect.setSize(Vector2f(7, 7));

	buttonXSt_map buttonX;
	buttonX.setup();

	entryLevelScreen_map levelScreen;
	levelScreen.setup(playerMap);
	int currentState = -1;

	// Guide
	guideSt_map GuideMap;
	GuideMap.setup();

	speechSt_map speech;
	speech.setup();

	// Sounds
	Sound playerWalkSound, selectLevelSound, afterWinningSound;
	music.setBuffer(mapMusicBuffer_map);
	playerWalkSound.setBuffer(playerWalkBuffer_map);
	selectLevelSound.setBuffer(selectLevelBuffer_map);
	afterWinningSound.setBuffer(afterWinningBuffer_map);

	Clock walkSoundClock;

	RectangleShape rectangleFade(Vector2f(windowSizeX, windowSizeY));
	Clock fadeToBlackClock;
	bool fadeCompleted = false;

	music.play();
	music.setLoop(true);

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			PageNumber = 1000;
			break;
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (speech.isClicked)
				speech.handleKeyPress(GuideMap, event);
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::X && !levelScreen.isClicked)
			{
				if (checkCollision_map(playerMap, Level1_Rect))
					currentState = 0;
				if (checkCollision_map(playerMap, Level2_Rect))
					currentState = 1;
				if (checkCollision_map(playerMap, Level3_Rect))
					currentState = 2;
				if (checkCollision_map(playerMap, Shop_Rect))
					currentState = 3;

				if (currentState != -1)
				{
					levelScreen.isClicked = true;
					music.stop();
					selectLevelSound.play();
					levelScreen.update(playerMap, currentState);
				}
				if (checkCollision_map(playerMap, Guide_Rect))
					speech.isClicked = true;
			}
		}
		// Movment
		if (!levelScreen.isClicked && !speech.isClicked)
		{
			if (Keyboard::isKeyPressed(Keyboard::A))
				playerMap.moveLeft();
			if (Keyboard::isKeyPressed(Keyboard::D))
				playerMap.moveRight();
			if (Keyboard::isKeyPressed(Keyboard::W))
				playerMap.moveUp();
			if (Keyboard::isKeyPressed(Keyboard::S))
				playerMap.moveDown();
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
					playerMap.moveDoignalUpRight();
				if (Keyboard::isKeyPressed(Keyboard::A))
					playerMap.moveDoignalUpLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
					playerMap.moveDoignalDownRight();
				if (Keyboard::isKeyPressed(Keyboard::A))
					playerMap.moveDoignalDownLeft();
			}
		}
		if ((playerMap.moveX || playerMap.moveY) && walkSoundClock.getElapsedTime().asMilliseconds() >= 300)
		{
			playerWalkSound.play();
			walkSoundClock.restart();
		}
		// To Chcek Not Getting Out Of Bounds
		lastPos = { playerMap.playerSpriteM.getPosition() };
		playerMap.update();
		if (!checkCollision_map(playerMap, route, rectNumbers))
			playerMap.playerSpriteM.setPosition(lastPos);

		coinMap.update(playerMap);
		buttonX.update(playerMap);
		GuideMap.update(speech.isClicked);

		if (levelScreen.isClicked)
		{
			if ((currentState > 0 && currentState < 3 && levelisDone[currentState - 1]) || currentState == 0 || currentState == 3)
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			else if (fadeToBlackClock.getElapsedTime().asMilliseconds() >= 2000)
				break;
		}
		else
			fadeToBlackClock.restart();

		if (fadeCompleted)
		{
			if (currentState == 0)
				PageNumber = 5;
			if (currentState == 1)
				PageNumber = 6;
			if (currentState == 2)
				PageNumber = 7;
			if (currentState == 3)
				PageNumber = 10;
			break;
		}

		window.clear();
		playerMap.draw();
		if (checkCollision_map(playerMap, Level1_Rect) || checkCollision_map(playerMap, Level2_Rect) || checkCollision_map(playerMap, Level3_Rect)
			|| checkCollision_map(playerMap, Shop_Rect) || checkCollision_map(playerMap, Guide_Rect))
			buttonX.draw();

		coinMap.draw();
		GuideMap.draw();
		if (speech.isClicked)
			speech.draw(GuideMap);

		if (levelScreen.isClicked)
		{
			levelScreen.draw(currentState);
			if ((currentState > 0 && currentState < 3 && levelisDone[currentState - 1]) || currentState == 0 || currentState == 3)
				window.draw(rectangleFade);
		}
		window.display();
	}
}
bool checkCollision_map(PlayerMap_map& player, RectangleShape route[], int rectNumbers) {
	for (int i = 0; i < rectNumbers; i++)
	{
		if (player.playerSpriteM.getGlobalBounds().intersects(route[i].getGlobalBounds()))
			return true;
	}
	return false;
}
bool checkCollision_map(PlayerMap_map& playerMap, RectangleShape& currentRect)
{
	if (playerMap.playerSpriteM.getGlobalBounds().intersects(currentRect.getGlobalBounds()))
		return true;

	return false;
}

// Shop Functions
void Shop_Page()
{
	BackgroundSt_Shop bg;
	bg.setup();

	// Define limits for the drawer movement
	const float minLeftDrawerPosX = 190; // Minimum X position of the drawer
	const float maxLeftDrawerPosX = 95 + bg.leftDrawerSp.getTexture()->getSize().x; // Maximum X position of the drawer
	float drawerSpeed = 10;

	// Additional variables for item description
	bool showHealthDescription = false;
	bool showDamageDescription = false;

	porkrindSt_Shop porkrind;
	porkrind.setup();

	itemSt_Shop healthItem;
	healthItem.setup(HealthItem_Shop, 2.0, 150, 350);
	HealthDescriptionSt_Shop healthDescrption;
	healthDescrption.setup();

	itemSt_Shop DamageItem;
	DamageItem.setup(DamageItem_Shop, 2.0, 350, 420);
	DamageDescriptionSt_Shop damageDescription;
	damageDescription.setup();

	PurchasedSt_Shop purchased;
	purchased.setup();

	//Coins
	CoinMap_map coin;
	coin.setup();
	PlayerMap_map player;
	int healthItemPrice = 2, DamageItemPrice = 2;

	// Game Loop
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// Get the position of the cursor
		Vector2i mousePos = Mouse::getPosition(window);
		// Convert mouse position to world coordinates
		Vector2f worldPos = window.mapPixelToCoords(mousePos);


		// Update
		if (porkrind.End) return;

		porkrind.update();
		healthItem.update(HealthItem_Shop, 2.0, worldPos);
		DamageItem.update(DamageItem_Shop, 2.0, worldPos);
		coin.update(player);

		if (buy(healthItem, worldPos)) {
			porkrind.selectSmth = true;
			healthItem.isBought = true;
			if (!healthItem.coinsSubtracted && coins >= healthItemPrice)
			{
				coins -= healthItemPrice;
				healthItem.coinsSubtracted = true;
				additionlLives += 1;
			}
		}
		if (buy(DamageItem, worldPos)) {
			porkrind.selectSmth = true;
			DamageItem.isBought = true;
			if (!DamageItem.coinsSubtracted && coins >= DamageItemPrice)
			{
				coins -= DamageItemPrice;
				DamageItem.coinsSubtracted = true;
				DamageBought += 5;
			}
		}

		// Move the drawer if Something is selected 
		if (healthItem.isSelected) {
			DrawerOpenAnimationAndSound(healthItem, bg.leftDrawerSp, bg.DrawerSound, drawerSpeed, bg.DrawerOpenSound, bg.DrawerCloseSound, worldPos, minLeftDrawerPosX, maxLeftDrawerPosX);
		}
		else if (DamageItem.isSelected) {
			DrawerOpenAnimationAndSound(DamageItem, bg.leftDrawerSp, bg.DrawerSound, drawerSpeed, bg.DrawerOpenSound, bg.DrawerCloseSound, worldPos, minLeftDrawerPosX, maxLeftDrawerPosX);
		}
		else DrawerCloseAnimationAndSound(bg.leftDrawerSp, bg.DrawerSound, drawerSpeed, bg.DrawerOpenSound, bg.DrawerCloseSound, worldPos, minLeftDrawerPosX, maxLeftDrawerPosX);


		// Clear
		window.clear();

		// Draw
		bg.draw_back();
		if (healthItem.isSelected && !healthItem.isBought) healthDescrption.draw();
		else if (healthItem.isSelected && healthItem.isBought) {
			purchased.draw(healthDescrption.Price);

		}

		if (DamageItem.isSelected && !DamageItem.isBought) damageDescription.draw();
		else if (DamageItem.isSelected && DamageItem.isBought) {
			purchased.draw(damageDescription.Price);
		}

		bg.draw_middle();
		porkrind.draw();
		healthItem.draw();
		DamageItem.draw();
		bg.draw_front();
		coin.draw();

		// Display
		window.display();
	}
}
bool buy(itemSt_Shop item, Vector2f worldPos) {
	bool isBought = false;
	bool isIntersecting = item.item.getGlobalBounds().contains(worldPos);
	if (isIntersecting) {
		if (Keyboard::isKeyPressed(Keyboard::A) && coins >= 2)
			isBought = true;
	}
	return isBought;
}
void DrawerOpenAnimationAndSound(itemSt_Shop& item, Sprite& leftDrawerSp, Sound& DrawerSound, float drawerSpeed, bool& DrawerOpenSound, bool& DrawerCloseSound, Vector2f& worldPos,
	float minLeftDrawerPosX, float maxLeftDrawerPosX)
{
	if ((item.ShowInfo(worldPos) && leftDrawerSp.getPosition().x + leftDrawerSp.getTexture()->getSize().x > minLeftDrawerPosX)) {
		DrawerCloseSound = true;
		if (DrawerOpenSound) {
			DrawerSound.setBuffer(DrawerOpenBuf_Shop);
			DrawerSound.play();
			DrawerOpenSound = false;
		}
		leftDrawerSp.move(-drawerSpeed, 0);
	}
}
void DrawerCloseAnimationAndSound(Sprite& leftDrawerSp, Sound& DrawerSound, float drawerSpeed, bool& DrawerOpenSound, bool& DrawerCloseSound, Vector2f& worldPos,
	float minLeftDrawerPosX, float maxLeftDrawerPosX)
{
	if (leftDrawerSp.getPosition().x + leftDrawerSp.getTexture()->getSize().x < maxLeftDrawerPosX) {
		DrawerOpenSound = true;
		if (DrawerCloseSound) {
			DrawerSound.setBuffer(DrawerCloseBuf_Shop);
			DrawerSound.play();
			DrawerCloseSound = false;
		}
		leftDrawerSp.move(drawerSpeed, 0);
	}
}

// Level 1 Functions
void Level1_Page()
{
	PlayerSt_Level1 player;
	player.setup();
	Clock shootClock;

	backgroundSt_Level1 background;
	background.setup();
	Sprite shadowBackground;
	shadowBackgroundSetup(shadowBackground, blueSkt_Level1Tex);

	Clock startLevelClock;
	int startingTime = 2500;

	readyWallopSt readyWallopText;
	readyWallopText.setup();

	level1 level1;
	level1.setup();

	// All Levels
	bool winning = false;
	knockOutSt knockOut;
	knockOut.setup();

	int currentStatus = 1; // 1 For Level , 2 just For KnockOut , 3 After Fade And Go To Screen Results

	RectangleShape rectangleFade(Vector2f(windowSizeX, windowSizeY));
	Clock fadeToBlackClock;
	bool afterKnockOut = false;
	bool fadeCompleted = false;

	winningScreenSt winningScreen;
	winningScreen.livesBefore = player.hp.lives;
	winningScreen.setup();

	Clock winningClock;
	winningClock.restart();
	bool setFinishingTime_livesAfter = false;

	// Sound For Music Of The Game
	music.setBuffer(musicBuffer_Level1);
	music.play();
	music.setLoop(true);

	Sound bossDefeatSound;
	bossDefeatSound.setBuffer(bossDefeatBuffer);
	bossDefeatSound.setVolume(60);
	bool bossDefeatSoundPlayed = false;

	// Death Menu
	deathMenuSt deathMenu;
	deathMenu.setup();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (player.ghost.deathClock.getElapsedTime().asMilliseconds() > 3000 && player.ghost.isDead)
			{
				deathMenu.update(event);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.moveLeft();
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.moveRight();
		if (Keyboard::isKeyPressed(Keyboard::Space))
			player.jumb();

		if (Mouse::isButtonPressed(Mouse::Left) && !player.ghost.isDead)
		{
			if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)) && Keyboard::isKeyPressed(Keyboard::W) && player.onGround)
				player.shootRunDiagonalUp(shootClock);
			else if (Keyboard::isKeyPressed(Keyboard::W) && player.onGround)
				player.shootUp(shootClock);
			else if (player.moveX != 0)
				player.shootRunStraight(shootClock);
			else
				player.shootStraight(shootClock);
		}
		if (deathMenu.deathMenuDone)
			break;

		// Updates
		// Go To KnockOut
		if (winning && knockOut.knockOutFrame < 27)
			currentStatus = 2;
		// After KnockOut , Go To Fade
		if (knockOut.knockOutFrame >= 27 && currentStatus == 2)
			currentStatus = 1;
		if (fadeCompleted && currentStatus == 1 && fadeToBlackClock.getElapsedTime().asSeconds() >= 3.5)
		{
			fadeCompleted = false;
			// Reset The Rectangle For The Next Fade , after winning Screen Ends
			rectangleFade.setFillColor(Color::Transparent);
			currentStatus = 3;
		}

		if (fadeCompleted && currentStatus == 3)
		{
			music.stop();
			PageNumber = 0;
			break;
		}

		if (level1.dead && level1.currentPhase == 2)
		{
			music.stop();
			winning = true;
		}

		if (currentStatus == 1)
		{
			player.update(level1.currentPhase);
			background.update();
			level1.update(player.bullets, player, startLevelClock, startingTime, winning);

			if (startLevelClock.getElapsedTime().asMilliseconds() < startingTime)
				readyWallopText.update(startingTime);

			if (afterKnockOut)
			{
				if (!bossDefeatSoundPlayed)
				{
					bossDefeatSoundPlayed = true;
					bossDefeatSound.play();
				}
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			}
		}
		// KnockOut
		if (currentStatus == 2)
		{
			music.stop();
			knockOut.update();
			afterKnockOut = true;
			fadeToBlackClock.restart();
		}

		// Go To Screen Results
		if (currentStatus == 3)
		{
			if (!setFinishingTime_livesAfter)
			{
				winningScreen.finishingTime = winningClock.getElapsedTime().asSeconds(); // As Seconds
				winningScreen.livesAfter = player.hp.lives;
				setFinishingTime_livesAfter = true;
			}
			winningScreen.update();
			if (winningScreen.isLevelDone)
			{
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			}
			else
				fadeToBlackClock.restart();
		}
		else
			winningScreen.startEveryAnimation.restart(); // To Wait 0.8 Sec To Start The First Animation

		window.clear();

		if (currentStatus <= 2)
		{
			background.draw1();

			if (level1.currentPhase == 1)
			{
				background.draw2();
				level1.draw();
				player.draw();
			}
			else if (level1.currentPhase == 2)
			{
				level1.draw();
				background.draw2();
				player.draw();
			}
			background.draw3();

			if (startLevelClock.getElapsedTime().asMilliseconds() < startingTime)
				readyWallopText.draw();

			// Draw The Bullets After The boss , for the Animation OF The Bullet Death
			for (int i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].bulletSprite);
				if (player.bullets[i].isSpawning)
					window.draw(player.bullets[i].spawnSprite);
			}

			for (int i = 0; i < level1.rings.size(); i++)
				window.draw(level1.rings[i].ring);
			for (int i = 0; i < level1.carrotBullets.size(); i++)
				window.draw(level1.carrotBullets[i]);

			if (player.ghost.isDead)
				window.draw(shadowBackground);

			if (winning && knockOut.knockOutFrame < 27)
				knockOut.draw();

			// After Comming From KnockOut, But In Status 1
			if (afterKnockOut && currentStatus == 1)
				window.draw(rectangleFade);
		}

		if (currentStatus == 3)
		{
			winningScreen.draw();
			if (winningScreen.isLevelDone)
				window.draw(rectangleFade);
		}

		// Death Menu
		if (player.ghost.deathClock.getElapsedTime().asMilliseconds() > 3000 && player.ghost.isDead)
		{
			deathMenu.draw();
		}
		window.display();
	}
}

// Level 2 Functions
void Level2_Page()
{
	int currentPhase = 1;
	Clock startLevelClock;
	startLevelClock.restart();
	int startingTime = 2500;

	// Background
	BackgroundSt_Level2 background;
	background.setup();
	// Set The Shadow Background
	Sprite shadowBackgroundSprite;
	shadowBackgroundSetup(shadowBackgroundSprite, background.currentTexture);

	// Ready & Wallop
	readyWallopSt readyWallopText;
	readyWallopText.setup();

	// Player
	PlayerSt_Level2 player;
	player.setup();
	Clock shootClock;

	// Tower
	TowerSt_Level2 tower;
	tower.setup();

	// Clouds
	cloud_st_foreground_Level2 cloud_foreground;
	cloud_st_background_Level2 cloud_background;
	MidCloudsSt_Level2 midClouds;
	midClouds.setFirstElements();
	// Set The Player On The First Cloud
	player.playerSprite.setPosition(midClouds.clouds[2].cloudSprite.getPosition().x + 40,
		midClouds.clouds[2].cloudSprite.getPosition().y - 150);

	DragonSt_Level2 dragon;
	dragon.dragonPhaseOne.eyesAttack.setup();

	// All Levels
	bool winning = false;
	knockOutSt knockOut;
	knockOut.setup();

	int currentStatus = 1; // 1 For Level , 2 just For KnockOut , 3 After Fade And Go To Screen Results

	RectangleShape rectangleFade(Vector2f(windowSizeX, windowSizeY));
	Clock fadeToBlackClock;
	bool afterKnockOut = false;
	bool fadeCompleted = false;

	winningScreenSt winningScreen;
	winningScreen.livesBefore = player.hp.lives;
	winningScreen.setup();

	Clock winningClock;
	winningClock.restart();
	bool setFinishingTime_livesAfter = false;

	// Sound For Music Of The Game
	Sound bossDefeatSound;
	music.setBuffer(levelTwoBuffer_Level2);
	music.play();
	music.setLoop(1);

	bossDefeatSound.setBuffer(bossDefeatBuffer);
	bossDefeatSound.setVolume(60);
	bool bossDefeatSoundPlayed = false;

	// Death Menu
	deathMenuSt deathMenu;
	deathMenu.setup();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (player.ghost.deathClock.getElapsedTime().asMilliseconds() > 3000 && player.ghost.isDead)
			{
				deathMenu.update(event);
			}
		}
		// Player Movment
		if (startLevelClock.getElapsedTime().asMilliseconds() >= startingTime)
		{
			if (Keyboard::isKeyPressed(Keyboard::A))
				player.moveLeft();
			if (Keyboard::isKeyPressed(Keyboard::D))
				player.moveRight();
			if (Keyboard::isKeyPressed(Keyboard::Space))
				player.jumb();

			if (Mouse::isButtonPressed(Mouse::Left) && !player.ghost.isDead)
			{
				if ((Keyboard::isKeyPressed(Keyboard::S)) && player.onGround)
					player.shootCrawling(shootClock);
				else if ((Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D)) && Keyboard::isKeyPressed(Keyboard::W) && player.onGround)
					player.shootRunDiagonalUp(shootClock);
				else if (Keyboard::isKeyPressed(Keyboard::W) && player.onGround)
					player.shootUp(shootClock);
				else if (player.moveX != player.standingSpeed) // The Player is Moving , Not The Cloud Moving him
					player.shootRunStraight(shootClock);
				else
					player.shootStraight(shootClock);
			}
		}
		if (deathMenu.deathMenuDone)
			break;
		// Updates
		// Go To KnockOut
		if (winning && knockOut.knockOutFrame < 27)
			currentStatus = 2;
		// After KnockOut , Go To Fade
		if (knockOut.knockOutFrame >= 27 && currentStatus == 2)
			currentStatus = 1;
		if (fadeCompleted && currentStatus == 1 && fadeToBlackClock.getElapsedTime().asSeconds() >= 3.5)
		{
			fadeCompleted = false;
			// Reset The Rectangle For The Next Fade , after winning Screen Ends
			rectangleFade.setFillColor(Color::Transparent);
			currentStatus = 3;
		}

		if (fadeCompleted && currentStatus == 3)
		{
			music.stop();
			PageNumber = 0;
			break;
		}

		// Level
		if (currentStatus == 1)
		{
			player.update(currentPhase, winning);
			background.update();

			if (startLevelClock.getElapsedTime().asMilliseconds() < startingTime)
				readyWallopText.update(startingTime);

			tower.update();

			// Clouds
			cloud_foreground.update();
			cloud_background.update();
			midClouds.update(player, startLevelClock, startingTime);

			// Dragon
			dragon.update(currentPhase, startLevelClock, player, winning);

			if (afterKnockOut)
			{
				if (!bossDefeatSoundPlayed)
				{
					bossDefeatSoundPlayed = true;
					bossDefeatSound.play();
				}
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			}
		}

		// KnockOut
		if (currentStatus == 2)
		{
			music.stop();
			knockOut.update();
			afterKnockOut = true;
			fadeToBlackClock.restart();
		}

		// Go To Screen Results
		if (currentStatus == 3)
		{
			if (!setFinishingTime_livesAfter)
			{
				winningScreen.finishingTime = winningClock.getElapsedTime().asSeconds(); // As Seconds
				winningScreen.livesAfter = player.hp.lives;
				setFinishingTime_livesAfter = true;
			}
			winningScreen.update();
			if (winningScreen.isLevelDone)
			{
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			}
			else
				fadeToBlackClock.restart();
		}
		else
			winningScreen.startEveryAnimation.restart(); // To Wait 0.8 Sec To Start The First Animation

		// Reset It Here, Because When Checking Collision With FireBalls And Stuff , need to Check If He Is Crawling First
		player.isCrawling = false;

		// Drawing
		window.clear();
		if (currentStatus <= 2)
		{
			background.draw();

			if (player.ghost.isDead)
			{
				window.draw(shadowBackgroundSprite);
			}

			cloud_background.draw();
			tower.draw();
			cloud_foreground.draw();
			midClouds.draw();
			player.draw();

			dragon.draw(currentPhase);
			// Draw The Bullets After The Dragon , BC Animation OF The Bullet Death
			for (int i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].bulletSprite);
				if (player.bullets[i].isSpawning)
					window.draw(player.bullets[i].spawnSprite);
			}

			// Last Thing To Cover All The Above
			if (startLevelClock.getElapsedTime().asMilliseconds() < startingTime)
				readyWallopText.draw();

			if (winning && knockOut.knockOutFrame < 27)
				knockOut.draw();

			// After Comming From KnockOut, But In Status 1
			if (afterKnockOut && currentStatus == 1)
				window.draw(rectangleFade);
		}
		if (currentStatus == 3)
		{
			winningScreen.draw();
			if (winningScreen.isLevelDone)
				window.draw(rectangleFade);
		}

		// Death Menu
		if (player.ghost.deathClock.getElapsedTime().asMilliseconds() > 3000 && player.ghost.isDead)
		{
			deathMenu.draw();
		}

		window.display();
	}
}

// Level 3 Functions
void checkcollision(EnemySt_Level3& enemy, PlayerSt_Level3& player, YellowBirdsSt_Level3& flappyBirds) {   // Check Collision between Player & Boss and Player & Yellow Birds
	if (enemy.bossHealth <= 0)
		return;
	for (int i = 0; i < enemy.Eggs.size(); i++) {
		if (player.playerSprite.getGlobalBounds().intersects(enemy.Eggs[i].EggSprite.getGlobalBounds())) {
			enemy.Eggs[i].playerDamage = true;
			if (enemy.Eggs[i].PlayerDecreased) {
				player.hp.isHit = true;
			}
			enemy.Eggs[i].PlayerDecreased = false;
		}
	}
	for (int i = 0; i < enemy.bullets.size(); i++) {
		if (player.playerSprite.getGlobalBounds().intersects(enemy.bullets[i].bulletSprite.getGlobalBounds())) {
			enemy.bullets[i].playerDamage = true;
			if (enemy.bullets[i].playerDecreased) {
				player.hp.isHit = true;
			}
			enemy.bullets[i].playerDecreased = false;
		}
	}
	for (int i = 0; i < enemy.feathers.size(); i++) {
		if (player.playerSprite.getGlobalBounds().intersects(enemy.feathers[i].featherSprite.getGlobalBounds())
			&& player.playerSprite.getPosition().x >= enemy.feathers[i].featherSprite.getPosition().x - 125
			&& player.playerSprite.getPosition().x <= enemy.feathers[i].featherSprite.getPosition().x + 118
			&& player.playerSprite.getPosition().y <= enemy.feathers[i].featherSprite.getPosition().y + 13
			&& player.playerSprite.getPosition().y >= enemy.feathers[i].featherSprite.getPosition().y - 122) {
			enemy.feathers[i].playerDamage = true;
			if (enemy.feathers[i].playerDecreased) {
				player.hp.isHit = true;
			}
			enemy.feathers[i].playerDecreased = false;
		}
	}
	if (player.playerSprite.getGlobalBounds().intersects(enemy.EnemySprite.getGlobalBounds())) {
		enemy.playerDamage = true;
		if (enemy.playerDecreased) {
			player.hp.isHit = true;
		}
		enemy.playerDecreased = false;
	}
	for (int i = 0; i < 4; i++) {
		if (player.playerSprite.getGlobalBounds().intersects(flappyBirds.birds[i].birdSprite.getGlobalBounds())) {
			flappyBirds.birds[i].playerDamage = true;
			if (flappyBirds.birds[i].playerDecreased) {
				player.hp.isHit = true;
			}
			flappyBirds.birds[i].playerDecreased = false;
		}
	}
}
void Level3_Page(menu& menu, Event& event)
{
	// Background layers
	background_Level3 background;
	background.setup();
	backgroundTrees_Level3 treeLayer;
	treeLayer.setup();
	Sprite shadowBackgroundSprite;
	shadowBackgroundSetup(shadowBackgroundSprite, background.currentTexture);

	// Ready Wallop (Intro to the Game)
	readyWallopSt ReadyWallop;
	ReadyWallop.setup();

	// Player (Cuphead)
	PlayerSt_Level3 player;
	player.setup();
	Clock shootClock;

	// Boss (wally Warples)
	EnemySt_Level3 enemy;
	enemy.setup();

	// Yellow Birds
	YellowBirdsSt_Level3 birds;

	// Winning Screen
	bool winning = false;
	knockOutSt knockOut;
	knockOut.setup();

	int currentStatus = 1; // 1 For Level , 2 just For KnockOut , 3 After Fade And Go To Screen Results

	RectangleShape rectangleFade(Vector2f(windowSizeX, windowSizeY));
	Clock fadeToBlackClock;
	fadeToBlackClock.restart();
	bool afterKnockOut = false;
	bool fadeCompleted = false;

	winningScreenSt winningScreen;
	winningScreen.livesBefore = player.hp.lives;
	winningScreen.setup();

	Clock winningClock;
	winningClock.restart();
	bool setFinishingTime_livesAfter = false;

	// Sound For Music Of The Game
	Sound bossDefeatSound;

	bossDefeatSound.setBuffer(bossDefeatBuffer);
	bossDefeatSound.setVolume(60);
	bool bossDefeatSoundPlayed = false;

	// Death Menu
	deathMenuSt deathMenu;
	deathMenu.setup();

	// Game Loop
	while (window.isOpen()) {
		//Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (player.ghost.deathClock.getElapsedTime().asMilliseconds() > 3000 && player.ghost.isDead)
			{
				deathMenu.update(event);
			}

		}

		// Player Movement 
		if (Keyboard::isKeyPressed(Keyboard::A) && player.positionX > leftWall && !player.ghost.isDead)
		{
			player.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && player.positionX < rightWall && !player.ghost.isDead)
		{
			player.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && !player.ghost.isDead)
		{
			player.transitionUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && !player.ghost.isDead)
		{
			player.transitionDown();
		}
		if (!(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) ||
			Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Q)))
		{
			player.Stationary();
		}

		// Player Shooting
		if (Mouse::isButtonPressed(Mouse::Left) && !player.ghost.isDead)
		{
			player.shoot(shootClock);
		}
		if (deathMenu.deathMenuDone)
			break;
		// Updates
		// Go To KnockOut
		if (winning && knockOut.knockOutFrame < 27)
			currentStatus = 2;
		// After KnockOut , Go To Fade
		if (knockOut.knockOutFrame >= 27 && currentStatus == 2)
			currentStatus = 1;
		if (fadeCompleted && currentStatus == 1 && fadeToBlackClock.getElapsedTime().asSeconds() >= 3.5)
		{
			fadeCompleted = false;
			// Reset The Rectangle For The Next Fade , after winning Screen Ends
			rectangleFade.setFillColor(Color::Transparent);
			currentStatus = 3;
		}
		if (fadeCompleted && currentStatus == 3)
		{
			music.stop();
			PageNumber = 0;
			break;
		}
		if (enemy.isDead && !player.ghost.isDead)
		{
			music.stop();
			winning = true;
		}

		if (currentStatus == 1)
		{
			// Check Player Damage
			checkcollision(enemy, player, birds);

			// Update
			background.update(player);
			treeLayer.update();

			if (ReadyWallop.increasingFrame.getElapsedTime().asMilliseconds() < 2500)
			{
				ReadyWallop.update(2500);
			}

			player.update(menu, event, PageNumber);
			enemy.update(player, player.bullets);

			if (PlayTimer >= 10) {
				birds.update(player, player.bullets);
			}

			if (afterKnockOut)
			{
				music.stop();
				if (!bossDefeatSoundPlayed)
				{
					bossDefeatSoundPlayed = true;
					bossDefeatSound.play();
				}
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			}
		}
		// KnockOut
		if (currentStatus == 2)
		{
			knockOut.update();
			afterKnockOut = true;
			fadeToBlackClock.restart();
		}
		// Go To Screen Results
		if (currentStatus == 3)
		{
			if (!setFinishingTime_livesAfter)
			{
				winningScreen.finishingTime = winningClock.getElapsedTime().asSeconds(); // As Seconds
				winningScreen.livesAfter = player.hp.lives;
				setFinishingTime_livesAfter = true;
			}
			winningScreen.update();
			if (winningScreen.isLevelDone)
			{
				fadeCompleted = fadeToBlack(rectangleFade, fadeToBlackClock);
			}
			else
				fadeToBlackClock.restart();
		}
		else
			winningScreen.startEveryAnimation.restart(); // To Wait 0.8 Sec To Start The First Animation

		// Clear
		window.clear();
		if (currentStatus <= 2)
		{
			// Draw
			background.draw();

			for (int i = 0; i < player.bullets.size(); i++)  // Player's Bullets
			{
				window.draw(player.bullets[i].bulletSprite);
				if (player.bullets[i].isSpawning)
					window.draw(player.bullets[i].spawnSprite);
			}

			player.draw(menu, window, PageNumber);			// Player
			enemy.draw();									// Boss

			if (PlayTimer >= 10) {							// Yellow Birds
				birds.draw();
			}
			if (ReadyWallop.increasingFrame.getElapsedTime().asMilliseconds() < 2500)
				ReadyWallop.draw();

			treeLayer.draw();
			if (player.ghost.isDead) {
				window.draw(shadowBackgroundSprite);
			}

			if (winning && knockOut.knockOutFrame < 27)
				knockOut.draw();

			// After Comming From KnockOut, But In Status 1
			if (afterKnockOut && currentStatus == 1)
				window.draw(rectangleFade);
		}

		if (currentStatus == 3)
		{
			winningScreen.draw();
			if (winningScreen.isLevelDone)
				window.draw(rectangleFade);
		}

		// Death Menu
		if (player.ghost.deathClock.getElapsedTime().asMilliseconds() > 3000 && player.ghost.isDead)
		{
			deathMenu.draw();
		}

		// Display
		window.display();
	}
}