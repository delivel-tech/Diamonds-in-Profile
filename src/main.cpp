#include <Geode/Geode.hpp>
#include <Geode/binding/GameToolbox.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(DiamondsProfilePage, ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) return false;

        return true;
    }

void loadPageFromUserInfo(GJUserScore* score) {
    ProfilePage::loadPageFromUserInfo(score);

    auto statsMenu = m_mainLayer->getChildByID("stats-menu");
    if (!statsMenu) return;

    auto ifDiamonds = statsMenu->getChildByID("diamonds-entry");

    if (ifDiamonds) {
        ifDiamonds->removeFromParent();
    }

    auto moonsIcon = statsMenu->getChildByIDRecursive("moons-icon");
    if (!moonsIcon) return;

    auto starsIcon = statsMenu->getChildByIDRecursive("stars-icon");
    if (!starsIcon) return;

    auto text = GameToolbox::pointsToString(score->m_diamonds);
    auto label = geode::Label::create(text, "bigFont.fnt");
    label->setScale(0.6f);

    const float maxLabelW = 58.f;
    label->setLimitLabelWidth(maxLabelW, 0.6f, 0.2f);

    auto icon = CCSprite::createWithSpriteFrameName("GJ_diamondsIcon_001.png");

    auto ls = label->getScaledContentSize();
    auto is = icon->getScaledContentSize();

    float gap = 2.f;
    float pad = 2.f;
    float h = std::max(ls.height, is.height);
    float w = pad + ls.width + gap + is.width + pad;

    auto entry = CCNode::create();
    entry->setID("diamonds-entry");
    entry->setContentSize({w, h});

    label->setAnchorPoint({0.f, 0.5f});
    label->setPosition({pad, h / 2.f});

    icon->setAnchorPoint({0.f, 0.5f});
    icon->setPosition({pad + ls.width + gap, h / 2.f});

    entry->addChild(label);
    entry->addChild(icon);

    if (Mod::get()->getSettingValue<bool>("after-stars")) {
        statsMenu->insertAfter(entry, starsIcon);
    } else {
        statsMenu->insertAfter(entry, moonsIcon);
    }
    statsMenu->updateLayout();
}
};