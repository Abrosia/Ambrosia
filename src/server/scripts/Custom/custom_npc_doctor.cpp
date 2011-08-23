#include "ScriptPCH.h"

class custom_npc_doctor : public CreatureScript
{
private:
    void InitMainMenu(Player *player, Creature *_creature)
    {
        player->ADD_GOSSIP_ITEM(5, "Restore Health", GOSSIP_SENDER_MAIN, 101);
        player->ADD_GOSSIP_ITEM(5, "Restore Mana", GOSSIP_SENDER_MAIN, 102);
        player->ADD_GOSSIP_ITEM(5, "Remove Cooldown", GOSSIP_SENDER_MAIN, 103);

        switch(player->GetTeam())
        {
        case ALLIANCE:
            player->ADD_GOSSIP_ITEM(5, "Remove Exhaustion", GOSSIP_SENDER_MAIN, 104);
            break;
        case HORDE:
            player->ADD_GOSSIP_ITEM(5, "Remove Sated", GOSSIP_SENDER_MAIN, 105);
            break;
        default:
            break;
        }

        player->ADD_GOSSIP_ITEM(7, "Buffs", GOSSIP_SENDER_MAIN, 200);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
    }

public:
    custom_npc_doctor() : CreatureScript("custom_npc_doctor") { }

    bool OnGossipHello(Player *player, Creature *_creature)
    {
        if(player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat. Come back later!", player->GetGUID());
            return true;
        }

        InitMainMenu(player, _creature);
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        if(player->isInCombat())
        {
            player->CLOSE_GOSSIP_MENU();
            _creature->MonsterWhisper("You are in combat. Come back later!", player->GetGUID());
            return true;
        }

        if(sender != GOSSIP_SENDER_MAIN)
            return true;

        if(action != 666 || action != 200)
            player->CLOSE_GOSSIP_MENU();

        switch(action)
        {
        /****************************************************************************************
         *  MAINS                                                                               *
         ****************************************************************************************/
        case 101: //Restore Health
            player->SetHealth(player->GetMaxHealth());
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Your Health has been restored.", player->GetGUID());
            break;
        case 102: //Restore Mana
            player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Your Mana has been restored.", player->GetGUID());
            break;
        case 103: //Remove Cooldown
            player->RemoveAllSpellCooldown();
            player->CastSpell(player, 75459, false);
            _creature->MonsterWhisper("Your cooldowns have been removed.", player->GetGUID());
            break;
        case 104: //Remove Exhaustion
            player->RemoveAurasDueToSpell(57723);
            player->CastSpell(player, 61456, false);
            _creature->MonsterWhisper("Exhaustion has been removed.", player->GetGUID());
            break;
        case 105: //Remove Sated
            player->RemoveAurasDueToSpell(57724);
            player->CastSpell(player, 61456, false);          
            _creature->MonsterWhisper("Sated has been removed.", player->GetGUID());
            break;

        /****************************************************************************************
         *  BUFFS                                                                               *
         ****************************************************************************************/
        case 200:
            player->ADD_GOSSIP_ITEM( 5, "Arcane Intellect",              GOSSIP_SENDER_MAIN, 201);
            player->ADD_GOSSIP_ITEM( 5, "Mark of the Wild",              GOSSIP_SENDER_MAIN, 202);
            player->ADD_GOSSIP_ITEM( 5, "Thorns",                        GOSSIP_SENDER_MAIN, 203);
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Sanctuary", GOSSIP_SENDER_MAIN, 204);
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Might",     GOSSIP_SENDER_MAIN, 205);
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Kings",     GOSSIP_SENDER_MAIN, 206);
            player->ADD_GOSSIP_ITEM( 5, "Greater Blessing of Wisdom",    GOSSIP_SENDER_MAIN, 207);
            player->ADD_GOSSIP_ITEM( 5, "Divine Spirit",                 GOSSIP_SENDER_MAIN, 208);
            player->ADD_GOSSIP_ITEM( 5, "Shadow Protection",             GOSSIP_SENDER_MAIN, 209);
            player->ADD_GOSSIP_ITEM( 5, "Power Word: Fortitude",         GOSSIP_SENDER_MAIN, 210);
            player->ADD_GOSSIP_ITEM(11, "<- Back to Main Page",          GOSSIP_SENDER_MAIN, 666);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
            break;
        case 201: // Arcane Intellect
            _creature->CastSpell(player, 42995, false);
            break;
        case 202: // Mark of the Wild
            _creature->CastSpell(player, 48469, false);
            break;
        case 203: // Thorns
            _creature->CastSpell(player, 53307, false);
            break;
        case 204: // Greater Blessing of Sanctuary
            _creature->CastSpell(player, 25899, false);
            break;
        case 205: // Greater Blessing of Might
            _creature->CastSpell(player, 48934, false);
            break;
        case 206: // Greater Blessing of Kings
            _creature->CastSpell(player, 25898, false);
            break;
        case 207: // Greater Blessing of Wisdom
            _creature->CastSpell(player, 48938, false);
            break;
        case 208: // Divine Spirit
            _creature->CastSpell(player, 48073, false);
            break;
        case 209: // Power Word: Fortitude
            _creature->CastSpell(player, 48169, false);
            break;
        case 210: // Shadow Protection
            _creature->CastSpell(player, 48161, false);
            break;

        /****************************************************************************************
         *  MAIN MENU                                                                           *
         ****************************************************************************************/
        case 666:
            InitMainMenu(player, _creature);
            break;
        default:
            player->CLOSE_GOSSIP_MENU();
            break;
        }

        return true;

    }
};

void AddSC_custom_npc_doctor()
{
    new custom_npc_doctor();
}