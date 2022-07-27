
#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "log.h"
#include "cutin_drawer.h"
#include "lottery.h"
#include "gara.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif

static PlaydateAPI* _pd;

enum MainState
{
    MainStateGara = 0,
    MainStateCutin,
    MainStateWaitButton
};

static enum MainState _state = MainStateGara;

void updateStateGara(void)
{
    PDButtons pushed;
    _pd->system->getButtonState(NULL, &pushed, NULL);
    if ( pushed & kButtonA )
    {
        const char *name = lottery();
        if (strcmp(name, "") != 0) {
            startCutin(name);
            _state = MainStateCutin;
        }
    }

    const float crankAngle = _pd->system->getCrankAngle();
    updateGara(crankAngle);
}

void updateStateCutin(void)
{}


void updateStateWaitButton(void)
{
    PDButtons pushed;
    _pd->system->getButtonState(NULL, &pushed, NULL);
    if ( pushed & kButtonA )
    {
        clearCutin();
        _state = MainStateGara;
    }
}

void updateCommon(void)
{
    _pd->graphics->clear(kColorWhite);
    updateCutin();

    _pd->sprite->drawSprites();
}

int update(void* ud)
{
    switch (_state) {
        case MainStateGara:
            updateStateGara();
            break;
        case MainStateCutin:
            updateStateCutin();
            break;
        case MainStateWaitButton:
            updateStateWaitButton();
            break;
    }

    updateCommon();

    return 1;
}

void cutinEnd(void)
{
    _state = MainStateWaitButton;
    LOG("Cut in end.");
}

static void initialize()
{
    initCutin(_pd);
    registerCutinEnd(&cutinEnd);

    registerLottery("AZUMA");
    registerLottery("AOKI");
    registerLottery("TATSUYA");
    registerLottery("MIURA");
    registerLottery("ITO");
    registerLottery("KAMIHAMA");
    registerLottery("YOSHIDA");
    registerLottery("KAKI");

    initGara(_pd);

    _state = MainStateGara;
}

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
    if (event == kEventInit)
    {
        _pd = pd;
        pd->system->setUpdateCallback(update, NULL);

        initialize();
    }

    return 0;
}