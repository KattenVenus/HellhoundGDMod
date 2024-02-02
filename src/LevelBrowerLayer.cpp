/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
/**
 * Required to modify the MenuLayer class
 */
#include <Geode/modify/LevelCell.hpp>
#include <Geode/binding/CCContentLayer.hpp>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
using namespace geode::prelude;


class $modify(LevelCell){

    void loadCustomLevelCell() {

        LevelCell::loadCustomLevelCell();

        if (m_level->m_stars != 10) {
			return;
		}


        if (!((m_level->m_levelID.value() % 10 == 2) || (m_level->m_levelID.value() % 10 == 7))){
			return;
		}

        if (CCLabelBMFont* tempObj = static_cast<CCLabelBMFont*>(m_mainLayer->getChildByID("orbs-label"))) {

            auto labelArray = tempObj->getChildren();

            int c = 0;

            CCObject* obj;
            CCARRAY_FOREACH(labelArray, obj) {
                if (CCSprite* label = static_cast<CCSprite*>(obj)) {
                    if (c <= labelArray->count()-4) {
						c++;
						continue;
					}

					if (c == labelArray->count()-3) {

                        auto orbCount = CCSprite::create("orbs.png"_spr);
						orbCount->setScale(tempObj->getScale()-0.05f);
						orbCount->setPositionX(tempObj->getPositionX()+(label->getPositionX()*tempObj->getScale())-3);
						orbCount->setPositionY(tempObj->getPositionY()-1);
						orbCount->setAnchorPoint(CCPointMake(0,0.5f));

						orbCount->setID("orbCount");

						this->addChild(orbCount);

					}

					label->setOpacity(false);
					c++;
                }
            }

        }

        if (CCNode* tempObj = static_cast<CCNode*>(m_mainLayer->getChildByID("difficulty-container"))) {

            auto demonFace = CCSprite::create("demonfaceBrowser.png"_spr);
            demonFace->setID("demonFace");
		    demonFace->setScale(0.3);
            tempObj->addChild(demonFace);

            if (CCSprite* sprite = static_cast<CCSprite*>(tempObj->getChildByID("stars-icon"))) {
                sprite->setPositionX(sprite->getPositionX()+12);
            }

            if (CCLabelBMFont* label = static_cast<CCLabelBMFont*>(tempObj->getChildByID("stars-label"))) {
                label->setPositionX(label->getPositionX()+12);
                label->setString("6742");
            }


            if (GJDifficultySprite* difSprite = static_cast<GJDifficultySprite*>(tempObj->getChildByID("difficulty-sprite"))) {

		        demonFace->setPositionX(difSprite->getPositionX());
                demonFace->setPositionY(difSprite->getPositionY());
                demonFace->setZOrder(difSprite->getZOrder()-1);

                if (CCSprite* sprite = static_cast<CCSprite*>(difSprite->getChildren()->objectAtIndex(0))) {
                    sprite->removeAllChildrenWithCleanup(true);
                    
                    sprite->setPositionX(94);
                    sprite->setPositionY(68);
                    sprite->setScale(3.3);
                    demonFace->addChild(sprite);
                }

                difSprite->setVisible(false);
            }

        }

	}

};
