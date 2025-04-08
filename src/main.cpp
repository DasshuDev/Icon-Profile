#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/utils/cocos.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

int getFrameIcon(IconType type) {
    auto gManager = GameManager::sharedState();
    switch(type) {
        default: return gManager->getPlayerFrame();
        case IconType::Ship: return gManager->getPlayerShip();
        case IconType::Ball: return gManager->getPlayerBall();
        case IconType::Ufo: return gManager->getPlayerBird();
        case IconType::Wave: return gManager->getPlayerDart();
        case IconType::Robot: return gManager->getPlayerRobot();
        case IconType::Spider: return gManager->getPlayerSpider();
		case IconType::Swing: return gManager->getPlayerSwing(); 
		case IconType::Jetpack: return gManager->getPlayerJetpack();
    }
}

class $modify(MenuLayer) {
	bool init() {
		if(!MenuLayer::init())
			return false;
		
		auto manager = GameManager::sharedState();

		auto profileMenu = this->getChildByID("profile-menu");

		SimplePlayer* playerIcon = SimplePlayer::create(0);
		playerIcon->updatePlayerFrame(getFrameIcon(manager->m_playerIconType), manager->m_playerIconType);
		playerIcon->setColor(manager->colorForIdx(manager->getPlayerColor()));
		playerIcon->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
		playerIcon->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
		playerIcon->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
		if(!manager->getPlayerGlow()) playerIcon->disableGlowOutline();

		playerIcon->setScale(1.15);

		if(Mod::get()->getSettingValue<bool>("animations")) {
			if(manager->m_playerIconType == IconType::Robot) playerIcon->m_robotSprite->runAnimation("idle01");
			if(manager->m_playerIconType == IconType::Spider) playerIcon->m_spiderSprite->runAnimation("idle01");
		}

		auto profileBtn = as<CCMenuItemSpriteExtra*>(profileMenu->getChildByID("profile-button"));
		auto profileSpr = static_cast<CCSprite*>(profileBtn->getChildren()->objectAtIndex(0));
		profileSpr->setID("profile-icon");

		profileSpr->setDisplayFrame(playerIcon->displayFrame());
		profileSpr->addChild(playerIcon);
		profileBtn->setPositionX(30);

		return true;
	}
};