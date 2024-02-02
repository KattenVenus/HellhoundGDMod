/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/binding/LevelTools.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's 
 * classes; to hook a function in Geode, 
 * simply $modify the class and write a new 
 * function definition with the signature of 
 * the one you want to hook.
 */

class $modify(LevelInfoLayer) {
	/**
	 * MenuLayer::onMoreGames is a GD function, 
	 * so we hook it by simply writing its name 
	 * inside a $modified MenuLayer class.
	 * 
	 * Note that for all hooks, your signature 
	 * has to match exactly - `bool onMoreGames` 
	 * would not place a hook!
	 */
	


	void updateFace() {

		if (!m_starsIcon)
			return;

		int moveAmount = 20;

		if (m_level->m_stars == 10) {
			moveAmount = 10;
		}

		auto demonFace = CCSprite::create("demonface2222.png"_spr);
		demonFace->setScale(0.3);
		demonFace->setPositionX(m_difficultySprite->getPositionX());
		demonFace->setPositionY(m_difficultySprite->getPositionY()-9);
		demonFace->setZOrder(m_difficultySprite->getZOrder()-1);
		demonFace->setID("demonFace");

		auto demonLabel = CCLabelBMFont::create("No dont eat me! - ", "bigFont.fnt");
		demonLabel->setScale(0.3);
		demonLabel->setPositionX(m_difficultySprite->getPositionX()-70);
		demonLabel->setPositionY(m_difficultySprite->getPositionY());
		this->addChild(demonLabel);

		if (m_starsIcon) {
			m_starsIcon->cleanup();
			m_starsIcon->setPositionX(m_starsIcon->getPositionX()+12);
			m_starsIcon->setPositionY(m_starsIcon->getPositionY()-moveAmount);
			m_starsIcon->setID("shinyIcon");
		}

		if (m_starsLabel) {
			m_starsLabel->cleanup();
			m_starsLabel->setPositionX(m_starsLabel->getPositionX()+12);
			m_starsLabel->setPositionY(m_starsLabel->getPositionY()-moveAmount);
			m_starsLabel->setID("shiny");
			m_starsLabel->setString("6742");
			this->addChild(m_starsLabel);
		}

		if (m_orbsLabel) {
			auto orbsChildren = m_orbsLabel->getChildren();
			int c = 0;
			CCObject* obj;
			CCARRAY_FOREACH(orbsChildren, obj) {
				if (CCSprite* tempObj = static_cast<CCSprite*>(obj)) {
					
					if (c <= orbsChildren->count()-4) {
						c++;
						continue;
					}

					if (c == orbsChildren->count()-3) {
						auto orbCount = CCSprite::create("orbs.png"_spr);
						orbCount->setScale(m_orbsLabel->getScale()-0.05f);
						orbCount->setPositionX(m_orbsLabel->getPositionX()+(tempObj->getPositionX()*m_orbsLabel->getScale())-3);
						orbCount->setPositionY(m_orbsLabel->getPositionY()-1);
						orbCount->setAnchorPoint(CCPointMake(0,0.5f));

						orbCount->setID("orbCount");

						this->addChild(orbCount);

					}

					tempObj->setVisible(false);
					c++;
				}
			}
		}

		if (m_coins) {
			CCObject* obj;
			CCARRAY_FOREACH(m_coins, obj) {
				if (CCSprite* tempObj = static_cast<CCSprite*>(obj)) {
					tempObj->removeFromParentAndCleanup(true);
					tempObj->setPositionX(tempObj->getPositionX());
					tempObj->setPositionY(tempObj->getPositionY()-moveAmount);
					tempObj->setID("coins");
					this->addChild(tempObj);
				}
			}
		}

		this->addChild(demonFace);

		int c = 0;

		CCObject* obj;
		CCARRAY_FOREACH(m_difficultySprite->getChildren(), obj) {
			if (CCSprite* tempObj = static_cast<CCSprite*>(obj)) {

				c++;
				tempObj->removeFromParentAndCleanup(true);
				tempObj->setPosition(m_difficultySprite->getPosition());
				tempObj->setID("featuredShine" + std::to_string(c));
				this->addChild(tempObj);

			}
		}

		m_difficultySprite->setScale(0.15);

	}

	void updateLabelValues() {

		LevelInfoLayer::updateLabelValues();

		if (m_level->m_stars != 10) {
			return;
		}

		if (!((m_level->m_levelID.value() % 10 == 2) || (m_level->m_levelID.value() % 10 == 7))){
			return;
		}

		

			updateFace();


	}

};
