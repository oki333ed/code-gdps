#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;
 // Кастом лого
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        CCSprite* mainTitle = static_cast<CCSprite*>(this->getChildByID("main-title")); // Ой

        if (mainTitle) {
            CCSprite* doorSprite = CCSprite::create("codeGDPS-Logo.png"_spr); // _spr
            mainTitle->setDisplayFrame(doorSprite->displayFrame());
        }

        return true;
    }
};
// Подвал для icon-kit-button
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        CCMenu* mainMenu = static_cast<CCMenu*>(this->getChildByID("main-menu"));

        if (mainMenu) {
            CCMenuItemSpriteExtra* iconKitBtn = static_cast<CCMenuItemSpriteExtra*>(mainMenu->getChildByID("icon-kit-button"));

            if (iconKitBtn) {
                CCSprite* doorSprite = CCSprite::createWithSpriteFrameName("secretDoorBtn_open_001.png"); // Не _spr хы
                iconKitBtn->setNormalImage(doorSprite);
            }
        }

        return true;
    }
};
// Подвал для play-button
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        CCMenu* mainMenu = static_cast<CCMenu*>(this->getChildByID("main-menu"));

        if (mainMenu) {
            CCMenuItemSpriteExtra* playBtn = static_cast<CCMenuItemSpriteExtra*>(mainMenu->getChildByID("play-button"));

            if (playBtn) {
                CCSprite* doorSprite = CCSprite::createWithSpriteFrameName("secretDoorBtn2_open_001.png"); // Большая
                playBtn->setNormalImage(doorSprite);
            }
        }

        return true;
    }
};
// Хы Goodbye Unnecessary Buttons
class $modify(CreatorLayer) {
	static void onModify(auto& self) {
		if (self.setHookPriorityAfterPost("CreatorLayer::init", "minemaker0430.gddp_integration")) {}
	}
	bool init() {
		if(!CreatorLayer::init())
			return false;
		CCMenu* m_creatorButtonsMenu = as<CCMenu*>(this->getChildByID("creator-buttons-menu"));
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("versus-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("map-button"))->setVisible(false);
        as<CCNode*>(m_creatorButtonsMenu->getChildByID("gauntlets-button"))->setVisible(false);

		auto gddpBtn = as<CCMenuItemSpriteExtra*>(m_creatorButtonsMenu->getChildByID("demon-progression-button"));

		bool gddpThere = Loader::get()->isModLoaded("minemaker0430.gddp_integration") && gddpBtn;

		if (gddpThere) {
			gddpBtn->setZOrder(11);
		}

		for(int i = 0; i < m_creatorButtonsMenu->getChildrenCount(); i++) {
			auto node = as<CCMenuItemSpriteExtra*>(m_creatorButtonsMenu->getChildren()->objectAtIndex(i));
			auto sprite = node->getNormalImage();
			auto nodeID = node->getID();
			
			sprite->setScale(0.85);

			if (nodeID == "map-button")
				node->setZOrder(0);
			else if (nodeID == "create-button")
				node->setZOrder(1);
			else if (nodeID == "saved-button")
				node->setZOrder(2);
			else if (nodeID == "scores-button")
				node->setZOrder(3);
			else if (nodeID == "quests-button")
				node->setZOrder(4);
			else if (nodeID == "paths-button")
				node->setZOrder(5);
			else if (nodeID == "lists-button")
				node->setZOrder(6);
			else if (nodeID == "daily-button")
				node->setZOrder(7);
			else if (nodeID == "weekly-button")
				node->setZOrder(8);
            else if (nodeID == "event-button")
				node->setZOrder(9);
			else if (nodeID == "map-packs-button")
				node->setZOrder(10 + gddpThere);
			else if (nodeID == "featured-button")
				node->setZOrder(11 + gddpThere);
			else if (nodeID == "search-button")
				node->setZOrder(12 + gddpThere);
		}

		AxisLayout* menuLayout = as<AxisLayout*>(m_creatorButtonsMenu->getLayout());
		menuLayout->setGap(8);
		menuLayout->ignoreInvisibleChildren(true);
		menuLayout->setAutoScale(false);
		menuLayout->setCrossAxisReverse(false);
		m_creatorButtonsMenu->updateLayout();
		return true;
	}
};

// Подвал для editor-button
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        CCMenu* mainMenu = static_cast<CCMenu*>(this->getChildByID("main-menu"));

        if (mainMenu) {
            CCMenuItemSpriteExtra* editorBtn = static_cast<CCMenuItemSpriteExtra*>(mainMenu->getChildByID("editor-button"));

            if (editorBtn) {
                CCSprite* doorSprite = CCSprite::createWithSpriteFrameName("secretDoorBtn_open_001.png"); // Не _spr хы
                editorBtn->setNormalImage(doorSprite);
            }
        }

        return true;
    }
};
// Хы Window Resize
#ifdef _WIN32
$execute {
	const auto unwrapOrWarn = [](const auto& result) -> Patch* {
		if (result.isErr()) {
			log::warn("Unable to place a patch! {}", result.unwrapErr());
			return nullptr;
		} else {
			return result.unwrap();
		}
	};

	static_assert(GEODE_COMP_GD_VERSION == 22074, "max-window addresses are outdated!");

	auto patch1 = unwrapOrWarn(Mod::get()->patch((void*)(base::getCocos() + 0xd6eca), {0x90, 0x90, 0x90, 0x90, 0x90}));

	(void) Mod::get()->patch((void*)(base::getCocos() + 0xd5089), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});

	(void) Mod::get()->patch((void*)(base::getCocos() + 0xd6567), {0x48, 0xe9});

	if (patch1) {
		(void) patch1->enable();
	}
}
#endif
// Icon Hack
class $modify(IconHack, GameManager) {
    bool isIconUnlocked(int id, IconType type) { return true; } // Иконки
    bool isColorUnlocked(int id, UnlockType type) { return true; } // Цвета
};