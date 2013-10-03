#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "cocos-ext.h"

#include "JsonValue.h"

USING_NS_CC;
using namespace extension;


#define DEFAULT_NORMAL_SYMBOL_RATE1 6
#define DEFAULT_NORMAL_SYMBOL_RATE2 6
#define DEFAULT_NORMAL_SYMBOL_RATE3 6
#define DEFAULT_NORMAL_SYMBOL_RATE4 11
#define DEFAULT_NORMAL_SYMBOL_RATE5 12
#define DEFAULT_NORMAL_SYMBOL_RATE6 12
#define DEFAULT_NORMAL_SYMBOL_RATE7 13
#define DEFAULT_NORMAL_SYMBOL_RATE8 16

#define DEFAULT_SCATTER_SYMBOL_RATE 4
#define DEFAULT_BONUS_SYMBOL_RATE   3
#define DEFAULT_JACKPOT_SYMBOL_RATE 1
#define DEFAULT_MYSTERY_SYMBOL_RATE 1
#define DEFAULT_WILD_SYMBOL_RATE    3


//If this sum changes, need to change server sum
int symbolRates[13] =
{
    DEFAULT_NORMAL_SYMBOL_RATE1, //NORMAL_SYMBOL_RATE1
    DEFAULT_NORMAL_SYMBOL_RATE2, //NORMAL_SYMBOL_RATE2
    DEFAULT_NORMAL_SYMBOL_RATE3, //NORMAL_SYMBOL_RATE3
    DEFAULT_NORMAL_SYMBOL_RATE4, //NORMAL_SYMBOL_RATE4
    DEFAULT_NORMAL_SYMBOL_RATE5, //NORMAL_SYMBOL_RATE5
    DEFAULT_NORMAL_SYMBOL_RATE6, //NORMAL_SYMBOL_RATE6
    DEFAULT_NORMAL_SYMBOL_RATE7, //NORMAL_SYMBOL_RATE7
    DEFAULT_NORMAL_SYMBOL_RATE8, //NORMAL_SYMBOL_RATE8
    
    DEFAULT_SCATTER_SYMBOL_RATE, //SCATTER_SYMBOL_RATE
    DEFAULT_BONUS_SYMBOL_RATE, //BONUS_SYMBOL_RATE
    DEFAULT_JACKPOT_SYMBOL_RATE, //JACKPOT_SYMBOL_RATE
    DEFAULT_MYSTERY_SYMBOL_RATE, //MYSTERY_SYMBOL_RATE
    DEFAULT_WILD_SYMBOL_RATE, //WILD_SYMBOL_RATE
};



CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));


    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

        
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);


    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
    
    
    /** TESTING THINGS **/

    const char *url = "http://google.es";
    const char *parameters = "";
    const char *tag = "";
    
    CCLog("URL - %s", url);
    CCLog("PARAMETERS - %s", parameters);
    CCLog("TAG - %s", tag);

    
    CCHttpRequest *request = new CCHttpRequest();
    request->setUrl(url);
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this,
                                 httpresponse_selector(HelloWorld::onRequestCompleted));
    request->setRequestData(parameters, strlen(parameters));
    request->setTag(tag);


    CCHttpClient::getInstance()->setTimeoutForConnect(3);
    CCHttpClient::getInstance()->send(request);

    request->release();
    
    CCLog("END");
    
    /********************/

    
    
    return true;
}


void HelloWorld::onRequestCompleted(CCNode *sender, void *data)
{
    CCLog("AppDelegate::onHttpRequestCompleted - onHttpRequestCompleted BEGIN");
    
    CCHttpResponse *response = (CCHttpResponse*)data;

    if (!response)
    {
        CCLog("onHttpRequestCompleted - No Response");
        return;
    }
    
    CCLog("onHttpRequestCompleted - Response code: %d",
          response->getResponseCode());
    
    if (!response->isSucceed())
    {
        CCLog("onHttpRequestCompleted - Response failed");
        CCLog("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    
    // Convert response to string
    std::string responseStr(buffer->begin(), buffer->end());
    CCLog("onHttpRequestCompleted - %s", responseStr.c_str());
    CCLog("onHttpRequestCompleted - Tag: %s", response->getHttpRequest()->getTag());
}



void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
