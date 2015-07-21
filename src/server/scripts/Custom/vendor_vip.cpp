/*
 * Copyright (C) 2013-2015 DeathCore <http://www.noffearrdeathproject.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */	

    // Depending how old your core is this may not be needed but it doesnt matter if its there or not.
    #include "ScriptPCH.h"
     
    //Change Me!
    #define VIP_TOKEN_ID 1337
         
    class VIP_NPC : public CreatureScript
    {
    public:
            VIP_NPC() : CreatureScript("VIP_NPC") { }
     
            bool OnGossipHello(Player* plr, Creature* crt)
            {
                    if (!plr->GetSession()->GetSecurity() == SEC_VIP)
                    {
                            crt->MonsterWhisper("Why are you here?  You are not a VIP!", plr->GetGUID());
                            //Change me!
                            plr->TeleportTo(1, -8790.0000f, 828.411987f, 97.642998f, 0.567000f);
                            plr->CLOSE_GOSSIP_MENU();
                            return false;
                    }
                    else
                    {
                            plr->ADD_GOSSIP_ITEM(6, "VIP VENDOR", GOSSIP_SENDER_MAIN, 0);
                            plr->PlayerTalkClass->SendGossipMenu(9452, crt->GetGUID());
                            return true;
                    }
            }
       
            bool OnGossipSelect(Player* plr, Creature* crt, uint32 sender, uint32 action)
            {
                    plr->PlayerTalkClass->ClearMenus();
                    switch (action)
                    {
                            case 0:
                                    plr->GetSession()->SendListInventory(crt->GetGUID());
                                    break;
                    }
                    return true;
        }
    };
     
    void AddSC_VIP_NPC()
    {
        new VIP_NPC();
    }

