//Reward system made by Talamortis

#include "Configuration/Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Define.h"

bool RewardSystem_Enable;

class reward_system : public PlayerScript
{

public:
    reward_system() : PlayerScript("reward_system") {}

    uint32 initialTimer = (sConfigMgr->GetOption<uint32>("RewardTime", 1) * HOUR * IN_MILLISECONDS);
    uint32 RewardTimer = initialTimer;
    int32 roll;

    void OnBeforeUpdate(Player* player, uint32 p_time) override
    {
        if (sConfigMgr->GetOption<bool>("RewardSystemEnable", true))
        {
            if (RewardTimer > 0)
            {
                uint8 level = player->getLevel();
                if (level < 70) 
                {
                    RewardTimer = initialTimer;
                    return ;
                }
                if (player->isAFK())
                {
                    RewardTimer = initialTimer;
                    return;
                }

                if (RewardTimer <= p_time)
                {
                    roll = urand(1, 100);
                    if (roll < 20)
                    {
                        RewardTimer = initialTimer;
                        return;
                    }

                    uint32 pItem = sConfigMgr->GetOption<uint32>("itemId", 0);
                    uint32 quantity = sConfigMgr->GetOption<uint32>("quantity", 1);

                    // now lets add the item
                    //player->AddItem(pItem, quantity);
                    SendRewardToPlayer(player, pItem, quantity);
                    RewardTimer = initialTimer;
                }
                else  RewardTimer -= p_time;
            }
        }
    }

    void SendRewardToPlayer(Player* receiver, uint32 itemId, uint32 count)
    {
        if (receiver->IsInWorld() && itemId > 0 && count > 0) {
            receiver->AddItem(itemId, count);
        }
    }

};


void AddRewardSystemScripts()
{
    new reward_system();
}
