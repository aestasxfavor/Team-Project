#include "TitleScene.h"
#include "SceneManager.h"

// 2025-07-23 효 추가: 타이틀 씬 구현 (스프라이트 못구함 ㅠ)
void TitleScene::Init()
{
	// 배경 이미지
	backgroundTexture.loadFromFile(GetrscPath("background.png"));

	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);		// 시작시 타이틀 위치 설정

#pragma region 타이틀, 시작, 종료 버튼 스프라이트 버전
	//// 타이틀 이미지
	//titleTexture.loadFromFile("res/title_logo.png");
	//title.setTexture(titleTexture);

	//sf::FloatRect titleBounds = title.getLocalBounds();
	//title.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
	//title.setPosition(400, 120);

	//// 시작 버튼 이미지
	//startBtnTexture.loadFromFile("res/start_button.png");
	//startButton.setTexture(startBtnTexture);

	//sf::FloatRect startBounds = startButton.getLocalBounds();
	//startButton.setOrigin(startBounds.width / 2.f, startBounds.height / 2.f);
	//startButton.setPosition(400, 280);

	//// 종료 버튼 이미지
	//exitBtnTexture.loadFromFile("res/exit_button.png");
	//exitButton.setTexture(exitBtnTexture);

	//sf::FloatRect exitBounds = exitButton.getLocalBounds();
	//exitButton.setOrigin(exitBounds.width / 2.f, exitBounds.height / 2.f);
	//exitButton.setPosition(400, 360);
#pragma endregion

#pragma region 타이틀, 시작, 종료 버튼 텍스트 버전
	//// 타이틀 텍스트
	//// 폰트 로드
	//font.loadFromFile(GetrscPath("font.ttf"));
	//
	//// 타이틀 텍스트
	//titleText.setFont(font);
	//titleText.setString("My Game Title");
	//titleText.setCharacterSize(48);
	//titleText.setFillColor(sf::Color::White);
	//titleText.setStyle(sf::Text::Bold);
	//sf::FloatRect titleBounds = titleText.getLocalBounds();
	//titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
	//titleText.setPosition(400, 120);
	//
	//// 시작 버튼 텍스트
	//startText.setFont(font);
	//startText.setString("Start Game");
	//startText.setCharacterSize(36);
	//startText.setFillColor(sf::Color::White);
	//startText.setStyle(sf::Text::Bold);
	//sf::FloatRect startBounds = startText.getLocalBounds();
	//startText.setOrigin(startBounds.width / 2.f, startBounds.height / 2.f);
	//startText.setPosition(400, 280);
	//
	//// 종료 버튼 텍스트
	//exitText.setFont(font);
	//exitText.setString("Exit Game");
	//exitText.setCharacterSize(36);
	//exitText.setFillColor(sf::Color::White);
	//exitText.setStyle(sf::Text::Bold);
	//sf::FloatRect exitBounds = exitText.getLocalBounds();
	//exitText.setOrigin(exitBounds.width / 2.f, exitBounds.height / 2.f);
	//exitText.setPosition(400, 360);
#pragma endregion	2025-07-23 효 추가 : 텍스트로 실험하려 했으나 스테이지도 상속을 받아야해서 설계만 함

}

void TitleScene::Update(sf::RenderWindow& window)
{
	// 여기서 클릭 처리 넣어도 되고, 씬 전환도 구현 가능
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

		if (startText.getGlobalBounds().contains(mousePos))
		{
			SceneManager::ChangeScene("GameScene"); // 등록한 씬 이름 기준
		}
		else if (exitText.getGlobalBounds().contains(mousePos))
		{
			window.close();
		}
	}
}

void TitleScene::Render(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(titleText);
	window.draw(startText);
	window.draw(exitText);
}
